/**
 * This program illustrates the functionality of the ipcs command on POSIX systems.
 *
 * sm.c
 *
 * Usage:
 *      gcc -o sm sm.c
 *
 *      ./sm 
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int segment_id;  			// identifier of the shared memory segment
	unsigned short mode;			// permissions of the segment
	struct shmid_ds shmbuffer; 		// the shared memory segment 

// Step 1: Create a new shared memory segment using shmget
	char *sm;				//pointer to the shared memory segment

	/*allocates a shared memory segment*/
	segment_id = shmget(IPC_PRIVATE, 100 * sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);;
	
	/*prints out the new memory segment*/
	printf("New memory segment is created: %d\n", segment_id);

// Step 2: Retrieve the information of the segment and store in shmbuffer

	if (shmctl(segment_id, IPC_STAT, &shmbuffer) == -1) {
		fprintf(stderr,"Unable to access segment %d\n",segment_id);
		return -1;
	}

// Step 3: output information about the segment in the required format

	/*prints in the fields*/
	printf("ID \t\t KEY \t MODE \t\t OWNER \t SIZE \t ATTTACHES \n");
	printf("-- \t\t --- \t ---- \t\t ----- \t ---- \t --------- \n");

	/*Prints the ID and key*/
	printf("%d \t\t %d \t", segment_id, shmbuffer.shm_perm.__key);

	/** report on the permission */
	mode = shmbuffer.shm_perm.mode;

	/** OWNER */
	if (mode & 0400)
		printf("r");
	else
		printf("-");
	if (mode & 0200)
		printf("w");
	else
		printf("-");
	if (mode & 0100)
		printf("x");
	else
		printf("-");

	/** GROUP */
	if (mode & 0040)
		printf("r");
	else
		printf("-");
	if (mode & 0020)
		printf("w");
	else
		printf("-");
	if (mode & 0010)
		printf("x");
	else
		printf("-");

	/** WORLD */
	if (mode & 0004)
		printf("r");
	else
		printf("-");
	if (mode & 0002)
		printf("w");
	else
		printf("-");
	if (mode & 0001)
		printf("x");
	else
		printf("-");

	printf("\t %d\t",shmbuffer.shm_perm.uid);	//Prints owner
	printf(" %zu\t",shmbuffer.shm_segsz);		//Prints size
	printf(" %ld\t",shmbuffer.shm_nattch);	//Prints number of attaches
	printf("\n");

// Step 4: Create a new process using fork

	pid_t cid = fork(); //cid is the new process

	/*error checking in case that fork failed*/
	if (cid < 0) { 
		fprintf(stderr, "Error! Fork failed!");
		return -1;
	}

// Step 5: The child process sends a message to the parent process via the 
//         shared memory segment created in Step 1 and the parent prints out 
//         the message it received from the child process

	if(cid == 0) // child process
	{		
	
		/*attach to the shared memory segment*/
		sm = (char *)shmat(segment_id, NULL, 0);

		/*another error checking just in case!*/
		if (sm == (char *)(-1)) {
				perror("unable to execute shmat");
				return -1;
		}
		
		/*saves shared memory as a string*/
		printf("%s\n", sm);
		
		/*send a message to the parent process via shared memory segment (using sprint)*/
		sprintf(sm, "Hello parent process!");
		pause();
	}

	else if (cid > 0) // parent process
	{
		/* sets parent on a nap because when I wrote wait (NULL), it'll wait for the child forever/a long time*/
		usleep(100); 
		//wait(NULL);
		
		/*attaches the sm so parent process can get access to it*/
		sm = (char *)shmat(segment_id, NULL, 0);

		if (sm == (char *)(-1)) {
				perror("unable to execute shmat");
				return -1;
		}
	
		/* prints out the message in the shared memory segment */
		printf("Parent received message from Child: %s\n", sm);

		/*detaches shared memory*/
		if (shmdt (sm) == -1) {
			fprintf(stderr, "Unable to detach!\n");
		}
		
		/*Destroys memory*/
		shmctl(segment_id, IPC_RMID, NULL);	
	}


    return 0;
}

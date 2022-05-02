#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
  
int main (int argc, char *argv[])
{
	int voters = 0;		//number of voter, the children
	int rounds = 5;		//number of rounds, I setted the limit
	int yes = 0, no = 0;		//integers to check for winner of the vote of the round, yes is 1, no is 0
	int yesPass =0, noPass = 0; 	//integers for the overall winner 
	int vote;			//the vote
	bool randVote;			//for the votes for later through checking if this is true or false and then set the votes
	time_t t;			//time to help with RNG later
	
	//Fun intro
	printf("Today, we will ask people to vote whether or not Big Foot is real! \n");
	printf("The majority vote wins! \n");
	
	//Step 1:Ask user to input number of voters (and max number of rounds if you want to set a limit)
	printf("Enter number of voters: ");
	scanf("%d", &voters);
	printf("\n");
	
	while (voters < 3) //if # of voters less than 3, it's invalid!
	{
		 printf("Invalid number of voters! \n");
		 printf("Enter a valid number of voters this time, thanks: ");
		 scanf("%d", &voters);
		 printf("\n");	
	}
	
	int pepper[voters][2];		//the pipe
	pid_t judge[voters];   	//the judge process id
	
	//Step 2 (loop):The judge process creates N pipes
	for (int i = 0; i < voters; i++)
	{
		if (pipe(pepper[i]) == -1)
		{
			perror("Unable to create pipe!");
        		exit(1);
		}	
	}
	
	//Step 3 (loop):The judge process creates N child processes.
	//(Only the judge process can call fork and child processes don’t call fork.)
	for (int i = 0; i < voters; i++) 
	{
		judge[i] = fork(); //judge forks to create child
		
		if (judge[i] < 0) //error message
		{
		   	perror("error calling fork()");
		    	exit(1);	
		}
		
		else if (judge[i] == 0) //child process
		{
			//makes sure that child processes don't call fork by breaking out and moving onto step 4
			break;
        	}
        	
        	else //parent process
        	{
        		//continues on to next iteration
        		continue;
        	}
	}
		
	//Step 4 (loop):At each round,For the judge process:
		//Collect votes from voters
		//Output the voting result
	//For each voter process:
		//Send the vote to the judge process (Voter Process i uses Pipe i to communicate with the judge)
	
	//for loop to go through the voter process
	for (int i = 0; i < voters; i++)
	{
		if (judge[i] == 0) //child process
		{
			close(pepper[i][0]);
			srand((int)time(&t) % getpid()); //Intializes random number generator
			randVote =  rand() & 1; //randomizes vote
			
			if (!randVote) {
				vote = 0; //If the bool is false, vote becomes 0
				//writes vote to the pipe(s)
				if (write(pepper[i][1], &vote, sizeof(vote)) == -1)
				{
					perror("writing error in pipe!");
					exit(1);
				}
			}
			
			else {
				vote = 1; //If the bool is true, vote becomes 1
				if (write(pepper[i][1], &vote, sizeof(vote)) == -1)
				{
					perror("writing error in pipe!");
					exit(1);
				}
			}
			
			
			if (write(pepper[i][1], &vote, sizeof(vote)) == -1)
			{
					perror("writing error in pipe!");
					exit(1);
			}
				
			exit(0);
        	}
	}
	
	//for loop to go through rounds and the judge process
	for (int i = 0; i < rounds; i++)
	{
		printf("Round %d \n", i + 1); //Prints what round it is
		
		//Judge process, in which it collects votes and outputs the results
		if (judge[i] > 0) //parent process
		{
			//for loop to get parent to get access to the child processes
			for (int j = 0; j < voters; j++) 
			{
				close(pepper[j][1]); //closes pipe
				
				//reads the votes from the child
				if (read(pepper[j][0], &vote, sizeof(vote)) == -1) {
					perror("read() error in the parent");
					exit(1);
				}
	     			
	     			else {
	     				printf("judge read '%d'\n", vote);
	     			}
	     			
	     			//Checks for the value of the vote and adds to no or yes depending on the value
	     			if (vote == 0) {
     					no++;
     				}
     			
     				else if (vote == 1) {
     					yes++;
     				}
     			}
		}
		
		//This section is where the yes and no will be counted for the round
		printf("Now, we will count the votes for this round!\n");
		if (yes > no) 
		{
			printf("For round %d: Yes, Big Foot is real!\n", i);
			yesPass++;
		}
							
		else if (no > yes) 
		{
			printf("For round %d: No, Big Foot is not real!\n", i);
			noPass++;
		}
							
		else 
		{
			printf("Well, there seems to be a tie on whether or not Big Foot is real on round %d!\n", i);
		}
	}
	
	//This section is where the previous winners will be counted for the final result
	printf("Now, for the winner!\n");
	if (yesPass > noPass) 
	{
		printf("The majority voted %d times out of %d rounds that Big Foot is definitely real!\n", yesPass, rounds);
	}
						
	else if (noPass > yesPass) 
	{
		printf("The majority voted %d times out of %d rounds that Big Foot is totally not real!\n", noPass, rounds);
	}
						
	else 
	{
		printf("Well, it seems like the voters can't decide whether or not Big Foot is real!\n");
	}
			
	//closes pipes
	for (int i = 0; i < pepper[i][2]; i++) {
		close(pepper[i][0]);
		close(pepper[i][1]);
		close(pepper[i][2]);
	}
	
	return 0;
}

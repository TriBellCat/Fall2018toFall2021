#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

typedef struct queue Node;
struct queue 
{
	int cliID;
	int cutTime;
	Node *next;
};

/*GLOBAL VARIABLES*/
int n, stop, min, max, chairs; //Input variables; will be used later
int isSleeping;		//0 is when the barber is awake, 1 is when he's sleeping
int cliCountAssign;		//Assigns the customer ID/number through counting a counter
int clientBeingCut;
int cutTime;
int count;
Node **waitSlotsNum;		//Number of waiting slots avaiable
pthread_mutex_t lockMan;

/*FUNCTION DECLARATIONS*/
void *customerFunction();
void *barberFunction();
int randTime(int, int);


int main() {
	int i, j;	//iterators
	
	printf("Welcome to the sleeping barber simulator!\n");
	
	/*USER INPUT*/
	printf("Enter your number of customers: ");
	scanf("%d",&n);
	printf("\n");
	
	while (n < 0) {
		printf("Invalid number! Enter your number of customers: ");
		scanf("%d",&n);
		printf("\n");
	}
	
	printf("Enter how long to run the simulation: ");
	scanf("%d",&stop);
	printf("\n");
	
	while (stop < 0) {
		printf("Invalid number! Enter the amount of seconds to run the simulation: ");
		scanf("%d",&stop);
		printf("\n");
	}
	
	printf("Enter the minimum random value to generate: ");
	scanf("%d",&min);
	printf("\n");
	
	while (min < 0) {
		printf("Invalid number! Enter a minimum random value to generate: ");
		scanf("%d",&min);
		printf("\n");
	}
	
	printf("Enter the maximum random value to generate: ");
	scanf("%d",&max);
	printf("\n");
	
	while (max < 0||max < min) {
		printf("Invalid numer! Enter the maximum random value to generate: ");
		scanf("%d",&min);
		printf("\n");
	}
	
	printf("Enter the number of waiting chairs in the waiting room to generate: ");
	scanf("%d",&chairs);
	printf("\n");
	
	while (max < 0||max < min) {
		printf("Invalid numer! Enter your number of customers: ");
		scanf("%d",&min);
		printf("\n");
	}
	
	//Allocates memory into the number of waiting slots available
	waitSlotsNum = malloc(chairs * sizeof(waitSlotsNum[0]));
	
	//Sets up the condition for the end time
	time_t endAt;
	time_t start = time(NULL);
	time_t end = stop;
	endAt = start + end;

	//Intializes the global variables
	count = 0;
	cliCountAssign = 1;
	isSleeping = 1;
	cutTime = 0;
	
	pthread_t barber, customers[n];	//declares the pthreads for barber and customers respectively
	//Creates the barber 
	pthread_create(&barber, NULL, barberFunction, NULL);
	
	//Creates the clients through a for loop
	for (i = 0; i < n; i++) {
		pthread_create(&customers[i], NULL, customerFunction, NULL);
	}
	
	//Until we run out of time, loop the main thread
	while(1)
	{
		//If we have run out of time yet
		if(start < endAt)	
		{
			sleep(1);
			start = time(NULL);
		}
		
		//We ran out of time
		else			
		{
			//Cancels the execution of the barber
			pthread_cancel(barber);	
			for(i = 0; i < n; i++)
			{
				//cancels the execution of the customer
				pthread_cancel(customers[i]);	
			}
			//Closing message
			printf("Time's up! The barber will close the salon!\n");
			break;
		}
	}
	//Frees up the assigned waiting memory
	for(i = 0; i < chairs; i++)
	{
		free(waitSlotsNum);
		waitSlotsNum = NULL;
	}
}


//Customer function, goal is to wake up the barber and gets a haircut; client ID is randomized too
void *customerFunction() 
{
	//Locks thread, assigns client ID through a counter, that counter goes up for the next client, unlocks the thread again
	pthread_mutex_lock(&lockMan);
	int cliID = cliCountAssign;
	cliCountAssign = cliCountAssign + 1;
	pthread_mutex_unlock(&lockMan);
	
	int aT;		//arrival time
	int clientCutTime;	//client cut time
	
	//Locks thread and then unlocks it again
	pthread_mutex_lock(&lockMan);
	pthread_mutex_unlock(&lockMan);
	
	//Sets up data for client
	Node *client = NULL;
	client = (Node*)malloc(sizeof(Node));
	client->cliID = cliID;
	
	//Puts the customer through a continous loop
	while(1)
	{
	
		aT = randTime(min, max);
		clientCutTime = randTime(min, max);
		client->cutTime = clientCutTime;
		sleep(aT);
		pthread_mutex_lock(&lockMan);
		
		//Barber is available or there are available waiting slots
		if (count <= chairs)
		{
			//If there are no other clients and the barber is available, customer goes to the barber
			if (count == 0)
			{
				isSleeping = 0; 		//Wakes up the barber;
				count = count + 1;		//Number of customers in the queue goes up
				clientBeingCut = cliID;	//Sets up the ID of the client getting a haircut
				cutTime = clientCutTime;	//Initializes the cutting time with the randomized cut time
				printf("Customer %d went to the barber and woke him up!\n",clientBeingCut);
				pthread_mutex_unlock(&lockMan);
			}
			
			//If there are clients in line, or there's one getting a haricut, this customer waits
			else
			{
				printf("Customer %d is in the queue.\n",cliID);
				waitSlotsNum[count-1] = client;	//Sets a client to waiting
				count = count + 1;		//The number of customers in the queue goes up
				pthread_mutex_unlock(&lockMan);
			}
			
		}
		
		//Barber isn't available or there are no available waiting slots
		else 
		{
			pthread_mutex_unlock(&lockMan);
			printf("Customer %d left because there isn't enough waiting seats and barber isn't available.\n", cliID);
		}
		
	}
}

//Barber function, goal is to sleep until a customer wakes up the barber and to give them a haircut
void *barberFunction()
{
	int i, j;
	//Puts the barber through a continous loop
	while (1) 
	{
		//The barber's going to be asleep until a customer wakes him up
		while(isSleeping == 1)
		{
			printf("The barber is having a beauty sleep!\n");
			sleep (1);
		}
		
		//What the barber will do while he's awake
		while (isSleeping == 0)
		{
			pthread_mutex_lock(&lockMan);	//locks the mutex until the Barber is done with the client or sleeping
			printf("Client %d's hair cut is %d seconds.\n",clientBeingCut,cutTime);
			isSleeping = 0;	//Set the barber to be still awake
			count = count - 1;	//The number of clients waiting goes down by 1
			sleep(cutTime);	//waits for the haircut to be done
			
			//If there's no clients waiting, the Barber goes back to sleep
			if (count == 0)
			{
				cutTime = 0;
				isSleeping = 1;
				pthread_mutex_unlock(&lockMan);
				break;
			}
			
			//If there's at least one or more client waiting, moves onto them
			else
			{
				//initializes data for client
				Node *client = waitSlotsNum[0];	
				clientBeingCut = client->cliID;
				cutTime = client->cutTime;
				
				//Nested for loop to move customers up the waiting list
				for (i = 0; i < count - 1; i++) {
					for (j = i+ 1; j > count; j++) {
						waitSlotsNum[i] = waitSlotsNum[j];
						waitSlotsNum [j] = NULL;
					}
				}
				isSleeping = 0;
				pthread_mutex_unlock(&lockMan);
			}
		}
	
	}
}
//Generates a random time between the min and max random number values
int randTime(int min, int max) {
	return rand() % (max + 1 - min) + min;
}

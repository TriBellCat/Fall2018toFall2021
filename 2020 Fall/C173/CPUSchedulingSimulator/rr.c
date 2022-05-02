#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

//Round Robin (RR) algorithm
void rr (int n, int pid[], int at[], int bt[], int tq)
{
	int i;						//for increments
	int ct[20];					//end/completion time
	int wt[20]; 					//waiting time
	int st[20];					//starting time
	int rt[20];					//run time
	int tat[20];
	
	int temp = 0, flag = 0, remain = n;		//more increments for a for loop
	int wait = 0;					//waiting time, but as an integer
	int turn = 0;					//turning time, but as an integer
	int runTi = tq, curTime = 0;			//running time and current time, but as integers
	int tempBT[20], tempCT[20]; 			//temporary values for bt and ct

	printf("RR (time quantum = %d)\n", tq);

	ct[0]=bt[0];			//sets the first value of ct to that of bt
	st[0] = 0;			//starting time starts at 0
	
	//calculates ct, skips to the second value considering that I set ct[0] to equal bt[0]
	for(i=1;i<n;i++)
	{
		ct[i]=ct[i-1]+bt[i];
		st[i] = ct[i-1]; 
	}
	
	//sets up temp values and running time
	for (i = 0; i < n; i++)
	{
		rt[i] = bt[i];
		tempBT[i] = bt[i];
		tempCT[i] = ct[i];
	}
	
	//Calculates current output
	printf("Process\t\tST\t\tET\t\tRT\n");
	
	//Goes through a for loop to sort and calculate values
	for (temp = 0, i = 0; remain !=0;)
	{
		//Checks if the value of st[i] is -1, and then changes it value to the current time if it is
		if (st[i] == -1) 
		{
			st[i] = curTime;
		}
			
		//Checks if the value of bt[i] is less than tq, then changes runTi	
		if (bt[i] < tq) 
		{
			runTi = bt[i];
		}
				
		else {
			runTi = tq;
		}
		
		printf("%d\t\t%d",pid[i], curTime);	
		curTime += runTi;	
		bt[i] -= runTi;
		tempCT[i] = ct[i];
		ct[i] = curTime; 
		
		printf("\t\t%d\t\t%d\n", curTime, runTi);
		
		//If rt[i] is less than or equal to tq and it's greater than 0, temprory store it, set rt[i] = 0, and change flag
		if (rt[i] <= tq && rt[i] >0)
		{
			temp += rt[i];
			rt[i] = 0;
			flag = 1;
		}
		
		//Else if rt[i] > 0, set rt[i] to minus tq and then temporarily add that value
		else if (rt[i] > 0)
		{
			rt[i] -= tq;
			temp += tq;
		}
		
		//If rt[i] equals 0 and flag is 1, remain decrements, do calculations, and flag becomes 0 again
		if (rt[i] == 0 && flag == 1)
		{
			remain--;
			wait = temp - at[i] - tempBT[i];
			turn = temp - at[i];
			wt[i] = wait;
			tat[i] = turn;
			flag = 0; 
		}
		
		//From this section check for the values of i
		if (i == n -1) 
		{
			i = 0;
		}
		
		else if(at[i+1]<=temp) 
		{
			i++;
		}
		
		else
		{
			i = 0;
		}
	}
	
	//sets first value of tempCT to be the last ending time
	for (int i = 0; i < n; i++) {
		tempCT[0] = curTime;
	}
	
	//Prints out pid, arriving time, running time, end time, and waiting time
	printf("\n");
	
	printResults(n, pid,at, tat, st, tempCT, tempBT, wt); 
}

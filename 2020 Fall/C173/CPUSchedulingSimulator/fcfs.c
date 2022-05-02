#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

//First Come First Serve (FCFS) alogrithm
void fcfs (int n, int pid[], int at[],int bt[])
{
	int ct[20];			//end/completion time
	int tat[20];			//turnaround time
	int wt[20];			//waiting time
	int st[20];			//start time
	int i;				//increments
	
	printf("FCFS\n");
	
	ct[0]=bt[0];			//sets the first value of ct to that of bt
	st[0] = 0;			//starting time starts at 0
	
	//calculates ct, skips to the second value considering that I set ct[0] to equal bt[0]
	for(i=1;i<n;i++)
	{
		ct[i]=ct[i-1]+bt[i];
		st[i] = ct[i-1]; //starting time equals the previous end time
	}

	//Calculates tat and wt
	for(i=0;i<n;i++)
	{
		tat[i]=ct[i]-at[i];
		wt[i]=tat[i]-bt[i];
	}

	//Calls function to print results
	printResults(n, pid, at,tat, st,ct,bt, wt);
}

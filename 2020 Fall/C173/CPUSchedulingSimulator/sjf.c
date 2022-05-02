#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

//Shortest Job First (SJF) algorithm 
void sjf (int n, int pid[], int at[], int bt[])
{
	int i,j;				//for increments
	int ct[20];				//end/completion time
	int wt[20]; 				//waiting time
	int st[20];				//starting time
	int tat[20];				//turnaround time
	int temp;				//an integer to temporarily store values
	
	printf("SJF \n");
	//sorts at, pid, and bt
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(at[i]>at[j])
			{
				temp=at[i];
				at[i]=at[j];
				at[j]=temp;
						
				temp=pid[i];
				pid[i]=pid[j];
				pid[j]=temp;
						
				temp=bt[i];
				bt[i]=bt[j];
				bt[j]=temp;
							
			}
		}
	}
	
	//calculates end time	
	ct[0]=bt[0]+at[0];
	
	//checks if the first value of end time greater than the previous arrival time
	if(ct[0]>at[n-1])
	{
		//sorts at, pid, and bt again
		for(i=1;i<n;i++)
		{
			for(j=i+1;j<n;j++)
			{
				if(bt[i]>bt[j])
				{
					temp=at[i];
					at[i]=at[j];
					at[j]=temp;
							
					temp=pid[i];
					pid[i]=pid[j];
					pid[j]=temp;
							
					temp=bt[i];
					bt[i]=bt[j];
					bt[j]=temp;
								
				}
			}
		}
	
		//sets up turn around time around time and waiting time
		tat[0]=bt[0];
		wt[0]=0;
				
		//calculate completion time
		for(i=1;i<n;i++)
		{
			ct[i]=abs(ct[i-1]+bt[i]);		
		}
	}
	
	//otherwise, i goes up to 2 and j is added by one for the second sorting after the first one
	else
	{
		for(i=1;i<n;i++)
		{
			for(j=i+1;j<n;j++)
			{
				if(at[i]>at[j])
				{
					temp=at[i];
					at[i]=at[j];
					at[j]=temp;
							
					temp=pid[i];
					pid[i]=pid[j];
					pid[j]=temp;
							
					temp=bt[i];
					bt[i]=bt[j];
					bt[j]=temp;
								
				}
			}
		}
				
		ct[1]=bt[1]+at[1];
				
		for(i=2;i<n;i++)
		{
			for(j=i+1;j<n;j++)
			{
				if(bt[i]>bt[j])
				{
					temp=at[i];
					at[i]=at[j];
					at[j]=temp;
							
					temp=pid[i];
					pid[i]=pid[j];
					pid[j]=temp;
							
					temp=bt[i];
					bt[i]=bt[j];
					bt[j]=temp;					
				}
			}
		}
				
		tat[0]=bt[0];
		wt[0]=0;
					
		//calculates completion time	
		for(i=2;i<n;i++) 
		{
			ct[i]=abs(ct[i-1]+bt[i]);		
		}
	}
			
	//calculates turn around time
	for(i=0;i<n;i++) {
		tat[i]=abs(ct[i]-at[i]);		
	}
	
	//calculates waiting time
	for(i=0;i<n;i++) {
		wt[i]=abs(tat[i]-bt[i]);		
	}
	
	//sets up starting time
	st[0] = 0;			
	for(i=1;i<n;i++)
	{
		
		st[i] = ct[i-1]; 
	}
		
	//calls function to print the results
	printResults(n,pid,at,tat,st,ct,bt,wt);
}

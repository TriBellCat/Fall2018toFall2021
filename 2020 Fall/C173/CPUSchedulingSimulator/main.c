#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fcfs.h"
#include "sjf.h"
#include "rr.h"

//Function to print the final result
void printResults(int n, int pid[],int at[],int tat[], int st[],int ct[],int bt[],int wt[]) 
{
	float atat=0;			//average turnaround time
	float awt=0;			//average waiting time
	float act=0;			//average completion time
	
	printf("Process\t\tAT\t\tST\t\tET\t\tRT\t\tWT\t\tTAT\n");
	
	for(int i=0;i<n;i++)
	{
		printf(" %d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",pid[i],at[i],st[i],ct[i],bt[i],wt[i],tat[i]);
		act=act+ct[i];
		awt=awt+wt[i];
		atat=atat+tat[i];
	}
	
	//Calculates the final average time
	act=act/n;
	awt=awt/n;
	atat=atat/n;
	
	//Prints the final average time
	printf("Average Completion Time: %f\n",act);
	printf("Average Waiting Time: %f\n",awt);
	printf("Average Turnaround Time: %f\n",atat);
}

int main(int argc, char *argv[]) {
	FILE *fp; 		//input file
	
	int pid [20];		//the pid
	int at  [20];		//arrival time
	int bt  [20];		//burst time
	int n;			//the number of processes
    	int time_quantum = 1;	//time quantum, defaults to 1
	int swi;		//Switch for the process that the user choses
	
	if (argc < 3) {
		fprintf(stderr, "input must be ./lab5 input_file [FCFS|RR|SJF] [time_quantum]\n");
		exit(-1);
	}
		
	//fname = argv[1];
		
	fp = fopen (argv[1],"r");
	
	if (fp == NULL) {
		exit(EXIT_FAILURE);
	}	
	
	if (strcmp(argv[2], "FCFS") == 0)
	{
		swi = 1;
	}
	
	else if (strcmp(argv[2], "SJF") == 0)
	{
		swi = 2;
	}	
	
	else if (strcmp(argv[2], "RR") == 0)
	{
		swi = 3;
		time_quantum = atoi(argv[3]);
		if (time_quantum <= 0 || (!(time_quantum <= 0) && !(time_quantum >= 0))) {
			fprintf(stderr, "invalid time_quantum!\n");
			exit(-1);
		}
	}	
	
	fscanf(fp, "%d", &n); //gets the number of processes
	
	//through a for loop, scan through the rest of the file to get information for pid, at, and bt
	for (int i = 0; i < n; i++) {
		fscanf(fp, "%d %d %d", &pid[i], &at[i], &bt[i]);
	}
	
	switch (swi) {
		case 1:
			//calls fcfs
			fcfs(n, pid, at,bt);
			break;
		
		case 2:
			//calls sjf
			sjf (n, pid, at, bt);
			break;
		
		case 3:
			//calls rr
			rr (n, pid, at, bt,time_quantum);
			break;
		default:
			printf("Invalid method!");
	}
	//Closes the file
	fclose(fp);
}


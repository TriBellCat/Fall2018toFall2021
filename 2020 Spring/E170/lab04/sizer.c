//Trinity Caitlin Atayan Belen
//t_belen@u.pacific.edu
//ECPE 170

//Description: Gets the size of the board
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include "size.h"
#include "clue.h"

Size sizer()
{
  	char letter[256];//Array to store letters
  	int w, c, s; //Width, Column, Size
  	FILE* file; //file to call later
  	Size obj; //Size object   

	printf("Enter game filename to load: ");
  	scanf("%s",letter);//Scans file for letter
  	file=fopen(letter,"r");//Opens and read the file
	
	//Error statement if there is no file
  	if(file==NULL)
  	{
   		printf("\nFile isn't there!\n");
   	}

	//Scans the width, height, and size of the file
  	fscanf(file,"%d %d %d",&w, &c, &s);
	
	//Saves information into the size object
	obj.width=w;
	obj.height=c;
	obj.numLetter=s;
  	obj.fp = file;
	
  	strcpy(obj.fileText,letter);//Copies letter into the file
	
  	return obj;
}

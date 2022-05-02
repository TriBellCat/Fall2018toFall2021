#include <stdio.h>
#include <stdint.h>

#include "main.h"

int main() {
 uint32_t array1[3][5] = {{1,2,3,4,5}, {11,12,13,14,15},{-1,-3,-5,-6,-7}}; 
    uint32_t array2[2][3][4] = {
    {{3, 4, 2, 3}, {0, -3, 9, 11}, {23, 12, 23, 2}},
    {{13, 4, 56, 3}, {5, 9, 3, 5}, {3, 1, 4, 9}}};
 uint32_t i, j, k;

 printf("Allocating a 2D Array:\n");
 for(i=0; i<3; i++) {
      for(j=0;j<5;j++) {
	     printf("Array Initialization Value: %d ", array1[i][j]);
             printf("Memory Address : %p\n", &array1[i][j]);
      }
  }

 printf("\nSince the unsigned 2d array is initialized to {1,2,3,4,5}, {11,12,13,14,15},{-1,-3,-5,-6,-7}, which is 3 rows and 5 columns, it goes like: a[0][0] a[0][1] a[0][2] a[0][3] a[0][4] a[0][5], a[1][0] a[1][1] a[1][2] a[1][3] a[1][4] a[1][5], a[2][0] a[2][1] a[2][2] a[2][3] a[2][4] a[2][5]. The program goes through two for loops for the rows and column; starting from row 0 and column 0, stepping through each row and then advancing to the columns and repeat. Then it'll print the memory address for each of the values.\n");

 printf("Allocating a 3D Array:\n");
 for(i=0; i<2; i++) {
      for(j=0;j<3;j++) {
		for (k=0; k< 4; k++) {
			printf("Array Number: %d ", array2[i][j][k]);
         		printf("Memory Address : %p\n", &array2[i][j][k]);
		}
      }
  }

printf("\n The same process for the 2D array applies to the 3D array, except it goes through three for loops, one for each dimension. \n");
}

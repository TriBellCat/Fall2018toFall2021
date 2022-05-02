#include "config.h"
#include "vec.h"
#include "combine.h"

#include <stdio.h>

// ORIGINAL function.
// This combiner function uses the greater amount
// of abstraction to operate, but has the slowest
// performance.
void combine1(vec_ptr v, data_t *dest)
{
  printf("Running combine1() - No code-level optimizations\n");

  long int i;

  *dest = IDENT;

  for(i=0; i < vec_length(v); i++)
    {
      data_t val;
      get_vec_element(v, i, &val);
      *dest = *dest OP val;
    }
}


// CODE MOTION OPTIMIZATION:

// Move the call to vec_length() out of the loop
// because we (the programmer) know that the vector length will
// not change in the middle of the combine() function. 
//  The compiler, though, doesn't know that!
void combine2(vec_ptr v, data_t *dest)
{
  printf("Running combine2()\n");
  printf("Added optimization: Code motion\n");

  // XXX - STUDENT CODE GOES HERE - XXX

   long int i;
   *dest = IDENT;
   long int length =  vec_length(v);
   for(i=0; i < length; i++)
   {
      data_t val;
      get_vec_element(v, i, &val);
      *dest = *dest OP val;
   }
}


// REDUCING PROCEDURE CALLS OPTIMIZATION:

// This optimization eliminates the function call to
// get_vec_element() and accesses the data directly,
// trading off higher performance versus some loss
// of program modularity.
void combine3(vec_ptr v, data_t *dest)
{
  printf("Running combine3()\n");
  printf("Added optimization: Reducing procedure calls\n"); 

  // XXX - STUDENT CODE GOES HERE - XXX
  data_t *val = get_vec_start(v);
  long int i;
  *dest = IDENT;
  long int length =  vec_length(v);
  for(i=0; i < length; i++)
  {
      *dest = *dest OP val[i];
  }
}


// ELIMINATING UNNEEDED MEMORY ACCESSES OPTIMIZATION:

// This optimization eliminates the trip to memory
// to store the result of each operation (and retrieve it
// the next time). Instead, it is saved in a local variable 
// (i.e. a register in the processor)
// and only written to memory at the very end.
void combine4(vec_ptr v, data_t *dest)
{
  printf("Running combine4()\n");
  printf("Added optimization: Eliminating unneeded memory accesses\n");

  // XXX - STUDENT CODE GOES HERE - XXX
  data_t *val = get_vec_start(v);
  long int i;
  data_t accumulate = IDENT;
  long int length = vec_length(v);
  for (i = 0; i<length; i++) 
  {
      accumulate = accumulate OP val[i];
  }
  
  *dest = accumulate;

}


// LOOP UNROLLING x2
// (i.e. process TWO vector elements per loop iteration)
void combine5x2(vec_ptr v, data_t *dest)
{
  printf("Running combine5x2()\n");
  printf("Added optimization: Loop unrolling x2\n");


  // XXX - STUDENT CODE GOES HERE - XXX
	data_t *val = get_vec_start(v);
	long int i;
  	long int length = vec_length(v);
	long int limit = length-1;
	data_t accumulate = IDENT;

	for (i = 0; i < limit; i+=2) {
		accumulate = (accumulate OP val[i]) OP val[i+1];
	}
	
	for (; i < length; i++) {
		accumulate = accumulate OP val[i];
	}
	*dest = accumulate;
}

// LOOP UNROLLING x3
// (i.e. process THREE vector elements per loop iteration)
void combine5x3(vec_ptr v, data_t *dest)
{
  printf("Running combine5x3()\n");
  printf("Added optimization: Loop unrolling x3\n");

  	// XXX - STUDENT CODE GOES HERE - XXX
	data_t *val = get_vec_start(v);
	long int i;
  	long int length = vec_length(v);
	long int limit = length-1;
	data_t accumulate = IDENT;

	for (i = 0; i < limit; i+=3) {
		accumulate = (accumulate OP val[i]) OP val[i+1];
	}
	
	for (; i < length; i++) {
		accumulate = accumulate OP val[i];
	}
	*dest = accumulate;
}


// LOOP UNROLLING x2 + 2-way parallelism
void combine6(vec_ptr v, data_t *dest)
{
  printf("Running combine6()\n");
  printf("Added optimization: Loop unrolling x2, Parallelism x2\n");

 	 // XXX - STUDENT CODE GOES HERE - XXX
	data_t *val = get_vec_start(v);
  	long int i;
	long int length = vec_length(v);
	long int limit = length -1;
	data_t accumulate0 = IDENT;
	data_t accumulate1 = IDENT;

	for (i = 0; i < limit; i+=2) {
		accumulate0 = accumulate0 OP val[i];
		accumulate1 = accumulate1 OP val[i+1];
	}

	for (; i < length; i++) {
		accumulate0 = accumulate0 OP val[i];
	}
	*dest = accumulate0 OP accumulate1;
}

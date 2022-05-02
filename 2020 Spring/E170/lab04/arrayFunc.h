//Trinity Caitlin Atayan Belen
//t_belen@u.pacific.edu
//ECPE 170

#include "clue.h"
#include "size.h"

#ifndef ARRAYFUNC_H
#define ARRAYFUNC_H

struct Board** createBoard( Size clue);

void makeBoard( Clue **arr,  Size clue);

void printBoard( Clue** arr,  Size clue);

void updateBoard ( Clue** arr,  Clue* clue,  Size size);

#endif


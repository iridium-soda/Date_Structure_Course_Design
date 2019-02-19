#pragma once
# include "stdio.h"
# include "io.h"
# include <stdlib.h>
#include <iostream>
#include <string>

typedef struct cnfdata
{
	int units;
	int clauses;
	int** matrix;
}cnf;

typedef struct openode
{
	int unit;//Non-0 style;1=NEG
	int **mairix;//Zipped matrix
	int *solution;//To store current Solution
	int unis;//To save its current number of the units
}Node;

void Lisence();// To show Lisence information
char* Folderanlysis();//folder read and analysis
cnf* Fileread(char* filename);//read file and return struct pointer
int* DPLL(cnf* input);//Standard DPLL ,return solution group's pointer
int scan_single(int** matrix, int Row, int Column);//Scan Matrix and return the first single clause's UNIT in non-0 style
// If it only has ONE POSTIVE unit,return positive number
// If it only has ONE NEGATIVE unit,return negative number;
int scan_endflag(int** matrix, int row, int column);
//To judge if any special potisition(all 255 or a line 0)
//If all 255, return 1
//If any 0, return -1
//Return 0 means nothing happens

void operate(int flag, int unit, int parameter, int** matrix, int row, int column, int* solution);
//To operate the matrix.
//Flag=0->remove single clauses,parameter is the lines of the single clause(if Neg,Unit is Neg)
//Flag=1->Assign the unit and Remove the same and Delete the diffierent,patameter is 255
//Unit =Pos Or Neg represent the Assignment should be Pos or Neg

void push(Node* point, Node** top);//push in
void pop(Node* point, Node** top);//Pop to the pointer
void showmartix(int** matrix, int row, int column);
void showsolution(int* solution, int units);
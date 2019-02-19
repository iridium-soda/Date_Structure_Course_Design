#include "head.h"
int* DPLL(cnf* input)//If success,return int*->solution;if fail or error,return NULL
{
	Node* stack[1024];
	memset(stack, NULL, 1024);//Stack space
	//Empty stack requirement: top=stack[0]
	Node** top = &stack[0];//Top pointer points to the first empty space
	//Origin Solution Space:first is 0000, and pass by Assignment Operation
	int* current_solution = (int*)malloc(sizeof(int)*input->units);
	memset(current_solution, 0, input->units * sizeof(int));
	printf("[INFO] Origin Solution Space has been set up\n");

	int i, j;
	int unit;//Focoused unit
	int endflag = 0;
	int track_flag = 0;
	Node* neg_node ;
	Node* current_node = NULL;
	int unis = 0;
	int ksbr = 0;
	int** matrix = (int **)malloc(sizeof(int*)*input->clauses);
	for (i = 0; i < input->clauses; i++)
	{
		matrix[i] = (int*)malloc(sizeof(int)*input->units);
	}
	for (i = 0; i < input->clauses; i++)
	{
		for (j = 0; j < input->units; j++)
		{
			matrix[i][j] = input->matrix[i][j];
		}
	}//Copy origin matrix data
	printf("[INFO] Origin matrix has been set up\n");
	do
	{
		if (track_flag == 0)
		{
			if (unit = scan_single(matrix, input->clauses, input->units), unit != 0)//Have single clause
			{
				printf("[INFO] Single clause detected:unit %d \n", abs(unit));
				current_solution[abs(unit) - 1] = unit / abs(unit);
				for (i = 0; i < input->clauses; i++)
				{
					if (matrix[i][abs(unit) - 1] == unit / abs(unit))
					{
						for (j = 0; j < input->clauses; j++)
						{
							matrix[i][j] = 255;
						}
						printf("[INFO] The pos_clause %d has removed\n", i);
					}
					//Remove Same clause
					else
						if (matrix[i][abs(unit) - 1] == -unit / abs(unit))
						{
							matrix[i][abs(unit) - 1] = 0;
							printf("[INFO] The neg_clause%d's unit has removed\n", i);
						}//Delete different unit
				}
				goto Judgement;
				//Seem here should be an exit
			}
			else
			{
				//Assignment part
				unit = 0;//Reset Focous unit
				for (i = 0; i < input->units; i++)
				{
					if (current_solution[i] == 0)
						unit = i + 1;//Set the first 0 unit as the focous
				}
				if (unit == 0)
				{
					printf("[ERROR] Assignment unit select error\n");
					showsolution(current_solution, input->units);
					return NULL;
				}//select an unit to assign

				neg_node = (Node*)malloc(sizeof(Node));
				if (neg_node == NULL)
				{
					printf("[ERROR] The operation space of the operation node failed to apply. \n");
					return NULL;
				}//Apply one  node to store operation information in the stack
				neg_node->unit = unit;//To be a neg node warning: unit is a non-0 style number
				printf("[INFO] Neg node's foucous unit has loaded\n");
				//Assign the neg node
				//Zip the matrix
				unis = 0;
				ksbr = 0;
				for (i = 0; i < input->clauses; i++)
				{
					for (j = 0; j < input->units; j++)
					{
						if (matrix[i][j] != 0)
							unis++;
					}
				}//To stat the number of the units.
				neg_node->mairix = (int**)malloc(sizeof(int*)*unis);
				neg_node->unis = unis;//The rows of the zipped matrix
				for (i = 0; i < unis; i++)
				{
					neg_node->mairix[i] = (int*)malloc(sizeof(int) * 2);
				}//Set up a zipped matrix
				//Zipped matrix format: Row|Column(1->+,-1->-)
				//Zipped matrix's information is non-0 style
				for (i = 0; i < input->clauses; i++)
				{
					for (j = 0; j < input->units; j++)
					{
						if (matrix[i][j] != 0)
						{
							neg_node->mairix[ksbr][0] = i + 1;//NON-0 STYLE
							neg_node->mairix[ksbr][1] = j + 1;
							if (matrix[i][j] == -1)
								neg_node->mairix[ksbr][1] *= -1;
							ksbr++;
						}
				}//Load zipped information of the matrix
				printf("[INFO] Zipped matrix has been set up and load\n");
				//Solution Backup
				neg_node->solution = NULL;
				neg_node->solution = (int*)malloc(sizeof(int)*(input->units));
				for (i = 0; i < input->units; i++)
				{
					neg_node->solution[i] = current_solution[i];
				}

				printf("[INFO] Solution backup has been set up and load\n");
				//Push in the stack
				push(neg_node, top);
				//free(neg_node);
				neg_node = NULL;//Free and Reset
				printf("[INFO] The node has been pushed\n");
				//Operate the pos node
				current_solution[unit - 1] = 1;
				printf("[INFO] Solution updated\n");
				for (i = 0; i < input->clauses; i++)
				{
					if (matrix[i][unit - 1] == 1)
					{
						for (j = 0; j < input->units; j++)
						{
							matrix[i][j] = 255;
						}//Remove pos clause
					}
					if (matrix[i][unit - 1] == -1)
					{
						matrix[i][unit - 1] = 0;
					}
				}
				printf("[INFO] The unit %d has operated\n", unit - 1);
				//An exit here-Jump to Judgement directily
			}
		}
		//DOING: Place the re-track part here
		else
		{
			track_flag = 0;//Reset flag
			printf("[INFO] Re-track starts. The track flag has reset.\n");
			//Pop,Unzip and Redirection
			current_node = (Node*)malloc(sizeof(Node));
			if (current_node == NULL)
			{
				printf("[ERROR] The space of the operation node failed to apply. \n");
				return NULL;
			}
			pop(current_node, top);
			if (current_node == NULL)
			{
				printf("[ERROR] Error occurs when pop fron the stack. \n");
				return NULL;
			}
			for (i = 0; i < input->clauses; i++)
			{
				for (j = 0; j < input->units; j++)
					matrix[i][j] = 0;
			}//Reset the matrix
			for (i = 0; i < current_node->unis; i++)
			{
				matrix[current_node->mairix[i][1] - 1][abs(current_node->mairix[i][2]) - 1] = current_node->mairix[i][2] / abs(current_node->mairix[i][2]);
				//Unzip the matrix
			}
			printf("[INFO] The matrix has unzipped and the current matrix has redirected.\n");
			memcpy(current_solution, current_node->solution, input->units);
			printf("[INFO] The solution space has mounted\n");
			//Operate
			current_solution[current_node->unit - 1] = -1;//Current->unit is non-0 style
			printf("[INFO] The solution has assigned\n");
			for (i = 0; i < input->units; i++)
			{
				if (matrix[i][current_node->unit - 1] == -1)
				{
					for (j = 0; j < input->units; j++)
						matrix[i][j] = 255;
				}
				else if (matrix[i][current_node->unit - 1] == 1)
				{
					matrix[i][current_node->unit - 1] = 0;
				}
			}//Operate finished
			printf("[INFO] The unit %d has operated\n", current_node->unit - 1);
			free(current_node);
		}
		//Operation function can be abandoned
		//Judgement area
	Judgement:
		endflag = scan_endflag(matrix, input->clauses, input->units);
		if (endflag == 1)
		{
			printf("[SUCCESS] The matrix has been solved!\n");
			showmartix(matrix, input->clauses, input->units);
			for (i = 0; i < input->units; i++)
			{
				if (current_solution[i] == 0)
				{
					current_solution[i] = 1;
				}
			}//Finishing Solutions
			showsolution(current_solution, input->units);

			return current_solution;
		}
		else if (endflag == 0)
		{
			printf("[INFO] Keep cycling...\n");
			continue;
		}
		else if (endflag == -1)
		{
			printf("[ERROR] It seems these Solutions can't be satisified. Retrying...\n");
			if (top == &stack[0])
			{
				printf("[ERROR] It seems the matrix can't be satisified. Please check the information of the matrix or fix the bugs.\n");
				showmartix(matrix, input->clauses, input->units);

				return NULL;
			}
			else
			{
				track_flag = 1;
				printf("[INFO] Start Retracking\n");
				continue;
			}
		}
	} while (1);
}

int scan_single(int** matrix, int Row, int Column)
{
	int i, j;//Cycle point
	int unit = 0;
	int pos_flag = 0;//If it's a positive clause
	int neg_flag = 0;//If it's a negative clause
	for (i = 0; i < Row; i++)
	{
		for (j = 0, pos_flag = 0, neg_flag = 0; j < Column; j++)
		{
			if (matrix[i][j] == 1)
			{
				pos_flag++;
				unit = j + 1;
			}
			if (matrix[i][j] == -1)
			{
				neg_flag++;
				unit = -(j + 1);
			}
		}
		if (pos_flag == 1 || neg_flag == 1)
			return unit;
		//Return unit's order (non-0 style)
	}
	return 0;//If not exist,return 0
}//Alert: Chain-stack's top is the first node, and its bottom's next is NULL.

int scan_endflag(int** matrix, int row, int column)
//To judge if any special position(all 255 or a line 0)
//If all 255, return 1
//If any 0000, return -1
//Return 0 means nothing happens
{
	int i, j;
	int trueflag = 1;
	int falseflag = 1;
	for (i = 0; i < row; falseflag = 1/*Reset flag*/, i++)
	{
		for (j = 0; j < column; j++)
		{
			if (matrix[i][j] != 255)
			{
				trueflag = 0;
			}
			else
				trueflag = 0;
			if (matrix[i][j] != 0)
				falseflag = 0;
		}
		if (falseflag == 1)
			return -1;
	}
	if (trueflag == 1)
		return 1;
	else
		return 0;
}

void operate(int flag, int unit, int parameter, int** matrix, int row, int column, int* solution)
{
	int i, j;
	if (flag == 0)//Single clause Remove
	{
		solution[abs(unit) - 1] = unit / abs(unit);//Mount solution space
		for (i = 0; i < column; i++)
		{
			matrix[parameter][i] = 255;
		}//Remove this clause(Alert:parameter can be 0 but never be Neg)
	}
	if (flag == 1)//Assign
	{
		solution[abs(unit) - 1] = unit / abs(unit);//Mount solution space
	}
	for (i = 0; i < row; i++)
	{
		if (matrix[i][unit - 1] == unit / abs(unit))//Equ unit, Remove
		{
			for (j = 0; j < column; j++)
			{
				matrix[i][j] = 255;
			}
		}
		if (matrix[i][unit - 1] == -(unit / abs(unit)))//Opp unit, Delete
		{
			matrix[i][unit - 1] = 0;
		}
	}//Clean this unit via the matrix
}//Maybe that is... But what's the meaning of the difference between two flags?
//Fatal problem occured.Stop using.

void push(Node* point, Node** top)
{
	//memcpy(*top, point, sizeof(Node));
	*top = point;//Transfer of control of the structure
	top++;
}
void pop(Node* point, Node** top)//The result is placed at the pointer *point
{
	top--;
	memcpy(point, top, sizeof(Node));//Deep copy
	free(top);
}

void showmartix(int** matrix, int row, int column)
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		printf("[TEST%d] ",i);
		for (j = 0; j < column; j++)
		{
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}
void showsolution(int* solution, int units)
{
	int i;
	printf("[TEST] ");
	for (i = 0; i < units; i++)
		printf("%d ", solution[i]);
	printf("\n");
}

//Sum up in 2/18
//It seems that it keeps single clause's operation. Certainly it needs more manufacture work to discover the order.
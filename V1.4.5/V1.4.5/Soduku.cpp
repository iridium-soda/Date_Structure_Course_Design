#include "head.h"

void Soduku()
{//Random staeagty:add payload to secure rendomly enough and cover time-seed's influence
	int i;
	cnf* sodu;
	int** finalsquare;
	system("cls");
	printf("Preparing...\n");
	printf("Generating...\n");
	double* timecost = (double*)malloc(sizeof(double));
	/*Generation*/
	int** soduku_square = (int**)malloc(sizeof(int*) * 9);

	for (i = 0; i < 9; i++)
		soduku_square[i] = (int*)calloc(9, sizeof(int));
kksk:
	sodu = sodukugenerating(soduku_square);
	if (sodu == NULL)
	{
		cleansquare(soduku_square);
		goto kksk;
	}

	system("PAUSE");
	system("cls");
	printf("[INFO] Stage V: Soduku\n");//Start sign
	//fileSimulator(sodu);

	printf("[INFO] Calculating...\n");
	int* solution = DPLL(sodu, timecost);
	if (solution == NULL)
	{
		printf("[ERROR] There is no solution to the equation or error occurred. Read log for more information.\n");
		printf("[TIME] %lf\n", *timecost);
	}
	else
	{
		printf("[SUCCESS] The equation has been solved.\n");
		//showsolution(solution, 1000);
		finalsquare = solution2square(solution);
		showsoduku(finalsquare);
	}
	//Problem occured: digit arrangement error. To prevent ,have to move the digit
	getchar();
}

cnf* sodukugenerating(int** square)//To generate soduku randomly
{
	int i, j;
	long payload = 0;
	int timemark = 0;
	cnf* quiz;

	//By layer
	for (i = 1; i < 10; i++)
	{
		timemark = 0;
		for (j = 0; j < 9; j++)
		{
			while (1)
			{
				//payload %= 1000;
				srand(time(0) + payload);
				int kksk = rand() % 9;
				//printf("[TEST] Assign[%d][%d]=%d\n", j, kksk, i);
				if (square[j][kksk] != 0)
				{
					//printf("[ERROR] 位元占用!%d\n", timemark);
					payload += 80;
					timemark++;
					if (timemark >= 400)
					{
						//printf("[ERROR] RESTART...\n");
						return NULL;
					}
					continue;
				}
				else
				{
					square[j][kksk] = i;
					if (checkcell(square, j, kksk) == 1)
					{
						//printf("[SUCCESS] 成功赋值%d\n", timemark);
						payload += 80;
						timemark++;
						if (timemark >= 400)
						{
							//printf("[ERROR] RESTART...\n");
							return NULL;
						}
						break;
					}
					else
					{
						//printf("[ERROR] 位元未占用但审查不通过%d\n", timemark);
						square[j][kksk] = 0;
						payload += 80;
						timemark++;
						if (timemark >= 400)
						{
							//printf("[ERROR] RESTART...\n");
							return NULL;
						}
						continue;//reassign
					}
				}
				payload += 80;
			}
			//showsoduku(square);
			//printf("\n");
			//if (timemark > 100)
				//getchar();
		}
	}
	printf("[INFO] Sudoku generated\n");
	showsoduku(square);
	getchar();
	digging(square);
	getchar();
	quiz = translation2cnf(square);
	return quiz;
}
int checkcell(int** square, int row, int column)//To check if the potision correct
//0-style
{
	//printf("[INFO] Checking\n");
	int i, j;
	int cell;
	for (i = 0; i < COLUMN; i++)
	{
		if (square[row][i] == square[row][column] && i != column)
			return 0;
	}//Line check
	for (j = 0; j < ROW; j++)
	{
		if (square[j][column] == square[row][column] && j != row)
			return 0;
	}//Column check
	cell = showcell(row, column);
	for (i = 1; i < 4; i++)
	{
		for (j = 1; j < 4; j++)
		{
			if (square[(cell - 1) / 3 * 3 + i - 1][(cell - 1) % 3 * 3 + j - 1] == square[row][column] && (cell - 1) / 3 * 3 + i - 1 != row && (cell - 1) % 3 * 3 + j - 1 != column)
				return 0;
		}
	}//Cell check
	return 1;
}//Correct=1,Wrong=0
void showsoduku(int** square)//show final square for test
{
	int i, j;
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COLUMN; j++)
		{
			printf("%d ", square[i][j]);
			if (j % 3 == 2)
				printf(" | ");
		}

		printf("\n");
		if (i % 3 == 2)
		{
			printf("- - - - - - - - - - - - - - \n");
		}
	}
}
int showcell(int row, int column)//To show which big cell belongs to
//0-style
{
	int across, straight;
	across = column / 3 + 1;
	straight = row / 3 + 1;
	return (straight - 1) * 3 + across;
}//1-9
void digging(int** square)
{
	printf("[INFO] Start digging\n");
	int row, column;//0-style
	int holecounter = 0;
	int payload = 0;
	int payload2 = 0;
	for (holecounter = 1; holecounter <= 40;)
	{
		payload %= 1000;
		payload2 %= 1285;
		srand(time(0) + payload);
		row = rand() % 9;
		srand(time(0) + payload + payload2 + 77);
		column = rand() % 9;
		if (square[row][column] == 0)
		{
			//printf("[ERROR] DIGGED![%d][%d]\n", row, column);
			payload += 80;
			payload2 += 120;
			continue;
		}
		else
		{
			//printf("[SUCCESS] DIGGED![%d][%d]:%d\n", row, column, holecounter);
			square[row][column] = 0;
			payload += 90;
			payload2 += 131;
			holecounter++;
		}
	}
	printf("[INFO] Digging complete\n");
	showsoduku(square);
}
void cleansquare(int** square)
{
	int i, j;
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COLUMN; j++)
			square[i][j] = 0;
	}
}
cnf* translation2cnf(int** square)
{
	int i, j, k, l;
	int j1, k1;
	int overallorder = 0;//to save current potision
	/*translation stage*/
	/*40hole,41known*/
	/*7677 clauses*/
	/*known-single=41,unknown,each cell has=40*/
	/*each unknown cell only:36*40*/
	/*line unique: 9*36*9*/
	/*column unique:9*36*9*/
	/*cell unique:only check diffierent row and column cells*4:4*9*9*/
	cnf* sudoinfo = (cnf*)malloc(sizeof(cnf));
	sudoinfo->clauses = 10269;//Don't skip assigned unit to avoid randon bugs
	sudoinfo->focus_unit = 0;
	sudoinfo->units = 1000;//1->999,use 111-999only,and xx0 is not used
	sudoinfo->solutions = (int*)calloc(1000, sizeof(int));
	sudoinfo->matrix = (int**)malloc(sizeof(int*)*sudoinfo->clauses);
	for (i = 0; i < sudoinfo->clauses; i++)
	{
		sudoinfo->matrix[i] = (int*)calloc(sudoinfo->units + 1, sizeof(int));//one more is the flag
	}
	//SCANNING known single HAVE&ONLY
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COLUMN; j++)
		{
			if (square[i][j] != 0)
			{
				sudoinfo->matrix[overallorder][(i + 1) * 100 + (j + 1) * 10 + square[i][j]] = 1;//Calculate its offset and push
				overallorder++;
			}
		}
	}
	printf("[INFO] Known unit's single complete:%d\n", overallorder);
	//Assumed value:42
	getchar();
	//SCANNING unknown cell HAVE
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COLUMN; j++)
		{
			if (square[i][j] == 0)
			{
				for (k = 1; k <= 9; k++)//Units
				{
					sudoinfo->matrix[overallorder][(i + 1) * 100 + (j + 1) * 10 + k] = 1;//Calculate its offset and push
				}
				overallorder++;
			}
		}
	}
	printf("[INFO] UNKnown unit's single complete:%d\n", overallorder);
	getchar();
	//Assumed value:82
	//SCANNING unknown ONLY
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COLUMN; j++)
		{
			for (k = 1; k <= 9; k++)//unit1
			{
				for (l = k + 1; l <= 9; l++)//Fixed: Logic disorder
				{
					sudoinfo->matrix[overallorder][(i + 1) * 100 + (j + 1) * 10 + k] = -1;//Calculate its offset and push
					sudoinfo->matrix[overallorder][(i + 1) * 100 + (j + 1) * 10 + l] = -1;//Calculate its offset and push
					overallorder++;
				}
			}
		}
	}
	printf("[INFO] UNKnown unit's ONLY complete:%d\n", overallorder);
	//Assumed value:1522
	getchar();
	//SCANNING line meets
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COLUMN; j++)
		{
			for (k = j + 1; k < 9; k++)
			{
				for (l = 1; l <= 9; l++)
				{
					sudoinfo->matrix[overallorder][(i + 1) * 100 + (j + 1) * 10 + l] = -1;//Calculate its offset and push
					sudoinfo->matrix[overallorder][(i + 1) * 100 + (k + 1) * 10 + l] = -1;//Calculate its offset and push
					//printf("[TEST] %d %d<->%d %d\n\n", overallorder, (i + 1) * 100 + (j + 1) * 10 + l, overallorder, (i + 1) * 100 + (k + 1) * 10 + l);
					overallorder++;
				}
			}
		}
	}
	printf("[INFO] LINE scanning complete:%d\n", overallorder);
	//Assumed value:3255
	getchar();
	//SCANNING column meets
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COLUMN; j++)
		{
			for (k = j + 1; k < 9; k++)
			{
				for (l = 1; l <= 9; l++)
				{
					sudoinfo->matrix[overallorder][(j + 1) * 100 + (i + 1) * 10 + l] = -1;//Calculate its offset and push
					sudoinfo->matrix[overallorder][(k + 1) * 100 + (i + 1) * 10 + l] = -1;//Calculate its offset and push
					overallorder++;
				}
			}
		}
	}
	printf("[INFO] Column's scanning complete:%d\n", overallorder);
	//Assumed value:5446
	getchar();
	//SCANNING cell meets
	for (i = 1; i <= 9; i++)//cell order
	{
		for (j = ((i - 1) / 3) * 3; j < ((i - 1) / 3) * 3 + 3; j++)
		{
			for (k = (i % 3) * 3; k < (i % 3) * 3 + 3; k++)//first unit
			{
				for (j1 = ((i - 1) / 3) * 3; j1 < ((i - 1) / 3) * 3 + 3; j1++)
				{
					if (j1 == j)
						continue;
					for (k1 = (i % 3) * 3; k1 < (i % 3) * 3 + 3; k1++)//second unit
					{
						if (k1 == k)
							continue;
						if (square[j1][k1] != 0)
							continue;
						else
						{
							for (l = 1; l <= 9; l++)
							{
								sudoinfo->matrix[overallorder][(j + 1) * 100 + (k + 1) * 10 + l] = -1;//Calculate its offset and push
								sudoinfo->matrix[overallorder][(j1 + 1) * 100 + (k1 + 1) * 10 + l] = -1;//Calculate its offset and push
								overallorder++;
							}
						}
					}
				}
			}
		}
	}
	printf("[INFO] Cell's scanning complete:%d\n", overallorder);
	getchar();
	printf("[INFO] CNF generate succeed\n");
	return sudoinfo;
}
void fileSimulator(cnf* input)
{
	int i, j;
	for (i = 0; i < input->clauses; i++)
	{
		printf("[TEST%d] ", i);
		for (j = 1; j < input->units + 1; j++)
		{
			if (input->matrix[i][j] != 0)
			{
				printf("%d ", j*input->matrix[i][j]);
			}
		}
		printf("\n");
	}
}
int** solution2square(int*solution)
{
	int i, j, l;
	int** square = (int**)malloc(ROW * sizeof(int*));
	for (i = 0; i < ROW; i++)
	{
		square[i] = (int*)calloc(COLUMN, sizeof(int));
	}//calloc square
	for (j = 0; j < COLUMN; j++)
	{
		for (i = 0; i < ROW; i++)
		{
			for (l = 1; l <= 9; l++)
			{
				if (solution[(i + 1) * 100 + (j + 1) * 10 + l - 1] == 1)
					square[i][j] = l;
			}
		}
	}
	return square;
}
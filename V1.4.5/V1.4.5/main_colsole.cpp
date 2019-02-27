#include "head.h"

int main()
{
	//Demostration Note: please run "s-8-50","s-6-50","s-2-50","s-11-100"and"s-7-20-90000" to show the best result
	int i, j;//Cycle units,intitalize before using
	double* timecost = (double*)malloc(sizeof(double));//A pointer to pass timecost when dpll
	double* timecost2 = (double*)malloc(sizeof(double));
	int units, units2;//To backup units
	int flag;//Assign the condition and status
	int status;
	Lisence();//Lisence info
	/*=========================================================*/
	printf("[INFO] STAGE I:read file and Analysis\n");
	printf("[INFO] Folder is limited to ../../data/data/data/basic/function,\nthink carefully before moving the position because may cause Dependence disorder\n");

	char* Filename;
	Filename = Folderanlysis();//filename is the full path
	if (!Filename)
	{
		printf("[ERROR] No cnf file detected! Error occured! The program will exit!\n");
		system("PAUSE");
		return 0;
	}
	printf("[SUCCESS] The function has exited successfully\n[INFO] Goal Path:%s\n", Filename);
	system("PAUSE");
	system("cls");//Bugs inside have clear
	/*=================================================*/
	printf("[INFO] STAGE II:Analysis file and save in data struture\n");
	cnf* mainstorge = Fileread(Filename);
	if (mainstorge == NULL)
	{
		perror("[ERROR] Something wrong happened. The program will exit. For more information, please refer wrong massage.");
		system("PAUSE");
		return 0;
	}
	printf("[SUCCESS] The file has been read successfully\n");
	i = 0; j = 0;
	/*for (i = 0; i < mainstorge->clauses; i++)
	{
		printf("[INFO%d] ", i);
		for (j = 0; j < mainstorge->units+1; j++)
		{
			printf("%d ", mainstorge->matrix[i][j]);
		}

		printf("\n");
	}*///Test part//May visiable when demonstrate
	cnf* backup = (cnf*)malloc(sizeof(cnf));
	backup->clauses = mainstorge->clauses;
	backup->focus_unit = mainstorge->focus_unit;
	backup->units = mainstorge->units;
	backup->matrix = (int**)malloc(sizeof(int*)*backup->clauses);
	backup->solutions = (int*)calloc(backup->units, sizeof(int));
	for (i = 0; i < backup->clauses; i++)
	{
		backup->matrix[i] = (int*)malloc(sizeof(int)*(backup->units + 1));
	}
	for (i = 0; i < backup->clauses; i++)
	{
		for (j = 0; j < backup->units + 1; j++)
			backup->matrix[i][j] = mainstorge->matrix[i][j];
	}//Copy struct

	system("PAUSE");
	/*=================================================*/
	printf("[INFO] Stage III: Solve the matrix\n");
	units = mainstorge->units;
	units2 = mainstorge->units;
	int* solutions = DPLL(mainstorge, timecost);//Warning: mainstorge here has freed!
	/*free(mainstorge);
	mainstorge = NULL;*///Destory mainstorge
	//Can't release because of unknown reason. But don't use it again!
	if (solutions == NULL)
	{
		printf("[ERROR] There is no solution to the equation or error occurred. Read log for more information.\n");
		printf("[TIME] %lf\n", *timecost);
		flag = -1;
	}
	else
	{
		printf("[SUCCESS] The equation has been solved.\n");
		printf("[RESULT] ");
		for (i = 0; i < units; i++)
			printf("%d ", solutions[i]);
		printf("\n");
		printf("[TIME] %lf\n", *timecost);
		flag = 1;
	}
	status = filewirite(Filename, solutions, units, *timecost, flag);
	if (status == 1)
	{
		printf("[INFO] File written successfully\n");
	}
	if (status == -1)
	{
		printf("[ERROR] File unable to write, check the program\n");
	}
	system("PAUSE");
	/*==========================================*/
	printf("[INFO] Stage IV: Solve the matrix with revise\n");

	units = mainstorge->units;
	int* solutions2 = DPLL_revise(backup, timecost2);//Warning: mainstorge here has freed!
	/*free(mainstorge);
	mainstorge = NULL;*///Destory mainstorge
	//Can't release because of unknown reason. But don't use it again!
	if (solutions2 == NULL)
	{
		printf("[ERROR] There is no solution to the equation or error occurred. Read log for more information.\n");
		printf("[TIME] %lf\n", *timecost2);
		flag = -1;
	}
	else
	{
		printf("[SUCCESS] The equation has been solved.\n");
		printf("[RESULT] ");
		for (i = 0; i < units2; i++)
			printf("%d ", solutions2[i]);
		printf("\n");
		printf("[TIME] %lf\n", *timecost2);
		flag = 1;
	}
	printf("[INFO] Time saved %f\%100\n", (*timecost - *timecost2) / (*timecost) * 100);
	getchar();
	Soduku();
	system("PAUSE");
	system("cls");
	Lisence(); return 0;
}
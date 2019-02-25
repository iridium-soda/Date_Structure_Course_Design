#include "head.h"

int main()
{
	int i, j, k;//Cycle units,intitalize before using
	double* timecost=(double*)malloc(sizeof(double));//A pointer to pass timecost when dpll
	int units;//To backup units 
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
	system("PAUSE");
	/*=================================================*/
	printf("[INFO] Stage III: Solve the matrix\n");
	units=mainstorge->units;
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
	status=filewirite(Filename, solutions, units,*timecost, flag);
	if (status == 1)
	{
		printf("[INFO] File written successfully\n");
	}
	if (status == -1)
	{
		printf("[ERROR] File unable to write, check the program\n");
	}
	getchar();

	return 0;
}
#include "head.h"

int main()
{
	int i, j, k;//Cycle units,intitalize before using
	Lisence();//Lisence info
	/*=========================================================*/
	printf("[INFO] STAGE I:read file and Analysis\n");
	printf("[INFO] Folder is limited to ../../../data/data/data/basic/function,\nthink carefully before moving the position because may cause Dependence disorder\n");

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
	for (i = 0; i < mainstorge->clauses; i++)
	{
		printf("[INFO%d] ",i);
		for (j = 0; j < mainstorge->units; j++)
		{
			printf("%d ", mainstorge->matrix[i][j]);
		}

		printf("\n");
	}//Test part//May visiable when demonstrate
	system("PAUSE");
	/*=================================================*/
	printf("[INFO] Stage III: Solve the matrix\n");
	int* solution = DPLL(mainstorge);
	if (solution == NULL)
	{
		printf("[ERROR] There is no solution to the equation or error occurred. Read log for more information.\n");
	}
	else
	{
		printf("[SUCCESS] The equation has been solved.\n");
		printf("[INFO] ");
		for (i = 0; i < mainstorge->units; i++)
			printf("%d ", solution[i]);
		printf("\n");
	}
	getchar();
	getchar();
	getchar();
	return 0;
}
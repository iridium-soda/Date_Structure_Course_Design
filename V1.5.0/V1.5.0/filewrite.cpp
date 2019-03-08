# include "head.h"
int filewirite(char* filename, int* solution, int units, double time, int flag)//To write files in file,Return status
{
	int i, j;
	printf("[INFO] Strat write file\n");
	printf("%s\n", filename);
	char* fullpath = (char*)malloc(sizeof(char) * 512);
	strncpy_s(fullpath, 512, filename, 21);
	strcat_s(fullpath, 512, "Log/");
	strcat_s(fullpath, 512, &filename[36]);
	fullpath[strlen(fullpath) - 1] = 'g';
	fullpath[strlen(fullpath) - 2] = 'o';
	fullpath[strlen(fullpath) - 3] = 'l';
	printf("[INFO] File's full path is %s\n", fullpath);
	FILE* filep = NULL;
	fopen_s(&filep, fullpath, "w+");
	if (filep == NULL)
	{
		printf("[ERROR] The file open error\n");
		return -1;
	}
	if (flag == 1)
	{
		fprintf_s(filep, "s 1\n");
	}
	else if (flag == -1)
	{
		fprintf_s(filep, "s 0\n");
	}//Flag write

	if (solution == NULL)
	{
		fprintf_s(filep, "v NULL\n");
	}
	else
	{
		fprintf_s(filep, "v ");
		for (i = 0; i < units; i++)
		{
			fprintf_s(filep, "%d ", solution[i]);
		}
		fprintf_s(filep, "%d units\n", units);
	}//Solution write
	fprintf_s(filep, "t %lf\n", time);
	fclose(filep);
	printf("[SUCCESS] File write success\n");
	return 1;
}
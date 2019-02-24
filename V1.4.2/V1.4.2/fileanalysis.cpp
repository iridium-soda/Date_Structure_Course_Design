#include "head.h"

char* Folderanlysis()
{
	/* file read and analysis*/
	/* The code below is copied from https://blog.csdn.net/baidu_30000217/article/details/53098788 ,with some modification. How does it work? I don't know.*/

	char* filename;
	struct _finddata_t fileinfo;//A struct to store file info
	//int status;//To detect status of the handle, and has been abandoned
	intptr_t fHandle;//file handle
	//When use long type  to declare the variable, some information may lose when use _findnext function

	int i = 0;//recycle variable. Remember initalizing before using
	int filenumber = 0;//counter of number of file
	int fileorder = 0;//To select file
	if ((fHandle = _findfirst("../../data/data/data/basic/function/*.cnf", &fileinfo)) == -1L)
	{
		system("PAUSE");
		return NULL;//fail to find file
	}
	else
	{
	fileshow:
		filenumber = 0;
		fHandle = _findfirst("../../data/data/data/basic/function/*.cnf", &fileinfo);
		printf("------------------------------------\n");
		printf("NO.\tFilename\tSize\n");
		printf("------------------------------------\n");
		do {
			filenumber++;
			printf("%d\t%s\t%d Bytes\n", filenumber, fileinfo.name, fileinfo.size);
		} while (_findnext(fHandle, &fileinfo) == 0);
	}
	printf("------------------------------------\n");
	printf("Put in the order to open\n");
	scanf_s("%d", &fileorder);
	if (fileorder <= 0 || fileorder > filenumber)
	{
		printf("Invalid input!\n");
		system("PAUSE");
		system("cls");
		goto fileshow;
	}
	else
	{
		FILE* file = NULL;

		fHandle = _findfirst("../../data/data/data/basic/function/*.cnf", &fileinfo);
		/*do
		{
			i++;
			printf("Test message:%s", fileinfo.name);
			_findnext(fHandle, &fileinfo);
		} while (i < fileorder);*/
		for (i = 1; i < fileorder; i++, _findnext(fHandle, &fileinfo))
		{
			//printf("Test message:%s", fileinfo.name);
		}//Info: change some logic to solve a problem about the first file is skipped and jump to the second one directly
		filename = (char*)malloc(255 * sizeof(char));
		strcpy_s(filename, strlen(fileinfo.name) + 1, fileinfo.name);
		//		printf("The file name is %s\n", filename);->The test message
		//		system("PAUSE");
	}
	char* fullpath = (char*)malloc(sizeof(char) * 512);
	strcpy_s(fullpath, 512, "../../data/data/data/basic/function/");

	_findclose(fHandle);//Close file detect handle
	strcat_s(fullpath, 512, filename);
	return fullpath;
	/*File load and choose stage ends. Maybe... ithis part can be a function placed in another .cpp file?*/
}
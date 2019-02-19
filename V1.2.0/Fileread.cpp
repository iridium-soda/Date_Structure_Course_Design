#include "head.h"

cnf* Fileread(char* filename)
{
	char content[255];//eachline reader
	FILE* file = NULL;
	cnf* output;
	int datapan;//Tempory save data
	int units;//Temporary storage unit number(Matrix's column)
	int lines;////Temporary storage clause number(Matrix's line)
	int i;//Cycle unit
	int j;//Cycle unit
	int offset;//data's offset in a line
	int digits;//To store each data's Number of digits, and decide offset's add in each operation
	int flag;//To storge the sign.1=pos.-1=neg.
	int cls = 0;//To point out the order of cluses
	int data;
	output = (cnf*)malloc(sizeof(struct cnfdata));//alloc Main control struct
	fopen_s(&file, filename, "r");
	if (!file)
	{
		perror("[ERROR] file open failed\n");
		return NULL;
	}
	while (feof(file) == 0)//read by each line
	{
		memset(content, 0, sizeof(content));
		fgets(content, sizeof(content) - 1, file);
		if (*content == 'c')
			continue;
		if (*content == 'p')
		{
			if (output == NULL)
			{
				perror("[ERROR] malloc failed!");
				fclose(file);
				return NULL;
			}

			printf("[INFO] Standard string has been intercepted:\n[INFO] %s", content);

			//content += 6;//Move pointer to number's head
			units = atoi(&content[6]);//switch string into number
			//content += 3;
			lines = atoi(&content[9]);
			printf("[INFO] Matrix Data Intercepted:Lines:%d\tColumns:%d\n", lines, units);
			output->clauses = lines;
			output->units = units;//Save Row and Column data

			output->matrix = (int**)malloc(sizeof(int*)*lines);
			if (output->matrix == NULL)
			{
				perror("[ERROR] malloc failed!");
				system("PAUSE");
				fclose(file);
				return NULL;
			}
			//printf("log info: \noutput->matrix:\naddress:%x\nvalue:%d\n------", &(output->matrix), output->matrix);
			for (i = 0; i < lines; i++)
			{
				*(output->matrix + i) = (int*)malloc(sizeof(int)*units);
				if (*(output->matrix + i) == NULL)
				{
					perror("[ERROR] Malloc Failed!\n");
					system("PAUSE");
					fclose(file);
					return NULL;
				}
				//A HUGE PROBLEM !!! NEED TO FIX AT ONCE!!!!!!//FIXED.
				for (j = 0; j < output->units; j++)
					output->matrix[i][j] = 0;//Instability due to the use of the memset function, initialize the matrix manually
				//memset(*(output->matrix + i), 0, units);//Initialize the Matrix by row(An unstdable way)
			}//alloc by lines and columns
			printf("[SUCCESS] Malloc Finished\n[INFO] %dLines*%dColumns\n", output->clauses, output->units);

			continue;
		}//Info string interrupt and space malloc
		offset = 0;
		while (datapan = atoi(&content[offset]), datapan != 0)//In each Line,for each number
		{
			if (datapan > 0)
				flag = 1;
			else
				flag = -1;
			//save sign
			datapan = abs(datapan);
			data = datapan; //A tempory copy
			digits = 0;
			while (datapan != 0)//To calculate digit
			{
				datapan /= 10;
				digits++;
			}
			offset += digits;
			offset++;//space offset
			if (flag == -1)
				offset++;//sign offset
			output->matrix[cls][data - 1] = flag;//Save sign in correct place
			//I used the pointer to save data but interruption always occurred. Then by testing, I used number directly and it worked. It's a hard job.
		}//Each Line
		cls++;
	}
	//Problem occured:The malloc Module is processing while reading 'p' lines//solved

	fclose(file);
	printf("[SUCCESS] All the information in file have been mounted\n");
	system("PAUSE");
	return output;
}
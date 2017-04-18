// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAXRECORDNO  100

struct dataBase
{
	int id_number;
	char* name;
	int score_number;
};

int main()
{
	/*Define variables*/
	char *tokChar;
	FILE *ptr_file;
	char fileStr[999];

	int tokCounter = 0;
	int keywordNo = 0;
	int loopCounter = 0;
	int itemNo = 0;
	bool keywordExistanceResult = false;
	char keyWords[100][10];
	dataBase emploee[MAXRECORDNO];

	/*Open keywords file and extract keywords*/
	memset(&fileStr[0], 0, sizeof(fileStr));
	ptr_file = fopen("D:\\Keywords.txt", "r");
	if (ptr_file) 
	{
		while (fscanf(ptr_file, "%s", fileStr) != EOF);
		fclose(ptr_file);
	}

	tokChar = strtok(fileStr, ";");
	while (tokChar != NULL)
	{
		/*Insert keywords in an array*/
		strcpy(keyWords[tokCounter], tokChar);

		tokCounter++;
		tokChar = strtok(NULL, ";");

		/*Check Maximum keywords validity*/
		if (tokCounter >= 99)
		{
			/*Report too many keywords Error and terminate the app*/
			printf("Too many keywords Error");
			return 0;
		}
	}

	/*Find keywords number*/
	keywordNo = tokCounter;

	/*Open data file and extract data items*/
	memset(&fileStr[0], 0, sizeof(fileStr));
	ptr_file = fopen("D:\\Data.txt", "r");
	if (ptr_file)
	{
		while (fscanf(ptr_file, "%s", fileStr) != EOF);
		fclose(ptr_file);
	}

	/*Find Item before ';'*/
	tokChar = strtok(fileStr, ";");
	while (tokChar != NULL)
	{
		/*Chek if token item include keywords*/
		char *substring = strstr(tokChar, "=");
		if (substring)
		{
			size_t len = substring - tokChar;
			char *prefixString = (char*)malloc(len + 1);
			char *suffixString = substring + 1;

			if (prefixString)
			{
				memcpy(prefixString, tokChar, len);
				prefixString[len] = 0;

				/*Compare readed keyword from data file with reference keywords in keywordFile*/
				for (loopCounter = 0; loopCounter < keywordNo; loopCounter++)
				{
					if (!strcmp(prefixString, keyWords[loopCounter]))
					{
						keywordExistanceResult = true;
						break;
					}
					else
					{
						keywordExistanceResult = false;
					}
				}

				/*report any issue in keywords finding*/
				if (keywordExistanceResult == false)
				{
					/*Report finding issue with key word in data file*/
					printf("Error:Issue with key word in data file");
					return 0;
				}
				else
				{
					/*Store item in struct*/
					if (!strcmp(prefixString, "ID"))
						emploee[itemNo /keywordNo].id_number = atoi(suffixString);
					else if (!strcmp(prefixString, "Name"))
						emploee[itemNo / keywordNo].name = suffixString;
					else if (!strcmp(prefixString, "Score"))
						emploee[itemNo / keywordNo].score_number = atoi(suffixString);
					itemNo++;
				}
				

			}
		}
		else
		{
			/*Report data file include invalid format item*/
			printf("Error:Data file include invalid format");
			return 0;
		}


		tokChar = strtok(NULL, ";");
	}

	/*Show result in console*/
	printf("Total number of keywords: %d\nTotal number of record: %d\n", keywordNo, (itemNo / keywordNo));
	for (loopCounter = 0; loopCounter < (itemNo / keywordNo); loopCounter++)
	{
		printf("%d-%03d\t%s\t%d\n", loopCounter + 1, emploee[loopCounter].id_number, emploee[loopCounter].name, emploee[loopCounter].score_number);
	}
	getchar();
}




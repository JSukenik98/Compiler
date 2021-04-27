#include "IOMngr.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>


FILE* in = NULL;
FILE* out = NULL;
int lineNum = 0;
int columnNum = 0;
int lineRead = 0;
int linePrint = 0;
char* line = NULL;
size_t len = 0;
int read = 0;

int openFiles(char* sourceName, char* listingName)
{
	in = fopen(sourceName, "r");
	if (in == NULL)
	{
		fprintf(stderr, "ERROR: Source file does not exist or there was an issue opening!");
		return 0;
	}
	if (listingName != NULL)
	{
		out = fopen(listingName, "w");
		if (out == NULL)
		{
			fprintf(stderr, "ERROR: Listing file does not exist or there was an issue opening!");
			if (in != NULL)
			{
				fclose(in);
			}
			return 0;
		}
		return 1;
	}
	else
	{
		out = stdout;
		return 1;
	}
}


void closeFiles()
{
	if (in != NULL)
	{
		fclose(in);
	}
	if (out != stdout && out != NULL)
	{
		fclose(out);
	}
}


char getNextSourceChar()
{
	
	if (line == NULL)
	{
		line = malloc(sizeof(char) * MAXLINE);
	}
	if (lineRead == 0)
	{
		if (read = getline(&line, &len, in) != -1)
		{
			lineRead = 1;
			lineNum = lineNum + 1;
			linePrint = 1;
			if (out != stdout)
			{
				fprintf(out, "%d. %s", lineNum, line);
			}
			char c = line[columnNum];
			columnNum = columnNum + 1;
			return c;
		}
		else
		{
			return EOF;
		}
	}
	else
	{
		char c = line[columnNum];
		if (c == '\n')
		{
			if (read = getline(&line, &len, in) != -1)
			{
				lineRead = 1;
				lineNum = lineNum + 1;
				linePrint = 1;
				if (out != stdout)
				{
					fprintf(out, "%d. %s", lineNum, line);
				}
				char c = line[columnNum];
				columnNum = columnNum + 1;
				return c;
			}
			else
			{
				return EOF;
			}
		}
		else
		{
			columnNum = columnNum + 1;
			return c;
		}
	}
}


void writeIndicator(int column)
{
	if (linePrint == 0)
	{
		fprintf(out, "%s", line);
		linePrint == 1;
	}
	fprintf(out, "%*c^\n", column+2,' ');
}


void writeMessage(char* message)
{
	fprintf(out, "%s\n", message);
}


int getCurrentLineNum()
{
	return lineNum;
}


int getCurrentColumnNum()
{
	return columnNum;
}
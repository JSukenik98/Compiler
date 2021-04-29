#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantics.h"

extern struct SymTab* table;

void printSymTab()
{
	fprintf(stderr, "In Print SymTab\n");
	if (0 != startIterator(table))
	{
		do
		{
			printf(getCurrentName(table));
			printf(": {");
			if (getCurrentAttr(table) == NULL)
			{
				printf("}\n");
			}
			else
			{
				SymTab* current = (SymTab*) getCurrentAttr(table);
				if (0 != startIterator(current))
				{
					printf(getCurrentName(current));
					
					while (nextEntry(current))
					{
						printf(",");
						printf(getCurrentName(current));
					}
					printf("}\n");
				}
				else
				{
					printf("}\n");
				}
			}
		} while (nextEntry(table));
		//printf("\n");
	}
	else
	{
		printf("SymTab is empty!\n");
	}
}

void storeVar(char* name, SymTab* storeTable)
{
	fprintf(stderr, "In StoreVar\n");
	enterName(table, name);

	/*if (startIterator(storeTable))
	{
		fprintf(stderr, "%s\n", getCurrentName(storeTable));
		while (nextEntry(storeTable))
		{
			fprintf(stderr, "%s\n", getCurrentName(storeTable));
		}
	}*/

	setCurrentAttr(table, (void*) storeTable);
	//printSymTab(table);
}

SymTab* doUnion(SymTab* table1, SymTab* table2)
{
	fprintf(stderr, "In DoUnion\n");
	SymTab* unionTable = createSymTab(20);
	//fprintf(stderr, "Union Table Created\n");
	if (0 != startIterator(table1))
	{
		//fprintf(stderr, "Iterator worked table1\n");
		enterName(unionTable, getCurrentName(table1));
		while (nextEntry(table1))
		{
			//fprintf(stderr, "In while table1\n");
			enterName(unionTable, getCurrentName(table1));
		}
	}
	if (0 != startIterator(table2))
	{
		//fprintf(stderr, "Iterator worked table2\n");
		enterName(unionTable, getCurrentName(table2));
		while (nextEntry(table2))
		{
			//fprintf(stderr, "In while table2\n");
			enterName(unionTable, getCurrentName(table2));
		}
	}

	/*if (startIterator(unionTable))
	{
		fprintf(stderr, "%s\n", getCurrentName(unionTable));
		while (nextEntry(unionTable))
		{
			fprintf(stderr, "%s\n", getCurrentName(unionTable));
		}
	}*/

	//fprintf(stderr, "Leaving DoUnion\n");
	//destroySymTab(table1);
	//destroySymTab(table2);
	return unionTable;
}

SymTab* doIntersect(SymTab* table1, SymTab* table2)
{
	fprintf(stderr, "In DoIntersect\n");

	SymTab* intersectTable = createSymTab(20);
	if (0 != startIterator(table1))
	{
		if (0 != startIterator(table2))
		{
			if (findName(table2, getCurrentName(table1)))
			{
				enterName(intersectTable, getCurrentName(table1));
			}
			while (nextEntry(table1))
			{
				if (findName(table2, getCurrentName(table1)))
				{
					enterName(intersectTable, getCurrentName(table1));
				}
			}
		}
		else
		{
			destroySymTab(table1);
			destroySymTab(table2);
			return intersectTable;
		}
	}
	else
	{
		destroySymTab(table1);
		destroySymTab(table2);
		return intersectTable;
	}
	destroySymTab(table1);
	destroySymTab(table2);
	return intersectTable;
}

SymTab* getVal(char* name)
{
	fprintf(stderr, "In getVal\n");

	if (enterName(table, name))
	{
		writeIndicator(getCurrentColumnNum());
		writeMessage("Initialize variable to empty set");
		setCurrentAttr(table, (void*) createSymTab(20));
	}
	SymTab* current = (SymTab*) getCurrentAttr(table);
	SymTab* valTable = createSymTab(20);

	if (startIterator(current))
	{
		enterName(valTable, getCurrentName(current));
		while (nextEntry(current))
		{
			enterName(valTable, getCurrentName(current));
		}
		return valTable;
	}
	else
	{
		return valTable;
	}

	/*if (startIterator(valTable))
	{
		fprintf(stderr, "%s\n", getCurrentName(valTable));
		while (nextEntry(valTable))
		{
			fprintf(stderr, "%s\n", getCurrentName(valTable));
		}
	}*/
}

SymTab* newSet(char* set)
{
	fprintf(stderr, "In newSet: %s\n", set);

	SymTab* newTable = createSymTab(20);
	if (strcmp(set, "{}") == 0)
	{
		return newTable;
	}
	else
	{
		char* step1 = malloc(sizeof(char) * (strlen(set) - 1));
		strcpy(step1, &set[1]);
		char* step2 = malloc(sizeof(char) * (strlen(step1) - 1));
		strncpy(step2, step1, strlen(step1) - 1);


		char* token = strtok(step2, ",");
		while (token != NULL)
		{
			enterName(newTable, token);
			token = strtok(NULL, ",");
		}

		/*if (startIterator(newTable))
		{
			fprintf(stderr, "%s\n", getCurrentName(newTable));
			while (nextEntry(newTable))
			{
				fprintf(stderr, "%s\n", getCurrentName(newTable));
			}
		}*/

		return newTable;
	}
}
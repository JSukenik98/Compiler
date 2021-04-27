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
				SymTab* current = (SymTab*)getCurrentAttr(table);
				if (0 != startIterator(current))
				{
					printf(getCurrentName(current));
					printf(",");
					while (nextEntry(current))
					{
						printf(getCurrentName(current));
						printf(",");
					}
					printf("}\n");
				}
				else
				{
					printf("}\n");
				}
			}
		} while (nextEntry(table));
	}
	else
	{
		printf("SymTab is empty!\n");
	}
}

void storeVar(char* name, SymTab* store_table)
{
	fprintf(stderr, "In StoreVar\n");
	enterName(table, name);
	setCurrentAttr(table, (void*)store_table);
}

SymTab* doUnion(SymTab* table1, SymTab* table2)
{
	fprintf(stderr, "In DoUnion\n");
	SymTab* unionTable = createSymTab(40);
	if (0 != startIterator(table1))
	{
		enterName(unionTable, getCurrentName(table1));
		while (nextEntry(table1))
		{
			enterName(unionTable, getCurrentName(table1));
		}
	}
	if (0 != startIterator(table2))
	{
		enterName(unionTable, getCurrentName(table2));
		while (nextEntry(table2))
		{
			enterName(unionTable, getCurrentName(table2));
		}
	}
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
			return intersectTable;
		}
	}
	else
	{
		return intersectTable;
	}
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
	return (SymTab*) getCurrentAttr(table);
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
		return newTable;
	}
}
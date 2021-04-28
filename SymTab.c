#include "SymTab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pos = 0;

SymTab * createSymTab(int size)
{
	if (size >= 0)
	{
		SymTab* table = malloc(sizeof(SymTab));
		table->contents = malloc(size * sizeof(SymEntry));
		table->current = malloc(sizeof(SymEntry));
		table->size = size;
		return table;
	}
	else
	{
		return NULL;
	}
}

void destroySymTab(SymTab *table)
{
	if (startIterator(table))
	{
		SymEntry* current = NULL;
		while (hasCurrent(table))
		{
			current = table->current;
			if (nextEntry(table))
			{
				free(current->attribute);
				free(current->name);
				free(current->next);
			}
			else
			{
				free(current->attribute);
				free(current->name);
				free(current);
				free(table->contents);
				free(table);
				return;
			}
		}
	}
}

int hash(char* key, int tableSize)
{
	int hashVal = 0;
	int i = 0;
	for (i = 0; i < strlen(key); i++)
	{
		hashVal = 37 * hashVal + key[i];
	}

	hashVal = hashVal % tableSize;
	if (hashVal < 0)
	{
		hashVal = hashVal + tableSize;
	}

	return hashVal;
}

int enterName(SymTab* table, char* name)
{
	fprintf(stderr, "%s\n", name);
	if (findName(table, name))
	{
		fprintf(stderr, "Already In\n");
		return 0;
	}
	else
	{
		pos = hash(name, table->size);
		table->current = table->contents[pos];
		while (hasCurrent(table))
		{
			if (table->current->next == NULL)
			{
				SymEntry* enter = malloc(sizeof(SymEntry));
				enter->attribute = NULL;
				enter->name = malloc(sizeof(char) * strlen(name));
				enter->name = strdup(name);
				enter->next = NULL;
				table->current->next = enter;
				table->current = table->current->next;
				return 1;
			}
			else
			{
				table->current = table->current->next;
			}
		}
		SymEntry* enter = malloc(sizeof(SymEntry));
		enter->attribute = NULL;
		enter->name = malloc(sizeof(char) * strlen(name));
		enter->name = strdup(name);
		enter->next = NULL;
		table->current = enter;
		if (table->contents[pos] == NULL)
		{
			table->contents[pos] = enter;
		}
		return 1;
	}
}

int findName(SymTab* table, char* name)
{
	SymEntry* current = table->current;
	if (startIterator(table))
	{
		if (strcmp(table->current->name, name) == 0)
		{
			return 1;
		}
		while (nextEntry(table) != 0)
		{
			if (strcmp(table->current->name, name) == 0)
			{
				return 1;
			}
		}
		table->current = current;
		return 0;
	}
	else
	{
		return 0;
	}
}

int hasCurrent(SymTab* table)
{
	if (table->current != NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void setCurrentAttr(SymTab* table, void* attr)
{
	if (hasCurrent(table) == 1)
	{
		table->current = attr;
	}
}

void* getCurrentAttr(SymTab* table)
{
	if (hasCurrent(table) == 1)
	{
		return table->current->attribute;
	}
	else
	{
		return NULL;
	}
}

char* getCurrentName(SymTab* table)
{
	if (hasCurrent(table) == 1)
	{
		return table->current->name;
	}
	else
	{
		return NULL;
	}
}

int startIterator(SymTab* table)
{
	fprintf(stderr, "In Start Iterator!\n");
	int found = 0;
	for (pos = 0; pos < table->size; pos++)
	{
		//fprintf(stderr, "Attempting setting current!\n");
		table->current = table->contents[pos];
		//fprintf(stderr, "Current Set!\n");
		if (hasCurrent(table))
		{
			found = 1;
			break;
		}
	}
	if (found == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int nextEntry(SymTab* table)
{
	if (hasCurrent(table))
	{
		while (pos < table->size)
		{
			if (table->current == NULL)
			{
				if (pos == table->size - 1)
				{
					return 0;
				}
				pos = pos + 1;
				table->current = table->contents[pos];
				if (table->current != NULL)
				{
					return 1;
				}
			}
			else if (table->current->next == NULL)
			{
				if (pos == table->size - 1)
				{
					return 0;
				}
				pos = pos + 1;
				table->current = table->contents[pos];
				if (table->current != NULL)
				{
					return 1;
				}
			}
			else
			{
				table->current = table->current->next;
				return 1;
			}
		}
		//pos is >= table->size
		return 0;
	}
	else
	{
		return 0;
	}
}

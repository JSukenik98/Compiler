#include "SymTab.h"

extern void printSymTab();
extern void storeVar(char* name, SymTab table);
extern SymTab* doUnion(SymTab* table1, SymTab* table2);
extern SymTab* doIntersect(SymTab* table1, SymTab* table2);
extern SymTab* getVal(char* name);
extern SymTab* newSet(char* set);
#include <string.h> 
#include <stdlib.h>
#include <stdio.h>
/*********************************




/*Semantic cube*/
/*

"=="        { return(EQUALITY); }
"!="        { return(NOTEQUALITY); }
"<="        { return(LESSTHANOREQUAL); }
">="        { return(GREATERTHANOREQUAL); }

%left EQUALITY NOTEQUALITY
%left '<' '>' LESSTHANOREQUAL GREATERTHANOREQUAL
%left '-' '+'
%left '*' '/'

    PROGRAM, PROGRAMNAME, SEMICOLON, GREATERTHAN, SMALLERTHAN, EQUALITY, NOTEQUALITY, EQUAL, UNITARYMINUS,
    LESSTHANOREQUAL, GREATERTHANOREQUAL, MAIN, RIGHTCURLYBRACKET, VOID, NUMBERINTEGER, NUMBERFLOAT,
    LEFTCURLYBRACKET, RIGHTSQUAREBRACKET, LEFTSQUAREBRACKET, RIGHTPARENTHESIS, LETTERCHAR, WORDSTRING
    LEFTPARENTHESIS, VAR, COLON, MODULE, INTEGER, FLOAT, CHAR, COMMA, MODULENAME, THEN,
    RETURN, READ, WRITE, IF, ELSE, DO, WHILE, FOR, TO, COMPARISON, STRING, AND, OR, SIGN, IDENTIFIER

0 '==' EQUALITY 
1 '!=' NOTEQUALITY
2 '<=' LESSTHANOREQUAL

3 '>=' GREATERTHANOREQUAL
4 '<' SMALLERTHAN
5 '>' GREATERTHAN
6 '|' OR
7 '&' AND


8 '-' subtraction
9 '+' addition 
10 '*' multiplication
11 '/' division
12 '=' EQUAL


0 int
1 float
2 char

55 error


*/


/*Initial Global Function Table */


/*

globalProceduresDirectory *entryGlobalDirectory;

globalProceduresDirectory *globalProceduresDirectoryTable = (globalProceduresDirectory *)0;
int countFunctions=0;


*/
int semanticCube[13][3][3]; 

/*structure of the global procedures Directory */


struct globalProceduresDirectory
{
char *name; 
int type; 
int arrayParamsTypes[3]; 
struct globalVariables *globalMemory;
struct globalProceduresDirectory *next;
};
typedef struct globalProceduresDirectory globalProceduresDirectory;


/*structure of the procedures Directory */
struct proceduresDirectory
{
char *name; 
int codeinitial;
int type; 

int arrayParamsTypes[3]; 

struct parameters *initialParam; 
struct parameters *finalParam;
struct localVariables *localMemory;

struct proceduresDirectory *next; 
};
typedef struct proceduresDirectory proceduresDirectory;



/*structure of the global Variables */
struct globalVariables
{
char *name;
int virtualAddress;


/*
int type;
*/
int type; 


struct globalVariables *next; 
};
typedef struct globalVariables globalVariables;


/*structure of the local Variables */
struct localVariables
{
char *name; 
int virtualAddress;

int type;

struct globalVariables *globalVars;
struct localVariables *next; 
};
typedef struct localVariables localVariables;


/*structure of the parameters array */
struct parameters
{
int type; 
/*int offset;  data offset */
struct parameters *next; 
};
typedef struct parameters parameters;



/*structure of the constant talbe */
struct constantTable
{
char *name;

int intValue;
int *intValuebool;
char charValue;
float floatValue;

int type;
int virtualAddress;

struct constantTable *next; 
};
typedef struct constantTable constantTable;

/*structure of the constants */
struct constantsDirectory
{
char *name; 
int type; 
int arrayParamsTypes[3]; 
struct constantTable *constantTableMemory;
struct constantsDirectory *next;  
};
typedef struct constantsDirectory constantsDirectory;

/*structure of the temps talbe */
struct tempVar
{
char *name; 
int virtualAddress;
int type;

struct tempVar *next; 
};
typedef struct tempVar tempVar;


/*----------------------------------------------------------------

-----------------------------------------------------------------  */
globalProceduresDirectory *entryGlobalDirectory;
globalProceduresDirectory *globalProceduresDirectoryTable = (globalProceduresDirectory *)0;

globalVariables *entryglobalVariables;
globalVariables *globalVariablesTable = (globalVariables *)0;



proceduresDirectory *entryDirectory;
proceduresDirectory *proceduresDirectoryTable = (proceduresDirectory *)0;

localVariables *entrylocalVariables;
localVariables *localVariablesTable = (localVariables *)0;


constantsDirectory *entryConstantDirectory;
constantsDirectory *constantDirectory = (constantsDirectory *)0;
constantTable *entryconstantTable;
constantTable *constantTableTable = (constantTable *)0;



globalProceduresDirectory *entrytempDirectory;
globalProceduresDirectory *tempDirectoryTable = (globalProceduresDirectory *)0;

globalVariables *entrygtemporals;
globalVariables *temporalsVarTable = (globalVariables *)0;

/*
tempVar *entrytempVar;
tempVar *tempVarTable = (tempVar *)0;
*/

void init_Semantic_Cube(){

 globalProceduresDirectoryTable = NULL;
 globalVariablesTable = NULL;
 proceduresDirectoryTable = NULL;
 localVariablesTable = NULL;
 constantDirectory = NULL;
 constantTableTable = NULL;
 tempDirectoryTable = NULL;
 temporalsVarTable = NULL;





    int auxsemanticCube[13][3][3] = {{{0 , 0, 0}, {0 , 0, 0}, { 0, 0, 0}}, {{0 , 0, 0}, {0 , 0, 0}, { 0, 0, 0}}, 

                              {{ 0, 0, 9}, { 0, 0, 9}, { 9, 9, 0}}, {{ 0, 0, 9}, { 0, 0, 9}, { 9, 9, 0}}, 
                              {{ 0, 0, 9}, { 0, 0, 9}, { 9, 9, 0}}, {{ 0, 0, 9}, { 0, 0, 9}, { 9, 9, 0}},

                              {{ 0, 9, 9}, { 9, 9, 9}, { 9, 9, 9}}, {{ 0, 9, 9}, { 9, 9, 9}, { 9, 9, 9}}, 
                              
                              {{ 0, 1, 9}, { 1, 1, 9}, { 9, 9, 9}}, {{ 0, 1, 9}, { 1, 1, 9}, { 9, 9, 9}}, 
                              {{ 0, 1, 9}, { 1, 1, 9}, { 9, 9, 9}}, {{ 0, 1, 9}, { 1, 1, 9}, { 9, 9, 9}},

                              {{ 9, 9, 9}, { 9, 9, 9}, { 9, 9, 9}}}; 
    for(int i=0;i<13;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                semanticCube[i][j][k] = auxsemanticCube[i][j][k];
            }
        }
    }
}

int globalvirtualaddresscount[3] = {1000,2000,3000};
int localvirtualaddresscount[3] = {10000,11000,12000};
int constvirtualaddresscount[3] = {20000,21000,22000};
int tempvirtualaddresscount[3] =  {30000,31000,32000};
/*----------------------------------------------------------------

-----------------------------------------------------------------  */


/*---------------------------------------------------------------------------
Operations for the structures
-----------------------------------------------------------------------------*/



/*Operations to the procedure Directory  */


proceduresDirectory * putNameProceduresDirectory (char *dir_name )
{

proceduresDirectory *ptr;
ptr = (proceduresDirectory *) malloc (sizeof(proceduresDirectory)+1);

ptr->name = (char *) malloc (strlen(dir_name)+1);
strcpy (ptr->name,dir_name);


ptr->next = (struct proceduresDirectory *)proceduresDirectoryTable;
proceduresDirectoryTable = ptr;
proceduresDirectoryTable->arrayParamsTypes[0] = 0; 
proceduresDirectoryTable->arrayParamsTypes[1] = 0; 
proceduresDirectoryTable->arrayParamsTypes[2] = 0; 
proceduresDirectoryTable->codeinitial = 0;


return ptr;
}



void  putTypeProceduresDirectory (int funType )
{
    proceduresDirectoryTable->type = funType;
}

void  putcodeinitialProceduresDirectory (int intial)
{
    proceduresDirectoryTable->codeinitial = intial;
}

void addTypeParamsProceduresDirectory (int paramType)
{
    if (paramType == 0 ){
        proceduresDirectoryTable->arrayParamsTypes[0] +=1;
    }
    if (paramType == 1 ){
        proceduresDirectoryTable->arrayParamsTypes[1] +=1;
    }
    if (paramType == 2 ){
        proceduresDirectoryTable->arrayParamsTypes[2] +=1;
    }
}
/*
void addTypeParamsTableProceduresDirectory (int *paramType)
{
    if (*paramType == 0 | *paramType == 1 | *paramType == 2 ){
        if(proceduresDirectoryTable->initialParam == NULL){

            proceduresDirectoryTable->initialParam = (struct parameters *) malloc (sizeof(parameters));
            
            proceduresDirectoryTable->initialParam->type = (int *) malloc (sizeof(int));
            *//*
            proceduresDirectoryTable->initialParam->type = paramType;
            proceduresDirectoryTable->finalParam = (struct parameters *) proceduresDirectoryTable->initialParam ;

        }
        else{
            parameters *ptr;
            ptr = (struct parameters *) malloc (sizeof(parameters));
            ptr->type = paramType;
            proceduresDirectoryTable->finalParam->next = (struct parameters *) ptr ;
            proceduresDirectoryTable->finalParam = (struct parameters *) ptr ;

            
        }
    }

}
*/
/*----------------Params-----------------*/
void addTypeParamsTableProceduresDirectory (int paramType)
{
    if (paramType == 0 | paramType == 1 | paramType == 2 ){
        if(proceduresDirectoryTable->initialParam == NULL){

            proceduresDirectoryTable->initialParam = (struct parameters *) malloc (sizeof(parameters)+1);
            /*
            proceduresDirectoryTable->initialParam->type = (int *) malloc (sizeof(int));
            */
            proceduresDirectoryTable->initialParam->type = paramType;
            proceduresDirectoryTable->finalParam = (struct parameters *) proceduresDirectoryTable->initialParam ;

        }
        else{
            parameters *ptr;
            ptr = (struct parameters *) malloc (sizeof(parameters)+1);
            ptr->type = paramType;
            proceduresDirectoryTable->finalParam->next = (struct parameters *) ptr ;
            proceduresDirectoryTable->finalParam = (struct parameters *) ptr ;

            
        }
    }

}






proceduresDirectory * getProceduresDirectory (char *dir_name)
{
proceduresDirectory *ptr;
for ( ptr = proceduresDirectoryTable;
ptr != (proceduresDirectory *) 0;
ptr = (proceduresDirectory *)ptr->next )
if (strcmp (ptr->name,dir_name) == 0)
return ptr;
return NULL;
}


proceduresDirectory * getProceduresDirectorybycodeinitial (int codea)
{
proceduresDirectory *ptr;
for ( ptr = proceduresDirectoryTable;
ptr != (proceduresDirectory *) 0;
ptr = (proceduresDirectory *)ptr->next )
if (ptr->codeinitial == codea )
return ptr;
return 0;
}

int getcodeinitialProceduresDirectory (char *dir_name)
{
proceduresDirectory *ptr;
for ( ptr = proceduresDirectoryTable;
ptr != (proceduresDirectory *) 0;
ptr = (proceduresDirectory *)ptr->next )
if (strcmp (ptr->name,dir_name) == 0)
return ptr->codeinitial;
return -1;
}



/*----------------------------------------------------------------
Locals
------------------------------------------------------------------
------------------------------------------------------------------ */

void addLocalVarTable (char *name)
{

        if(proceduresDirectoryTable->localMemory == NULL){

            proceduresDirectoryTable->localMemory = (struct localVariables *) malloc (sizeof(localVariables)+1);
            /*
            proceduresDirectoryTable->initialParam->type = (int *) malloc (sizeof(int));
            */
            proceduresDirectoryTable->localMemory->name = name;
            localVariablesTable = (struct localVariables *) proceduresDirectoryTable->localMemory;
        }
        else{
            localVariables *ptr;
            ptr = (struct localVariables *) malloc (sizeof(localVariables)+1);
            ptr->name = name;
            ptr->next = (struct localVariables *) localVariablesTable;
            /*
            ptr->next = (struct localVariables *) proceduresDirectoryTable->localMemory;
            */
            proceduresDirectoryTable->localMemory = (struct localVariables *) ptr ;
            localVariablesTable = (struct localVariables *) ptr ;

    }

}


void addTypeLocalVarTable (int  type)
{

    localVariablesTable->type = type;

}


void addVirtualAddressLocalVarTable (int type)
{

    localVariablesTable->virtualAddress = localvirtualaddresscount[type];
    localvirtualaddresscount[type] ++;

}



int getLocalVarTableOnlylocal(char *name)
{
int foundFlag = 0;
localVariables *ptr;
if(localVariablesTable != NULL){
for ( ptr = localVariablesTable;
ptr != (localVariables *) 0;
ptr = (localVariables *)ptr->next )
if (strcmp (ptr->name,name) == 0){
foundFlag = ptr->virtualAddress;
}
if (foundFlag != 0)
{
    return foundFlag;
}
else{
    return 0;
}}
return 0;
}

int getGlobalVarTable(char *name)
{
int foundFlag = 0;
globalVariables *ptr;
if(globalVariablesTable != NULL){

for ( ptr = globalVariablesTable;
ptr != (globalVariables *) 0;
ptr = (globalVariables *)ptr->next ){

if (strcmp (ptr->name,name) == 0){
return ptr->virtualAddress;}

}
}
return 0;
}

int getLocalVarTable(char *name)
{
int foundFlag = 0;
localVariables *ptr;
if(localVariablesTable != NULL){
for ( ptr = localVariablesTable;
ptr != (localVariables *) 0;
ptr = (localVariables *)ptr->next )
if (strcmp (ptr->name,name) == 0){
foundFlag = ptr->virtualAddress;
}
if (foundFlag != 0)
{
    return foundFlag;
}
else{
    foundFlag = getGlobalVarTable(name);
    return foundFlag;
}
}
return 0;
}

int getbyVyrtualAddresLocalVarTable(int vir)
{
int foundFlag = 0;
localVariables *ptr;
if(localVariablesTable != NULL){
for ( ptr = localVariablesTable;
ptr != (localVariables *) 0;
ptr = (localVariables *)ptr->next )
if ( ptr->virtualAddress == vir){
foundFlag = ptr->virtualAddress;
}
if (foundFlag != 0)
{
    return foundFlag;
}
else{
    foundFlag = 0;
    return foundFlag;
}
}
return 0;
}






/*----------------------------------------------------------------
Globals Procedure
------------------------------------------------------------------
------------------------------------------------------------------ */
globalProceduresDirectory * CrateGlobalProceduresDirectory (char *dir_name)
{

globalProceduresDirectory *ptr;
ptr = (globalProceduresDirectory *) malloc (sizeof(globalProceduresDirectory)+1);

ptr->name = (char *) malloc (strlen(dir_name)+1);
strcpy (ptr->name,dir_name);


ptr->next = (struct globalProceduresDirectory *)globalProceduresDirectoryTable;
globalProceduresDirectoryTable = ptr;
globalProceduresDirectoryTable->arrayParamsTypes[0]= 0;
globalProceduresDirectoryTable->arrayParamsTypes[1]= 0;
globalProceduresDirectoryTable->arrayParamsTypes[2]= 0;

return ptr;
}


void addTypeGlobalsParamsProceduresDirectory (int paramType)
{
    if (paramType == 0 ){
        globalProceduresDirectoryTable->arrayParamsTypes[0] +=1;
    }
    if (paramType == 1 ){
        globalProceduresDirectoryTable->arrayParamsTypes[1] +=1;
    }
    if (paramType == 2 ){
        globalProceduresDirectoryTable->arrayParamsTypes[2] +=1;
    }
}

int getTypeGlobalsParamsProceduresDirectory (int paramType)
{
    if (paramType == 0 ){
        return globalProceduresDirectoryTable->arrayParamsTypes[0];
    }
    if (paramType == 1 ){
        return globalProceduresDirectoryTable->arrayParamsTypes[1];
    }
    if (paramType == 2 ){
        return globalProceduresDirectoryTable->arrayParamsTypes[2];
    }
}


/*----------------------------------------------------------------
Globals
------------------------------------------------------------------
------------------------------------------------------------------ */

void addGlobalVarTable (char *name)
{

        if(globalProceduresDirectoryTable->globalMemory == NULL){

            globalProceduresDirectoryTable->globalMemory = (struct globalVariables *) malloc (sizeof(globalVariables)+1);
            /*
            globalProceduresDirectoryTable->initialParam->type = (int *) malloc (sizeof(int));
            */
            globalProceduresDirectoryTable->globalMemory->name = name;
            globalVariablesTable = (struct globalVariables *) globalProceduresDirectoryTable->globalMemory;
        }
        else{
            globalVariables *ptr;
            ptr = (struct globalVariables *) malloc (sizeof(globalVariables)+1);
            ptr->name = name;
            ptr->next = (struct globalVariables *) globalVariablesTable;
            /*
            ptr->next = (struct globalVariables *) proceduresDirectoryTable->globalMemory;
            */
            globalProceduresDirectoryTable->globalMemory = (struct globalVariables *) ptr ;
            globalVariablesTable = (struct globalVariables *) ptr ;

    }

}




void addTypeGlobalVarTable (int type)
{

    globalVariablesTable->type = type;

}


void addVirtualAddressGlobalVarTable (int type)
{

    globalVariablesTable->virtualAddress = globalvirtualaddresscount[type];
    globalvirtualaddresscount[type] ++;

}




/*----------------------------------------------------------------
Temporals Procedure
------------------------------------------------------------------
------------------------------------------------------------------ */
globalProceduresDirectory * CrateGlobalProceduresDirectoryTemps ()
{

globalProceduresDirectory *ptr;
ptr = (globalProceduresDirectory *) malloc (sizeof(globalProceduresDirectory)+1);



ptr->next = (struct globalProceduresDirectory *)tempDirectoryTable;
tempDirectoryTable = ptr;

return ptr;
}


void addTypeGlobalsParamsProceduresDirectoryTemps (int paramType)
{
    if (paramType == 0 ){
        tempDirectoryTable->arrayParamsTypes[0] +=1;
    }
    if (paramType == 1 ){
        tempDirectoryTable->arrayParamsTypes[1] +=1;
    }
    if (paramType == 2 ){
        tempDirectoryTable->arrayParamsTypes[2] +=1;
    }
}

int getTypeGlobalsParamsProceduresDirectoryTemps (int paramType)
{
    if (paramType == 0 ){
        return tempDirectoryTable->arrayParamsTypes[0];
    }
    if (paramType == 1 ){
        return tempDirectoryTable->arrayParamsTypes[1];
    }
    if (paramType == 2 ){
        return tempDirectoryTable->arrayParamsTypes[2];
    }
}



/*----------------------------------------------------------------
Temporals
------------------------------------------------------------------
------------------------------------------------------------------ */


void addGlobalVarTableTemporals (char *name)
{

        if(tempDirectoryTable->globalMemory == NULL){

            tempDirectoryTable->globalMemory = (struct globalVariables *) malloc (sizeof(globalVariables)+1);
            /*
            tempDirectoryTable->initialParam->type = (int *) malloc (sizeof(int));
            */
            tempDirectoryTable->globalMemory->name = name;
            temporalsVarTable = (struct globalVariables *) tempDirectoryTable->globalMemory;
        }
        else{
            globalVariables *ptr;
            ptr = (struct globalVariables *) malloc (sizeof(globalVariables)+1);
            ptr->name = name;
            ptr->next = (struct globalVariables *) temporalsVarTable;
            /*
            ptr->next = (struct globalVariables *) proceduresDirectoryTable->globalMemory;
            */
            tempDirectoryTable->globalMemory = (struct globalVariables *) ptr ;
            temporalsVarTable = (struct globalVariables *) ptr ;

    }

}

void addTemporals ()
{

        if(tempDirectoryTable->globalMemory == NULL){
            tempDirectoryTable->globalMemory = (struct globalVariables *) malloc (sizeof(globalVariables)+1);
            temporalsVarTable = (struct globalVariables *) tempDirectoryTable->globalMemory;
        }
        else{
            globalVariables *ptr;
            ptr = (struct globalVariables *) malloc (sizeof(globalVariables)+1);
            ptr->next = (struct globalVariables *) temporalsVarTable;
            tempDirectoryTable->globalMemory = (struct globalVariables *) ptr ;
            temporalsVarTable = (struct globalVariables *) ptr ;

    }

}


void addTypeGlobalVarTableTemporals (int  type)
{

    temporalsVarTable->type =  type;

}

void addVirtualAddressGlobalVarTableTemporals (int type)
{

    temporalsVarTable->virtualAddress = tempvirtualaddresscount[type];
    tempvirtualaddresscount[type] ++;

}


globalVariables * getGlobalVarTableTemporals(char *name)
{
int foundFlag = 0;
globalVariables *ptr;
for ( ptr = temporalsVarTable;
ptr != (globalVariables *) 0;
ptr = (globalVariables *)ptr->next )
if (strcmp (ptr->name,name) == 0)
return ptr;
return NULL;
}


/*----------------------------------------------------------------
Constant Procedure
------------------------------------------------------------------
------------------------------------------------------------------ */
constantsDirectory * CrateConstantDirectory ()
{

constantsDirectory *ptr;
ptr = (constantsDirectory *) malloc (sizeof(constantsDirectory)+1);

ptr->next = (struct constantsDirectory *)constantDirectory;
constantDirectory = ptr;
constantDirectory->arrayParamsTypes[0] = 0;
constantDirectory->arrayParamsTypes[1] = 0;
constantDirectory->arrayParamsTypes[2] = 0;

return ptr;
}


void addTypeConstantParamsProceduresDirectory (int paramType)
{
    if (paramType == 0 ){
        constantDirectory->arrayParamsTypes[0] +=1;
    }
    if (paramType == 1 ){
        constantDirectory->arrayParamsTypes[1] +=1;
    }
    if (paramType == 2 ){
        constantDirectory->arrayParamsTypes[2] +=1;
    }
}

int getTypeConstantParamsProceduresDirectory (int paramType)
{
    if (paramType == 0 ){
        return constantDirectory->arrayParamsTypes[0];
    }
    if (paramType == 1 ){
        return constantDirectory->arrayParamsTypes[1];
    }
    if (paramType == 2 ){
        return constantDirectory->arrayParamsTypes[2];
    }
}

/*----------------------------------------------------------------
------------------------------------------------------------------
Constants 

------------------------------------------------------------------ */


void addConstantTable ()
{

        if(constantDirectory->constantTableMemory == NULL){

            constantDirectory->constantTableMemory = (struct constantTable *) malloc (sizeof(constantTable)+1);
            /*
            constantDirectory->initialParam->type = (int *) malloc (sizeof(int));
            */
            constantTableTable = (struct constantTable *) constantDirectory->constantTableMemory;
        }
        else{
            constantTable *ptr;
            ptr = (struct constantTable *) malloc (sizeof(constantTable)+1);
            
            
            ptr->next = (struct constantTable *) constantTableTable;
            /*
            ptr->next = (struct constantTable *) proceduresDirectoryTable->constantTableMemory;
            */
            constantDirectory->constantTableMemory = (struct constantTable *) ptr ;
            constantTableTable = (struct constantTable *) ptr ;

    }

}



void addTypeConstantTable (int type)
{
    constantTableTable->type =  type;
}


void addVirtualAddressConstantTable (int type)
{
    constantTableTable->virtualAddress = constvirtualaddresscount[type];
    constvirtualaddresscount[type] += 1;
}


constantTable * getConstTableByName(char *name)
{
constantTable *ptr;
for ( ptr = constantTableTable;
ptr != (constantTable *) 0;
ptr = (constantTable *)ptr->next )
if (strcmp (ptr->name,name) == 0)
return ptr;
return 0;
}


constantTable * getConstTableByAddress(int address)
{
constantTable *ptr;
for ( ptr = constantTableTable;
ptr != (constantTable *) 0;
ptr = (constantTable *)ptr->next )
if (ptr->virtualAddress == address)
return ptr;
return 0;
}

constantTable * getConstTableByInt(int val)
{
constantTable *ptr;
if ( constantTableTable != NULL){
for ( ptr = constantTableTable;
ptr != (constantTable *) 0;
ptr = (constantTable *)ptr->next ){
if (ptr->intValue == val){
return ptr;
}
}
}
return NULL;
}


void addConstTableByInt(int val)
{
constantTableTable->intValue = val; 
}

void addConstTableByFloat(float val)
{
constantTableTable->floatValue = val; 
}

void addConstTableByChar(char val)
{
constantTableTable->charValue = val; 
}





constantTable * getConstTableByChar(char val)
{
constantTable *ptr;
for ( ptr = constantTableTable;
ptr != (constantTable *) 0;
ptr = (constantTable *)ptr->next )
if (ptr->charValue == val)
return ptr;
return NULL;
}
constantTable * getConstTableByFloat(float val)
{
constantTable *ptr;
for ( ptr = constantTableTable;
ptr != (constantTable *) 0;
ptr = (constantTable *)ptr->next )
if (ptr->floatValue == val)
return ptr;
return NULL;
}



















































/* -----------------  0         1        2         3        4          5    6     7   8   9    10             11 12  13  14     15          16        17           18      19            20        21    22   23   24                         
*/
enum operationsCode {MAININIT, GOTO, GOTOFALSE, GOSUB, GOSUBSPECIAL, MULT, DIV, ADD, SUB, EQ, EQUALITYSYMBOL, LT,GT,LOET,GOET, ANDLOGICAL, ORLOGICAL, READVAL, WRITEVAL , RETURNVAL, ENDFUNCTION,PARAM, ERA, VER, END  };

/* OPERATIONS:  Representation */
 char *operationsCodeName[] = {"MAININIT" ,"GOTO", "GOTOFALSE", "GOSUB", "GOSUBSPECIAL", "MULT", "DIV", "ADD", "SUB", "EQ", "EQUALITYSYMBOL", "LT","GT","LOET","GOET", "ANDLOGICAL", "ORLOGICAL", "READVAL", "WRITEVAL" , "RETURNVAL", "ENDFUNCTION","PARAM", "ERA", "VER","END" };

struct instructionCode
{
enum operationsCode op;
int operation;

int arg1;
int arg2;
int result;


char *arg1c;
char *arg2c;
float farg1;
float farg2;

};
typedef struct instructionCode instructionCode;




struct instructionCode execution;
 struct instructionCode code[999];


/*-------------------------------------------------------------------------
Data Segment
-------------------------------------------------------------------------*/
int data_offset = 0; /* Initial offset */
int data_location() /* Reserves a data location */
{
return data_offset++;
}

/*Jump Stack, Operands Stack, Operators Satack */
struct jumpStack{
    int jumpValue;
    struct jumpStack *next;
    
};
typedef struct jumpStack jumpStack;

struct operandsStack{
    int operandAddress;
    struct operandsStack *next;
    
};
typedef struct operandsStack operandsStack;

struct operators{
    int opValue;
    struct operators *next;
    
};
typedef struct operators operators;


/*-----------------------------------------------------------------------
Initializa Stakcs
-----------------------------------------------------------------------*/

jumpStack *jumpStackActual;
operandsStack *operandsStackActual;
operators *operatorsActual;




/*-----------------------------------------------------------------------

Methods for struct jumpStack

-----------------------------------------------------------------------*/

jumpStack * addjumpStack (int jumpVal)
{
jumpStack *ptr;
ptr = (jumpStack *) malloc (sizeof(jumpStack)+1);
ptr->jumpValue =  jumpVal;
ptr->next = (struct jumpStack *)jumpStackActual;
jumpStackActual = ptr;
return ptr;
}


void * eliminateActualJumpStackNode ()
{
if(jumpStackActual == NULL){

}
else{
    jumpStack *ptr;
    ptr = (jumpStack *) malloc (sizeof(jumpStack)+1);
    ptr->next = (struct jumpStack *)jumpStackActual;
    jumpStackActual = (struct jumpStack *) jumpStackActual->next;
    free(ptr);
}

}

int getTopJumpStackValue()
{
if(jumpStackActual != NULL){ 
int value;
value = jumpStackActual->jumpValue;
return value;
}

return 0;
}


/*-----------------------------------------------------------------------

Methods for struct operands Stack

-----------------------------------------------------------------------*/


operandsStack * addoperandsStack (int operandAd)
{
operandsStack *ptr;
ptr = (operandsStack *) malloc (sizeof(operandsStack)+1);
ptr->operandAddress  = operandAd;
ptr->next = (struct operandsStack *)operandsStackActual;
operandsStackActual = ptr;
return ptr;
}


void  eliminateActualOperandsStackNode ()
{
    if(operandsStackActual == NULL){
    }
    else{
        operandsStack *ptr;
        ptr = (operandsStack *) malloc (sizeof(operandsStack)+1);
        ptr->next = (struct operandsStack *)operandsStackActual;
        operandsStackActual = (struct operandsStack *) operandsStackActual->next;
        free(ptr);
    }

}


int getTopOperandsStackValue()
{
    if(operandsStackActual != NULL){ 
        int value;
        value = operandsStackActual->operandAddress;
        return value;
    }
    return 0;
}




/*-----------------------------------------------------------------------

Methods for struct operators

operators *operatorsActual;

-----------------------------------------------------------------------*/



operators * addoperatorsStack (int opVal)
{
operators *ptr;
ptr = (operators *) malloc (sizeof(operators)+1);
ptr->opValue  = opVal;
ptr->next = (struct operators *)operatorsActual;
operatorsActual = ptr;
return ptr;
}

/*
void eliminateActualOperandsStackNode ()
{
if(operatorsActual == NULL){
}
else{
    operators *ptr;
    ptr = (operators *) malloc (sizeof(operators));
    ptr = (struct operators *)operatorsActual;
    operatorsActual = (struct operators *) operatorsActual->next;
    free(ptr);
}
}
*/

int getTopOperatorsStackValue()
{
if(operatorsActual != NULL){ 
int value;
value = operatorsActual->opValue;
return value;
}

return 0;
}






/*-------------------------------------------------------------------------
Code Segment
-------------------------------------------------------------------------*/
int code_offset; /* Initial offset */





/* Generates code at current location */
 void generate_code( int operation, int arg1, int arg2, int result )
{ code[code_offset].op = operation;
code[code_offset].arg1 = arg1;
code[code_offset].arg2 = arg2;
code[code_offset].result = result;
code_offset++;
}
void modify_code_at_given_cuad_num_arg1( int arg1, int cuad_num )
{ 
code[cuad_num].arg1 = arg1;
}
void modify_code_at_given_cuad_num_arg2( int arg2, int cuad_num )
{ 
code[code_offset].arg2 = arg2;
}
void modify_code_at_given_cuad_num_result( int result , int cuad_num )
{ 
code[cuad_num].result = result;
}


/* Generates code at a reserved location */
 void back_patch( int codeLine, int operation, int arg1, int arg2, int result )
{
code[codeLine].op = operation;
code[codeLine].arg1 = arg1;
code[codeLine].arg2 = arg2;
code[codeLine].result = result;
}

void addGotoFalse(int codeLine, int result ){
    code[codeLine].result = result;

}



/*-------------------------------------------------------------------------
Print Code to stdio
-------------------------------------------------------------------------*/
 void print_code()
{
int i = 0;
while (i < code_offset) {
printf("%d: %d %d %d %d \n",i, code[i].op, code[i].arg1,code[i].arg2,code[i].result );
i++;
}
}
/************************** End Code Generator **************************/







/*-------------------Start Virtual Machine-------------------------*/


/*-------------------------------------------------*/




struct intergers{
    int len;
    int  arrayinterger[];
};
typedef struct intergers intergers;

struct floats{
    int len;
    float arrayfloat[];
};
typedef struct floats floats;

struct chars{
    int len;
    float arraychar[];
};
typedef struct chars chars;


struct memValues{
    struct intergers *structintergers;
    struct floats *structfloats;
    struct chars *structchars;
    
};
typedef struct memValues memValues;

struct stackMemValues{
    struct memValues *memoryVar;
    struct stackMemValues *next;
};
typedef struct stackMemValues stackMemValues;

struct stackMemValues * actualLocalMemory;
struct stackMemValues * newLocalMemory;
struct memValues * globalMemory;
struct memValues * tempMemory;

struct parameters * paramsActual;

int globalvirtaddresscount[4];
int localvirtaddresscount[4];
int constvirtaddresscount[4];
int tempvirtaddresscount[4];

struct memValues * createMemory(struct memValues *s, int lenInt, int lenFloat, int lenChar){
    s = (struct memValues *) malloc(sizeof(struct memValues));

    s->structintergers = (struct intergers *) 
    malloc(sizeof(struct intergers)+ sizeof(int)*(lenInt));

    s->structfloats = (struct floats *) 
    malloc(sizeof(struct floats)+ sizeof(float)*(lenFloat));

    s->structchars = (struct chars *) 
    malloc(sizeof(struct chars)+ sizeof(char)*(lenChar)+1);

    return s;

}




/* Function for the cration of a new local memory*/
struct stackMemValues * createLocalMemory(struct stackMemValues *s, int lenInt, int lenFloat, int lenChar){
    s = (struct stackMemValues *) malloc(sizeof(struct stackMemValues));

    s->memoryVar = createMemory(s->memoryVar, lenInt, lenFloat, lenChar);
    return s;

}


void putTopLocalMemory(struct stackMemValues *s){
    s->next = actualLocalMemory;
    actualLocalMemory = s;
    
}


void erraseLocalMemory(){
    stackMemValues * s;
    s = actualLocalMemory;
    actualLocalMemory = actualLocalMemory->next;
    free(s);
}



void changeNewToActual(){
    newLocalMemory->next = actualLocalMemory;
    actualLocalMemory = newLocalMemory;
}



int returntypebyByVirtualAddress(int dir){
    if( (1000 <= dir && dir < 2000) | (10000 <= dir && dir < 11000) | (30000 <= dir && dir < 31000) ){
        return 1;
    }
    if( (2000 <= dir && dir < 3000) | (11000 <= dir && dir < 12000) | (31000 <= dir && dir < 32000) ){
        return 2;
    }
    if( (3000 <= dir && dir < 4000) | (12000 <= dir && dir < 13000) | (32000 <= dir && dir < 33000) ){
        return 3;
    }
    if(33000 <= dir && dir < 34000){
        return 4;
    }
    return 0 ; 

}


/*
struct memValues * getByVirtualAddressLocalGlobalConstant( int dir, int typelocal){
    

 
    if(returnGlobalLocalConstanteTemporal(dir) == 1){

        return globalMemory;
    }


    if(returnGlobalLocalConstanteTemporal(dir) == 2){
        if(typelocal == 1){
            return actualLocalMemory->memoryVar;
        }
        if(typelocal == 3){
            return newLocalMemory->memoryVar;
        }
        return 0;
    }

  
    if(returnGlobalLocalConstanteTemporal(dir) == 1){
        return tempMemory;
    }
    return 0;

}

*/
int returnGlobalLocalConstanteTemporal(int dir){
    if(1000 <= dir && dir < 10000){
        return 1;
    }
    if(10000 <= dir && dir < 20000){
        return 2;
    }

    if(20000 <= dir && dir < 30000){
        return 3;
    }

    if(30000 <= dir && dir < 33000){
        return 4;
    }

    if(33000 <= dir && dir < 34000){
        return 5;
    }
    return 0 ; 

}


int returtIntValue(int dir, int typelocal){
    if(returnGlobalLocalConstanteTemporal(dir) == 1){
        if(1000 <= dir && dir < 2000){
        return globalMemory->structintergers->arrayinterger[dir-1000];
    }
    }

    if(returnGlobalLocalConstanteTemporal(dir) == 2){
        if(typelocal == 1){
            if(10000 <= dir && dir < 11000){
                return actualLocalMemory->memoryVar->structintergers->arrayinterger[dir-10000];
            }
        }
        if(typelocal == 3){
            if(10000 <= dir && dir < 11000){
                return newLocalMemory->memoryVar->structintergers->arrayinterger[dir-10000];
            }
        }
        
    }

    if(returnGlobalLocalConstanteTemporal(dir) == 3){
        if(20000 <= dir && dir < 21000){
            struct constantTable * aux;
            aux = getConstTableByAddress(dir);
            return aux->intValue;
        }
    }

    if(returnGlobalLocalConstanteTemporal(dir) == 4){
        if(30000 <= dir && dir < 31000){
        return tempMemory->structintergers->arrayinterger[dir-30000];
        }
    }

    if(returnGlobalLocalConstanteTemporal(dir) == 4){
        if(33000 <= dir && dir < 34000){
        return tempMemory->structintergers->arrayinterger[dir-33000];
        }
    }
}

/*
if(returntypebyByVirtualAddress(returtIntValue(dir,1),1) = 1){
    int value = returtIntValue(returtIntValue(dir,1),1);
}
if(returntypebyByVirtualAddress(returtIntValue(dir,0),0) = 2){
    float value = returtIntValue(returtIntValue(dir,0),0);
}
if(returntypebyByVirtualAddress(returtIntValue(dir,0),0) = 3){
    char value = returtIntValue(returtIntValue(dir,0),0);
}

if(returntypebyByVirtualAddress(returtIntValue(dir,1),1) = 1){
    modifyIntValue(returtIntValue(dir,value,0),0);
}
if(returntypebyByVirtualAddress(returtIntValue(dir,0),0) = 2){
    modifyFloatValue(returtIntValue(dir,value,0),0);
}
if(returntypebyByVirtualAddress(returtIntValue(dir,0),0) = 3){
    modifyCharValue(returtIntValue(dir,value,0),0);
}
*/

void modifyIntValue(int dir, int value, int typelocal){
    if(returnGlobalLocalConstanteTemporal(dir) == 1){
        if(1000 <= dir && dir < 2000){
            globalMemory->structintergers->arrayinterger[dir-1000] = value;
        }
    }

    if(returnGlobalLocalConstanteTemporal(dir) == 2){
        if(typelocal == 1){
            if(10000 <= dir && dir < 11000){
                actualLocalMemory->memoryVar->structintergers->arrayinterger[dir-10000] = value;
            }
        }
        if(typelocal == 3){
            if(10000 <= dir && dir < 11000){
                newLocalMemory->memoryVar->structintergers->arrayinterger[dir-10000] = value;
            }
        }    
    }

    if(returnGlobalLocalConstanteTemporal(dir) == 3){
        if(30000 <= dir && dir < 31000){
            tempMemory->structintergers->arrayinterger[dir-30000] = value;
        }
    }
}


float returtfloatValue(int dir, int typelocal){
    if(returnGlobalLocalConstanteTemporal(dir) == 1){
        if(2000 <= dir && dir < 3000){
        return globalMemory->structfloats->arrayfloat[dir-2000];
    }
    }
    if(returnGlobalLocalConstanteTemporal(dir) == 2){
        if(typelocal == 1){
            if(11000 <= dir && dir < 12000){
                return actualLocalMemory->memoryVar->structfloats->arrayfloat[dir-11000];
            }
        }
        if(typelocal == 3){
            if(11000 <= dir && dir < 12000){
                return newLocalMemory->memoryVar->structfloats->arrayfloat[dir-11000];
            }
        }
    }
    if(returnGlobalLocalConstanteTemporal(dir) == 3){
        if(21000 <= dir && dir < 22000){
            struct constantTable * aux;
            aux = getConstTableByAddress(dir);
            return aux->floatValue;
        }
    }
    if(returnGlobalLocalConstanteTemporal(dir) == 4){
        if(31000 <= dir && dir < 32000){
        return tempMemory->structfloats->arrayfloat[dir-31000];
        }
    }

    return -1;
}

void modifyFloatValue(int dir, float value, int typelocal){
    if(returnGlobalLocalConstanteTemporal(dir) == 1){
        if(2000 <= dir && dir < 3000){
            globalMemory->structfloats->arrayfloat[dir-2000] = value;
        }
    }

    if(returnGlobalLocalConstanteTemporal(dir) == 2){
        if(typelocal == 1){
            if(11000 <= dir && dir < 12000){
                actualLocalMemory->memoryVar->structfloats->arrayfloat[dir-11000] = value;
            }
        }
        if(typelocal == 3){
            if(11000 <= dir && dir < 12000){
                newLocalMemory->memoryVar->structfloats->arrayfloat[dir-11000] = value;
            }
        }    
    }

    if(returnGlobalLocalConstanteTemporal(dir) == 3){
        if(31000 <= dir && dir < 32000){
            tempMemory->structfloats->arrayfloat[dir-31000] = value;
        }
    }
}


char returtcharValue(int dir, int typelocal){
    if(returnGlobalLocalConstanteTemporal(dir) == 1){
        if(3000 <= dir && dir < 4000){
        return globalMemory->structchars->arraychar[dir-3000];
    }
    }
    if(returnGlobalLocalConstanteTemporal(dir) == 2){
        if(typelocal == 1){
            if(12000 <= dir && dir < 13000){
                return actualLocalMemory->memoryVar->structchars->arraychar[dir-12000];
            }
        }
        if(typelocal == 3){
            if(12000 <= dir && dir < 13000){
                return newLocalMemory->memoryVar->structchars->arraychar[dir-12000];
            }
        }
    }
    if(returnGlobalLocalConstanteTemporal(dir) == 3){
        if(22000 <= dir && dir < 23000){
            struct constantTable * aux;
            aux = getConstTableByAddress(dir);
            return aux->charValue;
        }
    }
    if(returnGlobalLocalConstanteTemporal(dir) == 4){
        if(32000 <= dir && dir < 33000){
        return tempMemory->structchars->arraychar[dir-32000];
        }
    }

    return -1;
}

void modifyCharValue(int dir, char value, int typelocal){
    if(returnGlobalLocalConstanteTemporal(dir) == 1){
        if(3000 <= dir && dir < 4000){
            globalMemory->structchars->arraychar[dir-3000] = value;
        }
    }

    if(returnGlobalLocalConstanteTemporal(dir) == 2){
        if(typelocal == 1){
            if(12000 <= dir && dir < 13000){
                actualLocalMemory->memoryVar->structchars->arraychar[dir-12000] = value;
            }
        }
        if(typelocal == 3){
            if(12000 <= dir && dir < 13000){
                newLocalMemory->memoryVar->structchars->arraychar[dir-12000] = value;
            }
        }    
    }

    if(returnGlobalLocalConstanteTemporal(dir) == 3){
        if(32000 <= dir && dir < 33000){
            tempMemory->structchars->arraychar[dir-32000] = value;
        }
    }
}






/* RUN-TIME Stack Memory*/
int GotoReturnStack[999];
int top;
int initial;
/*-------------------------------------------------------------------------
Registers
-------------------------------------------------------------------------*/
int programcounter;


char ch;



 void execute_the_code_cycle(){
    globalvirtaddresscount[0] = 1000;
    globalvirtaddresscount[1] = 2000;
    globalvirtaddresscount[2] = 3000;
    globalvirtaddresscount[3] = 4000;


    localvirtaddresscount[0] = 10000;
    localvirtaddresscount[1] = 11000;
    localvirtaddresscount[2] = 12000;
    localvirtaddresscount[3] = 13000;


    constvirtaddresscount[0] = 20000;
    constvirtaddresscount[1] = 21000;
    constvirtaddresscount[2] = 22000;
    constvirtaddresscount[3] = 23000;


    tempvirtaddresscount[0] =  30000;
    tempvirtaddresscount[1] =  31000;
    tempvirtaddresscount[2] =  32000;
    tempvirtaddresscount[3] =  43000;



    int errorocurred =0;
    programcounter = 0;
    top = 0;
    initial = 0;

    globalProceduresDirectory * st = globalProceduresDirectoryTable;
    memValues *p = createMemory(p,st->arrayParamsTypes[0],st->arrayParamsTypes[1],st->arrayParamsTypes[2]) ;
    globalMemory = p;
    
    globalProceduresDirectory * s = tempDirectoryTable;
    memValues *q = createMemory(q,s->arrayParamsTypes[0],s->arrayParamsTypes[1],s->arrayParamsTypes[2]) ;
    tempMemory = q;

    stackMemValues *pa;
    proceduresDirectory * sa;



    

    do{
        printf("Program Counter : %d  \n" ,programcounter);
        execution = code[programcounter];
        programcounter++;
        switch(execution.op){
            /**/

            case MAININIT : printf("Initialice Execution\n"); programcounter = execution.result ;
            break;
            case GOTO : programcounter = execution.result ;
            break;
            case GOTOFALSE : if(returtIntValue(execution.arg1,0) >0){
                                programcounter = execution.result;
                             } ;
            break;
            case GOSUB :GotoReturnStack[top] = programcounter; top++ ; if(execution.result >0){
                                programcounter = execution.result;
                             } ; changeNewToActual(); 
            break;
            case GOSUBSPECIAL :  ;
            break;
            case MULT : if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                            int expval = returtIntValue(execution.arg1,1)*returtIntValue(execution.arg2,1);
                            modifyIntValue(execution.result,expval,1);
                        }
                        if( (returntypebyByVirtualAddress(execution.arg1) == 2) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                            float expval = returtfloatValue(execution.arg1,1)*returtIntValue(execution.arg2,1);
                            modifyFloatValue(execution.result,expval,1);
                        }
                        if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 2) ) {
                            float expval = returtIntValue(execution.arg1,1)*returtfloatValue(execution.arg2,1);
                            modifyFloatValue(execution.result,expval,1);
                        }
                        if( (returntypebyByVirtualAddress(execution.arg1) == 2) & (returntypebyByVirtualAddress(execution.arg2) == 2) ) {
                            float expval = returtfloatValue(execution.arg1,1)*returtfloatValue(execution.arg2,1);
                            modifyFloatValue(execution.result,expval,1);
                        }        
             ;

            break;


            case DIV :  if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                            int expval = returtIntValue(execution.arg1,1)/returtIntValue(execution.arg2,1);
                            modifyIntValue(execution.result,expval,1);
                        }
                        if( (returntypebyByVirtualAddress(execution.arg1) == 2) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                            float expval = returtfloatValue(execution.arg1,1)/returtIntValue(execution.arg2,1);
                            modifyFloatValue(execution.result,expval,1);
                        }
                        if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 2) ) {
                            float expval = returtIntValue(execution.arg1,1)/returtfloatValue(execution.arg2,1);
                            modifyFloatValue(execution.result,expval,1);
                        }
                        if( (returntypebyByVirtualAddress(execution.arg1) == 2) & (returntypebyByVirtualAddress(execution.arg2) == 2) ) {
                            float expval = returtfloatValue(execution.arg1,1)/returtfloatValue(execution.arg2,1);
                            modifyFloatValue(execution.result,expval,1);
                        }
             ;
            break;


            case ADD :  if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                            int expval = returtIntValue(execution.arg1,1) - returtIntValue(execution.arg2,1);
                            modifyIntValue(execution.result,expval,1);
                        }
                        if( (returntypebyByVirtualAddress(execution.arg1) == 2) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                            float expval = returtfloatValue(execution.arg1,1) - returtIntValue(execution.arg2,1);
                            modifyFloatValue(execution.result,expval,1);
                        }
                        if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 2) ) {
                            float expval = returtIntValue(execution.arg1,1) - returtfloatValue(execution.arg2,1);
                            modifyFloatValue(execution.result,expval,1);
                        }
                        if( (returntypebyByVirtualAddress(execution.arg1) == 2) & (returntypebyByVirtualAddress(execution.arg2) == 2) ) {
                            float expval = returtfloatValue(execution.arg1,1) - returtfloatValue(execution.arg2,1);
                            modifyFloatValue(execution.result,expval,1);
                        } ;
            break;


            case SUB :  if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                            int expval = returtIntValue(execution.arg1,1) - returtIntValue(execution.arg2,1);
                            modifyIntValue(execution.result,expval,1);
                        }
                        if( (returntypebyByVirtualAddress(execution.arg1) == 2) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                            float expval = returtfloatValue(execution.arg1,1) - returtIntValue(execution.arg2,1);
                            modifyFloatValue(execution.result,expval,1);
                        }
                        if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 2) ) {
                            float expval = returtIntValue(execution.arg1,1) - returtfloatValue(execution.arg2,1);
                            modifyFloatValue(execution.result,expval,1);
                        }
                        if( (returntypebyByVirtualAddress(execution.arg1) == 2) & (returntypebyByVirtualAddress(execution.arg2) == 2) ) {
                            float expval = returtfloatValue(execution.arg1,1) - returtfloatValue(execution.arg2,1);
                            modifyFloatValue(execution.result,expval,1);
                        } ;
            break;

            case EQ : if( (returntypebyByVirtualAddress(execution.arg1) == 1) )  {
                            int expval = returtIntValue(execution.arg1,1);
                            modifyIntValue(execution.result,expval,1);
                        }
                        if( (returntypebyByVirtualAddress(execution.arg1) == 2) ) {
                            float expval = returtfloatValue(execution.arg1,1);
                            modifyFloatValue(execution.result,expval,1);
                        }
                        if( (returntypebyByVirtualAddress(execution.arg1) == 3) ) {
                            char expval = returtIntValue(execution.arg1,1);
                            modifyFloatValue(execution.result,expval,1);
                        } ;
            break;

            case EQUALITYSYMBOL :   if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                                        if(returtIntValue(execution.arg1,1) == returtIntValue(execution.arg2,1)){
                                            modifyIntValue(execution.result,1,1);
                                        }
                                        else{
                                            modifyIntValue(execution.result,0,1);
                                        }
                                        
                                    }
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 2) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                                        modifyIntValue(execution.result,0,1);
                                    }
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 2) ) {
                                        modifyIntValue(execution.result,0,1);
                                    }
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 2) & (returntypebyByVirtualAddress(execution.arg2) == 2) ) {
                                        if(returtfloatValue(execution.arg1,1) == returtfloatValue(execution.arg2,1)){
                                            modifyIntValue(execution.result,1,1);
                                        }
                                        else{
                                            modifyIntValue(execution.result,0,1);
                                        }
                                    }
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 3) ) {
                                        modifyIntValue(execution.result,0,1);
                                    }
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 2) & (returntypebyByVirtualAddress(execution.arg2) == 3) ) {
                                        modifyIntValue(execution.result,0,1);
                                    }
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 3) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                                        modifyIntValue(execution.result,0,1);
                                    }
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 3) & (returntypebyByVirtualAddress(execution.arg2) == 2) ) {
                                        modifyIntValue(execution.result,0,1);
                                    }
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 3) & (returntypebyByVirtualAddress(execution.arg2) == 3) ) {
                                        if(returtcharValue(execution.arg1,1) == returtcharValue(execution.arg2,1)){
                                            modifyCharValue(execution.result,1,1);
                                        }
                                        else{
                                            modifyCharValue(execution.result,0,1);
                                        }
                                    } ; 


            break;
            case LT :               if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                                        if(returtIntValue(execution.arg1,1) < returtIntValue(execution.arg2,1)){
                                            modifyIntValue(execution.result,1,1);
                                        }
                                        else{
                                            modifyIntValue(execution.result,0,1);
                                        }
                                        
                                    }
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 2) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                                        modifyIntValue(execution.result,0,1);
                                    }
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 2) ) {
                                        modifyIntValue(execution.result,0,1);
                                    }
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 2) & (returntypebyByVirtualAddress(execution.arg2) == 2) ) {
                                        if(returtfloatValue(execution.arg1,1) < returtfloatValue(execution.arg2,1)){
                                            modifyIntValue(execution.result,1,1);
                                        }
                                        else{
                                            modifyIntValue(execution.result,0,1);
                                        }
                                    }
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 3) ) {
                                        modifyIntValue(execution.result,0,1);
                                    }
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 2) & (returntypebyByVirtualAddress(execution.arg2) == 3) ) {
                                        modifyIntValue(execution.result,0,1);
                                    }
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 3) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                                        modifyIntValue(execution.result,0,1);
                                    }
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 3) & (returntypebyByVirtualAddress(execution.arg2) == 2) ) {
                                        modifyIntValue(execution.result,0,1);
                                    }
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 3) & (returntypebyByVirtualAddress(execution.arg2) == 3) ) {
                                            modifyCharValue(execution.result,0,1);
                                    } ;
            break;
            case GT :               if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                                        if(returtIntValue(execution.arg1,1) > returtIntValue(execution.arg2,1)){
                                            modifyIntValue(execution.result,1,1);
                                        }
                                        else{
                                            modifyIntValue(execution.result,0,1);
                                        }
                                        
                                    }
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 2) & (returntypebyByVirtualAddress(execution.arg2) == 2) ) {
                                        if(returtfloatValue(execution.arg1,1) > returtfloatValue(execution.arg2,1)){
                                            modifyIntValue(execution.result,1,1);
                                        }
                                        else{
                                            modifyIntValue(execution.result,0,1);
                                        }
                                    } else{
                                        modifyIntValue(execution.result,0,1);
                                    };
            break;
            case LOET :             if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                                        if(returtIntValue(execution.arg1,1) <= returtIntValue(execution.arg2,1)){
                                            modifyIntValue(execution.result,1,1);
                                        }
                                        else{
                                            modifyIntValue(execution.result,0,1);
                                        }
                                        
                                    }
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 2) & (returntypebyByVirtualAddress(execution.arg2) == 2) ) {
                                        if(returtfloatValue(execution.arg1,1) <= returtfloatValue(execution.arg2,1)){
                                            modifyIntValue(execution.result,1,1);
                                        }
                                        else{
                                            modifyIntValue(execution.result,0,1);
                                        }
                                    } else{
                                        modifyIntValue(execution.result,0,1);
                                    }; 
            break;
            case GOET :             if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                                        if(returtIntValue(execution.arg1,1) >= returtIntValue(execution.arg2,1)){
                                            modifyIntValue(execution.result,1,1);
                                        }
                                        else{
                                            modifyIntValue(execution.result,0,1);
                                        }
                                        
                                    }
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 2) & (returntypebyByVirtualAddress(execution.arg2) == 2) ) {
                                        if(returtfloatValue(execution.arg1,1) >= returtfloatValue(execution.arg2,1)){
                                            modifyIntValue(execution.result,1,1);
                                        }
                                        else{
                                            modifyIntValue(execution.result,0,1);
                                        }
                                    } else{
                                        modifyIntValue(execution.result,0,1);
                                    } ;
            break;

            case ANDLOGICAL :        if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                                        if(returtIntValue(execution.arg1,1) > 0 & 0 < returtIntValue(execution.arg2,1)){
                                            modifyIntValue(execution.result,1,1);
                                        }
                                        else{
                                            modifyIntValue(execution.result,0,1);
                                        }
                                        
                                    }else{
                                        modifyIntValue(execution.result,0,1);
                                    }  ;
            break;
            case ORLOGICAL :        if( (returntypebyByVirtualAddress(execution.arg1) == 1) | (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                                        if(returtIntValue(execution.arg1,1) > 0 & 0 < returtIntValue(execution.arg2,1)){
                                            modifyIntValue(execution.result,1,1);
                                        }
                                        else{
                                            modifyIntValue(execution.result,0,1);
                                        }
                                        
                                    }else{
                                        modifyIntValue(execution.result,0,1);
                                    }  ; ;
            break;
            case READVAL :  if( (returntypebyByVirtualAddress(execution.arg1) == 1) )  {
                                int expval;
                                scanf("%d", &expval); 
                                modifyIntValue(execution.result,expval,1);
                            }
                            if( (returntypebyByVirtualAddress(execution.arg1) == 2) ) {
                                float expval;
                                scanf("%f", &expval); 
                                modifyFloatValue(execution.result,expval,1);
                            }
                            if( (returntypebyByVirtualAddress(execution.arg1) == 3) ) {
                                char expval;
                                scanf("%c", &expval); 
                                modifyFloatValue(execution.result,expval,1);
                            } ;      
            ;
            break;
            case WRITEVAL : if( (returntypebyByVirtualAddress(execution.arg1) == 1) )  {
                                int expval = returtIntValue(execution.result,1);
                                printf("%d Val \n", expval); 
                            }
                            if( (returntypebyByVirtualAddress(execution.arg1) == 2) ) {
                                float expval = returtfloatValue(execution.result,1);
                                printf("%f\n", expval); 
                            }
                            if( (returntypebyByVirtualAddress(execution.arg1) == 3) ) {
                                char expval = returtcharValue(execution.result,1);
                                printf("%c\n", expval); 
                            };
            break;
            case RETURNVAL : if( (returntypebyByVirtualAddress(execution.arg1) == 1) )  {
                                int expval = returtIntValue(execution.arg1,1);
                                modifyIntValue(execution.result,expval,1);
                            }
                            if( (returntypebyByVirtualAddress(execution.arg1) == 2) ) {
                                float expval = returtfloatValue(execution.arg1,1);
                                modifyFloatValue(execution.result,expval,1);
                            }
                            if( (returntypebyByVirtualAddress(execution.arg1) == 3) ) {
                                char expval = returtIntValue(execution.arg1,1);
                                modifyFloatValue(execution.result,expval,1);
                            }  ;
            break;
            case ENDFUNCTION : erraseLocalMemory() ; programcounter = GotoReturnStack[top-1];top--;
            break;
            case PARAM : if( (returntypebyByVirtualAddress(execution.arg1) == returntypebyByVirtualAddress(execution.result) & returntypebyByVirtualAddress(execution.result)  == 1 ) )  {
                                modifyIntValue(execution.result,returtIntValue(execution.arg1,2),2);
                                if(paramsActual == NULL){
                                    printf("error number of params on a method on execution");
                                    errorocurred = 1;
                                }else{
                                paramsActual = paramsActual->next;}
                            }
                            else{
                                if( (returntypebyByVirtualAddress(execution.arg1) == 2 & returntypebyByVirtualAddress(execution.result) == 2) ) {
                                    float expval = returtfloatValue(execution.arg1,2);
                                    modifyFloatValue(execution.result,expval,2);
                                    if(paramsActual == NULL){
                                        printf("error number of params on a method on execution");
                                        errorocurred = 1;
                                    }else{
                                    paramsActual = paramsActual->next;}
                                }
                                else{
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 3 & returntypebyByVirtualAddress(execution.arg1) == 3) ) {
                                        char expval = returtIntValue(execution.arg1,2);
                                        modifyFloatValue(execution.result,expval,2);
                                        if(paramsActual == NULL){
                                            printf("error number of params on a method on execution");
                                            errorocurred = 1;
                                        }
                                        else{
                                        paramsActual = paramsActual->next;
                                            }
                                    }
                                    else{
                                        printf("error of type on params on a method on execution");
                                        errorocurred = 1;
                                        }
                                    
                                }
                                
                                
                            }
                            /*
                            if( (returntypebyByVirtualAddress(execution.arg1) == 2 & returntypebyByVirtualAddress(execution.result) == 2) ) {
                                float expval = returtfloatValue(execution.arg1,1);
                                modifyFloatValue(execution.result,expval,1);
                            }
                            if( (returntypebyByVirtualAddress(execution.arg1) == 3 & returntypebyByVirtualAddress(execution.arg1) == 3) ) {
                                char expval = returtIntValue(execution.arg1,1);
                                modifyFloatValue(execution.result,expval,1);
                            } */
                             ;
            break;
            case ERA :  sa = getProceduresDirectorybycodeinitial (execution.result);
            pa = createLocalMemory(pa,sa->arrayParamsTypes[0],sa->arrayParamsTypes[1],sa->arrayParamsTypes[2]) ;
            pa->next = actualLocalMemory; newLocalMemory = pa; paramsActual = sa->initialParam;
            break;
            case VER :  ;
            break;
            case END : printf("Ending execution\n") ;
            break;

            
            default  : errorocurred = 1; printf( "Execution Error: Memory\n" ); 
            break;
            
            
            /*
            
            case  :  ;
            break;
            case  :  ;
            break;
            case  :  ;
            break;
            case  :  ;
            break;
            */

            /*
            case  :  ;
            break;
            */
            

        }
    } while (execution.op != END & programcounter < 999 & errorocurred != 1);
}













































/*----------------------------------------------------------------*/



















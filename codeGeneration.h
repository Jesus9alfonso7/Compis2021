#include <string.h> 
#include <stdlib.h>
#include <stdio.h>

#include<GL/glut.h>
#include<math.h>
#define pi 3.142857
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
*/


int semanticCube[14][3][3]; 
int errors=0;

/*Estructura para el directorio global*/
struct globalProceduresDirectory
{
    char *name; 
    int type; 
    int arrayParamsTypes[3];
    int temporalsCount[5];
    struct temporalVariables *globalTemporals;
    struct globalVariables *globalMemory;
    struct globalProceduresDirectory *next;
};
typedef struct globalProceduresDirectory globalProceduresDirectory;

/*Estructura para el directorio local */
struct proceduresDirectory
{
    char *name; 
    int codeinitial;
    int type; 
    int arrayParamsTypes[3];

    int temporalsCount[5];
    struct temporalVariables *localTemporals; 
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
int type;
int dimArray;
struct globalVariables *next; 
};
typedef struct globalVariables globalVariables;

/*structure of the temporal Variables */
struct temporalVariables
{
char *name;
int virtualAddress;
int type; 
struct temporalVariables *next; 
};
typedef struct temporalVariables temporalVariables;

/*structure of the local Variables */
struct localVariables
{
char *name; 
int virtualAddress;
int type;
int dimArray;
/*no used*/
struct globalVariables *globalVars;
struct localVariables *next; 
};
typedef struct localVariables localVariables;


/*structure of the parameters array */
struct parameters
{
int type;
int virtualAddress;
struct parameters *next; 
};
typedef struct parameters parameters;

/*structure of the parameters Stack */
struct parametersStack
{
    struct parameters *actualParam;
    struct parametersStack *next; 
};
typedef struct parametersStack parametersStack;



/*-----------------Constantes---------------*/

/*Estructura para strings*/
struct constantStringVars
{
    char *stringValue;
    int type;
    int virtualAddress;
    struct constantStringVars *next; 
};
typedef struct constantStringVars constantStringVars;

/*Estructura para los constantes chars*/
struct constantCharVars
{
    char charValue;
    int type;
    int virtualAddress;
    struct constantCharVars *next; 
};
typedef struct constantCharVars constantCharVars;


/*Estructura para los constantes flotantes*/
struct constantFloatVars
{
    float floatValue;
    int type;
    int virtualAddress;
    struct constantFloatVars *next; 
};
typedef struct constantFloatVars constantFloatVars;

/*Estructura para los constantes enteros*/
struct constantIntVars
{
    int intValue;
    int type;
    int virtualAddress;
    struct constantIntVars *next; 
};
typedef struct constantIntVars constantIntVars;

/*Estructura de las constantes*/
struct constantsDirectory
{
    int arrayParamsTypes[4]; 

    struct constantIntVars *constantIntMemory;
    struct constantFloatVars *constantFloatMemory;
    struct constantCharVars *constantCharMemory;
    struct constantStringVars *constantStringMemory;
};
typedef struct constantsDirectory constantsDirectory;



/*----------------------------------------------------------------

-----------------------------------------------------------------  */

globalProceduresDirectory *globalProceduresDirectoryTable = (globalProceduresDirectory *)0;

proceduresDirectory *proceduresDirectoryTable = (proceduresDirectory *)0;
parametersStack *parametersStackTable = (parametersStack *)0;



constantsDirectory *constantDirectory = (constantsDirectory *)0;

constantIntVars *consIntMemory;
constantFloatVars *consFloatMemory;
constantCharVars *consCharMemory;
constantStringVars *consStringMemory;

globalVariables *globalVariablesTable = (globalVariables *)0;
localVariables *localVariablesTable = (localVariables *)0;

temporalVariables *lastLocalTemporal = (temporalVariables *) 0;
temporalVariables *lastGlobalTemporal = (temporalVariables *) 0;


void init_Semantic_Cube(){

    globalProceduresDirectoryTable = NULL;
    globalVariablesTable = NULL;
    proceduresDirectoryTable = NULL;
    localVariablesTable = NULL;

    constantDirectory = NULL;


    consIntMemory  = NULL;
    consFloatMemory = NULL;
    consCharMemory = NULL;
    consStringMemory = NULL;



    lastLocalTemporal = NULL;
    lastGlobalTemporal = NULL;

    parametersStackTable = NULL;





    int auxsemanticCube[14][3][3] = {{{0 , 0, 0}, {0 , 0, 0}, { 0, 0, 0}}, {{0 , 0, 0}, {0 , 0, 0}, { 0, 0, 0}}, 

                              {{ 0, 0, 9}, { 0, 0, 9}, { 9, 9, 0}}, {{ 0, 0, 9}, { 0, 0, 9}, { 9, 9, 0}}, 
                              {{ 0, 0, 9}, { 0, 0, 9}, { 9, 9, 0}}, {{ 0, 0, 9}, { 0, 0, 9}, { 9, 9, 0}},

                              {{ 0, 9, 9}, { 9, 9, 9}, { 9, 9, 9}}, {{ 0, 9, 9}, { 9, 9, 9}, { 9, 9, 9}}, 
                              
                              {{ 0, 1, 9}, { 1, 1, 9}, { 9, 9, 9}}, {{ 0, 1, 9}, { 1, 1, 9}, { 9, 9, 9}}, 
                              {{ 0, 1, 9}, { 1, 1, 9}, { 9, 9, 9}}, {{ 0, 1, 9}, { 1, 1, 9}, { 9, 9, 9}},

                              {{ 9, 9, 9}, { 9, 9, 9}, { 9, 9, 9}}, {{ 0, 9, 9}, { 9, 1, 9}, { 9, 9, 9}}  }; 
    for(int i=0;i<14;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                semanticCube[i][j][k] = auxsemanticCube[i][j][k];
            }
        }
    }
}

int globalvirtualaddresscount[3] = {1000,2000,3000};
int localvirtualaddresscount[3] = {10000,11000,12000};
int constvirtualaddresscount[4] = {20000,21000,22000,23000};
int tempvirtualaddresscount[3] =  {30000,31000,32000};

/*                               Int   Float Char  String  PointerInt  Pointerfloat PointerChar  Limit      */
/*                                0      1      2      3      4            5           6            7*/
int globalTemporalsCount[8] = {  5000,  6000,  7000,  8000,  9000,       9300,        9600,       10000};
int fixGlobalTemporals[8] =   {  5000,  6000,  7000,  8000,  9000,       9300,        9600,       10000};
int localTemporalsCount[8] =  { 15000, 16000, 17000, 18000, 19000,      19300,       19600,       20000};
int fixLocalTemporals[8] =    { 15000, 16000, 17000, 18000, 19000,      19300,       19600,       20000};
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
        //printf("%d: %d \n",localVariablesTable->virtualAddress,paramType);
        proceduresDirectoryTable->finalParam->virtualAddress = localVariablesTable->virtualAddress;
    }

}






proceduresDirectory * getProceduresDirectory (char *dir_name)
{
    proceduresDirectory *ptr;
    for (ptr = proceduresDirectoryTable;
        ptr != (proceduresDirectory *) 0;
        ptr = (proceduresDirectory *)ptr->next ){
            if (strcmp (ptr->name,dir_name) == 0){
                return ptr;
            }
    }
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
            proceduresDirectoryTable->localMemory->name = name;
            localVariablesTable = (struct localVariables *) proceduresDirectoryTable->localMemory;
        }
        else{
            localVariables *ptr;
            ptr = (struct localVariables *) malloc (sizeof(localVariables)+1);
            ptr->name = name;
            ptr->next = (struct localVariables *) localVariablesTable;
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
    localvirtualaddresscount[type]++;

}

void resetVirtualAddressLocalVarTable ()
{
    localvirtualaddresscount[0] = 10000;
    localvirtualaddresscount[1] = 11000;
    localvirtualaddresscount[2] = 12000;
}




int getLocalVarTableOnlylocal(char *name)
{
    int foundFlag = 0;
    localVariables *ptr;
    if(localVariablesTable != NULL){
        for ( ptr = localVariablesTable; ptr != (localVariables *) 0; 
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
        }
    }
    return 0;
}

int getGlobalVarTable(char *name)
{
    int foundFlag = 0;
    globalVariables *ptr;
    if(globalVariablesTable != NULL){
        for ( ptr = globalVariablesTable; ptr != (globalVariables *) 0;
                                        ptr = (globalVariables *)ptr->next ){
            if (strcmp (ptr->name,name) == 0){
                return ptr->virtualAddress;
            }
        }
    }
    return 0;
}

int getLocalVarTable(char *name)
{
    int foundFlag = 0;
    localVariables *ptr;
    if(localVariablesTable != NULL){
        for ( ptr = localVariablesTable; ptr != (localVariables *) 0;
                                        ptr = (localVariables *)ptr->next ){
            if (strcmp (ptr->name,name) == 0){
                foundFlag = ptr->virtualAddress;
            }
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
    else{
        foundFlag = getGlobalVarTable(name);
        return foundFlag;
    }
}

int getbyVyrtualAddresLocalVarTable(int vir)
{
    int foundFlag = 0;
    localVariables *ptr;
    if(localVariablesTable != NULL){
        for ( ptr = localVariablesTable;  ptr != (localVariables *) 0;
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


int isArrayGlobalVar(char *name)
{
    int foundFlag = -2;
    globalVariables *ptr;
    if(globalVariablesTable != NULL){
        for ( ptr = globalVariablesTable; ptr != (globalVariables *) 0;
                                        ptr = (globalVariables *)ptr->next ){
            if (strcmp (ptr->name,name) == 0){
                return ptr->dimArray;
            }
        }
    }
    return -2;
}

int isArrayLocalVar(char *name)
{
    int foundFlag = -2;
    localVariables *ptr;
    if(localVariablesTable != NULL){
        for ( ptr = localVariablesTable; ptr != (localVariables *) 0;
                                        ptr = (localVariables *)ptr->next ){
            if (strcmp (ptr->name,name) == 0){
                foundFlag = ptr->dimArray;
            }
        }
        if (foundFlag != -2)
        {
            return foundFlag;
        }
        else{
            foundFlag = isArrayGlobalVar(name);
            return foundFlag;
        }
    }
    else{
        foundFlag = isArrayGlobalVar(name);
        return foundFlag;
    }
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
    globalProceduresDirectoryTable->temporalsCount[0]= 0;
    globalProceduresDirectoryTable->temporalsCount[1]= 0;
    globalProceduresDirectoryTable->temporalsCount[2]= 0;
    globalProceduresDirectoryTable->temporalsCount[3]= 0;
    globalProceduresDirectoryTable->temporalsCount[4]= 0;

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
            globalProceduresDirectoryTable->globalMemory->name = name;
            globalVariablesTable = (struct globalVariables *) globalProceduresDirectoryTable->globalMemory;
        }
        else{
            globalVariables *ptr;
            ptr = (struct globalVariables *) malloc (sizeof(globalVariables)+1);
            ptr->name = name;
            ptr->next = (struct globalVariables *) globalVariablesTable;
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

/* New */
void addGlobalTemporalsCount (globalProceduresDirectory *global, int tempType)
{
    if (tempType == 0 ){
        global->temporalsCount[0] +=1;
    }
    if (tempType == 1 ){
        global->temporalsCount[1] +=1;
    }
    if (tempType == 2 ){
        global->temporalsCount[2] +=1;
    }
    if (tempType == 3 ){
        global->temporalsCount[3] +=1;
    }
    if (tempType == 4 ){
        global->temporalsCount[4] +=1;
    }
}
void addLocalTemporalsCount (proceduresDirectory *local, int tempType)
{
    if (tempType == 0 ){
        local->temporalsCount[0] +=1;
    }
    if (tempType == 1 ){
        local->temporalsCount[1] +=1;
    }
    if (tempType == 2 ){
        local->temporalsCount[2] +=1;
    }
    if (tempType == 3 ){
        local->temporalsCount[3] +=1;
    }
    if (tempType == 4 ){
        local->temporalsCount[4] +=1;
    }
}





/*----------------------------------------------------------------
Temporals
------------------------------------------------------------------
------------------------------------------------------------------ */

/* Se agrega una nueva variable en los globales temporales con su tipo y dirección virtual */
void addGlobalTemporals (int type)
{
    temporalVariables *ptr;
    ptr = (struct temporalVariables *) malloc (sizeof(temporalVariables)+1);
    ptr->next = (struct temporalVariables *) lastGlobalTemporal;
    globalProceduresDirectoryTable->globalTemporals = (struct temporalVariables *) ptr ;
    lastGlobalTemporal = (struct temporalVariables *) ptr ;
    
    lastGlobalTemporal->type = type;
    //printf("%d \n", globalTemporalsCount[type]);
    //printf("%d \n", type);
    /* Se verifica que todavía hay espacio en el tipo específico de los temporales */
    if( globalTemporalsCount[type] < fixGlobalTemporals[type+1] ){
        lastGlobalTemporal->virtualAddress = globalTemporalsCount[type];
        globalTemporalsCount[type] ++;
    }
    else{
        errors++;
        printf("Error : Memory limit reached at Global Temporals");
    }
    //printf("%d \n", globalTemporalsCount[type]);
}

void addGlobalTemporalPointer (int type)
{
    temporalVariables *ptr;
    ptr = (struct temporalVariables *) malloc (sizeof(temporalVariables)+1);
    ptr->next = (struct temporalVariables *) lastGlobalTemporal;
    globalProceduresDirectoryTable->globalTemporals = (struct temporalVariables *) ptr ;
    lastGlobalTemporal = (struct temporalVariables *) ptr ;
    
    lastGlobalTemporal->type = type;
    type = 4;
    
    /* Se verifica que todavía hay espacio en el tipo específico de los temporales */
    if( globalTemporalsCount[type] < fixGlobalTemporals[type+1] ){
        lastGlobalTemporal->virtualAddress = globalTemporalsCount[type];
        globalTemporalsCount[type] ++;
    }
    else{
        errors++;
        printf("Error : Memory limit reached at Global Temporals");
    }
}

void addLocalTemporalPointer (int type)
{
    temporalVariables *ptr;
    ptr = (struct temporalVariables *) malloc (sizeof(temporalVariables)+1);
    ptr->next = (struct temporalVariables *) lastLocalTemporal;
    proceduresDirectoryTable->localTemporals = (struct temporalVariables *) ptr ;
    lastLocalTemporal = (struct temporalVariables *) ptr ;

    lastLocalTemporal->type =  type;
    type = 4;
    
    if( localTemporalsCount[type] < fixLocalTemporals[type+1] ){
        lastLocalTemporal->virtualAddress = localTemporalsCount[type];
        localTemporalsCount[type] ++;
    }
    else{
        errors++;
        printf("Error : Memory limit reached at Local Temporals");
    }
}

/*Se agrega una nueva variable en los locales temporales */
void addLocalTemporals (int type)
{
    temporalVariables *ptr;
    ptr = (struct temporalVariables *) malloc (sizeof(temporalVariables)+1);
    ptr->next = (struct temporalVariables *) lastLocalTemporal;
    proceduresDirectoryTable->localTemporals = (struct temporalVariables *) ptr ;
    lastLocalTemporal = (struct temporalVariables *) ptr ;

    lastLocalTemporal->type =  type;
    
    if( localTemporalsCount[type] < fixLocalTemporals[type+1] ){
        lastLocalTemporal->virtualAddress = localTemporalsCount[type];
        localTemporalsCount[type] ++;
    }
    else{
        errors++;
        printf("Error : Memory limit reached at Local Temporals");
    }
}




/*                               Int   Float Char  String  PointerInt  Pointerfloat PointerChar  Limit      */
/*                                0      1      2      3      4            5           6            7
int globalTemporalsCount[8] = {  5000,  6000,  7000,  8000,  9000,       9300,        9600,       10000};
int fixGlobalTemporals[8] =   {  5000,  6000,  7000,  8000,  9000,       9300,        9600,       10000};
int localTemporalsCount[8] =  { 15000, 16000, 17000, 18000, 19000,      19300,       19600,       20000};
int fixLocalTemporals[8] =    { 15000, 16000, 17000, 18000, 19000,      19300,       19600,       20000};

*/
int isPointer(int dir){
    if((dir >=fixGlobalTemporals[4] && dir < fixGlobalTemporals[5]  ) | (dir >=fixLocalTemporals[4] && dir < fixLocalTemporals[5]  ) ){
        return 1;
    }
    if((dir >=fixGlobalTemporals[5] && dir < fixGlobalTemporals[6]  ) | (dir >=fixLocalTemporals[5] && dir < fixLocalTemporals[6]  ) ){
        return 2;
    }
    if((dir >=fixGlobalTemporals[6] && dir < fixGlobalTemporals[7]  ) | (dir >=fixLocalTemporals[6] && dir < fixLocalTemporals[7]  ) ){
        return 3;
    }
    return 0;

}
/*----------------------------------------------------------------
Constant Procedure
------------------------------------------------------------------
------------------------------------------------------------------ */
constantsDirectory * CrateConstantDirectory (){
    
    constantsDirectory *ptr;
    ptr = (constantsDirectory *) malloc (sizeof(constantsDirectory)+1);

    constantDirectory = ptr;
    constantDirectory->arrayParamsTypes[0] = 0;
    constantDirectory->arrayParamsTypes[1] = 0;
    constantDirectory->arrayParamsTypes[2] = 0;
    constantDirectory->arrayParamsTypes[3] = 0;

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
    if (paramType == 3 ){
        constantDirectory->arrayParamsTypes[3] +=1;
    }
}


/*----------------------------------------------------------------
------------------------------------------------------------------
Constants 

------------------------------------------------------------------ */

void addConstantTable (int type) {
    if (type == 0 ){
        constantIntVars *ptr;
        ptr = (struct constantIntVars *) malloc (sizeof(constantIntVars)+1);
        ptr->next = (struct constantIntVars *) consIntMemory;
        constantDirectory->constantIntMemory = (struct constantIntVars *) ptr ;
        consIntMemory = (struct constantIntVars *) ptr;

        consIntMemory->virtualAddress = constvirtualaddresscount[type];
        constvirtualaddresscount[type] += 1;
        consIntMemory->type =  type;
    }
    if (type == 1 ){
        constantFloatVars *ptr;
        ptr = (struct constantFloatVars *) malloc (sizeof(constantFloatVars)+1);
        ptr->next = (struct constantFloatVars *) consFloatMemory;
        constantDirectory->constantFloatMemory = (struct constantFloatVars *) ptr ;
        consFloatMemory = (struct constantFloatVars *) ptr;

        consFloatMemory->virtualAddress = constvirtualaddresscount[type];
        constvirtualaddresscount[type] += 1;
        consFloatMemory->type =  type;
    }
    if (type == 2 ){
        constantCharVars *ptr;
        ptr = (struct constantCharVars *) malloc (sizeof(constantCharVars)+1);
        ptr->next = (struct constantCharVars *) consCharMemory;
        constantDirectory->constantCharMemory = (struct constantCharVars *) ptr ;
        consCharMemory = (struct constantCharVars *) ptr;

        consCharMemory->virtualAddress = constvirtualaddresscount[type];
        constvirtualaddresscount[type] += 1;
        consCharMemory->type =  type;
    }
    if (type == 3 ){
        constantStringVars *ptr;
        ptr = (struct constantStringVars *) malloc (sizeof(constantStringVars)+1);
        ptr->next = (struct constantStringVars *) consStringMemory;
        constantDirectory->constantStringMemory = (struct constantStringVars *) ptr ;
        consStringMemory = (struct constantStringVars *) ptr;

        consStringMemory->virtualAddress = constvirtualaddresscount[type];
        constvirtualaddresscount[type] += 1;
        consStringMemory->type =  type;
    }
}


constantIntVars * getConstIntMemoryByAddress(int address)
{
    constantIntVars *ptr;
    for ( ptr = consIntMemory; ptr != (constantIntVars *) 0;
                                    ptr = (constantIntVars *)ptr->next )
    if (ptr->virtualAddress == address)
        return ptr;
    return NULL;
}
constantFloatVars* getConstFloatMemoryByAddress(int address)
{
    constantFloatVars *ptr;
    for ( ptr = consFloatMemory; ptr != (constantFloatVars *) 0;
                                    ptr = (constantFloatVars *)ptr->next )
    if (ptr->virtualAddress == address)
        return ptr;
    return NULL;
}
constantCharVars * getConstCharMemoryByAddress(int address)
{
    constantCharVars *ptr;
    for ( ptr = consCharMemory; ptr != (constantCharVars *) 0;
                                    ptr = (constantCharVars *)ptr->next )
    if (ptr->virtualAddress == address)
        return ptr;
    return NULL;
}
constantStringVars * getConstStringMemoryByAddress(int address)
{
    constantStringVars *ptr;
    for ( ptr = consStringMemory; ptr != (constantStringVars *) 0;
                                    ptr = (constantStringVars *)ptr->next )
    if (ptr->virtualAddress == address)
        return ptr;
    return NULL;
}



constantIntVars * getConstTableByInt(int val)
{
    constantIntVars *ptr;
    if ( consIntMemory != NULL){
        for ( ptr = consIntMemory; ptr != (constantIntVars *) 0; 
                                        ptr = (constantIntVars *)ptr->next ){
            if (ptr->intValue == val){
                return ptr;
            }
        }
    }
    return NULL;
}
constantFloatVars * getConstTableByFloat(float val)
{
    constantFloatVars *ptr;
    if ( consFloatMemory != NULL){
        for ( ptr = consFloatMemory; ptr != (constantFloatVars *) 0; 
                                        ptr = (constantFloatVars *)ptr->next ){
            if (ptr->floatValue == val){
                return ptr;
            }
        }
    }
    return NULL;
}
constantCharVars * getConstTableByChar(char val)
{
    constantCharVars *ptr;
    if ( consCharMemory != NULL){
        for ( ptr = consCharMemory; ptr != (constantCharVars *) 0; 
                                        ptr = (constantCharVars *)ptr->next ){
            if (ptr->charValue == val){
                return ptr;
            }
        }
    }
    return NULL;
}
constantStringVars * getConstTableByString(char * val)
{
    constantStringVars *ptr;
    if ( consStringMemory != NULL){
        for ( ptr = consStringMemory; ptr != (constantStringVars *) 0; 
                                        ptr = (constantStringVars *)ptr->next ){  
            if (strcmp ( ptr->stringValue , val ) == 0){
                return ptr;
            }
            
        }
    }
    return NULL;
}


void addConstTableByInt(int val)
{
    consIntMemory->intValue = val; 
}

void addConstTableByFloat(float val)
{
    consFloatMemory->floatValue = val; 
}

void addConstTableByChar(char val)
{
    consCharMemory->charValue = val; 
}

void addConstTableByString(char *val)
{
    consStringMemory->stringValue = val; 
}
























































/* -----------------  0         1        2         3        4          5    6     7   8   9    10             11 12  13  14     15          16        17           18      19            20        21    22   23   24   25                 26        27      28     29       30       31                 
*/
enum operationsCode {MAININIT, GOTO, GOTOFALSE, GOSUB, GOSUBSPECIAL, MULT, DIV, ADD, SUB, EQ, EQUALITYSYMBOL, LT,GT,LOET,GOET, ANDLOGICAL, ORLOGICAL, READVAL, WRITEVAL , RETURNVAL, ENDFUNCTION,PARAM, ERA, VER, END, NOTEQUALITYSYMBOL, GOTOTRUE, MINUS,   PENUP, PENDOWN, LINE, CIRCLE};

/* OPERATIONS:  Representation */
char *operationsCodeName[] = {"MAININIT" ,"GOTO", "GOTOFALSE", "GOSUB", "GOSUBSPECIAL", "MULT", "DIV", "ADD", "SUB", "EQ", "EQUALITYSYMBOL", "LT","GT","LOET","GOET", "ANDLOGICAL", "ORLOGICAL", "READVAL", "WRITEVAL" , "RETURNVAL", "ENDFUNCTION","PARAM", "ERA", "VER","END", "NOTEQUALITYSYMBOL", "GOTOTRUE", "MINUS", "PENUP", "PENDOWN", "LINE", "CIRCLE" };

struct instructionCode
{
enum operationsCode op;
int operation;

int arg1;
int arg2;
int result;


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
Initializa Stacks
-----------------------------------------------------------------------*/
jumpStack *ifJumpStack;
operandsStack *operandsStackActual;
operators *operatorsActual;




/*-----------------------------------------------------------------------

Methods for struct jumpStack

-----------------------------------------------------------------------*/

jumpStack * addjumpStack (struct jumpStack *jumpStackActual, int jumpVal)
{
    jumpStack *ptr;
    ptr = (jumpStack *) malloc (sizeof(jumpStack)+1);
    ptr->jumpValue =  jumpVal;
    ptr->next = (struct jumpStack *)jumpStackActual;
    jumpStackActual = ptr;
    /*
    printf("%d : %d : %d : %d \n", jumpVal, ptr->jumpValue, jumpStackActual->jumpValue,
                                     ifJumpStack->jumpValue);
    */
    return jumpStackActual;
    
}


jumpStack * eliminateActualJumpStackNode (struct jumpStack *jumpStackActual)
{
    if(jumpStackActual == NULL){

    }
    else{
        jumpStack *ptr;
        if(jumpStackActual != NULL){
            ptr = (struct jumpStack *) jumpStackActual->next;
        }
        //printf("error if   \n");
        //printf("error %d  jumpStackActual -> jum value \n",jumpStackActual->jumpValue);
        free(jumpStackActual);
        //printf("error free   \n");
        jumpStackActual =  ptr;
    }
    return jumpStackActual;

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
































/*-----------------------------------Virtual Machine------------------------------------*/


/*-------------------------------------------------*/



/* Arreglo dinámico de Enteros */
struct intergers{
    int len;
    int  arrayinterger[];
};
typedef struct intergers intergers;

/* Arreglo dinámico de Flotantes */
struct floats{
    int len;
    float arrayfloat[];
};
typedef struct floats floats;

/* Arreglo dinámico de Chars */
struct chars{
    int len;
    char arraychar[];
};
typedef struct chars chars;

/* Memoria real */
struct memValues{
    struct intergers *structintergers;
    struct intergers *tempStructIntergers;
    struct intergers *tempStructPointers;
    struct floats *structfloats;
    struct floats *tempStructFloats;
    struct chars *structchars;
    struct chars *tempStructChars;
};
typedef struct memValues memValues;

/* Pila de la Memoria real*/
struct stackMemValues{
    struct memValues *memoryVar;
    struct stackMemValues *next;
};
typedef struct stackMemValues stackMemValues;

struct stackMemValues * actualLocalMemory;
struct stackMemValues * newLocalMemory;
struct memValues * globalMemory;


int globalvirtaddresscount[4];
int localvirtaddresscount[4];
int constvirtaddresscount[4];
int tempvirtaddresscount[4];
int errorocurred;

/*Se crea la memoria real y se crean los arreglos dinámicos de la máquina virtual*/
struct memValues * createMemory(struct memValues *s, int lenInt, int lenFloat, int lenChar, int tempInt, int tempFloat, int tempChar, int tempPointer){
    s = (struct memValues *) malloc(sizeof(struct memValues));

    /*Creación de los tipos*/
    s->structintergers = (struct intergers *) 
    malloc(sizeof(struct intergers)+ sizeof(int)*(lenInt));

    s->structfloats = (struct floats *) 
    malloc(sizeof(struct floats)+ sizeof(float)*(lenFloat));

    s->structchars = (struct chars *) 
    malloc(sizeof(struct chars)+ sizeof(char)*(lenChar)+1);

    /*Creación de los temporales*/
    s->tempStructIntergers = (struct intergers *) 
    malloc(sizeof(struct intergers)+ sizeof(int)*(tempInt));

    s->tempStructFloats = (struct floats *) 
    malloc(sizeof(struct floats)+ sizeof(float)*(tempFloat));

    s->tempStructChars = (struct chars *) 
    malloc(sizeof(struct chars)+ sizeof(char)*(tempChar)+1);
    
    s->tempStructPointers = (struct intergers *) 
    malloc(sizeof(struct intergers)+ sizeof(int)*(tempPointer));

    return s;
}

/* Creación de un atributo para la Pila de la Memoria real */
struct stackMemValues * createLocalMemory(struct stackMemValues *s, int lenInt, int lenFloat, int lenChar, int tempInt, int tempFloat, int tempChar, int tempPointer){
    s = (struct stackMemValues *) malloc(sizeof(struct stackMemValues));

    /* Creacion de la Memoria Real*/
    s->memoryVar = createMemory(NULL, lenInt, lenFloat, lenChar, tempInt, tempFloat, tempChar, tempPointer);
    return s;
}



/************** End structures for Virtual Machine **************/









/******** Start of methods for structures of Virtual Machine  ******/


void putTopLocalMemory(struct stackMemValues *s){
    s->next = actualLocalMemory;
    actualLocalMemory = s;
    
}


void erraseLocalMemory(){
    stackMemValues * s;
    s = actualLocalMemory;
    if(actualLocalMemory != NULL){
        actualLocalMemory = actualLocalMemory->next;
        if(s->memoryVar != NULL){
            if(s->memoryVar->structintergers != NULL){
                free(s->memoryVar->structintergers);
            }
            if(s->memoryVar->structfloats != NULL){
                free(s->memoryVar->structfloats);
            }
            if(s->memoryVar->structchars != NULL){
                free(s->memoryVar->structchars);
            }
            if(s->memoryVar->tempStructIntergers != NULL){
                free(s->memoryVar->tempStructIntergers);
            }
            if(s->memoryVar->tempStructFloats != NULL){
                free(s->memoryVar->tempStructFloats);
            }
            if(s->memoryVar->tempStructChars != NULL){
                free(s->memoryVar->tempStructChars);
            }
            if(s->memoryVar->tempStructPointers != NULL){
                free(s->memoryVar->tempStructPointers);
            }
            free(s->memoryVar);
        }
        else{
            errorocurred=1;
            printf("Error in Virtual Machine : In Actual memory : Memory variables are Null \n");
        }
        free(s);
    }
    else{
        errorocurred=1;
        printf("Error in Virtual Machine : Actual memory is Null \n");
    }

}



void changeNewToActual(){
    stackMemValues * auxPtr;
    if(newLocalMemory != NULL){
        auxPtr = newLocalMemory->next;
        newLocalMemory->next = actualLocalMemory;
        actualLocalMemory = newLocalMemory;
        newLocalMemory = auxPtr;
    }
    else{
        errorocurred = 1;
        printf("Error in Virtual Machine : New memory is Null \n");
    }
}

/*                               Int   Float Char  String  PointerInt  Pointerfloat PointerChar  Limit      */
/*                                0      1      2      3      4            5           6            7
int globalTemporalsCount[8] = {  5000,  6000,  7000,  8000,  9000,       9300,        9600,       10000};
int fixGlobalTemporals[8] =   {  5000,  6000,  7000,  8000,  9000,       9300,        9600,       10000};
int localTemporalsCount[8] =  { 15000, 16000, 17000, 18000, 19000,      19300,       19600,       20000};
int fixLocalTemporals[8] =    { 15000, 16000, 17000, 18000, 19000,      19300,       19600,       20000};

*/

int returntypebyByVirtualAddress(int dir){
    if( (1000 <= dir && dir < 2000) | (10000 <= dir && dir < 11000) | (20000 <= dir && dir < 21000) | (30000 <= dir && dir < 31000) 
        | (fixGlobalTemporals[0] <= dir && dir < fixGlobalTemporals[1] )
        | (fixGlobalTemporals[4] <= dir && dir < fixGlobalTemporals[5] )
        | (fixLocalTemporals[0] <= dir && dir < fixLocalTemporals[1]   )
        | (fixLocalTemporals[4] <= dir && dir < fixLocalTemporals[5]   )  ){
        return 1;
    }
    if( (2000 <= dir && dir < 3000) | (11000 <= dir && dir < 12000) | (21000 <= dir && dir < 22000) | (31000 <= dir && dir < 32000) 
        | (fixGlobalTemporals[1] <= dir && dir < fixGlobalTemporals[2] )
        | (fixLocalTemporals[1] <= dir && dir < fixLocalTemporals[2]   )  
        | (fixGlobalTemporals[5] <= dir && dir < fixGlobalTemporals[6] )
        | (fixLocalTemporals[5] <= dir && dir < fixLocalTemporals[6]   )  ){
        return 2;
    }
    if( (3000 <= dir && dir < 4000) | (12000 <= dir && dir < 13000) | (22000 <= dir && dir < 23000) | (32000 <= dir && dir < 33000) 
        | (fixGlobalTemporals[2] <= dir && dir < fixGlobalTemporals[3] )
        | (fixLocalTemporals[2] <= dir && dir < fixLocalTemporals[3]   )  
        | (fixGlobalTemporals[6] <= dir && dir < fixGlobalTemporals[7] )
        | (fixLocalTemporals[6] <= dir && dir < fixLocalTemporals[7]   )){
        return 3;
    }
    if(23000 <= dir && dir < 24000){
        return 4;
    }
    return 0 ; 

}


/*
int fixGlobalTemporals[6] =   {  5000,  6000,  7000,  8000,  9000,  10000};
int localTemporalsCount[6] =  { 15000, 16000, 17000, 18000, 19000,  20000};
int fixLocalTemporals[6]
*/
/*  1      2       3          4            5           6           7     */
/*Global Local Constante GlobTemporal GlobPoninter LocalTemp LocalPointer*/
/*returnGlobalLocalConstanteGlobTemporalGlobPoninterLocalTempLocalPointer*/
int returnGlobalLocalConstanteTemporal(int dir){
    if(1000 <= dir && dir < 5000){
        return 1;
    }
    if(10000 <= dir && dir < 15000){
        return 2;
    }

    if(20000 <= dir && dir < 25000){
        return 3;
    }

    if(fixGlobalTemporals[0] <= dir && dir < fixGlobalTemporals[4]){
        return 4;
    }
    if(fixGlobalTemporals[4] <= dir && dir < fixGlobalTemporals[7]){
        return 5;
    }

    if(fixLocalTemporals[0] <= dir && dir < fixLocalTemporals[4]){
        return 6;
    }
    if(fixLocalTemporals[4] <= dir && dir < fixLocalTemporals[7]){
        return 7;
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
            constantIntVars * aux = getConstIntMemoryByAddress(dir);
            if(aux != NULL){
                return aux->intValue;
            }
            else{
                return 0;
            }
        }
    }

    if(returnGlobalLocalConstanteTemporal(dir) == 4){
        if(fixGlobalTemporals[0] <= dir && dir < fixGlobalTemporals[1]){
        return globalMemory->tempStructIntergers->arrayinterger[dir-fixGlobalTemporals[0]];
        }
    }
    if(returnGlobalLocalConstanteTemporal(dir) == 5){
        if(fixGlobalTemporals[4] <= dir && dir < fixGlobalTemporals[7]){
            if(fixGlobalTemporals[4] <= dir && dir < fixGlobalTemporals[5])
            return globalMemory->tempStructPointers->arrayinterger[dir-fixGlobalTemporals[4]];
            if(fixGlobalTemporals[5] <= dir && dir < fixGlobalTemporals[6])
            return globalMemory->tempStructPointers->arrayinterger[dir-fixGlobalTemporals[5]];
            if(fixGlobalTemporals[6] <= dir && dir < fixGlobalTemporals[7])
            return globalMemory->tempStructPointers->arrayinterger[dir-fixGlobalTemporals[6]];
        }
    }

    if(returnGlobalLocalConstanteTemporal(dir) == 6){
        if(fixLocalTemporals[0] <= dir && dir < fixLocalTemporals[1]){
        return actualLocalMemory->memoryVar->tempStructIntergers->arrayinterger[dir-fixLocalTemporals[0]];
        }
    }
    if(returnGlobalLocalConstanteTemporal(dir) == 7){
        if(fixLocalTemporals[4] <= dir && dir < fixLocalTemporals[7]){
            if(fixLocalTemporals[4] <= dir && dir < fixLocalTemporals[5])
            return actualLocalMemory->memoryVar->tempStructPointers->arrayinterger[dir-fixLocalTemporals[4]];
            if(fixLocalTemporals[5] <= dir && dir < fixLocalTemporals[6])
            return actualLocalMemory->memoryVar->tempStructPointers->arrayinterger[dir-fixLocalTemporals[5]];
            if(fixLocalTemporals[6] <= dir && dir < fixLocalTemporals[7])
            return actualLocalMemory->memoryVar->tempStructPointers->arrayinterger[dir-fixLocalTemporals[6]];
        }
    }
}


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
    /*
    printf("returnGlobalLocalConstanteTemporal : %d \n int value : %d \n int typelocal : %d\n" ,
            returnGlobalLocalConstanteTemporal(dir),value,typelocal);
    printf("dir : %d  \n" ,dir);
    */
    if(returnGlobalLocalConstanteTemporal(dir) == 4){
        if(fixGlobalTemporals[0] <= dir && dir < fixGlobalTemporals[1]){
            globalMemory->tempStructIntergers->arrayinterger[dir-fixGlobalTemporals[0]] = value;
        }
    }
    if(returnGlobalLocalConstanteTemporal(dir) == 5){
        if(fixGlobalTemporals[4] <= dir && dir < fixGlobalTemporals[7]){
            if(fixGlobalTemporals[4] <= dir && dir < fixGlobalTemporals[5])
            globalMemory->tempStructPointers->arrayinterger[dir-fixGlobalTemporals[4]] = value;
            if(fixGlobalTemporals[5] <= dir && dir < fixGlobalTemporals[6])
            globalMemory->tempStructPointers->arrayinterger[dir-fixGlobalTemporals[5]] = value;
            if(fixGlobalTemporals[6] <= dir && dir < fixGlobalTemporals[7])
            globalMemory->tempStructPointers->arrayinterger[dir-fixGlobalTemporals[6]] = value;
        }
    }

    if(returnGlobalLocalConstanteTemporal(dir) == 6){
        if(fixLocalTemporals[0] <= dir && dir < fixLocalTemporals[1]){
            actualLocalMemory->memoryVar->tempStructIntergers->arrayinterger[dir-fixLocalTemporals[0]] = value;
        }
    }
    if(returnGlobalLocalConstanteTemporal(dir) == 7){
        if(fixLocalTemporals[4] <= dir && dir < fixLocalTemporals[7]){
            if(fixLocalTemporals[4] <= dir && dir < fixLocalTemporals[5])
            actualLocalMemory->memoryVar->tempStructPointers->arrayinterger[dir-fixLocalTemporals[4]] = value;
            if(fixLocalTemporals[5] <= dir && dir < fixLocalTemporals[6])
            actualLocalMemory->memoryVar->tempStructPointers->arrayinterger[dir-fixLocalTemporals[5]] = value;
            if(fixLocalTemporals[6] <= dir && dir < fixLocalTemporals[7])
            actualLocalMemory->memoryVar->tempStructPointers->arrayinterger[dir-fixLocalTemporals[6]] = value;
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
            constantFloatVars * aux = getConstFloatMemoryByAddress( dir );
            if(aux != NULL){
                return aux->floatValue;
            }
            else{
                return 0.0;
            }

        }
    }

    if(returnGlobalLocalConstanteTemporal(dir) == 4){
        if(fixGlobalTemporals[1] <= dir && dir < fixGlobalTemporals[2]){
        return globalMemory->tempStructFloats->arrayfloat[dir-fixGlobalTemporals[1]];
        }
    }

    if(returnGlobalLocalConstanteTemporal(dir) == 6){
        if(fixLocalTemporals[1] <= dir && dir < fixLocalTemporals[2]){
        return actualLocalMemory->memoryVar->tempStructFloats->arrayfloat[dir-fixLocalTemporals[1]];
        }
    }

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

    if(returnGlobalLocalConstanteTemporal(dir) == 4){
        if(fixGlobalTemporals[1] <= dir && dir < fixGlobalTemporals[2]){
            globalMemory->tempStructFloats->arrayfloat[dir-fixGlobalTemporals[1]] = value;
        }
    }

    if(returnGlobalLocalConstanteTemporal(dir) == 6){
        if(fixLocalTemporals[1] <= dir && dir < fixLocalTemporals[2]){
            actualLocalMemory->memoryVar->tempStructFloats->arrayfloat[dir-fixLocalTemporals[1]] = value;
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
            constantCharVars * aux = getConstCharMemoryByAddress(dir);
            if(aux != NULL){
                return aux->charValue;
            }
            else{
                return ' ';
            }
        }
    }

    if(returnGlobalLocalConstanteTemporal(dir) == 4){
        if(fixGlobalTemporals[2] <= dir && dir < fixGlobalTemporals[3]){
        return globalMemory->tempStructChars->arraychar[dir-fixGlobalTemporals[2]];
        }
    }

    if(returnGlobalLocalConstanteTemporal(dir) == 6){
        if(fixLocalTemporals[2] <= dir && dir < fixLocalTemporals[3]){
        return actualLocalMemory->memoryVar->tempStructChars->arraychar[dir-fixLocalTemporals[2]];
        }
    }

    return ' ';
}

char * returnStringValue(int dir, int typelocal){
    if(returnGlobalLocalConstanteTemporal(dir) == 3){
        if(23000 <= dir && dir < 24000){
            constantStringVars* aux = getConstStringMemoryByAddress(dir);
            if(aux != NULL){
                return aux->stringValue;
            }
            else{
                return NULL;
            }
        }
    }
    return NULL;
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

    if(returnGlobalLocalConstanteTemporal(dir) == 4){
        if(fixGlobalTemporals[2] <= dir && dir < fixGlobalTemporals[3]){
            globalMemory->tempStructChars->arraychar[dir-fixGlobalTemporals[2]] = value;
        }
    }

    if(returnGlobalLocalConstanteTemporal(dir) == 6){
        if(fixLocalTemporals[2] <= dir && dir < fixLocalTemporals[3]){
            actualLocalMemory->memoryVar->tempStructChars->arraychar[dir-fixLocalTemporals[2]] = value;
        }
    }
}




void eliminateGlbalMemory(){
    if (globalMemory != NULL){ 
                //printf("ini\n");
              if(globalMemory->structintergers != NULL)
                     free(globalMemory->structintergers);
              //printf("int\n");
              if(globalMemory->structfloats != NULL)
                     free(globalMemory->structfloats);
              //printf("float\n");
              if(globalMemory->structchars != NULL)
                     free(globalMemory->structchars);
              //printf("old\n");
              

              if(globalMemory->tempStructIntergers != NULL)
                     free(globalMemory->tempStructIntergers);
              //
              //printf("tint\n");
              if(globalMemory->tempStructFloats != NULL)
                     free(globalMemory->tempStructFloats);
              //
              //printf("tfloat\n");
              if(globalMemory->tempStructChars != NULL)
                     free(globalMemory->tempStructChars);
              //
              //printf("tchar\n");    
              if(globalMemory->tempStructPointers != NULL)
                     free(globalMemory->tempStructPointers);
              //
              //printf("new\n");


              free(globalMemory);
              globalMemory = NULL;
              //printf("new2\n");
       }
}



void eliminateall(){
       //printf("starting eliminate \n");
       if (globalProceduresDirectoryTable != NULL){
              //printf("global \n");  
              free(globalProceduresDirectoryTable->name);
              while(globalProceduresDirectoryTable->globalMemory != NULL){
                     globalVariables *ptr;
                     ptr = globalProceduresDirectoryTable->globalMemory->next;
                     free(globalProceduresDirectoryTable->globalMemory->name);
                     free(globalProceduresDirectoryTable->globalMemory);
                     globalProceduresDirectoryTable->globalMemory = ptr;
                     
              }
              //printf("global 1 while \n"); 
              while(globalProceduresDirectoryTable->globalTemporals != NULL){
                     temporalVariables *ptr;
                     ptr = globalProceduresDirectoryTable->globalTemporals->next;
                     free(globalProceduresDirectoryTable->globalTemporals->name);
                     free(globalProceduresDirectoryTable->globalTemporals);
                     globalProceduresDirectoryTable->globalTemporals = ptr;
                     
              }
              free(globalProceduresDirectoryTable);
              globalProceduresDirectoryTable =   NULL;
       }  
       /*
       printf("eliminate globalProceduresDirectoryTable \n");
       */


       while(proceduresDirectoryTable != NULL){
              proceduresDirectory *ptr;
              ptr = proceduresDirectoryTable->next;
              free(proceduresDirectoryTable->name);

              while(proceduresDirectoryTable->localMemory != NULL){
                     localVariables *ptr_aux;
                     ptr_aux = proceduresDirectoryTable->localMemory->next;
                     free(proceduresDirectoryTable->localMemory->name);
                     free(proceduresDirectoryTable->localMemory);
                     proceduresDirectoryTable->localMemory = ptr_aux;
              }
              while(proceduresDirectoryTable->localTemporals != NULL){
                     temporalVariables *ptr;
                     ptr = proceduresDirectoryTable->localTemporals->next;
                     free(proceduresDirectoryTable->localTemporals->name);
                     free(proceduresDirectoryTable->localTemporals);
                     proceduresDirectoryTable->localTemporals = ptr;
                     
              }

              while(proceduresDirectoryTable->initialParam != NULL){
                     parameters *ptr_aux;
                     ptr_aux = proceduresDirectoryTable->initialParam->next;
                     free(proceduresDirectoryTable->initialParam);
                     proceduresDirectoryTable->initialParam = ptr_aux;
              }

              free(proceduresDirectoryTable);
              proceduresDirectoryTable = ptr;
       }
       proceduresDirectoryTable =   NULL;
       
       /*
       printf("eliminate proceduresDirectoryTable \n");
       */



       while(constantDirectory != NULL){
              constantsDirectory *ptr = NULL;

              //Ints
              while(constantDirectory->constantIntMemory != NULL){
                     constantIntVars *ptr_aux;
                     ptr_aux = constantDirectory->constantIntMemory->next;
                     free(constantDirectory->constantIntMemory);
                     constantDirectory->constantIntMemory = ptr_aux;
              }
              //FLoats
              while(constantDirectory->constantFloatMemory != NULL){
                     constantFloatVars *ptr_aux;
                     ptr_aux = constantDirectory->constantFloatMemory->next;
                     free(constantDirectory->constantFloatMemory);
                     constantDirectory->constantFloatMemory = ptr_aux;
              }
              //Chars
              while(constantDirectory->constantCharMemory != NULL){
                     constantCharVars *ptr_aux;
                     ptr_aux = constantDirectory->constantCharMemory->next;
                     free(constantDirectory->constantCharMemory);
                     constantDirectory->constantCharMemory = ptr_aux;
              }
              //String
              //printf("eliminate string \n");
              while(constantDirectory->constantStringMemory != NULL){
                     constantStringVars *ptr_aux;
                     ptr_aux = constantDirectory->constantStringMemory->next;
                     if(constantDirectory->constantStringMemory->stringValue != NULL){
                     //printf("eliminate string %s \n",constantDirectory->constantStringMemory->stringValue );
                     free(constantDirectory->constantStringMemory->stringValue);
                     }
                     //printf("eliminate constantDirectory STRING\n");
                     free(constantDirectory->constantStringMemory);
                     //printf("eliminateD  \n");
                     constantDirectory->constantStringMemory = ptr_aux;
              }
              //printf("eliminate constantDirectory 1 \n");
              free(constantDirectory);
              //printf("eliminateD constantDirectory 2 \n");
              constantDirectory = ptr;
              //printf("eliminateD constantDirectory 3 \n");
       }
       constantDirectory =   NULL;
       /*
       printf("eliminate constantDirectory \n");
       */


       /********* Eliminate the dynamic memory of the code generator ***********/


       while(operandsStackActual != NULL){
              operandsStack *ptr;
              ptr = operandsStackActual->next;
              free(operandsStackActual);
              operandsStackActual = ptr;
       }
       operandsStackActual = NULL;

       while(operatorsActual != NULL){
              operators *ptr;
              ptr = operatorsActual->next;
              free(operatorsActual);
              operatorsActual = ptr;
       }
       operatorsActual = NULL;
       /*

       printf("Eliminate the dynamic memory of the code generator\n");
       */


       /********* Eliminate the dynamic memory of the Virtual Machine ***********/
       
       while(actualLocalMemory != NULL){
              stackMemValues *ptr;
              ptr = actualLocalMemory->next;
              if(actualLocalMemory->memoryVar != NULL){
                     if(actualLocalMemory->memoryVar->structintergers != NULL)
                     free(actualLocalMemory->memoryVar->structintergers);
                     if(actualLocalMemory->memoryVar->structfloats != NULL)
                     free(actualLocalMemory->memoryVar->structfloats);
                     if(actualLocalMemory->memoryVar->structchars != NULL)
                     free(actualLocalMemory->memoryVar->structchars);

                     if(actualLocalMemory->memoryVar->tempStructIntergers != NULL)
                     free(actualLocalMemory->memoryVar->tempStructIntergers);
                     if(actualLocalMemory->memoryVar->tempStructFloats != NULL)
                     free(actualLocalMemory->memoryVar->tempStructFloats);
                     if(actualLocalMemory->memoryVar->tempStructChars != NULL)
                     free(actualLocalMemory->memoryVar->tempStructChars);
                     if(actualLocalMemory->memoryVar->tempStructPointers != NULL)
                     free(actualLocalMemory->memoryVar->tempStructPointers);

                     free(actualLocalMemory->memoryVar);
              }
              free(actualLocalMemory);
              actualLocalMemory = ptr;
       }
       /**/

       actualLocalMemory = NULL;

       //printf("Eliminate actualLocalMemory\n");
       
       while(newLocalMemory != NULL){
              stackMemValues *ptr;
              ptr = newLocalMemory->next;

              if(newLocalMemory->memoryVar != NULL){
                     if(newLocalMemory->memoryVar->structintergers != NULL)
                     free(newLocalMemory->memoryVar->structintergers);
                     if(newLocalMemory->memoryVar->structfloats != NULL)
                     free(newLocalMemory->memoryVar->structfloats);
                     if(newLocalMemory->memoryVar->structchars != NULL)
                     free(newLocalMemory->memoryVar->structchars);

                     if(newLocalMemory->memoryVar->tempStructIntergers != NULL)
                     free(newLocalMemory->memoryVar->tempStructIntergers);
                     if(newLocalMemory->memoryVar->tempStructFloats != NULL)
                     free(newLocalMemory->memoryVar->tempStructFloats);
                     if(newLocalMemory->memoryVar->tempStructChars != NULL)
                     free(newLocalMemory->memoryVar->tempStructChars);
                     if(newLocalMemory->memoryVar->tempStructPointers != NULL)
                     free(newLocalMemory->memoryVar->tempStructPointers);

                     free(newLocalMemory->memoryVar);
              }

              free(newLocalMemory);
              newLocalMemory = ptr;
       }
       newLocalMemory = NULL;

       /*
       printf("Eliminate newLocalMemory\n");
       */
       //globalMemory = NULL;
        /*
       if (globalMemory != NULL){ 

              if(globalMemory->structintergers != NULL)
                     free(globalMemory->structintergers);

              if(globalMemory->structfloats != NULL)
                     free(globalMemory->structfloats);

              if(globalMemory->structchars != NULL)
                     free(globalMemory->structchars);


              if(globalMemory->tempStructIntergers != NULL)
                     free(globalMemory->tempStructIntergers);
       
              if(globalMemory->tempStructFloats != NULL)
                     free(globalMemory->tempStructFloats);
     
              if(globalMemory->tempStructChars != NULL)
                     free(globalMemory->tempStructChars);
                
              if(globalMemory->tempStructPointers != NULL)
                     free(globalMemory->tempStructPointers);
              

              free(globalMemory);
              globalMemory = NULL;
       }

      
       printf("Eliminate the dynamic memory of the Virtual Machine\n");
       */


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


float x, y;
float newposx, newposy; 
float radio;
int pen;

int slow;


void displayCircle (void) 
{   
    if(pen == 1){
        glBegin(GL_POINTS);
        float i;

        for ( i = 0; i < (2 * pi); i += 0.001)
        {
            newposx = radio * cos(i);
            newposy = radio * sin(i);
            glVertex2i(x+newposx, y+newposy);
        }
        printf("Print Circle\n") ;
        glEnd();
        //glFlush();
        glutSwapBuffers();
    }
}


void displayLine (void) 
{
    //printf("Error Line enter\n") ;
    slow = 1000*1000;
    if(pen == 1){
     glBegin(GL_LINES);
        //printf("Error Line enter if \n") ;
        slow = 1000*1000;

          glVertex2f(x, y);
              //printf("Error Line enter 1 vert\n") ;
              slow = 1000*1000;

    }
          x = newposx;
          y = newposy;
     if(pen == 1){     
          glVertex2f(x, y);
printf("Print Line\n") ;
slow = 1000*1000;
     glEnd();
     //glFlush();
     glutSwapBuffers();
     }
     //printf("Error Line enter end\n") ;
     slow = 1000*1000;
}




//OpenGL
// funcion para inicializar
void myInit (void)
{
    // color del fondo inicial
    // 3 argumentos son 0.0
    glClearColor(0.0, 0.0, 0.0, 1.0);
     
    // color de la linea, verde
    glColor3f(0.0, 1.0, 0.0);
     
    // tamaño de los puntos 1 pixel
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
     
    // dimencion de la ventana 
    gluOrtho2D(-780, 780, -420, 420);
}


int justOneCicle;




 void execute_the_code_cycle(void){
     
    if(justOneCicle != 0){

    }
    else{
    glClear(GL_COLOR_BUFFER_BIT);

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



    
    programcounter = 0;
    top = 0;
    initial = 0;
    errorocurred =0;



    /******* **************/

    globalProceduresDirectory * st = globalProceduresDirectoryTable;
    /*
    memValues *p = createMemory(p,st->arrayParamsTypes[0],st->arrayParamsTypes[1],
                    st->arrayParamsTypes[2], st->temporalsCount[0],st->temporalsCount[1],
                    st->temporalsCount[2], st->temporalsCount[4]) ;
    globalMemory = p;
    */
    globalMemory = createMemory(globalMemory,st->arrayParamsTypes[0],st->arrayParamsTypes[1],
                    st->arrayParamsTypes[2], st->temporalsCount[0],st->temporalsCount[1],
                    st->temporalsCount[2], st->temporalsCount[4]) ;
    int oldarg1;
    int oldarg2;
    int oldresult;


    stackMemValues *pa;
    proceduresDirectory * sa;
    pen =0;
    x = 60;
    y = 30;
    radio = 0;

    
    do{
        printf("Program Counter : %d  \n" ,programcounter);
        //printf("error?\n");
        execution = code[programcounter];
        //printf("error? exe\n");
        programcounter++;
        switch(execution.op){
            /**/

            case MAININIT : printf("Initialice Execution\n"); 
                            programcounter = execution.result ;
            break;
            case GOTO : programcounter = execution.result ;
            break;
            case GOTOFALSE :
                            oldarg1 = execution.arg1;
                            if ( isPointer(execution.arg1)  != 0 ) {
                                execution.arg1 = returtIntValue(execution.arg1,1);
                            } 
                            if(returtIntValue(execution.arg1,0) > 0){
                                
                             }
                             else{
                                programcounter = execution.result;
                             }
                             execution.arg1 = oldarg1;
                             ;
            break;
            case GOTOTRUE : oldarg1 = execution.arg1;
                            if ( isPointer(execution.arg1)  != 0 ) {
                                execution.arg1 = returtIntValue(execution.arg1,1);
                            }
                            if(returtIntValue(execution.arg1,0) > 0){
                                programcounter = execution.result;
                             } 
                             execution.arg1 = oldarg1;
                             ;
            break;
            case GOSUB :GotoReturnStack[top] = programcounter; top++ ; 
                        if(execution.result >0){
                            programcounter = execution.result;
                        } ; 
                        changeNewToActual(); 
            break;
            case GOSUBSPECIAL :  ;
            break;
            case MULT : 
            
                        oldarg1 = execution.arg1;
                        if ( isPointer(execution.arg1)  != 0 ) {
                                execution.arg1 = returtIntValue(execution.arg1,1);
                        }

                        oldarg2 = execution.arg2;
                        if ( isPointer(execution.arg2)  != 0 ) {
                                execution.arg2 = returtIntValue(execution.arg2,1);
                        }
            
            
            
                        if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                            int expval = returtIntValue(execution.arg1,1) * returtIntValue(execution.arg2,1);
                            modifyIntValue(execution.result,expval,1);
                            /*
                            printf("%d Val type \n", expval);
                            */
                        }
                        if( (returntypebyByVirtualAddress(execution.arg1) == 2) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                            float expval = returtfloatValue(execution.arg1,1) * returtIntValue(execution.arg2,1);
                            modifyFloatValue(execution.result,expval,1);
                        }
                        if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 2) ) {
                            float expval = returtIntValue(execution.arg1,1) * returtfloatValue(execution.arg2,1);
                            modifyFloatValue(execution.result,expval,1);
                        }
                        if( (returntypebyByVirtualAddress(execution.arg1) == 2) & (returntypebyByVirtualAddress(execution.arg2) == 2) ) {
                            float expval = returtfloatValue(execution.arg1,1) * returtfloatValue(execution.arg2,1);
                            modifyFloatValue(execution.result,expval,1);
                        }
                        execution.arg1 = oldarg1;
                        execution.arg2 = oldarg2;       
             ;

            break;


            case DIV :  

                        oldarg1 = execution.arg1;
                        if ( isPointer(execution.arg1)  != 0 ) {
                                execution.arg1 = returtIntValue(execution.arg1,1);
                        }

                        oldarg2 = execution.arg2;
                        if ( isPointer(execution.arg2)  != 0 ) {
                                execution.arg2 = returtIntValue(execution.arg2,1);
                        }



                        if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                            int expval = returtIntValue(execution.arg1,1)/returtIntValue(execution.arg2,1);
                            modifyIntValue(execution.result,expval,1);
                            /*
                            printf("%d Val type \n", expval);
                            */
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
                        execution.arg1 = oldarg1;
                        execution.arg2 = oldarg2;
             ;
            break;


            case ADD :  
                        /*int oldresult = execution.result;
                        if ( isPointer(execution.result)  != 0 ) {
                                execution.result = returtIntValue(execution.result,1);
                        }
                        */
                        oldarg1 = execution.arg1;
                        if ( isPointer(execution.arg1)  != 0 ) {
                                execution.arg1 = returtIntValue(execution.arg1,1);
                        }

                        oldarg2 = execution.arg2;
                        if ( isPointer(execution.arg2)  != 0 ) {
                                execution.arg2 = returtIntValue(execution.arg2,1);
                        }
            
            
                        if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                            int expval = returtIntValue(execution.arg1,1) + returtIntValue(execution.arg2,1);
                            modifyIntValue(execution.result,expval,1);
                            /*
                            printf("%d Val type \n", expval);
                            */
                        }
                        if( (returntypebyByVirtualAddress(execution.arg1) == 2) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                            float expval = returtfloatValue(execution.arg1,1) + returtIntValue(execution.arg2,1);
                            modifyFloatValue(execution.result,expval,1);
                        }
                        if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 2) ) {
                            float expval = returtIntValue(execution.arg1,1) + returtfloatValue(execution.arg2,1);
                            modifyFloatValue(execution.result,expval,1);
                        }
                        if( (returntypebyByVirtualAddress(execution.arg1) == 2) & (returntypebyByVirtualAddress(execution.arg2) == 2) ) {
                            float expval = returtfloatValue(execution.arg1,1) + returtfloatValue(execution.arg2,1);
                            modifyFloatValue(execution.result,expval,1);
                        }
                        /*
                        printf("%d Val type \n", returntypebyByVirtualAddress(execution.arg1));
                        */ 
                        execution.arg1 = oldarg1;
                        execution.arg2 = oldarg2;
                ;
            break;


            case SUB :  
                        oldarg1 = execution.arg1;
                        if ( isPointer(execution.arg1)  != 0 ) {
                                execution.arg1 = returtIntValue(execution.arg1,1);
                        }

                        oldarg2 = execution.arg2;
                        if ( isPointer(execution.arg2)  != 0 ) {
                                execution.arg2 = returtIntValue(execution.arg2,1);
                        }
            
            
            
            
                        if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                            int expval = returtIntValue(execution.arg1,1) - returtIntValue(execution.arg2,1);
                            modifyIntValue(execution.result,expval,1);
                            /*
                            printf("%d Val type \n", expval);
                            */
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
                        } 
                        execution.arg1 = oldarg1;
                        execution.arg2 = oldarg2;        
                ;
            break;

            case EQ :   oldarg1 = execution.arg1;
                        if ( isPointer(execution.arg1)  != 0 ) {
                                execution.arg1 = returtIntValue(execution.arg1,1);
                        }

                        oldresult = execution.result;
                        if ( isPointer(execution.result)  != 0 ) {
                                execution.result = returtIntValue(execution.result,1);
                        }
            
                        if( (returntypebyByVirtualAddress(execution.arg1) == 1) )  {
                            int expval = returtIntValue(execution.arg1,1);
                            /*
                            int expval2 = returtIntValue(execution.result,1);
                            int expval30000 = returtIntValue(30000,1);
                            printf("Exarg1 val %d \n",expval);
                            printf("expval2 val %d \n",expval2);
                            printf("expval30000 val %d \n",expval30000);
                            */
                            modifyIntValue(execution.result,expval,1);
                            /*
                            printf("After Exarg1 val %d \n",expval);
                            printf("After expval2 val %d \n",expval2);
                            */
                            
                        }
                        if( (returntypebyByVirtualAddress(execution.arg1) == 2) ) {
                            float expval = returtfloatValue(execution.arg1,1);
                            modifyFloatValue(execution.result,expval,1);
                        }
                        if( (returntypebyByVirtualAddress(execution.arg1) == 3) ) {
                            char expval = returtcharValue(execution.arg1,1);
                            modifyCharValue(execution.result,expval,1);
                        }
                        execution.arg1 = oldarg1;
                        execution.result = oldresult;
                         ;
            break;
            case MINUS : 
                        oldarg1 = execution.arg1;
                        if ( isPointer(execution.arg1)  != 0 ) {
                                execution.arg1 = returtIntValue(execution.arg1,1);
                        }

                        oldresult = execution.result;
                        if ( isPointer(execution.result)  != 0 ) {
                                execution.result = returtIntValue(execution.result,1);
                        }
            
                        if( (returntypebyByVirtualAddress(execution.arg1) == 1) )  {
                            int expval = -returtIntValue(execution.arg1,1);
                            /*
                            int expval2 = returtIntValue(execution.result,1);
                            int expval30000 = returtIntValue(30000,1);
                            printf("Exarg1 val %d \n",expval);
                            printf("expval2 val %d \n",expval2);
                            printf("expval30000 val %d \n",expval30000);
                            */
                            modifyIntValue(execution.result,expval,1);
                            /*
                            printf("After Exarg1 val %d \n",expval);
                            printf("After expval2 val %d \n",expval2);
                            */
                            
                        }
                        if( (returntypebyByVirtualAddress(execution.arg1) == 2) ) {
                            float expval = -returtfloatValue(execution.arg1,1);
                            modifyFloatValue(execution.result,expval,1);
                        }
                        if( (returntypebyByVirtualAddress(execution.arg1) == 3) ) {
                            char expval = returtIntValue(execution.arg1,1);
                            modifyFloatValue(execution.result,expval,1);
                        } 
                        execution.arg1 = oldarg1;
                        execution.result = oldresult;
                        ;
            break;

            case EQUALITYSYMBOL :   
            
                        oldarg1 = execution.arg1;
                        if ( isPointer(execution.arg1)  != 0 ) {
                                execution.arg1 = returtIntValue(execution.arg1,1);
                        }

                        oldarg2 = execution.arg2;
                        if ( isPointer(execution.arg2)  != 0 ) {
                                execution.arg2 = returtIntValue(execution.arg2,1);
                        }
            
            
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
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
                                            modifyIntValue(execution.result,1,1);
                                            /*
                                            printf("True equality : %c \n",returtcharValue(execution.arg1,1));
                                            printf("True equality : %c \n",returtcharValue(execution.arg2,1));
                                            */
                                        }
                                        else{
                                            modifyIntValue(execution.result,0,1);
                                        }
                                    } 
                                    execution.arg1 = oldarg1;
                                    execution.arg2 = oldarg2;
                        ; 


            break;
            case NOTEQUALITYSYMBOL :
            
            
                        oldarg1 = execution.arg1;
                        if ( isPointer(execution.arg1)  != 0 ) {
                                execution.arg1 = returtIntValue(execution.arg1,1);
                        }

                        oldarg2 = execution.arg2;
                        if ( isPointer(execution.arg2)  != 0 ) {
                                execution.arg2 = returtIntValue(execution.arg2,1);
                        }
            
            
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                                        if(returtIntValue(execution.arg1,1) != returtIntValue(execution.arg2,1)){
                                            modifyIntValue(execution.result,1,1);
                                        }
                                        else{
                                            modifyIntValue(execution.result,0,1);
                                        }
                                        
                                    }
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 2) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                                        modifyIntValue(execution.result,1,1);
                                    }
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 2) ) {
                                        modifyIntValue(execution.result,1,1);
                                    }
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 2) & (returntypebyByVirtualAddress(execution.arg2) == 2) ) {
                                        if(returtfloatValue(execution.arg1,1) != returtfloatValue(execution.arg2,1)){
                                            modifyIntValue(execution.result,1,1);
                                        }
                                        else{
                                            modifyIntValue(execution.result,0,1);
                                        }
                                    }
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 3) ) {
                                        modifyIntValue(execution.result,1,1);
                                    }
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 2) & (returntypebyByVirtualAddress(execution.arg2) == 3) ) {
                                        modifyIntValue(execution.result,1,1);
                                    }
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 3) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                                        modifyIntValue(execution.result,1,1);
                                    }
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 3) & (returntypebyByVirtualAddress(execution.arg2) == 2) ) {
                                        modifyIntValue(execution.result,1,1);
                                    }
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 3) & (returntypebyByVirtualAddress(execution.arg2) == 3) ) {
                                        if(returtcharValue(execution.arg1,1) != returtcharValue(execution.arg2,1)){
                                            modifyCharValue(execution.result,1,1);
                                        }
                                        else{
                                            modifyCharValue(execution.result,0,1);
                                        }
                                    } 
                                    execution.arg1 = oldarg1;
                                    execution.arg2 = oldarg2;
                        ; 


            break;
            case LT :               
            
                        oldarg1 = execution.arg1;
                        if ( isPointer(execution.arg1)  != 0 ) {
                                execution.arg1 = returtIntValue(execution.arg1,1);
                        }

                        oldarg2 = execution.arg2;
                        if ( isPointer(execution.arg2)  != 0 ) {
                                execution.arg2 = returtIntValue(execution.arg2,1);
                        }
            
            
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
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
                                    }
                                    execution.arg1 = oldarg1;
                                    execution.arg2 = oldarg2;
                         ;
            break;
            case GT :               
            
                        oldarg1 = execution.arg1;
                        if ( isPointer(execution.arg1)  != 0 ) {
                                execution.arg1 = returtIntValue(execution.arg1,1);
                        }

                        oldarg2 = execution.arg2;
                        if ( isPointer(execution.arg2)  != 0 ) {
                                execution.arg2 = returtIntValue(execution.arg2,1);
                        }
            
            
            
            
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                                        /*
                                        printf("Enter Both Int\n"); 
                                        */
                                        if(returtIntValue(execution.arg1,1) > returtIntValue(execution.arg2,1)){
                                            /*
                                            int expval = returtIntValue(30000,1);
                                            printf("Before val %d \n",expval);
                                            */
                                            modifyIntValue(execution.result,1,1);
                                            /*
                                            expval = returtIntValue(30000,1);
                                            printf("After val %d \n",expval);
                                            */
                                        }
                                        else{
                                            modifyIntValue(execution.result,0,1);
                                            /*
                                            printf("Enter Greater Than False\n"); 
                                            */
                                        }
                                        
                                    }else{
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 2) & (returntypebyByVirtualAddress(execution.arg2) == 2) ) {
                                        if(returtfloatValue(execution.arg1,1) > returtfloatValue(execution.arg2,1)){
                                            modifyIntValue(execution.result,1,1);
                                        }
                                        else{
                                            modifyIntValue(execution.result,0,1);
                                        }
                                    } else{
                                        modifyIntValue(execution.result,0,1);
                                    }}
                                    
                                    
                                    execution.arg1 = oldarg1;
                                    execution.arg2 = oldarg2;
                        ;
            break;
            case LOET :             
                        oldarg1 = execution.arg1;
                        if ( isPointer(execution.arg1)  != 0 ) {
                                execution.arg1 = returtIntValue(execution.arg1,1);
                        }

                        oldarg2 = execution.arg2;
                        if ( isPointer(execution.arg2)  != 0 ) {
                                execution.arg2 = returtIntValue(execution.arg2,1);
                        }
            
            
            
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                                        if(returtIntValue(execution.arg1,1) <= returtIntValue(execution.arg2,1)){
                                            modifyIntValue(execution.result,1,1);
                                        }
                                        else{
                                            modifyIntValue(execution.result,0,1);
                                        }
                                        
                                    }else{
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 2) & (returntypebyByVirtualAddress(execution.arg2) == 2) ) {
                                        if(returtfloatValue(execution.arg1,1) <= returtfloatValue(execution.arg2,1)){
                                            modifyIntValue(execution.result,1,1);
                                        }
                                        else{
                                            modifyIntValue(execution.result,0,1);
                                        }
                                    } else{
                                        modifyIntValue(execution.result,0,1);
                                    }}
                                    
                                    execution.arg1 = oldarg1;
                                    execution.arg2 = oldarg2;
                                    ; 
            break;
            case GOET :             
                        oldarg1 = execution.arg1;
                        if ( isPointer(execution.arg1)  != 0 ) {
                                execution.arg1 = returtIntValue(execution.arg1,1);
                        }

                        oldarg2 = execution.arg2;
                        if ( isPointer(execution.arg2)  != 0 ) {
                                execution.arg2 = returtIntValue(execution.arg2,1);
                        }
            
            
            
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                                        if(returtIntValue(execution.arg1,1) >= returtIntValue(execution.arg2,1)){
                                            modifyIntValue(execution.result,1,1);
                                        }
                                        else{
                                            modifyIntValue(execution.result,0,1);
                                        }
                                        
                                    }else{
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 2) & (returntypebyByVirtualAddress(execution.arg2) == 2) ) {
                                        if(returtfloatValue(execution.arg1,1) >= returtfloatValue(execution.arg2,1)){
                                            modifyIntValue(execution.result,1,1);
                                        }
                                        else{
                                            modifyIntValue(execution.result,0,1);
                                        }
                                    } else{
                                        modifyIntValue(execution.result,0,1);
                                    }} 
                                    
                                    execution.arg1 = oldarg1;
                                    execution.arg2 = oldarg2;
                        ;
            break;

            case ANDLOGICAL :        
            
                        oldarg1 = execution.arg1;
                        if ( isPointer(execution.arg1)  != 0 ) {
                                execution.arg1 = returtIntValue(execution.arg1,1);
                        }

                        oldarg2 = execution.arg2;
                        if ( isPointer(execution.arg2)  != 0 ) {
                                execution.arg2 = returtIntValue(execution.arg2,1);
                        }
            
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                                        if(returtIntValue(execution.arg1,1) > 0 & 0 < returtIntValue(execution.arg2,1)){
                                            modifyIntValue(execution.result,1,1);
                                        }
                                        else{
                                            modifyIntValue(execution.result,0,1);
                                        }
                                        
                                    }else{
                                        modifyIntValue(execution.result,0,1);
                                    }  
                                    
                                    
                                    execution.arg1 = oldarg1;
                                    execution.arg2 = oldarg2;
                        ;
            break;
            case ORLOGICAL :        
            
                                    oldarg1 = execution.arg1;
                                    if ( isPointer(execution.arg1)  != 0 ) {
                                            execution.arg1 = returtIntValue(execution.arg1,1);
                                    }

                                    oldarg2 = execution.arg2;
                                    if ( isPointer(execution.arg2)  != 0 ) {
                                            execution.arg2 = returtIntValue(execution.arg2,1);
                                    }
            
            
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 1) & (returntypebyByVirtualAddress(execution.arg2) == 1) ) {
                                        if(returtIntValue(execution.arg1,1) > 0 || 0 < returtIntValue(execution.arg2,1)){
                                            modifyIntValue(execution.result,1,1);
                                        }
                                        else{
                                            modifyIntValue(execution.result,0,1);
                                        }
                                        
                                    }else{
                                        modifyIntValue(execution.result,0,1);
                                    } 
                                    execution.arg1 = oldarg1;
                                    execution.arg2 = oldarg2;
                         ; 
            break;
            case READVAL :          oldresult = execution.result;
                                    if ( isPointer(execution.result)  != 0 ) {
                                            execution.result = returtIntValue(execution.result,1);
                                    }
                            if( (returntypebyByVirtualAddress(execution.result) == 1) )  {
                                int expval;
                                scanf("%d", &expval); 
                                modifyIntValue(execution.result,expval,1);
                            }
                            if( (returntypebyByVirtualAddress(execution.result) == 2) ) {
                                float expval;
                                scanf("%f", &expval); 
                                modifyFloatValue(execution.result,expval,1);
                            }
                            if( (returntypebyByVirtualAddress(execution.result) == 3) ) {
                                printf("Enter char read\n"); 
                                char expval;
                                scanf(" %c", &expval); 
                                modifyCharValue(execution.result,expval,1);
                            } ;
                            execution.result = oldresult;      
            ;
            break;
            case WRITEVAL :         oldresult = execution.result;
                                    if ( isPointer(execution.result)  != 0 ) {
                                            execution.result = returtIntValue(execution.result,1);
                                    }
            
                            if( (returntypebyByVirtualAddress(execution.result) == 1) )  {
                                int expval = returtIntValue(execution.result,1);
                                printf("%d\n", expval); 
                            }
                            if( (returntypebyByVirtualAddress(execution.result) == 2) ) {
                                float expval = returtfloatValue(execution.result,1);
                                printf("%f\n", expval); 
                            }
                            if( (returntypebyByVirtualAddress(execution.result) == 3) ) {
                                char expval = returtcharValue(execution.result,1);
                                printf("%c\n", expval); 
                            }
                            if( (returntypebyByVirtualAddress(execution.result) == 4) ) {
                                char * expval = returnStringValue(execution.result,1);
                                printf("%s\n", expval); 
                            }
                            execution.result = oldresult;
                            ;
            break;
            case RETURNVAL :        oldarg1 = execution.arg1;
                                    if ( isPointer(execution.arg1)  != 0 ) {
                                            execution.arg1 = returtIntValue(execution.arg1,1);
                                    }
            
                            if( (returntypebyByVirtualAddress(execution.arg1) == 1) )  {
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
                            }  
                            execution.arg1 = oldarg1;
                            ;
            break;
            case ENDFUNCTION : erraseLocalMemory() ; programcounter = GotoReturnStack[top-1];top--;
            break;
            case PARAM : if( (returntypebyByVirtualAddress(execution.arg1) == returntypebyByVirtualAddress(execution.result) & returntypebyByVirtualAddress(execution.result)  == 1 ) )  {
                                modifyIntValue(execution.result,returtIntValue(execution.arg1,1),3);
                            }
                            else{
                                if( (returntypebyByVirtualAddress(execution.arg1) == 2 & returntypebyByVirtualAddress(execution.result) == 2) ) {
                                    float expval = returtfloatValue(execution.arg1,1);
                                    modifyFloatValue(execution.result,expval,3);
                                }
                                else{
                                    if( (returntypebyByVirtualAddress(execution.arg1) == 3 & returntypebyByVirtualAddress(execution.arg1) == 3) ) {
                                        char expval = returtcharValue(execution.arg1,1);
                                        modifyCharValue(execution.result,expval,3);
                                    }
                                    else{
                                        printf("error of type on params on a method on execution");
                                        errorocurred = 1;
                                        }
                                }
                            }
                             ;
            break;
            case ERA :  
            //printf("enter era\n");
            sa = getProceduresDirectorybycodeinitial (execution.result);
            //printf("enter sa\n");
            pa = createLocalMemory(NULL,sa->arrayParamsTypes[0],sa->arrayParamsTypes[1],
                sa->arrayParamsTypes[2], sa->temporalsCount[0], sa->temporalsCount[1]
                , sa->temporalsCount[2], sa->temporalsCount[4]) ;
            //printf("out sa\n");
            pa->next = newLocalMemory;
            newLocalMemory = pa;
            break;
            case VER :  oldresult = execution.result;
                        if ( isPointer(execution.result)  != 0 ) {
                                execution.result = returtIntValue(execution.result,1);
                        }
                        if( execution.arg1 >= returtIntValue(execution.result,1) ) {
                        }
                        else{
                            printf("error array boundary exceeded");
                            errorocurred = 1;
                        }
                        execution.result = oldresult;
            break;

            case PENUP :  pen = 0;
            ;
            break;
            case  PENDOWN :  pen = 1;
            ;
            break;
            case LINE :  if( (returntypebyByVirtualAddress(execution.arg1) == 2 & returntypebyByVirtualAddress(execution.arg2) == 2) ) {
                            float argument1 = returtfloatValue(execution.arg1,1);
                            float argument2 = returtfloatValue(execution.arg2,1);
                            newposx = argument1;
                            newposy = argument2;
                            //printf("Error Line\n") ;
                            slow = 1000*1000;
                            displayLine ();
                        }
                                
            ;
            break;
            case CIRCLE : if( (returntypebyByVirtualAddress(execution.arg1) == 2 ) ) {
                            float argument1 = returtfloatValue(execution.arg1,1);
                            radio = argument1;
                            slow = 1000*1000;
                            displayCircle (); 
                        } 
            
            ;
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
    eliminateGlbalMemory();
    eliminateall();
    
    //glFlush();
    glutSwapBuffers();
    }
    justOneCicle = 1;
    
    printf( "End\n" ); 
    
}


/*----------------------------------------------------------------*/

%{
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "codeGeneration.h"

int errors=0;
int code_start_main=0;
int savevar_current_memory_global_local_const=0;
int current_type_var=0;
int current_type_func=0;

installConstantDirectory()
{
constantsDirectory *s;
s = CrateConstantDirectory ();
}

installConstatFloat(float val)
{constantTable * value = getConstTableByFloat(val);
if(value == NULL ){
addTypeConstantParamsProceduresDirectory (1);
addConstantTable();
addTypeConstantTable (1);
addVirtualAddressConstantTable (1);
addConstTableByFloat(val);
}

}

installConstatChar(char val)
{constantTable * value = getConstTableByChar(val);
if(value == NULL ){
addTypeConstantParamsProceduresDirectory (2);
addConstantTable();
addTypeConstantTable (2);
addVirtualAddressConstantTable (2);
addConstTableByChar(val);

}

}
installConstatInt(int val)
{
constantTable * value = getConstTableByInt(val);
if(value == NULL ){
addTypeConstantParamsProceduresDirectory (0);
addConstantTable();
addTypeConstantTable (0);
addVirtualAddressConstantTable (0);
addConstTableByInt(val);
value = getConstTableByInt(val);

}

}



installTemporalsDirectory ()
{
globalProceduresDirectory *s;
s = CrateGlobalProceduresDirectoryTemps ();
}

installGlobalVarTemps(int paramType)
{
addTemporals ();
addTypeGlobalsParamsProceduresDirectoryTemps (paramType);
addTypeGlobalVarTableTemporals (paramType);
addVirtualAddressGlobalVarTableTemporals (paramType);
}


installGlobalVar(int paramType, char *name)
{int value = getGlobalVarTable(name);
if(value == 0 ){
addTypeGlobalsParamsProceduresDirectory (paramType);
addGlobalVarTable(name);
addTypeGlobalVarTable (paramType);
addVirtualAddressGlobalVarTable (paramType);
}
else{errors++;
       printf("%s is already defined\n", name);
}
}

installLocalDirectory ( int funType, char *dir_name )
{
proceduresDirectory *s;
s = getProceduresDirectory (dir_name);
if (s == NULL){
       /*
       free(localVariablesTable);
       */
       resetVirtualAddressLocalVarTable();
       localVariablesTable = NULL;
       if(funType == 3){
              proceduresDirectory * a = putNameProceduresDirectory(dir_name);
              putTypeProceduresDirectory(funType);
       }
       else{
              proceduresDirectory * a = putNameProceduresDirectory(dir_name);
              putTypeProceduresDirectory(funType);
              installGlobalVar (funType, dir_name );
       }


}
else { errors++;
printf( "%s is already defined\n", dir_name );
}
}

putCodeInitil(int intial){
       putcodeinitialProceduresDirectory (intial);
}

installGlobalDirectory ( char *dir_name )
{
globalProceduresDirectory *s;
s = CrateGlobalProceduresDirectory (dir_name);
}




eliminateall(){

       if (globalProceduresDirectoryTable != NULL){     
              free(globalProceduresDirectoryTable->name);
              while(globalProceduresDirectoryTable->globalMemory != NULL){
                     globalVariables *ptr;
                     ptr = globalProceduresDirectoryTable->globalMemory->next;
                     free(globalProceduresDirectoryTable->globalMemory->name);
                     free(globalProceduresDirectoryTable->globalMemory);
                     globalProceduresDirectoryTable->globalMemory = ptr;
                     
              }
              free(globalProceduresDirectoryTable);
       }  
       //printf("eliminate globalProceduresDirectoryTable \n");

       /*
       free(globalVariablesTable);
       */

       while(temporalsVarTable != NULL){
              globalVariables *ptr;
              ptr = temporalsVarTable->next;
              free(temporalsVarTable->name);
              free(temporalsVarTable);
              temporalsVarTable = ptr;
       }
       //printf("eliminate temporalsVarTable \n");


       /*
       free(temporalsVarTable);
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

              while(proceduresDirectoryTable->initialParam != NULL){
                     parameters *ptr_aux;
                     ptr_aux = proceduresDirectoryTable->initialParam->next;
                     free(proceduresDirectoryTable->initialParam);
                     proceduresDirectoryTable->initialParam = ptr_aux;
              }

              free(proceduresDirectoryTable);
              proceduresDirectoryTable = ptr;
       }
       
       //printf("eliminate proceduresDirectoryTable \n");
       /*
       free(proceduresDirectoryTable);
       free(localVariablesTable);
       */


       while(constantDirectory != NULL){
              constantsDirectory *ptr;
              ptr = constantDirectory->next;
              free(constantDirectory->name);

              while(constantDirectory->constantTableMemory != NULL){
                     constantTable *ptr_aux;
                     ptr_aux = constantDirectory->constantTableMemory->next;
                     free(constantDirectory->constantTableMemory->name);
                     free(constantDirectory->constantTableMemory);
                     constantDirectory->constantTableMemory = ptr_aux;
              }

              free(constantDirectory);
              constantDirectory = ptr;
       }
       
       //printf("eliminate constantDirectory \n");

       /*
       free(constantDirectory);
       free(constantTableTable);
       */

       if (tempDirectoryTable != NULL){   
              free(tempDirectoryTable->name);
              free(tempDirectoryTable);
       }
       
       //printf("eliminate tempDirectoryTable \n");




       /********* Eliminate the dynamic memory of the code generator ***********/
       /*
       jumpStack *jumpStackActual;
       operandsStack *operandsStackActual;
       operators *operatorsActual;
       */



       while(jumpStackActual != NULL){
              jumpStack *ptr;
              ptr = jumpStackActual->next;
              free(jumpStackActual);
              jumpStackActual = ptr;
       }

       while(operandsStackActual != NULL){
              operandsStack *ptr;
              ptr = operandsStackActual->next;
              free(operandsStackActual);
              operandsStackActual = ptr;
       }

       while(operatorsActual != NULL){
              operators *ptr;
              ptr = operatorsActual->next;
              free(operatorsActual);
              operatorsActual = ptr;
       }
       /*

       printf("Eliminate the dynamic memory of the code generator\n");
       */


       /********* Eliminate the dynamic memory of the Virtual Machine ***********/
       /*
       struct stackMemValues * actualLocalMemory;
       struct stackMemValues * newLocalMemory;
       struct memValues * globalMemory;
       struct memValues * tempMemory;
       struct parameters * paramsActual;

       stackMemValues *pa;
       proceduresDirectory * sa;

       */
       
       while(actualLocalMemory != NULL){
              stackMemValues *ptr;
              ptr = actualLocalMemory->next;
              free(actualLocalMemory->memoryVar->structintergers);
              free(actualLocalMemory->memoryVar->structfloats);
              free(actualLocalMemory->memoryVar->structchars);
              free(actualLocalMemory->memoryVar);
              free(actualLocalMemory);
              actualLocalMemory = ptr;
       }

       while(newLocalMemory != NULL){
              stackMemValues *ptr;
              ptr = newLocalMemory->next;
              free(newLocalMemory->memoryVar->structintergers);
              free(newLocalMemory->memoryVar->structfloats);
              free(newLocalMemory->memoryVar->structchars);
              free(newLocalMemory->memoryVar);
              free(newLocalMemory);
              newLocalMemory = ptr;
       }

       /*
       printf("Eliminate newLocalMemory\n");
       */

       if (globalMemory != NULL){ 
              free(globalMemory->structintergers);
              free(globalMemory->structfloats);
              free(globalMemory->structchars);
              free(globalMemory);
       }


       if (tempMemory != NULL){ 
              free(tempMemory->structintergers);
              free(tempMemory->structfloats);
              free(tempMemory->structchars);
              free(tempMemory);
       }

       while(paramsActual != NULL){
              parameters *ptr;
              ptr = paramsActual->next;
              free(paramsActual);
              paramsActual = ptr;
       }

       /*
       printf("Eliminate the dynamic memory of the Virtual Machine\n");
       */
       


}


installLocalVar(int paramType, char *name, int variables_parameters){
       int value = getLocalVarTableOnlylocal(name);
       if(value == 0 ){
              addTypeParamsProceduresDirectory ( paramType);
              addLocalVarTable(name);
              addTypeLocalVarTable (paramType);
              addVirtualAddressLocalVarTable (paramType);
              if(variables_parameters == 2){
                     addTypeParamsTableProceduresDirectory ( paramType);
              }
       }
       else{
              errors++;
              printf("Error: Variable defined\n");
       }
}









%}
%union  /* The Semantic Records */
{
int intval; /* Integer values  */
float varfloat;
char *varchar;
char *id; /* Identifiers */
char *varstring;
int typeid;
int virtualMemory;
};
%token <id> IDENTIFIER 
%token <intval> NUMBERINTEGER
%token <varchar> LETTERCHAR 
%token <varstring> WORDSTRING
%token <varfloat> NUMBERFLOAT
%type <typeid> type definitiontypefunctionssecondpart definitiontypefunctionsthirdpart


%type <virtualMemory> expression retornoffunction

%token PROGRAM PROGRAMNAME SEMICOLON GREATERTHAN SMALLERTHAN EQUALITY NOTEQUALITY EQUAL UNITARYMINUS
%token LESSTHANOREQUAL GREATERTHANOREQUAL MAIN RIGHTCURLYBRACKET VOID 
%token LEFTCURLYBRACKET RIGHTSQUAREBRACKET LEFTSQUAREBRACKET RIGHTPARENTHESIS 
%token LEFTPARENTHESIS VAR GLOVALVAR COLON MODULE INTEGER FLOAT CHARAC COMMA MODULENAME THEN
%token RETURNN READ WRITE IF ELSE DO WHILE FOR TO COMPARISON STRING AND OR SIGN 




 /* %left ',' */

%left '|'
%left '&'
%left EQUALITY NOTEQUALITY
%left '<' '>' LESSTHANOREQUAL GREATERTHANOREQUAL
%left '-' '+'
%left '*' '/'
%nonassoc '('

%start initialprogram 
%%





initialprogram : PROGRAM {init_Semantic_Cube();code_offset=0; errors = 0; 
                         generate_code( 0, -1, -1, -1 ); code_start_main = 0; 
                         installConstantDirectory();installTemporalsDirectory();} 
                     IDENTIFIER {savevar_current_memory_global_local_const = 1; 
                                   installGlobalDirectory($3);} 
                     ';' variables secondpartprogram   {generate_code(24,-1,-1,-1); 
                                                        printf("%s", "final"); YYACCEPT;}
                ;

                
secondpartprogram : declarationoffunctions {savevar_current_memory_global_local_const = 1;
                                            } 
                            thirdpartprogram 
                  ;

thirdpartprogram : MAIN {modify_code_at_given_cuad_num_result(code_offset, 0);}'(' ')' 
                     '{' statutes '}'
                ;


/* Global variables*/
variables : VAR 
           '{' variablessecondpart '}'
          |
           ;

variablessecondpart : type { current_type_var = $1; } ':' list_ids ';'  
                    | variablessecondpart type { current_type_var = $2; } ':' list_ids ';' 
                     ;


/**/

type : INTEGER { $$ = 0;}
     | FLOAT   { $$ = 1;}
     | CHARAC    { $$ = 2;}
     ;

list_ids : IDENTIFIER { if(savevar_current_memory_global_local_const == 1){
                            
                            installGlobalVar(current_type_var, $1);
                        }
                        if(savevar_current_memory_global_local_const == 2){
                            
                            installLocalVar(current_type_var, $1,1);
                        } }
         |list_ids ',' IDENTIFIER { if(savevar_current_memory_global_local_const == 1){
                            installGlobalVar(current_type_var, $3);
                        }
                        if(savevar_current_memory_global_local_const == 2){
                            installLocalVar(current_type_var, $3,1);
                        } } 
                     
         ;


/* declaration of functions */
declarationoffunctions : auxdeclarationoffunctions 
                       | declarationoffunctions auxdeclarationoffunctions 
                       |
                       ;

auxdeclarationoffunctions : definitionvoidfunctions {generate_code(20,-1,-1,-1); }
                          | definitiontypefunctions {generate_code(20,-1,-1,-1);}
                          ;



/* definition of void funcions */
definitionvoidfunctions : VOID MODULE IDENTIFIER 
                     {current_type_func = 3;
                     installLocalDirectory(current_type_func,$3);
                     putCodeInitil(code_offset); 
                     savevar_current_memory_global_local_const = 2;
                     current_type_func = 0;} 
                     '(' parametersaux ')' definitionvoidfunctionssecondpart 
                         ;

definitionvoidfunctionssecondpart : ';' '{' variables definitionvoidfunctionsthirdpart
                                 ;

definitionvoidfunctionsthirdpart : statutes '}'
                                | '}'
                                ;


/* definition of type funcions */

definitiontypefunctions : type MODULE IDENTIFIER 
              {current_type_func = $1; 
              installLocalDirectory($1,$3);
              putCodeInitil(code_offset);
              savevar_current_memory_global_local_const = 2;
              current_type_func = $1;
              }
                        '(' parametersaux ')' definitiontypefunctionssecondpart {generate_code(19, $8 , -1, globalVariablesTable->virtualAddress);}
                        ;

definitiontypefunctionssecondpart : ';' '{' variables definitiontypefunctionsthirdpart {$$ = $4;}
                                 ;


definitiontypefunctionsthirdpart : statutes retornoffunction '}' {$$ = $2;}
                                ;


retornoffunction : RETURNN '(' expression ')' ';' {$$ = $3;}
                 ;

/* parameters */
parametersaux : parameters
              |
              ;

parameters : type {current_type_var = $1;} ':' IDENTIFIER {installLocalVar(current_type_var,$4,2);}
           | parameters ','  type {current_type_var = $3;} ':' IDENTIFIER {installLocalVar(current_type_var,$6,2);} 
           ;


statutes : auxstatutes
          | statutes auxstatutes 
          |
          ;

auxstatutes : assignment
             | callvoidmodule
             | toread
             | towrite
             | statuteofdecision
             | statuteofloop
             ;

assignment : IDENTIFIER  '=' expression ';' {
              if (getLocalVarTable($1) == 0){
                            printf("Var no defined\n"); errors++;
              }
              else{ 
                     if(savevar_current_memory_global_local_const == 2){
                            if (returntypebyByVirtualAddress($3) == returntypebyByVirtualAddress(getLocalVarTable($1))) { 
                                   generate_code(9,$3,-1,getLocalVarTable($1));
                            }
                            else{
                                   printf(" Type missmathc\n");errors++;
                            }
                     }
                     else {
                            if(savevar_current_memory_global_local_const == 1){
                                   if (returntypebyByVirtualAddress($3) == returntypebyByVirtualAddress(getGlobalVarTable($1))) { 
                                          generate_code(9,$3,-1,getGlobalVarTable($1));
                                   }
                                   else{
                                          printf("Type missmathc\n");errors++;
                                   }  
                            }
                     }
              }            
       }
           ;

callvoidmodule : IDENTIFIER {proceduresDirectory *ptr = getProceduresDirectory($1);
                            //printf("Enter call to void function \n");
                        if(ptr == NULL){
                               errors++;
                               printf("Error Module does not exist \n");
                        }
                        else{
                               if(ptr->type != 3){
                                   errors++;
                                   printf("Error Module is not a void funcion \n");
                               }
                               else{

                                //printf("Enter call to void function - funcions exist\n");
                                   generate_code(22, -1, -1,
                                          getcodeinitialProceduresDirectory($1) );

                                   parametersStack *auxPointer = (parametersStack *)0;
                                   auxPointer = (parametersStack *) malloc (sizeof(parametersStack)+1);
                                   auxPointer->actualParam = ptr->initialParam;

                                   if(parametersStackTable == NULL ){
                                           //printf("Enter call to void function - else - pst is null \n");
                                          parametersStackTable =  auxPointer;
                                   }
                                   else{
                                        //printf("Enter call to void function - else - pst is not null \n");

                                          auxPointer->next = parametersStackTable;
                                          parametersStackTable = auxPointer;
                                   }
                               }
                        }
                     } 
              '(' auxParam ')' ';' { if(parametersStackTable != NULL){
                                //printf("Enter out params void function - pst is not null \n");
                                   if(parametersStackTable->actualParam != NULL){
                                          errors++;
                                          printf("Error No arrived to last parameter \n");
                                      }
                                      else{
                                          //printf("Enter out params void function - pst is not null - pst->ap is null\n");
                                          proceduresDirectory *ptr = getProceduresDirectory($1);
                                          generate_code(3, -1, -1,
                                                 ptr->codeinitial);
                                          parametersStackTable = parametersStackTable->next;
                                          //printf("Enter out params void function - pst is not null -  out\n");
                                      }
                                   }
                            }
               ;


toread : READ '(' auxtoread ')' ';'
       ;

auxtoread : IDENTIFIER 
          | auxtoread ',' IDENTIFIER 
          ;


towrite : WRITE '(' auxtowrite ')' ';'
       ;


/*  SIGN miss  */
auxtowrite : expression  { generate_code(18, -1, -1, $1);}
           |auxtowrite ',' expression   { generate_code(18, -1, -1, $3);}
           ;

statuteofdecision : IF '(' expression ')' THEN '{' statutes '}' statuteofdecisionsecondpart
                  ;

statuteofdecisionsecondpart : ELSE '{' statutes '}'
                            |  /*empty*/
                            ;

statuteofloop : conditional
              | noconditional
              ; 

conditional : DO '{' statutes '}' WHILE '(' expression ')' ';'
            ;
            
noconditional : FOR IDENTIFIER '=' expression TO expression DO '{' statutes '}'
              ;





expression : NUMBERINTEGER {installConstatInt($1); 
              constantTable * value = getConstTableByInt($1); 
              $$ = value->virtualAddress;}
           | LETTERCHAR {installConstatChar($1[1]); 
              constantTable * value = getConstTableByChar($1[1]); 
              $$ = value->virtualAddress;}
           | IDENTIFIER {   if (getLocalVarTable($1) == 0){
                                   printf("Identifier no defined : %s \n", $1); errors++;
                            }
                            else{
                                   if(savevar_current_memory_global_local_const == 1){
                                                 $$ = getGlobalVarTable($1);
                                   }
                                   else {
                                          if(savevar_current_memory_global_local_const == 2){
                                                 $$ = getLocalVarTableOnlylocal($1);
                                           }
                                           else{
                                                  printf("Identifier no defined : %s \n",
                                                        $1); 
                                                 errors++;
                                           }
                                   }
                            }
                        }
           | NUMBERFLOAT {installConstatFloat($1); 
              constantTable * value = getConstTableByFloat($1); 
              $$ = value->virtualAddress;}
           | expression '<' expression{
                            int type_exp = semanticCube[4]
                                   [returntypebyByVirtualAddress($1)-1]
                                   [returntypebyByVirtualAddress($3)-1];
                            if(type_exp == 9 ){
                                   printf("Error type expression");
                                   errors++;
                            }{
                                  installGlobalVarTemps(type_exp);
                                   generate_code(11,$1,$3,
                                          temporalsVarTable->virtualAddress);
                                   $$ = temporalsVarTable->virtualAddress; 
                            }}
           | expression EQUALITY expression{
                            int type_exp = semanticCube[0]
                                   [returntypebyByVirtualAddress($1)-1]
                                   [returntypebyByVirtualAddress($3)-1];
                            if(type_exp == 9 ){
                                   printf("Error type expression");
                                   errors++;
                            }{
                                  installGlobalVarTemps(type_exp);
                                   generate_code(10,$1,$3,
                                          temporalsVarTable->virtualAddress);
                                   $$ = temporalsVarTable->virtualAddress;
                            }}
           | expression NOTEQUALITY expression{
                            int type_exp = semanticCube[1]
                                   [returntypebyByVirtualAddress($1)-1]
                                   [returntypebyByVirtualAddress($3)-1];
                            if(type_exp == 9 ){
                                   printf("Error type expression");
                                   errors++;
                            }{
                                  installGlobalVarTemps(type_exp);
                                   generate_code(25,$1,$3,
                                          temporalsVarTable->virtualAddress);
                                   $$ = temporalsVarTable->virtualAddress;
                            }}
           | expression '>' expression {
                            int type_exp = semanticCube[5]
                                   [returntypebyByVirtualAddress($1)-1]
                                   [returntypebyByVirtualAddress($3)-1];
                            if(type_exp == 9 ){
                                   printf("Error type expression");
                                   errors++;
                            }{
                                  installGlobalVarTemps(type_exp);
                                   generate_code(12,$1,$3,
                                          temporalsVarTable->virtualAddress);
                                   $$ = temporalsVarTable->virtualAddress; 
                            }}
           | expression GREATERTHANOREQUAL expression {
                            int type_exp = semanticCube[3]
                                   [returntypebyByVirtualAddress($1)-1]
                                   [returntypebyByVirtualAddress($3)-1];
                            if(type_exp == 9 ){
                                   printf("Error type expression");
                                   errors++;
                            }{
                                  installGlobalVarTemps(type_exp);
                                   generate_code(14,$1,$3,
                                          temporalsVarTable->virtualAddress);
                                   $$ = temporalsVarTable->virtualAddress; 
                            }}
           | expression LESSTHANOREQUAL expression {
                            int type_exp = semanticCube[2]
                                   [returntypebyByVirtualAddress($1)-1]
                                   [returntypebyByVirtualAddress($3)-1];
                            if(type_exp == 9 ){
                                   printf("Error type expression");
                                   errors++;
                            }{
                                  installGlobalVarTemps(type_exp);
                                   generate_code(13,$1,$3,
                                          temporalsVarTable->virtualAddress);
                                   $$ = temporalsVarTable->virtualAddress; 
                            }}



           | expression '+' expression 
                            {
                            
                            int type_exp = semanticCube[9]
                                   [returntypebyByVirtualAddress($1)-1]
                                   [returntypebyByVirtualAddress($3)-1];
                            
                            if(type_exp == 9 ){
                                   printf("Error type expression");
                                   errors++;
                            }
                            {
                                  installGlobalVarTemps(type_exp);
                                   generate_code(7,$1,$3,
                                          temporalsVarTable->virtualAddress);
                                   $$ = temporalsVarTable->virtualAddress;
                             
                            }
                            
                            }



                            
           | expression '-' expression {
                            int type_exp = semanticCube[8]
                                   [returntypebyByVirtualAddress($1)-1]
                                   [returntypebyByVirtualAddress($3)-1];
                            if(type_exp == 9 ){
                                   printf("Error type expression");
                                   errors++;
                            }{
                                  installGlobalVarTemps(type_exp);
                                   generate_code(8,$1,$3,
                                          temporalsVarTable->virtualAddress);
                                   $$ = temporalsVarTable->virtualAddress; 
                            }}

           | expression '*' expression {
                            int type_exp = semanticCube[10]
                                   [returntypebyByVirtualAddress($1)-1]
                                   [returntypebyByVirtualAddress($3)-1];
                            if(type_exp == 9 ){
                                   printf("Error type expression");
                                   printf("%d Error type expression", type_exp);
                                   printf("%d Error type expression", 
                                          returntypebyByVirtualAddress($1));
                                   errors++;
                            }{
                                   installGlobalVarTemps(type_exp);
                                   generate_code(5,$1,$3,
                                          temporalsVarTable->virtualAddress);
                                   $$ = temporalsVarTable->virtualAddress; 
                            }}

           | expression '/' expression {
                            int type_exp = semanticCube[11]
                                   [returntypebyByVirtualAddress($1)-1]
                                   [returntypebyByVirtualAddress($3)-1];
                            if(type_exp == 9 ){
                                   printf("Error type expression");
                                   errors++;
                            }{
                                  installGlobalVarTemps(type_exp);
                                   generate_code(6,$1,$3,
                                          temporalsVarTable->virtualAddress);
                                   $$ = temporalsVarTable->virtualAddress; 
                            }}

           | expression '&' expression {
                            int type_exp = semanticCube[8]
                                   [returntypebyByVirtualAddress($1)-1]
                                   [returntypebyByVirtualAddress($3)-1];
                            if(type_exp == 9 ){
                                   printf("Error type expression");
                                   errors++;
                            }{
                                   installGlobalVarTemps(type_exp);
                                   generate_code(15,$1,$3,
                                          temporalsVarTable->virtualAddress);
                                   $$ = temporalsVarTable->virtualAddress; 
                            }}
           | expression '|' expression {
                            int type_exp = semanticCube[7]
                                   [returntypebyByVirtualAddress($1)-1]
                                   [returntypebyByVirtualAddress($3)-1];
                            if(type_exp == 9 ){
                                   printf("Error type expression");
                                   errors++;
                            }{
                                  installGlobalVarTemps(type_exp);
                                   generate_code(16,$1,$3,
                                          temporalsVarTable->virtualAddress);
                                   $$ = temporalsVarTable->virtualAddress; 
                            }}
           /* 
           | '(' expression ')' expression {
                            int type_exp = semanticCube[10]
                                   [returntypebyByVirtualAddress($2)-1]
                                   [returntypebyByVirtualAddress($4)-1];
                            if(type_exp == 9 ){
                                   printf("Error type expression");
                                   errors++;
                            }{
                                   installGlobalVarTemps(type_exp);
                                   generate_code(5,$2,$4,
                                          temporalsVarTable->virtualAddress);
                                   $$ = temporalsVarTable->virtualAddress; 
                            }}
           | expression '(' expression ')' {
                            int type_exp = semanticCube[10]
                                   [returntypebyByVirtualAddress($1)-1]
                                   [returntypebyByVirtualAddress($3)-1];
                            if(type_exp == 9 ){
                                   printf("Error type expression");
                                   errors++;
                            }{
                                   installGlobalVarTemps(type_exp);
                                   generate_code(5,$1,$3,
                                          temporalsVarTable->virtualAddress);
                                   $$ = temporalsVarTable->virtualAddress; 
                            }}
       
           */
           | '(' expression ')' {$$ = $2;}



           | IDENTIFIER {proceduresDirectory *ptr = getProceduresDirectory($1);
                            //printf("Enter call to function \n");
                        if(ptr == NULL){
                               errors++;
                               printf("Error Module does not exist \n");
                        }
                        else{
                               if(ptr->type == 3){
                                   errors++;
                                   printf("Error Module is not a type funcion \n");
                               }
                               else{
                                //printf("Enter call to function - funcions exist\n");
                                   generate_code(22, -1, -1,
                                          getcodeinitialProceduresDirectory($1) );
                                  
                                   parametersStack *auxPointer = (parametersStack *)0;
                                   auxPointer = (parametersStack *) malloc (sizeof(parametersStack)+1);
                                   auxPointer->actualParam = ptr->initialParam;

                                   if(parametersStackTable == NULL ){
                                           //printf("Enter call to function - else - pst is null \n");
                                          parametersStackTable =  auxPointer;
                                          //printf("Enter call to function - else - pst is null out\n");
                                   }
                                   else{
                                        //printf("Enter call to function - else - pst is not null \n");

                                          auxPointer->next = parametersStackTable;
                                          parametersStackTable = auxPointer;
                                          printf("Enter call to function - else - pst is not null  out\n");
                                   }
                               }
                        }
                     } 
              '(' auxParam ')' { if(parametersStackTable != NULL){
                               // printf("Enter out params  function - pst is not null \n");
                                   if(parametersStackTable->actualParam != NULL){
                                          errors++;
                                          printf("Error No arrived to last parameter \n");
                                      }
                                      else{
                                        //  printf("Enter out params  function - pst is not null - pst->ap is null\n");
                                          proceduresDirectory *ptr = getProceduresDirectory($1);
                                          generate_code(3, -1, -1,
                                                 ptr->codeinitial);
                                          parametersStackTable = parametersStackTable->next;
                                        //  printf("Enter out params  function - pst is not null -  out\n");
                                          $$ = getGlobalVarTable($1);
                                      }
                                   }
                            }
 
           ;
           
auxParam      :      auxexpression
              |      /*empty*/
              ;

auxexpression : expression {if(parametersStackTable->actualParam != NULL){
                            //printf("Enter call to auxexpression - pst->ap is not null \n");
                            if(returntypebyByVirtualAddress($1)-1 == 
                                          parametersStackTable->actualParam->type ){
                                   //printf("Enter call to auxexpression - pst->ap is not null - same type \n");
                                   generate_code(21, $1, -1,
                                        parametersStackTable->actualParam->virtualAddress);
                                   parametersStackTable->actualParam = 
                                                 parametersStackTable->actualParam->next;
                            }
                            else{
                                   errors++;
                                   printf("Error Different type in a parameter \n");
                            } 
                            }
                            else{
                                   errors;
                                   printf("Error Maximun number of parameters arrived \n");
                            }
                            }
              | auxexpression ','  expression
                            {if(parametersStackTable->actualParam != NULL){
                            //printf("Enter call to auxexpression , expression - pst->ap is not null \n");
                            if(returntypebyByVirtualAddress($3)-1 == 
                                          parametersStackTable->actualParam->type ){
                                   //printf("Enter call to auxexpression , expression - pst->ap is not null - same type \n");
                                   generate_code(21, $3, -1,
                                        parametersStackTable->actualParam->virtualAddress);
                                   parametersStackTable->actualParam = 
                                                 parametersStackTable->actualParam->next;
                            }
                            else{
                                   errors++;
                                   printf("Error Different type in a parameter \n");
                            } 
                            }
                            else{
                                   errors;
                                   printf("Error Maximun number of parameters arrived \n");
                            }
                            }
              ;




%%
main( int argc, char *argv[] )
{ extern FILE *yyin;
++argv; --argc;
yyin = fopen( argv[0], "r" );
/*yydebug = 1;*/
errors = 0;
yyparse ();
printf ( "Parse Completed\n" );
if ( errors == 0 )
{ 

print_code ();

execute_the_code_cycle();
eliminateall();

}
else{
       print_code ();

       eliminateall();
}
}


yyerror ( char *s ) /* Called by yyparse on error */
{
errors++;
printf ("%s\n", s);
}
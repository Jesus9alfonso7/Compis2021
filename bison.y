%{
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<GL/glut.h>

#include "codeGeneration.h"


int code_start_main=0;
int savevar_current_memory_global_local_const=0;
int current_type_var=0;
int current_type_func=0;
int auxJump = 0;
int returnJump = 0;


void installConstantDirectory()
{
       constantsDirectory *s;
       s = CrateConstantDirectory ();
}



void installConstatInt(int val)
{
       constantIntVars * value = getConstTableByInt(val);
       if(value == NULL ){
              addTypeConstantParamsProceduresDirectory (0);
              addConstantTable(0);
              addConstTableByInt(val);
       }
}
void installConstatFloat(float val)
{
       constantFloatVars * value = getConstTableByFloat(val);
       if(value == NULL ){
              addTypeConstantParamsProceduresDirectory (1);
              addConstantTable(1);
              addConstTableByFloat(val);
       }
}
void installConstatChar(char val)
{
       constantCharVars * value = getConstTableByChar(val);
       if(value == NULL ){
              addTypeConstantParamsProceduresDirectory (2);
              addConstantTable(2);
              addConstTableByChar(val);
       }
}
void installConstatString(char * val)
{
       constantStringVars * value = getConstTableByString(val);
       if(value == NULL ){
              addTypeConstantParamsProceduresDirectory (3);
              addConstantTable(3);
              addConstTableByString(val);
       }
}





void installGlobalTemps(int paramType)
{      
       addGlobalTemporals (paramType);
       addGlobalTemporalsCount (globalProceduresDirectoryTable, paramType);
}

void installLocalTemps(int paramType)
{
       addLocalTemporals (paramType);
       addLocalTemporalsCount (proceduresDirectoryTable, paramType);
}


void installGlobalVar(int paramType, char *name)
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

void installLocalDirectory ( int funType, char *dir_name )
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

void putCodeInitil(int intial){
       putcodeinitialProceduresDirectory (intial);
}

void installGlobalDirectory ( char *dir_name )
{
globalProceduresDirectory *s;
s = CrateGlobalProceduresDirectory (dir_name);
}





void installLocalVar(int paramType, char *name, int variables_parameters){
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


%type <virtualMemory> expression retornoffunction arrayid

%token PROGRAM PROGRAMNAME SEMICOLON GREATERTHAN SMALLERTHAN EQUALITY NOTEQUALITY EQUAL UNITARYMINUS
%token LESSTHANOREQUAL GREATERTHANOREQUAL MAIN RIGHTCURLYBRACKET VOID 
%token LEFTCURLYBRACKET RIGHTSQUAREBRACKET LEFTSQUAREBRACKET RIGHTPARENTHESIS 
%token LEFTPARENTHESIS VAR GLOVALVAR COLON MODULE INTEGER FLOAT CHARAC COMMA MODULENAME THEN
%token RETURNN READ WRITE IF ELSE DO WHILE FOR TO COMPARISON STRING AND OR SIGN 
%token SFPENUP SFPENDOWN SFDRAWLINE SFDRAWCIRCLE SPECIAL



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
                         installConstantDirectory();
                         /*
                         installTemporalsDirectory();
                         */
                         } 
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
variables : VAR  '{' variablessecondpart '}'
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
                            globalVariablesTable->dimArray = -1;
                        }
                        if(savevar_current_memory_global_local_const == 2){
                            installLocalVar(current_type_var, $1,1);
                            localVariablesTable->dimArray = -1;
                        } }
         |list_ids ',' IDENTIFIER { if(savevar_current_memory_global_local_const == 1){
                            installGlobalVar(current_type_var, $3);
                            globalVariablesTable->dimArray = -1;
                        }
                        if(savevar_current_memory_global_local_const == 2){
                            installLocalVar(current_type_var, $3,1);
                            localVariablesTable->dimArray = -1;
                        } } 
       | vardim
       | list_ids ',' vardim
       ;

vardim : IDENTIFIER '[' NUMBERINTEGER ']' {
              if ($3 < 0){
                     printf("Error : Array declaration : Dimension can not be negative\n");
                     errors++;
              }
              else { installConstatInt($3); 
                     constantIntVars * value = getConstTableByInt($3);

                     if(savevar_current_memory_global_local_const == 1){
                            installGlobalVar(current_type_var, $1);
                            globalVariablesTable->dimArray = $3;
                            globalvirtualaddresscount[current_type_var] = globalvirtualaddresscount[current_type_var] + $3;
                        }
                     if(savevar_current_memory_global_local_const == 2){
                            installLocalVar(current_type_var, $1,1);
                            localVariablesTable->dimArray = $3;
                            localvirtualaddresscount[current_type_var] = localvirtualaddresscount[current_type_var] + $3;
                     }

                     /*
                     printf("%d : INTEGER \n", $1 );
                     */
                      
             } 
             }                     
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
definitionvoidfunctions : VOID IDENTIFIER 
                     {current_type_func = 3;
                     installLocalDirectory(current_type_func,$2);
                     putCodeInitil(code_offset); 
                     savevar_current_memory_global_local_const = 2;
                     current_type_func = 0;} 
                     '(' parametersaux ')' definitionvoidfunctionssecondpart 
                         ;

definitionvoidfunctionssecondpart :  '{' variables definitionvoidfunctionsthirdpart
                                 ;

definitionvoidfunctionsthirdpart : statutes '}'
                                | '}'
                                ;


/* definition of type funcions */

definitiontypefunctions : type IDENTIFIER 
              {current_type_func = $1; 
              installLocalDirectory($1,$2);
              putCodeInitil(code_offset);
              savevar_current_memory_global_local_const = 2;
              current_type_func = $1;
              }
                        '(' parametersaux ')' definitiontypefunctionssecondpart {generate_code(19, $7 , -1, 
                                                                                    globalVariablesTable->virtualAddress);}
                        ;

definitiontypefunctionssecondpart :  '{' variables definitiontypefunctionsthirdpart {$$ = $3;}
                                 ;


definitiontypefunctionsthirdpart : statutes retornoffunction '}' {$$ = $2;}
                                ;


retornoffunction : RETURNN '(' expression ')' ';' {$$ = $3;}
                 ;

/* parameters */
parametersaux : parameters
              |
              ;

parameters : type {current_type_var = $1;} ':' IDENTIFIER {installLocalVar(current_type_var,$4,2);
                                                               localVariablesTable->dimArray = -1;}
           | parameters ','  type {current_type_var = $3;} ':' IDENTIFIER {installLocalVar(current_type_var,$6,2);
                                                                             localVariablesTable->dimArray = -1;} 
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
             | espenup
             | espendown
             | esdrawline
             | esdrawcircle
             ;

espenup : SPECIAL SFPENUP '(' ')' ';' {
                            generate_code(28,-1,-1,-1);
}

espendown : SPECIAL SFPENDOWN '(' ')' ';' {
                            generate_code(29,-1,-1,-1);
}

esdrawline : SPECIAL SFDRAWLINE '(' expression ',' expression ')' ';' {
                            generate_code(30, $4, $6,-1);
}
esdrawcircle : SPECIAL SFDRAWCIRCLE '(' expression ')' ';' {
                            generate_code(31, $4, -1,-1);
}

assignment : IDENTIFIER  '=' expression ';' {
              if (getLocalVarTable($1) == 0){
                            printf("Var no defined\n"); errors++;
              }
              else{ 
                     if(savevar_current_memory_global_local_const == 2){
                            if(isArrayGlobalVar($1) >= 0){
                                   printf("Error Variable is an array : %s \n", $1); 
                                   errors++;
                            }
                            else{
                                   if (returntypebyByVirtualAddress($3) == returntypebyByVirtualAddress(getLocalVarTable($1))) { 
                                          generate_code(9,$3,-1,getLocalVarTable($1));
                                   }
                                   else{
                                          printf(" Type missmathc\n");errors++;
                                   }
                            }
                     }
                     else {
                            if(savevar_current_memory_global_local_const == 1){
                                   if(isArrayLocalVar($1) >= 0){
                                          printf("Error Variable is an array : %s \n", $1); 
                                          errors++;
                                   }
                                   else{
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
       }
       | arrayid '=' expression ';' {
              
              
                     if(savevar_current_memory_global_local_const == 2){

                                   if (returntypebyByVirtualAddress($3) == isPointer( $1 ) ) { 
                                          generate_code(9,$3,-1,$1 );
                                   }
                                   else{
                                          printf(" Type missmathc\n");errors++;
                                   }
                            
                     }
                     else {
                            if(savevar_current_memory_global_local_const == 1){

                                          if (returntypebyByVirtualAddress($3) == isPointer( $1 ) ) { 
                                                 generate_code(9,$3,-1,$1 );
                                          }
                                          else{
                                                 printf("Type missmathc\n");errors++;
                                          } 
                                   
                            }
                     }           
       }
           ;


arrayid : IDENTIFIER '[' expression ']' {
                  
                            if (getLocalVarTable($1) == 0){
                                   printf("Identifier no defined : %s \n", $1); errors++;
                            }
                            else{
                                   
                                   
                                   if( isPointer($3) == 0){

                                          
                                          if(savevar_current_memory_global_local_const == 1){
                                                        if(isArrayGlobalVar($1) < 0){
                                                               printf("Variable is not an array : %s \n", $1); 
                                                               errors++;
                                                        }
                                                        else{  installConstatInt(getGlobalVarTable($1));
                                                               constantIntVars * value = getConstTableByInt(getGlobalVarTable($1));
                                                               
                                                               if(returntypebyByVirtualAddress( $3 )  == 1){
                                                                      installGlobalTemps( returntypebyByVirtualAddress( getGlobalVarTable($1) ) + 3);
                                                                      generate_code(23,isArrayGlobalVar($1),-1, $3);
                                                                      generate_code(7,value->virtualAddress,$3, lastGlobalTemporal->virtualAddress);
                                                                      $$ = lastGlobalTemporal->virtualAddress;
                                                               }
                                                               else{
                                                                      printf("Expression is not int, array access : %s \n", $1); 
                                                                             errors++;
                                                               }
                                                        }
                                          }
                                          else {
                                                 if(savevar_current_memory_global_local_const == 2){


                                                        if(isArrayLocalVar($1) < 0){
                                                               printf("Variable is not an array : %s \n", $1); 
                                                               errors++;
                                                        }
                                                        else{  installConstatInt(getGlobalVarTable($1));
                                                               constantIntVars * value = getConstTableByInt(getGlobalVarTable($1));
                                                               if(returntypebyByVirtualAddress( $3 )  == 1){
                                                                      installGlobalTemps( returntypebyByVirtualAddress( getLocalVarTable($1) ) + 3);
                                                                      generate_code(23,isArrayLocalVar($1),-1, $3);
                                                                      generate_code(7,value->virtualAddress,$3, lastLocalTemporal->virtualAddress);
                                                                      $$ = lastLocalTemporal->virtualAddress;
                                                               }
                                                               else{
                                                                      printf("Expression is not int, array access : %d \n", $3); 
                                                                             errors++;
                                                               }
                                                        }



                                                 }
                                                 else{
                                                        printf("Identifier no defined : %s \n",
                                                               $1); 
                                                        errors++;
                                                 }
                                          }

                                   }
                                   else{
                                          if( isPointer($3) == 1){
                                                 if(savevar_current_memory_global_local_const == 1){
                                                        if(isArrayGlobalVar($1) < 0){
                                                               printf("Variable is not an array : %s \n", $1); 
                                                               errors++;
                                                        }
                                                        else{  installConstatInt(getGlobalVarTable($1));
                                                               constantIntVars * value = getConstTableByInt(getGlobalVarTable($1));
                                                               //if(returntypebyByVirtualAddress( $3 )  == 1){
                                                                      installGlobalTemps( returntypebyByVirtualAddress( getGlobalVarTable($1) ) + 3);
                                                                      generate_code(23,isArrayGlobalVar($1),-1, $3);
                                                                      generate_code(7,value->virtualAddress,$3, lastGlobalTemporal->virtualAddress);
                                                                      $$ = lastGlobalTemporal->virtualAddress;
                                                               /*}
                                                               else{
                                                                      printf("Expression is not int, array access : %s \n", $1); 
                                                                             errors++;
                                                               }*/
                                                        }
                                                 }
                                                 else {
                                                        if(savevar_current_memory_global_local_const == 2){


                                                               if(isArrayLocalVar($1) < 0){
                                                                      printf("Variable is not an array : %s \n", $1); 
                                                                      errors++;
                                                               }
                                                               else{  installConstatInt(getGlobalVarTable($1));
                                                                      constantIntVars * value = getConstTableByInt(getGlobalVarTable($1));
                                                                      //if(returntypebyByVirtualAddress( $3 )  == 1){
                                                                             installGlobalTemps( returntypebyByVirtualAddress( getLocalVarTable($1) ) + 3);
                                                                             generate_code(23,isArrayLocalVar($1),-1, $3);
                                                                             generate_code(7,value->virtualAddress,$3, lastLocalTemporal->virtualAddress);
                                                                             $$ = lastLocalTemporal->virtualAddress;
                                                                      /*}
                                                                      else{
                                                                             printf("Expression is not int, array access : %s \n", $3); 
                                                                                    errors++;
                                                                      }*/
                                                               }

                                                        }

                                                 }

                                          }
                                          else{
                                                 printf("Expression is not int in array access : %d \n", $3); 
                                                 errors++;
                                          }


                                   
                                   
                                   
                                   }




                            }
                  
           }

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

auxtoread : IDENTIFIER { 
                     if (getLocalVarTable($1) == 0){
                                   printf("Identifier no defined : %s \n", $1); errors++;
                     }
                     else{
                            if(savevar_current_memory_global_local_const == 1){
                                   if(isArrayGlobalVar($1) >= 0){
                                          printf("Variable is an array : %s \n", $1); 
                                          errors++;
                                   }
                                   else{
                                          generate_code(17, -1, -1, getGlobalVarTable($1));
                                   }
                            }
                            else {
                                   if(savevar_current_memory_global_local_const == 2){
                                          if(isArrayLocalVar($1) >= 0){
                                                 printf("Variable is an array : %s \n", $1); 
                                                 errors++;
                                          }
                                          else{
                                                 generate_code(17, -1, -1, getLocalVarTable($1));
                                          }
                                   }
                            }
                     }
              }
          | auxtoread ',' IDENTIFIER 
                     { 
                     if (getLocalVarTable($3) == 0){
                                   printf("Identifier no defined : %s \n", $3); errors++;
                     }
                     else{
                            if(savevar_current_memory_global_local_const == 1){
                                   if(isArrayGlobalVar($3) >= 0){
                                          printf("Variable is an array : %s \n", $3); 
                                          errors++;
                                   }
                                   else{
                                   generate_code(17, -1, -1, getGlobalVarTable($3));
                                   }
                            }
                            else {
                                   if(savevar_current_memory_global_local_const == 2){
                                          if(isArrayLocalVar($3) >= 0){
                                                        printf("Variable is an array : %s \n", $3); 
                                                        errors++;
                                                 }
                                          else{
                                                 generate_code(17, -1, -1, getLocalVarTable($3));
                                          }
                                   }
                            }
                     }
              }
          ;


towrite : WRITE '(' auxtowrite ')' ';'
       ;


auxtowrite : expression  { generate_code(18, -1, -1, $1);}
           |auxtowrite ',' expression   { generate_code(18, -1, -1, $3);}
           | WORDSTRING {
                     //printf("%s\n", $1);
                     installConstatString($1);
                     //printf("%s\n", $1); 
                     constantStringVars * value = getConstTableByString($1);
                     //printf("%s\n", $1);
                     //printf("%d\n", value->virtualAddress); 
                     generate_code(18, -1, -1, value->virtualAddress);
                     //printf("%s\n", $1);
                     }
           | auxtowrite ',' WORDSTRING {
                     installConstatString($3);
                     constantStringVars * value = getConstTableByString($3);
                     generate_code(18, -1, -1, value->virtualAddress);
                     }
           ;

statuteofdecision : IF '(' expression ')' { if( (returntypebyByVirtualAddress($3)-1) != 0){
                                                 errors++;
                                                 printf("Error type-mismatch at if");
                                          }
                                          else{
                                                 generate_code(2,$3,-1,-1);
                                                 ifJumpStack = addjumpStack (ifJumpStack, code_offset-1);
                                          }
                                          }
                     '{' statutes '}' statuteofdecisionsecondpart 
                     {                      
                     modify_code_at_given_cuad_num_result( code_offset , 
                            ifJumpStack->jumpValue );
                            //printf("in fin \n");
                     ifJumpStack = eliminateActualJumpStackNode (ifJumpStack);
                     }
                  ;

statuteofdecisionsecondpart : ELSE {
                                   //printf("in else \n");

                                   generate_code(1,-1,-1,-1);
                                   //printf("in gen code \n");
                                   auxJump = ifJumpStack->jumpValue;
                                   //printf("aj = ijs-jv \n");
                                   ifJumpStack = eliminateActualJumpStackNode (ifJumpStack);

                                   ifJumpStack = addjumpStack (ifJumpStack, code_offset-1);
                                   modify_code_at_given_cuad_num_result( code_offset , 
                                                 auxJump );
                                   }            
                                   '{' statutes '}' 
                            |  
                            ;

statuteofloop : conditional
              | noconditional
              ; 

conditional : DO {
              ifJumpStack = addjumpStack (ifJumpStack, code_offset);
              }
            '{' statutes '}' WHILE '(' expression ')' ';' {
              auxJump = ifJumpStack->jumpValue;
              ifJumpStack = eliminateActualJumpStackNode (ifJumpStack);
              generate_code(26,-1,-1,auxJump);
            }

            | WHILE {
                   ifJumpStack = addjumpStack (ifJumpStack, code_offset);
            }
            '(' expression ')' {
                   if( (returntypebyByVirtualAddress($4)-1) != 0){

                            errors++;
                            printf("Error type-mismatch at if");
                     }
                     else{
                            generate_code(2,$4,-1,-1);
                            ifJumpStack = addjumpStack (ifJumpStack, code_offset-1);
                     }
            }
            '{' statutes '}' {
                   auxJump = ifJumpStack->jumpValue;

                     //printf("aux   \n");

                   ifJumpStack = eliminateActualJumpStackNode (ifJumpStack);

                     //printf("elim   \n");

                   returnJump = ifJumpStack->jumpValue;
                   
                     //printf("return    \n");

                   ifJumpStack = eliminateActualJumpStackNode (ifJumpStack);

                     //printf("elim2    \n");

                   generate_code(1,-1,-1,returnJump);
                   modify_code_at_given_cuad_num_result( code_offset , auxJump );

                     //printf("modify  \n");
            }
            ;
            
noconditional : FOR IDENTIFIER '=' expression TO expression DO '{' statutes '}'
              ;





expression : NUMBERINTEGER {
              /*
              printf("%d : INTEGER \n", $1 );
              */
              installConstatInt($1); 
              constantIntVars * value = getConstTableByInt($1); 
              $$ = value->virtualAddress;}
           | LETTERCHAR {installConstatChar($1[1]); 
              constantCharVars * value = getConstTableByChar($1[1]); 
              $$ = value->virtualAddress;}
           | IDENTIFIER {   if (getLocalVarTable($1) == 0){
                                   printf("Identifier no defined : %s \n", $1); errors++;
                            }
                            else{
                                   //if(){}

                                   if(savevar_current_memory_global_local_const == 1){
                                                 if(isArrayGlobalVar($1) >= 0){
                                                        printf("Variable is an array : %s \n", $1); 
                                                        errors++;
                                                 }
                                                 else{
                                                        $$ = getGlobalVarTable($1);
                                                 }
                                   }
                                   else {
                                          if(savevar_current_memory_global_local_const == 2){
                                                 if(isArrayLocalVar($1) >= 0){
                                                        printf("Variable is an array : %s \n", $1); 
                                                        errors++;
                                                 }
                                                 else{
                                                        $$ = getLocalVarTable($1);
                                                 }
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
              constantFloatVars * value = getConstTableByFloat($1); 
              $$ = value->virtualAddress;}
           | expression '<' expression{
                            int type_exp = semanticCube[4]
                                   [returntypebyByVirtualAddress($1)-1]
                                   [returntypebyByVirtualAddress($3)-1];
                            if(type_exp == 9 ){
                                   printf("Error type expression");
                                   errors++;
                            }
                            else
                            {     
                                   if(savevar_current_memory_global_local_const == 1){
                                          installGlobalTemps(type_exp);
                                          generate_code(11,$1,$3,
                                                 lastGlobalTemporal->virtualAddress);
                                          $$ = lastGlobalTemporal->virtualAddress; 
                                   }
                                   else{
                                          installLocalTemps(type_exp);
                                          generate_code(11,$1,$3,
                                                 lastLocalTemporal->virtualAddress);
                                          $$ = lastLocalTemporal->virtualAddress; 
                                   }
                            }
                            
                            }
           | expression EQUALITY expression{
                  //printf("type 1 global %d\n",  returntypebyByVirtualAddress($1)-1);
                  //printf("type 2 global %d\n",  returntypebyByVirtualAddress($3)-1);
                            int type_exp = semanticCube[0]
                                   [returntypebyByVirtualAddress($1)-1]
                                   [returntypebyByVirtualAddress($3)-1];
                            if(type_exp == 9 ){
                                   printf("Error type expression\n");
                                   errors++;
                            }
                            else
                            {      
                                   if(savevar_current_memory_global_local_const == 1){
                                          installGlobalTemps(type_exp);
                                          //printf("type global %d\n",  type_exp);
                                          generate_code(10,$1,$3,
                                                 lastGlobalTemporal->virtualAddress);
                                          $$ = lastGlobalTemporal->virtualAddress; 
                                   }
                                   else{
                                          installLocalTemps(type_exp);
                                          //printf("type %d\n",  type_exp);
                                          generate_code(10,$1,$3,
                                                 lastLocalTemporal->virtualAddress);
                                          $$ = lastLocalTemporal->virtualAddress; 
                                   }
                            }
                            }
           | expression NOTEQUALITY expression{
                            int type_exp = semanticCube[1]
                                   [returntypebyByVirtualAddress($1)-1]
                                   [returntypebyByVirtualAddress($3)-1];
                            if(type_exp == 9 ){
                                   printf("Error type expression");
                                   errors++;
                            }
                            else
                            {      
                                   if(savevar_current_memory_global_local_const == 1){
                                          installGlobalTemps(type_exp);
                                          generate_code(25,$1,$3,
                                                 lastGlobalTemporal->virtualAddress);
                                          $$ = lastGlobalTemporal->virtualAddress; 
                                   }
                                   else{
                                          installLocalTemps(type_exp);
                                          generate_code(25,$1,$3,
                                                 lastLocalTemporal->virtualAddress);
                                          $$ = lastLocalTemporal->virtualAddress; 
                                   }
                            }
                            }
           | expression '>' expression {
                            int type_exp = semanticCube[5]
                                   [returntypebyByVirtualAddress($1)-1]
                                   [returntypebyByVirtualAddress($3)-1];
                            if(type_exp == 9 ){
                                   printf("Error type expression");
                                   errors++;
                            }
                            else
                            {      
                                   if(savevar_current_memory_global_local_const == 1){
                                          installGlobalTemps(type_exp);
                                          generate_code(12,$1,$3,
                                                 lastGlobalTemporal->virtualAddress);
                                          $$ = lastGlobalTemporal->virtualAddress; 
                                   }
                                   else{
                                          installLocalTemps(type_exp);
                                          generate_code(12,$1,$3,
                                                 lastLocalTemporal->virtualAddress);
                                          $$ = lastLocalTemporal->virtualAddress; 
                                   }
                            }
                            }
           | expression GREATERTHANOREQUAL expression {
                            int type_exp = semanticCube[3]
                                   [returntypebyByVirtualAddress($1)-1]
                                   [returntypebyByVirtualAddress($3)-1];
                            if(type_exp == 9 ){
                                   printf("Error type expression");
                                   errors++;
                            }
                            else
                            {      
                                   if(savevar_current_memory_global_local_const == 1){
                                          installGlobalTemps(type_exp);
                                          generate_code(14,$1,$3,
                                                 lastGlobalTemporal->virtualAddress);
                                          $$ = lastGlobalTemporal->virtualAddress; 
                                   }
                                   else{
                                          installLocalTemps(type_exp);
                                          generate_code(14,$1,$3,
                                                 lastLocalTemporal->virtualAddress);
                                          $$ = lastLocalTemporal->virtualAddress; 
                                   }
                            }
                            }
           | expression LESSTHANOREQUAL expression {
                            int type_exp = semanticCube[2]
                                   [returntypebyByVirtualAddress($1)-1]
                                   [returntypebyByVirtualAddress($3)-1];
                            if(type_exp == 9 ){
                                   printf("Error type expression");
                                   errors++;
                            }
                            else
                            {      
                                   if(savevar_current_memory_global_local_const == 1){
                                          installGlobalTemps(type_exp);
                                          generate_code(13,$1,$3,
                                                 lastGlobalTemporal->virtualAddress);
                                          $$ = lastGlobalTemporal->virtualAddress; 
                                   }
                                   else{
                                          installLocalTemps(type_exp);
                                          generate_code(13,$1,$3,
                                                 lastLocalTemporal->virtualAddress);
                                          $$ = lastLocalTemporal->virtualAddress; 
                                   }
                            }
                            }



           | expression '+' expression 
                            {
                            
                            int type_exp = semanticCube[9]
                                   [returntypebyByVirtualAddress($1)-1]
                                   [returntypebyByVirtualAddress($3)-1];
                            
                            if(type_exp == 9 ){
                                   printf("Error type expression");
                                   errors++;
                            }
                            else
                            {      
                                   if(savevar_current_memory_global_local_const == 1){
                                          installGlobalTemps(type_exp);
                                          generate_code(7,$1,$3,
                                                 lastGlobalTemporal->virtualAddress);
                                          $$ = lastGlobalTemporal->virtualAddress; 
                                   }
                                   else{
                                          installLocalTemps(type_exp);
                                          generate_code(7,$1,$3,
                                                 lastLocalTemporal->virtualAddress);
                                          $$ = lastLocalTemporal->virtualAddress; 
                                   }
                            }
                            
                            }



                            
           | expression '-' expression {
                            int type_exp = semanticCube[8]
                                   [returntypebyByVirtualAddress($1)-1]
                                   [returntypebyByVirtualAddress($3)-1];
                            if(type_exp == 9 ){
                                   printf("Error type expression");
                                   errors++;
                            }
                            else
                            {      
                                   if(savevar_current_memory_global_local_const == 1){
                                          installGlobalTemps(type_exp);
                                          generate_code(8,$1,$3,
                                                 lastGlobalTemporal->virtualAddress);
                                          $$ = lastGlobalTemporal->virtualAddress; 
                                   }
                                   else{
                                          installLocalTemps(type_exp);
                                          generate_code(8,$1,$3,
                                                 lastLocalTemporal->virtualAddress);
                                          $$ = lastLocalTemporal->virtualAddress; 
                                   }
                            }
                            }

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
                            }
                            else
                            {      
                                   if(savevar_current_memory_global_local_const == 1){
                                          installGlobalTemps(type_exp);
                                          generate_code(5,$1,$3,
                                                 lastGlobalTemporal->virtualAddress);
                                          $$ = lastGlobalTemporal->virtualAddress; 
                                   }
                                   else{
                                          installLocalTemps(type_exp);
                                          generate_code(5,$1,$3,
                                                 lastLocalTemporal->virtualAddress);
                                          $$ = lastLocalTemporal->virtualAddress; 
                                   }
                            }
                            }

           | expression '/' expression {
                            int type_exp = semanticCube[11]
                                   [returntypebyByVirtualAddress($1)-1]
                                   [returntypebyByVirtualAddress($3)-1];
                            if(type_exp == 9 ){
                                   printf("Error type expression");
                                   errors++;
                            }
                            else
                            {      
                                   if(savevar_current_memory_global_local_const == 1){
                                          installGlobalTemps(type_exp);
                                          generate_code(6,$1,$3,
                                                 lastGlobalTemporal->virtualAddress);
                                          $$ = lastGlobalTemporal->virtualAddress; 
                                   }
                                   else{
                                          installLocalTemps(type_exp);
                                          generate_code(6,$1,$3,
                                                 lastLocalTemporal->virtualAddress);
                                          $$ = lastLocalTemporal->virtualAddress; 
                                   }
                            }
                            }

           | expression '&' expression {
                            int type_exp = semanticCube[8]
                                   [returntypebyByVirtualAddress($1)-1]
                                   [returntypebyByVirtualAddress($3)-1];
                            if(type_exp == 9 ){
                                   printf("Error type expression");
                                   errors++;
                            }
                            else
                            {      
                                   if(savevar_current_memory_global_local_const == 1){
                                          installGlobalTemps(type_exp);
                                          generate_code(15,$1,$3,
                                                 lastGlobalTemporal->virtualAddress);
                                          $$ = lastGlobalTemporal->virtualAddress; 
                                   }
                                   else{
                                          installLocalTemps(type_exp);
                                          generate_code(15,$1,$3,
                                                 lastLocalTemporal->virtualAddress);
                                          $$ = lastLocalTemporal->virtualAddress; 
                                   }
                            }
                            }
           | expression '|' expression {
                            int type_exp = semanticCube[7]
                                   [returntypebyByVirtualAddress($1)-1]
                                   [returntypebyByVirtualAddress($3)-1];
                            if(type_exp == 9 ){
                                   printf("Error type expression");
                                   errors++;
                            }
                            else
                            {      
                                   if(savevar_current_memory_global_local_const == 1){
                                          installGlobalTemps(type_exp);
                                          generate_code(16,$1,$3,
                                                 lastGlobalTemporal->virtualAddress);
                                          $$ = lastGlobalTemporal->virtualAddress; 
                                   }
                                   else{
                                          installLocalTemps(type_exp);
                                          generate_code(16,$1,$3,
                                                 lastLocalTemporal->virtualAddress);
                                          $$ = lastLocalTemporal->virtualAddress; 
                                   }
                            }
                            }
           | '-' expression {
                            int type_exp = semanticCube[13]
                                   [returntypebyByVirtualAddress($2)-1]
                                   [returntypebyByVirtualAddress($2)-1];
                            if(type_exp == 9 ){
                                   printf("Error type expression");
                                   errors++;
                            }
                            else
                            {      
                                   if(savevar_current_memory_global_local_const == 1){
                                          installGlobalTemps(type_exp);
                                          generate_code(27,$2,-1,
                                                 lastGlobalTemporal->virtualAddress);
                                          $$ = lastGlobalTemporal->virtualAddress; 
                                   }
                                   else{
                                          installLocalTemps(type_exp);
                                          generate_code(27,$2,-1,
                                                 lastLocalTemporal->virtualAddress);
                                          $$ = lastLocalTemporal->virtualAddress; 
                                   }
                            }
                            }

           | '(' expression ')' {$$ = $2;}

           | arrayid { $$ = $1; }

           


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
                                          int type_exp = returntypebyByVirtualAddress(getGlobalVarTable($1))-1;
                                          if(savevar_current_memory_global_local_const == 1){
                                                 installGlobalTemps(type_exp);
                                                 generate_code(9,getGlobalVarTable($1),-1,
                                                        lastGlobalTemporal->virtualAddress);
                                                 $$ = lastGlobalTemporal->virtualAddress; 
                                          }
                                          else{
                                                 installLocalTemps(type_exp);
                                                 generate_code(9,getGlobalVarTable($1),-1,
                                                        lastLocalTemporal->virtualAddress);
                                                 $$ = lastLocalTemporal->virtualAddress; 
                                          }
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
int main( int argc, char *argv[] )
{ 
       extern FILE *yyin;
       ++argv; --argc;
       yyin = fopen( argv[0], "r" );
       /*yydebug = 1;*/
       errors = 0;
       yyparse ();
       printf ( "Parse Completed\n" );
       justOneCicle=0;

       
       
              
       //glutDisplayFunc(execute_the_code_cycle);
       
       if ( errors == 0 )
       { 
              print_code ();


              //configurar openGl
              glutInit(&argc, argv);
              //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
              glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
                     
              // tamaño para la ventana
              glutInitWindowSize(1366, 768);
              glutInitWindowPosition(0, 0);
                     
              //nombre a la ventana
              glutCreateWindow("Drawing");
              myInit();

              //execute_the_code_cycle();
              glutDisplayFunc(execute_the_code_cycle);
              glutMainLoop();

              //eliminateall();
              //eliminateGlbalMemory();
              //eliminateall();
              
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
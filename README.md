# Compis2021


Avanzado

1-Anlizadores lexico y sintatico

2-Semantica de variables

3-Cubo semantico

4-Generacion de codigo para funciones

5-Mapa de memeoria para la Maquina virtual

6-semi-Maquina virtual

7-funciones normales

8-Generacion de codigo para estatutos condicionales

9-Arreglos

10-Graficos



bison -d bison.y
gcc -c bison.tab.c
flex flex.l
gcc -c lex.yy.c
gcc -o fin bison.tab.o lex.yy.o -lGL -lGLU -lglut -lm
./fin


Tu primer programa:

En el siguiente programa se imprimen las palabras “Hello World”.
program firstProgram; 

main(){
    write ("Hello World");
}
Resultado
Hello World



Tipos de Datos
En este lenguaje hay enteros, caracteres y números con decimal, 
También existe el tipo void que significa que su valor no está disponible.

Capacidad de las variables
Type			Storage size	Value range
int 	4 bytes	-2,147,483,648 a 2,147,483,647
char	1 bytes	A-Za-z
float	4 byte	1.2E-38 a 3.4E+38 (6 posiciones decimales)



Declaración de variables

El nombre de las variables solo acepta letras y números
program variables ; 
var {int : entero1; float : decimal1; char : letra1;} 

main(){
    entero1= 5;
    decimal1 = 3.1415;
    letra1 = 'a';
    write (entero1);
    write (decimal1);
    write (letra1);
}

Resultado
5
3.1415
'a'



Expresiones Aritméticas 

En este lenguaje existen los siguientes operadores:
/,+,-,*,<,>,==,>=,<=,|,&,
Lógica Entera
Existen operaciones de comparación como el ‘<’ o el ‘==’
Si se quisiera saber si algo es verdadero o falso, en este lenguaje se utilizan los enteros, si algo es verdad entonces es representado como un entero mayor o igual que 1, y si es falso entonces es representado como un entero menor o igual que 0.
Ejemplo:
6<10
Resultado
1



Expresiones Lógicas 

El resultado de una operación lógica siempre es 1 o 0, pero las operaciones aceptan los demás enteros.

While
        <<estatuto>>

    }

Do while
do{
        <<estatuto>>
}
while(<<exp>>)

If else
if(<<exp>>){
        <<estatuto>>
    }
    else {
        <<estatuto>>
    }




Definición de Funciones

Existen funciones void y funciones tipo que regresan un valor en su llamada.
Las funciones tienen parámetros, y sus propias variables locales. Los parámetros son variables que se utilizan en la llamada de una función.
Funciones Void
program funcionEjemplo ; 
var {int : entero1;} 

void funcionVoid( int : aux ){
    write (aux);
}

main(){
    entero1=10;
    funcionVoid( entero1 );
    write (entero1);
}

Resultado
10
10



Funciones Tipo

Las funciones tipo soportan recursión. 
program fibonacciRecursivo ; 
var {int : factorf, total;} 

int fibonacci( int : factorf ){
    var {int : total;}
    total=0;
    if(factorf <= 1){
        total = factorf;
    }
    else {
        total = fibonacci(factorf-1) +fibonacci(factorf-2);
    }
    return (total);
}

main(){
    factorf=10;
    total = fibonacci(factorf);
    write (total);
}
Resultado
55



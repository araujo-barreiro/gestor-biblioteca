/*
  Libreria que se encarga de mostrar en pantalla los menus de Biblioteca.
  Por una parte incluye las funciones necesarias para imprimir la cabecera, y
  por otra muestra el mensaje de confirmacion de salida del programa.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define long_max 80 //maximo numero de caracteres por linea
#include "pantalla.h"

void pantalla(){  //funcion que me llama a las otras funciones de pantalla
  int k,largo=100;// puedo cambiar el 50 por una variable para dejarla mas facil de modificar
  char caracter = '#'; //caracter con el que dibuja el borde
	if (largo>long_max)
		largo=long_max; // si largo> long_max lo limitamos a 80
  for (k=0;k<7;k++){
    if (k==0 || k==6)
      base(caracter,largo);
    else if (k==3)
      titulo("BIBLIOTECA",caracter,largo);
    else lado(caracter,largo);
  }
  printf("\n");
  return;
}

void base(char caracter,int longitud){
  // Imprime una linea con 'longitud' 'caracter' repetidos
  int k;
  for (k=0;k<longitud;k++){
    printf("%c",caracter);
  }
  printf("\n");

  return;
}

void lado(char caracter,int longitud){
  // Imprime una linea con un 'caracter' al principio y al final
  int k;
  for (k=0;k<longitud;k++){
    if (k==0 || k ==(longitud-1))
      printf("%c",caracter);
    else printf(" ");
  }
  printf("\n");
  return;
}

void titulo(char *palabra,char caracter,int longitud){
  // Imprime un mensaje centrado en pantalla, con un 'caracter' a cada lateral
  int k,d;
  d = strlen(palabra)-1;
  for (k=0;k<(longitud-d);k++){
    if (k==0 || k == (longitud-d-1)) //longitud-d-1 es el punto final para el ultimo caracter
      printf("%c",caracter);
    else if (k==((longitud-d)/2)){
      printf("%s",palabra);
    }
    else printf(" ");
  }
  printf("\n");
}

int confirmar (){
  // Confirma la salida del programa usualmente dentro de un while(?)
  // Devuelve 1 para 'si', 0 para 'no', o un -1 para cualquier otra respuesta
  char opcion;
  int sol;
 do{ printf("\nSeguro que deseas salir del programa? (s/n): ");
  scanf(" %c",&opcion);
  while (getchar()!='\n');
  opcion=tolower(opcion);
  if (opcion == 's')
    sol =1;
  else  if (opcion =='n')
    sol =0;
else sol =-1;
 }while(sol == -1); // si introduce un caracter no valido te lo vuelve a pedir
  return sol;


}

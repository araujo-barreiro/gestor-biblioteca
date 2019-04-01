/*
  Programa de gestion de referencias bibliograficas. Trabaja con una base de datos
  guardada en dos ficheros llamados 'lectores.txt' y 'referencias.txt' y gestionada
  por la biblioteca base_datos.

  Proyecto de Diego Araujo y Guillermo Barreiro.
*/

#include <stdio.h>
#include "pantalla.h"
#include "base_datos.h"


#define Lector 1
#define Referencia 2
#define Opinion 3
#define Informe 4
#define Voto 5
#define Nota 6
#define Listar 7
#define Salir 0

#define Opcion1 "1) Incorporar lector\n"
#define Opcion2 "2) Agregar referencia\n"
#define Opcion3 "3) Expresar opinion\n"
#define Opcion4 "4) Obtener informe\n"
#define Opcion5 "5) Emitir voto\n"
#define Opcion6 "6) Calcular nota\n"
#define Opcion7 "7) Listar referencias\n"
#define Opcion0 "0) Salir\n"
#define Siguiente "\nSiguiente comando? "
#define SeleccionInvalida "\nHas realizado una seleccion no valida\n\n"

struct est_lector lectores [100];
struct est_referencia referencias [100];
int ultimo_lector, ultima_ref; // son los indices de los arrays: codigo = indice+1
int main (){
  int respuesta,res;
  comprobar_fichero_lectores();
  if (comprobar_formato_lectores()){
    return 1;
  }
  comprobar_fichero_referencias();
  if (comprobar_formato_referencias()){
    return 1;
  }
    pantalla();
    arranque(lectores,referencias,&ultimo_lector,&ultima_ref);
    do{
      // Muestra el menu principal
      printf(Opcion1);
      printf(Opcion2);
      printf(Opcion3);
      printf(Opcion4);
      printf(Opcion5);
      printf(Opcion6);
      printf(Opcion7);
      printf(Opcion0);

      printf(Siguiente);
      respuesta=-1;// si se mete una letra respuesta queda = -1 y da error
      scanf("%i",&respuesta);
      while(getchar()!='\n');
      printf("\n");
      switch (respuesta){ // ejecuta la funcion correspondiente a la opcion escogida
        case Lector:
        lector(&ultimo_lector,lectores);
        break;
        case Referencia:
        referencia(&ultima_ref,referencias);
        break;
        case Opinion:
        opinion(ultimo_lector,ultima_ref,referencias);
        break;
        case Informe:
        informa(ultima_ref,referencias,lectores);
        break;
        case Voto:
        voto(ultima_ref,referencias);
        break;
        case Nota:
        nota(ultima_ref,referencias);
        break;
        case Listar:
        listar(ultima_ref, referencias);
        break;

        case Salir:
        res=confirmar();
        printf("\n");
        break;

        default:
        printf (SeleccionInvalida);
      }

    }while (res!=1); // muestra reiteradamente el menu

    return 0;


}

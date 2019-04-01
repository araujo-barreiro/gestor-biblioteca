/*
Libreria que se encarga de gestionar la base de datos del programa Biblioteca.
La base de datos se almacena en los ficheros de texto 'referencias.txt' y 'lectores.txt'.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "base_datos.h"

#define archivo_lectores "lectores.txt"
#define archivo_referencias "referencias.txt"

#define nom_user "\nEscribe el nombre del lector:  "
#define cad_vac "\nCadena vacia\n"
#define long_max "\nLongitud de la cadena excesiva\n"
#define car_inv "\nCaracter invalido\n"
#define lec_repe "\nLector repetido\n"
#define lec_asig "\nLector %s: asignado %i\n\n"
#define error_fichero_lectores "Linea mal formada en el fichero (lectores.txt)\n"
#define error_fichero_referencias "Linea mal formada en el fichero (referencias.txt)\n"
#define autor_refe "\nEscribe el autor de la referencia: "
#define escribe_titulo "\nEscribe el titulo: "
#define escribe_ano "\nEscribe el anho: "
#define valor_incorrecto "\nValor seleccionado incorrecto\n"
#define tipo_refe "\nEscribe el tipo:"
#define escribe_sign "\nEscribe la signatura: "
#define escribe_codigo "\nEscribe el codigo: "
#define escribe_comentario "\nEscribe el comentario: "
#define escribe_voto "\nEscribe el voto: "
#define opinion_registrada "Opinion registrada\n\n"
#define operacion_no_disponible "Operacion imposible en este momento\n\n"
#define numero_comentarios "\nNumero de comentarios:%i\n"
#define voto_registrado "Voto registrado\n"
#define numero_votos "\nNumero de votos:%i\n"
#define nota_media "Nota media:%.2f\n"
#define elegir_tipo "\nL) Libros\nA) Articulos\n\nElige el tipo de referencias que quieres listar: "
#define tipo_invalido "Tipo seleccionado no valido\n"


/**
FUNCIONES DEL MENU PRINCIPAL:
1) Incorporar lector
2) Agregar referencia
3) Expresar opinion
4) Obtener informe
5) Emitir voto
6) Calcular nota
7) Listar referencias

**/

int lector (int *id,struct est_lector* lectores){ //lector

  char nombre[150];
  int comprobar,k;
  do{
    printf(nom_user);
    fgets(nombre,150,stdin); //el user introduce un nombre
    comprobar = comprobar_cadena(nombre, 48); // comprueba que el formato sea correcto

    if(!comprobar){
      // si el formato es correcto, compruebo que el nombre no este repetido
      for(k=0;k<100;k++){
        if(strcmp(nombre,(lectores+k)->nombre)==0){
          printf(lec_repe);
          comprobar++;
          return 1;
        }
      }

    }

  }while(comprobar!=0);

  *id=*id+1; // se va a escribir en una nueva posicion del array
  FILE *escritura;
  escritura=fopen(archivo_lectores,"a");
  strcpy(lectores[*id-1].nombre,nombre);
  lectores[*id-1].codigo=*id;
  printf(lec_asig,lectores[*id-1].nombre,*id);
  fprintf(escritura,":%i:%s:\n",*id,lectores[*id-1].nombre);
  fclose(escritura);

  return 0;
}


int referencia (int *q,struct est_referencia* referencia){
  char tipo; // 'L' || 'A'
  char tipos[10];
  char autor [100];
  char titulo [110];
  char anho[10]; // anho
  int ano;
  int comprobar;
  do{
    printf(autor_refe);
    fgets(autor,120,stdin); //el user introduce un autor
    comprobar = comprobar_cadena(autor, 50); // comprueba que el formato sea correcto
  }while(comprobar!=0);
  do {
    printf(escribe_titulo);
    fgets(titulo,110,stdin); //el user introduce un titulo
    comprobar = comprobar_cadena(titulo, 81); // comprueba que el formato sea correcto
  }while(comprobar!=0);
  do{

    comprobar=0;
    printf(escribe_ano);
    fgets(anho,10,stdin);// se introduce un anho
    int d=strlen(anho)-1;
    if (d>5) {
    while(fgetc(stdin)!='\n');
    printf(valor_incorrecto);
    ano=-1;
    continue;
    }
    ano = comprobar_numero(anho, 1450, 2017);
  }while(ano==-1);

  do{
    printf(tipo_refe);
    fgets(tipos,10,stdin);
    comprobar = comprobar_cadena(tipos, 2);
    if(comprobar==0){
      tipo=tipos[0];
      tipo=toupper(tipo);
      if (tipo!='A'&& tipo!='L'){
        printf(car_inv);
        comprobar++;
        continue;
      }

    }
  }while(comprobar!=0);

  FILE *escritura;
  *q=*q+1;
  escritura=fopen(archivo_referencias,"a");
  strcpy(referencia[*q-1].autor,autor);
  strcpy(referencia[*q-1].titulo,titulo);
  referencia[*q-1].ano=ano;
  referencia[*q-1].tipo=tipo;
  referencia[*q-1].signatura=*q;
  printf("\nReferencia %c:%s:%s:%i: asignada %i\n\n",referencia[*q-1].tipo,referencia[*q-1].autor,referencia[*q-1].titulo,referencia[*q-1].ano,referencia[*q-1].signatura);
  fprintf(escritura,":%i:%c:%s:%s:%i:%i:%i:%i:\n",referencia[*q-1].signatura,referencia[*q-1].tipo,referencia[*q-1].autor,referencia[*q-1].titulo,referencia[*q-1].ano,referencia[*q-1].votantes,referencia[*q-1].votos,referencia[*q-1].criticos);

  fclose(escritura);
  return 0;
}

int opinion(int indice_lector, int indice_signatura,struct est_referencia* referencias ){
  int signatura, lector;
  char comentario[90], respuesta[25];
if (indice_lector ==0 || indice_signatura==0){ //si no hay referencias o lectores volvemos al menú
    printf(operacion_no_disponible);
    return 1;
}
  // 1º: pide la signatura
  do{
    printf(escribe_sign);
    fgets(respuesta, 25, stdin);
    signatura = comprobar_numero(respuesta, 1, indice_signatura);
  }while(signatura==-1);

  // 2º: pide el codigo del lector
  do{
    printf(escribe_codigo);
    fgets(respuesta, 25, stdin);
    lector = comprobar_numero(respuesta, 1, indice_lector);
  }while(lector==-1);

  // 3º: pide el comentario
  do{
    printf(escribe_comentario);
    fgets(comentario, 100, stdin);
    if(!comprobar_cadena(comentario, 80)) break;
  }while(1);

  // Guarda el comentario en el array
  int indice_comentario = referencias[signatura-1].criticos;
  if(referencias[signatura-1].comentarios==NULL){ // si no habia comentarios todavia
    // inicializa el array de comentarios
    referencias[signatura-1].comentarios = malloc(20*sizeof(struct est_comentario));
  }
  referencias[signatura-1].comentarios[indice_comentario].lector = lector;
  strcpy(referencias[signatura-1].comentarios[indice_comentario].opinion,comentario);
  referencias[signatura-1].criticos++;

  referencias_to_file(referencias); // actualiza el fichero de texto

  // Confirmacion al usuario de la operacion:
  printf(opinion_registrada);

  return 0;
}

int informa(int indice, struct est_referencia* referencias, struct est_lector* lectores){
  int signatura,k;
  char respuesta[25];

  if (indice ==0 ){ //si no hay referencias volvemos al menú
      printf(operacion_no_disponible);
      return 1;
    }
    // Pide la signatura al usuario
  do{
    printf(escribe_sign);
    fgets(respuesta, 25, stdin);
    signatura = comprobar_numero(respuesta, 1, indice);
  }while(signatura == -1);

  struct est_referencia referencia = referencias[signatura-1]; // la referencia
          // de la que queremos obtener los comentarios
  printf(numero_comentarios, referencia.criticos); // imprime el numero de comentarios registrados
  for(k=0;k<referencia.criticos;k++){
    // imprime los comentarios, uno a uno
    int lector = referencia.comentarios[k].lector;
    printf("%s:",lectores[lector-1].nombre);
    printf("%s\n",referencia.comentarios[k].opinion);

  }
  printf("\n");

  return 0;
}

int voto(int indice,struct est_referencia* referencias){
  int signatura, voto;
  char respuesta[25];
  if (indice ==0 ){ //si no hay referencias volvemos al menú
      printf(operacion_no_disponible);
      return 1;
    }
  // 1º: Pide la signatura al usuario
  do{
    printf(escribe_sign);
    fgets(respuesta, 25, stdin);
    signatura = comprobar_numero(respuesta, 1, indice);
  }while(signatura == -1);

  // 2º: pide el voto entre el 0 y el 10
  do{
    printf(escribe_voto);
    fgets(respuesta,100, stdin);
    voto = comprobar_numero(respuesta, 0, 10);
  }while(voto==-1);

  // Registra voto en la BD
  referencias[signatura-1].votantes=referencias[signatura-1].votantes+1;
  referencias[signatura-1].votos=referencias[signatura-1].votos+voto;
  referencias_to_file(referencias);
  printf(voto_registrado);
  printf("\n");
  return 0;
}

int nota(int indice,struct est_referencia* referencias){
  int signatura;
  char respuesta[25];
  float media;
  if (indice ==0 ){ //si no hay referencias volvemos al menú
      printf(operacion_no_disponible);
      return 1;
    }
  // Pide la signatura al usuario
  do{
    printf(escribe_sign);
    fgets(respuesta, 25, stdin);
    signatura = comprobar_numero(respuesta, 1, indice);
  }while(signatura==-1);

  // Muestra numero de votos y valor medio
  struct est_referencia referencia = referencias[signatura-1];
  printf(numero_votos,referencia.votantes);
  if (referencia.votos==0 || referencia.votantes ==0) media =0;
  else media = (float)referencia.votos/referencia.votantes;
  printf(nota_media,media);
  printf("\n");
  return 0;
}

int listar(int indice, struct est_referencia* referencias){
  char tipo;
  do{
    // Solicita el tipo de referencia hasta que se introduzca correctamente
    printf(elegir_tipo);
    char respuesta[10];
    fgets(respuesta,10,stdin);
    printf("\n");
    int d = strlen(respuesta)-1;
    respuesta[d] = '\0'; // sustituye el caracter final por un fin de cadena

    // 1º: cadena vacia?
    if(d<=0){
      printf(tipo_invalido);
      continue;
    }

    // 2º: demasiado largo?
    if(d>=2){
      printf(tipo_invalido);
      while(fgetc(stdin)!='\n');
      continue;
    }

    // si la cadena es correcta, extrae el char y comprueba si es una l o una a
    tipo = toupper(respuesta[0]);
    if(tipo=='A' || tipo=='L') break;
    else {
      printf(tipo_invalido);
      continue;}

  }while(1);

  // Imprime por pantalla las referencias del tipo seleccionado
  int k;
  for(k=0;k<indice; k++){
    // comprueba si el tipo coincide, y en caso afirmativo la muestra en pantalla
    struct est_referencia referencia = referencias[k];
    if(referencia.tipo == tipo){
      printf("%i) %s. \"%s\" (%i)\n",referencia.signatura, referencia.autor,
        referencia.titulo, referencia.ano);
    }
  }

  printf("\n");

  return 0;

}

/**
FUNCIONES DE E/S
*/

void comprobar_fichero_lectores(){
  // Comprueba que existen los ficheros. Si no es asi los crea.

  FILE * lectores;
  lectores = fopen(archivo_lectores,"r");
  if (lectores== NULL){
    lectores= fopen(archivo_lectores,"w");
}
  fclose(lectores);

}

void comprobar_fichero_referencias(){
  // Comprueba que existen los ficheros. Si no es asi los crea.
  FILE * referencias;
  referencias= fopen(archivo_referencias,"r");
  if (referencias== NULL){
    referencias= fopen(archivo_referencias,"w");
  }
  fclose(referencias);
}


int comprobar_formato_lectores(){
  int a=0;
  //lectores
  FILE *lectores = fopen(archivo_lectores,"r");
  if(lectores!=NULL){
    while(1){ // lee el archivo linea a linea, hasta llegar al EOF
      char cadena[200];
      fgets(cadena, 200, lectores);
      if(feof(lectores)==0){
        // Comprueba que la linea leida tiene un formato correcto
        if (comprobar_lectores(cadena)){
          printf(error_fichero_lectores);
          a=1;
        }
      }else{
        break;
      }
    }

  }
  return a;
}
int comprobar_formato_referencias(){
  int a=0;
  //referencias
  FILE *referencias = fopen(archivo_referencias,"r");
  if(referencias!=NULL){
    while(1&&a!=1){ // lee el archivo linea a linea, hasta llegar al EOF , si hay un error sale
      char cadena[500];
      fgets(cadena, 500, referencias);
      if(feof(referencias)==0){
        // comprueba que la linea leida tiene un formato correcto
        if(comprobar_referencias(cadena)){
          printf(error_fichero_referencias);
          a = 1;
        }
      }else{
        break;
      }
    }
  }
  return a;
}

int comprobar_lectores(char *cadena){
  // Comprueba que el formato del archivo lectores.txt sea correcto
  // Analiza linea a linea
  // Devuelve 0 si solo si el formato es correcto
  int d,k,retorno=0,contador=0,a;// d= longitud array, k y a para recorrer el array y contador almacena el numero de ":" encontrados
  d=strlen(cadena)-2;

  if (cadena[0]!=':'|| cadena [d]!=':'){ //compruebo si el  caracter inicial y final es distinto de  ":"
  return 1;
}

for (k=0;k<d;k++){
  if (cadena[k]==' ') //si detecta un espacio avanza una posición
  continue;
  else if (cadena[k]==':'){ //compruebo la presencia de los ":"
  contador++;
  if (contador==3 && k<d){ // compruebo que no hay caracteres despues del los ":" finales
  retorno=1;
  break;
}
else if(contador==2){ //compruebo que solo hay numeros en el id de usuario
  if (k==1) return 1;
  for (a=1;a<k;a++){
    if(!isdigit(cadena[a])){
      retorno =1;
      break;
    }
  }
}
continue;
}    else if (cadena[k]!=':')// compruebo si el nombre del lector tiene letras o numeros
continue;
else { // en cualquier otro caso da error
  retorno=1;
  break;
}
}

return retorno;// devuelvo el valor de retorno, si es distinto de 0 lo consideramos error
}

int comprobar_referencias(char* cadena){
  // Comprueba que el formato del fichero referencias.txt sea correcto
  // Lo analiza linea a linea
  // Devuelve 0 si solo si el formato es correcto
  int d = strlen(cadena)-2;
  int contador = 1, k,a,e; // contador es el numero de ':' encontrados

  // 1º: acaba por ':'?
  if(cadena[d]!=':'){
    return 1;
  }

  // 2º: es una referencia o una opinion?
  if(cadena[0]=='#'){
    // Es una opinion
    for(k=1;k<d;k++){
      // Recorre la cadena posicion a posicion
      if(cadena[k]==' ') continue;
      if(cadena[k]==':'){
        contador ++;
        // si ya se han leido tres ':', la linea deberia de haberse terminado
        if(contador == 3 && k<d){
          return 1;
        }else if(contador == 2){
          // Compruebo que solo hubiese numeros entre # y :
          for(a=1;a<k;a++){
            if(!isdigit(cadena[a])) return 1;
          }
          continue;

        }
      }
      if(cadena[k]==':') return 1;
    }
  }

  if(cadena[0]==':'){
    // Es una referencia
    int ultimos_puntos = 0,antes;
    for(k=1;k<d;k++){
      // Recorre la cadena posicion a posicion
      if(cadena[k]==' ') continue;
      if(cadena[k]==':'){
        ultimos_puntos = k;
        contador++;

        // si ya se han leido ocho ':', la linea deberia de haberse terminado
        if(contador == 9 && k<d){
          return 1;
        }else if(contador == 2 || (contador>5 && contador<10)){
          // comprueba si es un numero
          for(a=ultimos_puntos-1;a<k;a++){
            if(!isdigit(cadena[a])) return 1;
          }
        }else if(contador == 4 || contador == 5){
          // comprueba si es un caracter alfanumerico
          if(ultimos_puntos-antes==1) return 1;
          for(a=antes+1;a<ultimos_puntos;a++){
        //   printf("%c\n",cadena[a]);
            if(cadena[a]==':') return 1;
          }
        }else if(contador == 3){
          // comprueba si es un unico caracter L o A
          if(k-ultimos_puntos!=0) return 1;
          if(cadena[k-1]!='A' && cadena[k-1]!='L') return 1;
        }
        antes=k;// posicion de los 2 puntos antes de guardar en ultimos_puntos
	e=contador; //igualo contador a 'e' porque contador tiene un valor local
      }
    }
    if (e!=8) return 1; // compruebo que son exactamente 8 campos
  }

  if(cadena[0]!=':' && cadena[0]!='#') return 1;
//printf("%i",e);

  return 0; // Si llega hasta este punto es que esta todo correcto
}


void arranque(struct est_lector* lectores, struct est_referencia* referencias, int *ultimo_lector, int *ultima_ref){
  /*
    Inicializa los arrays de lectores y referencias, cargando el contenido de los ficheros de texto en memoria.
    Se presupone que estos ficheros ya han sido creados y comprobado su formato.
  */

  // Empieza cargando la lista de lectores
  int indice = 0;
  FILE *archivo = fopen(archivo_lectores,"r");
  while(!feof(archivo)){ //feof da distinto de 0 si llega a EOF
    lector_to_struct(archivo, &lectores[indice]);
    indice++;
  }
  *ultimo_lector = indice-1; //indice apunta hacia el ultimo elemento del array
  fclose(archivo);

  // Carga la lista de opiniones / referencias
  indice = 0;
  archivo = fopen(archivo_referencias,"r");
  while(!feof(archivo)){ //feof da distinto de 0 si llega a EOF
    referencia_to_struct(archivo, &referencias[indice]);
    if(referencias[indice].criticos>0){
      //  Si la referencia tiene opiniones
      int k;
      //int n = referencias[indice].criticos;
      referencias[indice].comentarios = malloc((referencias[indice].criticos+20)*sizeof(struct est_comentario));
      for(k=0;k<referencias[indice].criticos;k++){
        // Guarda las opiniones de dicha referencia en su array de opiniones
        comentario_to_struct(archivo, &(referencias[indice].comentarios[k]));

      }
    }

    indice++;
  }

  *ultima_ref = indice-1; //indice apunta hacia el ultimo elemento del array
  fclose(archivo);
  return;
}

/**
  FUNCIONES AUXILIARES
  Estas funciones son para uso interno de base_datos.c
  TODO: revisar cuales hacen falta y cuales sobran
*/

void lector_to_struct(FILE* puntero, struct est_lector* lector){
  // Crea una struct lector a partir de una linea del fichero lectores.txt
  int d;
  char temp[50];
  fscanf(puntero, ":%i:" , &lector->codigo);
  fgets(temp,50,puntero);
  d=strlen(temp)-2;
  temp[d]='\0';
  strcpy(lector->nombre,temp);
  return;
}

void referencias_to_file(struct est_referencia* referencias){
  // Guarda en un fichero todas las referencias y comentarios
  int k = 0; //indice del array de referencias
  FILE* archivo = fopen(archivo_referencias, "w"); // se va a sobreescribir el fichero orignal!

  do{
    struct est_referencia referencia = referencias[k]; // la referencia actual
    if(referencia.signatura==0) break; // al llegar al final del array termina el proceso

    // Escribe una nueva linea con el contenido de referencias[k]
    fprintf(archivo, ":%i:%c:%s:%s:%i:%i:%i:%i:\n",referencia.signatura,
    referencia.tipo, referencia.autor, referencia.titulo,
    referencia.ano, referencia.votantes, referencia.votos,
    referencia.criticos);

    if(referencia.criticos>0){
      // guarda las opiniones, linea a linea
      int m;
      for(m=0;m<referencia.criticos;m++){
        fprintf(archivo, "#%i:%s:\n", referencia.comentarios[m].lector, referencia.comentarios[m].opinion);
      }
    }
    k++;
  }while(1);

  fclose(archivo);

  printf("\n");
  return;
}

void referencia_to_struct(FILE *puntero, struct est_referencia* referencia){
  int k;
  // Crea una struct referencia a partir de una linea del fichero lectores.txt
  char linea[110],*token;
  fgets(linea,110,puntero);
  int d= strlen(linea);
  if (d<10) return; //si la linea tiene menos de 10 caracteres se elimia por ser basura
//  printf("L= %i %s",d,linea);
  // Saca los elementos de la linea, uno a uno
  const char separador[2] = ":";
  int numero;
  token=strtok(linea, separador);
//  printf("\n");
  for (k=0;k<8;++k){
    if(token!=NULL){

      switch (k){
        case 0: //signatura
        numero = atoi(token);
        referencia->signatura = numero;
        //    printf("signatura: %i\n",referencia->signatura);
        break;
        case 1: //tipo
        token = strtok(NULL,separador);
        referencia->tipo=token[0];
        //      printf("tipo :%c\n",referencia->tipo);
        break;
        case 2: //autor
        token = strtok(NULL,separador);
        strcpy(referencia->autor,token);
        //    printf("autor: %s\n",referencia->autor);
        break;
        case 3: //titulo
        token = strtok(NULL,separador);
        strcpy(referencia->titulo,token);
        //    printf("titulo: %s\n",referencia->titulo);
        break;
        case 4: //anho
        token = strtok(NULL,separador);
        numero = atoi(token);
        referencia->ano = numero;
        //  printf("anho: %i\n",referencia->ano);
        break;
        case 5: //votantes (pp)
        token = strtok(NULL,separador);
        numero = atoi(token);
        referencia->votantes = numero;
        //      printf("votantes: %i\n",referencia->votantes);
        break;
        case 6: //votos
        token = strtok(NULL,separador);
        numero = atoi(token);
        referencia->votos = numero;
        //    printf("votos: %i\n",referencia->votos);
        break;
        case 7://criticos
        token = strtok(NULL,separador);
        numero = atoi(token);
        referencia->criticos = numero;
        //    printf("criticos: %i\n",referencia->criticos);
        break;
      }
    }
    else break;
  }


  return;
}

void comentario_to_struct(FILE* puntero, struct est_comentario* comentario){
  // Crea una struct comentario a partir de una linea del fichero referencias.txt
  fscanf(puntero, "#%i:", &comentario->lector);
  char opinion[100];
  fgets(opinion,100,puntero);
  int d = strlen(opinion)-2;
  opinion[d] = '\0';
  strcpy(comentario->opinion, opinion);
  return;
}

int comprobar_cadena(char* cadena, int longitud){
  /* Comprueba si una cadena cumple el formato correcto (sin :, longitud maxima...)
  Tambien sustituye el salto de linea final por un fin de cadena
  Devuelve 0 si el formato es correcto, 1 si hay algun error
  Si hay algun error lo indica por pantalla */

  int d = strlen(cadena)-1,k;
  cadena[d] = '\0'; // sustituye el caracter final por un fin de cadena

  // 1º: cadena vacia?
  if(d<=0){
    printf(cad_vac);
    return 1;
  }

  // 2º: demasiado largo?
  if(d>=longitud){
    printf(long_max);
    //while(fgetc(stdin)!='\n');
    return 1;
  }

  // 3º: caracteres invalidos?
  for (k=0;k<d;k++){
    if (cadena[k]==' ')
    continue;
    else if (cadena[k]==':'){
      printf(car_inv);
      return 1;
    }
  }

  // Si se ha llegado hasta aqui es que el formato es correcto
  return 0;

}

int comprobar_numero(char* cadena, int inicio, int final){
  /* Comprueba si una cadena obtenida mediante fgets es un numero comprendido entre
  inicio y final (incluidos). En caso afirmativo devuelve dicho numero como un entero,
  y en caso negativo devuelve -1.
  Los numeros de inicio y final tienen que ser mayores o iguales a 0. Si no devuelve -1.*/

  if(inicio<final && inicio<0) return -1;

  int d = strlen(cadena)-1;
 cadena[d] = '\0'; // sustituye el salto de linea por un fin de cadena
  int k;
  for(k=0;k<strlen(cadena);k++){
    if(!isdigit(cadena[k])){
      printf(valor_incorrecto);
      return -1;
    }
  }

  // En caso de que sea un numero comprueba que este en el rango correcto
  int entero = atoi(cadena);
  if(entero>=inicio && entero<=final) return entero;
  else printf(valor_incorrecto);
  return -1;

}

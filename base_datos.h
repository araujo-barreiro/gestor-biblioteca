
struct est_lector{
  // Estructura con los datos de un lector de la base de datos
  char nombre[50];
  int codigo; // asignado por el programa, no por el usuario!
};

struct est_comentario{
  // Estructura con los comentarios de una referencia determinada
  int lector; // lector = est_lector.codigo
  char opinion[80];
};

struct est_referencia{
  // Estructura con los datos de una referencia de la base de datos
  char tipo; // 'L' || 'A'
  char autor [50];
  char titulo [80];
  int ano; // anho
  int signatura; // asignado por el programa, no por el usuario!
  int votantes;
  int votos;
  int criticos;
  struct est_comentario *comentarios; // array con los comentarios de la referencia
};

// Funciones menu principal
int lector(int *,struct est_lector*); //necesito pasarle la direccion del struct de lectores
int referencia(int *,struct est_referencia*);
int opinion(int, int,struct est_referencia*);
int informa(int, struct est_referencia*, struct est_lector*);
int voto(int,struct est_referencia*);
int nota(int,struct est_referencia*);
int listar(int, struct est_referencia*);

// Funciones E/S
void comprobar_fichero();
void comprobar_fichero_lectores();
void comprobar_fichero_referencias();
int comprobar_formato_lectores();
int comprobar_formato_referencias();
int comprobar_lectores(char *);
int comprobar_referencias(char*);
void arranque(struct est_lector *, struct est_referencia *, int *, int *);

// Funciones auxiliares
void lector_to_file(struct est_lector*, FILE*);
void lector_to_struct(FILE*, struct est_lector*);
void referencias_to_file(struct est_referencia*);
void referencia_to_struct(FILE*, struct est_referencia*);
void comentario_to_file(struct est_comentario, FILE*);
void comentario_to_struct(FILE*, struct est_comentario*);
int comprobar_cadena(char*, int);
int comprobar_numero(char*, int, int);

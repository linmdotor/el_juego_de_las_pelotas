/******************************************************************************
  Constantes Define
******************************************************************************/

//Resoluci�n de Pantalla en X e Y (valores min: 160x10 modo ventana, 640x480 pantalla completa)
#define RESOX 640 
#define RESOY 480


/******************************************************************************
  Variables Globales
******************************************************************************/

BITMAP* buffer=NULL; // Definimos las siguientes como un BITMAP
BITMAP* fondo=NULL;
BITMAP* BolaBmp[4]; //se crean tantas como tama�os de bola existen
BITMAP* DispBmp[3];
BITMAP* DispCuadroBmp[3]; 
BITMAP* Mens[6]; //bitmap para los mensajes de pantalla

MIDI* musica=NULL; //Definimos "musica" como un MIDI

SAMPLE* SampDisp[3]; //SAMPLES para los sonidos WAV
SAMPLE* SampMuerte=NULL; 
SAMPLE* SampBolas=NULL;

int VeloTemp=40; //Velocidad de Incremento del Temporizador (en milisegundos: 1000=1seg.)(40 para velocidad normal)
int Temp; //Contador que se emplear� para el temporizador del bucle principal
int TempAux; //Auxiliar del Contador de Tiempo
int TiempoMax=120; //Tiempo M�ximo de Juego
int Tiempo=TiempoMax; //Tiempo de Juego
float Reta=0; //Retardo del Bucle Principal
int ContGlobal=0; //Contador global (de "ciclos") para procesos como el de secuenciaci�n de sprites
int ContReinicio=0; //Contador que se emplear� en el m�dulo de reinicio

int Punt=0; //puntuaci�n TOTAL
int ModoProg=0; //Marcador del Modo Programador (MOSTRAR TEXTOS Y M�SCARAS) 0-no 1-si
int ModoJuego=1; //Marcador del modo de Juego(1 survivor, 2 time survivor)
int VersionJuego=1; //Versi�n de Juego (carpeta de carga de gr�ficos y sonido)
char Archivo[50]; //archivo que se utilizar� para elegir de d�nde se cargan las im�genes del juego
   
int LimiIzqd=20;  //l�mite IZQUIERDO (1 min.)
int LimiSupe=20;  //l�mite SUPERIOR (1 min.)
int LimiDere=620;  //l�mite DERECHO (640 max.)
int LimiInfe=438;  //l�mite INFERIOR (480 max.)


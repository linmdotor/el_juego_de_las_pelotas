/******************************************************************************
  Estructuras de las Máscaras
******************************************************************************/

struct PMASK* DispMask[3];
struct PMASK* BolaMask[4]; //se crean tantas como tamaños de bola existen


/******************************************************************************
  Otras Estructuras
******************************************************************************/

//Estructura de X e Y
typedef struct EstrXY 
{
   int X; 
   int Y;

}TEstrXY;

//Estructura de los Disparos
typedef struct EstrDisp 
{
   TEstrXY Posi; //Posición en X e Y
   int Tipo; //Tipo de disparo: 0-flecha 1-balas
   
}TEstrDisp;
 
//Estructura de los Personajes
typedef struct EstrPers 
{
   TEstrXY Posi; //Posición en X e Y
   TEstrXY Velo; //Velocidad en X e Y
   TEstrXY Acel; //Aceleración en X e Y  
   
   int Vida; //nº de Vidas
   char Muert; //Marcador de si el persona está "muerto" ('S' ó 'N')
   
   int ImagLong; //nº de imágenes (Longitud del Vector de imágenes)
   BITMAP* Imag[15]; //Vector de imágenes
   char ArchivoConRuta[50]; //Nombre de Archivo con ruta de las imágenes
   int ImagMarc; //Marcador de la imagen actual en la secuencia
   int VeloFrame; //Velocidad entre frames para la animación 
   
   BITMAP* MaskBmp; //Imagen BMP de la que se pintará la máscara
   BITMAP* BmpActu; //Imagen BMP ACTUAL
   struct PMASK* Mask; //Máscara de la imágen    
         
}TEstrPers;

//Estructura de los Objetos con Aceleración (bolas)
typedef struct EstrObjtMovi 
{
   TEstrXY Posi; //Posición en X e Y
   TEstrXY Velo; //Velocidad en X e Y
   TEstrXY Acel; //Aceleración en X e Y   
   
   int Tama; //Marcador del tamaño  
         
}TEstrObjtMovi;

//Estructura del Fichero de las Puntuaciones
typedef struct EstrPuntuacion
{
   int Modo;
   int Nivel;
   int Puntos;
}TEstrPuntuacion;


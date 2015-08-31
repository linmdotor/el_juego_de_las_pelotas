/******************************************************************************
  Estructuras de las M�scaras
******************************************************************************/

struct PMASK* DispMask[3];
struct PMASK* BolaMask[4]; //se crean tantas como tama�os de bola existen


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
   TEstrXY Posi; //Posici�n en X e Y
   int Tipo; //Tipo de disparo: 0-flecha 1-balas
   
}TEstrDisp;
 
//Estructura de los Personajes
typedef struct EstrPers 
{
   TEstrXY Posi; //Posici�n en X e Y
   TEstrXY Velo; //Velocidad en X e Y
   TEstrXY Acel; //Aceleraci�n en X e Y  
   
   int Vida; //n� de Vidas
   char Muert; //Marcador de si el persona est� "muerto" ('S' � 'N')
   
   int ImagLong; //n� de im�genes (Longitud del Vector de im�genes)
   BITMAP* Imag[15]; //Vector de im�genes
   char ArchivoConRuta[50]; //Nombre de Archivo con ruta de las im�genes
   int ImagMarc; //Marcador de la imagen actual en la secuencia
   int VeloFrame; //Velocidad entre frames para la animaci�n 
   
   BITMAP* MaskBmp; //Imagen BMP de la que se pintar� la m�scara
   BITMAP* BmpActu; //Imagen BMP ACTUAL
   struct PMASK* Mask; //M�scara de la im�gen    
         
}TEstrPers;

//Estructura de los Objetos con Aceleraci�n (bolas)
typedef struct EstrObjtMovi 
{
   TEstrXY Posi; //Posici�n en X e Y
   TEstrXY Velo; //Velocidad en X e Y
   TEstrXY Acel; //Aceleraci�n en X e Y   
   
   int Tama; //Marcador del tama�o  
         
}TEstrObjtMovi;

//Estructura del Fichero de las Puntuaciones
typedef struct EstrPuntuacion
{
   int Modo;
   int Nivel;
   int Puntos;
}TEstrPuntuacion;


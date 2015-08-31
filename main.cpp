/******************************************************************************

 Autor: Lin M.Dotor
 Proceso: Programa Principal del videojuego "EL JUEGO DE LAS PELOTAS"
 
 Sugerencias, comentarios, críticas e insultos de todo tipo a: linmdotor@gmail.com  

******************************************************************************/

/* Ficheros Include */

#include <allegro.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "pmask.h"
#include "Globales.h"
#include "Estructuras.h"
#include "Declaraciones.h"
#include "Inicializar.h"
#include "Modulos.h"



int main(void) 
{
/* Declaración de Variables */

   int ModoPant=0; //Modo de Pantalla (1 para pantalla completa y 0 para modo ventana)
     
   TEstrPuntuacion Record; //Estructura para el Fichero de Records
   int PuntRecord=0; //Puntuación Record
   char NombFich[]="Records.dat"; //Ruta del fichero de los record
    
   struct EstrPers Juga; //Estructura del Jugador
   
   int BolaMaxi=24; //Máximo de Bolas simultaneas (hasta 3 bolas grandes desplegadas- 24/8 = 3)
   struct EstrObjtMovi Bola[BolaMaxi]; //Vector de Estructura de la Bola
   int BolaCont=0; //Contador del Número de Bolas actual
   
   int SeguGeneBola=10; //Segundos que tarda en generarse una nueva bola aleatoria
    
   int DispMaxi=15; //Máximo de Disparos simultáneos
   struct EstrDisp Disp[DispMaxi]; //Vector de Estructura de Posición (para los disparos)
   int DispVeloX=0, DispVeloY=15; //Velocidades en X e Y
   int DispCont=0; //Contador del Número de Disparos actual 
   int NivelJuego=1; //marcador del tipo de disparo utilizado actualmente (nivel FACIL, NORMAL y DIFICIL)
  
   int ImagFondoLong=6; //nº de imágenes (Longitud del Vector)
   BITMAP* ImagFondo[ImagFondoLong]; //Vector de imágenes
   char ArchivoFondoConRuta[50]="/img/fondo/fondo";
   int ImagFondoMarc=0; //Marcador de la imagen actual en la secuencia
   int VeloFondoFrame=5; //velocidad entre Frames para el fondo
  
   int ColiJugaBola=0; //Marcador de la Colisión Jugador/Bola
   int ColiDispBola=0; //Marcador de la Colisión Disparo/Bola
     
   int MarcTeclSPACE=0; //Marcador de la pulsación de la tecla ESPACIO
   int MarcTeclModoDisp=0; //Marcador de la pulsación de la tecla de cambio de tipo de disparo (I)
   int MarcTeclGeneBola=0; //Marcador de la pulsación de la tecla de generación de bolas (O)
   int MarcTeclGeneProg=0; //Marcador de la pulsación de la tecla de activación de modo programador (P) 
   int MarcMouse1=0; //Marcador del click izquierdo del mouse

  
/* Algoritmo */
   srand(time(NULL)); //Inicializa el Random

   IniciarJugador(&Juga); //Iniciamos el Jugador

   init(ModoPant); //Inicializamos Allegro
  
   buffer=create_bitmap(SCREEN_W,SCREEN_H); // Iniciamos el BITMAP para el buffer
   
   EligirModoPantalla(); //Elegimos el Modo de Pantalla (reinicializa Allegro)
   ElegirVersionJuego(); //Elegimos la Versión de Juego (carpeta de carga de gráficos y de sonidos)
   EligirModoJuego(); //Elegimos el Modo de Juego (Tiempo Activado o Desactivado)
   EligirNivelJuego(&NivelJuego, &DispMaxi); //Elegimos el Nivel de Juego (Tipo de Disparo)
  
   ActualizaRecord(NombFich, Record, ModoJuego, NivelJuego, Punt, &PuntRecord); //Actualiza la puntación de Record Mostrada, desde el fichero  
  
   CargaMidi(&musica, "/snd/musica");  
  
   IniciarBmpMascaras(&Juga); //Iniciamos los BMP y las máscaras   
  
   CargaSecuenciaBMP(ImagFondo, ArchivoFondoConRuta, ImagFondoLong); //Carga los BMP Fondo
   CargaSecuenciaBMP(Juga.Imag, Juga.ArchivoConRuta, Juga.ImagLong); //Carga los BMP Jugador
   
   int MensActu=0; //Marcador del Mensaje Actual
   CargaSecuenciaBMP(Mens, "/img/fondo/mensaje", 6); //Carga los BMP de los Mensajes
   
   CargaWav(&SampDisp[0], "/snd/efectos/Disparo0");
   CargaWav(&SampDisp[1], "/snd/efectos/Disparo1");
   CargaWav(&SampDisp[2], "/snd/efectos/Disparo2");
   CargaWav(&SampMuerte, "/snd/efectos/Muerte");
   CargaWav(&SampBolas, "/snd/efectos/Bolas");

   IniciarBola(&Bola[0], &BolaCont, 3); //Iniciamos la Bola
   Juga.Posi.X=LimiDere/2-(Juga.Imag[0]->w)/2, Juga.Posi.Y=LimiInfe-(Juga.Imag[0]->h); //Inicia la posición del Jugador
   Juga.ImagLong=5;
   
   Temp=0;
   
while (!key[KEY_ESC]) 
{
while (!key[KEY_ESC] && Temp!=TempAux) //Para que reproduzca el bucle según el temporizador 
{   
   //¡¡¡Comentar estas 3 líneas si se quieren desactivar los "cheats" de programador!!!  
   GenerarBolaAleatoriaTecla(Bola, &BolaCont, BolaMaxi, &MarcTeclGeneBola);     //Genera una Nueva Bola   
   CambiarModoDisparo(&NivelJuego, &MarcTeclModoDisp, &DispMaxi);               //Cambia entre el Tipo de Disparo
   CambiarModoProgramador(&MarcTeclGeneProg);                                   //Activa el "Modo Programador"
   ModificarRetardo();                                                          //Modifica el retardo (con + ó -)
   
   if (Juga.Muert=='S') //Si el jugador está MUERTO y...
   {                
      if (Juga.Vida<0) //...SIN INICIAR
         IniciarJuego(&Juga, &MensActu);    
      else if (Juga.Vida>0 && Tiempo>0) //...CON VIDAS
         ReiniciarJuego(&Juga, Bola, &BolaCont, BolaMaxi, &SeguGeneBola, &DispCont, &ColiJugaBola, &MensActu); //Continua el Juego en caso de que muera el jugador                                                       
      else if (Juga.Vida==0 || Tiempo==0) //...CON '0' VIDAS o TIEMPO '0'
         TerminarJuego(&Juga, Bola, &BolaCont, BolaMaxi, &SeguGeneBola, &DispCont, &ColiJugaBola, &MensActu, &NivelJuego, &DispMaxi, NombFich, Record, &PuntRecord); //Da la opción de CONTINUAR o ELEGIR MODO   
   }                                                            
      
   if (Juga.Muert=='N') //Si el jugador está VIVO
   {
                        
      if ((Temp*ModoJuego)%(20000/VeloTemp)<=1 && SeguGeneBola>3)               //Disminuye SeguGeneBola cada 20 ó 10 segundos   
         SeguGeneBola--;
      GenerarBolaAleatoriaTiempo(Bola, &BolaCont, BolaMaxi, SeguGeneBola);      //Genera una Nueva Bola    
      
      ColisionDispBola(Bola, &BolaCont, BolaMaxi, Disp, &DispCont, &ColiDispBola, &MarcMouse1, NivelJuego); //Comprueba Colisión Disparo-Bola

      if (BolaCont<=0)                                                          //Genera nueva bola si hay 0
         IniciarBola(Bola, &BolaCont, -1);

      MoverJugador(&Juga, Disp, &DispCont, DispMaxi, &NivelJuego, &MarcTeclSPACE); //Mueve el Jugador      
      MoverBola(Bola, BolaCont);                                                //Mueve la Bola
      MoverDisparos(Disp, &DispCont, DispVeloX, DispVeloY);                     //Mueve los Disparos
      
      ColisionJugaBola(&Juga, Bola, BolaCont, &ColiJugaBola);                   //Comprueba Colisión Jugador-Bola
              
   }

   
   //Dibuja los gráficos
   clear_bitmap(buffer);                                                        // Limpiamos el buffer cada pasada
            
   PintarFondo(&Juga, VeloFondoFrame, &ImagFondoMarc, ImagFondoLong, ImagFondo); //Pinta el Fondo
    
   PintarDisparos(Disp, DispCont);                                              //Pinta los Disparos
      
   draw_sprite(Juga.MaskBmp,Juga.BmpActu,0,0);                                  //Cambiamos la Máscara del Jugador
   Juga.Mask = create_allegro_pmask(Juga.MaskBmp);   
      
   PintarJugador(&Juga);                                                        //Pinta el Jugador
      
   PintarBolas(Bola, BolaCont);                                                 //Pinta las Bolas
   
   PintarSprite(DispCuadroBmp[NivelJuego-1], (RESOX/2)-(DispCuadroBmp[NivelJuego-1]->w/2), RESOY-(DispCuadroBmp[NivelJuego-1]->h)); //Pinta el Cuadrado de Tipo de Disparo
 
   MostrarParametros(Juga, ColiJugaBola, ColiDispBola, MarcMouse1, Juga.Vida, DispCont, BolaCont, SeguGeneBola, NivelJuego); //Muestra los Textos   

   PintarSprite(Mens[MensActu],(RESOX/2)-(Mens[MensActu]->w/2),(RESOY/2)-(Mens[MensActu]->h/2)); //Pinta el Mensaje Correspondiente
   
   PintarMensajes(Juga, PuntRecord);
   
   PintarMouse(NivelJuego);                                                     //Dibuja el mouse
   
   blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);                               //Intercambia el Buffer a la Pantalla
        
   if (Juga.Muert=='N' && ModoJuego==2)                                         //Calcula el tiempo restante
      {
         Tiempo=TiempoMax-(Temp*VeloTemp/1000);                                          
         if(Tiempo<=0)
         {                   
            Tiempo=0;
            Juga.Muert='S';
         }
      }      
                      	                     	
   AumentarContador(&ContGlobal, INT_MAX);                                      //Aumenta Contador Global  
   TempAux=Temp;                                                                //Volvemos a guardar el tiempo actual   
   rest((int)Reta);                                                             //Retardo
   //readkey(); //habilitaremos esto si queremos hacer una pasusa cuadro a cuadro                                                             
}  
}

/* Fin de Algoritmo */
   deinit(); //Deinicializamos Allegro
   return (0);
}
END_OF_MAIN(); // Esto es para tener portabilidad a Linux


/*MODULOS ORDENADOS EN ORDEN ALFABÉTICO*/

/******************************************************************************
  AbrirFichero: Función de Apertura de un Fichero 
******************************************************************************/

int AbrirFichero(FILE **Fich, char Nomb[], char Modo[])
{
   *Fich=NULL; 
   *Fich = fopen(Nomb, Modo);

   if(*Fich == NULL)
   {
      allegro_message("Error al abrir el fichero %s en modo %s\n", Nomb, Modo);
      return (0);
	}
   else
   	return (1);
}

/******************************************************************************
  ActualizaFichero: Función de Actualización de un Record en el Fichero correspondiente 
******************************************************************************/

void ActualizaFichero(char NombFich[], TEstrPuntuacion Record, int Modo, int Nivel, int Punt)
{
   FILE *Fich;  
     
   AbrirFichero(&Fich, NombFich, "r+b"); //Modo lectura y escritura (sin creación de nuevo) 
    
   if (Punt > CompruebaRecord(Fich, Record, Modo, Nivel, Punt))
   {     
      Record.Modo=Modo;
      Record.Nivel=Nivel;
      Record.Puntos=Punt;

      fseek(Fich, (((Modo-1)*3)+(Nivel-1))*sizeof(Record), SEEK_SET); //Buscamos la posición en el fichero

      fwrite (&Record, sizeof(Record), 1, Fich); //Y lo sustituimos
   }
    
   fclose(Fich);
}

/******************************************************************************
  ActualizaRecord: Función de Actualización de la variable Record con el valor correspondiente 
******************************************************************************/

void ActualizaRecord(char NombFich[], TEstrPuntuacion Record, int Modo, int Nivel, int Punt, int *PuntRecord)
{
   FILE *Fich;  
     
   AbrirFichero(&Fich, NombFich, "rb"); //Modo lectura
    
   *PuntRecord=CompruebaRecord(Fich, Record, Modo, Nivel, Punt);
       
   fclose(Fich);
}

/******************************************************************************
  AumentarContador: Función de Aumentar un Contador desde 0 a un límite (exclusive) 
******************************************************************************/

void AumentarContador(int *Nume, int Limi)
{
   *Nume = ((*Nume+1)%Limi);
}

/******************************************************************************
  CambiarModoDisparo: Procedimiento de Cambio de Tipo de Disparo
******************************************************************************/

void CambiarModoDisparo(int *NivelJuego,  int *MarcTeclModoDisp, int *DispMaxi)
{

   if (key[KEY_I] && *MarcTeclModoDisp==0)
   {
      *NivelJuego=(*NivelJuego%3)+1;
      if (*NivelJuego == 1)
         *DispMaxi=2;
      else if (*NivelJuego == 2)
         *DispMaxi=8;
      else if (*NivelJuego == 3)
         position_mouse(RESOX/2,RESOY/2);
         
      *MarcTeclModoDisp=1;
   }
      
   else if (!key[KEY_I])
       *MarcTeclModoDisp=0;
}

/******************************************************************************
  CambiarModoProgramador: Activación de los textos y las máscaras
******************************************************************************/

void CambiarModoProgramador(int *MarcTeclGeneProg)
{

   if (key[KEY_P] && *MarcTeclGeneProg==0)
   {
      ModoProg=(ModoProg+1)%2;
      *MarcTeclGeneProg=1;     
   }    
   else if (!key[KEY_P])
      *MarcTeclGeneProg=0;
}

/******************************************************************************
  CargaBitmap: Función de Carga de un BITMAP
******************************************************************************/

void CargaBitmap(BITMAP **Imag, char Archivo[]) //la ruta de los archivos se debe incluir sin el .bmp y sin el número de versión
{
   char NombArch[50];

   sprintf(NombArch, "%d%s.bmp", VersionJuego, Archivo); //Crea el Nombre de Archivo
   *Imag=NULL;
   *Imag=load_bitmap(NombArch, NULL); //Carga la imagen
   if(!*Imag)
   {
      allegro_message("Error al cargar el archivo %s", NombArch);
      exit(1);
   }
}

/******************************************************************************
  CargaMidi: Función de Carga de un MIDI
******************************************************************************/

void CargaMidi(MIDI **Midi, char Archivo[]) //la ruta de los archivos se debe incluir sin el .mid y sin el número de versión
{
   char NombArch[50];

   sprintf(NombArch, "%d%s.mid", VersionJuego, Archivo); //Crea el Nombre de Archivo
   *Midi=NULL;
   *Midi=load_midi(NombArch); //Carga el MIDI
   if(!*Midi)
      allegro_message("Error al cargar el archivo %s", NombArch);
}

/******************************************************************************
  CargaSecuenciaBMP: Procedimiento de Carga de BMP's en un Vector de BITMAP's
******************************************************************************/

void CargaSecuenciaBMP(BITMAP *Imag[], char ArchivoConRuta[], int Maxi) //la ruta de los archivos se debe incluir sin el .bmp
{
   char NombArch[50];
   
   for(int i=0; i<Maxi; i++)
   {
      sprintf(NombArch, "%s%d", ArchivoConRuta, i); //Crea los Nombres Archivo1.bmp, Archivo2.bmp, Archivoi.bmp...
      CargaBitmap(&Imag[i], NombArch); //Carga las Imagenes correspondientes
   }
}

/******************************************************************************
  CargaWav: Función de Carga de un SAMPLE WAV
******************************************************************************/

void CargaWav(SAMPLE **Soni, char Archivo[]) //la ruta de los archivos se debe incluir sin el .wav y sin el número de versión
{
   char NombArch[50];

   sprintf(NombArch, "%d%s.wav", VersionJuego, Archivo); //Crea el Nombre de Archivo
   *Soni=NULL;
   *Soni=load_wav(NombArch); //Carga el WAV
   if(!*Soni)
      allegro_message("Error al cargar el archivo %s", NombArch);
}

/******************************************************************************
  ColisionDispBola: Procedimiento para Comprobar la Colisión Disparo-Bola
******************************************************************************/

void ColisionDispBola(TEstrObjtMovi *Bola, int *BolaCont, int BolaMaxi, TEstrDisp Disp[], int *DispCont, int *ColiDispBola, int *MarcMouse1, int NivelJuego)
{
   (*ColiDispBola)=0;   
   for(int i=0 ; i<(*DispCont) && *ColiDispBola==0; i++) //Recorre el vector de Disparos
   {
      for(int j=0; j<(*BolaCont) && *ColiDispBola==0; j++) //Recorre el vector de Bolas y compara
      {
         if (check_pmask_collision(DispMask[Disp[i].Tipo], BolaMask[Bola[j].Tama], Disp[i].Posi.X, Disp[i].Posi.Y, Bola[j].Posi.X, Bola[j].Posi.Y)) 
         {
            MoverVectorDisp(Disp, i, DispCont); //CAMBIAR nombre por borrar disparo o algo asín
            DivisionBola(Bola, BolaCont, BolaMaxi, j);                                                                                               
            (*ColiDispBola)=1;   
         }
      }
   }
   
   if (NivelJuego==3) //Si está activado el modo DIFICIL (el cursor)
   {
      if (mouse_b&1 && *MarcMouse1==0) 
      {
         play_sample(SampDisp[2], 75, 128, 1000, 0);
         for(int j=0; j<(*BolaCont) && (*MarcMouse1)==0; j++) //Recorre el vector de Bolas y compara
         {           
            if (check_pmask_collision(DispMask[2], BolaMask[Bola[j].Tama], mouse_x-DispMask[2]->w/2, mouse_y-DispMask[2]->w/2, Bola[j].Posi.X, Bola[j].Posi.Y))
            {
               DivisionBola(Bola, BolaCont, BolaMaxi, j);
               (*MarcMouse1)=1;
            } 
         }
         (*MarcMouse1)=1;
      }  
      else if (!mouse_b&1) //si se suelta el click
         (*MarcMouse1)=0;  
   }
}
 
/******************************************************************************
  ColisionJugaBola: Procedimiento para Comprobar la Colisión Jugador-Bola
******************************************************************************/

void ColisionJugaBola(TEstrPers *Juga, TEstrObjtMovi *Bola, int BolaCont, int *ColiJugaBola)
{
   for(int i=0; i<BolaCont && (*ColiJugaBola)==0; i++)  //Recorre el Vector de Bolas
   {
           
      (*ColiJugaBola)=0;
      //ESTRUCTURA IF/ELSE PARA QUE SÓLO QUITE UNA VIDA AL PASAR POR "ENCIMA" DEL JUGADOR
      if (check_pmask_collision(Juga->Mask, BolaMask[Bola[i].Tama], Juga->Posi.X, Juga->Posi.Y, Bola[i].Posi.X, Bola[i].Posi.Y))
      {
         play_sample(SampMuerte, 100, 128, 1000, 0);
         if ((*ColiJugaBola)==0)
            Juga->Vida--;                                 
         (*ColiJugaBola)=1;
         Juga->Muert='S'; //Marca como muerto (sale del bucle de juego)
      }
      else
         (*ColiJugaBola)=0; //Cuando se ponga la barrera se debe pasar automaticamente a Muert='N' y ColiJugaBola=0
   }
}

/******************************************************************************
  CompruebaRecord: Función de comprobación de puntuación
******************************************************************************/

int CompruebaRecord(FILE *Fich, TEstrPuntuacion Record, int Modo, int Nivel, int Punt)
{
   fseek (Fich, (((Modo-1)*3)+(Nivel-1))*sizeof(Record), SEEK_SET); //Vamos al registro indicado (Comienza desde 0)

   fread (&Record, sizeof(Record), 1, Fich); //Leemos la puntuación

   return (Record.Puntos);
}

/******************************************************************************
  CompruebaVersionJuego: Procedimiento de comprobación de la versión de juego, meidante la carga de un BMP
******************************************************************************/
int CompruebaVersionJuego()
{
   char NombArch[50]; 
   BITMAP* ImagVers;
    
   sprintf(NombArch, "%d%s.bmp", VersionJuego, "/img/jugador/Juga8"); //Crea el Nombre de Archivo
   ImagVers=NULL;
   ImagVers=load_bitmap(NombArch, NULL); //Carga la imagen
   if(ImagVers)
      return(1);
   else
       return(0);
}

/******************************************************************************
  DivisionBola: Procedimiento para Comprobar la Colisión Disparo-Bola
******************************************************************************/
void DivisionBola(TEstrObjtMovi *Bola, int *BolaCont, int BolaMaxi, int NumeBola)
{
   //Tener en cuenta que si se llega la máximo de bolas (cosa improbable) no se producirá más división!     
   if ((*BolaCont)<BolaMaxi)
   {
      play_sample(SampBolas, 75, 128, 1000, 0);
      Punt=Punt+300/((Bola[NumeBola].Tama)+1); //Aumenta los puntos según el tamaño(IMPORTANTE que 300 sea divisible entre 1,2,3 y 4)
      
      if(Bola[NumeBola].Tama>=1) //Acciones para dividir la bola en 2 más pequeñas
      {
         MoverVectorBola(Bola, NumeBola, *BolaCont);
         Bola[NumeBola].Velo.X=-(Bola[NumeBola+1].Velo.X);
         Bola[NumeBola].Velo.Y=-10;
         Bola[NumeBola+1].Velo.Y=-10;
         Bola[NumeBola].Tama--;
         Bola[NumeBola+1].Tama--;
         (*BolaCont)++;                 
      }
      else //Acciones para borrar la bola, cuando es lo más pequeña posible
      {
         MoverVectorBolaInverso(Bola, NumeBola, *BolaCont);
         (*BolaCont)--;
      }
   }
}     

/******************************************************************************
  EligirModoJuego: Procedimiento de elección de Modo de Juego (tiempo activado/desactivado)
******************************************************************************/

void EligirModoJuego()
{
   int Menu=1;
     
   clear_bitmap(buffer);
   blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);  
  
   textprintf_ex(screen, font, (RESOX/2)-230, (RESOY/2)-50, -1, makecol(0,0,0), "PULSE 1 PARA MODO \"SURVIVOR\" ó 2 PARA MODO \"TIME SURVIVOR\"");
   while (!key[KEY_ESC] && Menu==1) //Esperamos a que pulse 1 ó 2
   {
      if  (key[KEY_1] || key[KEY_1_PAD] || key[KEY_2] || key[KEY_2_PAD])
      {  
         if(key[KEY_1] || key[KEY_1_PAD]) 
         {
            ModoJuego=1;
            textprintf_ex(screen, font, (RESOX/2)-15, (RESOY/2), -1, makecol(0,0,0), "SURVIVOR");
         }
         if(key[KEY_2] || key[KEY_2_PAD])
         {
            ModoJuego=2;
            textprintf_ex(screen, font, (RESOX/2)-30, (RESOY/2), -1, makecol(0,0,0), "TIME SURVIVOR");
         }
         Menu=0;
      }   
   }
   rest(1000);
}

/******************************************************************************
  EligirModoPantalla: Procedimiento de elección de Modo de Pantalla
******************************************************************************/

void EligirModoPantalla()
{
   int Menu=1;
     
   int ModoPant=1;
  
   textprintf_ex(screen, font, (RESOX/2)-230, (RESOY/2)-50, -1, makecol(0,0,0), "PULSE 0 PARA MODO PANTALLA COMPLETA ó 1 PARA MODO VENTANA");
   while (!key[KEY_ESC] && Menu==1) //Esperamos a que pulse 1 ó 0
   {
      if(key[KEY_1] || key[KEY_1_PAD] || key[KEY_0] || key[KEY_0_PAD]) //Cambiamos el Modo
      {
         if(key[KEY_0] || key[KEY_0_PAD])
            ModoPant=1;
         if(key[KEY_1] || key[KEY_1_PAD]) 
            ModoPant=0;
           
         deinit(); //Deinicializamos Allegro
         init(ModoPant); //Inicializamos Allegro con la nueva configuración 
         Menu=0;
      }    
   }
}

/******************************************************************************
  EligirNivelJuego: Procedimiento de elección de Nivel de Juego (arma utilizada)
******************************************************************************/

void EligirNivelJuego(int *NivelJuego, int *DispMaxi)
{  
   int Menu=1;
  
   clear_bitmap(buffer);
   blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
   
   textprintf_ex(screen, font, (RESOX/2)-200, (RESOY/2)-50, -1, makecol(0,0,0), "PULSE 1 PARA FÁCIL ó 2 PARA NORMAL ó 3 PARA DIFÍCIL");
   while (!key[KEY_ESC] && Menu==1) //Esperamos a que pulse 1, 2 ó 3
   {
      if(key[KEY_1] || key[KEY_1_PAD] || key[KEY_2] || key[KEY_2_PAD] || key[KEY_3] || key[KEY_3_PAD]) //Cambiamos el Modo
      {
         if(key[KEY_1] || key[KEY_1_PAD])
         {
            *NivelJuego=1;
            *DispMaxi=2;
            textprintf_ex(screen, font, (RESOX/2)-10, (RESOY/2), -1, makecol(0,0,0), "FÁCIL");
         }
         else if(key[KEY_2] || key[KEY_2_PAD])
         {
            *NivelJuego=2;
            *DispMaxi=8;
            textprintf_ex(screen, font, (RESOX/2)-10, (RESOY/2), -1, makecol(0,0,0), "NORMAL");
         }
         else if(key[KEY_3] || key[KEY_3_PAD])
         {
            *NivelJuego=3;
            textprintf_ex(screen, font, (RESOX/2)-10, (RESOY/2), -1, makecol(0,0,0), "DIFÍCIL");
         }
         Menu=0;
      }       
   }
   rest(1000);
}

/******************************************************************************
  ElegirVersionJuego: Procedimiento de elección de Versión de Juego (carpeta de carga de gráficos y de sonidos)
******************************************************************************/

void ElegirVersionJuego()
{
   int Menu=1;
    
   int AuxPulsa=0;
   BITMAP* JugaVers;
   
   while (!key[KEY_ESC] && Menu==1) //Esperamos a que pulse una opción
   {
      clear_bitmap(buffer); 
      
      if (key[KEY_LEFT] && AuxPulsa==0)
      {
         VersionJuego--;
         if(CompruebaVersionJuego()==0)
            VersionJuego++;
         AuxPulsa=1;     
      }
      else if (key[KEY_RIGHT] && AuxPulsa==0)
      {
         VersionJuego++;
         if(CompruebaVersionJuego()==0)
            VersionJuego--;
         AuxPulsa=1;   
      }
      else if (key[KEY_ENTER] || key[KEY_ENTER_PAD])
           Menu=0;
      else if (!key[KEY_LEFT] && !key[KEY_RIGHT])
         AuxPulsa=0;
        
      CargaBitmap(&JugaVers, "/img/jugador/Juga8");
      draw_sprite(buffer, JugaVers, LimiDere/2-(JugaVers->w)/2, LimiInfe-(JugaVers->h));
      textprintf_ex(buffer, font, (RESOX/2)-250, (RESOY/2)-50, -1, makecol(0,0,0), "ELIJA LA VERSIÓN DE JUEGO MEDIANTE LAS FLECHAS Y PULSE INTRO");
      blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
   }
   rest(1000);
}
/******************************************************************************
  GenerarBolaAleatoriaTiempo: Generación de una Bola según el Tiempo de generación
******************************************************************************/

void GenerarBolaAleatoriaTiempo(TEstrObjtMovi *Bola, int *BolaCont, int BolaMaxi, int SeguGeneBola)
{
   if (*BolaCont<BolaMaxi)
      if (Temp%(SeguGeneBola*1000/VeloTemp)==0) //Genera nueva bola cada SeguGeneBola segundos
         IniciarBola(Bola, BolaCont, -1);    
}

/******************************************************************************
  GenerarBolaAleatoriaTecla: Generación de una Bola según pulses una Tecla
******************************************************************************/

void GenerarBolaAleatoriaTecla(TEstrObjtMovi *Bola, int *BolaCont, int BolaMaxi, int *MarcTeclGeneBola)
{
   if (*BolaCont<BolaMaxi)
   {  
      if (key[KEY_O] && *MarcTeclGeneBola==0)           
      {   
         IniciarBola(Bola, BolaCont, -1);    
         *MarcTeclGeneBola=1;   
      }
      else if (!key[KEY_O])
         *MarcTeclGeneBola=0;  
   }
}

/******************************************************************************
  IniciarBola: Procedimientos de Inicialización de Bola (Tama -1 para tamaño aleatorio)
******************************************************************************/

void IniciarBola(TEstrObjtMovi *Bola, int *BolaCont, int Tama)
{   
   if (Tama>=0 && Tama <=3)                        
      Bola[*BolaCont].Tama=3;
   else
      Bola[*BolaCont].Tama=Random(1, 3);
   Bola[*BolaCont].Posi.X=Random(LimiIzqd, LimiDere-(BolaBmp[Bola[*BolaCont].Tama]->w)); //50 sería correcto
   Bola[*BolaCont].Posi.Y=Random(LimiSupe+25, LimiInfe-175-BolaBmp[Bola[*BolaCont].Tama]->h); //50 sería correcto
   if (Random(0,1)==0)
      Bola[*BolaCont].Velo.X=5;
   else
      Bola[*BolaCont].Velo.X=-5;  
   Bola[*BolaCont].Velo.Y=-5; //negativo, para que suba un poco al aparecer
   Bola[*BolaCont].Acel.X=0;
   Bola[*BolaCont].Acel.Y=1;
   (*BolaCont)++;
      
}

/******************************************************************************
  IniciarBmpMascaras: Procedimiento de Inicialización de las Máscaras y BMP's
******************************************************************************/

void IniciarBmpMascaras(TEstrPers *Juga)
{
   CargaBitmap(&Juga->MaskBmp, "/img/jugador/Juga4"); 
   Juga->BmpActu = Juga->MaskBmp;
   Juga->Mask = create_allegro_pmask(Juga->MaskBmp); 
   
   CargaSecuenciaBMP(BolaBmp, "/img/bolas/Bola", 4); //Carga los BMP Bola
   BolaMask[0] = create_allegro_pmask(BolaBmp[0]);
   BolaMask[1] = create_allegro_pmask(BolaBmp[1]);
   BolaMask[2] = create_allegro_pmask(BolaBmp[2]);
   BolaMask[3] = create_allegro_pmask(BolaBmp[3]);
   
   CargaSecuenciaBMP(DispBmp, "/img/armas/Disparo", 3); 
   BITMAP* Disp2MaskBmp;
   CargaBitmap(&Disp2MaskBmp, "/img/armas/Disparo2Mascara");
   DispMask[0] = create_allegro_pmask(DispBmp[0]);   
   DispMask[1] = create_allegro_pmask(DispBmp[1]);
   DispMask[2] = create_allegro_pmask(Disp2MaskBmp);
   
   CargaSecuenciaBMP(DispCuadroBmp, "/img/armas/DisparoCuadro", 3);
}
/******************************************************************************
  IniciarJuego: Procedimiento de Inicio del Juego (y muestra de mensajes iniciales)
******************************************************************************/

void IniciarJuego(TEstrPers *Juga, int *MensActu)
{
         if (Temp*VeloTemp/1000==3) //En el segundo 2
         {
            if(ModoJuego==1) //Reproduce la música
               play_midi(musica, TRUE);                 
            else
               play_midi(musica, FALSE);                  
         }           
         MostrarMensajesIniciales(Juga, MensActu); //Muestra los mensajes de "preparado" y "ya"
}

/******************************************************************************
  IniciarJugador: Procedimientos de Inicialización del Jugador
******************************************************************************/

void IniciarJugador(TEstrPers *Juga)
{
  //las posiciones (PosiX, PosiY) se "reinicializan" más adelante 
  Juga->Posi.X=0;
  Juga->Posi.Y=0;
  Juga->Velo.X=10;
  Juga->Velo.Y=0;
  Juga->Acel.X=0;
  Juga->Acel.Y=0; 
  Juga->Muert='S';
  Juga->Vida=-1; 
  Juga->ImagLong=9;     
  strcpy(Juga->ArchivoConRuta, "/img/jugador/Juga");
  Juga->ImagMarc=0;
  Juga->VeloFrame=5;
}

/******************************************************************************
  ModificarRetardo: Función de Aumento/Disminución del Retardo al pulsar + ó -
******************************************************************************/

void ModificarRetardo()
{
   if (key[KEY_PLUS_PAD])
   {   
      Reta-=0.5;
      if (Reta <= 0) //Pone como límite el 0, inclusive
         Reta=0;
   } 
   if (key[KEY_MINUS_PAD])
      Reta+=0.5;
}

/******************************************************************************
  MostrarMensajesIniciales: Muestra los mensajes de PREPARADO y ¡YA!
******************************************************************************/

void MostrarMensajesIniciales(TEstrPers *Juga, int *MensActu)
{     
      if (Temp*VeloTemp/1000<1) //El primer segundo       
         *MensActu=1; //Muestra el mensaje de "PREPARADO"
      if (Temp*VeloTemp/1000>=1 && Temp*VeloTemp/1000<3) //En el segundo 1-2                            
      {     
          
         if (Temp%10>=0 && Temp%10<5) //Intermitentemente
            *MensActu=2; //Muestra el mensaje de "YA"
         else
            *MensActu=0;                                                        
      }
      if (Temp*VeloTemp/1000==3) //En el segundo 2
      {
         Juga->Muert='N'; //Comienza el juego
         Juga->Vida=3;                                                           
         *MensActu=0;
         Temp=1;                          
      }                                
}

/******************************************************************************
  MostrarParametros: Procedimiento de Muestra de Textos
******************************************************************************/

void MostrarParametros(TEstrPers Juga, int ColiJugaBola, int ColiDispBola, int MarcMouse1, 
                    int Vida, int DispCont, int BolaCont, int SeguGeneBola, int NivelJuego)
{  
   if (ModoProg==1)
   {
      textprintf_ex(buffer, font, 100, 10, -1, makecol(0,0,0), "Jugador X %3d  Y %3d", Juga.Posi.X, Juga.Posi.Y);
      textprintf_ex(buffer, font, 100, 20, -1, makecol(0,0,0), "Cursor X %3d  Y %3d", mouse_x, mouse_y);		 
      textprintf_ex(buffer, font, 100, 40, -1, makecol(0,0,0), "ColiJugaBola %d", ColiJugaBola);
      textprintf_ex(buffer, font, 100, 50, -1, makecol(0,0,0), "ColiDispBola %d", ColiDispBola);
      textprintf_ex(buffer, font, 100, 60, -1, makecol(0,0,0), "MarcMouse1 %d", MarcMouse1);
      textprintf_ex(buffer, font, 100, 80, -1, makecol(0,0,0), "Vida %d", Vida);
      textprintf_ex(buffer, font, 100, 90, -1, makecol(0,0,0), "DispCont %d", DispCont);
      textprintf_ex(buffer, font, 100, 100, -1, makecol(0,0,0), "BolaCont %d", BolaCont);
      textprintf_ex(buffer, font, RESOX-250, 10, -1, makecol(0,0,0), "ContGlobal %d", ContGlobal);
      textprintf_ex(buffer, font, RESOX-250, 20, -1, makecol(0,0,0), "Temp %d", Temp);
      textprintf_ex(buffer, font, RESOX-250, 30, -1, makecol(0,0,0), "Tiempo(seg) %d", (Temp*VeloTemp/1000));
      textprintf_ex(buffer, font, RESOX-250, 40, -1, makecol(0,0,0), "Reta %.1f", Reta);
      textprintf_ex(buffer, font, RESOX-250, 60, -1, makecol(0,0,0), "SeguGeneBola %d", SeguGeneBola);     
      textprintf_ex(buffer, font, RESOX-250, 80, -1, makecol(0,0,0), "ModoJuego %d", ModoJuego);
      textprintf_ex(buffer, font, RESOX-250, 90, -1, makecol(0,0,0), "NivelJuego %d", NivelJuego);
   }
}

/******************************************************************************
  MoverBola: Procedimiento de Movimiento de la Bola
******************************************************************************/

void MoverBola(TEstrObjtMovi *Bola, int BolaCont)
{
   for (int i=0; i<BolaCont; i++)
   {
      Bola[i].Velo.X=Bola[i].Velo.X+Bola[i].Acel.X; //Cambia las velocidades y posiciones
      Bola[i].Velo.Y=Bola[i].Velo.Y+Bola[i].Acel.Y;
      Bola[i].Posi.X=Bola[i].Posi.X+Bola[i].Velo.X;
      Bola[i].Posi.Y=Bola[i].Posi.Y+Bola[i].Velo.Y;
    
      if(Bola[i].Posi.X<LimiIzqd || Bola[i].Posi.X>LimiDere-(BolaBmp[Bola[i].Tama]->w)) //Considera límites
      {
         Bola[i].Velo.X=-Bola[i].Velo.X;
         if(Bola[i].Posi.X<LimiIzqd)
            Bola[i].Posi.X=LimiIzqd;
         if(Bola[i].Posi.X>LimiDere-(BolaBmp[Bola[i].Tama]->w))
            Bola[i].Posi.X=LimiDere-(BolaBmp[Bola[i].Tama]->w);
      }

      if(Bola[i].Posi.Y<LimiSupe || Bola[i].Posi.Y>LimiInfe-(BolaBmp[Bola[i].Tama]->h)) //Considera límites
      {
      Bola[i].Velo.Y=-Bola[i].Velo.Y;
      if(Bola[i].Posi.Y<LimiSupe)
         Bola[i].Posi.Y=LimiSupe;
      if(Bola[i].Posi.Y>LimiInfe-(BolaBmp[Bola[i].Tama]->h))
         Bola[i].Posi.Y=LimiInfe-(BolaBmp[Bola[i].Tama]->h);
      }
   }     
}

/******************************************************************************
  MoverDisparos: Procedimiento para Mover los Disparos de Posición
******************************************************************************/

void MoverDisparos(TEstrDisp Disp[], int *DispCont, int DispVeloX, int DispVeloY)
{
   for(int i=0 ; i<(*DispCont) ; i++) //Mueve de posición los disparos
   {
      Disp[i].Posi.Y=Disp[i].Posi.Y-DispVeloY;
      if(Disp[i].Posi.Y<LimiSupe)
         MoverVectorDisp(Disp, i, DispCont); //Si sale de pantalla, lo quita del vector                   
   }
}

/******************************************************************************
  MoverJugador: Procedimiento para Mover el Jugador
******************************************************************************/

void MoverJugador(TEstrPers *Juga, TEstrDisp Disp[], int *DispCont, int DispMaxi, int *NivelJuego, int *MarcTeclSPACE)
{
   clear_to_color(Juga->BmpActu, makecol(255,0,255)); //Limpiamos el BMP del jugador actual
      
   if (key[KEY_LEFT] || key[KEY_A]) 
   {
      if (Juga->Posi.X > LimiIzqd) //Mueve el jugador
         Juga->Posi.X=Juga->Posi.X-Juga->Velo.X;                       
      draw_sprite_h_flip(Juga->BmpActu,Juga->Imag[Juga->ImagMarc],0,0);
      if (ContGlobal%Juga->VeloFrame==0) //Cambia el sprite del jugador dependiendo de la secuencia global
         AumentarContador(&Juga->ImagMarc, 4);  
   }
   else if (key[KEY_RIGHT] || key[KEY_D]) 
   {
      if (Juga->Posi.X < LimiDere-(Juga->Imag[0]->w)) //Mueve el jugador 
         Juga->Posi.X=Juga->Posi.X+Juga->Velo.X;  
      draw_sprite(Juga->BmpActu,Juga->Imag[Juga->ImagMarc],0,0);
      if (ContGlobal%Juga->VeloFrame==0) //Cambia el sprite del jugador dependiendo de la secuencia global
         AumentarContador(&Juga->ImagMarc, 4);
   }
   else
   {
      Juga->ImagMarc=0;  
      if (key[KEY_SPACE] && (*MarcTeclSPACE)==0 && (*DispCont)<DispMaxi && (*NivelJuego==1 || *NivelJuego==2)) 
      {
            Disp[(*DispCont)].Tipo=(*NivelJuego)-1;
            Disp[(*DispCont)].Posi.X=Juga->Posi.X+(Juga->Imag[0]->w)/2-(DispBmp[Disp[(*DispCont)].Tipo]->w)/2;
            Disp[(*DispCont)].Posi.Y=Juga->Posi.Y;
            
            play_sample(SampDisp[*NivelJuego-1], 100, 128, 1000, 0);              
            (*DispCont)++;  //MARCAR EL LÍMITE DE MÁXIMO
            draw_sprite(Juga->BmpActu,Juga->Imag[5],0,0);
            (*MarcTeclSPACE)=1;
      }
      else 
      {
         draw_sprite(Juga->BmpActu,Juga->Imag[4],0,0);
         if (!key[KEY_SPACE])
            (*MarcTeclSPACE)=0; 
      }
   } 
}

/******************************************************************************
  MoverVectorBola: Procedimiento para Mover el Vector de las Bolas
******************************************************************************/

void MoverVectorBola(TEstrObjtMovi Bola[], int BolaMini, int BolaCont)
{
   for (int j=BolaCont; j>BolaMini; j--) //"Crea" un espacio en el vector (a la derecha del actual)
   {      
      Bola[j]=Bola[j-1];
   }                      
}

/******************************************************************************
  MoverVectorBolaInverso: Procedimiento para Mover el Vector de las Bolas a la Inversa
******************************************************************************/

void MoverVectorBolaInverso(TEstrObjtMovi Bola[], int BolaMini, int BolaCont)
{
   for (int j=BolaMini; j<BolaCont; j++) //"Borra" el espacio del vector
   {      
      Bola[j]=Bola[j+1];
   }                      
}

/******************************************************************************
  MoverVectorDisp: Procedimiento para Mover el Vector de los Disparos
******************************************************************************/

void MoverVectorDisp(TEstrDisp Disp[], int Mini, int *Maxi)
{
   for (int j=Mini; j<(*Maxi)-1; j++) //Adelanta todo el vector una posición
   {      
      Disp[j].Posi.X=Disp[j+1].Posi.X;
      Disp[j].Posi.Y=Disp[j+1].Posi.Y;
      Disp[j].Tipo=Disp[j+1].Tipo;
   }
   (*Maxi)--;                       
}

/******************************************************************************
  PintarBolas: Procedimiento para Pintar las Bolas
******************************************************************************/

void PintarBolas(TEstrObjtMovi *Bola, int BolaCont)
{
   if (ModoProg==0)
      for(int i=0; i<BolaCont; i++) //Pintado del Vector Bola
         draw_sprite(buffer,BolaBmp[Bola[i].Tama],Bola[i].Posi.X,Bola[i].Posi.Y);
  else
     for(int i=0; i<BolaCont; i++) //Pintado del Vector Bola como Máscara   
        draw_allegro_pmask ( BolaMask[Bola[i].Tama], buffer, Bola[i].Posi.X, Bola[i].Posi.Y, makecol(255,255,255));   
}

/******************************************************************************
  PintarDisparos: Procedimiento para Pintar los Disparos
******************************************************************************/

void PintarDisparos(TEstrDisp Disp[], int DispCont)
{
   if (ModoProg==0)  
      for(int i=0 ; i<DispCont ; i++) //Pintado del Vector Disparo
         draw_sprite(buffer,DispBmp[Disp[i].Tipo],Disp[i].Posi.X,Disp[i].Posi.Y);
   else
      for(int i=0 ; i<DispCont ; i++) //Pintado del vector Disparo como máscara
         draw_allegro_pmask ( DispMask[Disp[i].Tipo], buffer, Disp[i].Posi.X, Disp[i].Posi.Y, makecol(255,255,255));
   
   rectfill(buffer, 0, LimiInfe+2, RESOX, RESOY, makecol(0,0,0));               //Borra el sobrante de la flecha por abajo   
}

/******************************************************************************
  PintarFondo: Procedimiento de Pintado del Fondo
******************************************************************************/

void PintarFondo(TEstrPers *Juga, int VeloFondoFrame, int *ImagFondoMarc, int ImagFondoLong, BITMAP *ImagFondo[])
{
   if (ModoProg==0)
   {   
      if (Juga->Vida>0 && Tiempo>0)
         if (ContGlobal%VeloFondoFrame==0) //Cambia de Fondo según la secuencia del contador global
            AumentarContador(ImagFondoMarc, ImagFondoLong);
      fondo = ImagFondo[*ImagFondoMarc];
      stretch_blit(fondo,buffer, 0, 0, 320, 240, 0, 0, RESOX, RESOY);
   }
}

/******************************************************************************
  PintarJugador: Procedimiento de Pintado del Jugador
******************************************************************************/

void PintarJugador(TEstrPers *Juga)
{
   if (ModoProg==0)
      draw_sprite(buffer,Juga->BmpActu,Juga->Posi.X,Juga->Posi.Y);                            
   else
      draw_allegro_pmask (Juga->Mask, buffer, Juga->Posi.X, Juga->Posi.Y, makecol(255,255,255));
}

/******************************************************************************
  PintarMensajes: Procedimiento de Pintado de Mensajes de Juego
******************************************************************************/

void PintarMensajes(TEstrPers Juga, int PuntRecord)
{  
   textprintf_ex(buffer, font, 100, RESOY-30, -1, makecol(0,0,0), "Puntos %d", Punt);
   textprintf_ex(buffer, font, 100, RESOY-20, -1, makecol(0,0,0), "Record %d", PuntRecord);   
     
   if (Juga.Vida==-1)   
      textprintf_ex(buffer, font, RESOX-200, RESOY-30, -1, makecol(0,0,0), "Vidas 3");
   else
      textprintf_ex(buffer, font, RESOX-200, RESOY-30, -1, makecol(0,0,0), "Vidas %d", Juga.Vida);
   if (ModoJuego==2)
   {   
      if (Juga.Muert=='S' && Juga.Vida==-1)          
         textprintf_ex(buffer, font, RESOX-200, RESOY-20, -1, makecol(0,0,0), "Tiempo %d", TiempoMax); 
      else 
         textprintf_ex(buffer, font, RESOX-200, RESOY-20, -1, makecol(0,0,0), "Tiempo %d", Tiempo); 
   }          
}

/******************************************************************************
  PintarMouse: Procedimiento de Pintado del Mouse
******************************************************************************/

void PintarMouse(int NivelJuego)
{  
   if(NivelJuego==3)    
   {
      draw_sprite(buffer, DispBmp[2], mouse_x, mouse_y);
      if (ModoProg==1)   
         draw_allegro_pmask (DispMask[2], buffer, mouse_x, mouse_y, makecol(255,255,255)); //máscara del mouse
   }
}

/******************************************************************************
  PintarSprite: Procedimiento para Pintar un Sprite cuando NO se active el modo Programador
******************************************************************************/

void PintarSprite(BITMAP *Imagen, int PosiX, int PosiY)
{
   if (ModoProg==0)
      draw_sprite(buffer, Imagen, PosiX, PosiY);
}   

/******************************************************************************
  Random: Función de Aleatorio entre 2 Límites (ambos inclusive)
******************************************************************************/

int Random(int LimiInfe, int LimiSupe) 
{
   return ((rand()%(LimiSupe-LimiInfe+1))+LimiInfe);   
}

/******************************************************************************
  ReiniciarJuego: Procedimiento de Reinicio del Juego
******************************************************************************/

void ReiniciarJuego(TEstrPers *Juga, TEstrObjtMovi *Bola, int *BolaCont, int BolaMaxi, int *SeguGeneBola, int *DispCont, int *ColiJugaBola, int *MensActu)
{     
   *MensActu=3;                                                            //Muestra mensaje de "MUERTO"
   clear_to_color(Juga->BmpActu, makecol(255,0,255)); //Pinta al jugador en la posición inicial
   draw_sprite(Juga->BmpActu,Juga->Imag[7],0,0);
   
   ContReinicio++;      
   if (ContReinicio%(2*1000/VeloTemp)==0)  //A los 2 segundos
   {
      ContReinicio=0;
      
      Juga->Muert='N'; //Permite entrar en el bucle del juego
      (*BolaCont)=0;  //Lo reinicia todo
      IniciarBola(Bola, BolaCont, 3);
      Juga->Posi.X=LimiDere/2-(Juga->Imag[0]->w)/2, Juga->Posi.Y=LimiInfe-(Juga->Imag[0]->h);
      clear_to_color(Juga->BmpActu, makecol(255,0,255)); //Pinta al jugador en la posición inicial
      draw_sprite(Juga->BmpActu,Juga->Imag[8],0,0);   
      *DispCont=0;
      *ColiJugaBola=0;
      *MensActu=0;
      *SeguGeneBola=10; 
   } 
   
   Tiempo=TiempoMax-(Temp*VeloTemp/1000); //Sigue calculando el tiempo restante       
}

/******************************************************************************
  Temporizador: Incremento (automático e independiente) del Temporizador
******************************************************************************/

void Temporizador()
{
   AumentarContador(&Temp, INT_MAX);
}

/******************************************************************************
  TerminarJuego: Procedimiento de Finalización del Juego
******************************************************************************/

void TerminarJuego(TEstrPers *Juga, TEstrObjtMovi *Bola, int *BolaCont, int BolaMaxi, int *SeguGeneBola, int *DispCont, int *ColiJugaBola, int *MensActu, int *NivelJuego, int *DispMaxi, char NombFich[], TEstrPuntuacion Record, int *PuntRecord)
{
   play_midi(NULL, FALSE); //Para la música
   ActualizaFichero(NombFich, Record, ModoJuego, *NivelJuego, Punt); //Actualiza el fichero de Record
   ActualizaRecord(NombFich, Record, ModoJuego, *NivelJuego, Punt, PuntRecord);
   if (Juga->Vida==0)
   {                                                      
      clear_to_color(Juga->BmpActu, makecol(255,0,255)); //Pinta al jugador en la posición inicial
      draw_sprite(Juga->BmpActu,Juga->Imag[7],0,0);
      *MensActu=4; //Muestra mensaje de "GAME OVER"                                      
   }
   else if (Tiempo==0)
   { 
      clear_to_color(Juga->BmpActu, makecol(255,0,255)); //Pinta al jugador en la posición inicial
      draw_sprite(Juga->BmpActu,Juga->Imag[6],0,0);         
      *MensActu=5; ////Muestra mensaje de "TIME OUT"
   }  
     
   if (key[KEY_ENTER] || key[KEY_ENTER_PAD] || key[KEY_R]) //Espera que pulse la tecla correspondiente
   {
      if (key[KEY_R]) //Si pulsa reiniciar
      {                
         EligirModoJuego();
         EligirNivelJuego(NivelJuego, DispMaxi);
      }
      
      ActualizaRecord(NombFich, Record, ModoJuego, *NivelJuego, Punt, PuntRecord);
      Juga->Vida=-1; //permite entrar en la "intro"           
      (*BolaCont)=0;  //Lo reinicia todo
      IniciarBola(Bola, BolaCont, 3);      
      Juga->Posi.X=LimiDere/2-(Juga->Imag[0]->w)/2, Juga->Posi.Y=LimiInfe-(Juga->Imag[0]->h);
      clear_to_color(Juga->BmpActu, makecol(255,0,255)); //Pinta al jugador en la posición inicial
      draw_sprite(Juga->BmpActu,Juga->Imag[4],0,0);
      *DispCont=0;
      *ColiJugaBola=0;
      Punt=0;
      *MensActu=0;
      *SeguGeneBola=10; 

      Tiempo=TiempoMax;
      Temp=0;          
   }
}


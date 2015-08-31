/******************************************************************************
  Proceso: Procedimiento de Inicializaci�n de Allegro
******************************************************************************/

void init(int Screen) 
{
   int Depth, Reso; //profundidad de color y resoluci�n de pantalla
   int Sound; //sonido DIGI y MIDI
   int music_driver1, music_driver2; //drivers de sonido (DIGI y MIDI)

//Inicializa allegro
   set_uformat (U_ASCII); //establece el formato de codificaci�n de caracteres a ASCII  
   allegro_init();
  
//Sacamos la profundidad de color del escritorio y lo fijamos en nuestro programa
   Depth = desktop_color_depth(); 
   if (Depth == 0) 
   {
      allegro_message("Profundidad de color autom�tico a 32 bits"); 
      Depth = 32;
   }
   set_color_depth(Depth);
  
//Fijamos la resoluci�n de pantalla  
   if (Screen == 1)
      Reso = set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, RESOX, RESOY, 0, 0);
   else
      Reso = set_gfx_mode(GFX_AUTODETECT_WINDOWED, RESOX, RESOY, 0, 0);
   if (Reso != 0) 
   
   {
      allegro_message("Error al iniciar el modo gr�fico (resoluci�n)");
      exit(1);
   }

//Inicializamos el control del teclado
   if(install_keyboard() != 0)
   { 
      allegro_message("Error al instalar el controlador de interrupciones de teclado.");  
      exit(1);
   }
//Inicializamos el control de tiempo   
   if(install_timer() != 0) 
      allegro_message("Error al instalar el controlador de temporizaci�n");
    
//Inicializamos el control del rat�n  
   if(install_mouse() == -1) 
      allegro_message("Error al instalar el controlador del rat�n");
    
//Fijamos los controladores de sonido
   detect_digi_driver(music_driver1);
   detect_midi_driver(music_driver2);
   Sound = install_sound(music_driver1, music_driver2, NULL);
   if (Sound == -1 || music_driver1 == 0 || music_driver2 == 0) 
      allegro_message("Error al cargar los controladores de sonido"); 
   set_volume(150,150); //Volumen de salida del sonido DIGI y MIDI (entre 0 y 255)

//Instalamos el Temporizador
   LOCK_VARIABLE(Temp);
   LOCK_FUNCTION(Temporizador);
   Temp=0;
   install_int(Temporizador, VeloTemp); //que cambie cada VeloTemp/1000 segundos
   TempAux=Temp;
}

/******************************************************************************
  Proceso: Procedimiento de Desinicializaci�n de Allegro
******************************************************************************/

void deinit() 
{
   clear_keybuf();
   allegro_exit(); //Finalizamos Allegro

}

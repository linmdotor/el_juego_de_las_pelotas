/******************************************************************************
  Declaraciones de los módulos, en orden alfabético
******************************************************************************/

int AbrirFichero(FILE **Fich, char Nomb[], char Modo[]);
void ActualizaFichero(FILE *Fich, TEstrPuntuacion Record, int Modo, int Nivel, int Punt);
void ActualizaRecord(FILE *Fich, char NombFich[], TEstrPuntuacion Record, int Modo, int Nivel, int Punt, int *PuntRecord);
void AumentarContador(int *Nume, int Limi);
void CambiarModoDisparo(int *NivelJuego, int *MarcTeclModoDisp, int *DispMaxi);
void CambiarModoProgramador(int *MarcTeclGeneProg);
void CargaBitmap(BITMAP **Imag, char Archivo[]);
void CargaMidi(MIDI **Musi, char Archivo[]);
void CargaSecuenciaBMP(BITMAP *Imag[], char ArchivoConRuta[], int Maxi);
void CargaWav(SAMPLE **Soni, char Archivo[]);
void ColisionDispBola(TEstrObjtMovi *Bola, int *BolaCont, int BolaMaxi, TEstrDisp Disp[], int *DispCont, int *ColiDispBola, int *MarcMouse1, int NivelJuego);
void ColisionJugaBola(TEstrPers *Juga, TEstrObjtMovi *Bola, int BolaCont, int *ColiJugaBola);
int CompruebaRecord(FILE *Fich, TEstrPuntuacion Record, int Modo, int Nivel, int Punt);
int CompruebaVersionJuego();
void DivisionBola(TEstrObjtMovi *Bola, int *BolaCont, int BolaMaxi, int NumeBola);
void EligirModoJuego();
void EligirModoPantalla();
void EligirNivelJuego(int *NivelJuego, int *DispMaxi);
void ElegirVersionJuego();
void GenerarBolaAleatoriaTiempo(TEstrObjtMovi *Bola, int *BolaCont, int BolaMaxi, int SeguGeneBola);
void GenerarBolaAleatoriaTecla(TEstrObjtMovi *Bola, int *BolaCont, int BolaMaxi, int *MarcTeclGeneBola);
void IniciarBola(TEstrObjtMovi *Bola, int *BolaCont, int Tama);
void IniciarBmpMascaras(TEstrPers *Juga);
void IniciarJuego(TEstrPers *Juga, int *MensActu);
void IniciarJugador(TEstrPers *Juga);
void ModificarRetardo();
void MostrarMensajesIniciales(TEstrPers *Juga, int *MensActu);
void MostrarParametros(TEstrPers Juga, int ColiJugaBola, int ColiDispBola, int MarcMouse1, int Vida, int DispCont, int BolaCont, int SeguGeneBola, int NivelJuego);
void MoverBola(TEstrObjtMovi *Bola, int BolaCont);
void MoverDisparos(TEstrDisp Disp[], int *DispCont, int DispVeloX, int DispVeloY);
void MoverJugador(TEstrPers *Juga, TEstrDisp Disp[], int *DispCont, int DispMaxi, int *NivelJuego, int *MarcTeclSPACE);
void MoverVectorBola(TEstrObjtMovi Bola[], int BolaMini, int BolaCont);
void MoverVectorBolaInverso(TEstrObjtMovi Bola[], int BolaMini, int BolaCont);
void MoverVectorDisp(TEstrDisp Disp[], int Mini, int *Maxi);
void PintarBolas(TEstrObjtMovi *Bola, int BolaCont);
void PintarSprite(BITMAP *Imagen, int PosiX, int PosiY);
void PintarDisparos(TEstrDisp Disp[], int DispCont);
void PintarFondo(TEstrPers *Juga, int VeloFondoFrame, int *ImagFondoMarc, int ImagFondoLong, BITMAP *ImagFondo[]);
void PintarJugador(TEstrPers *Juga);
void PintarMensajes(TEstrPers Juga, int PuntRecord);
void PintarMouse(int NivelJuego);
int Random(int LimiInfe, int LimiSupe);
void ReiniciarJuego(TEstrPers *Juga, TEstrObjtMovi *Bola, int *BolaCont, int BolaMaxi, int *SeguGeneBola, int *DispCont, int *ColiJugaBola, int *MensActu);
void Temporizador();
void TerminarJuego(TEstrPers *Juga, TEstrObjtMovi *Bola, int *BolaCont, int BolaMaxi, int *SeguGeneBola, int *DispCont, int *ColiJugaBola, int *MensActu, int *NivelJuego, int *DispMaxi, char NombFich[], TEstrPuntuacion Record, int *PuntRecord);
   


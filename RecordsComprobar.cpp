/*
Autor: Jesús M. Dotor
Proceso: Comprueba todas las puntucaiones
		Definiendo una estructura y rellenando el fichero con Punt=0
*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

typedef struct EstrPuntuacion
{
   int Modo;
   int Nivel;
   int Puntos;
}TEstrPuntuacion;

int main(void)
{

FILE *Fichero;
TEstrPuntuacion Record;


/* Abrimos el fichero */
printf("\nAbriendo fichero...\n");
Fichero = NULL;
Fichero = fopen("Records.dat", "rb"); //Modo de lectura

/* Calculamos el número de registros creados */
printf("\nCalculando numero de registros...\n");
fseek(Fichero, 0, SEEK_END);
int NumeRegistros = ftell(Fichero)/sizeof(Record);

/* Y los imprimimos */
for(int i=0; i<NumeRegistros; i++)  
{
	fseek (Fichero, i*sizeof(Record), SEEK_SET);

	printf("\nMostrando registro %d...\n", i);
	fread (&Record, sizeof(Record), 1, Fichero);
	printf ("Modo = %d\n", Record.Modo);
	printf ("Nivel = %d\n", Record.Nivel);
	printf ("Puntuacion = %d\n", Record.Puntos);

}

/* Cerramos el fichero */
printf("\nCerrando fichero...\n");
fclose(Fichero);

getch();
}

/*
Autor: Jesús M. Dotor
Proceso: Reinicia todas las puntucaiones
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
Fichero = fopen("Records.dat", "w+b"); //Modo de escritura y lectura (con creación de nuevo fichero)

/* Iniciando el fichero */
printf("\nReiniciando fichero...\n");
for (int i=1; i<=2; i++)
	for (int j=1; j<=3; j++)
	{
   	Record.Modo=i;
   	Record.Nivel=j;
      Record.Puntos=0;
   	/* El tamaño es sizeof(dato) y escribimos un registro */
   	fwrite (&Record, sizeof(Record), 1, Fichero);
	}

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

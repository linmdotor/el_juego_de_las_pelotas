# El juego de las pelotas

![Screenshot1](\screenshots\screen_01.png)
![Screenshot2](\screenshots\screen_02.png)
![Screenshot3](\screenshots\screen_03.png)
![ScreenshotProgrammerMode](\screenshots\screen_ProgrammerMode.png)

Cómo Jugar
==========

1º Ejecutar el archivo "El Juego de las Pelotas.exe" y seguir las instrucciones.

2º Teclas
   ------

- ESCAPE - Mantén pulsado para salir del juego en cualquier momento
- ESPACIO - Disparar en modos Fácil y Normal (es necesario estar parado)
- CLICK IZQDO - Disparar en modo Difícil
- TECLAS DIRECCIÓN - Movimiento del personaje
- 'A' y 'D' - Movimiento del personaje

- 'I' - Cambiar de arma
- 'o' - Generar nuevas bolas
- 'P' - Activar Modo Programador (muestra las máscaras y estado de variables)
- '-' y '+' - Disminuye o aumenta la velocidad de juego, exceptuando el tiempo. 

	Estas 4 últimas teclas se pueden desactivar comentando 4 líneas del
	código, dentro del main:
		GenerarBolaAleatoriaTecla()
		CambiarModoDisparo()
		CambiarModoProgramador()
		ModificarRetardo()

Modos de Juego
============== 

El juego tiene a elegir 6 modos de juego:

- Survivor - Sin límite de tiempo, hasta que se acaben las 3 vidas disponibles
- Time Survivor - Con límite de tiempo 2 min. y límite de 3 vidas

- Fácil - Emplea el tipo de disparo similar a una cuerda (límite de 2)
- Normal - Emplea el tipo de disparo similar a balas (límite de 8)
- Difícil - Emplea el cursor y click izquierdo como disparo 

Records
=======

Los records de juego se guardan en el fichero Records.dat (no modificar)
Existe un record por cada combinación de módo de juego.
Si al final del juego se supera el record, este será actualizado.

Hay 2 programas, que pueden ser ejecutados, externos al juego:
 
RecordsComprobar.exe
--------------------
Comprueba y muestra por pantalla todos los record actuales

RecordsReiniciar.exe
--------------------
Crea de nuevo, con todos los valores a 0, el archivo "Records.dat"
Osea, reinicia a 0 todos los records.

Modificación del Juego
====================== 

El juego está creado para que sea posible jugar con cualquier sprite o música
creado por el usuario.

Para agregar nuevas versiones de juego no se tiene más que agregar una carpeta
cuyo nombre sea el siguiente número teniendo en cuenta las carpetas ya creadas.
Dentro, los archivos deben conservar el mismo nombre de archivo que el original,

Para ello copie cualquiera de las carpetas con número y modifique lo que desee.
Luego cambiele el nombre al siguiente número en la serie.
¡Aparecerá automáticamente en el menú de inicio!

------------------------------------
Lin M. Dotor © 2010

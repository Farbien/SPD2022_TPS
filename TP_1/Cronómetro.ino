


/******************************************************************************

           **       *****      *****
         ******     *******    *******
         **  **     **   **    **    ** 
          **        **  ***    **    **
           **       ******     **    **
            **      ***        **    **
         **  **     ***        **    **
         ******     ***        *******
           **       ***        *****
 



                UNIVERSIDAD TECNOLOGICA NACIONAL
                Facultad Regional Avellaneda
                Tecnicatura Superior en Programación
                
        Asignatura: Sistema de Procesamiento de Datos.
        
        Grupo: Eleven
        Alumnos: 
        - Chirdo, Nicolas Andres           nchirdo@hotmail.com
        - Días, Orlando                    ojose89@gmail.com
        - Fernandez, Florencia             florenciafernandezasconape@gmail.com
        - jiménez, Matías
        Division: 1 F
                ---- Primer cuatrimestre 2022 ----
        
        Fecha de entrega 04/05/2022

******************************************************************************/





/*
 *	Trabajo Práctico 1: Cronómetro Binario
 *
 *	Al iniciar la simulacion, todos los led deben comenzar apagados.
 *	Cada 1 segundo que transcurra, se deben encender los led
 *	de acuerdo al numero que representan.
 *
 *	Ejemplo:
 *   
 *	El numero 15 (0000001111) se representaria encendiendo los 
 *	leds AMARILLO y NARANJA.
 *	Al pasar al numero 16 (0000010000), se deben apagar todos 
 *	los led anteriores y encenderse uno de los leds VERDES. 
 *	Notese, en el ejemplo los 0 representan los led apagados 
 *	y los 1 los led encendidos). 
 *   
 *	-------------------------------------------------------
 *   
 *	Al presionarse el boton START, debe iniciar el cronometro.
 *	Volver a presionarlo hace que la secuencia se detenga. 
 *  (Como si se hubiese presionado pausa).
 *	Al presionarse el boton RESET, el cronometro
 *	debe reiniciarse y arrancar de 0.
 *
 *	Tip: Modularizar la función que controla el encendido de los 
 *	LEDS y de ser posible, todo el código para evitar repetir lineas lo mas posible.
 *  Usar millis para controlar el tiempo del contador para que el cambio de los 
 *	leds encendidos sea perceptible para el ojo humano y 
 *	documentar cada función creada en el código. 
 *	Un breve comentario que diga que es lo que hace esa función
 *  y de corresponder, que retorna).
      UNIVERSIDAD TECNOLOGICA NACIONAL
                Facultad Regional Avellaneda
                Tecnicatura Superior en Programación
                
        Asignatura: Sistema de Procesamiento de Datos.
        
        Grupo: Eleven
        Alumnos: 
        - Chirdo, Nicolas Andres
        - Díaz, Orlando
        - Fernández, Florencia
        - jiménez, Matías
        Division: 1 F
                ---- Primer cuatrimestre 2022 ----
        
        Fecha de entrega 04/05/2022
*/

//--- Defines ---//
#define PRIMER_LED 4			//? First pin of the leds
#define ULTIMO_LED 13			//? Last pin of the leds
#define INICIO_ITER 0			//? To start the counter from 0
#define FIN_ITER 1023			//! Max amount of secods to show
#define TAM 10
#define BOTON_RESET 2
#define BOTON_PAUSA 3
#define TIME 255				//Secods expresed in miliseconds
//--- End Defines ---//
//\brief configura los pins como salida  
//\param variable PRIMER_LED
//\param variables ULTIMO_LED
//\return esta función simplemente activa los pins sin devolver ningún valor de retorno
void set_pins()
{
	for (int i = PRIMER_LED; i <= ULTIMO_LED; ++i)
	{
		pinMode(i, OUTPUT);
	}
}
//\brief se configuran los pin  2 y 3 de entrada para los botones 
//\param variable son los numeros de los pin 
//\return esta función simplemente  configura los pins sin devolver ningún valor de retorno
void setButton()
{
	pinMode(2, INPUT);
	pinMode(3, INPUT);
}
//\brief se inician las funciones set_pins y setButton
//\param variable son las funciones set_pins() y setButton();
//\return  no  devuelve ningún valor de retorno 
void setup()
{
	Serial.begin(9600);
	set_pins();
	setButton();
}

//Variables area

long int contador = INICIO_ITER;
int arrayEnteros[TAM];
short boton_antes = LOW;
short boton_antes2 = LOW;
short flagReset = HIGH;
int ultimoIndice = TAM - 1;
short flagPausa=HIGH;


unsigned long millis_antes = 0;

// Funciones
//\brief se inicializa el tamaño del indice  array 
//\paramint array[]
//\return  no  devuelve ningún valor de retorno 

void InicializarArray(int array[])
{
	for (int i = 0; i <= ultimoIndice; ++i)
	{
		array[i] = 0;
	}
}
//\brief funcion que el numero de contador de decimal a binario 
//\param contador para sumar vueltas en el cronometro 
//\param int array - se guarda el  resultado del numero binario 
//\return  no  devuelve ningún valor de retorno 
void decimalABinario(long int cont, int array[])
{
	short numeroBin = 0;
	int ultimoIndice = TAM - 1;
	//Solucion de decimal a binario
	while (cont > 0)
	{
		numeroBin = cont % 2;
		cont /= 2;
		array[ultimoIndice] = numeroBin;
		ultimoIndice--;
	}
}
//\brief funcion para iterar leds 
//\param int array[] 
 //\param int ultimo led  
//\return  no  devuelve ningún valor de retorno 
void IterarLeds(int array[], int ultimoIndice)
{
	int primerled = PRIMER_LED, ultimoLed = ULTIMO_LED;

	do
	{
		digitalWrite(primerled, array[ultimoIndice]);
		primerled++;
		ultimoIndice--;
	} while (primerled <= 13);

}
//\brief funcion para  empezar la secuencia  en formato de tiempo  millis 
//\param int array[] 
 //\param int ultimo led  
//\return  no  devuelve ningún valor de retorno
void Secuencia(int array[])
{
	unsigned long millisAhora = millis();
	decimalABinario(contador, array);

	if (millisAhora - millis_antes >= TIME)
	{
		if (flagPausa == HIGH)
		{
			contador++;
			Serial.print(contador - 1);
			Serial.print("   ");
			for (int i = 0; i < TAM; i++)
			{
				Serial.print(arrayEnteros[i]);
			}
			Serial.print("\n");
			IterarLeds(arrayEnteros, ultimoIndice);
			millis_antes = millisAhora;
		}

	}
}
//\brief funcion de boton  para resetear el contador
//\param int array[] 
 //\param int ultimo led  
//\return  no  devuelve ningún valor de retorno
void botonReset()
{
	int boton_ahora = digitalRead(BOTON_RESET);
	// Anti rebote
	if (boton_ahora == HIGH && boton_antes == LOW)
	{
		InicializarArray(arrayEnteros);
		contador=0;
		flagReset = !flagReset;
      	Serial.print("\n \n**** Reseteando ****\n");
	}

	boton_antes = boton_ahora;
}
//\brief funcion de boton  para  pausar el contador
//\param int array[] 
 //\param int ultimo led  
//\return  no  devuelve ningún valor de retorno
void botonPausa()
{
	int boton_ahora2 = digitalRead(BOTON_PAUSA);
	// Anti rebote
	if (boton_ahora2 == HIGH && boton_antes2 == LOW)
	{
		flagPausa= !flagPausa;
      	Serial.print("\n \n**** PAUSA ****\n");
	}

	boton_antes2 = boton_ahora2;
}



/****************************Loop*************************/
//\brief funcion que ejecutara  los comandos de inicilizarArray, Secuencia, boton reset y boton pausa mientras la placa Arduino esté habilitada
//\param funciones de inicilizarArray
//\param funciones de Secuencia
//\param funciones de botonReset
//\param funciones de 	botonPausa
//\return  no  devuelve ningún valor de retorno
void loop()
{
	InicializarArray(arrayEnteros);
	Secuencia(arrayEnteros);
	botonReset();
  	botonPausa();

	delay(7);
}

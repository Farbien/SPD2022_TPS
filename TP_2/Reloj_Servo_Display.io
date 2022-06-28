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
        
        	TRABAJO PRACTICO N° 02: 
            Reloj con servomotores y display LCD
        
        Grupo: Eleven
        Alumnos: 
        - Chirdo, Nicolas Andres           nchirdo@hotmail.com
        - Díaz, Orlando                    ojose89@gmail.com
        - Fernández, Florencia             florenciafernandezasconape@gmail.com
        - jiménez, Matías                  matias.jimenez.0096@gmail.com
        Division: 1 F
                ---- Primer cuatrimestre 2022 ----
        
        Fecha de entrega 29/06/2022

******************************************************************************/

#define TIME 1000
#define NO_BOTON 0
#define BOTON_SEG  1
#define BOTON_MIN  2
#define BOTON_HORA 3
#define BOTON_PAUSA 4

#include <LiquidCrystal.h>
#include <Servo.h>

//LiquidCrystal(rs, enable, d4, d5, d6, d7)

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
Servo servo_horas;
Servo servo_min;
Servo servo_seg;


    /****************************PROTOTIPOS*************************/
void ImprimirSegundos();
void ImprimirMinutos();
void ImprimirHoras();

int LeerBoton();
void ImprimirReloj();
void FuncBotones();
void CorrerElTiempo();
void PosicionarServo();

void ImprimirReloj();
/****************************PROTOTIPOS*************************/

void setup()
{
	
	Serial.begin(9600);
	servo_horas.attach(8);
	servo_min.attach(9);
	servo_seg.attach(10);
	lcd.begin(16, 2);
	lcd.print("    Horario");
	lcd.setCursor(4, 1);
	lcd.print("00:00:00");

}
/************************VARIABLES GLOBALES********************/
unsigned long millis_antes = 0;
int flagPausa = HIGH;

//CONTADORES
int contadorSeg = 55;
int contadorMin = 59;
int contadorHora = 23;
//BOTONES
int botonAntes = NO_BOTON;
/************************VARIABLES GLOBALES********************/

/****************************FUNCIONES*************************/

//\Brief funcion para imprimir segundos en el display. 
void ImprimirSegundos()
{
	//seg
	if (contadorSeg > 59)
	{
		contadorSeg = 0;
		contadorMin++;
	}

	if (contadorSeg < 10)
	{
		lcd.setCursor(10, 1);
		lcd.print("0");
		lcd.print(contadorSeg);
	}
	else
	{
		lcd.setCursor(10, 1);
		lcd.print(contadorSeg);

	}
}

//\Brief funcion para imprimir minutos en el display.
void ImprimirMinutos()
{
	//min
	if (contadorMin > 59)
	{
		contadorMin = 0;
		contadorHora++;
	}

	if (contadorMin < 10)
	{
		lcd.setCursor(7, 1);
		lcd.print("0");
		lcd.print(contadorMin);
	}
	else
	{
		lcd.setCursor(7, 1);
		lcd.print(contadorMin);

	}
}

//\Brief funcion para imprimir horas en el display
void ImprimirHoras()
{
	//horas
	if (contadorHora > 23)
	{
		contadorHora = 0;
	}

	if (contadorHora < 10)
	{
		lcd.setCursor(4, 1);
		lcd.print("0");
		lcd.print(contadorHora);
	}
	else
	{
		lcd.setCursor(4, 1);
		lcd.print(contadorHora);
	}
}

//Brief leer el valor analogico de los botones.
//Retorno Retorna el Boton presionado.
int LeerBoton()
{
  int valorA0 = analogRead(A0);
	valorA0 = analogRead(A0);

	if (valorA0 > 502 && valorA0 < 522)
		return BOTON_SEG;

	if (valorA0 > 672 && valorA0 < 692)
		return BOTON_MIN;

	if (valorA0 > 757 && valorA0 < 777)
		return BOTON_HORA;

	if (valorA0 > 808 && valorA0 < 828)
		
		return BOTON_PAUSA;
	

	return NO_BOTON;
}


//\Brief invocar a las funciones que imprimen en eñ display.
void ImprimirReloj()
{
	ImprimirSegundos();
	ImprimirMinutos();
	ImprimirHoras();
}

// Brief asignar funciones al reloj
void FuncBotones()
{
  
	int botonAhora = LeerBoton();

	if (botonAhora != NO_BOTON && botonAhora != botonAntes)
	{
		switch (botonAhora)
		{
		case BOTON_SEG:
			contadorSeg++;
			Serial.println("...::: Segundos ++ :::...");
			break;
		case BOTON_MIN:
			contadorMin++;
			Serial.println("...::: Minutos  ++ :::...");
			break;
		case BOTON_HORA:
			Serial.println("...::: Horas    ++ :::...");
			contadorHora++;
			break;
		case BOTON_PAUSA:
          	if(flagPausa){
				Serial.println("...:::   pausa     :::...");
            }
          else
          {
            Serial.println("...:::   Inicio    :::...");
          }
          	flagPausa=!flagPausa;
			break;
		}
	}
	botonAntes = botonAhora;
}

//Brief Funcion para iniciar tiempo.
void CorrerElTiempo()
{
	
	unsigned long millisAhora = millis();
	if (flagPausa)
	{
		if (millisAhora - millis_antes >= TIME)
		{
			contadorSeg++;
          millis_antes = millisAhora;
		}
	}
}

//Brief Funcion para posicionar los servomotores
void PosicionarServo()
{
	int posicionServoSeg = map(contadorSeg, 0, 59, 180, 0);
	servo_seg.write(posicionServoSeg);

	int posicionServoMin = map(contadorMin, 0, 59, 180, 0);
	servo_min.write(posicionServoMin);

	int posicionServoHoras = map(contadorHora, 0, 23, 180, 0);
	servo_horas.write(posicionServoHoras);
}

/****************************FUNCIONES*************************/

/****************************Loop*************************/
void loop()
{

	PosicionarServo();
	CorrerElTiempo();
	FuncBotones();
	ImprimirReloj();

	delay(7);
}
/****************************Loop*************************/

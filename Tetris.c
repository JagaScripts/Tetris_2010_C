#include <stdio.h>								//Jose Antonio Gonz�lez Alc�ntara
#include <stdlib.h>								//Esther Piqueras Arguisuelas
#include <conio.h>
#include <string.h>
#include "rutines_w.c"
#include "peces.h"
												// DEFINIMOS TODO TIPO DE CONSTANTES
#define TEXTO_PAUSA "JOC PAUSAT"				// PARA EL TEXTO DEL MENSAGE DE PAUSA
#define TEXTO_ESCAPE "GAME OVER"				// PARA EL TEXTO DEL MENSAGE DE SALIDA
#define TECLADO_EXTERNO 224						// PARA LA TECLA QUE DIFERENCIA EL TECLADO EXTERNO
#define TECLA_1 49								// PARA LA TECLA	1
#define TECLA_2 50								//		"			2
#define TECLA_3 51								//		"			3
#define TECLA_4 52								//		"			4		
#define TECLA_S_MINUS 83						//		"			s
#define TECLA_S_MAYUS 115						//		"			S
#define TECLA_ESCAPE 27							// PARA LA TECLA ESCAPE
#define TECLA_P_MAYUSCULA 112					// PARA LA TECLA P MAYUSCULA
#define TECLA_P_MINUSCULA 80					// PARA LA TECLA P MINUSCULA
#define TECLA_FLECHA_DERECHA 77					// PARA LA FLECHA DERECHA
#define TECLA_FLECHA_IZQUIERDA 75				// PARA LA FLECHA IZQUIERDA
#define TECLA_FLECHA_ABAJO 80					// PARA LA FLECHA ABAJO
#define TIEMPO_PIEZA_FINAL 250					// PARA TIEMPO DE MUESTRA DE LA PIEZA ABAJO
#define POSICION_Y_INICIAL_PIEZA 1				// POSICION INICIAL EN Y DE LA PIEZA
#define POSICION_X_INICIAL_PIEZA 9				// POSICION INICIAL X PIEZA
#define NUMERO_DE_PIEZAS 3						// NUMERO DE PIEZAS DIFERENTES POSIBLES
#define PUNTUACION_INICIAL 0					// PUNTUACION INICIAL
#define LIMITE_D_PIEZALYS 16					// LIMITE DERECHO DE LAS PIEZAS L Y S
#define LIMITE_D_PIEZAP 17						// LIMITE DERECHO DE LAS LA PIEZA P
#define LIMITE_I_PIEZAPYS 0						// LIMITE IZQUIERDO DE LAS PIEZAS P Y S
#define LIMITE_I_PIEZAL 1						// LIMITE IZQUIERDO DE LA PIEZA L
#define LIMITES 2
#define LIMITE_IZ 1
#define LIMITE_DER 0
#define INICILIZACION_TECLAPULSADA 0			// INICIALIZACION DE LA TECLA PULSADA POR SI NO PULSAN NINGUNA TECLA
#define NUMERO_BLOQUES_PIEZA_L 3				//										
#define NUMERO_BLOQUES_PIEZA_P 1				//				NUMERO DE BLOQUES
#define NUMERO_BLOQUES_PIEZA_S 2				//	
#define NIVEL_PRINCIPIANTE 1000					//
#define NIVEL_MEDIO 500							//				NIVELES
#define NIVEL_EXPERTO 250						//
#define MAXIMO_JUGADORES 5						
#define MAXIMO_CARACTERES_N 16
#define MAXIMO_CARACTERES_F 11
#define LIMITE_NIVEL_EXPERTO 30
#define LIMITE_NIVEL_MEDIO 15
#define NUM_VIDAS 5
#define ESPACIO 0

typedef struct{				//Definici�n de structura Tipo Jugador
	char Nombre[MAXIMO_CARACTERES_N];
	int Puntuacion;							
	char Fecha[MAXIMO_CARACTERES_F];
}TipoJugador;

//Prototipos de las funciones y procedimientos
void AccederFicheroPuntuaciones(TipoJugador Jugador[MAXIMO_JUGADORES]);
void MenuPuntuaciones(TipoJugador Jugador[MAXIMO_JUGADORES]);
int SeleccionarNivel(int Nivel);
int Jugar(int Nivel);
void InicializarLiniaFinal(int LiniaFinal[NCol]);
int ComprobarEspaciosContinuos(int LiniaFinal[NCol]);
void GenerarPieza(int TipoPieza[NUMERO_DE_PIEZAS],int Pieza[NUMERO_DE_PIEZAS]);
void PonerLimitePieza(int LimitesTablero[LIMITES],int *PosPiezaX,int LimitePiezaDerecho,int LimitePiezaIzquierdo);
int GenerarPiezaAleatoria(int Pieza[NUMERO_DE_PIEZAS],int PosPiezaX,int LimitesTablero[LIMITES],int PiezaPosible);
void ColocarPieza(int Pieza[NUMERO_DE_PIEZAS],int LiniaFinal[NCol],int Posicion);
void CambiarColorTexto(pantalla_t *tauler, int Color);
void ImprimirMenu();
int PreguntaSalir();
void PonerPiezaEnLiniaFinal(int Pieza[NUMERO_DE_PIEZAS],int LiniaFinal[NCol],int Posicion,int *Espacio,int *Puntuacion,int *Vida,int *Tecla);
void DesplazarLiniaFinal(int LiniaFinal[NCol]);
void IniTipoJugador(TipoJugador Jugador[MAXIMO_JUGADORES]);
void EscribirFicheroPuntuaciones(TipoJugador Jugador[MAXIMO_JUGADORES]);
void ConpararMejoresPuntuaciones(TipoJugador Jugador[MAXIMO_JUGADORES],int Puntuacion);
void ControlNivel(int Puntuacion,int *Nivel);

//Procedimiento principal
void main()
{
	int Accion,Nivel=NIVEL_MEDIO,Puntuacion;
	TipoJugador MiJugador[MAXIMO_JUGADORES];
	srand((unsigned)time(NULL));
	AccederFicheroPuntuaciones(MiJugador);
	do
	{
		ImprimirMenu();
		fflush(stdin);									
		Accion=getch();	
		switch(Accion)						//PARA CADA CASO
		{
			case TECLA_1:
				system("cls");
				MenuPuntuaciones(MiJugador);
				system("cls");
				break;
			case TECLA_2:
				system("cls");
				Nivel=SeleccionarNivel(Nivel);
				system("cls");
				break;
			case TECLA_3:
				Puntuacion=Jugar(Nivel);
				ConpararMejoresPuntuaciones(MiJugador,Puntuacion);
				EscribirFicheroPuntuaciones(MiJugador);
				system("cls");
				break;
			case TECLA_4:
				system("cls");
				Accion=PreguntaSalir();
				system("cls");
				break;
			case TECLA_S_MINUS:
			case TECLA_S_MAYUS:
				Accion=0;
				system("cls");
				break;
			default :
				system("cls");
				break;
		}
	}while((Accion!=TECLA_S_MINUS)&&(Accion!=TECLA_S_MAYUS));	
}

//Procedimiento que accede al archivo de puntuaciones si hay y si no lo crea. 
void AccederFicheroPuntuaciones(TipoJugador Jugador[MAXIMO_JUGADORES])
{
int i;
FILE *MejoresPuntuaciones, *MejoresPuntuacionesB;

MejoresPuntuaciones=fopen("MejoresPuntuaciones.txt","r");
	if (MejoresPuntuaciones == NULL)
	{
		printf ("Creant fitxer de puntuacions\n");
		system("cls");
		MejoresPuntuacionesB = fopen ("MejoresPuntuaciones.txt","w");
			if (MejoresPuntuacionesB == NULL)
			{
				printf ("Error obrint el segon fitxer\n");
			}
			else
			{
				IniTipoJugador(Jugador);
				for(i=0;i<MAXIMO_JUGADORES;i++)
				{
					fputs(Jugador[i].Nombre,MejoresPuntuacionesB);
					fputs(Jugador[i].Fecha,MejoresPuntuacionesB);
					fprintf(MejoresPuntuacionesB," %d\n",Jugador[i].Puntuacion);
				}
				fclose (MejoresPuntuacionesB);
			}
	}
	else
	{
			for(i=0;i<MAXIMO_JUGADORES;i++)
			{
				fgets(Jugador[i].Nombre,MAXIMO_CARACTERES_N,MejoresPuntuaciones);
				fgets(Jugador[i].Fecha,MAXIMO_CARACTERES_F,MejoresPuntuaciones);
				fscanf(MejoresPuntuaciones," %d\n",&Jugador[i].Puntuacion);
			}
		fclose (MejoresPuntuaciones);
	}		
}

//Procedimiento que accede al archivo de puntuaciones y muestra en pantalla los resultados.
void MenuPuntuaciones(TipoJugador Jugador[MAXIMO_JUGADORES])
{
int i;
FILE *MejoresPuntuaciones;

	MejoresPuntuaciones=fopen("MejoresPuntuaciones.txt","r");
	printf ("\t\tMIJORS PUNTUACIONS\n\n");
	printf ("NOM DEL JUGADOR\t     DATA\tPUNTUACIO\n\n");
		for(i=0;i<MAXIMO_JUGADORES;i++)
		{
			fgets(Jugador[i].Nombre,MAXIMO_CARACTERES_N,MejoresPuntuaciones);
			fgets(Jugador[i].Fecha,MAXIMO_CARACTERES_F,MejoresPuntuaciones);
			fscanf(MejoresPuntuaciones," %d\n",&Jugador[i].Puntuacion);
			printf("%d.%s %s\t\t%d\n",i+1,Jugador[i].Nombre,Jugador[i].Fecha,Jugador[i].Puntuacion);
		}
	fclose (MejoresPuntuaciones);		
system("PAUSE");
}

//Funci�n que permite cambiar de nivel y devuelve el nivel elegido al menu principal.
int SeleccionarNivel(int Nivel)
{
int Accion;
do
{
	printf("MENU DE NIVELL\n");
	printf("1. Principiant.\n");
	printf("2. Mitja\n");
	printf("3. Expert\n");
	printf("Escull una NIVELL pel TETRIS\n");
	fflush(stdin);									
	Accion=getch();
	switch(Accion)						//PARA CADA CASO
		{
			case TECLA_1:
				Nivel=NIVEL_PRINCIPIANTE;
				system("cls");
				break;
			case TECLA_2:
				Nivel=NIVEL_MEDIO;
				system("cls");
				break;
			case TECLA_3:
				Nivel=NIVEL_EXPERTO;
				system("cls");
				break;
			default :
				system("cls");
				break;
		}
}while((Accion!=TECLA_1)&&(Accion!=TECLA_2)&&(Accion!=TECLA_3));
return Nivel;
}

//Funci�n del juego que necesita un nivel para jugar y devuelve la puntuaci�n.
int Jugar(int Nivel)
{

	int Puntuacion, PosPiezaX, PosPiezaY, TeclaPulsada, Vida = NUM_VIDAS, Espacio = NCol;
	int Pieza[NUMERO_DE_PIEZAS], LimitesTablero[LIMITES], LiniaAbajo[NCol], PiezaPosible; //VECTOR PIEZA QUE PASAREMOS AL PROCEDIMIENTO MostraPesa()
	char Jugador[9] = {"Jugador1"};
	pantalla_t TableroTetris;
	Puntuacion = PUNTUACION_INICIAL;
	PosPiezaY = POSICION_Y_INICIAL_PIEZA;
	PosPiezaX = POSICION_X_INICIAL_PIEZA;
	TeclaPulsada = INICILIZACION_TECLAPULSADA;
	InicializarLiniaFinal(LiniaAbajo);
	InitPantalla(&TableroTetris); //INICIAMOS LA PANTALLA
	MostraTauler(&TableroTetris);
	MostraPartida(&TableroTetris, Jugador, Puntuacion, Vida);
	//DEFINIMOS LA PUNTUACION A CERO

	do //BUCLE REPETIR PRINCIPAL DEL ALGORISMO
	{
		PiezaPosible = ComprobarEspaciosContinuos(LiniaAbajo);
		PosPiezaX = GenerarPiezaAleatoria(Pieza, PosPiezaX, LimitesTablero, PiezaPosible);
		MostraPesa(&TableroTetris, Pieza, PosPiezaY, PosPiezaX);
		MostraLinia(&TableroTetris, LiniaAbajo);
		Sleep(Nivel);
		do
		{
			MostraPesa(&TableroTetris, Pieza, PosPiezaY, PosPiezaX);
			DesplazarLiniaFinal(LiniaAbajo);
			MostraLinia(&TableroTetris, LiniaAbajo);
			Sleep(Nivel);
			while ((_kbhit() != 0) && (TeclaPulsada != TECLA_ESCAPE)) //BUCLE MIENTRAS SECUNDARIO DEL
			{														  //ALGORISMO: REPITE MIENTRAS SE PULSA UNA TECLA QUE NO SEA ESCAPE
				fflush(stdin);										  //LIMPIA EL BUFER DE LAS TECLAS
				TeclaPulsada = getch();								  //ASIGNA EL VALOR DE LA TECLA PULSADA
				switch (TeclaPulsada)								  //PARA CADA CASO SEGUN LA TECLA PULSADA
				{
				case TECLA_P_MAYUSCULA:	
				case TECLA_P_MINUSCULA:
					MostraMSG(&TableroTetris,TEXTO_PAUSA); //SI SE PULSA PAUSE MUESTRA UN MENSAJE
					getch();					   //INTERRUMPE LA EJECUCION	
					system("cls");						   //LIMPIA LA PANTALLA PARA QUE QUEDE MAS BONITO	
					MostraTauler(&TableroTetris);
					MostraPartida(&TableroTetris,Jugador,Puntuacion,Vida);//MUESTRA EL TABLERO DE NUEVO PARA QUE QUEDE MAS BONITO
					break;
				case TECLADO_EXTERNO:					   //SI SE PULSA UNA DE LAS TECLAS DEL TECLADO EXTERNO
					TeclaPulsada=getch();				   //ASIGNA EL SEGUNDO VALOR DEL TECLADO EXTERNO
					switch(TeclaPulsada)				   //PARA CADA CASO SEGUN LA TECLA PULSADA	
					{
						case TECLA_FLECHA_DERECHA:		   //SI SE PULSA FLECHA DERECHA
							if(PosPiezaX<LimitesTablero[LIMITE_DER])  //SI LA PIEZA ESTA DENTRO DEL LIMITE DERECHO
							{
								PosPiezaX=PosPiezaX+1;		//SUMA 1 POSICION HACIA LA DERECHA PARA DESPLAZAR LA PIEZA
								MostraPesa(&TableroTetris,Pieza,PosPiezaY,PosPiezaX);
								MostraLinia(&TableroTetris,LiniaAbajo);
							}
							break;
						case TECLA_FLECHA_IZQUIERDA:	  //SI SE PULSA LA FLECHA IZQUIERDA
							if(PosPiezaX>LimitesTablero[LIMITE_IZ]) //SI LA PIEZA ESTA DENTRO DEL LIMITE IZQUIERDO
							{
								PosPiezaX=PosPiezaX-1;		//RESTA 1 POSICION HACIA LA DERECHA PARA DESPLAZAR LA PIEZA
								MostraPesa(&TableroTetris,Pieza,PosPiezaY,PosPiezaX);
								MostraLinia(&TableroTetris,LiniaAbajo);
							}
							break;
						case TECLA_FLECHA_ABAJO:
							PosPiezaY=NFil-1;
							break;
						default:	
							break;
					}
					break;
				default:
					break;
			}
		}
		PosPiezaY++;		
	}while((PosPiezaY!=NFil)&&(TeclaPulsada!=TECLA_ESCAPE));
		PonerPiezaEnLiniaFinal(Pieza,LiniaAbajo,PosPiezaX,&Espacio,&Puntuacion,&Vida,&TeclaPulsada);
		ControlNivel(Puntuacion,&Nivel);
		MostraPartida(&TableroTetris,Jugador,Puntuacion,Vida);
		MostraLinia(&TableroTetris,LiniaAbajo);	
		PosPiezaY=POSICION_Y_INICIAL_PIEZA;
}while(TeclaPulsada!=TECLA_ESCAPE);
Nivel=NIVEL_MEDIO;
system("cls");									//LIMPIAMOS LA PANTALLA
MostraMSG(&TableroTetris,TEXTO_ESCAPE);	
CambiarColorTexto(&TableroTetris,WHITE);				//MOSTRAMOS TEXTO PARA INFORMAR AL JUGADOR DE QUE EL JUEGO A TERMINADO
ClosePantalla();
system("cls");
return Puntuacion;
}

//Procedimiento que inicializa dentro del juego la linia final del juego
void InicializarLiniaFinal(int LiniaFinal[NCol])
{
	int i;
	for(i=0;i<NCol;i++)
	{
		LiniaFinal[i]=0;
	}
}

//Funci�n que comprueva los espacios continuos que hay en la linia vinal y devuelve el tipo pieza que es posible generar
int ComprobarEspaciosContinuos(int LiniaFinal[NCol])
{
	int i,PiezaPosible;
	PiezaPosible=1;
	i=0;
		do
		{
			if((LiniaFinal[i]==0)&&(LiniaFinal[i+1]==0))
			{
				if(i<NCol-2)
				{
					if(LiniaFinal[i+2]==0)
					{
						PiezaPosible=3;
						i=NCol-3;
					}
					else
					{
						PiezaPosible=2;
						if(i<NCol-3)
						{
							i=i+3;
						}
						else
						{
							i=NCol-3;
						}
					}
				}
				else
				{
					PiezaPosible=2;
					i=NCol-3;
				}
			}
		i++;
		}while(i<NCol-2);
	return PiezaPosible;
}

//Procedimiento que segun que pieza de haya generado aleatoriament la pasa a nuetro vector de pieza
void GenerarPieza(int TipoPieza[NUMERO_DE_PIEZAS],int Pieza[NUMERO_DE_PIEZAS])
{
int i;
	for(i=0;i<NUMERO_DE_PIEZAS;i++)					//LLENAMOS NUESTRO VECTOR CON EL VECTOR DE 
	{									//LA PIEZA
		Pieza[i]=TipoPieza[i];					
	}									
}

//Coloca en la linia final la pieza, suma uno a la puntuaci�n, si hay espacio y si no no la colaca y resta una vida.
void PonerPiezaEnLiniaFinal(int Pieza[NUMERO_DE_PIEZAS],int LiniaFinal[NCol],int Posicion,int *Espacios,int *Puntuacion,int *Vida,int *Tecla)
{
if(*Tecla!=TECLA_ESCAPE)
{
	switch(Pieza[1])
	{
		case 1:
			if(LiniaFinal[Posicion]==ESPACIO)
			{
				ColocarPieza(Pieza,LiniaFinal,Posicion);
				*Espacios=(*Espacios-1);
				*Puntuacion=(*Puntuacion+1);
			}else{*Vida=(*Vida-1);Sleep(TIEMPO_PIEZA_FINAL);}
			break;
		case 2:
			if((LiniaFinal[Posicion]==ESPACIO)&&(LiniaFinal[Posicion+1]==ESPACIO))
			{
				ColocarPieza(Pieza,LiniaFinal,Posicion);
				*Espacios=(*Espacios-2);
				*Puntuacion=(*Puntuacion+1);
			}else{*Vida=(*Vida-1);Sleep(TIEMPO_PIEZA_FINAL);}
			break;
		case 3:
			if((LiniaFinal[Posicion-1]==ESPACIO)&&(LiniaFinal[Posicion+1]==ESPACIO)&&(LiniaFinal[Posicion]==ESPACIO))
			{
				ColocarPieza(Pieza,LiniaFinal,Posicion);
				*Espacios=(*Espacios-3);
				*Puntuacion=(*Puntuacion+1);
			}else{*Vida=(*Vida-1);Sleep(TIEMPO_PIEZA_FINAL);}
			break;
		default:
			break;
	}
		if(*Vida==0)										//
		{													// Si se acaban las vidas sale del juego
			*Tecla=TECLA_ESCAPE;							//
		}
		else
		{
			if(*Espacios==0)
			{
				InicializarLiniaFinal(LiniaFinal);
				Puntuacion=Puntuacion+10;					//Si se completa la linea suma 10 puntos
				*Espacios=NCol;
			}
		}
}
}

//Prodecimiento que pone limite a la pieza y da una posicion aleatoria del tablero para que se genere.
void PonerLimitePieza(int LimitesTablero[LIMITES],int *PosPiezaX,int LimitePiezaDerecho,int LimitePiezaIzquierdo)
{
	LimitesTablero[LIMITE_DER]=LimitePiezaDerecho;	//DEFINIMOS LIMITES DEL TABLERO SEGUN LA
	LimitesTablero[LIMITE_IZ]=LimitePiezaIzquierdo;
	*PosPiezaX=rand()%(NCol);				//NICIALIZAMOS LA POSICION DE LA PIEZA ALEATORIAMENTE
		if(*PosPiezaX<LimitePiezaIzquierdo)
		{
			*PosPiezaX=LimitePiezaIzquierdo;
		}
		if(*PosPiezaX>LimitePiezaDerecho)
		{
			*PosPiezaX=LimitePiezaDerecho;
		}
}

//Funci�n que genera aleatoriamente una pieza, segun la pieza que se pueda generar y pone limitesy devuelve la posicion donde se a de generar.
int GenerarPiezaAleatoria(int Pieza[NUMERO_DE_PIEZAS],int PosPiezaX,int LimitesTablero[LIMITES],int PiezaPosible)
{
int PiezaAleatoria;
		PiezaAleatoria=rand()%(PiezaPosible);
		switch(PiezaAleatoria)						
		{
			case 0:
				GenerarPieza(P,Pieza);
				PonerLimitePieza(LimitesTablero,&PosPiezaX,LIMITE_D_PIEZAP,LIMITE_I_PIEZAPYS);
				break;
			case 1:
				GenerarPieza(S,Pieza);
				PonerLimitePieza(LimitesTablero,&PosPiezaX,LIMITE_D_PIEZALYS,LIMITE_I_PIEZAPYS);	
				break;
			case 2:
				GenerarPieza(L,Pieza);
				PonerLimitePieza(LimitesTablero,&PosPiezaX,LIMITE_D_PIEZALYS,LIMITE_I_PIEZAL);
				break;
			default:
				break;
		}
		return PosPiezaX;
}

//Procedimiento que controla el cambio de nivel segun la puntuaci�n.
void ControlNivel(int Puntuacion,int *Nivel)
{
	if(Puntuacion>=LIMITE_NIVEL_EXPERTO)
	{
		*Nivel=NIVEL_EXPERTO;
	}
	else
	{
		if((Puntuacion>=LIMITE_NIVEL_MEDIO)&&(*Nivel!=NIVEL_EXPERTO))
		{
			*Nivel=NIVEL_MEDIO;
		}
	}
}

//Procedimiento que comprueba si esta entre las cinco mejores puntuaciones y las ordena. 
void ConpararMejoresPuntuaciones(TipoJugador Jugador[MAXIMO_JUGADORES],int Puntuacion)
{
int i;
TipoJugador Auxiliar;
	i=MAXIMO_JUGADORES-1;
		if(Jugador[i].Puntuacion<Puntuacion)
		{	
				do
				{
					printf("ESCRIU EL TEU NOM (maxim 16 Caracters): ");
					gets(Jugador[i].Nombre);
				}while(strlen(Jugador[i].Nombre)>MAXIMO_CARACTERES_N);
					while(strlen(Jugador[i].Nombre)<MAXIMO_CARACTERES_N-1)
					{
						strcat(Jugador[i].Nombre," ");
					}
				do
				{
					printf("ESCRIU LA DATA (dd/mm/aaaa): ");
					gets(Jugador[i].Fecha);
				}while(strlen(Jugador[i].Fecha)!=MAXIMO_CARACTERES_F-1);
			Jugador[i].Puntuacion=Puntuacion;
			while((i>0)&&(Jugador[i-1].Puntuacion<Jugador[i].Puntuacion))
			{
				Auxiliar.Puntuacion=Jugador[i-1].Puntuacion;
				strcpy(Auxiliar.Fecha,Jugador[i-1].Fecha);
				strcpy(Auxiliar.Nombre,Jugador[i-1].Nombre);
				Jugador[i-1].Puntuacion=Jugador[i].Puntuacion;
				strcpy(Jugador[i-1].Fecha,Jugador[i].Fecha);
				strcpy(Jugador[i-1].Nombre,Jugador[i].Nombre);
				Jugador[i].Puntuacion=Auxiliar.Puntuacion;
				strcpy(Jugador[i].Fecha,Auxiliar.Fecha);
				strcpy(Jugador[i].Nombre,Auxiliar.Nombre);
				i--;
			}
		}
}

//Procedimiento escribe en el fichero de puntuaciones ya ordenadamente.
void EscribirFicheroPuntuaciones(TipoJugador Jugador[MAXIMO_JUGADORES])
{
int i;
FILE *MejoresPuntuaciones;
	MejoresPuntuaciones=fopen("MejoresPuntuaciones.txt","w");
	for(i=0;i<MAXIMO_JUGADORES;i++)
		{	
			fputs(Jugador[i].Nombre,MejoresPuntuaciones);
			fputs(Jugador[i].Fecha,MejoresPuntuaciones);
			fprintf(MejoresPuntuaciones," %d\n",Jugador[i].Puntuacion);
		}
	fclose (MejoresPuntuaciones);
}

//Procedimiento inicializa la lista de mejores puntuaciones por si no hay nada en el archivo y lo rellena.
void IniTipoJugador(TipoJugador Jugador[MAXIMO_JUGADORES])
{
int i;
	for(i=0;i<MAXIMO_JUGADORES;i++)
	{
		strcpy (Jugador[i].Nombre,"Jugador1        ");
		strcpy (Jugador[i].Fecha,"SINF       ");
		Jugador[i].Puntuacion=0;
	}
}

//Procedimiento desplaza una posicion a la izquierda las piezas colocada en la linia final.
void DesplazarLiniaFinal(int LiniaFinal[NCol])
{
	int i,Auxiliar;
	i=0;
	Auxiliar=LiniaFinal[i];
	for(i=0;i<NCol-1;i++)					 
	{								
		LiniaFinal[i]=LiniaFinal[i+1];
	}	
	LiniaFinal[NCol-1]=Auxiliar;
}

//Procedimiento que coloca la pieza en la linia final.
void ColocarPieza(int Pieza[NUMERO_DE_PIEZAS],int LiniaFinal[NCol],int Posicion)
{
int i;
	for(i=-1;i<2;i++)					 
	{
		if(Pieza[i+1]!=0)
		{
			LiniaFinal[Posicion+i]=Pieza[i+1];
		}
	}
}

//Procedimiento que cambia el color del texto.
void CambiarColorTexto(pantalla_t *tauler, int Color)
{
	HANDLE screen = tauler->screen;
	TextColor(Color,BLACK,screen);
}

//Procedimiento que imprime un menu.
void ImprimirMenu()
{
	printf("1. Puntuacions Previes\n");
	printf("2. Nivell\n");
	printf("3. Jugar\n");
	printf("4. Sortir\n");
	printf("Escull una opcio pel TETRIS\n");
}

//Funci�n que pregunta si quieres salir y devueve la tecla pulsada.
int PreguntaSalir()
{
int Accion;
	printf("Estas segur que vols sortir? \n");
	printf("Prem s per si y n per no\n");
	fflush(stdin);									
	Accion=getch();
	
	return Accion;
}

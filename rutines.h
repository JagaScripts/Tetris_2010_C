#ifndef __RUTINES_H__
#define __RUTINES_H__



//===================================================================================
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdio.h>



#include <windows.h>


//===================================================================================
// Definicio de colors
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGREY 7
#define DARKGREY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15
#define BLINK 128



//===================================================================================
// Dimensions del taulell de joc
#define NFil 28
#define NCol 18

//===================================================================================
// Desplaçament del taulell respecte la cantonada superior esquerre
#define DespF 5
#define DespC 27


//===================================================================================

// Declaracio de tipus
typedef struct pantalla_s {
	HANDLE screen;
	int Tauler[NFil][NCol];
	int CL[4];
} pantalla_t;




// Declaració de funcions
void gotoxy(int,int,HANDLE);
void TextColor(int,int,HANDLE);


void InitPantalla( pantalla_t *tauler );
void ClosePantalla( );


void MostraTauler( pantalla_t *tauler );
int MostraMSG(pantalla_t *tauler, char* );
void PosaPeca(int Tauler[NFil][NCol], int Peca[3], int F, int C);
void MostraPesa( pantalla_t *tauler, int Peca[3], int F, int C);
void MostraPartida(pantalla_t *tauler,char *jugador,int Punts,int VIDA);

void MostraLinia( pantalla_t *tauler, int linia[NCol]);

#endif

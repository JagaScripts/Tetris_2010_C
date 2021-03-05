#include "rutines.h"
#include <conio.h>



//===================================================================================
// NOM: Gotoxy
//===================================================================================
// DESCRIPCIÓ: Permet posar el cursor en una posicio donada
//===================================================================================
void gotoxy(int c,int f,HANDLE screen)
{
 COORD position = { c, f };
 SetConsoleCursorPosition(screen,position);
}


//===================================================================================
// NOM: TextColor
//===================================================================================
// DESCRIPCIÓ: Funcio per canviar els colors de texte i fons de la consola DOS
//===================================================================================
void TextColor(int fontcolor,int backgroundcolor,HANDLE screen)
{
   unsigned short color_attribute;
   color_attribute = backgroundcolor;
   color_attribute = _rotl(color_attribute,4) | fontcolor;
   SetConsoleTextAttribute(screen,color_attribute);
}

//===================================================================================
// NOM: InitPantalla
//===================================================================================
// DESCRIPCIÓ: Funcio que inicialitza estructures per visualitzar el tauler de joc
//===================================================================================
void InitPantalla( pantalla_t *tauler )
{
	CONSOLE_CURSOR_INFO ConCurInf;
	tauler->screen = GetStdHandle(STD_OUTPUT_HANDLE);   
	
	// ------------------------------------------------------------------------------
	// Les peces estan representades dins la matriu peces, i cadascuna esta codificada
	// amb un valor entre 0 i 7, que coincideix amb l'index del següent vector que 
	// n'especifica el color.
	// 
	// index 0 -> No hi ha peça.
	// index 1 -> Color de fons de la peça P.
	// index 2 -> Color de fons de la peça S.
	// index 3 -> Color de fons de la peça L.

	
	tauler->CL[0] = BLACK;
    tauler->CL[1] = LIGHTMAGENTA;
    tauler->CL[2] = GREEN;
    tauler->CL[3] = YELLOW;
	
	
	// ------------------------------------------------------------------------------
	// Amaguem el cursor:	         
	ConCurInf.dwSize = 10; 
    ConCurInf.bVisible = FALSE;
    SetConsoleCursorInfo(tauler->screen,&ConCurInf);

	// ------------------------------------------------------------------------------
	// Iniciem el Joc
	printf("Maximitza la pantalla i prem una tecla....");
	getch();
	system("cls");
}

//===================================================================================
// NOM: ClosePantalla
//===================================================================================
// DESCRIPCIÓ: Funcio que tanca les estructures i surt correctament del joc
//===================================================================================
void ClosePantalla( )
{
//	getch();
}



//===================================================================================
// NOM: MostraTauler
//===================================================================================
// DATA: 08 / 10 / 2007
//===================================================================================
// DESCRIPCIÓ: Funcio que permet mostrar el tauler de joc.
//===================================================================================
void MostraTauler( pantalla_t *tauler)
{
	// ------------------------------------------------------------------------------
	// FORMAT TAULELL:
	//
	// El vector FT (Format Taulell) conté a cada posició el codi d'un determinat 
	// caràcter ASCII. Si modifiquem els valors  d'aquest vector, l'aparença del
	// taulell, també variarà.
	//	
	// index 0 -> Contorn lateral.
	// index 1 -> Cantonada inferior esquerre.
	// index 2 -> Cantonada inferior dreta.
	// index 3 -> Contorn inferior.
	int FT[4]={186,200,205,188};	
	
	// ------------------------------------------------------------------------------
	// Altres variables:
	int f,c;
	HANDLE  screen= tauler->screen;
	
	TextColor(LIGHTGREY,BLACK,screen);
	// ------------------------------------------------------------------------------	
	// pintem les col·lumnes
	for(f=0;f<NFil;f++)
	{
		gotoxy(DespC,DespF+f,screen);
		printf("%c",FT[0]);

		gotoxy(DespC+NCol+1,DespF+f,screen);		
		printf("%c",FT[0]);
	}

    //pintem la cantonada esquerra
	gotoxy(DespC,DespF+NFil,screen);
	printf("%c",FT[1]);

    //pintem la barra d'abaix
	for(c=0;c<NCol;c++)
		printf("%c",FT[2]);
	
	//pintem la cantonada dreta
	printf("%c",FT[3]);

	// ------------------------------------------------------------------------------	
	// pintem les linies del menu
	gotoxy(DespC,DespF+NFil+2,screen);
	for(c=0;c<NCol+2;c++)
		printf("%c",FT[2]);

	gotoxy(DespC,DespF+NFil+4,screen);
	for(c=0;c<NCol+2;c++)
		printf("%c",FT[2]);

}


//===================================================================================
// NOM: MostraMSG
//===================================================================================
// DATA: 09 / 10 / 2007
//===================================================================================
// DESCRIPCIÓ: Funcio que permet mostrar un dels missatges predefinits sobre el 
// tauler de joc. 
// retorna: int amb el codi de la tecla que s'ha pres (crida a la funció getch()
//===================================================================================
int MostraMSG(pantalla_t *tauler, char *msg)
{
	HANDLE screen = tauler->screen;
	int i,L,C,CC,CF;

	L=strlen(msg); // Longitud de la cadena.
	C=(int)ceil(L/2);  // Punt mig de la cadena.

	CF=(int)floor(NFil/2);
	CC=(int)floor(NCol/2);

	TextColor(RED,BLACK,screen);
	gotoxy(DespC+CC-C,DespF+CF-1,screen);
	for(i=0;i<L+2;i++)
		printf(" ");
	gotoxy(DespC+CC-C,DespF+CF,screen);
	printf(" %s ",msg);
	gotoxy(DespC+CC-C,DespF+CF+1,screen);
	for(i=0;i<L+2;i++)
		printf(" ");
	
	return getch();
}

//===================================================================================
// NOM: MostraPesa
//===================================================================================
// DATA: 08 / 10 / 2007
//===================================================================================
// DESCRIPCIÓ: Funcio copia la peca en la fila F i columna C del tauler Tauler
//===================================================================================
void PosaPeca(int Tauler[NFil][NCol], int Peca[3], int F, int C)
{
	int i;
	for(i=-1;i<=1;i++)	
		if ( Peca[i+1]> 0 )
			Tauler[F-1][C+i]=Peca[i+1];
}

//===================================================================================
// NOM: MostraPesa
//===================================================================================
// DATA: 08 / 10 / 2007
//===================================================================================
// DESCRIPCIÓ: Funcio que permet mostrar les peces que hi hagi en un moment Co
// determinat. 
//===================================================================================
void MostraPesa( pantalla_t *tauler,  int Peca[3], int F, int C)
{

	int *CL= tauler->CL;

	// ------------------------------------------------------------------------------
	// Altres variables:
	int f,c;
	HANDLE  screen= tauler->screen;

	// Inicialitzem la matriu Tauler a zero
	for(f=0;f<NFil;f++)
	  for(c=0;c<NCol;c++)
	    tauler->Tauler[f][c]=0;
	
	PosaPeca(tauler->Tauler, Peca, F, C);
	// ------------------------------------------------------------------------------
	// Dibuixem les peces:
	for(f=0;f<NFil;f++)
	{
		for(c=0;c<NCol;c++)
		{		
			gotoxy(DespC+c+1,DespF+f,screen);			
			TextColor(CL[tauler->Tauler[f][c]],BLACK,screen);
            printf("%c",177);
		}
    }
}

//===================================================================================
// NOM: MostraPartida
//===================================================================================
// DATA: 08 / 10 / 2007
//===================================================================================
// DESCRIPCIÓ: Funcio que permet mostrar el nom del jugador i la seva puntuacio
//===================================================================================
void MostraPartida(pantalla_t* tauler, char *Jugador, int Puntuacio, int VIDA)
{
	HANDLE  screen= tauler->screen;	
	
	// Mostrem el nom del jugador i la puntuació:
	gotoxy(DespC+1,DespF+NFil+1,screen);
	TextColor(LIGHTGREY,BLACK,screen);
	printf("PLAYER: ");
	TextColor(RED,BLACK,screen);
	printf("%s\n",Jugador);
	
	
	gotoxy(DespC+1,DespF+NFil+3,screen);
	TextColor(LIGHTGREY,BLACK,screen);
	printf("SCORE: ");
	TextColor(RED,BLACK,screen);
	printf(" %d VIDA: %d\n",Puntuacio,VIDA);
}

//===================================================================================
// NOM: MostraPartida
//===================================================================================
// DATA: 08 / 10 / 2007
//===================================================================================
// DESCRIPCIÓ: Funcio que permet mostrar el nom del jugador i la seva puntuacio
//===================================================================================
void MostraLinia( pantalla_t *tauler, int linia[NCol])
{
     int j;
    int *CL= tauler->CL;

	// ------------------------------------------------------------------------------
	// Dibuixem les peces:
    gotoxy(DespC+1,DespF+NFil-1,tauler->screen);
	for(j=0;j<NCol;j++)
	{         			
         TextColor(CL[linia[j]],BLACK,tauler->screen);
         printf("%c",177);
    }

}

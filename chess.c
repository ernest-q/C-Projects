/*
AUTHOR: Ernest J. Quant
PURPOSE: Making a nice, command line game of chess.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#define MAX_SIZE 8

wchar_t bknight = 0x2658;
wchar_t wpawn = 0x265f;
wchar_t wknight = 0x265e;
wchar_t bpawn = 0x2659;
wchar_t bking = 0x2654;
wchar_t wking = 0x265a;
wchar_t wrook = 0x265c;
wchar_t brook = 0x2656;
wchar_t wbish = 0x265d;
wchar_t bbish = 0x2657;
wchar_t bqueen = 0x2655;
wchar_t wqueen = 0x265b;

typedef struct square {
	int color;
	int piece;

}board[MAX_SIZE][MAX_SIZE];
static board table;

FILE readPosition();
FILE writeFile();
FILE boardtl5();
int mv(int curRow, char curColChar, int desRow, char desColChar);
void cp(int curRow, char curColChar, int desRow, char desColChar);
void printy();

int main(){

	int start = 0;
	char command[50];
	int inRowOne;
	char inColOne;
	int inRowTwo;
	char inColTwo;

	setlocale(LC_CTYPE, "");
	readPosition(table);
	
	if(!start){
			printf("\n~~~~ WELCOME TO ERNEST'S CHESS PROGRAM! ~~~~\n\n");
			printf("COMMANDS:\n");
			printf("-  MOVE  : mv (current row) (current column) (desired row) (desired column)\n");
			printf("     EXAMPLE INPUT: mv 5b 4a\n");
			printf("\n- CAPTURE: cp (current row) (current column) (desired row) (desired column)\n");
			printf("     EXAMPLE INPUT: cp 5b 4a\n");
			printf("\n- SHOW: cp (current row) (current column) (desired row) (desired column)\n");
			printf("     EXAMPLE INPUT: cp 5 b 4 a\n\n");
			printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			printy();
			++start;
		}

	// POPULATES BOARD WITH COLOR TILES
	int x = 0;
	for (int i = 0; i < MAX_SIZE; i++){
		for(int j = 0; j < MAX_SIZE; j++){
			x = 1 - x;
			table[i][j].color = x;
		}
		x = 1 - x;
	}

	printf("Enter a command: ");
	while(scanf("%s %d%c %d%c",command,&inRowOne,&inColOne,&inRowTwo,&inColTwo)!=0){

		if(strcmp("mv",command)==0){
			printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			mv(inRowOne,inColOne,inRowTwo,inColTwo);
			writeFile();
			printy();
		}
		else if(strcmp("cp",command)==0){
			printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			cp(inRowOne,inColOne,inRowTwo,inColTwo);
			writeFile();
			printy();
		}
		else if(strcmp("show",command)==0){
			printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			boardtl5();
		}
		else{
			printf("Not a valid command\n");
		}
		printf("Enter a command: ");
	}
}


FILE readPosition(){

	char buff[255];
	char *delimString;

	int row = 0;
	int column = 0;

	FILE *fpIn;
	fpIn = fopen("board.csv","r");

	while(fgets(buff,255,(FILE*)fpIn)!=NULL){

		delimString = strtok(buff,",\n");

		while(delimString!=NULL){

			table[row][column].piece = atoi(delimString);
			printf("%2d,",table[row][column].piece);
			column++;
			delimString = strtok(NULL,",\n");
		}
		printf("\n");
		column = 0;
		row++;
	}
	fclose(fpIn);
}


FILE writeFile(){

	FILE *fpOut;
	fpOut = fopen("board.csv","w");

	for (int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			fprintf(fpOut,"%d",table[i][j].piece);
			if(j<7){
				fprintf(fpOut,",");
			}
		}
		fprintf(fpOut,"\n");
	}
	fclose(fpOut);
}

FILE boardtl5(){

	char buff[255];
	char *delimString;

	int row = 0;
	int column = 0;

	FILE *fpIn;
	fpIn = fopen("board.csv","r");
	int delimCount = 1;

	while(fgets(buff,255,(FILE*)fpIn)!=NULL){

		delimString = strtok(buff,",\n");

		while(delimString!=NULL){

			printf("%-5d",table[row][column].piece);
			if(delimCount < 8){
				printf("|");
				delimCount++;
			}

			column++;
			delimString = strtok(NULL,",\n");
		}
		delimCount = 1;
		printf("\n");
		column = 0;
		row++;
	}
	fclose(fpIn);

	printf("\n\n");
}


void printy(){

	printf(" __________________________\n");
	for (int i = 0; i < MAX_SIZE; i++){
		printf("%-1d|",MAX_SIZE-i);
		for(int j = 0; j < MAX_SIZE; j++){
			printf("[");
			if(table[i][j].piece==1){
				printf("%lc",wpawn);
			}
			else if(table[i][j].piece == -1){
				printf("%lc",bpawn);
			}
			else if(table[i][j].piece == 2){
				printf("%lc",wknight);
			}
			else if(table[i][j].piece == -2){
				printf("%lc",bknight);
			}
			else if(table[i][j].piece == 3){
				printf("%lc",wking);
			}
			else if(table[i][j].piece == -3){
				printf("%lc",bking);
			}
			else if(table[i][j].piece == 4){
				printf("%lc",wrook);
			}
			else if(table[i][j].piece == -4){
				printf("%lc",brook);
			}
			else if(table[i][j].piece == 5){
				printf("%lc",wbish);
			}
			else if(table[i][j].piece == -5){
				printf("%lc",bbish);
			}
			else if(table[i][j].piece == 6){
				printf("%lc",wqueen);
			}
			else if(table[i][j].piece == -6){
				printf("%lc",bqueen);
			}
			else{
				printf(" ");
			}	
			printf("]");
			if(j == 7){
				printf("|");
			}
		}
		printf("\n");
	}
	printf("   _  _  _  _  _  _  _  _\n");
	printf("   a  b  c  d  e  f  g  h");
	printf("\n\n");	
}


int mv(int curRowIn, char curColChar, int desRowIn, char desColChar){

	int curCol = curColChar - 97;
	int desCol = desColChar - 97;

	int curRow = MAX_SIZE - curRowIn;
	int desRow = MAX_SIZE - desRowIn;


	if(table[curRow][curCol].piece == 0){
		printf("Error: No piece to move.\n");
		return 0;
	}

	else if(table[desRow][desCol].piece != 0){
		printf("Error: The square is currently occupied, consider capturing\n");
		return 0;

	}
	else{

		//THIS IS THE PAWNS MOVEMENT
		if(abs(table[curRow][curCol].piece) == 1){

			if(table[curRow][curCol].piece>0){

				if(curCol!=desCol){
					printf("\nError: Pawn can't move sideways\n");
					return 0;
				}
				else if(desRow>curRow){
					printf("\nError: Pawn can't move backwards\n");
					return 0;
				}
				else if(abs(desRow - curRow)>2){
					printf("\nError:Pawn can't move that many spaces forward\n");
					return 0;
				}
				else if(abs(desRow - curRow) == 2 && table[desRow+1][desCol].piece!=0){
					printf("\nError: Cannot jump over a piece\n");
					return 0;
				}
				else if(abs(desRow - curRow) == 2 && curRowIn != 2){
					printf("\nError: Pawn cannot move two spaces after first turn\n");
					return 0;
				}
				else{
					table[desRow][desCol].piece = table[curRow][curCol].piece;
					table[curRow][curCol].piece = 0;
					return 1;
				}

			}
			else if(table[curRow][curCol].piece<0){

				if(curCol!=desCol){
					printf("\nError: Pawn can't move sideways\n");
					return 0;
				}
				else if(desRow<curRow){
					printf("\nError: Pawn can't move backwards\n");
					return 0;
				}
				else if(abs(desRow - curRow)>2){
					printf("\nError: Pawn can't move that many spaces forward\n");
					return 0;
				}
				else if(abs(desRow - curRow) == 2 && table[desRow-1][desCol].piece!=0){
					printf("\nError: Cannot jump over a piece\n");
					return 0;
				}
				else if(abs(desRow - curRow) == 2 && curRowIn != 7){
					printf("\nError: Pawn cannot move two spaces after first turn\n");
					return 0;
				}
				else{
					table[desRow][desCol].piece = table[curRow][curCol].piece;
					table[curRow][curCol].piece = 0;
					return 1;
				}
			}
		}

		//THIS IS THE KNIGHTS MOVEMENT
		else if(abs(table[curRow][curCol].piece) == 2){

			if((abs(curRow-desRow))+(abs(curCol-desCol))!= 3){
					printf("Error: Knight is moving too little or too many spaces\n");
					return 0;
				}
				else{
					if(abs(curRow-desRow) > 2 || abs(curCol-desCol) > 2){
						printf("Error: Knight is moving too many spaces in one direction\n");
						return 0;
					}
					else{
						table[desRow][desCol].piece = table[curRow][curCol].piece;
						table[curRow][curCol].piece = 0;
						return 1;
					}
				}
		}

		//THIS IS THE KINGS MOVEMENT
		else if(abs(table[curRow][curCol].piece) == 3){
			if(abs(curRow - desRow)>1 || abs(curCol - desCol)>1){
				printf("Error: King can't move that many spaces\n");
				return 0;
			}
			else{
				table[desRow][desCol].piece = table[curRow][curCol].piece;
				table[curRow][curCol].piece = 0;
				return 1;
			}
		}

		//THIS IS THE ROOKS MOVEMENT
		else if(abs(table[curRow][curCol].piece) == 4){
			if(abs(curRow-desRow)>0 && abs(curCol-desCol)>0){
				printf("Error: Rook cannot move sideways\n");
				return 0;
			}
			else{
				int pieceBetween = 0;

				// IF ROOK IS MOVING VERTICALLY
				if(abs(curRow-desRow)>0){
					// ROOK IS MOVING DOWN
					if(desRow > curRow){
						for(int i = curRow + 1; i < desRow; i++){
							if(table[i][curCol].piece!=0){
								pieceBetween = 1;
							}
						}
					}
					else if(desRow < curRow){
						for(int i = curRow - 1; i > desRow; i--){
							if(table[i][curCol].piece!=0){
								pieceBetween = 1;
							}
						}
					}
				}
				// IF ROOK IS MOVING HORIZONTALLY
				else if(abs(curCol-desCol)>0){
					if(desCol > curCol){
						for(int i = curCol + 1; i < desCol; i++){
							if(table[curRow][i].piece!=0){
								pieceBetween = 1;
							}
						}
					}
					else if(desCol < curCol){
						for(int i = curCol - 1; i > desCol; i--){
							if(table[curRow][i].piece!=0){
								pieceBetween = 1;
							}
						}
					}
				}

				// IF PIECE WAS FOUND BETWEEN CUR AND DES LOCATION
				if(pieceBetween==1){
					printf("Error: Rook can't jump over piece\n");
					return 0;
				}
				else{
					table[desRow][desCol].piece = table[curRow][curCol].piece;
					table[curRow][curCol].piece = 0;
					return 1;
				}


			}
		}
		// THIS IS THE BISHOPS MOVEMENTS
		else if(abs(table[curRow][curCol].piece)==5){
			if(abs(curRow - desRow) != abs(curCol - desCol)){
				printf("Error: Bishop can only move sideways.\n");
				return 0;
			}
			else{
				int pieceBetween = 0;

				// MOVING UP TO THE LEFT
				if((curRow > desRow) && (curCol > desCol)){			// FIXING THIS ISSUE WITH THE BISHOP MOVMENET
					int loopRow = curRow - 1;
					int loopCol = curCol - 1;
					do{
						if(table[loopRow][loopCol].piece!=0){
							pieceBetween = 1;
						}
						--loopRow;
						--loopCol;
					}while(loopRow > desRow);
				}
				// MOVING UP TO THE RIGHT
				else if((curRow > desRow) && (curCol < desCol)){
					int loopRow = curRow - 1;
					int loopCol = curCol + 1;
					do{
						if(table[loopRow][loopCol].piece!=0){
							pieceBetween = 1;
						}
						--loopRow;
						++loopCol;
					}while(loopRow > desRow);
				}
				// MOVING DOWN TO THE LEFT
				else if((curRow < desRow) && (curCol > desCol)){
					int loopRow = curRow + 1;
					int loopCol = curCol - 1;
					do{
						if(table[loopRow][loopCol].piece!=0){
							pieceBetween = 1;
						}
						++loopRow;
						--loopCol;
					}while(loopRow < desRow);
				}
				else if((curRow < desRow) && (curCol < desCol)){
					int loopRow = curRow + 1;
					int loopCol = curCol + 1;
					do{
						if(table[loopRow][loopCol].piece!=0){
							pieceBetween = 1;
						}
						++loopRow;
						++loopCol;
					}while(loopRow < desRow);
				}


				if(pieceBetween==1){
					printf("Error: Bishop can't jump over piece\n");
					return 0;
				}
				else{
					table[desRow][desCol].piece = table[curRow][curCol].piece;
					table[curRow][curCol].piece = 0;
					return 1;
				}
			}
		}
		//THIS IS THE QUEENS MOVEMENTS
		else if(abs(table[curRow][curCol].piece) == 6){

			// IF QUEEN IS MOVING LIKE BISHOP
			if(abs(curRow - desRow) == abs(curCol - desCol)){

				int pieceBetween = 0;

				// MOVING UP TO THE LEFT
				if((curRow > desRow) && (curCol > desCol)){
					int loopRow = curRow - 1;
					int loopCol = curCol - 1;
					do{
						if(table[loopRow][loopCol].piece!=0){
							pieceBetween = 1;
						}
						--loopRow;
						--loopCol;
					}while(loopRow > desRow);
				}
				// MOVING UP TO THE RIGHT
				else if((curRow > desRow) && (curCol < desCol)){
					int loopRow = curRow - 1;
					int loopCol = curCol + 1;
					do{
						if(table[loopRow][loopCol].piece!=0){
							pieceBetween = 1;
						}
						--loopRow;
						++loopCol;
					}while(loopRow > desRow);
				}
				// MOVING DOWN TO THE LEFT
				else if((curRow < desRow) && (curCol > desCol)){
					int loopRow = curRow + 1;
					int loopCol = curCol - 1;
					do{
						if(table[loopRow][loopCol].piece!=0){
							pieceBetween = 1;
						}
						++loopRow;
						--loopCol;
					}while(loopRow < desRow);
				}
				else if((curRow < desRow) && (curCol < desCol)){
					int loopRow = curRow + 1;
					int loopCol = curCol + 1;
					do{
						if(table[loopRow][loopCol].piece!=0){
							pieceBetween = 1;
						}
						++loopRow;
						++loopCol;
					}while(loopRow < desRow);
				}


				if(pieceBetween==1){
					printf("Error: Queen can't jump over piece\n");
					return 0;
				}
				else{
					table[desRow][desCol].piece = table[curRow][curCol].piece;
					table[curRow][curCol].piece = 0;
					return 1;
				}
			}
			// IF QUEEN IS MOVING LIKE ROOK
			else if(abs(curRow-desRow)>0 && abs(curCol-desCol)>0){
				printf("Error: Queen cannot move that way\n");
				return 0;
			}
			else{
				int pieceBetween = 0;

				// IF QUEEN IS MOVING VERTICALLY
				if(abs(curRow-desRow)>0){
					// QUEEN IS MOVING DOWN
					if(desRow > curRow){
						for(int i = curRow + 1; i < desRow; i++){
							if(table[i][curCol].piece!=0){
								pieceBetween = 1;
							}
						}
					}
					else if(desRow < curRow){
						for(int i = curRow - 1; i > desRow; i--){
							if(table[i][curCol].piece!=0){
								pieceBetween = 1;
							}
						}
					}
				}
				// IF QUEEN IS MOVING HORIZONTALLY
				else if(abs(curCol-desCol)>0){
					if(desCol > curCol){
						for(int i = curCol + 1; i < desCol; i++){
							if(table[curRow][i].piece!=0){
								pieceBetween = 1;
							}
						}
					}
					else if(desCol < curCol){
						for(int i = curCol - 1; i > desCol; i--){
							if(table[curRow][i].piece!=0){
								pieceBetween = 1;
							}
						}
					}
				}

				// IF PIECE WAS FOUND BETWEEN CUR AND DES LOCATION
				if(pieceBetween==1){
					printf("Error: Queen can't jump over piece\n");
					return 0;
				}
				else{
					table[desRow][desCol].piece = table[curRow][curCol].piece;
					table[curRow][curCol].piece = 0;
					return 1;
				}
			}
		}
	}
}


void cp(int curRowIn, char curColChar, int desRowIn, char desColChar){

	int curCol = curColChar - 97;
	int desCol = desColChar - 97;

	int curRow = 8 - curRowIn;
	int desRow = 8 - desRowIn;

	if(table[desRow][desCol].piece == 0){
		printf("Error: There is no piece to capture, consider mv instead.\n");
	}
	else if((table[curRow][curCol].piece < 0 && table[desRow][desCol].piece < 0) ||
		table[curRow][curCol].piece > 0 && table[desRow][desCol].piece > 0){
		printf("Error: Cannot eat one of your own pieces.\n");
	}
	else{

		// PAWN CAPTURING, SINCE PAWNS CAPTURE DIFFERENTLY THAN THEY MOVE
		if(abs(table[curRow][curCol].piece)==1){

			// IF PAWN IS +
			if(table[curRow][curCol].piece > 0){
				if(desRow > curRow){
					printf("Error: Pawn can't capture backwards.\n");
				}
				else if(abs(curRow - desRow)!= 1 ||  abs(curCol - desCol)!=1){
					printf("Error: Pawn can't capture there.\n");
				}
				else{
					table[desRow][desCol].piece = table[curRow][curCol].piece;
					table[curRow][curCol].piece = 0;
				}


			}
			// IF PAWN IS -
			else if(table[curRow][curCol].piece > 0){

				if(desRow < curRow){
					printf("Error: Pawn can't capture backwards.\n");
				}
				else if(abs(curRow - desRow)!= 1 ||  abs(curCol - desCol)!=1){
					printf("Error: Pawn can't capture there.\n");
				}
				else{
					table[desRow][desCol].piece = table[curRow][curCol].piece;
					table[curRow][curCol].piece = 0;
				}
			}
		}

		// GENERIC EATING FOR OTHER PIECES
		else{
			int tempDestPiece = table[desRow][desCol].piece;
			table[desRow][desCol].piece = 0;

			if(mv(curRowIn,curColChar,desRowIn,desColChar)==1){
				printf("\n");

			}
			else{
				printf("Error: Piece cannot eat like that.\n");
				table[desRow][desCol].piece = tempDestPiece;
			}
		}
	}
}
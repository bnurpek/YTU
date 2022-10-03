#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 43
#define LINE 255
#define APPLE 10

/*
*	MEAN OF NUMBERS ON MATRIS
*	0:		BLOCK
*	1:		ROAD
*	2:		START
*	3:		FINISH
*	4:		APPLE
*	-1:		PASSING ROAD (STAR)
*	-2:		TURNING ROAD (SPACE)
*/

typedef struct labirent{
	int matris[MAX][MAX];
	char matrisForPrint[MAX][MAX];
	int N, M;
	int start[2];
	int numOfApple;
	int score;
	int isSolved;
}LABIRENT;

LABIRENT labirent;

LABIRENT readLabirentFromText(char fileName[]){
	srand(time(NULL));
	FILE *fp = fopen(fileName,"r");
	int i, j;
	char buffer[LINE];
	if(fp == NULL)
		return;
	labirent.numOfApple = 0;
	i=0;
	while(fgets(buffer,255,fp)){
		j = 0;
		while(buffer[j] != '\n'){
			if(buffer[j] == ' '){
				if((rand()%25) == 0 && labirent.numOfApple < APPLE){
					labirent.matris[i][j] = 4;
					buffer[j] = 'o';
					labirent.numOfApple++;
				}
				else
					labirent.matris[i][j] = 1;
			}
			else if(buffer[j] == 'b'){
				labirent.start[0] = i;
				labirent.start[1] = j;
				labirent.matris[i][j] = 2;
			}
			else if(buffer[j] == 'c'){
				labirent.matris[i][j] = 3;
			}
			else{
				labirent.matris[i][j] = 0;
			}
			labirent.matrisForPrint[i][j] = buffer[j];
			j++;
		}
		i++;
	}
	labirent.N = i;
	labirent.M = j;
	labirent.score = labirent.isSolved = 0;
	return labirent;
}

void delay100ms(){
	clock_t start_time = clock();
    while (clock() < start_time + 100);
}

void printLabirent(){
	int i, j;
	printf("\t\t\tSCORE: %d\n",labirent.score);
	i=0;
	while(i<labirent.N){
		printf("\t\t\t");
		j=0;
		while(j<labirent.M){
			printf("%c",labirent.matrisForPrint[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	delay100ms();
}

int isScoreChanged(int i, int j){
	if(labirent.matris[i-1][j] == 0 && labirent.matris[i][j-1] == 0 && labirent.matris[i+1][j] == 0)
		return 1;
	else if(labirent.matris[i-1][j] == 0 && labirent.matris[i][j-1] == 0 && labirent.matris[i][j+1] == 0)
		return 1;
	else if(labirent.matris[i-1][j] == 0 && labirent.matris[i+1][j] == 0 && labirent.matris[i][j+1] == 0)
		return 1;
	else if(labirent.matris[i][j-1] == 0 && labirent.matris[i+1][j] == 0 && labirent.matris[i][j+1] == 0)
		return 1;
	return 0;
}

LABIRENT solveLabirent(int i, int j){
	if(labirent.matris[i][j] == 3){
		labirent.isSolved = 1;
		return;
	}
	else{
		printf("\n\n\n\n");
		if(labirent.matris[i][j] == 4){
			printf("\t\t\tLOOK!! Found an apple!!\n");
			labirent.score+=10;
		}
		labirent.matris[i][j] = -1;
		labirent.matrisForPrint[i][j] = '*';
		printLabirent();
		system("cls");
		if(labirent.matris[i-1][j] > 0 && !labirent.isSolved){
			solveLabirent(i-1,j);
		}
		if(labirent.matris[i][j-1] > 0 && !labirent.isSolved){
			solveLabirent(i,j-1);
		}
		if(labirent.matris[i+1][j] > 0 && !labirent.isSolved){
			solveLabirent(i+1,j);
		}
		if(labirent.matris[i][j+1] > 0 && !labirent.isSolved){
			solveLabirent(i,j+1);
		}
		if(!labirent.isSolved){
			if(isScoreChanged(i,j))
				labirent.score-=5;
			labirent.matris[i][j] = -2;
			labirent.matrisForPrint[i][j] = ' ';
			printf("\n\n\n\n");
			printf("\t\t\tDEAD END!!!\nBacktracking...\n");
			printLabirent(labirent);
			system("cls");
			return;
		}
		return;
	}
	
}

int main(){
	time_t start,end;
	char fileName[MAX], tmp;
	printf("\n\n\t\t\tWELCOME TO MAZE SOLVER\n");
	printf("\t\t\tCreated by Buse Nur Pekmezci - 20011001\n");
	printf("\t\t\tEnter file name: ");
	gets(fileName);
	printf("\t\t\tPress enter to continue...\n");
	tmp = getc(stdin);
	system("cls");
	readLabirentFromText(fileName);
	time(&start);
	solveLabirent(labirent.start[0],labirent.start[1]);
	time(&end);
	printf("\n\n\n\n");
	printf("\t\t\tMission Complated...\n");
	printf("\t\t\tTime: %d seconds\n",end-start);
	printLabirent();
	return 0;
}

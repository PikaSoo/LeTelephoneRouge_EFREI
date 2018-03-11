#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>

#define PLAYERS 5 /// SI MODIF, CHANGER LISTE DES IAS DANS game()
#define SIZE sqrt(PLAYERS * 120)

void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

int** createTab();
void initTab(int** pMat);
void printTab(int** pMat);
void initGame(int** pMat);
int game(int** pMat);

int* ia1(int** pMat,int* last,int* dep);
int* ia2(int** pMat,int* last,int* dep);
int* ia3(int** pMat,int* last,int* dep);
int* ia4(int** pMat,int* last,int* dep);

int main() /// MAIN GAME
{
    int** pMat = createTab();
    initTab(pMat);
    initGame(pMat);
    printTab(pMat);
    printf("\n\n");
    Sleep(3000);
    system("cls");
    game(pMat);
    printTab(pMat);
    return 0;
} /// END MAIN GAME

int** createTab(){
    int** pMat = NULL;
    pMat = malloc(SIZE * sizeof(int*));
    if(pMat != NULL){
        int i;
        for(i = 0; i<SIZE; i++){
            pMat[i] = malloc(SIZE * sizeof(int));
            if(pMat[i] == NULL)exit(EXIT_FAILURE);
        }
    }else{
        exit(EXIT_FAILURE);
    }
    return pMat;
}

void initTab(int** pMat){
    int i,j,n=SIZE;
    for(i = 0; i<SIZE; i++){
        for(j = 0; j<SIZE; j++){
            if(!i){
                if(!j){pMat[i][j] = -5;}
                else if(j == n){pMat[i][j] = -6;}
                else{pMat[i][j] = -1;}
            }
            else if(i == n){
                if(!j){pMat[i][j] = -8;}
                else if(j == n){pMat[i][j] = -7;}
                else{pMat[i][j] = -3;}
            }
            else{
                if(!j){pMat[i][j] = -4;}
                else if(j == n){pMat[i][j] = -2;}
                else{pMat[i][j] = 0;}
            }
        }
    }
}

void printTab(int** pMat){
    int i,j;
    for(i = 0; i<SIZE; i++){
        for(j = 0; j<SIZE; j++){
            if(pMat[i][j] >= 10){
                    if(pMat[i][j]==10){Color(3,3);}
                    else if(pMat[i][j]==20){Color(10,10);}
                    else if(pMat[i][j]==30){Color(12,12);}
                    else if(pMat[i][j]==40){Color(15,15);}
                    else if(pMat[i][j]==50){Color(14,14);}
                    printf("%d ", pMat[i][j]);
                    Color(8,0);

            }
            else if(pMat[i][j] >= 0){
                    if(pMat[i][j]==1){Color(0,3);}
                    else if(pMat[i][j]==2){Color(0,10);}
                    else if(pMat[i][j]==3){Color(0,12);}
                    else if(pMat[i][j]==4){Color(0,15);}
                    else if(pMat[i][j]==5){Color(0,14);}
                    else if(pMat[i][j]==0){Color(0,0);}
                    printf(" %d ", pMat[i][j]);
                    Color(8,0);

            }
            else{
                    Color(8,8);
                    printf("%d ", pMat[i][j]);
                    Color(8,0);
            }

        }
        printf("\n");
    }
}

void initGame(int** pMat){
    int i,x,y,n = SIZE;
    srand(time(NULL));
    for(i = 1; i<=PLAYERS; i++){
        do
        {
            x = rand()%n;
            y = rand()%n;
        }while(pMat[x][y] != 0);

        pMat[x][y] = i;
    }
}

int game(int** pMat){
    /// Players :  1,  2,  3...
    /// Lines :   10, 20, 30...
    /// Blocks :
    ///    0 : floor
    ///   -1 : wall n
    ///   -2 : wall e
    ///   -3 : wall s
    ///   -4 : wall o
    ///   -5 : corner no
    ///   -6 : corner ne
    ///   -7 : corner se
    ///   -8 : corner so

    /// VARS
    int i,j,p,len = SIZE;
    int* (*ias[PLAYERS])(int**,int*,int*) = {ia1,ia1,ia1,ia1,ia1,ia1};
    int dead[PLAYERS] = {0};
    int winner = -1;
    int* mov = {0};
    int dep[] = {4};

    /// LAST POS
    int** last = NULL;
    last = malloc(PLAYERS * sizeof(int*));
    if(last != NULL){
        for(i = 0; i<PLAYERS; i++){
            last[i] = malloc(sizeof(int));
            if(last[i] == NULL)exit(EXIT_FAILURE);
        }
    }else{
        exit(EXIT_FAILURE);
    }

    for(p = 0; p<=PLAYERS; p++){
        for(i = 0; i<SIZE; i++){
            for(j = 0; j<SIZE; j++){
                if(pMat[i][j] == p+1){
                    last[p][0] = j;
                    last[p][1] = i;
                }
            }
        }
    }

    /// GAME
    do
    {
        for(i = 0; i<PLAYERS; i++){
            p = 0;
            for(j = 0; j<PLAYERS;j++){
                if(dead[j] == 1){
                    p++;
                }
            }
            if(p < PLAYERS-1){
            if(dead[i] == 0){
                mov = (*ias[i])(pMat,last[i],dep);

                if(mov[0] == 1){ /// TOP
                    if(last[i][1]-1 >= 0){
                        pMat[last[i][1]][last[i][0]] = (i + 1) * 10;
                        last[i][1]--;
                        printf("PLAYER %d : %d %d\n",i+1,last[i][0],last[i][1]);
                        if(pMat[last[i][1]][last[i][0]] <= 0){
                            pMat[last[i][1]][last[i][0]] = (i + 1);
                        }else{
                            dead[i] = 1;
                        }
                    }else{
                            dead[i] = 1;
                    }
                }else if(mov[0] == 2){ /// RIGHT
                    if(last[i][0]+1 <= len){
                        pMat[last[i][1]][last[i][0]] = (i + 1) * 10;
                        last[i][0]++;
                        printf("PLAYER %d : %d %d\n",i+1,last[i][0],last[i][1]);
                        if(pMat[last[i][1]][last[i][0]] <= 0){
                            pMat[last[i][1]][last[i][0]] = (i + 1);
                        }else{
                            dead[i] = 1;
                        }
                    }else{
                            dead[i] = 1;
                    }
                }else if(mov[0] == 3){ /// BOTTOM
                    if(last[i][1]+1 <= len){
                        pMat[last[i][1]][last[i][0]] = (i + 1) * 10;
                        last[i][1]++;
                        printf("PLAYER %d : %d %d\n",i+1,last[i][0],last[i][1]);
                        if(pMat[last[i][1]][last[i][0]] <= 0){
                            pMat[last[i][1]][last[i][0]] = (i + 1);
                        }else{
                            dead[i] = 1;
                        }
                    }else{
                            dead[i] = 1;
                    }
                }else if(mov[0] == 4){ /// LEFT
                    if(last[i][0]-1 >= 0){
                        pMat[last[i][1]][last[i][0]] = (i + 1) * 10;
                        last[i][0]--;
                        printf("PLAYER %d : %d %d\n",i+1,last[i][0],last[i][1]);
                        if(pMat[last[i][1]][last[i][0]] <= 0){
                            pMat[last[i][1]][last[i][0]] = (i + 1);
                        }else{
                            dead[i] = 1;
                        }
                    }else{
                            dead[i] = 1;
                    }
                }

                printTab(pMat);
                for(p = 0; p < PLAYERS; p++){
                    if (dead[p] == 1){
                        if(p==0){Color(3,0);}
                        else if(p==1){Color(10,0);}
                        else if(p==2){Color(12,0);}
                        else if(p==3){Color(15,0);}
                        else if(p==4){Color(14,0);}
                        printf("PLAYER %d DEAD \n", p+1);
                        Color(8,0);
                    }}

                Sleep(750);
                system("cls");

            }}
        }

        if(p == PLAYERS - 1){
            for(j = 0; j < PLAYERS; j++){
                if(dead[j] == 0){
                    winner = j +1;
                }
            }
        }else{
            winner = -1;
        }


    }while(winner < 0);


    if(winner==1){Color(3,0);}
    else if(winner==2){Color(10,0);}
    else if(winner==3){Color(12,0);}
    else if(winner==4){Color(15,0);}
    else if(winner==5){Color(14,0);}
    printf("\nJOUEUR %d A GAGNE\n",winner);
    Color(8,0);


    return 1;
}

int* ia1(int** pMat,int* last,int* dep){
    dep[0] = rand()%4 +1;
    return dep;
}


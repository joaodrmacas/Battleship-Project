//Trabalho Realizado por Diogo Lee Leitao 99917
//                       João Maçãs 99970

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>

#define MAXROW 15
#define MAXCOL 24

char board[MAXROW][MAXCOL];
unsigned int invisible[MAXROW][MAXCOL];
int row=9, column=9;
int shipcount, shipt[9]={0};
int shiptype[9] = {0},shiptype1[9] = {0};
void boardsize();
void initBoard();
void p1();
int p2();
void jogo1();
void jogo2();
int rest1();
void d1();
int d2();
int d3();
int rest3();
int rest4();
int p1getship();
void p2getship();
int randomInt();
void instrucoes();


int pieces[43][3][3] = {
    //Peça 0
    {{0,0,0},{0,0,0},{0,0,0}},
    //Peça 1
    {{1,0,0},{0,0,0},{0,0,0}},
    {{0,1,0},{0,0,0},{0,0,0}},
    {{0,0,1},{0,0,0},{0,0,0}},
    {{0,0,0},{1,0,0},{0,0,0}},
    {{0,0,0},{0,1,0},{0,0,0}},
    {{0,0,0},{0,0,1},{0,0,0}},
    {{0,0,0},{0,0,0},{1,0,0}},
    {{0,0,0},{0,0,0},{0,1,0}},
    {{0,0,0},{0,0,0},{0,0,1}},
    //Peça 2
    {{2,2,0},{0,0,0},{0,0,0}},
    {{0,2,2},{0,0,0},{0,0,0}},
    {{0,0,0},{2,2,0},{0,0,0}},
    {{0,0,0},{0,2,2},{0,0,0}},
    {{0,0,0},{0,0,0},{2,2,0}},
    {{0,0,0},{0,0,0},{0,2,2}},
    {{2,0,0},{2,0,0},{0,0,0}},
    {{0,0,0},{2,0,0},{2,0,0}},
    {{0,2,0},{0,2,0},{0,0,0}},
    {{0,0,0},{0,2,0},{0,2,0}},
    {{0,0,2},{0,0,2},{0,0,0}},
    {{0,0,0},{0,0,2},{0,0,2}},
    //Peça 3
    {{3,3,3},{0,0,0},{0,0,0}},
    {{0,0,0},{3,3,3},{0,0,0}},
    {{0,0,0},{0,0,0},{3,3,3}},
    {{3,0,0},{3,0,0},{3,0,0}},
    {{0,3,0},{0,3,0},{0,3,0}},
    {{0,0,3},{0,0,3},{0,0,3}},
    //Peça 4
    {{4,4,0},{4,4,0},{0,0,0}},
    {{0,4,4},{0,4,4},{0,0,0}},
    {{0,0,0},{4,4,0},{4,4,0}},
    {{0,0,0},{0,4,4},{0,4,4}},
    //Peça 5
    {{5,5,5},{0,5,0},{0,5,0}},
    {{5,0,0},{5,5,5},{5,0,0}},
    {{0,5,0},{0,5,0},{5,5,5}},
    {{0,0,5},{5,5,5},{0,0,5}},
    //Peça 6
    {{0,6,0},{6,0,6},{6,6,6}},
    {{0,6,6},{6,0,6},{0,6,6}},
    {{6,6,6},{6,0,6},{0,6,0}},
    {{6,6,0},{6,0,6},{6,6,0}},
    //Peça 7
    {{7,0,7},{7,7,7},{7,0,7}},
    {{7,7,7},{0,7,0},{7,7,7}},
    //Peça 8
    {{8,8,8},{8,0,8},{8,8,8}}};

int main(int argc, char **argv){

    int modojogo=0, posicionamento=1, disparo=1;
    int g=0,r=0;
    int option_val = 0;

    while((option_val = getopt(argc, argv, "ht:j:p:d:1:2:3:4:5:6:7:8:")) != -1){
        switch(option_val){
            case 'h':
                instrucoes();
                break;
            case 't':
                sscanf(optarg," %dx%d", &row, &column);
                if(!(row<=15 && column<=24 && row >= 9 && column >= 9 && row%3 == 0 && column%3 == 0)){
                printf("Invalid Input\n");
                exit(EXIT_FAILURE);
                }
                break;
            case 'j':
                sscanf(optarg, "%d", &modojogo);
                break;
            case 'p':
                sscanf(optarg, "%d", &posicionamento);
                break;
            case 'd':
                sscanf(optarg, "%d", &disparo);
                break;
            case '1':
                sscanf(optarg, "%d", &shiptype1[0]);
                shipcount += shiptype1[0]*1;
                break;
            case '2':
                sscanf(optarg, "%d", &shiptype1[1]);
                shipcount += shiptype1[1]*2;
                break;
            case '3':
                sscanf(optarg, "%d", &shiptype1[2]);
                shipcount += shiptype1[2]*3;
                break;
            case '4':
                sscanf(optarg, "%d", &shiptype1[3]);
                shipcount += shiptype1[3]*4;
                break;
            case '5':
                sscanf(optarg, "%d", &shiptype1[4]);
                shipcount += shiptype1[4]*5;
                break;
            case '6':
                sscanf(optarg, "%d", &shiptype1[5]);
                shipcount += shiptype1[5]*6;
                break;
            case '7':
                sscanf(optarg, "%d", &shiptype1[6]);
                shipcount += shiptype1[6]*7;
                break;
            case '8':
                sscanf(optarg, "%d", &shiptype1[7]);
                shipcount += shiptype1[7]*8;
                break;
            default: instrucoes();
        }
    }

    printf("\n");
    srand(time(NULL));
    switch (modojogo){
    case 0: // modo jogo 0
        if(posicionamento==1){ //modo de posicionamento 1
                for(g=0; g<8; g++){
                        if(shiptype1[g]!=0){ //verificar se existe parametros relativos ao numero de barcos de cada tipo e abrir instrucoes caso contrario
                            instrucoes();
                            return -1;
                        }
                }
                initBoard();
                p1(0);
                p1(1);
        }
        else if(posicionamento==2){ //modo de posicionamento 2
                initBoard();
                r=p2(0);
                if (r==-1){ //caso as restricoes impostas no modo posicionamento 2 nao sejam cumpridas (restriçao 3,4 e as mil tentativas)
                    instrucoes();
                    return -1;
                    }
                else p2(1);
        }
        break;
    case 1: //modo de jogo 1
        if(posicionamento==1){ //modo de posicionamento 1
            for(g=0; g<8; g++){
                    if(shiptype1[g]!=0){//verificar se existe parametros relativos ao numero de barcos de cada tipo e abrir instrucoes caso contrario
                        instrucoes();
                        return -1;
                    }
            }
                p1(0);
        }
        else if(posicionamento==2)p2(0); //modo de posicionamento 2
        jogo1();  //função relativa ao modo de jogo 1
        if(posicionamento==1) p1(1); //print dos boards finais
        else if(posicionamento==2) p2(1); //print dos boards finais
        break;
    case 2: //modo de jogo 2
        if(disparo==1){  //modo disparo 1
            d1();
        }
        else if(disparo==2){ //modo de disparo 2
            d2();
        }
        else if(disparo==3){ //modo de disparo 3
            d3();
        }
        break;
    }
    }


    //Inicializa o tabuleiro a 0's em todas as coordenadas
void initBoard(){
    int i, j;

    for(i=row; i>=0; i--){
        for(j=0;j<column;j++){
            board[i][j] = 0;
        }
    }
}

/*funcao relativa ao posicinamento 1 com argumento para formar o tabuleiro caso seja 0,
ou imprimir o tabuleiro caso seja 1*/
void p1(int print){

    int i, j;
    int shipstore[30][30]; //dar storage aos tipos de barcos do tabuleiro criado

    if(print==0){
    for(i = 0; i < row; i++){
        for(j = 0; j < column; j++){
            if(i%3==0&&j%3==0){ //caso se trate de uma celula no canto superior esquerdo de uma matriz 3x3, gerar um barco e atribuir os seus valores à matriz atual
                p1getship(i, j, shipstore);
            }
        }
    }
    }

    if(print==1){
        printf("%dx%d %d %d %d %d %d %d %d %d\n", row, column, shiptype1[0], shiptype1[1], shiptype1[2], shiptype1[3], shiptype1[4], shiptype1[5], shiptype1[6], shiptype1[7]);
        for(i = 0; i < row; i++){
        printf("%02d ", row -i);
        for(j = 0; j < column; j++){
                if(board[i][j] == 0) {printf("- ");}
                else {printf("%d ", board[i][j]);}
        }
        putchar('\n');
    }
    putchar(' ');
    putchar(' ');
    putchar(' ');                   //print do tabuleiro

    for(i = 1; i <= column; i++){
        printf("%c ", 64 + i);
    }
    putchar('\n');
    putchar('\n');
    putchar('\n');
    }
}

//funcao relativa a formacao e impressao do tabuleiro no modo de posicionamento 2
int p2(int print){
    int i=0, j=0, a=0, b=0;
    int counter=0;

    if(print==0){
    for(i=0;i<8;i++){                   //atribui a quantidade fixa de cada tipo de barco a um array temporário
        shiptype[i] = shiptype1[i];
    }


    a= rest3();                         //verifica as condições 3 e 4 e retorna -1 se não forem cumpridas
    b=rest4();
    if(a==0||b==0)return -1;

//while loop que verifica se ficaram barcos por posicionar no tabuleiro ou se tentou 1000 vezes criar o tabuleiro
    while((shiptype[0]!=0||shiptype[1]!=0||shiptype[2]!=0||shiptype[3]!=0||shiptype[4]!=0||shiptype[5]!=0||shiptype[6]!=0||shiptype[7]!=0)&&counter<1000){
    counter++;
//atribuir a quantidade fixa de cada tipo de barco a um array temporário para a tentativa de criar o tabuleiro atual
    for(i=0; i<8; i++){
        shiptype[i] = shiptype1[i];
    }
    putchar('\n');
    putchar('\n');
    for(i=0; i<row; i++){
        for(j=0; j<column; j++){
            if(i%3==0 && j%3==0){
                p2getship(i, j, shiptype); //arranjar um barco quando o tabuleiro se encontra no canto superior esquerdo de cada matriz 3x3
            }
        }
    }
    }
        if(counter>=1000){
        printf("Não conseguiu gerar o tabuleiro, número de tentativas = %d\n", counter);
        return -1;
        }
    }
    if(print==1){
    printf("%dx%d %d %d %d %d %d %d %d %d\n", row, column, shiptype1[0], shiptype1[1], shiptype1[2], shiptype1[3], shiptype1[4], shiptype1[5], shiptype1[6], shiptype1[7]);
    for(i=0; i<row; i++){
        printf("%02d ", row -i);
        for(j=0;j<column;j++){
                if(board[i][j]==0)printf("- ");
                else printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    putchar(' ');
    putchar(' ');
    putchar(' ');

    for(i = 1; i <= column; i++){ //print das colunas
        printf("%c ", 64 + i);
    }

    putchar('\n');
    }
    return 0;
}

//Funcao relativa a geracao de um barco para o modo de posicionamento 2 (incluindo a restricao 3 e 4)
void p2getship(int i, int j){

    int yesno=0, k=0, l=0, randomship=0, m=0, n=0, rest=0, a=0;

    if(shiptype[0]!=0||shiptype[1]!=0||shiptype[2]!=0||shiptype[3]!=0||shiptype[4]!=0||shiptype[5]!=0||shiptype[6]!=0||shiptype[7]!=0){

            while(rest != 1){ //procurar uma matriz até cumprir a restrição 1
            yesno = rand()%2; //probabilidade de sair uma matriz 0
            if(yesno!=0){      //matriz 0
                rest=1;
                for(k=0; k<3; k++){
                    for(l=0; l<3; l++){
                        board[i+k][j+l] = pieces[0][k][l];
                    }
                }
            }
            else{
            while(randomship==0){           //vai procurar um tipo de barco que tenha quantidade positiva
                m = rand()% 8;              //tipo de barco aleatório
                randomship = shiptype[m];   //atribui a quantidade do tipo de barco a randomship
            }
            if(m==0){                       //tipo 1
                randomship=0;
                a=0;
                n = rand()%9+1;             //variante aleatória
                while(rest==0&&a<9){        //verifica se a variante cumpre a restrição 1, caso não verifique tenta todas as variantes por ordem
                rest = rest1(i, j, n, pieces);
                if(rest==0)
                n = a+1;
                a++;
                }

            }

            else if(m==1){                  //tipo 2
                randomship=0;
                a=0;
                n = rand()%12+10;           //variante aleatória
                while(rest==0&&a<12){       //verifica se a variante cumpre a restrição 1, caso não verifique tenta todas as variantes por ordem
                rest = rest1(i, j, n, pieces);
                if(rest==0)
                n = a+10;
                a++;
                }
            }

            else if(m==2){                  //tipo 3
                randomship=0;
                a=0;
                n = rand()%6+22;            //variante aleatória
                while(rest==0&&a<6){        //verifica se a variante cumpre a restrição 1, caso não verifique tenta todas as variantes por ordem
                rest = rest1(i, j, n, pieces);
                if(rest==0)
                n = a+22;
                a++;
                }

            }

            else if(m==3){                  //tipo 4
                randomship=0;
                a=0;
                n = rand()%4+28;            //variante aleatória
                while(rest==0&&a<4){        //verifica se a variante cumpre a restrição 1, caso não verifique tenta todas as variantes por ordem
                rest = rest1(i, j, n, pieces);
                if(rest==0)
                n = a+28;
                a++;
                }
            }

            else if(m==4){                  //tipo 5
                randomship=0;
                a=0;
                n = rand()%4+32;            //variante aleatória
                while(rest==0&&a<4){        //verifica se a variante cumpre a restrição 1, caso não verifique tenta todas as variantes por ordem
                rest = rest1(i, j, n, pieces);
                if(rest==0)
                n = a+32;
                a++;
                }
            }

            else if(m==5){                  //tipo 6
                randomship=0;
                a=0;
                n = rand()%4+36;            //variante aleatória
                while(rest==0&&a<4){        //verifica se a variante cumpre a restrição 1, caso não verifique tenta todas as variantes por ordem
                rest = rest1(i, j, n, pieces);
                if(rest==0)
                n = a+36;
                a++;
                }
            }

            else if(m==6){                  //tipo 7
                randomship=0;
                a=0;
                n = rand()%2+40;            //variante aleatória
                while(rest==0&&a<2){        //verifica se a variante cumpre a restrição 1, caso não verifique tenta todas as variantes por ordem
                rest = rest1(i, j, n, pieces);
                if(rest==0)
                n = a+40;
                a++;
                }
            }

            else if(m==7){                  //tipo 8
                n = 42;
                randomship=0;
                rest = rest1(i, j, n, pieces);
            }

//caso tenha cumprido a restrição 1, atribuir os valores ao board da peça gerada
            if(rest==1){
                for(k=0; k<3; k++){
                    for(l=0; l<3; l++){
                        board[i+k][j+l] = pieces[n][k][l];
                    }
                }
                shiptype[m]--;
            }
            }
        }
        rest = 0;
    }
    else{                                   //caso todos os barcos já tenham sido colocados preencher com uma matriz 0
            for(k=0; k<3; k++){
                for(l=0; l<3; l++){
                    board[i+k][j+l] = pieces[0][k][l];
                }
            }
        }
}

//funcao relativa a criacao de barcos no modo p1
int p1getship(int i, int j, int shipstore[50][50]){

    int rt=0, rn=0, shipvalue, a=0, k, l, m=0;

    do{
       rt = rand() % 9;             //gera um tipo de barco ou matriz 0
       if(rt==0){                   //matriz 0
            rn = 0;
            a = rest1(i, j, rn);
            m++;}
       else if(rt==1){              //tipo 1
            rn = rand()%9+1;
            a = rest1(i, j, rn);
            m++;}
       else if(rt==2){              //tipo 2
            rn = rand()%12+10;
            a = rest1(i, j, rn);
            m++;}
       else if(rt==3){              //tipo 3
            rn = rand()%6+22;
            a = rest1(i, j, rn);
            m++;}
       else if(rt==4){              //tipo 4
            rn = rand()%4+28;
            a = rest1(i, j, rn);
            m++;}
       else if(rt==5){              //tipo 5
            rn = rand()%4+32;
            a = rest1(i, j, rn);
            m++;}
       else if(rt==6){              //tipo 6
            rn = rand()%4+36;
            a = rest1(i, j, rn);
            m++;}
       else if(rt==7){              //tipo 7
            rn = rand()%2+40;
            a = rest1(i, j, rn);
            m++;}
       else if(rt==8){              //tipo 8
            rn = 42;
            a = rest1(i, j, rn);
            m++;}
    }while(a==0&&m<4);              //tenta gerar um barco 3 vezes ou até o barco cumprir a restrição 1

    if(m>3)rn = 5;                  //caso não consiga após 3 tentativas, coloca um barco tipo 5, isto é, peça 1 tipo centrada

    for(k=0; k<3; k++){             //atribuir os valores do barco ao tabuleiro
        for(l=0; l<3; l++){
            board[i+k][j+l] = pieces[rn][k][l];
        }
    }
//contagem das células do tabuleiro que contêm barcos
    if(rn>0&&rn<=9){shipcount++; shiptype1[0]++;}
    else if(rn>9&&rn<=21){shipcount=shipcount+2; shiptype1[1]++;}
    else if(rn>21&&rn<=27){shipcount=shipcount+3; shiptype1[2]++;}
    else if(rn>27&&rn<=31){shipcount=shipcount+4; shiptype1[3]++;}
    else if(rn>31&&rn<=35){shipcount=shipcount+5; shiptype1[4]++;}
    else if(rn>35&&rn<=39){shipcount=shipcount+6; shiptype1[5]++;}
    else if(rn>39&&rn<=41){shipcount=shipcount+7; shiptype1[6]++;}
    else if(rn==42){shipcount=shipcount+8; shiptype1[7]++;}
    shipstore[i][j] = rn;
    shipvalue = pieces[rn][i%3][j%3];

    return shipvalue;
}

//funcao relativa ao modo de disparo 1
void d1(){

    unsigned long start_t=0, end_t=0, total_t=0; //definição do cronometro
    int i, j, shotscount=0, r=0, c=0, repetido[row][column], tentativas=0;
    char a;

    printf("* ================================\n");
    printf("* Modo de Jogo 2\n");
    printf("* Crie um tabuleiro com as características indicadas\n");
    printf("* Responda aos disparos do programa\n");
    printf("* ================================\n");
    printf("%dx%d %d %d %d %d %d %d %d %d\n", row, column, shiptype1[0], shiptype1[1], shiptype1[2], shiptype1[3], shiptype1[4], shiptype1[5], shiptype1[6], shiptype1[7]);

    for(i=0; i<row; i++){
        for(j=0;j<column;j++){
            repetido[i][j] = 0;
        }
    }
    start_t = time(NULL); //incio do timer
    do{
        a = 0;
        do{
        r = randomInt(row);   //dar um valor random de coordenadas.
        c = randomInt(column);
        }while(repetido[r][c]!=0); //repete enquanto der coordenadas ja utilizadas
        repetido[r][c]=1;
        tentativas++;
        printf("%c%d", c+64, r);
        putchar('\n');
        scanf(" %c", &a);  //valor da célula do utilizador nas coordenadas geradas e atribuição dessas no tabuleiro.
        if(a!='-'){
            shotscount++;
            switch(a){
            case '1':
                board[row-r][c-1]=1;
                break;
            case '2':
                board[row-r][c-1]=2;
            break;
            case '3':
                board[row-r][c-1]=3;
                break;
            case '4':
                board[row-r][c-1]=4;
                break;
            case '5':
                board[row-r][c-1]=5;
                break;
            case '6':
                board[row-r][c-1]=6;
                break;
            case '7':
                board[row-r][c-1]=7;
                break;
            case '8':
                board[row-r][c-1]=8;
                break;
            default: printf("Invalid\n");
            }
        }

    }while(shotscount<shipcount); //condicao para repetir enquanto nao tiver afundado todos os barcos

    end_t = time(NULL); //fim do timer
    total_t = end_t - start_t;
    printf("Fim de Jogo: %d tentativas em %lu segundos.\n", tentativas, total_t);

    for(i=0; i<row; i++){
        printf("%02d ", row -i);
        for(j=0;j<column;j++){
            if(board[i][j]==0)printf("- ");
            else printf("%d ", board[i][j]);
        }
        printf("\n");
    }                                           //print do board final criado pelo utilizador

    putchar(' ');
    putchar(' ');
    putchar(' ');

    for(i = 1; i <= column; i++){
        printf("%c ", 64 + i);}

    putchar('\n');
}


//funcao relativa ao modo de disparo 2
//o invisible board, foi utilizado para atribuir valores logicos a cada celula de forma a que se pudesse printar o board sem mudar os seus valores:
//Legenda: quando invisible[x][y]==9 --> coordenadas a ser analisadas
        // quando invisible[x][y]==10 --> representacao de um barco no board
        //  quando invisible[x][y]==11 --> representacao da agua no board
int d2(){
    unsigned long start_t=0, end_t=0, total_t=0;
    int r=0, c=0, k,j,i,s=1;
    int x=0,y=0;
    int b,v;
    char input;
    int counter=0;
    int count=0;
    int cunt=0;
    start_t = time(NULL);
    initBoard();

    printf(" * ================================\n");
    printf(" * Modo de Jogo 2\n");
    printf(" * Crie um tabuleiro com as características indicadas\n");
    printf(" * Responda aos disparos do programa\n");
    printf(" * ================================\n");
    printf("%dx%d %d %d %d %d %d %d %d %d\n", row, column, shiptype1[0], shiptype1[1], shiptype1[2], shiptype1[3], shiptype1[4], shiptype1[5], shiptype1[6], shiptype1[7]);

    //loop para analisar matrizes 3x3 individualmente dentro da matriz do tabuleiro.

    for(b=0; b<row;){
        b=b+3;
            for(v=0;v<column;){
                v=v+3;
                for (k=1; k<=9; k++){
                    if(s==1){r=2+x,c=2+y;} //atribuicao do valor das coordenadas selecionadas pela ordem do algoritmo
                    if(s==2){r=1+x,c=2+y;}
                    if(s==3){r=3+x;c=2+y;}
                    if(s==4){r=2+x;c=1+y;}
                    if(s==5){r=2+x;c=3+y;}
                    if(s==6){r=1+x;c=1+y;}
                    if(s==7){r=3+x;c=3+y;}
                    if(s==8){r=1+x;c=3+y;}
                    if(s==9){r=3+x;c=1+y;s=0;if(board[r-1][c-1]==0&&invisible[r-1][c]==11&&invisible[r-2][c]==11&&invisible[r-2][c+1]==11&&invisible[r-2][c+2]==11&&invisible[r-1][c+1]==11&&invisible[r-1][c+2]==11&&invisible[r][c+1]==11&&invisible[r][c+2]==11)y=y+3;} //caso a matriz 3x3 seja vazia, seguir para a proxima matriz
                    invisible[r][c] = 9;
                    s++;
                    if(cunt>=shipcount){ //caso tenha acertado no numero total de celulas com barcos, termina a funcao
                            end_t = time(NULL);
                            total_t = end_t - start_t;
                            printf("Fim de Jogo: %d tentativas em %lu segundos.\n", count, total_t);
                            for( i = 0; i < row; i++){
                                printf("%02d ", row -i);
                                for(j = 0; j < column; j++){
                                if(invisible[i+1][j+1]==9){
                                    if(board[r-1][c-1]!=0){
                                    printf("%d ", board[i][j]);
                                }
                                else if(board[r-1][c-1]==0){
                                        invisible[r][c]=11;
                                        printf("- ");
                                        }
                                }
                                else if(invisible[i+1][j+1]==10) printf("%d ", board[i][j]);
                                else printf("- ");
                                }
                                printf("\n");
                                }
                                putchar(' ');
                                putchar(' ');
                                putchar(' ');

                                for(i = 1; i <= column; i++){
                                    printf("%c ", 64 + i);
                                }
                                    return 0;
                            }
                    printf("%c%d\n",c+64, row-r+1); //celelua em questao
                    scanf(" %c", &input);
                    count++;
                        if(input!='-'){
                            switch(input){
                            case '1':
                                board[r-1][c-1]=1;
                                break;
                            case '2':
                                board[r-1][c-1]=2;
                            break;
                            case '3':
                                board[r-1][c-1]=3;
                                break;
                            case '4':
                                board[r-1][c-1]=4;
                                break;
                            case '5':
                                board[r-1][c-1]=5;
                                break;
                            case '6':
                                board[r-1][c-1]=6;
                                break;
                            case '7':
                                board[r-1][c-1]=7;
                                break;
                            case '8':
                                board[r-1][c-1]=8;
                                break;
                            }
                        }
                    for( i = 0; i < row; i++){
                        for(j = 0; j < column; j++){
                            if(invisible[i+1][j+1]==9){
                                if(board[r-1][c-1]!=0){
                                cunt++; //contador de barcos afundados
                                counter++; //verifica se ja acertou em todas as celulas conforme o tipo de barco
                                invisible[r][c]=10; //atribuicao do valor do barco
                                    switch(board[r-1][c-1]){
                                        case 1:
                                            k=10;
                                            s=1;
                                            y=y+3;
                                            counter=0;
                                            break;
                                        case 2:
                                            if(counter==2){
                                                k=10;
                                                s=1;
                                                y=y+3;
                                                counter=0;
                                                break;
                                            }
                                        case 3:
                                            if(counter==3){
                                                k=10;
                                                s=1;
                                                y=y+3;
                                                counter=0;
                                                break;
                                            }
                                        case 4:
                                            if(counter==4){
                                                k=10;
                                                s=1;
                                                y=y+3;
                                                counter=0;
                                                break;
                                            }
                                        case 5:
                                            if(counter==5){
                                                k=10;
                                                s=1;
                                                y=y+3;
                                                counter=0;
                                                break;
                                            }
                                        case 6:
                                            if(counter==6){
                                                k=10;
                                                s=1;
                                                y=y+3;
                                                counter=0;
                                                break;
                                            }
                                        case 7:
                                            if(counter==7){
                                                k=10;
                                                s=1;
                                                y=y+3;
                                                counter=0;
                                                break;
                                            }
                                        case 8:
                                            if(counter==8){
                                                k=10;
                                                s=1;
                                                y=y+3;
                                                counter=0;
                                                break;
                                            }
                                    }
                                }
                            else if(board[r-1][c-1]==0){
                                invisible[r][c]=11; //atribuicao do valor da agua
                                }
                            }
                        }
                    }
                }
            }
            y=0; //vai para a primeira coluna
            x=x+3; //passa para a proxima linha de matrizes
    }
                            end_t = time(NULL);
                            total_t = end_t - start_t;
                            printf("Fim de Jogo: %d tentativas em %lu segundos.\n", count, total_t);
                            for( i = 0; i < row; i++){
                                printf("%02d ", row -i);
                                for(j = 0; j < column; j++){
                                if(invisible[i+1][j+1]==9){
                                    if(board[r-1][c-1]!=0){
                                    printf("%d ", board[i][j]);
                                }
                                else if(board[r-1][c-1]==0){
                                        invisible[r][c]=11;
                                        printf("- ");
                                        }
                                }
                                else if(invisible[i+1][j+1]==10) printf("%d ", board[i][j]);
                                else printf("- ");
                                }
                                printf("\n");
                                }
                                putchar(' ');
                                putchar(' ');
                                putchar(' ');

                                for(i = 1; i <= column; i++){
                                    printf("%c ", 64 + i);
                                }
                                    return 0;
}

//funcao relativa ao modo de disparo 2
//o invisible board, foi utilizado para atribuir valores logicos a cada celula de forma a que se pudesse printar o board sem mudar os seus valores:
//Legenda: quando invisible[x][y]==9 --> coordenadas a ser analisadas
        // quando invisible[x][y]==10 --> representacao de um barco no board
        //  quando invisible[x][y]==11 --> representacao da agua no board
        //  quando invisible[x][y]==12 --> representacao de celulas que nao podem ser atingindas no board
int d3(){
    unsigned long start_t=0, end_t=0, total_t=0;
    int r=0, c=0, k,j,i,s=1;
    int x=0,y=0;
    int b,v;
    char input;
    int saveR[9]={0};
    int saveC[9]={0};
    int count=0;
    int counter=0;
    int cunt=0;

    initBoard();

    printf(" * ================================\n");
    printf(" * Modo de Jogo 2\n");
    printf(" * Crie um tabuleiro com as características indicadas\n");
    printf(" * Responda aos disparos do programa\n");
    printf(" * ================================\n");
    printf("%dx%d %d %d %d %d %d %d %d %d\n", row, column, shiptype1[0], shiptype1[1], shiptype1[2], shiptype1[3], shiptype1[4], shiptype1[5], shiptype1[6], shiptype1[7]);

    start_t = time(NULL);

    for(b=0; b<row;){
        b=b+3; //avanca para a proxima linha
            for(v=0;v<column;){
                v=v+3; //avanca para a proxima matriz da mesma linha
                for (k=1; k<=9; k++){
                    do{
                    if(s==1){r=2+x,c=2+y;} //algoritmo de disparo
                    if(s==2){r=1+x,c=2+y;}
                    if(s==3){r=3+x;c=2+y;}
                    if(s==4){r=2+x;c=1+y;}
                    if(s==5){r=2+x;c=3+y;}
                    if(s==6){r=1+x;c=1+y;}
                    if(s==7){r=3+x;c=3+y;}
                    if(s==8){r=1+x;c=3+y;}
                    if(s==9){r=3+x;c=1+y;s=0;if((board[r-1][c-1]==0)&&(invisible[r-1][c]==11||invisible[r-1][c]==12)&&(invisible[r-2][c]==11||invisible[r-2][c]==12)&&(invisible[r-2][c+1]==11||invisible[r-2][c+1]==12)&&(invisible[r-2][c+2]==11||invisible[r-2][c+2]==12)&&(invisible[r-1][c+1]==11||invisible[r-1][c+1]==12)&&(invisible[r-1][c+2]==11||invisible[r-1][c+2]==12)&&(invisible[r][c+1]==11||invisible[r][c+1]==12)&&(invisible[r][c+2]==11||invisible[r][c+2]==12))y=y+3;}//condicao caso a matriz 3x3 seja vazia, passar para a proxima
                    if(invisible[r][c]!=12)invisible[r][c] = 9; //coordenada atual
                    s++;
                    if(cunt>=shipcount){ //condicao para acabar quando todos os barcos afundarem
                            end_t = time(NULL);
                            total_t = end_t - start_t;
                            printf("Fim de Jogo: %d tentativas em %lu segundos.\n", count, total_t);
                            //print do board final
                            for( i = 0; i < row; i++){
                                printf("%02d ", row -i);
                                for(j = 0; j < column; j++){
                                if(invisible[i+1][j+1]==9){
                                    if(board[r-1][c-1]!=0){
                                    printf("%d ", board[i][j]);
                                }
                                else if(board[r-1][c-1]==0){
                                        invisible[r][c]=11;
                                        printf("- ");
                                        }
                                }
                                else if(invisible[i+1][j+1]==10) printf("%d ", board[i][j]);
                                else printf("- ");
                                }
                                printf("\n");
                                }
                                putchar(' ');
                                putchar(' ');
                                putchar(' ');

                                for(i = 1; i <= column; i++){
                                    printf("%c ", 64 + i);
                                }
                                    return 0;
                            }
                    }while(invisible[r][c]==12); //nao diparar caso seja uma celula a x
                    printf("%c%d\n",c+64, row-r+1);
                    scanf(" %c", &input);
                    count++;
                        if(input!='-'){
                            switch(input){
                            case '1':
                                board[r-1][c-1]=1;
                                break;
                            case '2':
                                board[r-1][c-1]=2;
                            break;
                            case '3':
                                board[r-1][c-1]=3;
                                break;
                            case '4':
                                board[r-1][c-1]=4;
                                break;
                            case '5':
                                board[r-1][c-1]=5;
                                break;
                            case '6':
                                board[r-1][c-1]=6;
                                break;
                            case '7':
                                board[r-1][c-1]=7;
                                break;
                            case '8':
                                board[r-1][c-1]=8;
                                break;
                            }
                        }
                    for( i = 0; i < row; i++){
                        for(j = 0; j < column; j++){
                            if(invisible[i+1][j+1]==9){
                                if(board[r-1][c-1]!=0){
                                counter++; //incremento para determinar o numero de celulas do barco na matriz
                                cunt++; //incremento de acertar numa celula de barco
                                invisible[r][c]=10; //atirbuicao do valor de um barco
                                    switch(board[r-1][c-1]){
                                        case 1:
                                                saveR[counter]=r; //guardar as coordenadas dos barcos atingidos
                                                saveC[counter]=c;
                                            k=10; //terminar o for loop
                                            s=1; //reset do algoritmo
                                            y=y+3;//passar para a proxima linha depois de atingir as celulas do barco
                                            counter=0; //reset do counter
                                            //atribuicao dos valores x em volta de todas as particulas do barco 1
                                            if(invisible[saveR[1]-1][saveC[1]-1]!=10&&invisible[saveR[1]-1][saveC[1]-1]!=11)invisible[saveR[1]-1][saveC[1]-1]=12;
                                            if(invisible[saveR[1]-1][saveC[1]]!=10&&invisible[saveR[1]-1][saveC[1]]!=11)invisible[saveR[1]-1][saveC[1]]=12;
                                            if(invisible[saveR[1]-1][saveC[1]+1]!=10&&invisible[saveR[1]-1][saveC[1]+1]!=11)invisible[saveR[1]-1][saveC[1]+1]=12;
                                            if(invisible[saveR[1]][saveC[1]-1]!=10&&invisible[saveR[1]][saveC[1]-1]!=11)invisible[saveR[1]][saveC[1]-1]=12;
                                            if(invisible[saveR[1]][saveC[1]+1]!=10&&invisible[saveR[1]][saveC[1]+1]!=11)invisible[saveR[1]][saveC[1]+1]=12;
                                            if(invisible[saveR[1]+1][saveC[1]-1]!=10&&invisible[saveR[1]+1][saveC[1]-1]!=11)invisible[saveR[1]+1][saveC[1]-1]=12;
                                            if(invisible[saveR[1]+1][saveC[1]]!=10&&invisible[saveR[1]+1][saveC[1]]!=11)invisible[saveR[1]+1][saveC[1]]=12;
                                            if(invisible[saveR[1]+1][saveC[1]+1]!=10&&invisible[saveR[1]+1][saveC[1]+1]!=11)invisible[saveR[1]+1][saveC[1]+1]=12;
                                            break;
                                        case 2:
                                                saveR[counter]=r;
                                                saveC[counter]=c;  //guardar as coordenadas de cada particula
                                            if(counter==2){
                                                k=10;
                                                s=1;
                                                y=y+3;
                                                counter=0;
                                                //atribuicao dos valores x em volta de todas as particulas do barco 2
                                                if(invisible[saveR[1]-1][saveC[1]-1]!=10&&invisible[saveR[1]-1][saveC[1]-1]!=11)invisible[saveR[1]-1][saveC[1]-1]=12;
                                                if(invisible[saveR[1]-1][saveC[1]]!=10&&invisible[saveR[1]-1][saveC[1]]!=11)invisible[saveR[1]-1][saveC[1]]=12;
                                                if(invisible[saveR[1]-1][saveC[1]+1]!=10&&invisible[saveR[1]-1][saveC[1]+1]!=11)invisible[saveR[1]-1][saveC[1]+1]=12;
                                                if(invisible[saveR[1]][saveC[1]-1]!=10&&invisible[saveR[1]][saveC[1]-1]!=11)invisible[saveR[1]][saveC[1]-1]=12;
                                                if(invisible[saveR[1]][saveC[1]+1]!=10&&invisible[saveR[1]][saveC[1]+1]!=11)invisible[saveR[1]][saveC[1]+1]=12;
                                                if(invisible[saveR[1]+1][saveC[1]-1]!=10&&invisible[saveR[1]+1][saveC[1]-1]!=11)invisible[saveR[1]+1][saveC[1]-1]=12;
                                                if(invisible[saveR[1]+1][saveC[1]]!=10&&invisible[saveR[1]+1][saveC[1]]!=11)invisible[saveR[1]+1][saveC[1]]=12;
                                                if(invisible[saveR[1]+1][saveC[1]+1]!=10&&invisible[saveR[1]+1][saveC[1]+1]!=11)invisible[saveR[1]+1][saveC[1]+1]=12;

                                                if(invisible[saveR[2]-1][saveC[2]-1]!=10&&invisible[saveR[2]-1][saveC[2]-1]!=11)invisible[saveR[2]-1][saveC[2]-1]=12;
                                                if(invisible[saveR[2]-1][saveC[2]]!=10&&invisible[saveR[2]-1][saveC[2]]!=11)invisible[saveR[2]-1][saveC[2]]=12;
                                                if(invisible[saveR[2]-1][saveC[2]+1]!=10&&invisible[saveR[2]-1][saveC[2]+1]!=11)invisible[saveR[2]-1][saveC[2]+1]=12;
                                                if(invisible[saveR[2]][saveC[2]-1]!=10&&invisible[saveR[2]][saveC[2]-1]!=11)invisible[saveR[2]][saveC[2]-1]=12;
                                                if(invisible[saveR[2]][saveC[2]+1]!=10&&invisible[saveR[2]][saveC[2]+1]!=11)invisible[saveR[2]][saveC[2]+1]=12;
                                                if(invisible[saveR[2]+1][saveC[2]-1]!=10&&invisible[saveR[2]+1][saveC[2]-1]!=11)invisible[saveR[2]+1][saveC[2]-1]=12;
                                                if(invisible[saveR[2]+1][saveC[2]]!=10&&invisible[saveR[2]+1][saveC[2]]!=11)invisible[saveR[2]+1][saveC[2]]=12;
                                                if(invisible[saveR[2]+1][saveC[2]+1]!=10&&invisible[saveR[2]+1][saveC[2]+1]!=11)invisible[saveR[2]+1][saveC[2]+1]=12;
                                                break;
                                            }
                                        case 3:
                                            saveR[counter]=r;
                                            saveC[counter]=c;

                                            if(counter==3){
                                                k=10;
                                                s=1;
                                                y=y+3;
                                                counter=0;
                                                //atribuicao dos valores x em volta de todas as particulas do barco 3
                                                if(invisible[saveR[1]-1][saveC[1]-1]!=10&&invisible[saveR[1]-1][saveC[1]-1]!=11)invisible[saveR[1]-1][saveC[1]-1]=12;
                                                if(invisible[saveR[1]-1][saveC[1]]!=10&&invisible[saveR[1]-1][saveC[1]]!=11)invisible[saveR[1]-1][saveC[1]]=12;
                                                if(invisible[saveR[1]-1][saveC[1]+1]!=10&&invisible[saveR[1]-1][saveC[1]+1]!=11)invisible[saveR[1]-1][saveC[1]+1]=12;
                                                if(invisible[saveR[1]][saveC[1]-1]!=10&&invisible[saveR[1]][saveC[1]-1]!=11)invisible[saveR[1]][saveC[1]-1]=12;
                                                if(invisible[saveR[1]][saveC[1]+1]!=10&&invisible[saveR[1]][saveC[1]+1]!=11)invisible[saveR[1]][saveC[1]+1]=12;
                                                if(invisible[saveR[1]+1][saveC[1]-1]!=10&&invisible[saveR[1]+1][saveC[1]-1]!=11)invisible[saveR[1]+1][saveC[1]-1]=12;
                                                if(invisible[saveR[1]+1][saveC[1]]!=10&&invisible[saveR[1]+1][saveC[1]]!=11)invisible[saveR[1]+1][saveC[1]]=12;
                                                if(invisible[saveR[1]+1][saveC[1]+1]!=10&&invisible[saveR[1]+1][saveC[1]+1]!=11)invisible[saveR[1]+1][saveC[1]+1]=12;

                                                if(invisible[saveR[2]-1][saveC[2]-1]!=10&&invisible[saveR[2]-1][saveC[2]-1]!=11)invisible[saveR[2]-1][saveC[2]-1]=12;
                                                if(invisible[saveR[2]-1][saveC[2]]!=10&&invisible[saveR[2]-1][saveC[2]]!=11)invisible[saveR[2]-1][saveC[2]]=12;
                                                if(invisible[saveR[2]-1][saveC[2]+1]!=10&&invisible[saveR[2]-1][saveC[2]+1]!=11)invisible[saveR[2]-1][saveC[2]+1]=12;
                                                if(invisible[saveR[2]][saveC[2]-1]!=10&&invisible[saveR[2]][saveC[2]-1]!=11)invisible[saveR[2]][saveC[2]-1]=12;
                                                if(invisible[saveR[2]][saveC[2]+1]!=10&&invisible[saveR[2]][saveC[2]+1]!=11)invisible[saveR[2]][saveC[2]+1]=12;
                                                if(invisible[saveR[2]+1][saveC[2]-1]!=10&&invisible[saveR[2]+1][saveC[2]-1]!=11)invisible[saveR[2]+1][saveC[2]-1]=12;
                                                if(invisible[saveR[2]+1][saveC[2]]!=10&&invisible[saveR[2]+1][saveC[2]]!=11)invisible[saveR[2]+1][saveC[2]]=12;
                                                if(invisible[saveR[2]+1][saveC[2]+1]!=10&&invisible[saveR[2]+1][saveC[2]+1]!=11)invisible[saveR[2]+1][saveC[2]+1]=12;

                                                if(invisible[saveR[3]-1][saveC[3]-1]!=10&&invisible[saveR[3]-1][saveC[3]-1]!=11)invisible[saveR[3]-1][saveC[3]-1]=12;
                                                if(invisible[saveR[3]-1][saveC[3]]!=10&&invisible[saveR[3]-1][saveC[3]]!=11)invisible[saveR[3]-1][saveC[3]]=12;
                                                if(invisible[saveR[3]-1][saveC[3]+1]!=10&&invisible[saveR[3]-1][saveC[3]+1]!=11)invisible[saveR[3]-1][saveC[3]+1]=12;
                                                if(invisible[saveR[3]][saveC[3]-1]!=10&&invisible[saveR[3]][saveC[3]-1]!=11)invisible[saveR[3]][saveC[3]-1]=12;
                                                if(invisible[saveR[3]][saveC[3]+1]!=10&&invisible[saveR[3]][saveC[3]+1]!=11)invisible[saveR[3]][saveC[3]+1]=12;
                                                if(invisible[saveR[3]+1][saveC[3]-1]!=10&&invisible[saveR[3]+1][saveC[3]-1]!=11)invisible[saveR[3]+1][saveC[3]-1]=12;
                                                if(invisible[saveR[3]+1][saveC[3]]!=10&&invisible[saveR[3]+1][saveC[3]]!=11)invisible[saveR[3]+1][saveC[3]]=12;
                                                if(invisible[saveR[3]+1][saveC[3]+1]!=10&&invisible[saveR[3]+1][saveC[3]+1]!=11)invisible[saveR[3]+1][saveC[3]+1]=12;
                                            }
                                        case 4:
                                        saveR[counter]=r;
                                        saveC[counter]=c;
                                            if(counter==4){
                                                k=10;
                                                s=1;
                                                y=y+3;
                                                counter=0;
                                                //atribuicao dos valores x em volta de todas as particulas do barco 4
                                                if(invisible[saveR[1]-1][saveC[1]-1]!=10&&invisible[saveR[1]-1][saveC[1]-1]!=11)invisible[saveR[1]-1][saveC[1]-1]=12;
                                                if(invisible[saveR[1]-1][saveC[1]]!=10&&invisible[saveR[1]-1][saveC[1]]!=11)invisible[saveR[1]-1][saveC[1]]=12;
                                                if(invisible[saveR[1]-1][saveC[1]+1]!=10&&invisible[saveR[1]-1][saveC[1]+1]!=11)invisible[saveR[1]-1][saveC[1]+1]=12;
                                                if(invisible[saveR[1]][saveC[1]-1]!=10&&invisible[saveR[1]][saveC[1]-1]!=11)invisible[saveR[1]][saveC[1]-1]=12;
                                                if(invisible[saveR[1]][saveC[1]+1]!=10&&invisible[saveR[1]][saveC[1]+1]!=11)invisible[saveR[1]][saveC[1]+1]=12;
                                                if(invisible[saveR[1]+1][saveC[1]-1]!=10&&invisible[saveR[1]+1][saveC[1]-1]!=11)invisible[saveR[1]+1][saveC[1]-1]=12;
                                                if(invisible[saveR[1]+1][saveC[1]]!=10&&invisible[saveR[1]+1][saveC[1]]!=11)invisible[saveR[1]+1][saveC[1]]=12;
                                                if(invisible[saveR[1]+1][saveC[1]+1]!=10&&invisible[saveR[1]+1][saveC[1]+1]!=11)invisible[saveR[1]+1][saveC[1]+1]=12;

                                                if(invisible[saveR[2]-1][saveC[2]-1]!=10&&invisible[saveR[2]-1][saveC[2]-1]!=11)invisible[saveR[2]-1][saveC[2]-1]=12;
                                                if(invisible[saveR[2]-1][saveC[2]]!=10&&invisible[saveR[2]-1][saveC[2]]!=11)invisible[saveR[2]-1][saveC[2]]=12;
                                                if(invisible[saveR[2]-1][saveC[2]+1]!=10&&invisible[saveR[2]-1][saveC[2]+1]!=11)invisible[saveR[2]-1][saveC[2]+1]=12;
                                                if(invisible[saveR[2]][saveC[2]-1]!=10&&invisible[saveR[2]][saveC[2]-1]!=11)invisible[saveR[2]][saveC[2]-1]=12;
                                                if(invisible[saveR[2]][saveC[2]+1]!=10&&invisible[saveR[2]][saveC[2]+1]!=11)invisible[saveR[2]][saveC[2]+1]=12;
                                                if(invisible[saveR[2]+1][saveC[2]-1]!=10&&invisible[saveR[2]+1][saveC[2]-1]!=11)invisible[saveR[2]+1][saveC[2]-1]=12;
                                                if(invisible[saveR[2]+1][saveC[2]]!=10&&invisible[saveR[2]+1][saveC[2]]!=11)invisible[saveR[2]+1][saveC[2]]=12;
                                                if(invisible[saveR[2]+1][saveC[2]+1]!=10&&invisible[saveR[2]+1][saveC[2]+1]!=11)invisible[saveR[2]+1][saveC[2]+1]=12;

                                                if(invisible[saveR[3]-1][saveC[3]-1]!=10&&invisible[saveR[3]-1][saveC[3]-1]!=11)invisible[saveR[3]-1][saveC[3]-1]=12;
                                                if(invisible[saveR[3]-1][saveC[3]]!=10&&invisible[saveR[3]-1][saveC[3]]!=11)invisible[saveR[3]-1][saveC[3]]=12;
                                                if(invisible[saveR[3]-1][saveC[3]+1]!=10&&invisible[saveR[3]-1][saveC[3]+1]!=11)invisible[saveR[3]-1][saveC[3]+1]=12;
                                                if(invisible[saveR[3]][saveC[3]-1]!=10&&invisible[saveR[3]][saveC[3]-1]!=11)invisible[saveR[3]][saveC[3]-1]=12;
                                                if(invisible[saveR[3]][saveC[3]+1]!=10&&invisible[saveR[3]][saveC[3]+1]!=11)invisible[saveR[3]][saveC[3]+1]=12;
                                                if(invisible[saveR[3]+1][saveC[3]-1]!=10&&invisible[saveR[3]+1][saveC[3]-1]!=11)invisible[saveR[3]+1][saveC[3]-1]=12;
                                                if(invisible[saveR[3]+1][saveC[3]]!=10&&invisible[saveR[3]+1][saveC[3]]!=11)invisible[saveR[3]+1][saveC[3]]=12;
                                                if(invisible[saveR[3]+1][saveC[3]+1]!=10&&invisible[saveR[3]+1][saveC[3]+1]!=11)invisible[saveR[3]+1][saveC[3]+1]=12;

                                                if(invisible[saveR[4]-1][saveC[4]-1]!=10&&invisible[saveR[4]-1][saveC[4]-1]!=11)invisible[saveR[4]-1][saveC[4]-1]=12;
                                                if(invisible[saveR[4]-1][saveC[4]]!=10&&invisible[saveR[4]-1][saveC[4]]!=11)invisible[saveR[4]-1][saveC[4]]=12;
                                                if(invisible[saveR[4]-1][saveC[4]+1]!=10&&invisible[saveR[4]-1][saveC[4]+1]!=11)invisible[saveR[4]-1][saveC[4]+1]=12;
                                                if(invisible[saveR[4]][saveC[4]-1]!=10&&invisible[saveR[4]][saveC[4]-1]!=11)invisible[saveR[4]][saveC[4]-1]=12;
                                                if(invisible[saveR[4]][saveC[4]+1]!=10&&invisible[saveR[4]][saveC[4]+1]!=11)invisible[saveR[4]][saveC[4]+1]=12;
                                                if(invisible[saveR[4]+1][saveC[4]-1]!=10&&invisible[saveR[4]+1][saveC[4]-1]!=11)invisible[saveR[4]+1][saveC[4]-1]=12;
                                                if(invisible[saveR[4]+1][saveC[4]]!=10&&invisible[saveR[4]+1][saveC[4]]!=11)invisible[saveR[4]+1][saveC[4]]=12;
                                                if(invisible[saveR[4]+1][saveC[4]+1]!=10&&invisible[saveR[4]+1][saveC[4]+1]!=11)invisible[saveR[4]+1][saveC[4]+1]=12;
                                            }
                                        case 5:
                                        saveR[counter]=r;
                                        saveC[counter]=c;
                                            if(counter==5){
                                                k=10;
                                                s=1;
                                                y=y+3;
                                                counter=0;
                                                //atribuicao dos valores x em volta de todas as particulas do barco 5
                                                if(invisible[saveR[1]-1][saveC[1]-1]!=10&&invisible[saveR[1]-1][saveC[1]-1]!=11)invisible[saveR[1]-1][saveC[1]-1]=12;
                                                if(invisible[saveR[1]-1][saveC[1]]!=10&&invisible[saveR[1]-1][saveC[1]]!=11)invisible[saveR[1]-1][saveC[1]]=12;
                                                if(invisible[saveR[1]-1][saveC[1]+1]!=10&&invisible[saveR[1]-1][saveC[1]+1]!=11)invisible[saveR[1]-1][saveC[1]+1]=12;
                                                if(invisible[saveR[1]][saveC[1]-1]!=10&&invisible[saveR[1]][saveC[1]-1]!=11)invisible[saveR[1]][saveC[1]-1]=12;
                                                if(invisible[saveR[1]][saveC[1]+1]!=10&&invisible[saveR[1]][saveC[1]+1]!=11)invisible[saveR[1]][saveC[1]+1]=12;
                                                if(invisible[saveR[1]+1][saveC[1]-1]!=10&&invisible[saveR[1]+1][saveC[1]-1]!=11)invisible[saveR[1]+1][saveC[1]-1]=12;
                                                if(invisible[saveR[1]+1][saveC[1]]!=10&&invisible[saveR[1]+1][saveC[1]]!=11)invisible[saveR[1]+1][saveC[1]]=12;
                                                if(invisible[saveR[1]+1][saveC[1]+1]!=10&&invisible[saveR[1]+1][saveC[1]+1]!=11)invisible[saveR[1]+1][saveC[1]+1]=12;

                                                if(invisible[saveR[2]-1][saveC[2]-1]!=10&&invisible[saveR[2]-1][saveC[2]-1]!=11)invisible[saveR[2]-1][saveC[2]-1]=12;
                                                if(invisible[saveR[2]-1][saveC[2]]!=10&&invisible[saveR[2]-1][saveC[2]]!=11)invisible[saveR[2]-1][saveC[2]]=12;
                                                if(invisible[saveR[2]-1][saveC[2]+1]!=10&&invisible[saveR[2]-1][saveC[2]+1]!=11)invisible[saveR[2]-1][saveC[2]+1]=12;
                                                if(invisible[saveR[2]][saveC[2]-1]!=10&&invisible[saveR[2]][saveC[2]-1]!=11)invisible[saveR[2]][saveC[2]-1]=12;
                                                if(invisible[saveR[2]][saveC[2]+1]!=10&&invisible[saveR[2]][saveC[2]+1]!=11)invisible[saveR[2]][saveC[2]+1]=12;
                                                if(invisible[saveR[2]+1][saveC[2]-1]!=10&&invisible[saveR[2]+1][saveC[2]-1]!=11)invisible[saveR[2]+1][saveC[2]-1]=12;
                                                if(invisible[saveR[2]+1][saveC[2]]!=10&&invisible[saveR[2]+1][saveC[2]]!=11)invisible[saveR[2]+1][saveC[2]]=12;
                                                if(invisible[saveR[2]+1][saveC[2]+1]!=10&&invisible[saveR[2]+1][saveC[2]+1]!=11)invisible[saveR[2]+1][saveC[2]+1]=12;

                                                if(invisible[saveR[3]-1][saveC[3]-1]!=10&&invisible[saveR[3]-1][saveC[3]-1]!=11)invisible[saveR[3]-1][saveC[3]-1]=12;
                                                if(invisible[saveR[3]-1][saveC[3]]!=10&&invisible[saveR[3]-1][saveC[3]]!=11)invisible[saveR[3]-1][saveC[3]]=12;
                                                if(invisible[saveR[3]-1][saveC[3]+1]!=10&&invisible[saveR[3]-1][saveC[3]+1]!=11)invisible[saveR[3]-1][saveC[3]+1]=12;
                                                if(invisible[saveR[3]][saveC[3]-1]!=10&&invisible[saveR[3]][saveC[3]-1]!=11)invisible[saveR[3]][saveC[3]-1]=12;
                                                if(invisible[saveR[3]][saveC[3]+1]!=10&&invisible[saveR[3]][saveC[3]+1]!=11)invisible[saveR[3]][saveC[3]+1]=12;
                                                if(invisible[saveR[3]+1][saveC[3]-1]!=10&&invisible[saveR[3]+1][saveC[3]-1]!=11)invisible[saveR[3]+1][saveC[3]-1]=12;
                                                if(invisible[saveR[3]+1][saveC[3]]!=10&&invisible[saveR[3]+1][saveC[3]]!=11)invisible[saveR[3]+1][saveC[3]]=12;
                                                if(invisible[saveR[3]+1][saveC[3]+1]!=10&&invisible[saveR[3]+1][saveC[3]+1]!=11)invisible[saveR[3]+1][saveC[3]+1]=12;

                                                if(invisible[saveR[4]-1][saveC[4]-1]!=10&&invisible[saveR[4]-1][saveC[4]-1]!=11)invisible[saveR[4]-1][saveC[4]-1]=12;
                                                if(invisible[saveR[4]-1][saveC[4]]!=10&&invisible[saveR[4]-1][saveC[4]]!=11)invisible[saveR[4]-1][saveC[4]]=12;
                                                if(invisible[saveR[4]-1][saveC[4]+1]!=10&&invisible[saveR[4]-1][saveC[4]+1]!=11)invisible[saveR[4]-1][saveC[4]+1]=12;
                                                if(invisible[saveR[4]][saveC[4]-1]!=10&&invisible[saveR[4]][saveC[4]-1]!=11)invisible[saveR[4]][saveC[4]-1]=12;
                                                if(invisible[saveR[4]][saveC[4]+1]!=10&&invisible[saveR[4]][saveC[4]+1]!=11)invisible[saveR[4]][saveC[4]+1]=12;
                                                if(invisible[saveR[4]+1][saveC[4]-1]!=10&&invisible[saveR[4]+1][saveC[4]-1]!=11)invisible[saveR[4]+1][saveC[4]-1]=12;
                                                if(invisible[saveR[4]+1][saveC[4]]!=10&&invisible[saveR[4]+1][saveC[4]]!=11)invisible[saveR[4]+1][saveC[4]]=12;
                                                if(invisible[saveR[4]+1][saveC[4]+1]!=10&&invisible[saveR[4]+1][saveC[4]+1]!=11)invisible[saveR[4]+1][saveC[4]+1]=12;

                                                if(invisible[saveR[5]-1][saveC[5]-1]!=10&&invisible[saveR[5]-1][saveC[5]-1]!=11)invisible[saveR[5]-1][saveC[5]-1]=12;
                                                if(invisible[saveR[5]-1][saveC[5]]!=10&&invisible[saveR[5]-1][saveC[5]]!=11)invisible[saveR[5]-1][saveC[5]]=12;
                                                if(invisible[saveR[5]-1][saveC[5]+1]!=10&&invisible[saveR[5]-1][saveC[5]+1]!=11)invisible[saveR[5]-1][saveC[5]+1]=12;
                                                if(invisible[saveR[5]][saveC[5]-1]!=10&&invisible[saveR[5]][saveC[5]-1]!=11)invisible[saveR[5]][saveC[5]-1]=12;
                                                if(invisible[saveR[5]][saveC[5]+1]!=10&&invisible[saveR[5]][saveC[5]+1]!=11)invisible[saveR[5]][saveC[5]+1]=12;
                                                if(invisible[saveR[5]+1][saveC[5]-1]!=10&&invisible[saveR[5]+1][saveC[5]-1]!=11)invisible[saveR[5]+1][saveC[5]-1]=12;
                                                if(invisible[saveR[5]+1][saveC[5]]!=10&&invisible[saveR[5]+1][saveC[5]]!=11)invisible[saveR[5]+1][saveC[5]]=12;
                                                if(invisible[saveR[5]+1][saveC[5]+1]!=10&&invisible[saveR[5]+1][saveC[5]+1]!=11)invisible[saveR[5]+1][saveC[5]+1]=12;
                                            }
                                        case 6:
                                        saveR[counter]=r;
                                        saveC[counter]=c;
                                            if(counter==6){
                                                k=10;
                                                s=1;
                                                y=y+3;
                                                counter=0;
                                                //atribuicao dos valores x em volta de todas as particulas do barco 6
                                                if(invisible[saveR[1]-1][saveC[1]-1]!=10&&invisible[saveR[1]-1][saveC[1]-1]!=11)invisible[saveR[1]-1][saveC[1]-1]=12;
                                                if(invisible[saveR[1]-1][saveC[1]]!=10&&invisible[saveR[1]-1][saveC[1]]!=11)invisible[saveR[1]-1][saveC[1]]=12;
                                                if(invisible[saveR[1]-1][saveC[1]+1]!=10&&invisible[saveR[1]-1][saveC[1]+1]!=11)invisible[saveR[1]-1][saveC[1]+1]=12;
                                                if(invisible[saveR[1]][saveC[1]-1]!=10&&invisible[saveR[1]][saveC[1]-1]!=11)invisible[saveR[1]][saveC[1]-1]=12;
                                                if(invisible[saveR[1]][saveC[1]+1]!=10&&invisible[saveR[1]][saveC[1]+1]!=11)invisible[saveR[1]][saveC[1]+1]=12;
                                                if(invisible[saveR[1]+1][saveC[1]-1]!=10&&invisible[saveR[1]+1][saveC[1]-1]!=11)invisible[saveR[1]+1][saveC[1]-1]=12;
                                                if(invisible[saveR[1]+1][saveC[1]]!=10&&invisible[saveR[1]+1][saveC[1]]!=11)invisible[saveR[1]+1][saveC[1]]=12;
                                                if(invisible[saveR[1]+1][saveC[1]+1]!=10&&invisible[saveR[1]+1][saveC[1]+1]!=11)invisible[saveR[1]+1][saveC[1]+1]=12;

                                                if(invisible[saveR[2]-1][saveC[2]-1]!=10&&invisible[saveR[2]-1][saveC[2]-1]!=11)invisible[saveR[2]-1][saveC[2]-1]=12;
                                                if(invisible[saveR[2]-1][saveC[2]]!=10&&invisible[saveR[2]-1][saveC[2]]!=11)invisible[saveR[2]-1][saveC[2]]=12;
                                                if(invisible[saveR[2]-1][saveC[2]+1]!=10&&invisible[saveR[2]-1][saveC[2]+1]!=11)invisible[saveR[2]-1][saveC[2]+1]=12;
                                                if(invisible[saveR[2]][saveC[2]-1]!=10&&invisible[saveR[2]][saveC[2]-1]!=11)invisible[saveR[2]][saveC[2]-1]=12;
                                                if(invisible[saveR[2]][saveC[2]+1]!=10&&invisible[saveR[2]][saveC[2]+1]!=11)invisible[saveR[2]][saveC[2]+1]=12;
                                                if(invisible[saveR[2]+1][saveC[2]-1]!=10&&invisible[saveR[2]+1][saveC[2]-1]!=11)invisible[saveR[2]+1][saveC[2]-1]=12;
                                                if(invisible[saveR[2]+1][saveC[2]]!=10&&invisible[saveR[2]+1][saveC[2]]!=11)invisible[saveR[2]+1][saveC[2]]=12;
                                                if(invisible[saveR[2]+1][saveC[2]+1]!=10&&invisible[saveR[2]+1][saveC[2]+1]!=11)invisible[saveR[2]+1][saveC[2]+1]=12;

                                                if(invisible[saveR[3]-1][saveC[3]-1]!=10&&invisible[saveR[3]-1][saveC[3]-1]!=11)invisible[saveR[3]-1][saveC[3]-1]=12;
                                                if(invisible[saveR[3]-1][saveC[3]]!=10&&invisible[saveR[3]-1][saveC[3]]!=11)invisible[saveR[3]-1][saveC[3]]=12;
                                                if(invisible[saveR[3]-1][saveC[3]+1]!=10&&invisible[saveR[3]-1][saveC[3]+1]!=11)invisible[saveR[3]-1][saveC[3]+1]=12;
                                                if(invisible[saveR[3]][saveC[3]-1]!=10&&invisible[saveR[3]][saveC[3]-1]!=11)invisible[saveR[3]][saveC[3]-1]=12;
                                                if(invisible[saveR[3]][saveC[3]+1]!=10&&invisible[saveR[3]][saveC[3]+1]!=11)invisible[saveR[3]][saveC[3]+1]=12;
                                                if(invisible[saveR[3]+1][saveC[3]-1]!=10&&invisible[saveR[3]+1][saveC[3]-1]!=11)invisible[saveR[3]+1][saveC[3]-1]=12;
                                                if(invisible[saveR[3]+1][saveC[3]]!=10&&invisible[saveR[3]+1][saveC[3]]!=11)invisible[saveR[3]+1][saveC[3]]=12;
                                                if(invisible[saveR[3]+1][saveC[3]+1]!=10&&invisible[saveR[3]+1][saveC[3]+1]!=11)invisible[saveR[3]+1][saveC[3]+1]=12;

                                                if(invisible[saveR[4]-1][saveC[4]-1]!=10&&invisible[saveR[4]-1][saveC[4]-1]!=11)invisible[saveR[4]-1][saveC[4]-1]=12;
                                                if(invisible[saveR[4]-1][saveC[4]]!=10&&invisible[saveR[4]-1][saveC[4]]!=11)invisible[saveR[4]-1][saveC[4]]=12;
                                                if(invisible[saveR[4]-1][saveC[4]+1]!=10&&invisible[saveR[4]-1][saveC[4]+1]!=11)invisible[saveR[4]-1][saveC[4]+1]=12;
                                                if(invisible[saveR[4]][saveC[4]-1]!=10&&invisible[saveR[4]][saveC[4]-1]!=11)invisible[saveR[4]][saveC[4]-1]=12;
                                                if(invisible[saveR[4]][saveC[4]+1]!=10&&invisible[saveR[4]][saveC[4]+1]!=11)invisible[saveR[4]][saveC[4]+1]=12;
                                                if(invisible[saveR[4]+1][saveC[4]-1]!=10&&invisible[saveR[4]+1][saveC[4]-1]!=11)invisible[saveR[4]+1][saveC[4]-1]=12;
                                                if(invisible[saveR[4]+1][saveC[4]]!=10&&invisible[saveR[4]+1][saveC[4]]!=11)invisible[saveR[4]+1][saveC[4]]=12;
                                                if(invisible[saveR[4]+1][saveC[4]+1]!=10&&invisible[saveR[4]+1][saveC[4]+1]!=11)invisible[saveR[4]+1][saveC[4]+1]=12;

                                                if(invisible[saveR[5]-1][saveC[5]-1]!=10&&invisible[saveR[5]-1][saveC[5]-1]!=11)invisible[saveR[5]-1][saveC[5]-1]=12;
                                                if(invisible[saveR[5]-1][saveC[5]]!=10&&invisible[saveR[5]-1][saveC[5]]!=11)invisible[saveR[5]-1][saveC[5]]=12;
                                                if(invisible[saveR[5]-1][saveC[5]+1]!=10&&invisible[saveR[5]-1][saveC[5]+1]!=11)invisible[saveR[5]-1][saveC[5]+1]=12;
                                                if(invisible[saveR[5]][saveC[5]-1]!=10&&invisible[saveR[5]][saveC[5]-1]!=11)invisible[saveR[5]][saveC[5]-1]=12;
                                                if(invisible[saveR[5]][saveC[5]+1]!=10&&invisible[saveR[5]][saveC[5]+1]!=11)invisible[saveR[5]][saveC[5]+1]=12;
                                                if(invisible[saveR[5]+1][saveC[5]-1]!=10&&invisible[saveR[5]+1][saveC[5]-1]!=11)invisible[saveR[5]+1][saveC[5]-1]=12;
                                                if(invisible[saveR[5]+1][saveC[5]]!=10&&invisible[saveR[5]+1][saveC[5]]!=11)invisible[saveR[5]+1][saveC[5]]=12;
                                                if(invisible[saveR[5]+1][saveC[5]+1]!=10&&invisible[saveR[5]+1][saveC[5]+1]!=11)invisible[saveR[5]+1][saveC[5]+1]=12;

                                                if(invisible[saveR[6]-1][saveC[6]-1]!=10&&invisible[saveR[6]-1][saveC[6]-1]!=11)invisible[saveR[6]-1][saveC[6]-1]=12;
                                                if(invisible[saveR[6]-1][saveC[6]]!=10&&invisible[saveR[6]-1][saveC[6]]!=11)invisible[saveR[6]-1][saveC[6]]=12;
                                                if(invisible[saveR[6]-1][saveC[6]+1]!=10&&invisible[saveR[6]-1][saveC[6]+1]!=11)invisible[saveR[6]-1][saveC[6]+1]=12;
                                                if(invisible[saveR[6]][saveC[6]-1]!=10&&invisible[saveR[6]][saveC[6]-1]!=11)invisible[saveR[6]][saveC[6]-1]=12;
                                                if(invisible[saveR[6]][saveC[6]+1]!=10&&invisible[saveR[6]][saveC[6]+1]!=11)invisible[saveR[6]][saveC[6]+1]=12;
                                                if(invisible[saveR[6]+1][saveC[6]-1]!=10&&invisible[saveR[6]+1][saveC[6]-1]!=11)invisible[saveR[6]+1][saveC[6]-1]=12;
                                                if(invisible[saveR[6]+1][saveC[6]]!=10&&invisible[saveR[6]+1][saveC[6]]!=11)invisible[saveR[6]+1][saveC[6]]=12;
                                                if(invisible[saveR[6]+1][saveC[6]+1]!=10&&invisible[saveR[6]+1][saveC[6]+1]!=11)invisible[saveR[6]+1][saveC[6]+1]=12;
                                            }
                                        case 7:
                                        saveR[counter]=r;
                                        saveC[counter]=c;
                                            if(counter==7){
                                                k=10;
                                                s=1;
                                                y=y+3;
                                                counter=0;
                                                //atribuicao dos valores x em volta de todas as particulas do barco 7
                                                if(invisible[saveR[1]-1][saveC[1]-1]!=10&&invisible[saveR[1]-1][saveC[1]-1]!=11)invisible[saveR[1]-1][saveC[1]-1]=12;
                                                if(invisible[saveR[1]-1][saveC[1]]!=10&&invisible[saveR[1]-1][saveC[1]]!=11)invisible[saveR[1]-1][saveC[1]]=12;
                                                if(invisible[saveR[1]-1][saveC[1]+1]!=10&&invisible[saveR[1]-1][saveC[1]+1]!=11)invisible[saveR[1]-1][saveC[1]+1]=12;
                                                if(invisible[saveR[1]][saveC[1]-1]!=10&&invisible[saveR[1]][saveC[1]-1]!=11)invisible[saveR[1]][saveC[1]-1]=12;
                                                if(invisible[saveR[1]][saveC[1]+1]!=10&&invisible[saveR[1]][saveC[1]+1]!=11)invisible[saveR[1]][saveC[1]+1]=12;
                                                if(invisible[saveR[1]+1][saveC[1]-1]!=10&&invisible[saveR[1]+1][saveC[1]-1]!=11)invisible[saveR[1]+1][saveC[1]-1]=12;
                                                if(invisible[saveR[1]+1][saveC[1]]!=10&&invisible[saveR[1]+1][saveC[1]]!=11)invisible[saveR[1]+1][saveC[1]]=12;
                                                if(invisible[saveR[1]+1][saveC[1]+1]!=10&&invisible[saveR[1]+1][saveC[1]+1]!=11)invisible[saveR[1]+1][saveC[1]+1]=12;

                                                if(invisible[saveR[2]-1][saveC[2]-1]!=10&&invisible[saveR[2]-1][saveC[2]-1]!=11)invisible[saveR[2]-1][saveC[2]-1]=12;
                                                if(invisible[saveR[2]-1][saveC[2]]!=10&&invisible[saveR[2]-1][saveC[2]]!=11)invisible[saveR[2]-1][saveC[2]]=12;
                                                if(invisible[saveR[2]-1][saveC[2]+1]!=10&&invisible[saveR[2]-1][saveC[2]+1]!=11)invisible[saveR[2]-1][saveC[2]+1]=12;
                                                if(invisible[saveR[2]][saveC[2]-1]!=10&&invisible[saveR[2]][saveC[2]-1]!=11)invisible[saveR[2]][saveC[2]-1]=12;
                                                if(invisible[saveR[2]][saveC[2]+1]!=10&&invisible[saveR[2]][saveC[2]+1]!=11)invisible[saveR[2]][saveC[2]+1]=12;
                                                if(invisible[saveR[2]+1][saveC[2]-1]!=10&&invisible[saveR[2]+1][saveC[2]-1]!=11)invisible[saveR[2]+1][saveC[2]-1]=12;
                                                if(invisible[saveR[2]+1][saveC[2]]!=10&&invisible[saveR[2]+1][saveC[2]]!=11)invisible[saveR[2]+1][saveC[2]]=12;
                                                if(invisible[saveR[2]+1][saveC[2]+1]!=10&&invisible[saveR[2]+1][saveC[2]+1]!=11)invisible[saveR[2]+1][saveC[2]+1]=12;

                                                if(invisible[saveR[3]-1][saveC[3]-1]!=10&&invisible[saveR[3]-1][saveC[3]-1]!=11)invisible[saveR[3]-1][saveC[3]-1]=12;
                                                if(invisible[saveR[3]-1][saveC[3]]!=10&&invisible[saveR[3]-1][saveC[3]]!=11)invisible[saveR[3]-1][saveC[3]]=12;
                                                if(invisible[saveR[3]-1][saveC[3]+1]!=10&&invisible[saveR[3]-1][saveC[3]+1]!=11)invisible[saveR[3]-1][saveC[3]+1]=12;
                                                if(invisible[saveR[3]][saveC[3]-1]!=10&&invisible[saveR[3]][saveC[3]-1]!=11)invisible[saveR[3]][saveC[3]-1]=12;
                                                if(invisible[saveR[3]][saveC[3]+1]!=10&&invisible[saveR[3]][saveC[3]+1]!=11)invisible[saveR[3]][saveC[3]+1]=12;
                                                if(invisible[saveR[3]+1][saveC[3]-1]!=10&&invisible[saveR[3]+1][saveC[3]-1]!=11)invisible[saveR[3]+1][saveC[3]-1]=12;
                                                if(invisible[saveR[3]+1][saveC[3]]!=10&&invisible[saveR[3]+1][saveC[3]]!=11)invisible[saveR[3]+1][saveC[3]]=12;
                                                if(invisible[saveR[3]+1][saveC[3]+1]!=10&&invisible[saveR[3]+1][saveC[3]+1]!=11)invisible[saveR[3]+1][saveC[3]+1]=12;

                                                if(invisible[saveR[4]-1][saveC[4]-1]!=10&&invisible[saveR[4]-1][saveC[4]-1]!=11)invisible[saveR[4]-1][saveC[4]-1]=12;
                                                if(invisible[saveR[4]-1][saveC[4]]!=10&&invisible[saveR[4]-1][saveC[4]]!=11)invisible[saveR[4]-1][saveC[4]]=12;
                                                if(invisible[saveR[4]-1][saveC[4]+1]!=10&&invisible[saveR[4]-1][saveC[4]+1]!=11)invisible[saveR[4]-1][saveC[4]+1]=12;
                                                if(invisible[saveR[4]][saveC[4]-1]!=10&&invisible[saveR[4]][saveC[4]-1]!=11)invisible[saveR[4]][saveC[4]-1]=12;
                                                if(invisible[saveR[4]][saveC[4]+1]!=10&&invisible[saveR[4]][saveC[4]+1]!=11)invisible[saveR[4]][saveC[4]+1]=12;
                                                if(invisible[saveR[4]+1][saveC[4]-1]!=10&&invisible[saveR[4]+1][saveC[4]-1]!=11)invisible[saveR[4]+1][saveC[4]-1]=12;
                                                if(invisible[saveR[4]+1][saveC[4]]!=10&&invisible[saveR[4]+1][saveC[4]]!=11)invisible[saveR[4]+1][saveC[4]]=12;
                                                if(invisible[saveR[4]+1][saveC[4]+1]!=10&&invisible[saveR[4]+1][saveC[4]+1]!=11)invisible[saveR[4]+1][saveC[4]+1]=12;

                                                if(invisible[saveR[5]-1][saveC[5]-1]!=10&&invisible[saveR[5]-1][saveC[5]-1]!=11)invisible[saveR[5]-1][saveC[5]-1]=12;
                                                if(invisible[saveR[5]-1][saveC[5]]!=10&&invisible[saveR[5]-1][saveC[5]]!=11)invisible[saveR[5]-1][saveC[5]]=12;
                                                if(invisible[saveR[5]-1][saveC[5]+1]!=10&&invisible[saveR[5]-1][saveC[5]+1]!=11)invisible[saveR[5]-1][saveC[5]+1]=12;
                                                if(invisible[saveR[5]][saveC[5]-1]!=10&&invisible[saveR[5]][saveC[5]-1]!=11)invisible[saveR[5]][saveC[5]-1]=12;
                                                if(invisible[saveR[5]][saveC[5]+1]!=10&&invisible[saveR[5]][saveC[5]+1]!=11)invisible[saveR[5]][saveC[5]+1]=12;
                                                if(invisible[saveR[5]+1][saveC[5]-1]!=10&&invisible[saveR[5]+1][saveC[5]-1]!=11)invisible[saveR[5]+1][saveC[5]-1]=12;
                                                if(invisible[saveR[5]+1][saveC[5]]!=10&&invisible[saveR[5]+1][saveC[5]]!=11)invisible[saveR[5]+1][saveC[5]]=12;
                                                if(invisible[saveR[5]+1][saveC[5]+1]!=10&&invisible[saveR[5]+1][saveC[5]+1]!=11)invisible[saveR[5]+1][saveC[5]+1]=12;

                                                if(invisible[saveR[6]-1][saveC[6]-1]!=10&&invisible[saveR[6]-1][saveC[6]-1]!=11)invisible[saveR[6]-1][saveC[6]-1]=12;
                                                if(invisible[saveR[6]-1][saveC[6]]!=10&&invisible[saveR[6]-1][saveC[6]]!=11)invisible[saveR[6]-1][saveC[6]]=12;
                                                if(invisible[saveR[6]-1][saveC[6]+1]!=10&&invisible[saveR[6]-1][saveC[6]+1]!=11)invisible[saveR[6]-1][saveC[6]+1]=12;
                                                if(invisible[saveR[6]][saveC[6]-1]!=10&&invisible[saveR[6]][saveC[6]-1]!=11)invisible[saveR[6]][saveC[6]-1]=12;
                                                if(invisible[saveR[6]][saveC[6]+1]!=10&&invisible[saveR[6]][saveC[6]+1]!=11)invisible[saveR[6]][saveC[6]+1]=12;
                                                if(invisible[saveR[6]+1][saveC[6]-1]!=10&&invisible[saveR[6]+1][saveC[6]-1]!=11)invisible[saveR[6]+1][saveC[6]-1]=12;
                                                if(invisible[saveR[6]+1][saveC[6]]!=10&&invisible[saveR[6]+1][saveC[6]]!=11)invisible[saveR[6]+1][saveC[6]]=12;
                                                if(invisible[saveR[6]+1][saveC[6]+1]!=10&&invisible[saveR[6]+1][saveC[6]+1]!=11)invisible[saveR[6]+1][saveC[6]+1]=12;

                                                if(invisible[saveR[7]-1][saveC[7]-1]!=10&&invisible[saveR[7]-1][saveC[7]-1]!=11)invisible[saveR[7]-1][saveC[7]-1]=12;
                                                if(invisible[saveR[7]-1][saveC[7]]!=10&&invisible[saveR[7]-1][saveC[7]]!=11)invisible[saveR[7]-1][saveC[7]]=12;
                                                if(invisible[saveR[7]-1][saveC[7]+1]!=10&&invisible[saveR[7]-1][saveC[7]+1]!=11)invisible[saveR[7]-1][saveC[7]+1]=12;
                                                if(invisible[saveR[7]][saveC[7]-1]!=10&&invisible[saveR[7]][saveC[7]-1]!=11)invisible[saveR[7]][saveC[7]-1]=12;
                                                if(invisible[saveR[7]][saveC[7]+1]!=10&&invisible[saveR[7]][saveC[7]+1]!=11)invisible[saveR[7]][saveC[7]+1]=12;
                                                if(invisible[saveR[7]+1][saveC[7]-1]!=10&&invisible[saveR[7]+1][saveC[7]-1]!=11)invisible[saveR[7]+1][saveC[7]-1]=12;
                                                if(invisible[saveR[7]+1][saveC[7]]!=10&&invisible[saveR[7]+1][saveC[7]]!=11)invisible[saveR[7]+1][saveC[7]]=12;
                                                if(invisible[saveR[7]+1][saveC[7]+1]!=10&&invisible[saveR[7]+1][saveC[7]+1]!=11)invisible[saveR[7]+1][saveC[7]+1]=12;
                                            }
                                        case 8:
                                        saveR[counter]=r;
                                        saveC[counter]=c;
                                            if(counter==8){
                                                k=10;
                                                s=1;
                                                y=y+3;
                                                counter=0;
                                                //atribuicao dos valores x em volta de todas as particulas do barco 8
                                                if(invisible[saveR[1]-1][saveC[1]-1]!=10&&invisible[saveR[1]-1][saveC[1]-1]!=11)invisible[saveR[1]-1][saveC[1]-1]=12;
                                                if(invisible[saveR[1]-1][saveC[1]]!=10&&invisible[saveR[1]-1][saveC[1]]!=11)invisible[saveR[1]-1][saveC[1]]=12;
                                                if(invisible[saveR[1]-1][saveC[1]+1]!=10&&invisible[saveR[1]-1][saveC[1]+1]!=11)invisible[saveR[1]-1][saveC[1]+1]=12;
                                                if(invisible[saveR[1]][saveC[1]-1]!=10&&invisible[saveR[1]][saveC[1]-1]!=11)invisible[saveR[1]][saveC[1]-1]=12;
                                                if(invisible[saveR[1]][saveC[1]+1]!=10&&invisible[saveR[1]][saveC[1]+1]!=11)invisible[saveR[1]][saveC[1]+1]=12;
                                                if(invisible[saveR[1]+1][saveC[1]-1]!=10&&invisible[saveR[1]+1][saveC[1]-1]!=11)invisible[saveR[1]+1][saveC[1]-1]=12;
                                                if(invisible[saveR[1]+1][saveC[1]]!=10&&invisible[saveR[1]+1][saveC[1]]!=11)invisible[saveR[1]+1][saveC[1]]=12;
                                                if(invisible[saveR[1]+1][saveC[1]+1]!=10&&invisible[saveR[1]+1][saveC[1]+1]!=11)invisible[saveR[1]+1][saveC[1]+1]=12;

                                                if(invisible[saveR[2]-1][saveC[2]-1]!=10&&invisible[saveR[2]-1][saveC[2]-1]!=11)invisible[saveR[2]-1][saveC[2]-1]=12;
                                                if(invisible[saveR[2]-1][saveC[2]]!=10&&invisible[saveR[2]-1][saveC[2]]!=11)invisible[saveR[2]-1][saveC[2]]=12;
                                                if(invisible[saveR[2]-1][saveC[2]+1]!=10&&invisible[saveR[2]-1][saveC[2]+1]!=11)invisible[saveR[2]-1][saveC[2]+1]=12;
                                                if(invisible[saveR[2]][saveC[2]-1]!=10&&invisible[saveR[2]][saveC[2]-1]!=11)invisible[saveR[2]][saveC[2]-1]=12;
                                                if(invisible[saveR[2]][saveC[2]+1]!=10&&invisible[saveR[2]][saveC[2]+1]!=11)invisible[saveR[2]][saveC[2]+1]=12;
                                                if(invisible[saveR[2]+1][saveC[2]-1]!=10&&invisible[saveR[2]+1][saveC[2]-1]!=11)invisible[saveR[2]+1][saveC[2]-1]=12;
                                                if(invisible[saveR[2]+1][saveC[2]]!=10&&invisible[saveR[2]+1][saveC[2]]!=11)invisible[saveR[2]+1][saveC[2]]=12;
                                                if(invisible[saveR[2]+1][saveC[2]+1]!=10&&invisible[saveR[2]+1][saveC[2]+1]!=11)invisible[saveR[2]+1][saveC[2]+1]=12;

                                                if(invisible[saveR[3]-1][saveC[3]-1]!=10&&invisible[saveR[3]-1][saveC[3]-1]!=11)invisible[saveR[3]-1][saveC[3]-1]=12;
                                                if(invisible[saveR[3]-1][saveC[3]]!=10&&invisible[saveR[3]-1][saveC[3]]!=11)invisible[saveR[3]-1][saveC[3]]=12;
                                                if(invisible[saveR[3]-1][saveC[3]+1]!=10&&invisible[saveR[3]-1][saveC[3]+1]!=11)invisible[saveR[3]-1][saveC[3]+1]=12;
                                                if(invisible[saveR[3]][saveC[3]-1]!=10&&invisible[saveR[3]][saveC[3]-1]!=11)invisible[saveR[3]][saveC[3]-1]=12;
                                                if(invisible[saveR[3]][saveC[3]+1]!=10&&invisible[saveR[3]][saveC[3]+1]!=11)invisible[saveR[3]][saveC[3]+1]=12;
                                                if(invisible[saveR[3]+1][saveC[3]-1]!=10&&invisible[saveR[3]+1][saveC[3]-1]!=11)invisible[saveR[3]+1][saveC[3]-1]=12;
                                                if(invisible[saveR[3]+1][saveC[3]]!=10&&invisible[saveR[3]+1][saveC[3]]!=11)invisible[saveR[3]+1][saveC[3]]=12;
                                                if(invisible[saveR[3]+1][saveC[3]+1]!=10&&invisible[saveR[3]+1][saveC[3]+1]!=11)invisible[saveR[3]+1][saveC[3]+1]=12;

                                                if(invisible[saveR[4]-1][saveC[4]-1]!=10&&invisible[saveR[4]-1][saveC[4]-1]!=11)invisible[saveR[4]-1][saveC[4]-1]=12;
                                                if(invisible[saveR[4]-1][saveC[4]]!=10&&invisible[saveR[4]-1][saveC[4]]!=11)invisible[saveR[4]-1][saveC[4]]=12;
                                                if(invisible[saveR[4]-1][saveC[4]+1]!=10&&invisible[saveR[4]-1][saveC[4]+1]!=11)invisible[saveR[4]-1][saveC[4]+1]=12;
                                                if(invisible[saveR[4]][saveC[4]-1]!=10&&invisible[saveR[4]][saveC[4]-1]!=11)invisible[saveR[4]][saveC[4]-1]=12;
                                                if(invisible[saveR[4]][saveC[4]+1]!=10&&invisible[saveR[4]][saveC[4]+1]!=11)invisible[saveR[4]][saveC[4]+1]=12;
                                                if(invisible[saveR[4]+1][saveC[4]-1]!=10&&invisible[saveR[4]+1][saveC[4]-1]!=11)invisible[saveR[4]+1][saveC[4]-1]=12;
                                                if(invisible[saveR[4]+1][saveC[4]]!=10&&invisible[saveR[4]+1][saveC[4]]!=11)invisible[saveR[4]+1][saveC[4]]=12;
                                                if(invisible[saveR[4]+1][saveC[4]+1]!=10&&invisible[saveR[4]+1][saveC[4]+1]!=11)invisible[saveR[4]+1][saveC[4]+1]=12;

                                                if(invisible[saveR[5]-1][saveC[5]-1]!=10&&invisible[saveR[5]-1][saveC[5]-1]!=11)invisible[saveR[5]-1][saveC[5]-1]=12;
                                                if(invisible[saveR[5]-1][saveC[5]]!=10&&invisible[saveR[5]-1][saveC[5]]!=11)invisible[saveR[5]-1][saveC[5]]=12;
                                                if(invisible[saveR[5]-1][saveC[5]+1]!=10&&invisible[saveR[5]-1][saveC[5]+1]!=11)invisible[saveR[5]-1][saveC[5]+1]=12;
                                                if(invisible[saveR[5]][saveC[5]-1]!=10&&invisible[saveR[5]][saveC[5]-1]!=11)invisible[saveR[5]][saveC[5]-1]=12;
                                                if(invisible[saveR[5]][saveC[5]+1]!=10&&invisible[saveR[5]][saveC[5]+1]!=11)invisible[saveR[5]][saveC[5]+1]=12;
                                                if(invisible[saveR[5]+1][saveC[5]-1]!=10&&invisible[saveR[5]+1][saveC[5]-1]!=11)invisible[saveR[5]+1][saveC[5]-1]=12;
                                                if(invisible[saveR[5]+1][saveC[5]]!=10&&invisible[saveR[5]+1][saveC[5]]!=11)invisible[saveR[5]+1][saveC[5]]=12;
                                                if(invisible[saveR[5]+1][saveC[5]+1]!=10&&invisible[saveR[5]+1][saveC[5]+1]!=11)invisible[saveR[5]+1][saveC[5]+1]=12;

                                                if(invisible[saveR[6]-1][saveC[6]-1]!=10&&invisible[saveR[6]-1][saveC[6]-1]!=11)invisible[saveR[6]-1][saveC[6]-1]=12;
                                                if(invisible[saveR[6]-1][saveC[6]]!=10&&invisible[saveR[6]-1][saveC[6]]!=11)invisible[saveR[6]-1][saveC[6]]=12;
                                                if(invisible[saveR[6]-1][saveC[6]+1]!=10&&invisible[saveR[6]-1][saveC[6]+1]!=11)invisible[saveR[6]-1][saveC[6]+1]=12;
                                                if(invisible[saveR[6]][saveC[6]-1]!=10&&invisible[saveR[6]][saveC[6]-1]!=11)invisible[saveR[6]][saveC[6]-1]=12;
                                                if(invisible[saveR[6]][saveC[6]+1]!=10&&invisible[saveR[6]][saveC[6]+1]!=11)invisible[saveR[6]][saveC[6]+1]=12;
                                                if(invisible[saveR[6]+1][saveC[6]-1]!=10&&invisible[saveR[6]+1][saveC[6]-1]!=11)invisible[saveR[6]+1][saveC[6]-1]=12;
                                                if(invisible[saveR[6]+1][saveC[6]]!=10&&invisible[saveR[6]+1][saveC[6]]!=11)invisible[saveR[6]+1][saveC[6]]=12;
                                                if(invisible[saveR[6]+1][saveC[6]+1]!=10&&invisible[saveR[6]+1][saveC[6]+1]!=11)invisible[saveR[6]+1][saveC[6]+1]=12;

                                                if(invisible[saveR[7]-1][saveC[7]-1]!=10&&invisible[saveR[7]-1][saveC[7]-1]!=11)invisible[saveR[7]-1][saveC[7]-1]=12;
                                                if(invisible[saveR[7]-1][saveC[7]]!=10&&invisible[saveR[7]-1][saveC[7]]!=11)invisible[saveR[7]-1][saveC[7]]=12;
                                                if(invisible[saveR[7]-1][saveC[7]+1]!=10&&invisible[saveR[7]-1][saveC[7]+1]!=11)invisible[saveR[7]-1][saveC[7]+1]=12;
                                                if(invisible[saveR[7]][saveC[7]-1]!=10&&invisible[saveR[7]][saveC[7]-1]!=11)invisible[saveR[7]][saveC[7]-1]=12;
                                                if(invisible[saveR[7]][saveC[7]+1]!=10&&invisible[saveR[7]][saveC[7]+1]!=11)invisible[saveR[7]][saveC[7]+1]=12;
                                                if(invisible[saveR[7]+1][saveC[7]-1]!=10&&invisible[saveR[7]+1][saveC[7]-1]!=11)invisible[saveR[7]+1][saveC[7]-1]=12;
                                                if(invisible[saveR[7]+1][saveC[7]]!=10&&invisible[saveR[7]+1][saveC[7]]!=11)invisible[saveR[7]+1][saveC[7]]=12;
                                                if(invisible[saveR[7]+1][saveC[7]+1]!=10&&invisible[saveR[7]+1][saveC[7]+1]!=11)invisible[saveR[7]+1][saveC[7]+1]=12;

                                                if(invisible[saveR[8]-1][saveC[8]-1]!=10&&invisible[saveR[8]-1][saveC[8]-1]!=11)invisible[saveR[8]-1][saveC[8]-1]=12;
                                                if(invisible[saveR[8]-1][saveC[8]]!=10&&invisible[saveR[8]-1][saveC[8]]!=11)invisible[saveR[8]-1][saveC[8]]=12;
                                                if(invisible[saveR[8]-1][saveC[8]+1]!=10&&invisible[saveR[8]-1][saveC[8]+1]!=11)invisible[saveR[8]-1][saveC[8]+1]=12;
                                                if(invisible[saveR[8]][saveC[8]-1]!=10&&invisible[saveR[8]][saveC[8]-1]!=11)invisible[saveR[8]][saveC[8]-1]=12;
                                                if(invisible[saveR[8]][saveC[8]+1]!=10&&invisible[saveR[8]][saveC[8]+1]!=11)invisible[saveR[8]][saveC[8]+1]=12;
                                                if(invisible[saveR[8]+1][saveC[8]-1]!=10&&invisible[saveR[8]+1][saveC[8]-1]!=11)invisible[saveR[8]+1][saveC[8]-1]=12;
                                                if(invisible[saveR[8]+1][saveC[8]]!=10&&invisible[saveR[8]+1][saveC[8]]!=11)invisible[saveR[8]+1][saveC[8]]=12;
                                                if(invisible[saveR[8]+1][saveC[8]+1]!=10&&invisible[saveR[8]+1][saveC[8]+1]!=11)invisible[saveR[8]+1][saveC[8]+1]=12;
                                            }
                                    }
                                }
                            else if(board[r-1][c-1]==0){
                                invisible[r][c]=11;
                                }
                            }
                        }
                    }
                }
            }
            y=0;
            x=x+3;
    }
    end_t = time(NULL);
    total_t = end_t - start_t; //timer
    printf("Fim de Jogo: %d tentativas em %lu segundos.\n", count, total_t);

    //print do board final caso falhe todos os tiros
                    for( i = 0; i < row; i++){
                                printf("%02d ", row -i);
                                for(j = 0; j < column; j++){
                                if(invisible[i+1][j+1]==9){
                                    if(board[r-1][c-1]!=0){
                                    printf("%d ", board[i][j]);
                                }
                                else if(board[r-1][c-1]==0){
                                        invisible[r][c]=11;
                                        printf("- ");
                                        }
                                }
                                else if(invisible[i+1][j+1]==10) printf("%d ", board[i][j]);
                                else printf("- ");
                                }
                                printf("\n");
                                }
                                putchar(' ');
                                putchar(' ');
                                putchar(' ');

                                for(i = 1; i <= column; i++){
                                    printf("%c ", 64 + i);
                                }
                        return 0;
}

//funcao para a restricao 1
int rest1(int i, int j, int rn){
//verifica para todos os espaços à volta de cada elemento da matriz 3x3, que não esteja dentro da própria matriz, se tem um barco ou está vazio

    if((pieces[rn][0][0]!=0&&(board[i-1][j-1]!=0||board[i-1][j]!=0||board[i-1][j+1]!=0||board[i][j-1]!=0||board[i+1][j-1]!=0))||
    (pieces[rn][0][1]!=0&&(board[i-1][j]!=0||board[i-1][j+1]!=0||board[i-1][j+2]!=0))||
    (pieces[rn][0][2]!=0&&(board[i-1][j+1]!=0||board[i-1][j+2]!=0||board[i-1][j+3]!=0||board[i][j+3]!=0||board[i+1][j+3]!=0))||
    (pieces[rn][1][0]!=0&&(board[i][j-1]!=0||board[i+1][j-1]!=0||board[i+2][j-1]!=0))||
    (pieces[rn][1][2]!=0&&(board[i][j+3]!=0||board[i+1][j+3]!=0||board[i+2][j+3]!=0))||
    (pieces[rn][2][0]!=0&&(board[i+1][j-1]!=0||board[i+2][j-1]!=0||board[i+3][j-1]!=0||board[i+3][j]!=0||board[i+3][j+1]!=0))||
    (pieces[rn][2][1]!=0&&(board[i+3][j]!=0||board[i+3][j+1]!=0||board[i+3][j+2]!=0))||
    (pieces[rn][2][2]!=0&&(board[i+1][j+3]!=0||board[i+2][j+3]!=0||board[i+3][j+3]!=0||board[i+3][j+2]!=0||board[i+3][j+1]!=0))
    )
        return 0;

    else
        return 1;

}
//funcao para a restricao 3
int rest3(){
    //verifica se tem mais peças de um tipo de maior dimensão
    int i;
    for(i=0;i<7;i++){
        if(shiptype[i+1]>shiptype[i])
            return 0;
    }
    return 1;
}
//funcao para a restricao 4
int rest4(){

    int totalship=0, maxship, i;

    maxship = row*column/18;        //número máximo de barcos que o tabuleiro pode ter

    for(i=0;i<8;i++){               //número total de barcos
        totalship+=shiptype[i];
    }

    if(maxship>=totalship)          //verifica se tem mais barcos que o limite máximo
        return 1;

    else
        return 0;
}
//gerar um numero aleatorio com input maximo
int randomInt(int a){
    int r;
    r=(rand() % a) + 1;
    return r;
}

void jogo1(){


    unsigned long start_t=0, end_t=0, total_t=0;
    start_t = time(NULL);
    int r=0;
    int k /*k==contador de jogadas*/ ,j,i,b;
    char c;
    int cha;
    int count=0;

    printf("* -------------------------------Modo Jogo 1----------------------------------\n");
    printf("* Introduce the coords you pretend to attack [Columns(A-Z) and Rows(1-15)]:  \n");
    printf("* Make sure to type both characters together and capital letters. Example: C4 \n");

    for (k=0, b=0; count<shipcount; k++, b++){
    scanf(" %c%d", &c , &r);
    c = ((int) c) - 64;
    cha = c;
    r = row-r+1;
    invisible[r][cha] = 9; //atribuicao do valor atual as coordenadas introduzidas
    for(i = 0; i < row; i++){
        for(j = 0; j < column; j++){
            if(invisible[i+1][j+1]==9&&board[r-1][c-1]!=0){
                invisible[r][cha]=10; //atribuicao do valor de um barco as coordenadas atuais
                count++;
                }
            else if(invisible[i+1][j+1]==9&&board[r-1][cha-1]==0){
                invisible[r][cha]=11; //atribuicao do valor de um agua as coordenadas atuais
                }
        }
    }

    if(board[r-1][c-1]!=0){
        printf("%d\n", board[r-1][cha-1]);
    }
    else{
        printf("-\n");
    }
}
    end_t = time(NULL);
    total_t = end_t - start_t;
    printf("Fim de jogo: %d jogadas em %lu segundos\n", k, total_t);
}
//funcao com as instrucoes
void instrucoes(){
    printf("\tInstrucoes:\n \tInvocar o programa: ./wargame [OPTION]\n ");
    printf("\t'wargame' designa o nome do ficheiro executável contendo o programa desenvolvido.\n");
    printf("\t[OPTION] designa a possibilidade de o programa ser invocado com diferentes opções de funcionamento\n\n");
    printf("\tOptions:\n");
    printf("\t\t-h ajuda para o utilizador\n");
    printf("\t\t-t dimensões do tabuleiro (linha x coluna).\n");
    printf("\t\t-j modo de jogo (0 a 2)\n");
    printf("\t\t-p modo de posicionamento de peças pelo computador (1 a 2)\n");
    printf("\t\t-d modo de disparo de peças pelo computador (1 a 3)\n");
    printf("\t\t-1 número de peças tipo 1 (mínimo 1)\n");
    printf("\t\t-2 número de peças tipo 2\n");
    printf("\t\t-3 número de peças tipo 3\n");
    printf("\t\t-4 número de peças tipo 4\n");
    printf("\t\t-5 número de peças tipo 5\n");
    printf("\t\t-6 número de peças tipo 6\n");
    printf("\t\t-7 número de peças tipo 7\n");
    printf("\t\t-8 número de peças tipo 8\n");
    printf("\n\n\tCaso nao queira algum tipo de peça, -(1-8), deve deixar esse parametro em branco.\n");
    printf("\tAs opções -(1-8) não podem ser aplicadas caso o modo de posicionamento é o 1.\n");
}

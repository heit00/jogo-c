#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <conio.c>
#include <windows.h>
#define PI 3.14159265
//---
int diff = 0;
void medium();
int vida = 3;
int pontos = 0;
bool repeat = false;
void hard();
//declarando variaveis e funcoes iniciais
//----
void pl(char *frase, int time){ // pl = printf lento
    for (char *p = frase; *p; p++) {
        putchar(*p);
        fflush(stdout);
        Sleep(0);
    }
}
void desenhar(int a,int b)
{
	if(b>16){
		b = 16;
	}
	int ma=a/2;
	int mb=b/2;
	gotoxy(9,21);
	printf("C");
	gotoxy(10,20);
	for(int j=0; j<a; j++)
	{
		if(j==0)
			continue;
		if(j==ma)
		{
			gotoxy(10+j,20+1);
			printf("a");
		}
		gotoxy(10+j,20);
		printf("_");
	}
	printf("B");
	gotoxy(10,15);
	for(int i=0; i<b; i++)
	{
		if(i==mb)
		{
			gotoxy(10-2,20-i);
			printf("b");
		}
		gotoxy(10,20-i);
		printf("|");
	}
	gotoxy(10,20-b);
	printf("A");
	gotoxy(10+ma,20-mb);
	printf("c");
}
int good_sqrt(int a, int b, int c){//certificar que o delta pertenca ao conjunto dos numeros N (Naturais) 
    	float delta = pow((b),2)-4*(a)*(c);
    	if((sqrt(delta)/round(sqrt(delta))) == 1){
        	return delta;
    	}
    	else{
        	return 99;
    	}
}
void partens(char* B, char* C,int b, int c){//funcao para os sinais + e -
    if(b<0){
        *B=' ';
    }
    if(b>0 || b==0){
        *B='+';
    }
    if(c<0){
        *C=' ';
    }
    if(c>0 || c==0){
        *C='+';
    }
   
}
void ope(int *a, int *b, int*c, char *op, float *result, float *result2, char* nf, int diff) { // nucleo (de todas as funcoes)
    srand(time(NULL));
    int modo;
    int delta;
    if(diff == 0){ // definir de quando a quando o switch vai ir em funcao da dificuldade ;)
        modo = rand()%4;
    }
    else if(diff == 1){
        modo = rand()%2+4; 
    }
    else if(diff == 2){
        modo = rand()%2+6;
    }
    switch(modo){
        case 0:
            *op = '+';
            *b = rand() % 8;
            *a = rand() % 10;
            *result = (*a + *b);
            break;
        case 1:
            *op = '-';
            *a = rand() % 8 + 2;
            *b = rand() % 8;
            *result = (*a - *b);
            break;
        case 2:
            *op = 'x';
            *a = rand() % 6;
            *b = rand() % 9;
            *result = (*a * *b);
            break;
        case 3:
            *op = '/';
            *b = rand() % 9 + 1;
            *a = (rand() % 10 + 1) * *b;
            *result = (*a / *b);
            break;
        case 4:
            *op = '^';
            *a = rand() % 12;
            *b = rand() % 4;
            *result = pow(*a, *b);
            break;
        case 5:
            *op = 's';
            *b = rand()%30;
            *a = ((*b)*(*b));
            *result = (*b);
            break;
		case 6:
			*op='e';
			*a = 1;
            do{
                *b = rand()%10;
    		    *c = rand()%10;
                delta = good_sqrt(*a,*b,*c);
            }while(delta == 99);
			if(delta >=0 ){
				float sqrt_delta = sqrt(delta);
				*result = (-(*b)+sqrt_delta)/(2*(*a));
				*result2 = (-(*b)-sqrt_delta)/(2*(*a));
                nf = "REAL";
			}
			else{
				nf = "NAO REAL";
		    }
            break;
        case 7:
        	*op='p';
        	srand(time(NULL));
        	int random = rand()%6+1;
        	*a = 3*random;
			*b = 4*random;
			*c = sqrt(pow(*a,2)+pow(*b,2));
            break;
	}
}
void easy(){ // Dificuldade facil (operacoes basicas)
    int a, b;
    char op, resulchar[5];
    float result, resp;
    char* pEnd;
    while (pontos <= 5){
        ope(&a, &b, 0, &op, &result, 0, "n" , 0);
        printf("%d %c %d = ", a, op, b);
        fflush(stdin);
        gets(resulchar);
        resp = strtod(resulchar, &pEnd);
        if (result == resp) {
            ++pontos;
            printf("Acertou! Boa!!\nSeus pontos atuais: %d\nPontos restantes para o proximo nivel: %d\n",  (pontos-1), (6 - pontos));
        } else {
            --vida;
            printf("Voce errou! :(\nValor correto: %.0f\nSeus pontos atuais: %d\nSua vida atual: %d\n", result, pontos, vida);
            if (vida == 0) {
                printf("Voce morreu!");
                printf("\nSeus pontos finais: %d", pontos);
                break;
            }
        }
    }
    if(pontos >= 5){
        Sleep(1000);
        system("cls");
        pl("Voce passou para o ", 2);
        pl("NIVEL MEDIO!", 100);
        printf("\nBoa sorte.\n");
        Sleep(1000);
        medium();
    }
}
void medium(){ // Dificuldade media (exp e sqrt)
    int a, b;
    char op, resulchar[5];
    float result, resp;
    char* pEnd;
    while (pontos < 10) {
        ope(&a, &b, 0, &op, &result,0,"n",1);
        if (op == 's') {
            printf("Raiz quadrada de %d = ", a);
        } else {
            printf("%d %c %d = ", a, op, b);
        }
        fflush(stdin);
        gets(resulchar);
        resp = strtod(resulchar, &pEnd);
        if (result == resp) {
            ++pontos;
            printf("Acertou! Boa!!\nSeus pontos atuais: %d\nPontos restantes para o proximo nivel: %d\n", pontos - 1, 11 - pontos);
        } else {
            --vida;
            printf("Voce errou! :(\nValor correto: %.0f\nSeus pontos atuais: %d\nSua vida atual: %d\n", result, pontos, vida);
            if (vida == 0) {
                printf("Voce morreu!");
                printf("\nSeus pontos finais: %d", pontos);
                break;
            }
        }
    }
    if(pontos >= 10){
        Sleep(1000);
        system("cls");
        pl("Voce passou para o ", 2);
        pl("NIVEL D I F I C I L!", 500);
        pl("\nBoa sorte (porque você provavelmente vai precisar)\n", 30);
        Sleep(1000);
        hard();
    }
}
void hard() {// funcao para realizacao de operacoes de grau alto (para nosso contexto) tais como: equacoes do segundo grau e calculo de hipotenusas em triangulos retangulos
    int a, b, c;
	char C, B, op, nf[15], resulchar[5];
    char* pEnd;
    float result, result2;
    while (pontos < 20){
    	srand(time(NULL));
        ope(&a, &b, &c, &op, &result, &result2 , nf, 2);
        if(op == 'e'){
        	system("cls");
            partens(&B,&C,b,c);
            printf("\nResolva a seguinte equacao:\n\t%dx^2%c%dx%c%d = 0",a,B,b,C,c);
            if(strcmpi(nf,"NAO REAL") == 0){
                printf("\nx': ");
                char resp[20], resp2[20];
                gets(resp);
                printf("\nx'': ");
                gets(resp2);
                if(strcmpi(resp,"NAO REAL") == 0 || strcmpi(resp2,"NAO REAL") == 0){
                    ++pontos;
                    printf("Acertou! Boa!!\nSeus pontos atuais: %d\nPontos restantes para o proximo nivel: %d\n", pontos - 1, 21 - pontos);
                }
                else{
                    --vida;
                    printf("Voce errou! :(\nResultado correto: %s\nSeus pontos atuais: %d\nSua vida atual: %d\n", nf, pontos, vida);
                    if (vida == 0) {
                    printf("Voce morreu!");
                    printf("\nSeus pontos finais: %d", pontos);
                    break;
                    }
                }
            }
            else{
                int resp1, resp2;
                printf("\nx': ");
                scanf("%d",&resp1);
                fflush(stdin);
                printf("\nx'': ");
                scanf("%d",&resp2);
                fflush(stdin);
                system("cls");
                if(resp1 == result && resp2 == result2 || resp2 == result && resp1 == result2){
                    ++pontos;
                    printf("Acertou! Boa!!\nSeus pontos atuais: %d\nPontos restantes para o proximo nivel: %d\n", pontos - 1, 6 - pontos);
                    Sleep(3000);
                }
                else if(resp1 == result || resp2 == result2){                                                     
                    printf("Voce acertou uma das raizes, boa!!\nSeus pontos atuais: %d", pontos - 1);
                    Sleep(3000);
                }
                else{
                    --vida;
                    printf("Voce errou! :(\nResultados corretos (respectivamente): %f e %f\nSeus pontos atuais: %d\nSua vida atual: %d\n",result, result2, pontos, vida);
                    Sleep(3000);
                    if (vida == 0) {
                    printf("Voce morreu!");
                    printf("\nSeus pontos finais: %d", pontos);
                    break;
                    Sleep(2500);
                    }
                }
            }
        }
        else if(op == 'p'){
        	srand(time(NULL));
        	system("cls");
        	int resp;
        	printf("\nCalcule a hipotenusa (lado c) a seguir considerando que a = %d e b = %d: ",a,b);
        	desenhar(a,b);
        	gotoxy(1,3);
        	printf("C = ");
        	scanf("%d",&resp);
        	fflush(stdin);
        	system("cls");
        	if(resp == c){
        		++pontos;
                printf("Acertou! Boa!!\nSeus pontos atuais: %d", pontos - 1);
                Sleep(3000);
        	}
        	else{
            	--vida;
                printf("Voce errou! :(\nResultado correto: %d\nSeus pontos atuais: %d\nSua vida atual: %d\n",result, pontos, vida);
                Sleep(3000);
                if (vida == 0) {
                printf("Voce morreu!");
                printf("\nSeus pontos finais: %d", pontos);
                Sleep(2000);
                break;
			}
			}
		}
	}
}
void diff_escolha(){
    system("cls");
    pl("Beleza, ", 40);
    pl("entao, qual dificuldade voce quer comecar (ao longo do jogo, ela aumentara)\n 1- Facil;\n 2- Medio;\n 3- Dificil.\nDIGITE AQUI: ", 1);
    scanf("%d", &diff);
    do {
        if (diff == 1) {
            system("cls");
            easy();
            break;
        } else if (diff == 2) {
            system("cls");
            medium();
            break;
        } else if (diff == 3) {
            system("cls");
            hard();
            break;
        } else {
            printf("Escolha uma opcao valida!\n");
            diff = 0;
            scanf("%d", &diff);
        }
    } while (diff != 1 && diff != 2 && diff != 3); // Corrigido para usar && em vez de ||.
}
void graph(int LAR, int ALT){//imprimir o grafico bonito no terminal
    int x, y;
    double coss;
	gotoxy(1, 1);
	for(x = 2; x < LAR+40; x++) {
		int ran = rand()%15;
		coss = cos(((x - LAR / 2) * 2 * PI) / LAR*2); // cosseno de x convertido pra radiano, ja que a funcao cos nao aceita angulo
		y = ((coss)*(ALT/2)); //conversao do cosseno pra coordenada y, 1-coss pra inverter os extremos, 1-1=0, y la em cima, etc || o alt/2 serve pra pegar a metade da tela
		gotoxy(x + 1, (ALT-2) - y);
		printf("*");
		textcolor(ran-2);
		Sleep(10);
	}
    textcolor(15);
    textbackground(0);
}
int main() {
    system("cls");
    char title[]="Jogo da adivinhacao, de matematica!", choose;
    int n, call_title = 0, call_init = 0;
    srand(time(NULL));
    setlocale(LC_ALL, "");
    bool repeat = true;
    do{
        while(kbhit() == false){
            if(call_title == 0 ){
                gotoxy(1, 1);
	            graph(40, 5);
            }
            gotoxy(1, 1);
            printf("|=====================================|");
            Sleep(100);
            gotoxy(1, 1);
            printf("|+++++++++++++++++++++++++++++++++++++|");
            gotoxy(1, 3);
            printf("|+++++++++++++++++++++++++++++++++++++|");
            Sleep(100);
            gotoxy(1, 3);
            printf("|=====================================|");
            if(call_title==0){//chamar animacao do titulo so uma vez
                for(int i=0; i<=(strlen(title)-1); i++){
                    gotoxy((4+i), 2);//nivelar titulo
                    n = rand()%9+1;
                    printf("%d", n);
                    gotoxy((3+i), 2);//nivelar titulo tbm
                    Sleep(1);
                    printf("%c", title[i]);
                    Sleep(1);
                }
                gotoxy(38, 2);
                printf(" ");//certificar que nao haja nada impresso na frente do titulo
                call_title++;
            }
            if(call_init == 0){//chamar menu so uma vez
                printf("\n\n");
                pl("1- Comecar jogo;\n", 1);
                pl("2- Como jogar?\n", 1);
                call_init++;
            }
        }
        gotoxy(1, 6);
        if(kbhit() == true){
            choose = getchar();
            fflush(stdin);
            if(choose == '1') {
                repeat = false;
                diff_escolha();
                break;
            } 
            if(choose == '2') {
                repeat = false;
                pl("Voce deve responder a um problema matematico, se acertar voce ganha pontos para o proximo nivel!\nSe voce errar, perde uma vida e nao ganha pontos\nVoce acha que consegue? ;)\n", 1);
                printf("\nPressione qualquer tecla para comecar! ");
                fflush(stdin);
                while (kbhit() == true) {
                    continue;
                }
                getchar();
                system("cls");
                diff_escolha();
                break;
            }else{
                printf("Escolha uma opcao valida\n\n");
                call_init = 0;
                call_title = 0;
                Sleep(1000);
                system("cls");
                repeat = true;
            }
        }
        else{
            continue;
        }
    }while(repeat == true);
}

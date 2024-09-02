#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <conio.h> // Alterado para <conio.h> e removido .c
#include <windows.h>
#define PI 3.14159265358979323846
#define e 2.7182818284590452353602874713526624977572470936999595749669676277240766303535945713821785251664274
//---
int diff = 0;
void medium();
int vida = 3;
int pontos = 0;
bool repeat = false;
//declarando variaveis e funcoes iniciais
//----
void pl(char *frase, int time) { // pl = printf lento
    for (char *p = frase; *p; p++) {
        putchar(*p);
        fflush(stdout);
        Sleep(0);
    }
}
int good_sqrt(int a, int b, int c){
    float delta = pow((b),2)-4*(a)*(c);
    if((sqrt(delta)/round(sqrt(delta))) == 1){
        return delta;
    }
    else{
        return 99;
    }
}
//funcao para os sinais + e -
void partens(char* B, char* C,int b, int c)
{
    if(b<0)
    {
        *B=' ';
    }
    if(b>0 || b==0)
        *B='+';
    if(c<0)
    {
        *C=' ';
    }
    if(c>0 || c==0)
        *C='+';
   
}
void ope(int *a, int *b, int*c, char *op, float *result, float *result2, char* nf, int diff) { // nÃÂÃÂºcleo (de todas as funÃÂÃÂ§ÃÂÃÂµes)
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
    switch(modo) {
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
            *a = pow(rand() % 20, 2);
            *result = sqrt(*a);
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
            break;
            
            
	}
}
void easy() { // Dificuldade facil (operacoes basicas)
    int a, b;
    char op;
    float result, resp;
    while (pontos <= 5) {
        ope(&a, &b, 0, &op, &result, 0,"n", 0);
        printf("%d %c %d = ", a, op, b);
        scanf("%f", &resp);
        if (result == resp) {
            ++pontos;
            printf("Acertou! Boa!!\nSeus pontos atuais: %d\nPontos restantes para o proximo nivel: %d\n", (pontos - 1), (6 - pontos));
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
    Sleep(1000);
    system("cls");
    pl("Voce passou para o ", 2);
    pl("NIVEL MEDIO!", 100);
    printf("\nBoa sorte.\n");
    Sleep(1000);
    medium();
}

void medium() { // Dificuldade media (exp e sqrt)
    int a, b;
    char op;
    float result, resp;
    while (pontos < 10) {
        ope(&a, &b, 0, &op, &result,0,"n",1);
        if (op == 's') {
            printf("Raiz quadrada de %d = ", a);
        } else {
            printf("%d %c %d = ", a, op, b);
        }
        scanf("%f", &resp);
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
}
void hard() {// funcao para realizacao de operacoes de grau alto (para nosso contexto) tais como: equacoes do segundo grau e calculo de hipotenusas em triangulos retangulos
    int a, b, c;
	char C,B;
    char op, nf[15];
    float result, result2;
    while (pontos < 20){
        ope(&a, &b, &c, &op, &result, &result2,nf,2);
        if(op == 'e'){
            partens(&B,&C,b,c);
            printf("\n%f %f",result, result2);
            printf("Resolva a seguinte equacao:\n\t%dxÃÂ²%c%dx%c%d = 0",a,B,b,C,c);
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
                if(resp1 == result && resp2 == result2 || resp2 == result && resp1 == result2){
                    ++pontos;
                    printf("Acertou! Boa!!\nSeus pontos atuais: %d\nPontos restantes para o proximo nivel: %d\n", pontos - 1, 6 - pontos);
                }
                else if(resp1 == result || resp2 == result2){                                                     
                    printf("Voce acertou uma das raizes, boa!!\nSeus pontos atuais: %d", pontos - 1);
                }
                else{
                    --vida;
                    printf("Voce errou! :(\nResultados corretos (respectivamente): %f e %f\nSeus pontos atuais: %d\nSua vida atual: %d\n",result, result2, pontos, vida);
                    if (vida == 0) {
                    printf("Voce morreu!");
                    printf("\nSeus pontos finais: %d", pontos);
                    break;
                    }
                }
            }
        }
        
	}
}

void diff_escolha() {
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

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "");
    bool repeat = false;
    do {
        int choose;
        pl("=====================================\n", 10);
        pl("=Jogo da adivinhacao, de matematica!=\n", 10);
        pl("=====================================\n", 10);
        pl("1- Comecar jogo;\n", 1);
        pl("2- Como jogar?\n", 1);
        scanf("%d", &choose);
        if (choose == 1) {
            diff_escolha();
        } else if (choose == 2) {/* n=string[i]-'0' */
            pl("Voce deve responder a um problema matematico, se acertar voce ganha pontos para o proximo nivel!\nSe voce errar, perde uma vida e nao ganha pontos\nVoce acha que consegue? ;)\n", 1);
            printf("\nPressione qualquer tecla para comecar!");
            while (kbhit() == false) {
                continue;
            }//fgets(string de entrada, tamanho, ponteiro FILE);
            getchar();
            system("cls");
            diff_escolha();
        } else {
            printf("Escolha uma opcao valida\n\n");
            Sleep(1000);
            system("cls");
            repeat = true;
        }
    } while (repeat);
}

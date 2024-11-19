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
int diff = 0; //Dificuldade
void medium();
void hard();
int vida = 3;
int pontos = 0;
bool repeat = false;
//Declarando variáveis e funções iniciais
//---

void pl(char *frase, int time){ //pl = "printf lento", função para imprimir algo letra por letra e com um certo delay
    for (char *p = frase; *p; p++) {
        putchar(*p);
        fflush(stdout);
        Sleep(time);
    }
}

void desenhar(int a, int b) { //Função para desenhar o triângulo ABC no quiz de pitágoras (cálculo da hipotenusa)
	int randcor;
    if (b > 17) {
        b = 17;
    }
    int ma = a / 2;
    int mb = b / 2;
    for (int i = 0; i < b; i++) {
        gotoxy(10, 20 - i);  
        for (int j = 0; j <= i * (a/(float)b); j++) {
        	randcor = rand()%16;
        	textcolor(randcor);
            printf("*");
        }
    }
    textcolor(15);
    gotoxy(10 + ma, 20 - mb);
    printf("c");
    gotoxy(9, 20 - mb);
    printf("b");
    gotoxy(10+ma,20 - b);
    printf("a");
    gotoxy(10, 20);
    printf("A");
    gotoxy(10 + a, 20 -b);
    printf("B");
    gotoxy(10, 20 - b);
    printf("C");
}

int good_sqrt(int a, int b, int c){ //Certificar que o delta pertence ao conjunto dos Naturais 
    float delta = pow((b),2)-4*(a)*(c);
    if((sqrt(delta)/round(sqrt(delta))) == 1){
        return delta;
    }
    else{
        return 99;
    }
}

void partens(char* B, char* C,int b, int c){ //Função para os sinais '+' e '-'
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

void ope(int *a, int *b, int*c, char *op, float *result, float *result2, int diff){ //Núcleo (de todas as funções)
    srand(time(NULL));
    int modo;
    int delta;
    //////////
    if(diff == 0){ //Definir de quanto a quanto o switch vai ir em função da dificuldade ;)
        modo = rand()%4; //Fácil
    }
    else if(diff == 1){
        modo = rand() % 2 + 4; //Médio
    }
    else if(diff == 2){
        modo = rand() % 2 + 6; //Difícil
    }
    switch(modo){ //Seleção de operações e valores aleatórios
        case 0: //Adição simples
            *op = '+';
            *b = rand() % 8;
            *a = rand() % 10;
            *result = ((*a) + (*b));
            break;
        case 1: //Subtração simples
            *op = '-';
            *a = rand() % 8 + 2;
            *b = rand() % 8;
            *result = ((*a) - (*b));
            break;
        case 2: //Multiplicação
            *op = 'x';
            *a = rand() % 6;
            *b = rand() % 9;
            *result = ((*a) * (*b));
            break;
        case 3: //Divisão com números naturais
            *op = '/';
            *b = rand() % 9 + 1;
            *a = (rand() % 10 + 1) * (*b);
            *result = ((*a) / (*b));
            break;
        case 4: //Potenciação, limite de expoente = 3
            *op = '^';
            *a = rand() % 12;
            *b = rand() % 4;
            *result = pow(*a, *b);
            break;
        case 5: //Radiciação com números naturais
            *op = 's';
            *b = rand() % 30;
            *a = ((*b) * (*b));
            *result = (*b);
            break;
		case 6: //Equação do segundo grau com soluções inteiras
			*op='e';
			*a = 1;
            do{
                *b = rand()%21 - 10;
    		    *c = rand()%21 - 10;
                delta = good_sqrt(*a,*b,*c);
            }while(delta == 99);
			if(delta >=0 ){
				float sqrt_delta = sqrt(delta);
				*result = (-(*b)+sqrt_delta)/(2*(*a));
				*result2 = (-(*b)-sqrt_delta)/(2*(*a));
			}
            break;
        case 7: //Cálculo de hipotenusa
        	*op='p';
        	srand(time(NULL));
        	int random = rand()%10+1;
        	*a = 3*random;
			*b = 4*random;
			*c = sqrt(pow(*a,2)+pow(*b,2));
            break;
	}
}

void easy(){ //Dificuldade fácil (operações básicas)
    int a, b;
    char op, resulchar[5]; //op = char da representação da operação; resulchar = char do resultado inserido pelo usuário
    float result, resp;
    char* pEnd; //Usado para converter char para int (1)
    while(pontos <= 5){
        ope(&a, &b, 0, &op, &result, 0 , 0);
        printf("%d %c %d = ", a, op, b);
        fflush(stdin);
        gets(resulchar);
        resp = strtod(resulchar, &pEnd); //Converter char para int (2); tem muitos jeitos de fazer isso, mas esse deu certo, então deixemos assim.
        if(result == resp){
            ++pontos;
            printf("Acertou! Boa!!\nSeus pontos atuais: %d\nPontos restantes para o próxsimo nível: %d\n\n",  pontos, (6 - pontos));
        }
		else{
            --vida;
            printf("Você errou! :(\nValor correto: %.0f\nSeus pontos atuais: %d\nSua vida atual: %d\n\n", result, pontos, vida);
            if(vida == 0){
                printf("Você morreu!");
                printf("\nSeus pontos finais: %d", pontos);
                break;
            }
        }
    }
    if(pontos >= 5){ //Passagem para o nível médio
        Sleep(1000);
        system("cls");
        pl("Você passou para o ", 2);
        pl("NÍVEL MÉDIO!", 100);
        printf("\nBoa sorte.\n\n");
        Sleep(1000);
        medium();
    }
}

void medium(){ //Dificuldade média
    int a, b;
    char op, resulchar[5]; //op = char da representação da operação; resulchar = char do resultado inserido pelo usuário
    float result, resp;
    char* pEnd; // Usado p/ char --> int
    while(pontos < 10){
        ope(&a, &b, 0, &op, &result,0,1);
        if(op == 's'){
            printf("Raiz quadrada de %d = ", a);
        }
		else{
            printf("%d %c %d = ", a, op, b);
        }
        fflush(stdin);
        gets(resulchar);
        resp = strtod(resulchar, &pEnd); //Char --> int
        if(result == resp){
            ++pontos;
            printf("Acertou! Boa!!\nSeus pontos atuais: %d\nPontos restantes para o próximo nível: %d\n\n", pontos, 10 - pontos);
        }
		else{
            --vida;
            printf("Você errou! :(\nValor correto: %.0f\nSeus pontos atuais: %d\nSua vida atual: %d\n\n", result, pontos, vida);
            if(vida == 0){
                printf("Você morreu!");
                printf("\nSeus pontos finais: %d", pontos);
                break;
            }
        }
    }
    if(pontos >= 10){ //Passagem para o nível difícil
        Sleep(1000);
        system("cls");
        pl("Você passou para o ", 2);
        pl("NÍVEL  D I F Í C I L!", 200);
        pl("\nBoa sorte (porque você provavelmente vai precisar)\n", 30);
        Sleep(1000);
        hard();
    }
}

void hard() { //Função para realização de operações de alto grau (para nosso contexto), como equações do segundo grau e cálculo de hipotenusas em triângulos retângulos
    int a, b, c;
	char C, B, op; //op = char da representação da operação
    float result, result2;
    while(pontos < 20){
    	srand(time(NULL));
        ope(&a, &b, &c, &op, &result, &result2, 2);
        if(op == 'e'){ //op usado para determinar qual operação irá acontecer, nesse caso, equação
            system("cls");
            partens(&B,&C,b,c);
            printf("\nResolva a seguinte equação:\n\tx² %c %dx %c %d = 0",B,b,C,c);
            int resp1, resp2;
            printf("\nx': ");
            scanf("%d",&resp1);
            fflush(stdin);
            printf("\nx'': ");
            scanf("%d",&resp2);
            fflush(stdin);
            if( (resp1 == result && resp2 == result2) || (resp2 == result && resp1 == result2)){
                ++pontos;
                printf("Acertou! Boa!!\nSeus pontos atuais: %d\nPontos restantes para o próximo nível: %d\n\n", pontos, 20 - pontos);
                Sleep(500);
            }
            else if(resp1 == result || resp2 == result2){                                                     
                printf("Você acertou uma das raízes, boa!!\nSeus pontos atuais: %d", pontos);
                Sleep(500);
            }
            else{
                --vida;
                printf("Você errou! :(\nResultados corretos (respectivamente): %.0f e %.0f\nSeus pontos atuais: %d\nSua vida atual: %d\n\n",result, result2, pontos, vida);
                Sleep(500);
                if (vida == 0) {
                printf("Você morreu!");
                printf("\nSeus pontos finais: %d", pontos);
                break;
                }
            }
        }
        else if(op == 'p'){ //op para cálculo de hipotenusa
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
                printf("Acertou! Boa!!\nSeus pontos atuais: %d\nPontos restantes para o próximo nível: %d\n", pontos, 20 - pontos);
                Sleep(3000);
        	}
        	else{
            	--vida;
                printf("Você errou! :(\nResultado correto: %d\nSeus pontos atuais: %d\nSua vida atual: %d\n", c, pontos, vida);
                Sleep(3000);
                if (vida == 0) {
                printf("Você morreu!");
                printf("\nSeus pontos finais: %d", pontos);
                Sleep(2000);
                break;
			}
			}
		}
	}
	if(pontos >= 20){ //Finalização do jogo
        Sleep(1000);
        system("cls");
        pl("PARABÉNS!", 100);
        pl("\nVocê passou do nível mais difícil e concluiu o jogo!", 30);
        pl("\n\nObrigado por jogar! ;)\n", 20);
    }
}

void diff_escolha(){ //Seleção de dificuldade
    system("cls");
    pl("Beleza, ", 40);
    pl("então, qual dificuldade você quer começar (ao longo do jogo, ela aumentará)\n 1- Fácil\n 2- Médio\n 3- Difícil\n>  ", 1);
    diff = getchar();
    fflush(stdin);
    do{
        if(diff == '1'){
            system("cls");
            easy();
            break;
        }
		else if(diff == '2'){
            system("cls");
            medium();
            break;
        }
		else if(diff == '3'){
            system("cls");
            hard();
            break;
        }
		else{
            printf("Escolha uma opção válida!\n");
            diff = getchar();
            fflush(stdin);
        }
    }while(diff != 1 && diff != 2 && diff != 3); //Corrigido para usar && em vez de ||.
}

void graph(int LAR, int ALT){ //Imprimir o gráfico do menu
    int x, y;
    double coss;
	gotoxy(1, 1);
	for(x = 2; x < LAR+40; x++){
		int ran = rand()%15;
		coss = cos(((x - LAR / 2) * 2 * PI) / LAR*2); //Cosseno de x convertido pra radiano, já que a função cos não aceita ângulos
		y = ((coss)*(ALT/2)); //Conversão do cosseno pra coordenada y, 1-cos pra inverter os extremos, 1-1=0, y lá em cima, etc || o alt/2 serve pra pegar a metade da tela
		gotoxy(x + 1, (ALT-2) - y);
		printf("*");
		textcolor(ran-2);
		Sleep(10);
	}
    textcolor(15);
    textbackground(0);
}

int main(){
    system("cls");
    char title[] = "Math Quest", choose;
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
            if(call_title==0){ //Chamar animação do título apenas uma vez
                gotoxy(1, 2);
                printf("                                       ");
				for(int i=0; i<=(strlen(title)-1); i++){
                    gotoxy((14+i), 2); //Nivelar título
                    n = rand()%9+1;
                    printf("%d", n);
                    gotoxy((14+i), 2); //Nivelar título tbm
                    Sleep(1);
                    printf("%c", title[i]);
                    Sleep(1);
                }
                call_title++;
            }
            if(call_init == 0){ //Chamar menu apenas uma vez
                printf("\n\n");
                pl("1- Começar jogo;\n", 10);
                pl("2- Como jogar?\n>\n ", 10);
                call_init++;
            }
        }
        gotoxy(3, 6);
        if(kbhit() == true){
            choose = getchar();
            fflush(stdin);
            if(choose == '1'){ //Chamar o menu de dificuldades
                repeat = false;
                diff_escolha();
                break;
            }
            if(choose == '2'){ //Explicar o funcionamento do jogo
                repeat = false;
                pl("Você deve responder a um problema matemático, se acertar você ganha pontos para o próximo nível!\nSe você errar, perde uma vida e não ganha pontos.\nVocê acha que consegue? ;)\n", 1);
                pl("Pressione enter para começar! ", 10);
                fflush(stdin);
                while (kbhit() == true) {
                    continue;
                }
                getchar();
                system("cls");
                diff_escolha();
                break;
            }
			else{
                printf("Escolha uma opção válida\n\n");
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

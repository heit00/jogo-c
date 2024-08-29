#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <conio.c>
int esc;
void init(){
	printf("Bem vindo ao quiz de matemática!\n");
	Sleep(1000);
	printf("Escolha uma das opções: ");
	printf("1- Jogar\n 2- Como jogar?");
	scanf("%d", &esc);
	esc == 1?
}
int main(){
	setlocale(LC_ALL, "");
	init();
}

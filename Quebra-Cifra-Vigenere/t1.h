/* 
Seguranca Computacional - 2021/1 - Trabalho 1
Alice de Lima da Silva - 180112601
Carlos Eduardo de Oliveira Ribeiro - 180099094
*/

#include <bits/stdc++.h>

#define MAX_TAMANHO_CHAVE 20

using namespace std;

string cifrar(string texto, string chave);

string decifrar(string texto, string chave);

string padroniza(string texto);

double i_coincidencia(string texto);

int tamanho_chave(string texto);

char frequencia(string fatia, int idioma);

string quebra_chave(string texto, int tamanho);

void encontra_chave(string texto, int idioma);

string padroniza2(string texto);


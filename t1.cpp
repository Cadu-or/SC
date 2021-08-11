#include "t1.h"

using namespace std;

/*Vetor com as letras do alfabeto que e consultado nas funcoes de cifragem e decifragem */

char alfabeto[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

/*Vetores com a frequencias das palavras em portugues e ingles*/

vector <double> inglesfreq = {0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 
                              0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 
                              0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987, 
                              0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150, 
                              0.01974, 0.00074};

vector <double> portuguesfreq = {0.14630, 0.01040, 0.03880, 0.04990, 0.12570, 0.01020, 
                                 0.01300, 0.01280, 0.06180, 0.00400, 0.00020, 0.02780, 
                                 0.04740, 0.05050, 0.10730, 0.02520, 0.01200, 0.06530, 
                                 0.07810, 0.04340, 0.04630, 0.01670, 0.00100, 0.02100, 
                                 0.00100, 0.04700};

/*Vetor que armazena as fatias do texto na funcao tamanho_chave*/
vector <vector <string> > fatias(26);

/*Funcao que recebe um texto e uma chave e realiza a cifragem */
string cifrar(string texto, string chave){
    string ans;
    int i = 0;
    int j = 0;

    while(i <= texto.size()){
        if(texto[i] >= 'a' and texto[i] <= 'z'){
            int aux1 = texto[i] - 97;
            int aux2 = chave[j] - 97;
            ans.push_back(alfabeto[(aux1 + aux2)%26]);
            j++;

        }else{
            ans.push_back(texto[i]);
        }

        i++;

        if(j == chave.length()){
            j = 0;
        }
    }

    return ans;
}

/*Funcao que recebe um texto e uma chave e realiza a decifragem */
string decifrar(string texto, string chave){
    string ans;
    int i=0, j=0;

    while(i <= texto.size()){
        if(texto[i] >= 'a' and texto[i] <= 'z'){
            int aux1 = texto[i] - 97;
            int aux2 = chave[j] - 97;
            ans.push_back(alfabeto[(((aux1 - aux2) + 26) % 26)]);
            j++;
        }
        else{
            ans.push_back(texto[i]);
        }
        
        if(j == chave.size()){    /*se chegou ao fim da chave, recomecar*/
            j = 0;
        }
        i++;
    }

    return ans;
}

/* Funcao que converte todas as letras para minusculo */

string padroniza(string texto){
    string padrao;
    for(int i = 0; i <= texto.size(); i++){
        if(texto[i] >= 'A' and texto[i] <= 'Z'){
            padrao.push_back(tolower(texto[i]));
        }else{
            padrao.push_back(texto[i]);
        }
    }

    return padrao;
}

/* Funcao que padroniza os textos, ignorando espacos, caracteres especiais e passa as letras para minusculo */
string padroniza2(string texto){
    string padrao;
    for(int i = 0; i < texto.size(); i++){
        if(texto[i] >= 'A' and texto[i] <= 'Z'){
            padrao.push_back(tolower(texto[i]));

        }else if(texto[i] >= 'a' and texto[i] <= 'z'){
            padrao.push_back(texto[i]);

        }
    }
    return padrao;
}

/*Funcao que calcula o indice de coincidencia de uma fatia*/
double i_coincidencia(string texto){
    double soma_freq, i_coincidencia; 
    double tamanho = texto.length();

    for(int i = 0; i < 26; i++){
        int contador = count(texto.begin(), texto.end(), alfabeto[i]); // Formula do indice de coincidencia
        soma_freq += (contador * (contador - 1));
    }

    i_coincidencia = soma_freq/(tamanho*(tamanho-1));
    
    return i_coincidencia;
}

/* Funcao que recebe o texto cifrado e retorna o tamanho da chave*/
int tamanho_chave(string texto){
    int chute1 = 0, chute2 = 0;
    vector <double> indices_c, aux;
    
    for(int i = 1; i <= MAX_TAMANHO_CHAVE; i++){ // 1 a 20
        double media_ic = 0.0, ic_soma = 0.0;
        for(int j = 0; j < i; j++){
            string sequencia = "";
            for(int k = 0; k < texto.length() - j; k+=i){
                sequencia += texto[j+k];
            }
            fatias[i].push_back(sequencia);
            if(sequencia.length() > 1){
                ic_soma += i_coincidencia(sequencia); 
            }
        }
        if(i != 0){
            media_ic = ic_soma/(double)i;
        }
        indices_c.push_back(media_ic);
    }
    aux = indices_c;
    
    sort(aux.begin(), aux.end(), greater<double>());

    for(int i = 0; i < indices_c.size(); i++){
        if(aux[0] == indices_c[i]){
            chute1 = i+1;
        }
        if(aux[1] == indices_c[i]){
            chute2 = i+1;
        }
    }

    if(chute1 % chute2 == 0){
        return chute2;
    }else{
        return chute1;
    }
}

/*Funcao que analisa a frequencia das letras e aplica o metodo X2 para encontrar um caractere
da chave*/
char frequencia(string fatia, int idioma){
    vector<double> X2(26), aux2, lingua;

    if(idioma == 1){
        lingua = inglesfreq;
    }
    else{
        lingua = portuguesfreq;
    }

    for(int i = 0; i < 26; i++){                            // Quantidade de deslocamento
        vector <char> sequencia;

        double qaux =0.0;
        
        for(int j = 0; j < fatia.size(); j++){              // Desloca i vezes
            char seq = (((fatia[j]-97-i+26) % 26)+97);
            sequencia.push_back(seq);
        }

        vector<double> cont_freq(26,0);

        for(int j = 0; j < sequencia.size(); j++){          // Contador de frequencia 
            cont_freq[(int)(sequencia[j]-97)]++;
        }
 
        for(int j = 0; j < 26; j++){
            cont_freq[j] = (cont_freq[j]/(double)fatia.size()); // Media das frequencias
        }

        for(int j = 0; j < 26; j++){
            double aux1 = (cont_freq[j] - (double)(lingua[j])); // Formula X2
            qaux += (aux1*aux1/(double)(lingua[j]));
        }
        
        X2[i] = qaux;
    }

    aux2 = X2;
    sort(aux2.begin(), aux2.end());
    int indice = 0;
    
    for(int i = 0; i < X2.size(); i++){
        if(aux2[0] == X2[i]){
            indice = i;
        }
    }
    
    return (char)(indice+97);
}

/* Funcao que recebe o texto cifrado, o tamanho da chave e o idioma do texto. 
De acordo com as fatias escolhidas chama a funcao frequencia que retorna cada letra da chave.*/
string quebra_chave(string texto, int tamanho, int idioma){
    string chave;

    for(int i = 0; i < tamanho; i++){
        string fatia = fatias[tamanho][i];
        chave += frequencia(fatia, idioma);
        fatias[i].clear();
    }

    return chave;
}

/*Funcao corrente dos metodos da chave, chama primeiramente a funcao responsavel pelo tamanho da chave, 
em seguida quebra_chave que encaminha o processo de descobrir os caracteres da chave, por ultimo chama
a funcao de decifragem com o texto e a respectiva chave*/
void encontra_chave(string texto, int idioma){
    int tamanho = tamanho_chave(texto);
    string chave;
    
    cout << "Tamanho da chave: " << tamanho << endl;
    
    chave = quebra_chave(texto, tamanho, idioma);

    cout << "Chave: " << chave << endl;

    texto = decifrar(texto, chave);

    cout << "Texto: " << texto << endl;
}
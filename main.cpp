#include "t1.h"

using namespace std;

int main(){
    char op;
    string chave, texto, ans;
    int idioma=-1;
    /*menu interativo*/
    do{
        cout << "MENU\n\tFUNCIONALIDADES" << endl;
        cout << "1 - Codificar texto" << endl;
        cout << "2 - Decodificar texto" << endl; 
        cout << "3 - Encontrar chave" << endl;
        cout << "4 - Sair" << endl;
        cin >> op;

        switch(op){
            case '1':
                cout << "Digite o texto:" << endl;
                cin.ignore();
                getline(cin, texto);
                texto = padroniza(texto);
                cout << "\nDigite a chave:" << endl;
                cin >> chave;
                ans = cifrar(texto, chave);
                cout << ans << endl;
                break;
            case '2':
                cout << "Digite o texto a ser decodificado:" << endl;
                cin.ignore();
                getline(cin, texto);
                texto = padroniza(texto);
                cout << "\nDigite a chave:" << endl;
                cin >> chave;
                ans = decifrar(texto, chave);
                cout << ans << endl;;
                break;
            case '3':
                cout << "Digite o texto cifrado: " << endl;
                cin.ignore();
                getline(cin, texto);
                cout << "Por favor informe o idioma do texto:\n Digite 1 para inglês ou 2 para portugues" << endl;
                cin >> idioma;
                if(idioma != 1 && idioma != 2){
                    break;
                }
                texto = padroniza2(texto);
                encontra_chave(texto, idioma);
                break;
        }
    }while(op != '4');

    
    return 0;
}
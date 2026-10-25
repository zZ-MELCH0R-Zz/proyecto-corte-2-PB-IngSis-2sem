#include "MyString.h"
#include <iostream>
#include <ctype.h>
using namespace std;

//=============== ANALIZAR TEXTO ===============//

int totalCaracteres(const char t[]){
    int n = 0;
    while(t[n] != '\0'){
        n++;
    }
    return n;
}

int contarVocales(const char t[]){
    int cont = 0;
    for(int i = 0; t[i] != '\0'; i++){
        char c = tolower((unsigned char)t[i]);
        if(c=='a' || c=='e' || c=='i' || c=='o' || c=='u'){
            cont++;
        }
    }
    return cont;
}

int contarNumeros(const char t[]){
    int cont = 0;
    for(int i = 0; t[i] != '\0'; i++){
        if(isdigit((unsigned char)t[i])){
            cont++;
        }
    }
    return cont;
}

int contarEspacios(const char t[]){
    int cont = 0;
    for(int i = 0; t[i] != '\0'; i++){
        if(isspace((unsigned char)t[i])){
            cont++;
        }
    }
    return cont;
}

// Especial = ni letra, ni numero, ni espacio (solo se miran los caracteres ASCII basicos)
int contarEspeciales(const char t[]){
    int cont = 0;
    for(int i = 0; t[i] != '\0'; i++){
        unsigned char c = (unsigned char)t[i];
        if(c < 128 && !isalnum(c) && !isspace(c)){
            cont++;
        }
    }
    return cont;
}

int contarPalabras(const char t[]){
    int cont = 0;
    bool enPalabra = false;
    for(int i = 0; t[i] != '\0'; i++){
        if(isspace((unsigned char)t[i])){
            enPalabra = false;
        }else if(!enPalabra){
            enPalabra = true;
            cont++;
        }
    }
    return cont;
}

//=============== EDITAR TEXTO ===============//

void aMayusculas(char t[]){
    for(int i = 0; t[i] != '\0'; i++){
        t[i] = toupper((unsigned char)t[i]);
    }
}

void aMinusculas(char t[]){
    for(int i = 0; t[i] != '\0'; i++){
        t[i] = tolower((unsigned char)t[i]);
    }
}

// Cuenta cada oracion segun su signo final. "..." o "?!" cuentan como una sola.
// Si el texto no termina en signo, el ultimo fragmento se toma como declarativo.
void tipoOracion(const char t[], int &declarativas, int &interrogativas, int &exclamativas){
    declarativas = 0;
    interrogativas = 0;
    exclamativas = 0;
    int ultimo = -1;   // posicion del ultimo caracter que no es espacio
    for(int i = 0; t[i] != '\0'; i++){
        char c = t[i];
        if(c == '.' || c == '?' || c == '!'){
            char sig = t[i+1];
            if(sig == '.' || sig == '?' || sig == '!'){
                continue;   // todavia hay mas signos seguidos, se cuenta el ultimo
            }
            if(c == '?'){
                interrogativas++;
            }else if(c == '!'){
                exclamativas++;
            }else{
                declarativas++;
            }
        }
        if(!isspace((unsigned char)c)){
            ultimo = i;
        }
    }
    if(ultimo != -1){
        char u = t[ultimo];
        if(u != '.' && u != '?' && u != '!'){
            declarativas++;
        }
    }
}

// Primera letra de cada palabra en mayuscula (el resto del texto no se toca)
void primeraMayuscula(char t[]){
    bool inicio = true;
    for(int i = 0; t[i] != '\0'; i++){
        if(isspace((unsigned char)t[i])){
            inicio = true;
        }else if(inicio){
            t[i] = toupper((unsigned char)t[i]);
            inicio = false;
        }
    }
}

// Muestra el texto con color ANSI: 1 rojo, 2 verde, 3 amarillo, 4 azul, 5 magenta, 6 cian, 7 blanco
void asignarColor(const char t[], int color){
    cout << "\033[" << 30 + color << "m" << t << "\033[0m" << endl;
}

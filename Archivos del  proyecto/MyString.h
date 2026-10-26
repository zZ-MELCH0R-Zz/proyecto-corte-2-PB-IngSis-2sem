#pragma once

// Libreria MyString, una funcion por cada proceso del editor My WP

//----- Analizar texto -----
int totalCaracteres(const char t[]);   // A
int contarVocales(const char t[]);     // B
int contarNumeros(const char t[]);     // C
int contarEspacios(const char t[]);    // D
int contarEspeciales(const char t[]);  // E
int contarPalabras(const char t[]);    // F

//----- Editar texto -----
void aMayusculas(char t[]);            // A
void aMinusculas(char t[]);            // B
void tipoOracion(const char t[], int &declarativas, int &interrogativas, int &exclamativas); // C
void primeraMayuscula(char t[]);       // D
void asignarColor(const char t[], int color);  // E (color de 1 a 7)



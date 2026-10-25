#pragma once

#include <iostream>
#include <locale.h>
using namespace std;
// TODO LO QUE DIGA CONST CHAR VARIABLE[], lo que hace es que al llamar una funcion con esto, se le pasa un mensaje que luego ella imprimira


//=================== CAPACIDADES =================//
const int MAX_AUTORES = 2;
const int MAX_PUBLICACIONES = 200;

//=================== ESTRUCTURAS =================//
struct autor {
    long long idAutor;
    char nom[50];
    char email[60];
    char programa[60];
};

struct publicacion{
    long long idPubli;
    long long idAutor;   // enlaza la publicacion con su autor
    char autor[50];      // nombre del autor (se copia solo desde el arreglo de autores)
    char titulo[100];
    char tipoP[100];
    int anio;
    char premio[200];
    char abstract[500];
    int baseP;
    int adicP;
};

//=============== FUNCIONES ==============//
int menu(void);
void presentacion(void);
int cad_l(const char texto[]);
void cad_cpy(char destino[], const char origen[]);
double leer(bool esNumero, const char mensaje[], double minimo, double maximo, char texto[]=0);
void mostrar_error_en(const char mensaje[], const char error[]);

//=============== AUXILIARES ==============//
char leerLetra(const char mensaje[], char primera, char ultima);
int elegirOpcion(const char encabezado[], const char opciones[][60], int cantidad);
static int cad_cmp(const char a[], const char b[]);
static void imprimirFijo(const char t[], int ancho);


//=============== BUSQUEDAS / VALIDACIONES ==============//
int buscarAutor(long long id, const autor autores[], int nAutores);   // devuelve la posicion o -1
bool existeIdPublicacion(long long id, const publicacion publicaciones[], int nPublicaciones);

//=============== REGISTRO ==============//
void registrarAutores(autor autores[], int &nAutores);
void registrarPublicaciones(publicacion publicaciones[], int &nPublicaciones, const autor autores[], int nAutores);
void tipoPublicacion(publicacion &nueva);
void premioPublicacion(publicacion &nueva);
void mostrarPuntos(const publicacion &p);

//=============== EDITOR My WP ==============//
void editarAbstract(publicacion &nueva);
void analizarTexto(const char texto[]);
void editarTexto(char texto[]);


//===== PUBLISOFT EDITOR ======//
// Editor de texto, hecho solo con char[] y algoritmos propios.
//   texto: arreglo que se edita (se modifica en el mismo arreglo)
//   tam:   tamano total del arreglo (incluye el '\0'); ej. sizeof(nueva.abstract)
// Devuelve true si el texto quedo distinto al que tenia al abrir el editor.
bool PUBLISOFT_EDITOR(char texto[], int tam);

//=============== PENDIENTES ==============//
void actualizarDatos(autor autores[], int nAutores, publicacion publicaciones[], int nPublicaciones);
void reportes(const autor autores[], int nAutores, const publicacion publicaciones[], int nPublicaciones);
void estadisticas(const autor autores[], int nAutores, const publicacion publicaciones[], int nPublicaciones);



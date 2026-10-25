#pragma once

#include <iostream>
#include <locale.h>
using namespace std;

//=================== CAPACIDADES =================//
// Cuantos autores y publicaciones caben en el programa. Cambia estos numeros cuando quieras:
// se usan en TODO el codigo, no hay que tocar nada mas.
const int MAX_AUTORES = 100;
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
    long long idAutor;   // NUEVO: enlaza la publicacion con su autor
    char autor[50];      // nombre del autor (se copia solo desde el arreglo de autores)
    char titulo[100];
    char tipoP[100];
    int anio;
    char premio[200];
    char abstract[500];
    int baseP;
    int adicP;
};

//=============== TUS FUNCIONES (utilidades) ==============//
int menu(void);
void presentacion(void);
int cad_l(const char texto[]);
void cad_cpy(char destino[], const char origen[]);
double leer(bool esNumero, const char mensaje[], double minimo, double maximo, char texto[]=0);
void mostrar_error_en(const char mensaje[], const char error[]);

//=============== AUXILIARES NUEVAS ==============//
char leerLetra(const char mensaje[], char primera, char ultima);
int elegirOpcion(const char encabezado[], const char opciones[][60], int cantidad);

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

//=============== PENDIENTES ==============//
void actualizarDatos(autor autores[], int nAutores, publicacion publicaciones[], int nPublicaciones);
void reportes(const autor autores[], int nAutores, const publicacion publicaciones[], int nPublicaciones);
void estadisticas(const autor autores[], int nAutores, const publicacion publicaciones[], int nPublicaciones);



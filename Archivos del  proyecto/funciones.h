#pragma once
#include <iostream>
#include <vector>
#include <locale.h>
using namespace std;

struct autor {
    long long idAutor;
    char nom[50];
    char email[60];
    char programa[60];
};

struct publicacion{
    long idPubli;
    char autor[50];
    char titulo[100];
    char tipoP[100];
    int anio;
    char premio[200];
    char abstract[500];
    int baseP;
    int adicP;
};


int menu(void);
void presentacion(void);
int cad_l(const char texto[]);
void cad_cpy(char destino[], const char origen[]);
double leer(bool esNumero, const char mensaje[], double minimo, double maximo, char texto[]=0);
void registrarAutores(vector<autor> &autores);
int validarIdAutor(long long idAux, vector<autor> &autores, int n );
int validarIdPublicaciones(long long idAux, vector<publicacion> &publicaciones, int n );
int validarNombreAutor(char nomAux[50], vector<autor> &autores, int n );
void registrarPublicaciones(vector<publicacion> &publicaciones,  vector<autor> &autores);
void tipoPublicacion(publicacion &nueva, int &i);
void premioPublicacion(publicacion &nueva, int &i);
void editarAbstract(publicacion &nueva);
void analizarTexto(publicacion &nueva);
void puntos();
void actualizarDatos();
void reportes();
void estadisticas();

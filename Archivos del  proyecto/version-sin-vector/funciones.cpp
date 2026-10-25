#include "funciones.h"
#include "MyString.h"
#include "MyEditor.h"
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <iomanip>
using namespace std;

const double MAX_ID = 9999999999.0;   // documento de hasta 10 digitos

//=============== TABLAS DE TIPOS Y PREMIOS ===============//

static const char TIPOS[5][60] = {
    "Publicacion en revista internacional indexada",
    "Publicacion en revista nacional",
    "Ponencia en congreso internacional",
    "Ponencia en congreso nacional",
    "Articulo en boletin o revista estudiantil"
};
static const int PUNTOS_BASE[5] = {10, 7, 5, 3, 1};

static const char PREMIOS[4][60] = {
    "Primer lugar o mejor ponencia internacional",
    "Segundo o tercer lugar en ponencia internacional",
    "Premio nacional o mencion especial",
    "Sin premio o reconocimiento"
};
static const int PUNTOS_ADIC[4] = {5, 3, 2, 0};

static const char COLORES[7][60] = {
    "Rojo", "Verde", "Amarillo", "Azul", "Magenta", "Cian", "Blanco"
};

//===== DEFINICIONES DE FUNCIONES ====//

void presentacion(void){
	
    //Espaciado del logo.
    for (int i = 0; i < 7; i++) {
        cout << endl;
    }

    //Matriz que almacena el logo para ser mostrado posteriormente.
    char logo[10][70] = {
        " ____   _   _  ____   _      ___    ____    ___   _____  _____ ",
        "|  _ \\ | | | || __ ) | |    |_ _|  / ___|  / _ \\ |  ___||_   _|",
        "| |_) || | | ||  _ \\ | |     | |   \\___ \\ | | | || |_     | |  ",
        "|  __/ | |_| || |_) || |___  | |    ___) || |_| ||  _|    | |  ",
        "|_|     \\___/ |____/ |_____||___|  |____/  \\___/ |_|      |_|  ",
        "                                           ",
        "                                           ",
        "                                           ",
        "                                           ",
        "                                           "
    };

    //Impresion del logo.
    int alineador = 15;
    
    for (int i = 0; i < 9; i++) {
        cout << setw(alineador) << "" << logo[i] << endl;
    }

    cout << endl << endl;
    Sleep(2000);
    
    system("cls");
    
    for (int i = 0; i < 7; i++) {
        cout << endl;
    }
    
    for (int i = 0; i < 10; i++) {
    	switch(i){
    		case 6: cout<<setw(alineador+44)<<"UNIVERSIDAD DE CARTAGENA\n"; break;
    		case 7: cout<<setw(alineador+42)<<"Facultad de Ingenieria"; break;
			case 9: cout<<setw(alineador+40)<<"CORTE 2 - PROYECTO"; break;
			default: cout << setw(alineador) << "" << logo[i] << endl;
		}
    }
    Sleep(2000);
    system("cls");
    Sleep(1800);
    
    for (int i = 0; i < 12; i++) {
        cout << endl;
    }

    
    int alineador_barra = alineador;
    //Barra de carga.
    char barra[18];
    barra[10]=' ';
    barra[11]=' ';
    barra[12]=' ';
    barra[16]='%';
    barra[17]='\0';
    

		cout << setw(alineador_barra) << "";
        cout << "\x1b""7";
	    for(int porcentaje = 0; porcentaje <= 100; porcentaje++){
	        int carga = porcentaje / 10;
	        for(int i = 0; i < 10; i++){
	            if(i < carga){
	                barra[i] = '#';
	            }else{
	                barra[i] = '-';
	            }
	        }
	        barra[10] = '\0';
	
	        // '\0338' regresa al inicio de la linea y todo se sobrescribe en la misma fila
	        cout << "\0338" << setw(alineador_barra) << "[" << barra << "] "<< setw(3) << porcentaje << "%";
    	         
    	         if (porcentaje < 100){
    	         	cout<<"  Cargando...";
				 }else{
				 	cout<<"  Listo!     ";
				 }
    	         cout<< flush;
	
    	    Sleep(5);
    	}
		
    	Sleep(400);
    	
}//presentacion


int cad_l(const char texto[]){
	int i = 0;
	while(texto[i] != '\0'){
		i++;
	}
	return i;
}//largo de cadena de caracteres

void cad_cpy(char destino[], const char origen[]){
	int i = 0;
	while (origen[i] != '\0'){
		destino[i] = origen[i];
		i++;
	}
	destino[i] = '\0';
}//copiar cadenas

static bool textoANumero(const char t[], double &resultado){
	int i = 0;
		while (t[i] == ' '){
			i++; 
		}                      // espacios al inicio
		bool negativo = false;
		if (t[i] == '-'){
			negativo = true;
			i++;
		}else if (t[i] == '+'){
			i++;
		}

		double valor = 0;	
		int digitos = 0;
		while (t[i] >= '0' && t[i] <= '9'){              // parte entera: valor = valor*10 + digito
			valor = valor * 10 + (t[i] - '0');
			digitos++;
			i++;
		}
		if (t[i] == '.' || t[i] == ','){                 // parte decimal (acepta punto o coma)
			i++;
			double factor = 0.1;
			while (t[i] >= '0' && t[i] <= '9'){
				valor = valor + (t[i] - '0') * factor;
				factor = factor / 10;
				digitos++;
					i++;
			}
		}
		while (t[i] == ' '){ i++; }                      // espacios al final
			if (digitos == 0 || t[i] != '\0'){               // no hubo numero, o sobraron caracteres
				return false;
			}
		if(negativo){
			resultado = -valor;
		}else{
			resultado = valor;
		}
		return true;
}

void mostrar_error_en(const char mensaje[], const char error[]){
	int columna = cad_l(mensaje) + 1;
	cout << "\033[1A\033["<<columna<<"G";
	cout << "\033[J <ERROR, " << error << ">";
	getch();
	cout<<"\r\033[2K";
}


//==================  validar entrada =====================//
double leer(bool esNumero, const char mensaje[], double minimo, double maximo, char texto[]){
	char linea[128];
	while (true){
		cout << "\033[?25h" << mensaje;
		bool vacio = false;
		bool largo = false;
		if (!esNumero){
			cin.getline(texto, (int)maximo + 1);
			if (cin.fail()){
				largo = !cin.eof();
				cin.clear();
				cin.ignore(10000, '\n');
				vacio = !largo;
			}else if (cad_l(texto) > 0){
				return 0;
			}else{
				vacio = true;
			}
		}else{
			cin.getline(linea, 128);          // el numero tambien se lee como una linea completa
			if (cin.fail()){
				cin.clear();
				cin.ignore(10000, '\n');
			}else if (cad_l(linea) == 0){
				vacio = true;
			}else{
				double x = 0;
				if (textoANumero(linea, x) && x >= minimo && x <= maximo){
					return x;
				}
			}
		}

		if (largo){
			mostrar_error_en(mensaje, "Dato demasiado largo");
		}else if (vacio){
			mostrar_error_en(mensaje, "Dato Vacio");
		}else{
			mostrar_error_en(mensaje, "Dato invalido o fuera de rango");
		}
	}
}

int menu(void){
	int opc=0;
	    cout<<"\033[?25l";
		system("cls");
		cout<<"==========================================="<<endl;
		cout<<"                 PUBLISOFT                 "<<endl;
		cout<<"==========================================="<<endl;
		cout<<"   1. Registro de autores                  "<<endl;
		cout<<"   2. Registro de publicaciones            "<<endl;
		cout<<"   3. Asignacion y actualizacion de puntos "<<endl;
		cout<<"   4. Reportes y Consultas                 "<<endl;
		cout<<"   5. Estadisticas                         "<<endl;
		cout<<"   6. Regresar al inicio                   "<<endl;
		cout<<"\n";
		cout<<"\033[?25h";
		opc = (int)leer(true, "      OPCION -->", 1, 6);   // antes (1, 5): la opcion 6 nunca pasaba
		
		return opc;
	
}

//=============== AUXILIARES ===============//

// Pide UNA letra entre primera y ultima (acepta minusculas) y repite si no es valida.
char leerLetra(const char mensaje[], char primera, char ultima){
    char op[10];
    while(true){
        leer(false, mensaje, 0, 9, op);
        if (cad_l(op) == 1){
    	    char l = toupper((unsigned char)op[0]);
    	    if(l >= primera && l <= ultima){
    	        return l;
    	    }	
		}
        
        mostrar_error_en(mensaje, "Opcion invalida");
    }
}

// Muestra un menu numerado desde un arreglo de textos y devuelve la posicion elegida (0, 1, 2...).
int elegirOpcion(const char encabezado[], const char opciones[][60], int cantidad){
    cout << encabezado << endl;
    for(int i = 0; i < cantidad; i++){
        cout << "   " << i + 1 << ". " << opciones[i] << endl;
    }
    return (int)leer(true, "   Opcion --> ", 1, cantidad) - 1;
}

static bool tieneArroba(const char t[]){
    for(int i = 0; t[i] != '\0'; i++){
        if(t[i] == '@'){
            return true;
        }
    }
    return false;
}

//=============== BUSQUEDAS / VALIDACIONES ===============//

int buscarAutor(long long id, const autor autores[], int nAutores){
    for(int i = 0; i < nAutores; i++){
        if(autores[i].idAutor == id){
            return i;
        }
    }
    return -1;
}

bool existeIdPublicacion(long long id, const publicacion publicaciones[], int nPublicaciones){
    for(int i = 0; i < nPublicaciones; i++){
        if(publicaciones[i].idPubli == id){
            return true;
        }
    }
    return false;
}

//=============== REGISTRO DE AUTORES ===============//

void registrarAutores(autor autores[], int &nAutores){
	cout << "\x1b""[?25l";
    int libres = MAX_AUTORES - nAutores;
    if(libres == 0){
        cout << "Capacidad llena: ya hay " << MAX_AUTORES << " autores registrados." << endl;
        cout << "Presione una tecla para volver al menu ";
        getch();
        return;
    }
	
    int n = (int)leer(true, "Cuantos autores desea registrar: ", 1, libres);
    for(int i = 0; i < n; i++){
        autor nuevo{};
        cout << endl << "--- AUTOR #" << nAutores + 1 << " ---" << endl;

        while(true){
            long long id = (long long)leer(true, " - ID (documento): ", 1, MAX_ID);
            if(buscarAutor(id, autores, nAutores) == -1){
                nuevo.idAutor = id;
                break;
            }
            mostrar_error_en(" - ID (documento): ", "ID ya registrado");
        }

        leer(false, " - Nombre completo: ", 0, 49, nuevo.nom);

        while(true){
            leer(false, " - Correo: ", 0, 59, nuevo.email);
            if(tieneArroba(nuevo.email)){
                break;
            }
            mostrar_error_en(" - Correo: ", "Correo invalido (falta @)");
        }

        leer(false, " - Programa: ", 0, 59, nuevo.programa);
        autores[nAutores++] = nuevo;
    }
    cout << endl << "Autores registrados en total: " << nAutores << endl;
    cout << "Presione una tecla para volver al menu ";
    getch();
}

//=============== REGISTRO DE PUBLICACIONES ===============//

// Elige el tipo y deja listos el texto y los puntos base (con "=", no "+=": sirve tambien al actualizar)
void tipoPublicacion(publicacion &nueva){
    int op = elegirOpcion("Tipo de publicacion:", TIPOS, 5);
    cad_cpy(nueva.tipoP, TIPOS[op]);
    nueva.baseP = PUNTOS_BASE[op];
}

// Elige el premio y deja listos el texto ("Ninguno" si no hay) y los puntos adicionales
void premioPublicacion(publicacion &nueva){
    int op = elegirOpcion("Premio o reconocimiento:", PREMIOS, 4);
    if(op == 3){
        cad_cpy(nueva.premio, "Ninguno");
    }else{
        cad_cpy(nueva.premio, PREMIOS[op]);
    }
    nueva.adicP = PUNTOS_ADIC[op];
}

void mostrarPuntos(const publicacion &p){
    cout << "   Puntos base:        " << p.baseP << endl;
    cout << "   Puntos adicionales: " << p.adicP << endl;
    cout << "   Total de puntos:    " << p.baseP + p.adicP << endl;
}

void registrarPublicaciones(publicacion publicaciones[], int &nPublicaciones, const autor autores[], int nAutores){
	
    if(nAutores == 0){
        cout << "Debe registrar al menos un autor primero." << endl;
        cout << "Presione una tecla para volver al menu ";
        getch();
        return;
    }

    int libres = MAX_PUBLICACIONES - nPublicaciones;
    if(libres == 0){
        cout << "Capacidad llena: ya hay " << MAX_PUBLICACIONES << " publicaciones registradas." << endl;
        cout << "Presione una tecla para volver al menu ";
        getch();
        return;
    }

    time_t ahora = time(0);
    int anioActual = localtime(&ahora)->tm_year + 1900;
    cout<<"\033[?25l";
    int n = (int)leer(true, "Cuantas publicaciones desea registrar: ", 1, libres);
    for(int i = 0; i < n; i++){
        publicacion nueva{};
        system("cls");
        cout << "--- PUBLICACION #" << nPublicaciones + 1 << " ---" << endl;

        // El autor debe existir. Se pide el ID y el nombre se copia solo.
        int pos;
        while(true){
            long long idA = (long long)leer(true, " - ID del autor: ", 1, MAX_ID);
            pos = buscarAutor(idA, autores, nAutores);
            if(pos != -1){
                break;
            }
            mostrar_error_en(" - ID del autor: ", "Autor no registrado");
        }
        nueva.idAutor = autores[pos].idAutor;
        cad_cpy(nueva.autor, autores[pos].nom);
        cout << "   Autor: " << nueva.autor << endl;

        // El ID de la publicacion no se puede repetir.
        while(true){
            long long idP = (long long)leer(true, " - ID de la publicacion: ", 1, MAX_ID);
            if(!existeIdPublicacion(idP, publicaciones, nPublicaciones)){
                nueva.idPubli = idP;
                break;
            }
            mostrar_error_en(" - ID de la publicacion: ", "ID ya registrado");
        }

        leer(false, " - Titulo: ", 0, 99, nueva.titulo);
        nueva.anio = (int)leer(true, " - Anio de publicacion: ", 1900, anioActual);
        cout << endl;
        tipoPublicacion(nueva);
        cout << endl;
        premioPublicacion(nueva);

        cout << endl << "Puntos asignados:" << endl;
        mostrarPuntos(nueva);
        cout << endl;

        leer(false, " - Abstract: ", 0, 499, nueva.abstract);
        editarAbstract(nueva);

        publicaciones[nPublicaciones++] = nueva;
        
        cout<<"\033[?25l";
        system("cls");
        cout << "PUBLICACION REGISTRADA (" << i + 1 << " de " << n << ")" << endl;
        cout << "   Titulo: " << nueva.titulo << endl;
        cout << "   Autor:  " << nueva.autor << endl;
        mostrarPuntos(nueva);
        cout << endl << "Presione una tecla para continuar ";
        getch();
    }
}

//=============== EDITOR My WP ===============//

void editarAbstract(publicacion &nueva){
	cout<<"\033[?25l";
    int quiere = (int)leer(true, "Desea analizar o editar el abstract? (1=Si, 0=No): ", 0, 1);
    if(quiere == 0){
        return;
    }
    while(true){
    	cout<<"\033[?25l";
        system("cls");
        cout << "=========== My WP (Word Processor) ===========" << endl;
        cout << "   1. Analizar texto" << endl;
        cout << "   2. Editar texto" << endl;
        cout << "   3. PUBLISOFT EDITOR  (^X para salir)" << endl;
        cout << "   4. Salir" << endl;
        int op = (int)leer(true, "   Opcion --> ", 1, 4);
        if(op == 1){
            analizarTexto(nueva.abstract);
        }else if(op == 2){
            editarTexto(nueva.abstract);
        }else if(op == 3){
            PUBLISOFT_EDITOR(nueva.abstract, sizeof(nueva.abstract));
        }else{
            return;
        }
    }
}

void analizarTexto(const char texto[]){
    while(true){
        system("cls");
        cout << "=============== Analizar texto ===============" << endl;
        cout << "Abstract: " << texto << endl << endl;
        cout << "   A. Mostrar cantidad total de caracteres" << endl;
        cout << "   B. Contar vocales" << endl;
        cout << "   C. Contar caracteres numericos" << endl;
        cout << "   D. Contar espacios en blanco" << endl;
        cout << "   E. Contar caracteres especiales" << endl;
        cout << "   F. Cantidad de palabras" << endl;
        cout << "   G. Salir" << endl;
        char op = leerLetra("   Opcion --> ", 'A', 'G');
        if(op == 'G'){
            return;
        }
        cout << endl;
        switch(op){
            case 'A': cout << "Total de caracteres: " << totalCaracteres(texto) << endl; break;
            case 'B': cout << "Vocales: " << contarVocales(texto) << endl; break;
            case 'C': cout << "Caracteres numericos: " << contarNumeros(texto) << endl; break;
            case 'D': cout << "Espacios en blanco: " << contarEspacios(texto) << endl; break;
            case 'E': cout << "Caracteres especiales: " << contarEspeciales(texto) << endl; break;
            case 'F': cout << "Palabras: " << contarPalabras(texto) << endl; break;
        }
        cout << endl << "Presione una tecla para continuar ";
        getch();
    }
}

void editarTexto(char texto[]){
    while(true){
        system("cls");
        cout << "================ Editar texto ================" << endl;
        cout << "Abstract: " << texto << endl << endl;
        cout << "   A. Convertir todo el texto a mayusculas" << endl;
        cout << "   B. Convertir todo el texto a minusculas" << endl;
        cout << "   C. Detectar tipo de oracion" << endl;
        cout << "   D. Primera letra de cada palabra en mayuscula" << endl;
        cout << "   E. Asignar color" << endl;
        cout << "   F. Salir" << endl;
        char op = leerLetra("   Opcion --> ", 'A', 'F');
        if(op == 'F'){
            return;
        }
        cout << endl;
        switch(op){
            case 'A':
                aMayusculas(texto);
                cout << "Listo: " << texto << endl;
                break;
            case 'B':
                aMinusculas(texto);
                cout << "Listo: " << texto << endl;
                break;
            case 'C': {
                int decl, interr, excl;
                tipoOracion(texto, decl, interr, excl);
                cout << "Oraciones declarativas:   " << decl << endl;
                cout << "Oraciones interrogativas: " << interr << endl;
                cout << "Oraciones exclamativas:   " << excl << endl;
                break;
            }
            case 'D':
                primeraMayuscula(texto);
                cout << "Listo: " << texto << endl;
                break;
            case 'E': {
                int color = elegirOpcion("Color del texto:", COLORES, 7) + 1;
                cout << endl;
                asignarColor(texto, color);
                break;
            }
        }
        cout << endl << "Presione una tecla para continuar ";
        getch();
    }
}

//=============== PENDIENTES ===============//

void actualizarDatos(autor autores[], int nAutores, publicacion publicaciones[], int nPublicaciones){
    
    while(true){
        system("cls");
        cout << "Que informacion desea actualizar: \n";
        cout << "   1. Autor\n";
        cout << "   2. Publicacion\n";
        cout << "   3. Salir\n";
        int opc = (int)leer(true, "   Opcion --> ", 1, 3);

        if(opc == 1){
            long long id = (long long)leer(true, "Ingrese el ID del autor: ", 1, MAX_ID);
            int pos = buscarAutor(id, autores, nAutores);

            if(pos != -1){
                cout << "\nAutor encontrado..." << endl;
                cout << "ID: " << autores[pos].idAutor << endl;
                cout << "Nombre: " << autores[pos].nom << endl;
                cout << "Correo: " << autores[pos].email << endl;
                cout << "Programa: " << autores[pos].programa << endl;

                // Mostrar datos y preguntar si desea modificar[cite: 3]
                int mod = (int)leer(true, "\nDesea modificar la informacion registrada? (1=Si, 0=No): ", 0, 1);
                if(mod == 1){
                    system("cls");
                    cout << "Cual dato desea cambiar?\n";
                    cout << "1. Nombre\n2. Correo\n3. Programa\n";
                    int campo = (int)leer(true, "Opcion --> ", 1, 3);

                    if(campo == 1){
                        leer(false, "Ingrese nuevo nombre: ", 0, 49, autores[pos].nom);
                    }else if(campo == 2){
                        while(true){
                            leer(false, "Ingrese nuevo correo: ", 0, 59, autores[pos].email);
                            if(tieneArroba(autores[pos].email)) break;
                            mostrar_error_en(" - Nuevo Correo: ", "Correo invalido (falta @)");
                        }
                    }else if(campo == 3){
                        leer(false, "Ingrese nuevo programa: ", 0, 59, autores[pos].programa);
                    }
                    cout << "\nAutor actualizado con exito.\n";
                    getch();
                }
            }else{
                mostrar_error_en("ID Autor: ", "Autor no encontrado");
            }
        }
        else if(opc == 2){
            long long id = (long long)leer(true, "Ingrese el ID de la publicacion a actualizar: ", 1, MAX_ID);
            int pos = -1;
            for(int i = 0; i < nPublicaciones; i++){
                if(publicaciones[i].idPubli == id) { pos = i; break; }
            }

            if(pos != -1){
                cout << "\nPublicacion encontrada..." << endl;
                cout << "ID: " << publicaciones[pos].idPubli << endl;
                cout << "Titulo: " << publicaciones[pos].titulo << endl;
                cout << "Tipo: " << publicaciones[pos].tipoP << endl;
                cout << "Ano: " << publicaciones[pos].anio << endl;
                cout << "Premio: " << publicaciones[pos].premio << endl;
                mostrarPuntos(publicaciones[pos]);

                int mod = (int)leer(true, "\nDesea actualizar algun dato? (1=Si, 0=No): ", 0, 1);
                if(mod == 1){
                    system("cls");
                    cout << "Cual de los siguientes desea cambiar?\n";
                    cout << "1. Titulo\n2. Tipo de publicacion\n3. Ano de publicacion\n4. Premio\n5. Abstract\n";
                    int campo = (int)leer(true, "Opcion --> ", 1, 5);

                    if(campo == 1){
                        leer(false, "Ingrese nuevo titulo: ", 0, 99, publicaciones[pos].titulo);
                    }else if(campo == 2){
                        tipoPublicacion(publicaciones[pos]); // Recalcula puntos base automáticamente[cite: 3, 4]
                        cout << "\nPuntos base recalculados con exito.\n";
                    }else if(campo == 3){
                        time_t ahora = time(0);
                        int anioActual = localtime(&ahora)->tm_year + 1900;
                        publicaciones[pos].anio = (int)leer(true, "Ingrese nuevo ano: ", 1900, anioActual);
                    }else if(campo == 4){
                        premioPublicacion(publicaciones[pos]); // Recalcula puntos adicionales automáticamente[cite: 3, 4]
                        cout << "\nPuntos adicionales recalculados con exito.\n";
                    }else if(campo == 5){
                        leer(false, "Ingrese nuevo abstract: ", 0, 499, publicaciones[pos].abstract);
                        editarAbstract(publicaciones[pos]);
                    }
                    cout << "\nPublicacion actualizada con exito.\n";
                    getch();
                }
            }else{
                mostrar_error_en("ID Publicacion: ", "Publicacion no encontrada");
            }
        }
        else if(opc == 3){
            break;
        }
    }
}





void reportes(const autor autores[], int nAutores, const publicacion publicaciones[], int nPublicaciones){
    while(true){
    	system("cls");
		cout<<"1. Consultar Autor\n";
		cout<<"2. Consultar una Publicacion\n";
		cout<<"3. Listado de Autores y sus Publicaciones\n";
		cout<<"4. Salir\n";
		int opc = (int)leer(true, "   Opcion --> ", 1, 3);
		if(opc == 1){
			long long id = (long long)leer(true, "Ingrese el ID del autor: ", 1, MAX_ID);
            int pos = buscarAutor(id, autores, nAutores);

            if(pos != -1){
            	cout<<"Publicaciones: "<<endl;
				cout<<"Titulo "<<setw(15)<<"Tipo "<<setw(15)<<"Premio "<<setw(15)<<"puntaje Base "
				<<setw(15)<<"Puntajes Adicionales "<<setw(15)<<"Puntajes Totales ";
				cout<<endl;
				cout<<"==================================================================================";
				for(int i=0;i<nPublicaciones;i++){
					cout<<publicaciones[i].titulo<<setw(15)<<publicaciones[i].tipoP
					<<setw(15)<<publicaciones[i].premio<<setw(15)<<publicaciones[i].baseP
					<<setw(15)<<publicaciones[i].adicP<<setw(15)
					<<autores[i].publicaciones[a.baseP + publicaciones[a].adicP;
					cout<<endl;
					cout<<"===================================================================";
					cout<<endl;
				}
			}
			else{
				cout<<"Autor no encontrado!!\n";
				break;
			}
		}
		else if(opc == 2){
			long long id = (long long)leer(true, "Ingrese el ID de la publicacion: ", 1, MAX_ID);
            int pos = buscarAutor(id, autores, nAutores);
            if(pos != -1){
            	cout<<"Autor "<<setw(15)<<"Programa "<<setw(15)<<"cant. P. Obtenidos "<<setw(15)
				<<"Id Publicacion "<<setw(15)<<"Titulo "<<setw(15)<<"Tipo "<<setw(15)<<"Premio "<<setw(15)<<"puntaje Base "
				<<setw(15)<<"Puntajes Adicionales ";
				cout<<endl;
				for(int i=0;i<nPublicaciones;i++){
					if(id == autores[i].idAutor){
						cout<<autores[i].nom<<setw(15)<<autores[i].programa;
					}
					if(id == publicaciones[i].idAutor){
						cout<<publicaciones[i].baseP + publicaciones[i].adicP<<setw(15)<<publicaciones[i].titulo<<setw(15)<<publicaciones[i].tipoP
						<<setw(15)<<publicaciones[i].premio<<setw(15)<<publicaciones[i].baseP
						<<setw(15)<<publicaciones[i].adicP<<setw(15);
					}
				}
			}
		}
		else if(opc == 3){
			cout<<"Listado General "<<endl;
			cout<<"Autor"<<setw(15)<<"Publicacion"<<setw(15)<<"puntaje total"<<setw(15)<<"tipo de publicacion"<<setw(15)<<"puntaje total"<<setw(15)<<"premio"<<setw(15)<<"puntaje base"<<setw(15)<<"puntaje adicional";
			cout<<endl;
			for(int i=0;i<nPublicaciones;i++){
				
				cout<<publicasiones[i].nom<<setw(15)<<publicasiones[i].titulo<<setw(15)<<publicaciones[i].baseP + autor[i].publi[a].adicP<<
				<<setw(15)<<publicaciones[i].tipoP
				<<setw(15)<<publicaciones[i].premio<<setw(15)<<publicaciones[i].baseP
						<<setw(15)<<publicaciones[i].adicP;
				cout<<endl;
				cout<<"=========================================================";
				cout<<endl;
				
			}
		}
	}
    getch();
}
void estadisticas(const autor autores[], int nAutores, const publicacion publicaciones[], int nPublicaciones){
    cout << "En construccion..." << endl;
    getch();
}

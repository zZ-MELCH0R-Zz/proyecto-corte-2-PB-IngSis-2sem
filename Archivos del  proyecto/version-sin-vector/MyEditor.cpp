#include "funciones.h"      // usa tus cad_l y cad_cpy
#include <ctype.h>
#include <windows.h>
#include <conio.h>
using namespace std;

/*
  ------| COMO FUNCIONA |------
  
  1. El texto vive en UN solo arreglo de char, con '\n' como separador de lineas.
  2. El cursor es un numero: la posicion es un indice dentro de ese arreglo.
  3. De ese indice se calculan todo lo demas, como en que linea y columna esta,
     donde empieza y termina su linea, etc. Nada se guarda duplicado.
  4. Insertar/borrar = desplazar los caracteres de la cola una posicion.
  5. Cada vuelta: ajustar la vista (scroll), dibujar el cuadro completo con
     secuencias ANSI, esperar UNA tecla con getch() y ejecutar su accion.
*/

//=============== CONSTANTES Y ESTADO ===============//
static const int MAX_TXT = 4096;   // capacidad maxima que maneja el editor
static int ANCHO = 80;             // columnas de la consola (se mide al abrir)
static int ALTO  = 24;             // filas de la consola

struct Editor{
    char *t;                 // el texto que se edita (el arreglo de quien llama)
    int cap;                 // capacidad del arreglo (incluye el '\0')
    int len;                 // cantidad de caracteres actuales
    int cur;                 // posicion del cursor: indice dentro de t
    int colMeta;             // columna "deseada" al subir y bajar de linea
    int top;                 // primera linea visible (scroll vertical)
    int left;                // primera columna visible (scroll horizontal)
    bool modificado;         // hay cambios sin guardar
    char guardado[MAX_TXT];  // ultima version guardada con Ctrl+O
    char porta[MAX_TXT];     // portapapeles (Ctrl+K / Ctrl+U)
    int lenPorta;
    char msg[120];           // mensaje de la barra de estado
};

static const char ATAJO_TECLA[10][4] = {"^G","^O","^W","^K","^Y","^X","^U","^A","^E","^V"};
static const char ATAJO_TEXTO[10][12] = {"Ayuda","Guardar","Buscar","Cortar","Pag Ant",
                                         "Salir","Pegar","Inicio","Fin","Pag Sig"};

//=============== UTILIDADES DE TEXTO ===============//
static void cad_cat(char destino[], const char origen[]){
    cad_cpy(destino + cad_l(destino), origen);
}

static void numAStr(int n, char out[]){ //escribir un numero como caracter
    char tmp[12];
    int k = 0;
    if(n == 0){ tmp[k++] = '0'; }
    while(n > 0){
        tmp[k++] = (char)('0' + n % 10);
        n = n / 10;
    }
    int j = 0;
    while(k > 0){ out[j++] = tmp[--k]; }
    out[j] = '\0';
}

static bool iguales(const char a[], const char b[]){//devuelve si dos caracteres son iguales
    int i = 0;
    while(a[i] != '\0' && a[i] == b[i]){ i++; }
    return a[i] == b[i];
}

static void avisar(Editor &e, const char s[]){
    cad_cpy(e.msg, s);
}

//=============== BUFFER DEL CUADRO (se dibuja todo de una vez) ===============//
static char frame[65536];
static int nf = 0; //numero de filas

static void ponerCar(char c){
    if(nf < 65000){ frame[nf++] = c; }
}
static void ponerTexto(const char s[]){
    for(int i = 0; s[i] != '\0'; i++){ ponerCar(s[i]); }
}
static void ponerNum(int n){//escribir un numero como caracter
    char num[12];
    numAStr(n, num);
    ponerTexto(num);
}
static void irA(int fila, int col){   // posiciona el cursor (1,1 = esquina superior izquierda)
    ponerTexto("\033[");
    ponerNum(fila);
    ponerCar(';');
    ponerNum(col);
    ponerCar('H');
}

//=============== GEOMETRIA, todo sale del indice del cursor ===============//
static int inicioLinea(const Editor &e, int i){
    while(i > 0 && e.t[i-1] != '\n'){ i--; }
    return i;
}
static int finLinea(const Editor &e, int i){
    while(e.t[i] != '\0' && e.t[i] != '\n'){ i++; }
    return i;
}
static int numLinea(const Editor &e, int i){      // linea del indice i, empezando en 0
    int n = 0;
    for(int k = 0; k < i; k++){
        if(e.t[k] == '\n'){ n++; }
    }
    return n;
}
static int totalLineas(const Editor &e){
    return numLinea(e, e.len) + 1;
}

//=============== EDICION, insertar y borrar desplazando la cola ===============//
static bool insertarCar(Editor &e, char c){
    if(e.len >= e.cap - 1){ return false; }       // si no cabe (queda lugar para el '\0')
    for(int i = e.len; i >= e.cur; i--){          // mueve todo (incluido el '\0') una posicion
        e.t[i+1] = e.t[i];
    }
    e.t[e.cur] = c;
    e.cur++;
    e.len++;
    e.modificado = true;
    return true;
}

static void borrarRango(Editor &e, int a, int b){ // borra los indices [a, b)
    int n = b - a;
    if(n <= 0){ return; }
    for(int i = a; i + n <= e.len; i++){          // jala la cola hacia atras (incluye el '\0')
        e.t[i] = e.t[i+n];
    }
    e.len -= n;
    e.modificado = true;
}

//=============== MOVIMIENTO ===============//
static void moverArriba(Editor &e){
    int ini = inicioLinea(e, e.cur);
    if(ini == 0){ return; }                       // ya esta en la primera linea
    int iniPrev = inicioLinea(e, ini - 1);
    int largoPrev = (ini - 1) - iniPrev;
    
    if(e.colMeta < largoPrev){
    	e.cur = iniPrev + e.colMeta;
	}else{
		e.cur = iniPrev + largoPrev;
	}
}

static void moverAbajo(Editor &e){
    int fin = finLinea(e, e.cur);
    if(e.t[fin] == '\0'){ return; }               // ya esta en la ultima linea
    int iniSig = fin + 1;
    int largoSig = finLinea(e, iniSig) - iniSig;
    if(e.colMeta < largoSig){
    	e.cur = iniSig + e.colMeta;
	}else{
		e.cur = iniSig + largoSig;
	}
    
}

static void paginaArriba(Editor &e){
    for(int i = 0; i < ALTO - 5; i++){ 
			moverArriba(e); 
	}
}

static void paginaAbajo(Editor &e){
    for(int i = 0; i < ALTO - 5; i++){ 
		moverAbajo(e);
	}
}

static bool esSep(char c){
 return c == ' ' || c == '\n';
 }

static void palabraAnterior(Editor &e){
    while(e.cur > 0 && esSep(e.t[e.cur-1])){ e.cur--; }
    while(e.cur > 0 && !esSep(e.t[e.cur-1])){ e.cur--; }
}

static void palabraSiguiente(Editor &e){
    while(e.cur < e.len && !esSep(e.t[e.cur])){ e.cur++; }
    while(e.cur < e.len && esSep(e.t[e.cur])){ e.cur++; }
}

//=============== CORTAR, PEGAR, BUSCAR, GUARDAR ===============//
static void cortarLinea(Editor &e, bool seguido){
    int ini = inicioLinea(e, e.cur);
    int fin = finLinea(e, e.cur);
    if(e.t[fin] == '\n'){ fin++; }                // la linea incluye su salto
    int n = fin - ini;
    if(n == 0){ avisar(e, "Nada que cortar"); return; }
    if(!seguido){ e.lenPorta = 0; }               // varios Ctrl+K seguidos se acumulan
    if(e.lenPorta + n < MAX_TXT){
        for(int i = 0; i < n; i++){ e.porta[e.lenPorta + i] = e.t[ini + i]; }
        e.lenPorta += n;
        e.porta[e.lenPorta] = '\0';
    }
    borrarRango(e, ini, fin);
    e.cur = ini;
}

static void pegar(Editor &e){
    if(e.lenPorta == 0){ avisar(e, "Portapapeles vacio"); return; }
    if(e.len + e.lenPorta >= e.cap){ avisar(e, "No hay espacio para pegar"); return; }
    for(int i = e.len; i >= e.cur; i--){          // abre un hueco del tamano del portapapeles
        e.t[i + e.lenPorta] = e.t[i];
    }
    for(int i = 0; i < e.lenPorta; i++){//pega el portapapeles
        e.t[e.cur + i] = e.porta[i];
    }
    e.len += e.lenPorta;
    e.cur += e.lenPorta;
    e.modificado = true;
}

// Busca "pat" sin distinguir mayusculas, desde la posicion "desde" y dando la vuelta al texto.
static int buscarTexto(const Editor &e, const char pat[], int desde){
    int m = cad_l(pat);
    if(m == 0 || e.len == 0){ return -1; }
    for(int paso = 0; paso < e.len; paso++){
        int i = (desde + paso) % e.len;
        if(i + m > e.len){ continue; }
        int k = 0;
        while(k < m && tolower((unsigned char)e.t[i+k]) == tolower((unsigned char)pat[k])){ k++; }
        if(k == m){ return i; }
    }
    return -1;
}

static void guardar(Editor &e){
    cad_cpy(e.guardado, e.t);
    e.modificado = false;
    char num[12];
    cad_cpy(e.msg, "Guardado: ");
    numAStr(totalLineas(e), num);
    cad_cat(e.msg, num);
    cad_cat(e.msg, " linea(s)");
}

//=============== DIBUJO ===============//
static void colocar(char buf[], int pos, const char s[]){
    for(int i = 0; s[i] != '\0'; i++){
        if(pos + i >= 0 && pos + i < ANCHO){ buf[pos + i] = s[i]; }
    }
}

static void barraSuperior(const Editor &e, char buf[]){
    for(int i = 0; i < ANCHO; i++){ buf[i] = ' '; }
    buf[ANCHO] = '\0';
    colocar(buf, 1, "PUBLISOFT Editor");
    if(e.modificado){ colocar(buf, (ANCHO - 10) / 2, "Modificado"); }

    char der[80];
    char num[12];
    cad_cpy(der, "Ln ");
    numAStr(numLinea(e, e.cur) + 1, num);              cad_cat(der, num);
    cad_cat(der, ", Col ");
    numAStr(e.cur - inicioLinea(e, e.cur) + 1, num);   cad_cat(der, num);
    cad_cat(der, "  Car ");
    numAStr(e.len, num);                               cad_cat(der, num);
    cad_cat(der, "/");
    numAStr(e.cap - 1, num);                           cad_cat(der, num);
    colocar(buf, ANCHO - cad_l(der) - 1, der);
}

static void dibujar(const Editor &e){
    int filas = ALTO - 4;                              // filas disponibles para el texto
    nf = 0;
    ponerTexto("\033[?25l");                           // oculta el cursor mientras se dibuja

    // --- barra superior ---
    char buf[256];
    barraSuperior(e, buf);
    irA(1, 1);
    ponerTexto("\033[7m"); //invierte los colores para mostrarlo en blanco
    ponerTexto(buf); 
	ponerTexto("\033[0m");//regresa los colores a la normalidad

    // --- area de texto: solo la ventana [top, top+filas) x [left, left+ANCHO) ---
    int p = 0;                                         // inicio de la linea "top"
    for(int l = 0; l < e.top; l++){ p = finLinea(e, p) + 1; }
    bool hayMas = true;
    for(int r = 0; r < filas; r++){
        irA(2 + r, 1);
        if(hayMas){
            int fin = finLinea(e, p);
            int largo = fin - p;
            int ini = nf;
            for(int c = 0; c < ANCHO && e.left + c < largo; c++){
                ponerCar(e.t[p + e.left + c]);
            }
            if(e.left > 0 && nf > ini){ 
				frame[ini] = '$';     // hay texto oculto a la izquierda
				} 
            if(largo > e.left + ANCHO){ 
				frame[nf - 1] = '$'; // hay texto oculto a la derecha
			}  
            if(e.t[fin] == '\n'){ 
				p = fin + 1; 
			} else { 
				hayMas = false; 
			}
        }
        ponerTexto("\033[K");                          // borra lo que sobre de la fila
    }

    // --- barra de mensajes ---
    irA(ALTO - 2, 1);
    ponerTexto("\033[2K");
    int lm = cad_l(e.msg);//largo mensaje
    if(lm > 0){
        int colMsg = (ANCHO - lm - 4) / 2 + 1;
        if(colMsg < 1){ colMsg = 1; }
        irA(ALTO - 2, colMsg);
        ponerTexto("\033[7m[ "); 
		ponerTexto(e.msg);
		ponerTexto(" ]\033[0m");
    }

    // --- barras de atajos (2 filas x 5 columnas) ---
    int celda = ANCHO / 5;
    for(int f = 0; f < 2; f++){
        irA(ALTO - 1 + f, 1);
        for(int c = 0; c < 5; c++){
            int i = f * 5 + c;
            ponerTexto("\033[7m");
			ponerTexto(ATAJO_TECLA[i]); 
			ponerTexto("\033[0m ");
            ponerTexto(ATAJO_TEXTO[i]);
            for(int u = 3 + cad_l(ATAJO_TEXTO[i]); u < celda; u++){ ponerCar(' '); }
        }
        ponerTexto("\033[K");
    }

    // --- ubica el cursor real donde corresponde y lo muestra ---
    int filaCur = numLinea(e, e.cur) - e.top + 2;
    int colCur = (e.cur - inicioLinea(e, e.cur)) - e.left + 1;
    irA(filaCur, colCur);
    ponerTexto("\033[?25h");

    cout.write(frame, nf);                             // un solo envio a pantalla sin parpadear
    cout.flush();
}

// Scroll: mueve la ventana lo justo para que el cursor quede dentro (con margen horizontal)
static void ajustarVista(Editor &e){
    int filas = ALTO - 4;
    int fila = numLinea(e, e.cur);
    int col = e.cur - inicioLinea(e, e.cur);
    if(fila < e.top){ 
		e.top = fila; 
	}
    if(fila >= e.top + filas){ 
		e.top = fila - filas + 1; 
	}
    if(e.left > 0 && col < e.left + 1){ 
		if(col > 0){
			e.left= col-1;
		}else{
			e.left=0;
		}
	}
		
    if(col >= e.left + ANCHO - 1){ 
		e.left = col - (ANCHO - 2); 
	}
}

//=============== ENTRADA EN LA BARRA INFERIOR ===============//
static bool pedirLinea(const char etiqueta[], char destino[], int max){
    int n = 0;
    destino[0] = '\0';
    while(true){
        cout << "\033[" << ALTO - 2 << ";1H\033[2K\033[7m" << etiqueta << "\033[0m "
             << destino << "\033[?25h" << flush;
        int k = getch();
        if(k == 0 || k == 224){ getch(); continue; }
        if(k == 13){ return true; }
        if(k == 27){ return false; }
        if(k == 8){
            if(n > 0){ destino[--n] = '\0'; }
        }else if(k >= 32 && k != 127 && n < max - 1){
            destino[n++] = (char)k;
            destino[n] = '\0';
        }
    }
}

static int preguntarGuardar(){                         // 1 = guardar, 0 = descartar, -1 = cancelar
    cout << "\033[" << ALTO - 2 << ";1H\033[2K\033[7m"
         << " Guardar cambios? (S=Si, N=No, C=Cancelar) " << "\033[0m" << flush;
    while(true){
        int k = getch();
        if(k == 0 || k == 224){ getch(); continue; }
        k = toupper(k);
        if(k == 'S' || k == 'Y'){ return 1; }
        if(k == 'N'){ return 0; }
        if(k == 'C' || k == 27 || k == 3){ return -1; }
    }
}

static void buscar(Editor &e, char ultima[]){
    char pat[100];
    if(!pedirLinea("Buscar:", pat, 100)){ avisar(e, "Cancelado"); return; }
    if(pat[0] == '\0'){                                // Enter vacio: repite la ultima busqueda
        if(ultima[0] == '\0'){ avisar(e, "Nada que buscar"); return; }
        cad_cpy(pat, ultima);
    }else{
        cad_cpy(ultima, pat);
    }
    int pos = buscarTexto(e, pat, e.cur + 1);
    if(pos == -1){
        avisar(e, "No se encontro");
    }else{
        if(pos <= e.cur){ avisar(e, "Busqueda reiniciada desde el inicio"); }
        e.cur = pos;
    }
}

static void mostrarAyuda(){
    cout << "\033[2J\033[H";
    cout << "  AYUDA DEL EDITOR DE PUBLISOFT\n\n";
    cout << "  (^) ................ este simbolo significa presionar la tecla Ctrl para combinarla con otra tecla\n";
    cout << "  Flechas ............ mover el cursor\n";
    cout << "  Inicio / Fin ....... principio / final de la linea   (tambien ^A / ^E)\n";
    cout << "  Re Pag / Av Pag .... una pantalla arriba / abajo     (tambien ^Y / ^V)\n";
    cout << "  Ctrl + flechas ..... saltar de palabra en palabra\n";
    cout << "  Ctrl + Inicio/Fin .. principio / final del texto\n";
    cout << "  Retroceso / Supr ... borrar a la izquierda / a la derecha\n";
    cout << "  Enter .............. nueva linea\n";
    cout << "  ^K ................. cortar la linea (varios seguidos se acumulan)\n";
    cout << "  ^U ................. pegar lo cortado\n";
    cout << "  ^W ................. buscar (Enter vacio repite la ultima busqueda)\n";
    cout << "  ^O ................. guardar\n";
    cout << "  ^X ................. salir (pregunta si hay cambios sin guardar)\n";
    cout << "\n  Presione una tecla para volver al editor";
    cout << flush;
    getch();
}

static void medirConsola(){
    CONSOLE_SCREEN_BUFFER_INFO info;
    if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info)){
        ANCHO = info.srWindow.Right - info.srWindow.Left + 1;
        ALTO  = info.srWindow.Bottom - info.srWindow.Top + 1;
    }
    if(ANCHO < 60){ ANCHO = 60; }
    if(ANCHO > 200){ ANCHO = 200; }
    if(ALTO < 12){ ALTO = 12; }
    if(ALTO > 60){ ALTO = 60; }
}

//=============== PROGRAMA PRINCIPAL DEL EDITOR ===============//
bool PUBLISOFT_EDITOR(char texto[], int tam){
    medirConsola();

    Editor e;//variable de tipo Editor (salio de la estructura Editor), es para mejor legibilidad y ahorrar tiempo escribiendo cada cosa
    e.t = texto;
    if (tam < MAX_TXT){
    	e.cap = tam;
	}else{
		e.cap = MAX_TXT;
	}
	
    if(e.cap < 2){
		return false; 
	}
    if(cad_l(texto) >= e.cap){
		 texto[e.cap - 1] = '\0'; 
	}
    e.len = cad_l(texto);
    e.cur = 0;
    e.colMeta = 0;
    e.top = 0;
    e.left = 0;
    e.modificado = false;
    e.lenPorta = 0;
    e.porta[0] = '\0';
    e.msg[0] = '\0';
    cad_cpy(e.guardado, texto);

    char inicial[MAX_TXT];                             // para saber al final si hubo cambios
    cad_cpy(inicial, texto);
    char ultimaBusqueda[100];
    ultimaBusqueda[0] = '\0';

    bool corteAnterior = false;                        // la tecla anterior fue Ctrl+K
    bool seguir = true;

    cout << "\033[?1049h";                             // pantalla alterna: al salir, la consola queda como estaba

    while(seguir){
        ajustarVista(e);
        dibujar(e);
        e.msg[0] = '\0';

        int k = getch();
        bool vertical = false;                         // para conservar la columna deseada
        bool esCorte = false;

        if(k == 0 || k == 224){                        // teclas especiales: llegan en dos partes
            int k2 = getch();
            switch(k2){
                case 75: if(e.cur > 0){ e.cur--; } break;                  // izquierda
                case 77: if(e.cur < e.len){ e.cur++; } break;              // derecha
                case 72: moverArriba(e); vertical = true; break;           // arriba
                case 80: moverAbajo(e); vertical = true; break;            // abajo
                case 71: e.cur = inicioLinea(e, e.cur); break;             // Inicio
                case 79: e.cur = finLinea(e, e.cur); break;                // Fin
                case 73: paginaArriba(e); vertical = true; break;          // Re Pag
                case 81: paginaAbajo(e); vertical = true; break;           // Av Pag
                case 83: if(e.cur < e.len){ borrarRango(e, e.cur, e.cur + 1); } break;   // Supr
                case 115: palabraAnterior(e); break;                       // Ctrl + izquierda
                case 116: palabraSiguiente(e); break;                      // Ctrl + derecha
                case 119: e.cur = 0; break;                                // Ctrl + Inicio
                case 117: e.cur = e.len; break;                            // Ctrl + Fin
                default: break;
            }
        }else{
            switch(k){
                case 24:                                                   // ^X salir
                    if(!e.modificado){
                        seguir = false;
                    }else{
                        int r = preguntarGuardar();
                        if(r == 1){
                            seguir = false;                                // conserva lo escrito
                        }else if(r == 0){
                            cad_cpy(e.t, e.guardado);                      // vuelve a la ultima version guardada
                            e.len = cad_l(e.t);
                            seguir = false;
                        }
                    }
                    break;
                case 15: guardar(e); break;                                // ^O
                case 11: cortarLinea(e, corteAnterior); esCorte = true; break;   // ^K
                case 21: pegar(e); break;                                  // ^U
                case 23: buscar(e, ultimaBusqueda); break;                 // ^W
                case 7:  mostrarAyuda(); break;                            // ^G
                case 1:  e.cur = inicioLinea(e, e.cur); break;             // ^A
                case 5:  e.cur = finLinea(e, e.cur); break;                // ^E
                case 25: paginaArriba(e); vertical = true; break;          // ^Y
                case 22: paginaAbajo(e); vertical = true; break;           // ^V
                case 8:                                                    // Retroceso
                    if(e.cur > 0){
                        borrarRango(e, e.cur - 1, e.cur);
                        e.cur--;
                    }
                    break;
                case 13:
                case 10:                                                   // Enter
                    if(!insertarCar(e, '\n')){ avisar(e, "Texto lleno"); }
                    break;
                case 9:                                                    // Tab = 4 espacios
                    for(int i = 0; i < 4; i++){
                        if(!insertarCar(e, ' ')){ avisar(e, "Texto lleno"); break; }
                    }
                    break;
                default:
                    if(k >= 32 && k != 127){                               // caracter normal
                        if(!insertarCar(e, (char)k)){ avisar(e, "Texto lleno"); }
                    }
                    break;
            }
        }

        if(!vertical){ e.colMeta = e.cur - inicioLinea(e, e.cur); }
        corteAnterior = esCorte;
    }

    cout << "\033[0m\033[?25h\033[?1049l" << flush;            // restaura colores, cursor y pantalla
    return !iguales(texto, inicial);
}

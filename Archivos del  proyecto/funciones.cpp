#include "funciones.h"
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <conio.h>
#include <iomanip>
using namespace std;

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

    //Impresi�n del logo.
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

    	cout << "\033[?25h" << endl;   // vuelve a mostrar el cursor
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


void mostrar_error_en(const char mensaje[], const char error[]){
	int columna = cad_l(mensaje) + 1;
	cout << "\033[1A\033["<<columna<<"G";
	cout << "\033[J <EROR, " << error << ">";
	getch();
	cout<<"\r\033[2K";
}


//==================  validar entrada =====================//
double leer(bool esNumero, const char mensaje[], double minimo, double maximo, char texto[]){
	int columna_entrada = cad_l(mensaje)+1;
	while (true)
	{
		cout << mensaje << "\x1b""7";
		bool vacio = false;
		if (!esNumero){
			cin.getline(texto, (int)maximo+1);
			if(cin.fail()){
				cin.clear();
				cin.ignore(10000, '\n');
				vacio = true;
			}else if(cad_l(texto)>0){
				return 0;
			}else{
				vacio = true;
			}
		}else{
			double x;
			cin>>x;
			bool ok = !cin.fail() && cin.peek() == '\n' && x >= minimo && x <= maximo;
			cin.clear();
			cin.ignore(10000, '\n');
			if(ok){
				return x;
			}
		}
		
		if(vacio){
			mostrar_error_en(mensaje, "Dato Vacio");
		}else{
			mostrar_error_en(mensaje, "Dato invalido o fuera de rango");
		}
	}
}

int menu(void){
	int opc=0;
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
		
		opc = leer(true, "      OPCION -->", 1, 5);
		
		return opc;
	
}

int validarIdAutor(long long idAux, vector<autor> &autores, int n ){
    for(int i=0; i<n; i++)
    {
        if(idAux == autores[i].idAutor)
        { return 1; }
    }
    return 0;
};

int validarIdPublicaciones(long long idAux, vector<publicacion> &publicaciones, int n ){
    for(int i=0; i<n; i++)
    {
        if(idAux == publicaciones[i].idPubli)
        { return 1; }
    }
    return 0;
};

int validarNombreAutor(char* nomAux, vector<autor> &autores, int n ){
    for(int i=0; i<n; i++)
    {
        if((strcmp(nomAux, autores[i].nom) == 0))
        { return 0; }
    }
    return 1;
};

void registrarAutores(vector<autor> &autores){
    int n;
    long long idAux;
    cout<<"¿Cuántos autores desea registrar?";
    if (!(cin >> n) || n < 0) {
        cout << "Cantidad inválida." << endl;
        return;
    }
    for(int i=0; i<n; i++){
        do{
            cout<<"Digite id del autor "<<i+1<<"que registrará: ";
            if (!(cin >> idAux)) {
            cout << "ID inválido." << endl;
            return;
    }
        }while(validarIdAutor(idAux, autores, autores.size())!=0);
        autor nuevo{};
        nuevo.idAutor = idAux;
        cin.ignore();
        cout<<"Digite nombre del autor "<<i+1<<"que registrará: ";cin.getline(nuevo.nom, 50);if (cin.fail()) break;
        cout<<"Digite correo del autor "<<i+1<<"que registrará:  ";cin.getline(nuevo.email, 60);if (cin.fail()) break;
        cout<<"¿A qué programa de la facultad pertenece el docente "<<i+1<<" que registrará? : ";cin.getline(nuevo.programa, 60);if (cin.fail()) break;
        autores.push_back(nuevo);
    }   
};

void tipoPublicacion(publicacion &nueva, int &i){
    int tipo;
    bool c=true;
    cout<<"¿Cuál es el tipo de la publicación "<<i+1<<"que registrará?: "<<endl;
    cout<<"\t1. Publicación en revista internacional indexada."<<endl;
    cout<<"\t2. Publicación en revista nacional.";
    cout<<"\t3. Publicación en congreso internacional."<<endl;
    cout<<"\t4. Publicación en congreso nacional."<<endl;
    cout<<"\t5. Articulo en boletín o revista estudiantil."<<endl;
    while (c){
        cout<<"Ingrese número del tipo de la publicación: ";cin>>tipo;if (cin.fail()) break;
        switch (tipo)
        {
        case 1:
            strcpy(nueva.tipoP, "1. Publicación en revista internacional indexada.");
            nueva.baseP+=10;
            c=false;
            break;
        case 2:
            strcpy(nueva.tipoP, "2. Publicación en revista nacional.");
            nueva.baseP+=7;
            c=false;
            break;
        case 3:
            strcpy(nueva.tipoP, "3. Publicación en congreso internacional.");
            nueva.baseP+=5;
            c=false;
            break;
        case 4:
            strcpy(nueva.tipoP, "4. Publicación en congreso nacional.");
            nueva.baseP+=3;
            c=false;
            break;
        case 5:
            strcpy(nueva.tipoP, "5. Artículo en boletín o revista estudiantil.");
            nueva.baseP+=1;
            c=false;
            break;
        default:
            cout<<"Invalido, intente de nuevo. ";
            break;
        }
    }
}

void premioPublicacion(publicacion &nueva, int &i){
    int tipo;
    bool c=true;
    cout<<"Digite año de la publicación "<<i+1<<"que registrará: ";cin>>nueva.anio;if (cin.fail()) exit(0);
    cout<<"¿Cuál es el tipo de de premio que recibió su publicación? "<<endl;
    cout<<"\t1. Primer lugar o mejor ponencia internacional."<<endl;
    cout<<"\t2. Segundo o tercer lugar en ponencia internacional.";
    cout<<"\t3. Premio nacional o mención especial."<<endl;
    cout<<"\t4. Sin premio o reconocimiento."<<endl;
    while (c){
        cout<<"Ingrese número del tipo de premio que recibió la publicación: ";cin>>tipo;if (cin.fail()) break;
        switch (tipo)
        {
        case 1:
            strcpy(nueva.premio, "1. Primer lugar o mejor ponencia internacional.");
            nueva.adicP+=5;
            c=false;
            break;
        case 2:
            strcpy(nueva.premio,"2. Segundo o tercer lugar en ponencia internacional.");
            nueva.adicP+=3;
            c=false;
            break;
        case 3:
            strcpy(nueva.premio,"3. Premio nacional o mención especial.");
            nueva.adicP+=2;
            c=false;
            break;
        case 4:
            strcpy(nueva.premio,"4. Sin premio o reconocimiento.");
            nueva.adicP+=0;
            c=false;
            break;
        default:
            cout<<"Invalido, intente de nuevo. ";
            break;
        }
    }
}

void analizarTexto(publicacion &nueva){
    char opc=-1;
    while (opc != 'G' && opc != 'g') {
        int contVoc = 0, contNum = 0,contBlank = 0, contSpecial = 0, contPalabra = 0;
        cout<<"A. Mostrar cantidad total de caracteres."<<endl;
        cout<<"B. Contar vocales."<<endl;
        cout<<"C. Contar caracteres numéricos." <<endl;
        cout<<"D. Contar espacios en blanco." <<endl;
        cout<<"E. Contar caracteres especiales. "<<endl;
        cout<<"F. Cantidad de palabras. "<<endl;
        cout<<"G. Salir"<<endl;
        cout<<"Ingrese su opción aquí";cin>>opc;
        switch (opc)
        {
        case 'A':
            cout<<"El tamaño de su abstract es de "<<strlen(nueva.abstract);
            break;
        case 'B':
            for(int i=0;i<strlen(nueva.abstract);i++){
                if(nueva.abstract[i]=='a'||nueva.abstract[i]=='e'||nueva.abstract[i]=='i'||nueva.abstract[i]=='o'||nueva.abstract[i]=='u'||nueva.abstract[i]=='A'||nueva.abstract[i]=='E'||nueva.abstract[i]=='I'||nueva.abstract[i]=='O'||nueva.abstract[i]=='U'){
                    contVoc++;
                }
            }
            cout << "Cantidad de vocales: " << contVoc << endl;
            break;
        case 'C':
            for(int i=0; i<strlen(nueva.abstract);i++){
                if (isdigit(static_cast<unsigned char>(nueva.abstract[i]))){
                    contNum++;
                }
            }
            cout << "Cantidad de números: " << contNum << endl;
            break;
        case 'D':
            for(int i=0; i<strlen(nueva.abstract);i++){
                    if (isspace(static_cast<unsigned char>(nueva.abstract[i]))){
                        contBlank++;
                    } 
                }
            cout << "Cantidad de espacios: " << contBlank << endl;
            break;
        case 'E':
        for(int i=0; i<strlen(nueva.abstract);i++){
                if (!isalnum(static_cast<unsigned char>(nueva.abstract[i]))){
                    contSpecial++;
                }
                
            }
        cout << "Cantidad de caracteres especiales: " << contSpecial << endl;
            break;
        case 'F':{
            bool palabra=false;
            for(int i=0; i<strlen(nueva.abstract);i++){
                    if(isspace(static_cast<unsigned char>(nueva.abstract[i]))){
                        palabra=false;
                    }else if(!palabra){
                        palabra=true;
                        contPalabra++;
                    }
            }
            cout << "Cantidad de palabras: " << contPalabra << endl;
            break;
        }
        case 'G':
            opc='G';
            break;
        default:
            break;
        }
    }
}

void editarAbstract(publicacion &nueva){
    char opc;
    cout<<"¿Desea editar el texto del abstract?"<<endl;
    cout<<"Si (S)/No(N)";cin>>opc;
    if (opc=='N'||opc=='n'){
        cout<<"Ok";return;
    }else if(opc=='S'||opc=='s'){
        cout<<"\t\tMy WP-(Word Processor)"<<endl;
        cout<<"¿Qué desea hacer?";
        cout<<"\t1. Analizar texto"<<endl;
        cout<<"\t2. Editar texto"<<endl;
        cout<<"Ingrese aqui su opción: ";cin>>opc;
        if(opc=='1'){
            system("cls");
            analizarTexto(nueva);
        }else if(opc=='2'){

        }else{
            cout<<"Opcion inválida";exit(0);
        }
    }
}

void registrarPublicaciones(vector<publicacion> &publicaciones, vector<autor> &autores){
    if (autores.empty()) {
        cout << "Debe registrar al menos un autor primero." << endl;
        return;
    }
    int n;
    long long idAux;
    cout<<"¿Cuántas publicaciones desea registrar?";
    if (!(cin >> n) || n < 0) {
        cout << "Cantidad inválida." << endl;
        return;
    }
    for(int i=0; i<n; i++){
        publicacion nueva{};
        do{
            cout<<"Digite id de la publicación "<<i+1<<"que registrará: ";
            if (!(cin >> idAux)) {
            cout << "ID inválido." << endl;
            return;
    }
        }while(validarIdPublicaciones(idAux, publicaciones, publicaciones.size())!=0);
        cin.ignore();
        do{
            cout<<"Digite autor de la publicación "<<i+1<<"que registrará: ";cin.getline(nueva.autor, 50);if (cin.fail()) break;
        }while(validarNombreAutor(nueva.autor, autores, autores.size())!=0);
        nueva.idPubli = idAux;
        cout<<"Digite titulo de la publicación "<<i+1<<"que registrará: ";cin.getline(nueva.titulo,100);if (cin.fail()) break;
        tipoPublicacion(nueva, i);
        premioPublicacion(nueva, i);
        cin.ignore();
        cout<<"Digite abstract de la publicación "<<i+1<<"que registrará: ";cin.getline(nueva.abstract, 200);if (cin.fail()) break;

        publicaciones.push_back(nueva);
    }
        
}

#include "funciones.h"
#include <conio.h>
#include <windows.h>
using namespace std;

//============ MAIN ==================//
int main(){
    system("");

    // static: los arreglos viven fuera de la pila, asi puedes subir los maximos sin problema
    static autor autores[MAX_AUTORES];
    int nAutores = 0;
    static publicacion publicaciones[MAX_PUBLICACIONES];
    int nPublicaciones = 0;
    


	int inicio=0;
	int opcion=0;
	presentacion();
	
		do{
			system("cls");
			cout<<"==========================================="<<endl;
			cout<<"                 PUBLISOFT                 "<<endl;
			cout<<"==========================================="<<endl;
			cout<<"        [1] Iniciar Programa               "<<endl;
			cout<<"        [2] Creditos                       "<<endl;
			cout<<"        [3] Salir                          "<<endl;
			cout<<endl;
			inicio = (int)leer(true, "  OPCION --> ", 1, 3);
			
			switch(inicio){
				case 1: 
								
					do{
						opcion = menu();
						system("cls");
						switch(opcion){
	        	        	case 1: registrarAutores(autores, nAutores); break;
	            	    	case 2: registrarPublicaciones(publicaciones, nPublicaciones, autores, nAutores); break;
                    		case 3: actualizarDatos(autores, nAutores, publicaciones, nPublicaciones); break;
                    		case 4: reportes(autores, nAutores, publicaciones, nPublicaciones); break;
                    		case 5: estadisticas(autores, nAutores, publicaciones, nPublicaciones); break;
							}
							
					}while(opcion != 6);
						
				break;
		
				case 2: 
					system("cls");
					cout<<"===================================================="<<endl;
					cout<<"                     PUBLISOFT                      "<<endl;
					cout<<"===================================================="<<endl;
					cout<<"   PROYECTO CORTE 2 PROGRAMACION BASICA             "<<endl;
					cout<<"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--"<<endl;
					cout<<"   DOCENTE: Nohemy Castro Genes                     "<<endl;
					cout<<"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--"<<endl; 
					cout<<"    INTEGRANTES DEL GRUPO                           "<<endl;
					cout<<"                                                    "<<endl;
					cout<<"     (0222610008) ISABELA ORTEGA MARTIN             "<<endl;
					cout<<"     (0222610012) JHON ENMANUEL PAYARES CASTRO      "<<endl;
					cout<<"     (0222610014) ALAN PEREA ARAGON                 "<<endl;
					cout<<"     (0222420001) ANDRES TOBIAS PAYARES DUMAR       "<<endl;
					cout<<"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--"<<endl;
				
					Sleep(1800);
					cout<<"Presione cualquier tecla para regresar al menu";
					getch(); 
					continue; //Regresa al menú principal sin finalizar la ejecución total
					
					break;
				}
			
		}while(opcion != 3);
		
		system("cls");
		cout<<"==========================================="<<endl;
		cout<<" Cerrando programa...                    ||"<<endl;
		cout<<"==========================================="<<endl;
		Sleep(1500);
		system("cls");
		cout<<"==========================================="<<endl;
		cout<<" Gracias por usar nuestro programa! Adios||"<<endl;
		cout<<"==========================================="<<endl;
		Sleep(1200);

	return 0;
}
//============ MAIN ==================//

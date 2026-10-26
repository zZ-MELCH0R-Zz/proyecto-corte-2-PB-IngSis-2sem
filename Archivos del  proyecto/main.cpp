#include "funciones.h"
#include <conio.h>
#include <windows.h>
using namespace std;

//============ MAIN ==================//
int main(){
	system("");
	cout << "\033[?25l";
    

    
    static autor autores[MAX_AUTORES];
    static publicacion publicaciones[MAX_PUBLICACIONES];
    int nPublicaciones = 0;
    int nAutores = 0;


	int inicio=0;
	int opcion=0;
	
	presentacion();
	cout << "\033[?25h";
	
	
		do{
			cout << "\033[?25l";
			system("cls");
			cout << "\033[?25h";
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
					cout<<"\033[?25l";
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
			
		}while(inicio != 3);
		
		system("cls");
		cout<<"\033[?25l";
		
		cout<<flush<<"==========================================="<<endl;
		cout<<flush<<" Cerrando programa...                    ||"<<endl;
		cout<<flush<<"==========================================="<<endl;
		Sleep(1500);
		system("cls");
		cout<<flush<<"==========================================="<<endl;
		cout<<flush<<" Gracias por usar nuestro programa! Adios||"<<endl;
		cout<<flush<<"==========================================="<<endl;
		Sleep(1200);

	return 0;
}
//============ MAIN ==================//

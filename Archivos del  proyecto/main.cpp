#include "funciones.h"
#include <windows.h>
#include <conio.h>
#include <iomanip>
using namespace std;

vector<autor> autores;
vector<publicacion> publicaciones;


//============ MAIN ==================//
int main(){
	system("");
	int opcion=0;
	int opcion_menu=0;
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
			opcion = leer(true, "  OPCION --> ", 1, 3);
			
			switch(opcion){
				case 1: 
								
						do{
							opcion_menu = menu();
							system("cls");
							switch(opcion_menu){
								case 1: break;
								case 2: break;
								case 3: break;
								case 4: break;
								case 5: break;
							}
							
						}while(opcion_menu != 6);
						
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
					cout<<"     (0222610014) ALAN PEREA ARAGóN                 "<<endl;
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


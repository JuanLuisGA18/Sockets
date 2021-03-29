#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <list> 
#include <iterator> 
#include<sstream>
#include<fstream>
using namespace std;
class Pelicula
{

    //Atributoes
     public:
     string nombre;
     string genero;
    string estudio;
    string puntAud;
    string rentabilidad;
    string rotten;
    string worldGross;
    string ano;
    //Funciones
    public:
    string CrearMens(string op);
    //Constructores
    Pelicula(string linea);
    Pelicula();
    
    
};
Pelicula::Pelicula(string linea)
{   
    
    stringstream lin(linea);
    getline(lin,nombre,',');
    getline(lin,genero,',');
    getline(lin,estudio,',');
    getline(lin,puntAud,',');
    getline(lin,rentabilidad,',');
    getline(lin,rotten,',');
    getline(lin,worldGross,',');
    getline(lin,ano);

}



Pelicula::Pelicula()
	{

	}
    /*
string Pelicula::CrearMens(string op)
    {

         char *opc; 
        strcpy(opc,op.c_str());
		switch(opc[0])
		{
			case '1':
			return "1,"+ nombre;
			case '2':
			return "1,"+ genero;
			case '3':
			return "1,"+ estudio;
			case '4':
			return "1,"+ puntAud;
			case '5':
			return "1,"+rentabilidad;
			case '6':
			return "1,"+ rotten;
			case '7':
			return "1,"+ worldGross;
			case '8':
			return "1,"+ ano;
			default:
				{
					
					return "9 Opcode no encontrado";
				}
		}
    return "9 Opcode no encontrado";
	//Fin de generaciòn de paquete
  }*/
int main()
{
    
    //Establecer conexión
    int conexionServ, conexionClnt, puerto;
    socklen_t longc; 
    struct sockaddr_in cliente, servidor;
    char buffer[37];
    puerto = htons(1234);
    conexionServ = socket(AF_INET, SOCK_STREAM, 0);
    bzero((char *)&servidor, sizeof(servidor));
    servidor.sin_family = AF_INET;
    servidor.sin_port = puerto;
    servidor.sin_addr.s_addr = INADDR_ANY;
    if ((bind(conexionServ, (struct sockaddr *)&servidor, sizeof(servidor))) < 0)
    {
        cout << "Error al asingar el puerto";
        close(conexionServ);
        return 1;
    }
    listen(conexionServ, 3);
    longc = sizeof(cliente);
    conexionClnt = accept(conexionServ, (struct sockaddr *)&cliente, &longc);
    if (conexionClnt < 0)
    {
        cout << "Error al conectar al servidor";
        close(conexionServ);
        return 1;
    }
    //Leer archivo
    string linea;
    ifstream datos;
    datos.open("movies.csv");
    list <Pelicula> catalogo;
   // list <Pelicula>::iterator iter2;
  
      while (getline(datos,linea))
      {
         Pelicula aux = Pelicula(linea);
          catalogo.push_back(aux);
          //cout<<aux.nombre;
      }
     /* iter2=catalogo.begin();
      for(int i=0; i<5;i++)
      {
          cout<<iter2->nombre;
          iter2.operator++();
      }*/

    
  
    //Leer el mensaje recibido

    if (read(conexionClnt, buffer, 37) < 0)
    {  
        cout << "Error al recibir los datos\n";
        close(conexionClnt);
        close(conexionServ);
        return 1;
    
    }
   
    char opcode[2];
    opcode[0]=buffer[0];
    opcode[1]='\0';
    char nom[36];
    int i = 2;
    int j=0;
    while(buffer[i]!=','&&j<35&&i<37)
    {
       // cout<<i<<" "<<j;
        nom[j]=buffer[i];
        i++;
        j++;
    }
   nom[j]='\0';

    string nombre(nom);
    //cout<<nombre;
    //cout<<nombre;;



    //cout<<opcode;
    string paquete, *paque;
    char opc[2];
    //Buscar el nombre de la pelicula
    list <Pelicula>::iterator iter;
   iter=catalogo.begin();
   paquete="0";
    for(i=0;i<catalogo.size()-1;i++)
      { 

          if(iter->nombre==nombre)
            {
              
                switch(opcode[0])
                {
                    case '1':
                    {
                        paquete="1,"+iter->nombre+",";
                        break;
                    }

                    case '2':
                    {
                        paquete="1,"+iter->genero+",";
                        break;
                    }

                    case '3':
                    {
                        paquete="1,"+iter->estudio+",";
                        break;
                    }

                    case '4':
                    {
                        paquete="1,"+iter->puntAud+",";
                        break;
                    }

                    case '5':
                    {
                        paquete="1,"+iter->rentabilidad+",";
                        break;
                    }

                    case '6':
                    {
                        paquete="1,"+iter->rotten+",";
                        break;
                    }
                    case '7':
                    {
                        paquete="1,"+iter->worldGross+",";
                        break;
                    }
                    case '8':
                    {
                        paquete="1,"+iter->ano+",";
                        break;
                    }
                    default:
                    {
                        paquete="9,Opcode no encontrado";
                        break;
                    }
                        
                
                    
                    
                }
                break;
            }
            iter++;
      }
      //Responder
    char mens[37];
   
    strcpy(mens,paquete.c_str());
 
    send(conexionClnt,mens,37,0);
    close(conexionClnt);
    close(conexionServ);
    return 0;
}

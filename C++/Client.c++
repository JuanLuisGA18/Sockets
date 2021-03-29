#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<iostream>

using namespace std;
int main()
{
    struct sockaddr_in cliente;
    struct hostent *servidor;

    servidor = gethostbyname("localhost");
    if(servidor == NULL)
    {
        cout<<"Error en la direcciòn de servidor";
        return 1;
    }
    int puerto, conexion;
    char buffer[38];
    string opcode;
    string nombre;
    string mensaje;
    conexion = socket(AF_INET, SOCK_STREAM,0);
    puerto= htons(1234);
    bzero((char * )&cliente, sizeof((char *)&cliente));
    cliente.sin_family= AF_INET;
    cliente.sin_port = puerto;
     bcopy((char *)servidor->h_addr, (char *)&cliente.sin_addr.s_addr, sizeof(servidor->h_length));
     if(connect(conexion,(struct sockaddr*)&cliente, sizeof(cliente))<0)
     {
         cout<<"Error en la conexiòn\n";
         close(conexion);
         return 1;
     }
     cout<<"Conexion exitosa\n";
    cout<<"Ingrese Nombre ";
     getline(cin,nombre);
     cout<<"Opcode:\n";
     cout<<"1.- Nombre \n";
     cout<<"2.- Genero\n";
     cout<<"3.- Estudio\n";
     cout<<"4.- Puntuación Audiencia \n";
     cout<<"5.- Rentabilidad \n";
     cout<<"6.- Puntuación rotten tomatoes\n";
     cout<<"7.- Puntuación World Gross \n";
     cout<<"8.- Ano\n";
     cout<<"Ingrese opcode: ";
     
     
   
      getline(cin,opcode);
      mensaje=opcode+","+nombre+",";
     
    
    strcpy(buffer,mensaje.c_str());
     
    send(conexion,buffer,mensaje.length(), 0);
    
    
    int tam;
   
    bzero(buffer,38);
    read(conexion, buffer,38);

    if((buffer[0]=='0'))
    {
        cout<<"Pelicula no encontrada\n";
    }
   else
    {
    
        
        int i=2;
        int j=0;
        char *resultado= new char[37];
        while(buffer[i]!=','&&j<(36)&&i<38)
        {
    
            resultado[j]=buffer[i];
            i++;
            j++;
        }
        resultado[j]='\0';
         string respuesta(resultado);
         cout<<"La respuesta es: "<<respuesta<<"\n";
    }
  
     
}


//Clases
import java.io.*;
import java.net.*;
import java.util.*;
//Clase servidor
public class Servidor
{
	//Clase pelicula que incluye los datos de cada pelicula
	static class Pelicula
	{
		//Variables
		
		String nombre, genero, estudio, puntAud, rentabilidad, rotten,  worldGross, ano; 
		//COnstructor alternativos
		
		Pelicula(String[] linea)
		 {
		 	//Inicializaciòn de datos
		 	
		 	nombre=linea[0];
		 	genero=linea[1];
		 	estudio=linea[2];
		 	puntAud=linea[3];
		 	rentabilidad=linea[4];
		 	rotten=linea[5];
		 	worldGross=linea[6];
		 	ano=linea[7];
		 	

		 }//FIn constructor
		 Pelicula()
		{

		}

	}//Fin clase pelicula
	//Funciòn de busqueda
	static int buscar(ArrayList<Pelicula> catalogo, String buscada)
	{
		
		for(int i=0; i<catalogo.size();i++)
		{
			String aux= new String(catalogo.get(i).nombre);
			String aux2= new String(buscada);
			if(aux.equals(aux2))
			{	
				System.out.println(catalogo.get(i).nombre);
				return i;
				
			}
		}				
			return -1;

	}
	//Fin funciòn de busqueda
	//Generaciòn del paquete a enviar
	static String paquete (ArrayList<Pelicula> catalogo, String opcode, int pos)
	{
		char op=opcode.charAt(0);
		//System.out.println(op);
		switch(op)
		{
			case '1':
			return "1,"+catalogo.get(pos).nombre;
			case '2':
			return "1,"+catalogo.get(pos).genero;
			case '3':
			return "1,"+catalogo.get(pos).estudio;
			case '4':
			return "1,"+catalogo.get(pos).puntAud;
			case '5':
			return "1,"+catalogo.get(pos).rentabilidad;
			case '6':
			return "1,"+catalogo.get(pos).rotten;
			case '7':
			return "1,"+catalogo.get(pos).worldGross;
			case '8':
			return "1,"+catalogo.get(pos).ano;
			default:
				{
					
					return "9 Opcode no encontrado";
				}
		}

	}//Fin de generaciòn de paquete
//main
public static void main(String args[]) throws IOException 
{
	//Variables
	String linea;
	String[] datos = null;
	int i=0, pos;
	//Array de peliculas
	ArrayList<Pelicula> catalogo = new ArrayList<Pelicula>();
	//Iniciar conexiòn de socket
	BufferedReader reader = new BufferedReader(new FileReader("movies.csv"));
	ServerSocket servSock = new ServerSocket(1234);
	Socket clientSock = servSock.accept();
	OutputStream out = clientSock.getOutputStream();
	DataOutputStream texto = new DataOutputStream(out);
	InputStream in = clientSock.getInputStream();
	DataInputStream buscar = new DataInputStream(in);

	//Lectura de archivo
	while((linea = reader.readLine())!=null)
		{
			datos=linea.split(",");
			Pelicula aux=new Pelicula(datos);
			catalogo.add(aux);
			i++;
			
		}
		
	//Recepciòn de mensaje
	byte dat  [] = new byte[38];
	buscar.read(dat,0,38);
	String mensaje = new String(dat);
	
	
	String[] info = mensaje.split(",");
	//System.out.println(mensaje);
	//System.out.println(info[0]);
	//System.out.println(info[1]);
	
	//Busqueda de la pelicula
	pos=buscar(catalogo, info[1]);
	//Respuesta
	if(pos==-1)
		texto.writeBytes("0");		
	else
	{
	String aux = paquete(catalogo,info[0],pos);
	
		//System.out.println(aux.length());
		//texto.writeInt(aux.length());
		texto.write(aux.getBytes("utf-8"),0,aux.length());
			
		

		
	}
	//Cerrar conexiòn
	texto.close();
	out.close();
	clientSock.close();


}
//Fin main

}//Fin clase servidor
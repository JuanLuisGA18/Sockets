//Paquetes
import java.io.*;
import java.net.*;
import java.util.*;
//Clase principal
public class Client{
	//Menú para obtener opcode
	static String menuop()
	{
		Scanner lectura = new Scanner(System.in);
		String op=null;
		System.out.println("Ingrese el opcode a buscar:");
		System.out.println("1 Film");
		System.out.println("2 Genre");
		System.out.println("3 Lead Studio");
		System.out.println("4 Audience Score");
		System.out.println("5 Profitability");
		System.out.println("6 Rotten Tomatoes");
		System.out.println("7 Worldwide Gross");
		System.out.println("8 Year");
		System.out.println("0 No encontrado");
		op=lectura.nextLine();
		return op;
	}
	//Fin menù opcode
	//Menù para nombre de pelicula
	static String menu()
	{
		Scanner lectura = new Scanner(System.in);
		String nombre=null;
		System.out.println("Ingrese el nombre de la pelicula a buscar:");
		nombre=lectura.nextLine();
		return nombre;
	}//Fin menù nombre
	//main
	public static void main(String args[]) throws IOException
	{
		//Variables
		String nombre, op;
		//Iniciar conexiòn
		Socket socketGen= new Socket("localhost",1234);
		OutputStream salida = socketGen.getOutputStream();
		DataOutputStream escribir = new DataOutputStream(salida);
		InputStream entrada = socketGen.getInputStream();
		DataInputStream texto = new DataInputStream(entrada);
		//Pedir datos
		nombre=menu();
		op=menuop();
		//Solicitar informaciòn
		String aux= new String(op+","+nombre+",");
		escribir.write(aux.getBytes("utf-8"),0,aux.length());

		//Recibir y mostrar respuesta
		
		byte dat [] = new byte[38];
		entrada.read(dat,0,38);
		String cadena= new String(dat);
		
		//System.out.println(cadena);
		if(cadena.charAt(0)=='0')
		{
			System.out.println("No se encontro la pelicula");
			cadena=null;
		}
		else
		{
		String[] dato;
	
		dato=cadena.split(",");
		System.out.println(dato[1]);
		}

		
	}	
	//Fin main
}
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <locale.h>

/* incluyo los archivos de codigos que voy a usar */
#include "algoritomos.h"
#include "arboles.h"

/* version del programa */
const char *VERSION= "0.0.20";

/* base de dato por defecto, archivo binario, donde se aguardara el arbol */
const char *BASE_DATO = "datos.bin";

void print_usage();
void help();


int main(int argc, char *argv[]) 
{
	/* punteros a los nodos del arbol*/
	t_nodo* raiz=NULL;
	t_nodo* nodo=NULL;
	
	/* puntero doble a un arbol desplegado en una lista,
	* me permite guardar en un archivo de forma secuencial */
	t_nodo** tlist=NULL;
	
	/* variable que uso para almacenar la clave del cada archivo imagen */
	unsigned int hmac;
	
	char filename[FILENAME_MAX];
	char dbname[FILENAME_MAX];
	char svalue[64];
	int value;
	setlocale(LC_ALL, "es_ES");
	
	int option = 0;
	/* flags */
	int ffile = 0,
		fdb = 0,
		fhelp = 0,
		fvalue = 0,
		fcalculate = 0,
		fwrite = 0;
	
	while ((option = getopt(argc, argv,"hcf:d:w:v:")) != -1) {
		switch (option) {
		case 'h' : 
			fhelp = 1; 
			break;
		case 'f' : 
			ffile = 1;
			strncpy (filename, optarg, sizeof (filename));
			filename[sizeof (filename) - 1] = '\0';
			break;
		case 'd' : 
			fdb = 1; 
			strncpy (dbname, optarg, sizeof (dbname));
			dbname[sizeof (dbname) - 1] = '\0';
			break;
		case 'v' : 
			fvalue = 1;
			strncpy (svalue, optarg, sizeof (svalue));
			svalue[sizeof (svalue) - 1] = '\0';
			/* vamos a trabajar solo con numeros */
			value = atoi(svalue);
			/* en caso de trabajar con caracteres el valor tomado seria svalue, sin conversion */
			break;
		case 'c' : 
			fcalculate = 1;
			break;
		case 'w' : 
			fwrite = 1; 
			strncpy (svalue, optarg, sizeof (svalue));
			svalue[sizeof (svalue) - 1] = '\0';
			/* vamos a trabajar solo con numeros */
			value = atoi(svalue);
			break;
		default: 
			print_usage(); 
			exit(EXIT_FAILURE);
		}
	}

	if (fhelp) {
		help();
		return 0;
	}
	
	if (ffile) {
		raiz = load_file_to_tree( fdb ? dbname : BASE_DATO );
		hmac = file_get_adler32( filename );
		if (fcalculate) {
			printf("Hash:0x%X\n", hmac);
			delete_tree(&raiz);
			return 0;
		}
		if (fvalue) {
			nodo = search(raiz, hmac);				
			insert(&raiz, hmac, value);
			int num = size_tree(raiz);
			tlist = tree_to_list(raiz, &num);
			save_file_list(tlist , num, fdb ? dbname : BASE_DATO );
			delete_list(&tlist);
			delete_tree(&raiz);
			if (nodo == NULL)
				printf("Ok:Clave registrada\n");
			return 0;
		}
		if (fwrite) {
			nodo = search(raiz, hmac);
			if (nodo != NULL)
				delete_node(&raiz, hmac);
			insert(&raiz, hmac, value);
			int num = size_tree(raiz);
			tlist = tree_to_list(raiz, &num);
			save_file_list(tlist , num, fdb ? dbname : BASE_DATO );
			delete_list(&tlist);
			delete_tree(&raiz);
			if ( nodo != NULL )
				printf("Ok:Clave Re-Escrita\n");
			else
				printf("Ok:Clave registrada\n");
			return 0;				
		}
		
		nodo = search(raiz, hmac);
		if (nodo != NULL) {
			printf("Ok:%d\n", nodo->value);
			return nodo->value;
		} else {
			printf("Error:Clave no encontrada.\n", hmac);
		}
		delete_tree(&raiz);
		return 0;
	}
	help();
	return EXIT_SUCCESS;
}

void print_usage() 
{
	printf("Pruebe: 'bfrc -h' para mas información\n");
}

void help()
{
	printf(
		   "\nModo de empleo:  bfcr -f [FICHERO]]\n"
		   "Calcula el hash con el cifrado Adler32 del archivo, luego busca en su base de dato el valor asociado,\n"
		   "si lo encuentra devuelve [OK: (valor)]\n"
		   "En el caso que no encuentre el registro en la base de dato devuelve Error:Este Hash no esta registrado. \n\n"
		"Opción de ayuda:\n"
		" -h\tMostrar opciones de ayuda\n\n");
	printf("Opciones de la aplicaci%cn:\n", 162);
	printf(" -f\tArchivo de imagen, la app retorna el valor asociado con el formato Ok:[value],\n"
		"\tsi no esta registrado devuelve Error:Este Hash no esta registrado.\n"
		" -v\tEsta opción es para registrar el valor al Hash asociado al archivo indicado en '-f [FICHERO]',\n"
		"\tsi el Hash ya esta registrado se ignora el registro y retorna Error:La clave [HASH] ya existe,\n"
		"\tsi la operación de registro tiene excito devuelve Ok:Clave registrada.\n"
		" -w\tEsta opción es para registrar el valor al Hash asociado al archivo indicado en '-f [FICHERO]' \n"
		   "\tsi ese Hash ya esta registrado entonces sobre escribe el valor existente.\n"   
		" -c\tCalcula el hash (Adler-32) del archivo indicado en la opción '-f [FICHERO]',\n"
		"\tla app devuelve Hash:[0xVALUE] en hexadecimal.\n"
		" -d\tIndica que base de dato utilizar, si no se especifica la opción '-d database',\n"
		"\tentonces crea una por defecto llamada 'datos.bin'.\n\n"
		"Version: %s\n\n", VERSION );
}


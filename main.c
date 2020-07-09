#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* incluyo los archivos de codigos que voy a usar */
#include "algoritomos.h"
#include "arboles.h"

/* version del programa */
const char *VERSION= "0.0.10";

/* base de dato por defecto, archivo binario, donde se aguardara el arbol */
const char *BASE_DATO = "datos.bin";

/* funcion que se llama cuando se pide el help desde consola */
void help();

int main(int argc, char* argv[])
{
    /* punteros a los nodos del arbol*/
    t_nodo* raiz=NULL;
    t_nodo* nodo=NULL;

    /* puntero doble a un arbol desplegado en una lista,
     * me permite guardar en un archivo de forma secuencial */
    t_nodo** tlist=NULL;

    /* variable que uso para almacenar la clave del cada archivo imagen */
    unsigned int hmac;

    char file[FILENAME_MAX];
    char db[FILENAME_MAX];
    char svalue[64];

    int value;
    int     ffile = 0,
            fvalue = 0,
            fhelp = 0,
            fdb = 0,
            c;

    /* si ejecuto solo es programa sin argumentos */
    if ( argc < 2 ) {
        help();
        exit(1);
    }

    /* analiza los parametros de entrada */
    while ( --argc > 0 && (*++argv)[0] == '-') {
        while ( c = *++argv[0] ) {
            switch (c){
            case 'h':
                fhelp = 1;
                break;
            case 'v':
                fvalue = 1;
                strcpy(svalue, (*++argv));
                value = atoi(svalue);
                --argc;
                break;
            case 'f':
                ffile = 1;
                strcpy(file, (*++argv));
                --argc;
                break;
            case 'd':
                fdb = 1;
                strcpy(db, (*++argv));
                --argc;
                break;
            }
        }
        if(fhelp) break;
    }

    /* si se utilizo -h devuelve el help en consola */
    if (fhelp) {
        help();
        return 0;
    }


    /* si se utilizo la opcion -f + -v es el modo entrenamiento */
    if ( fvalue && ffile )
    {
        raiz = load_file_to_tree( fdb ? db : BASE_DATO );
        hmac = file_get_adler32( file );
        insert(&raiz, hmac, value);
        int num = size_tree(raiz);
        tlist = tree_to_list(raiz, &num);
        save_file_list(tlist , num, fdb ? db : BASE_DATO );
        delete_list(&tlist);
        delete_tree(&raiz);
        printf("Ok:Clave registrada\n");
    } else if ( ffile )
    {
        raiz = load_file_to_tree( fdb ? db : BASE_DATO );
        hmac = file_get_adler32( file );

        nodo = search(raiz, hmac);
        if (nodo != NULL) {
            printf("Ok:%d\n",nodo->value);
            return nodo->value;
        } else {
            printf("Error:Clave no encontrada.\n", hmac);

        }
        delete_tree(&raiz);
    } else {
        printf("Error:Los parametros no son correctos.\n"
               "Use: bfrc -h\n\n");
    }

    return 0;
}




void help()
{
    printf("\nModo de empleo:  bfcr -f [FICHERO]]\n"
    "Calcula el hash con el cifrado Adler32 del archivo, luego busca en su base de dato "
    "el valor asociado, si lo encuentra devuelve [OK: (valor)]\n"
    "En el caso que no este registrado devuelve [$ Not found!]\n\n"
    "Modo de entrenamiento: bfcr -f [FICHERO]] -v [VALUE]\n"
    "Calcula el hash con el cifrado Adler32 del archivo y asocia en la base de dato el valor que se paso con la opcion -v.\n"
    "Otros parametros:\n"
    "\t-d [FICHERO DATOS] : Dice que base de dato se utilizara, si no esta presente este parameto entonces se crea una por defecto. (datos.bin).\n\n"
    "Version: %s\n\n", VERSION );
}

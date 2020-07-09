#include <stdio.h>
#include <stdlib.h>

#include "algoritomos.h"

const unsigned int MOD_ADLER = 65521;

unsigned int adler32(unsigned char *data, size_t len)
{
    unsigned int a = 1, b = 0;
    size_t index;
    for (index = 0; index < len; ++index)
    {
        a = (a + data[index]) % MOD_ADLER;
        b = (b + a) % MOD_ADLER;
    }
    return (b << 16) | a;
}

unsigned int file_get_size(char *file_name)
{
    FILE *fp;
    fp = fopen ( file_name, "r" );
    if (fp==NULL)
    {
        fputs ("Error: Al intentar leer el archivo", stderr);
        exit (1);
    }
    fseek(fp, 0L, SEEK_END);    /* voy al final de fichero */
    int bytes = ftell(fp);      /* esto es para caluclar el tamaño del archivo */
    fclose(fp);
    return bytes;
}


unsigned int file_get_adler32(char *file_name)
{
    FILE *fp;
    unsigned int key;

    int bytes = file_get_size(file_name);

    fp = fopen ( file_name, "r" );
    if (fp==NULL)
    {
        fputs ("Error: Al intentar leer el archivo", stderr);
        exit (1);
    }


    //fseek(fp, 0L, SEEK_END);  /* voy al final de fichero */
    //int bytes = ftell(fp);    /* esto es para caluclar el tamaño del archivo */
    //printf("%s ocupa %d bytes\n", file_name, bytes);
    //fseek(fp, 0L, SEEK_SET); // vuelvo al principio del fichero
    unsigned char *data = malloc(sizeof(unsigned char)*bytes);
    fread ( data, sizeof(unsigned char*), bytes, fp );
    key = adler32(data, bytes);
    fclose(fp);
    return key;
}


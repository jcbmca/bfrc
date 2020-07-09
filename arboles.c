#include <stdio.h>
#include <stdlib.h>

#include "arboles.h"




void save_file_list( t_nodo*t[], int num, char *name_file)
{
    FILE *f;
    f = fopen(name_file, "wb");
    if (f== NULL) {
        fputs ("Error: Al intentar guardar el archivo",stderr);
        exit (1);
    }
    for ( register int i=0 ;  i<num ; i++)
        fwrite(t[i], sizeof(t_nodo), 1, f);
    fclose(f);
}


t_nodo*  load_file_to_tree( char *name_file)
{
    int bread;
    t_nodo* r=NULL;

    FILE *f;
    f = fopen(name_file, "rb");
    if (f== NULL)
    {
        //fputs ("No existe el archivo.\n", stderr);
        return r;
    }

    t_nodo* tmp = (t_nodo*)malloc(sizeof(t_nodo));
    do{
        bread = fread( tmp, sizeof(t_nodo), 1, f );
        if (bread>0)
        {
            insert(&r, tmp->key , tmp->value  );
        }
    }while(bread>0);
    free(tmp);
    fclose(f);
    return r;
}


int cmp_Key(int key1, int key2)
{
    return (key1==key2 ) ? 0 :(( key1<key2 ) ? -1 : 1);
}

void insert(t_nodo**r, int key, int value)
{
    t_nodo* n;
    int cmp;
    if(*r==NULL) {
        n=(t_nodo*)malloc(sizeof(t_nodo));
        n->key= key ;
        n->value = value;
        n->i = n->d=NULL;
        *r=n;
    }
    // atención no tener 2 claves idénticas
    else if( (cmp = cmp_Key( key, (*r)->key) ) == 0)
        printf("Error: la clave %X ya existe\n", key);
    else if (cmp<0)
        // paso de la dirección del puntero al hijo izquierdo
        insert(&(*r)->i, key, value);
    else
        // paso de la dirección del puntero al hijo derecho
        insert(&(*r)->d, key, value);
}


t_nodo* search(t_nodo*r, int key)
{
    int cmp;
    t_nodo* res=NULL;
    if(r!=NULL)
    {
        if ((cmp=cmp_Key(key,r->key))==0)
            res=r;
        else if (cmp<0)
            res= search(r->i, key);
        else
            res= search(r->d,key);
   }
   return res;
}

void show_inorder(t_nodo*r)
{
   if (r != NULL)
   {
      show_inorder(r->i);
      printf("%d  ",r->key);
      show_inorder(r->d);
   }
}


void delete_tree(t_nodo**r)
{
   if (*r!=NULL){
      delete_tree(&(*r)->i);
      delete_tree(&(*r)->d);
      free(*r);
      *r=NULL;
   }
}

t_nodo** tree_to_list(t_nodo* r, int *n_nodos)
{
    int t,q;
    t_nodo**tab = NULL;
    if (*n_nodos>0)
    {
        *n_nodos=size_tree(r);
        tab = (t_nodo**)malloc( sizeof(t_nodo*)*(*n_nodos) );
        t=0;
        q=1;
        tab[t]=r;                  // raíz al comienzo
        while ( q < *n_nodos )
        {
            if (tab[t]->i !=NULL )  // si hay hijo izq. añadir
                tab[q++]=tab[t]->i;
            if (tab[t]->d != NULL)  // si hay hijo der. añadir
                tab[q++]=tab[t]->d;
            t++;                    // pasar al siguiente
        }
    }
    return tab;
}

int size_tree(t_nodo*r)
{
int res=0;
   if (r!=NULL)
      res=1+size_tree(r->i)+size_tree(r->d);
   return res;
}

void show_list(t_nodo* t[], int num)
{
    int i;
    for (i=0; i<num; i++)
        printf("(%2d - 2%d) -- ", t[i]->key, t[i]->value);
    putchar('\n');
}

void delete_list(t_nodo***l)
{
   if(*l)
   {
      free(*l);
      *l=NULL;
   }
}

t_nodo* delete_node(t_nodo**r, int dat)
{
    int cmp;
    t_nodo*res=NULL;

    if(*r!=NULL)
    {
        if ( (cmp=cmp_Key(dat,(*r)->key))<0)
            res=delete_node(&(*r)->i,dat);
        else if (cmp>0)
            res=delete_node(&(*r)->d,dat);
        else{     // nodo encontrado, borrado
            res=*r;
            if (res->d==NULL)
                *r=res->i;
            else if (res->i==NULL)
                *r=res->d;
            else{  // si tiene un hijo izquierdo y un hijo derecho
                // elimina el más grande del subárbol izquierdo
                res=get_node_max(&(*r)->i);
                (*r)->key = res->key;
            }
        }
    }
    return res;
}

t_nodo* get_node_max(t_nodo**r)
{
    t_nodo*max=NULL;
    if(*r!=NULL)
    {
        if((*r)->d==NULL)
        { // máximo encontrado
            max=*r;
            *r=(*r)->i;
        }
        else
            max=get_node_max(&(*r)->d);
    }
    return max;
}

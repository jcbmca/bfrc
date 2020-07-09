#ifndef ARBOLES_H
#define ARBOLES_H

typedef struct nodo{
    int key;
    int value;
    struct nodo*i,*d;
} t_nodo;


int         cmp_Key        (int key1, int key2);
void        insert             (t_nodo**r, int key, int value);
t_nodo*     search               (t_nodo*r, int key);
void        show_inorder       (t_nodo*r);
int         altura               (t_nodo*r);
void        delete_tree        (t_nodo**r);
t_nodo**    tree_to_list          (t_nodo*r, int*n_nodos);
int         size_tree              (t_nodo*r);
void        show_list        (t_nodo*t[],int num);
void        delete_list        (t_nodo***l);
t_nodo*     delete_node          (t_nodo**r, int dat);
t_nodo*     get_node_max      (t_nodo**r);
void        save_file_list(t_nodo*t[], int num, char* name_file);
t_nodo*     load_file_to_tree( char* name_file );





#endif // ARBOLES_H

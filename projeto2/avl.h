#ifndef AVL_H
    #define AVL_H
    
    #include <stdbool.h>
    #include <stdlib.h>
    #include <stdio.h>
    //#include "item.h"

    typedef struct avl_ AVL;
    typedef struct no_ NO;

    AVL * avl_criar(void);
    bool avl_inserir(AVL *t, int chave);
    bool avl_remover(AVL *t, int chave);
    bool avl_apagar_arvore(AVL **t);
    bool avl_buscar(AVL *t, int chave);
    void avl_imprimir(AVL *t);
    AVL *avl_unir(AVL *a, AVL *b);
    AVL * avl_inter(AVL *a, AVL *b);
    bool avl_eh_vazia(AVL *t);

#endif

#include <stdlib.h>
#include <stdio.h>
#include<stdbool.h>
#include "avl.h"

typedef struct avl_ AVL;
typedef struct set_ SET;

struct set_{
    AVL *arvore;
};

SET * set_criar(void){
    SET *set = (SET *)malloc(sizeof(SET));
    if(set == NULL)
        return NULL; 
        
    set->arvore = avl_criar();
    return set;
}

void set_apagar(SET **set){
    if (*set != NULL){
        avl_apagar_arvore(&(*set)->arvore);
        free(*set);
        *set = NULL;
    }
}

bool set_inserir(SET *set, int chave){
    return avl_inserir(set->arvore, chave);  
}

bool set_remover(SET *set, int chave){
    return avl_remover(set->arvore, chave);
}

bool set_pertence(SET *set, int chave){
    return (avl_buscar(set->arvore, chave));
}

SET *set_uniao(SET *A, SET *B){
    SET *uniao = set_criar();  
    uniao->arvore = avl_unir(A->arvore, B->arvore);
    return uniao;
}

SET *set_intersecao(SET *A, SET *B) {
    SET * inter = set_criar();
    inter->arvore = avl_inter(A->arvore, B->arvore);
    return inter;
}

void set_imprimir(SET *set){
    if(set == NULL || set->arvore == NULL){
        printf("CONJUNTO VAZIO.\n");
        return; 
    }

    avl_imprimir(set->arvore);
}
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "avl.h"
#include "rb.h"

typedef struct avl_ AVL;
typedef struct set_ SET;

struct set_{
    AVL *arvore;
    RB *arvore2;
};

SET * set_avl_criar(void){
    SET *set = (SET *)malloc(sizeof(SET));
    if(set == NULL)
        return NULL; 
        
    set->arvore = avl_criar();
    set->arvore2 = NULL;
    return set;
}

void set_avl_apagar(SET **set){
    if (*set != NULL){
        avl_apagar_arvore(&(*set)->arvore);
        free(*set);
        *set = NULL;
    }
}

bool set_avl_inserir(SET *set, int chave){
    return avl_inserir(set->arvore, chave);  
}

bool set_avl_remover(SET *set, int chave){
    return avl_remover(set->arvore, chave);
}

bool set_avl_pertence(SET *set, int chave){
    return (avl_buscar(set->arvore, chave));
}

SET *set_avl_uniao(SET *A, SET *B){
    SET *uniao = set_avl_criar();  
    uniao->arvore = avl_unir(A->arvore, B->arvore);
    return uniao;
}

SET *set_avl_intersecao(SET *A, SET *B) {
    SET * inter = set_avl_criar();
    inter->arvore = avl_inter(A->arvore, B->arvore);
    return inter;
}

void set_avl_imprimir(SET *set){
    if(set == NULL || avl_eh_vazia(set->arvore))
        printf("Conjunto vazio.\n");

    avl_imprimir(set->arvore);
}

////////////////////////////////////////////////////////////////////////////////


SET * set_rb_criar(void){
    SET *set = (SET *)malloc(sizeof(SET));
    if(set == NULL)
        return NULL; 
        
    set->arvore2 = rb_criar();
    set->arvore = NULL;
    return set;
}

void set_rb_apagar(SET **set){
    if (*set != NULL){
        rb_apagar_arvore(&(*set)->arvore2);
        free(*set);
        *set = NULL;
    }
}

bool set_rb_inserir(SET *set, int chave){
    return rb_inserir(set->arvore2, chave);  
}

bool set_rb_remover(SET *set, int chave){
    return rb_remover(set->arvore2, chave);
}

bool set_rb_pertence(SET *set, int chave){
    return (rb_buscar(set->arvore2, chave));
}

SET *set_rb_uniao(SET *A, SET *B){
    SET *uniao = set_rb_criar();  
    uniao->arvore2 = rb_unir(A->arvore2, B->arvore2);
    return uniao;
}

SET *set_rb_intersecao(SET *A, SET *B) {
    SET * inter = set_rb_criar();
    inter->arvore2 = rb_inter(A->arvore2, B->arvore2);
    return inter;
}

void set_rb_imprimir(SET *set){
    if(set == NULL || rb_eh_vazia(set->arvore2))
        printf("Conjunto vazio.\n");

    rb_imprimir(set->arvore2);
}

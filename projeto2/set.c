#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "avl.h"
#include "rb.h"

typedef struct avl_ AVL;
typedef struct set_ SET;

/* Defines para ficar evidente qual estrutura estamos comparando */
#define ED_AVL 0
#define ED_RB 1

struct set_{
    int estrutura;
    AVL *avl; // Estrutura = 0
    RB *rb; // Estrutura = 1
};

/*
Cria um novo set, alocando o espaço apenas para a estrutura escolhida.
Esse conjunto é retornado.
*/
SET *set_criar(int estrutura_escolhida) {
    SET *set = (SET *) malloc(sizeof(SET));
    if (set == NULL)
        return NULL;

    set->avl = NULL;
    set->rb = NULL;
    set->estrutura = estrutura_escolhida;

    if (estrutura_escolhida == ED_AVL)
        set->avl = avl_criar();
    else if (estrutura_escolhida == ED_RB)
        set->rb = rb_criar();

    return set;
}

/* Apaga a memória alocada para o set e o espaço alocado para a estrutura da árvore usada. */
void set_apagar(SET **set) {
    if (*set == NULL)
        return;
    
    if ((*set)->estrutura == ED_AVL)
        avl_apagar_arvore(&(*set)->avl);
    else
        rb_apagar_arvore(&(*set)->rb);

    free(*set);
    *set = NULL;
}

/* Insere o elemento na estrutura escolhida. */
bool set_inserir(SET *set, int chave) {
    if (set->estrutura == ED_AVL)
        avl_inserir(set->avl, chave);
    else
        rb_inserir(set->rb, chave);  
}

/* Remove o elemento da estrutura escolhida. */
bool set_remover(SET *set, int chave) {
    if (set->estrutura == ED_AVL)
        avl_remover(set->avl, chave);
    else
        rb_remover(set->rb, chave);  
}

/* 
Verifica se o elemento de valor igual a chave pertence ao set.
Retorna verdadeiro ou falso.
*/
bool set_pertence(SET *set, int chave) {
    if (set->estrutura == ED_AVL)
        avl_buscar(set->avl, chave);
    else
        rb_buscar(set->rb, chave);  
}

/*
Cria um novo set com elementos igual a união dos conjuntos A e B. 
O set criado é retornado.
*/
SET *set_uniao(SET *A, SET *B){
    int estrutura = A->estrutura;

    /* Não passar estrutura para não alocar espaço para a árvore.
    * A árvore é criada em avl/rb unir() */
    SET *uniao = set_criar(-1);
    if (uniao == NULL)
        return NULL;

    uniao->estrutura = estrutura;
    
    if (estrutura == ED_AVL)
        uniao->avl = avl_unir(A->avl, B->avl);
    else
        uniao->rb = rb_unir(A->rb, B->rb);

    return uniao;
}

/*
Cria um novo set com elementos igual a intersecção dos conjuntos A e B. 
O set criado é retornado.
*/
SET *set_intersecao(SET *A, SET *B){
    int estrutura = A->estrutura;

    /* Não passar estrutura para não alocar espaço para a árvore.
    * A árvore é criada em avl/rb interseccao() */
    SET *intersecao = set_criar(-1);
    if (intersecao == NULL)
        return NULL;
    
    intersecao->estrutura = estrutura;

    if (estrutura == ED_AVL)
        intersecao->avl = avl_inter(A->avl, B->avl);
    else
        intersecao->rb = rb_inter(A->rb, B->rb);

    return intersecao;
}

/* Imprime os elementos do set. */
void set_imprimir(SET *set){
    if (set == NULL)
        printf("Conjunto vazio.\n");
    
    if (set->estrutura == ED_AVL) {
        if(avl_eh_vazia(set->avl))
            printf("Conjunto vazio.\n");
        else
            avl_imprimir(set->avl);
    }
    else {
        if(rb_eh_vazia(set->rb))
            printf("Conjunto vazio.\n");
        else
            rb_imprimir(set->rb);
    }
}
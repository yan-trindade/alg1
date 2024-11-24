#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "rb.h"


#define VERMELHO true
#define PRETO false

struct no_{
    int chave;
    bool cor;
    NO *esq;
    NO *dir;
};

struct rb_ {
    NO *raiz;
};

typedef struct no_ NO;
typedef struct rb_ RB;


NO * criar_no(int chave, bool cor){
    NO *no = (NO *)malloc(sizeof(NO));
    if(no != NULL){
        no->chave = chave;
        no->cor = cor;
        no->esq = no->dir = NULL;
    }
    return no;
}


bool eh_vermelho(NO *no){
    if(no == NULL) 
        return PRETO;
    return no->cor == VERMELHO;
}


NO * rotacionar_esquerda(NO *a){
    NO *b = a->dir;
    a->dir = b->esq;
    b->esq = a;
    b->cor = a->cor;
    a->cor = VERMELHO;
    return b;
}


NO * rotacionar_direita(NO *a){
    NO *b = a->esq;
    a->esq = b->dir;
    b->dir = a;
    b->cor = a->cor;
    a->cor = VERMELHO;
    return b;
}


void inverter_cores(NO *no){
    no->cor = VERMELHO;
    if(no->esq) 
        no->esq->cor = PRETO;
    if(no->dir) 
        no->dir->cor = PRETO;
}


NO * balancear(NO *no){
    if(eh_vermelho(no->dir) && !eh_vermelho(no->esq))
        no = rotacionar_esquerda(no);
    if(eh_vermelho(no->esq) && eh_vermelho(no->esq->esq))
        no = rotacionar_direita(no);
    if(eh_vermelho(no->esq) && eh_vermelho(no->dir))
        inverter_cores(no);
    return no;
}


NO * inserir_no(NO *no, int chave){
    if(no == NULL)
        return criar_no(chave, VERMELHO);

    if(chave < no->chave)
        no->esq = inserir_no(no->esq, chave);
    else if(chave > no->chave)
        no->dir = inserir_no(no->dir, chave);

    no = balancear(no);
    return no;
}


RB * rb_criar(void){
    RB *t = (RB *)malloc(sizeof(RB));
    if(t != NULL) 
        t->raiz = NULL;
    return t;
}


bool rb_inserir(RB *t, int chave){
    if(t == NULL) 
        return false;

    t->raiz = inserir_no(t->raiz, chave);
    t->raiz->cor = PRETO;  // A raiz deve ser sempre preta
    return true;
}


void apagar_no(NO **no){
    if(*no != NULL){
        apagar_no(&(*no)->esq);
        apagar_no(&(*no)->dir);
        free(*no);
        *no = NULL;
    }
}


bool rb_apagar_arvore(RB **t){
    if(t == NULL || *t == NULL) 
        return false;

    apagar_no(&(*t)->raiz);
    free(*t);
    *t = NULL;
    return true;
}


bool buscar_no(NO *no, int chave){
    if(no == NULL) 
        return false;

    if(chave < no->chave)
        return buscar_no(no->esq, chave);
    else if(chave > no->chave)
        return buscar_no(no->dir, chave);

    return true;
}


bool rb_buscar(RB *t, int chave){
    if(t == NULL) 
        return false;

    return buscar_no(t->raiz, chave);
}


void imprimir(NO *no){
    if(no != NULL){
        imprimir(no->esq);
        printf("%d ", no->chave);
        imprimir(no->dir);
    }
}


void rb_imprimir(RB *t){
    if(t == NULL || t->raiz == NULL){
        //printf("Conjunto vazio.\n");
        return;
    }
    //printf("ARVORE EM-ORDEM: ");
    imprimir(t->raiz);
    printf("\n");
}


NO *mover_vermelho_esquerda(NO *no){
    inverter_cores(no);
    if(no->dir != NULL && eh_vermelho(no->dir->esq)){
        no->dir = rotacionar_direita(no->dir);
        no = rotacionar_esquerda(no);
        inverter_cores(no);
    }
    return no;
}


NO * mover_vermelho_direita(NO *no){
    inverter_cores(no);
    if(no->esq != NULL && no->esq->esq != NULL && eh_vermelho(no->esq->esq)){
        no = rotacionar_direita(no);
        inverter_cores(no);
    }
    return no;
}


NO * menor_no(NO *no){
    while (no->esq != NULL){
        no = no->esq;
    }
    return no;
}


NO * remover_menor(NO **no){
    if((*no)->esq == NULL){
        free(*no);
        *no = NULL;
        return NULL;
    }

    if((*no)->esq != NULL && !eh_vermelho((*no)->esq) && ((*no)->esq->esq == NULL || !eh_vermelho((*no)->esq->esq)))
        *no = mover_vermelho_esquerda(*no);
    
    (*no)->esq = remover_menor(&(*no)->esq);
    return balancear(*no);
}


NO * remover_no(NO **no, int chave){
    if(chave < (*no)->chave){
        if((*no)->esq != NULL && !eh_vermelho((*no)->esq) && ((*no)->esq->esq == NULL || !eh_vermelho((*no)->esq->esq)))
            *no = mover_vermelho_esquerda(*no);

        if((*no)->esq != NULL)
            (*no)->esq = remover_no(&(*no)->esq, chave);
    } 
    else{
        if((*no)->esq != NULL && eh_vermelho((*no)->esq))
            *no = rotacionar_direita(*no);

        if(chave == (*no)->chave && (*no)->dir == NULL){
            free(*no);
            *no = NULL;
            return NULL;
        }

        if((*no)->dir != NULL && !eh_vermelho((*no)->dir) && ((*no)->dir->esq == NULL || !eh_vermelho((*no)->dir->esq)))
            *no = mover_vermelho_direita(*no);
        

        if (chave == (*no)->chave){
            NO *x = menor_no((*no)->dir);
            (*no)->chave = x->chave;
            (*no)->dir = remover_menor(&(*no)->dir);
        } 
        else if((*no)->dir != NULL)
            (*no)->dir = remover_no(&(*no)->dir, chave);
    }

    return balancear(*no);
}


bool rb_remover(RB *t, int chave){
    if(t == NULL || t->raiz == NULL) 
        return false;

    if(!rb_buscar(t, chave)) 
        return false;

    t->raiz = remover_no(&(t->raiz), chave);

    if(t->raiz != NULL)
        t->raiz->cor = PRETO;

    return true;
}



//Daqui pra frente funcoes criadas pra ajudar nos conjutos!!!!


bool rb_eh_vazia(RB *t){
    return (t == NULL || t->raiz == NULL);
}

void inserir_todos_elementos2(NO *raiz, RB *destino){
    if(raiz == NULL)
        return;
    rb_inserir(destino, raiz->chave);
    inserir_todos_elementos2(raiz->esq, destino);
    inserir_todos_elementos2(raiz->dir, destino);
}

RB * rb_unir(RB *a, RB *b){
    RB *c = rb_criar();
    if(c != NULL){
        if(a->raiz != NULL)
            inserir_todos_elementos2(a->raiz, c);
        if(b->raiz != NULL)    
            inserir_todos_elementos2(b->raiz, c);
    }

    return c;
}

void compara_igual_insere2(NO *raiz, RB *a, RB *inter){
    if(raiz == NULL)
        return;
    if(rb_buscar(a, raiz->chave))
        rb_inserir(inter, raiz->chave);
    
    compara_igual_insere2(raiz->esq, a, inter);
    compara_igual_insere2(raiz->dir, a, inter);

}


RB * rb_inter(RB *a, RB *b){
    RB *inter = rb_criar();
    if(a != NULL && b != NULL){
        compara_igual_insere2(a->raiz, b, inter);
    }
    return inter;
}
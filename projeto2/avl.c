#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//#define max(a,b)  (a >= b ? a : b)

typedef struct no_ NO;
typedef struct avl_ AVL;

struct no_{
    int chave;
    NO * esq;
    NO * dir;
    int FB;
};

struct avl_{
    NO * raiz;
};

int max(int a, int b){
    return(a >= b ? a : b);
}

AVL * avl_criar(void){
    AVL * t = (AVL *)malloc(sizeof(AVL));
    if(t != NULL){
        t->raiz = NULL;
    }
    return t;
}

NO * avl_cria_no(int chave){
    NO * no = (NO *)malloc(sizeof(NO));
    if(no != NULL){
        no->chave = chave;
        no->esq = NULL;
        no->dir = NULL;
        no->FB = 0;
    }
    return no;
}

NO * rodar_direita(NO *a){
    NO * b = a->esq;
    a->esq = b->dir;
    b->dir = a;

    a->FB = b->FB = 0;

    return b;
}

NO * rodar_esquerda(NO *a){
    NO * b = a->dir;
    a->dir = b->esq;
    b->esq = a;

    a->FB = b->FB = 0;

    return b;
}

NO * rodar_esquerda_direita(NO *a){
    a->esq = rodar_esquerda(a->esq);
    return(rodar_direita(a));
}

NO * rodar_direita_esquerda(NO *a){
    a->dir = rodar_direita(a->dir);
    return(rodar_esquerda(a));
}

int avl_altura(NO *raiz){
    if(raiz == NULL)
        return 0;
    else{
        return (1 + max(avl_altura(raiz->esq), avl_altura(raiz->dir)));
    }
}

NO * avl_inserir_no(NO *raiz, int chave){
    if(raiz == NULL)
        raiz = avl_cria_no(chave);
    else if(chave < raiz->chave)
        raiz->esq = avl_inserir_no(raiz->esq, chave);
    else if(chave > raiz->chave)
        raiz->dir = avl_inserir_no(raiz->dir, chave);

    raiz->FB = (avl_altura(raiz->esq) - avl_altura(raiz->dir));

    if(raiz->FB == 2){
        if(raiz->esq->FB >= 0)
            raiz = rodar_direita(raiz);
        else
            raiz = rodar_esquerda_direita(raiz);
    }
    if(raiz->FB == -2){
        if(raiz->dir->FB <= 0)
            raiz = rodar_esquerda(raiz);
        else
            raiz = rodar_direita_esquerda(raiz);
    }

    return raiz;
}

bool avl_inserir(AVL *t, int chave){
    return((t->raiz = avl_inserir_no(t->raiz, chave)) != NULL);
}

void troca_max_esq(NO *subarvore, NO *pai, NO *removido) {
    NO *atual = subarvore;
    NO *anterior = pai;
    while (atual->dir != NULL){
        anterior = atual;
        atual = atual->dir;
    }

    removido->chave = atual->chave;

    if(anterior->dir == atual)
        anterior->dir = atual->esq;
    else
        anterior->esq = atual->esq;

    free(atual);
    atual = NULL;
}

NO * avl_remover_no(NO **raiz, int chave){
    NO * aux;

    if(*raiz == NULL)
        return NULL;
    if(chave == (*raiz)->chave){
        if((*raiz)->esq == NULL || (*raiz)->dir == NULL){
            aux = *raiz;
            if((*raiz)->esq == NULL)
                *raiz = (*raiz)->dir;
            else
                *raiz = (*raiz)->esq;

            free(aux);
            aux = NULL;
        }
        else
            troca_max_esq((*raiz)->esq, (*raiz), (*raiz));
        
    }
    else if(chave < (*raiz)->chave)
        (*raiz)->esq = avl_remover_no(&(*raiz)->esq, chave);
    else if(chave > (*raiz)->chave)
        (*raiz)->dir = avl_remover_no(&(*raiz)->dir, chave);
        

    if((*raiz) != NULL){
        (*raiz)->FB = (avl_altura((*raiz)->esq) - avl_altura((*raiz)->dir));

        if((*raiz)->FB == 2){
            if((*raiz)->esq->FB >= 0)
                rodar_direita(*raiz);
            else
                rodar_esquerda_direita(*raiz);
        }
        if((*raiz)->FB == -2){
            if((*raiz)->dir <= 0)
                rodar_esquerda(*raiz);
            else
                rodar_direita_esquerda(*raiz);
        }
    }

    return(*raiz);
    
}

bool avl_remover(AVL *t, int chave){
    return((t->raiz = avl_remover_no(&t->raiz, chave)) != NULL);
}

void apagar_arvore(NO **no){
    if(*no != NULL){
        apagar_arvore(&(*no)->esq);
        apagar_arvore(&(*no)->dir);
        free(*no);
        *no = NULL;
    }
}

void avl_apagar_arvore(AVL **t){
    if(*t != NULL)
        apagar_arvore(&(*t)->raiz);
    free(*t);
    *t = NULL;
}

bool avl_buscar_no(NO *raiz, int chave){
    if(raiz == NULL)
        return false;
    else if(raiz->chave == chave)
        return true;
    else if(chave < raiz->chave)
        avl_buscar_no(raiz->esq, chave);
    else if(chave > raiz->chave)
        avl_buscar_no(raiz->dir, chave);
}

bool avl_buscar(AVL *t, int chave){
    return(avl_buscar_no(t->raiz, chave));
}

void imprimir_no(NO *raiz){
    if(raiz != NULL){
        imprimir_no(raiz->esq);
        printf("%d ", raiz->chave);
        imprimir_no(raiz->dir);
    }
}

void avl_imprimir(AVL *t){
    if(t != NULL){
        //printf("ARVORE EM-ORDEM: ");
        imprimir_no(t->raiz);
        printf("\n");
    }
}



//Daqui pra frente funcoes criadas pra ajudar nos conjutos!!!!


void inserir_todos_elementos(NO *raiz, AVL *destino){
    if(raiz == NULL)
        return;
    avl_inserir(destino, raiz->chave);
    inserir_todos_elementos(raiz->esq, destino);
    inserir_todos_elementos(raiz->dir, destino);
}

AVL * avl_unir(AVL *a, AVL *b){
    AVL *c = avl_criar();
    if(c != NULL){
        if(a->raiz != NULL)
            inserir_todos_elementos(a->raiz, c);
        if(b->raiz != NULL)    
            inserir_todos_elementos(b->raiz, c);
    }

    return c;
}

void compara_igual_insere(NO *raiz, AVL *a, AVL *inter){
    if(raiz == NULL)
        return;
    if(avl_buscar(a, raiz->chave))
        avl_inserir(inter, raiz->chave);
    
    compara_igual_insere(raiz->esq, a, inter);
    compara_igual_insere(raiz->dir, a, inter);

}


AVL * avl_inter(AVL *a, AVL *b){
    AVL *inter = avl_criar();
    if(a != NULL && b != NULL){
            compara_igual_insere(a->raiz, b, inter);
    }
    return inter;
}

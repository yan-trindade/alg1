#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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

/* Aloca a memória necessária para a estrutura avl_. Caso foi possivel alocar, a raíz é recebe NULL.
* O ponteiro para a árvore é retornado. */
AVL * avl_criar(void){
    AVL * t = (AVL *) malloc(sizeof(AVL));
    if(t != NULL){
        t->raiz = NULL;
    }
    return t;
}

/* Cria um novo ponteiro para a estrutura no_, setando os valores padrões.
* O ponteiro é retornado. */
NO * avl_cria_no(int chave){
    NO * no = (NO *) malloc(sizeof(NO));
    if(no != NULL){
        no->chave = chave;
        no->esq = NULL;
        no->dir = NULL;
        no->FB = 0;
    }
    return no;
}

/* Função para rotacionar o nó "a" para a direita;
* É tomado o cuidando para não perder as subárvores dos filhos dos nós relacionados com a rotação.
* Os nós recebem 0 para o fator de balanceamento, resultado da rotação. 
* O nó b, que tomou a posição de "raiz" do nó a, é retornado para poder ser conectado com a árvore. */
NO * rodar_direita(NO *a){
    NO * b = a->esq;
    a->esq = b->dir;
    b->dir = a;

    a->FB = b->FB = 0;

    return b;
}

/* Função para rotacionar o o nó "a" para a esquerda
* É tomado o cuidando para não perder as subárvores dos filhos dos nós relacionados com a rotação.
* Os nós recebem 0 para o fator de balanceamento, resultado da rotação. 
* O nó b, que tomou a posição de "raiz" do nó a, é retornado para poder ser conectado com a árvore. */
NO * rodar_esquerda(NO *a){
    NO * b = a->dir;
    a->dir = b->esq;
    b->esq = a;

    a->FB = b->FB = 0;

    return b;
}

/* Rotacionar, a partir do nó a, para a esquerda e direita. 
* Primeiramente, é rotacionado o nó a esquerda de "a", seguido da rotação de "a" para a direita. 
* O retorno de rodar_direita() é retornado.
*/
NO * rodar_esquerda_direita(NO *a){
    a->esq = rodar_esquerda(a->esq);
    return(rodar_direita(a));
}

/* Rotacionar, a partir do nó a, para a direita e esquerda. 
* Primeiramente, é rotacionado o nó a direita de "a", seguido da rotação de "a" para a esquerda. 
* O retorno de rodar_esquerda() é retornado.
*/
NO * rodar_direita_esquerda(NO *a){
    a->dir = rodar_direita(a->dir);
    return(rodar_esquerda(a));
}

/* Retorna a altura do nó passado como parâmetro. 
* Essa altura é obtida recursivamente, percorrendo todas as subárvores até os nós folhas.
* Em cada subárvore, é obtido o maior caminho até um nó folha.
*/
int avl_altura(NO *raiz){
    if(raiz == NULL)
        return 0;
    else{
        return (1 + max(avl_altura(raiz->esq), avl_altura(raiz->dir)));
    }
}

/* Função para inserir um novo nó na árvore. 
* Inicialmente é buscado a chave na árvore. Na posição correta, é inserido..
* Para o nó inserido e todos os nós anteriores a ele, é recalculado o FB e verificado se é necessário rotacionar.
* O nó inserido (raiz) é retornado para ser encadeado na árvore AVL. 
*/
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

/* Função pública para inserção. Passa a raíz para a função avl_inserir_no().*/
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

/* Remove a chave da árvore. É feito uma busca para encontrar o elemento na árvore.
* Caso ele tenha até uma subárvore, ela é encadeada como filho do pai do nó da chave removida.
* Se não, o elemento maior da subárvore esquerda do elemento com a chave buscada é substituido no lugar dele.
* Por fim, é recalculado o FB e verificado se é necessário fazer rebalanceamentos. 
*/
NO * avl_remover_no(NO **raiz, int chave){
    if(*raiz == NULL)
        return NULL;

    if(chave == (*raiz)->chave){
        if((*raiz)->esq == NULL || (*raiz)->dir == NULL){
            NO *aux = *raiz;
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

/* Função pública para remoção da chave. */
bool avl_remover(AVL *t, int chave){
    return((t->raiz = avl_remover_no(&t->raiz, chave)) != NULL);
}

/* Apaga a árvore e os nós utilizados. */
void apagar_arvore(NO **no){
    if(*no != NULL){
        apagar_arvore(&(*no)->esq);
        apagar_arvore(&(*no)->dir);
        free(*no);
        *no = NULL;
    }
}

/* Apaga a árvore e os nós utilizados. */
void avl_apagar_arvore(AVL **t){
    if(*t == NULL)
        return;
    
    apagar_arvore(&(*t)->raiz);
    free(*t);
    *t = NULL;
}

/* Busca a chave na AVL.*/
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

/* Busca a chave na AVL.*/
bool avl_buscar(AVL *t, int chave){
    return(avl_buscar_no(t->raiz, chave));
}

/* Percorre a árvore no percurso em-ordem, imprimindo os nós. */
void imprimir_no(NO *raiz){
    if(raiz != NULL){
        imprimir_no(raiz->esq);
        printf("%d, ", raiz->chave);
        imprimir_no(raiz->dir);
    }
}

/* Imprimindo os nós da árvore. */
void avl_imprimir(AVL *t){
    if(t != NULL){
        imprimir_no(t->raiz);
        printf("\n");
    }
}

/* *********************************
Daqui pra frente funcoes criadas pra ajudar nos conjutos!!!!
************************************ */

/* Insere todos os elementos na arvore "destino". A inserção é feita na ordem pré-ordem. 
* Caso um elemento já esteja inserido, a função avl_inserir() garante que não ele não vai ser inserido novamente.
*/
void inserir_todos_elementos(NO *raiz, AVL *destino){
    if(raiz == NULL)
        return;
    avl_inserir(destino, raiz->chave);
    inserir_todos_elementos(raiz->esq, destino);
    inserir_todos_elementos(raiz->dir, destino);
}

/* Cria uma nova árvore e insere todos os elementos de "a" seguido dos elementos de "b". */
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

/* Verifica se a chave de "raiz" (da árvore "a") está presente na árvore "b".
* Se o retorno de avl_buscar() é true, então é inserido na nova árvore.
* É feito essa checagem para todos os elementos de "a". 
*/
void compara_igual_insere(NO *raiz, AVL *b, AVL *inter){
    if(raiz == NULL)
        return;

    if(avl_buscar(b, raiz->chave))
        avl_inserir(inter, raiz->chave);
    
    compara_igual_insere(raiz->esq, b, inter);
    compara_igual_insere(raiz->dir, b, inter);

}

/* Cria uma nova árvore com a intersecção entre "a" e "b". */
AVL * avl_inter(AVL *a, AVL *b){
    AVL *inter = avl_criar();
    if(a != NULL && b != NULL){
        compara_igual_insere(a->raiz, b, inter);
    }
    return inter;
}

/* Verifica se a AVL não possui elementos. */
bool avl_eh_vazia(AVL *t){
    if(t->raiz == NULL)
        return true;
    return false;
}

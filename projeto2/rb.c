#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "rb.h"

#define VERMELHO true
#define PRETO false

typedef struct no_ NO;
typedef struct rb_ RB;

/* A árvore é constituída dessa estrutura. */
struct no_{
    int chave;
    bool cor; // Vermelho (true) ou Preto (false)
    NO *esq;
    NO *dir;
};

struct rb_ {
    NO *raiz;
};

/* Cria um novo ponteiro para a estrutura no_, setando os valores padrões.
* O ponteiro é retornado. */
NO * criar_no(int chave, bool cor){
    NO *no = (NO *) malloc(sizeof(NO));
    if(no != NULL){
        no->chave = chave;
        no->cor = cor;
        no->esq = no->dir = NULL;
    }
    return no;
}

/* Aloca a memória necessária para a estrutura rb_. Caso foi possivel alocar, a raíz recebe NULL.
* O ponteiro para a árvore é retornado. */
RB * rb_criar(void){
    RB *t = (RB *) malloc(sizeof(RB));
    if(t != NULL) 
        t->raiz = NULL;
    return t;
}

/* Apaga todos os nós da árvore, seguindo um percurso pós-ordem. */
void apagar_no(NO **no){
    if(*no != NULL){
        apagar_no(&(*no)->esq);
        apagar_no(&(*no)->dir);
        free(*no);
        *no = NULL;
    }
}

/* Apaga a árvore e os nós utilizados. */
bool rb_apagar_arvore(RB **t){
    if(t == NULL || *t == NULL) 
        return false;

    apagar_no(&(*t)->raiz);
    free(*t);
    *t = NULL;
    return true;
}

/* Verifica se o nó e vermelho. */
bool eh_vermelho(NO *no){
    if(no == NULL) 
        return PRETO;
    return no->cor == VERMELHO;
}

/* Função para rotacionar o o nó "a" para a esquerda
* É tomado o cuidado para não perder as subárvores dos filhos dos nós relacionados com a rotação.
* O nó b, que tomou a posição de "raiz" do nó a, recebe a cor de "a" e é retornado para poder ser conectado com a árvore. */
NO * rotacionar_esquerda(NO *a){
    NO *b = a->dir;
    a->dir = b->esq;
    b->esq = a;
    b->cor = a->cor;
    a->cor = VERMELHO; // Sempre vermelho
    return b;
}

/* Função para rotacionar o nó "a" para a direita;
* É tomado o cuidado para não perder as subárvores dos filhos dos nós relacionados com a rotação.
* O nó b, que tomou a posição de "raiz" do nó a, recebe a cor de "a" e é retornado para poder ser conectado com a árvore. */
NO * rotacionar_direita(NO *a){
    NO *b = a->esq;
    a->esq = b->dir;
    b->dir = a;
    b->cor = a->cor;
    a->cor = VERMELHO; // Sempre vermelho
    return b;
}

/* Seta a cor da aresta do nó para vermelho, e os filhos para preto. */
void inverter_cores(NO *no){
    no->cor = VERMELHO;
    if(no->esq != NULL) 
        no->esq->cor = PRETO;
    if(no->dir != NULL) 
        no->dir->cor = PRETO;
}

/* Verifica se é necessário fazer o balanceamento. Há três casos:
    - Caso 1:  o nó da direita é vermelho e o da esquerda é preto. Esse caso quebra a regra apenas filhos esquerdos possuem aresta vermelha. Assim, é feito a rotação para esquerda.

    - Caso 2: o nó da esquerda, e o filho esquerdo desse nó são vermelhos. Esse caso quebra a regra que não pode haver dois nós com arestas vermelhas seguidos. Assim, é feito rotação para direita.

    - Caso 3: Se as arestas dos dois nós filhos de "no" são vermelhas. Assim, é necessário inverter a cor do nó.

Se o nó não se encaixar em nenhum desses casos, ele apenas é retornado. */
NO * balancear(NO *no){
    if(eh_vermelho(no->dir) && !eh_vermelho(no->esq))
        no = rotacionar_esquerda(no);
    if(eh_vermelho(no->esq) && eh_vermelho(no->esq->esq))
        no = rotacionar_direita(no);
    if(eh_vermelho(no->esq) && eh_vermelho(no->dir))
        inverter_cores(no);
    return no;
}

/* É feito a posição de inserção na árvore. Quando encontrado, é criado um nó com a chave. Após a inserção, é verificado para ele, e para todos os nós anteriores (na volta da recursão) se é necessário fazer o balanceamento da árvore.
*/
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

/* Insere chave na árvore. */
bool rb_inserir(RB *t, int chave){
    if(t == NULL) 
        return false;

    t->raiz = inserir_no(t->raiz, chave);
    t->raiz->cor = PRETO;  // A raiz deve ser sempre preta
    return true;
}

/* Busca a chave na RB.*/
bool buscar_no(NO *no, int chave){
    if(no == NULL) 
        return false;

    if(chave < no->chave)
        return buscar_no(no->esq, chave);
    else if(chave > no->chave)
        return buscar_no(no->dir, chave);

    return true;
}

/* Busca a chave na RB.*/
bool rb_buscar(RB *t, int chave){
    if(t == NULL) 
        return false;

    return buscar_no(t->raiz, chave);
}

/* Percorre a árvore no percurso em-ordem, imprimindo os nós. */
void imprimir(NO *no){
    if(no != NULL){
        imprimir(no->esq);
        printf("%d, ", no->chave);
        imprimir(no->dir);
    }
}

/* Imprime os nós da árvore. */
void rb_imprimir(RB *t){
    if(t == NULL || t->raiz == NULL) {
        return;
    }
    
    imprimir(t->raiz);
    printf("\n");
}

/* A propagação ocorre apenas quando o esq, esq->esq são pretas.
    Se dir->esq for preta:
        - inverte as cores
    Se não:
        - inverte as cores 
        - rotacionar para direita o nó direito
        - rotacionar o nó para esquerda
        - inverter as cores novamente. 
*/
NO *mover_vermelho_esquerda(NO *no){
    // Verificar se as subárvores existem
    if (no->esq && no->dir && no->dir->esq && no->esq->esq) {
        if (!eh_vermelho(no->esq) && !eh_vermelho(no->esq->esq)) {
            inverter_cores(no); // Primeiro passo para ambos casos
            if (eh_vermelho(no->dir->esq)) {
                no->dir = rotacionar_direita(no->dir);
                no = rotacionar_esquerda(no);
                inverter_cores(no);
            }
        }
    }
    return no;
}

/* A propagação ocorre apenas quando o dir, dir->esq são pretas.
    Se esq for vermelha, é necessário fazer uma rotação pra direita

    Se esq->esq for preta:
        - inverte as cores
    Se não:
        - inverte as cores 
        - rotacionar para direita o nó direito
        - rotacionar o nó para esquerda
        - inverter as cores novamente. 
*/
NO * mover_vermelho_direita(NO *no){
    // Verificar se as subárvores existem
    if (no->esq && no->dir && no->dir->esq && no->esq->esq) {
        if (eh_vermelho(no->esq))
            no = rotacionar_direita(no);
        if (!eh_vermelho(no->dir) && !eh_vermelho(no->dir->esq)) {
            inverter_cores(no);
            if (eh_vermelho(no->esq->esq)) {
                no = rotacionar_direita(no);
                inverter_cores(no);
            }
        }
    }
    return no;
}

/* Retorna o menor nó a partir da raiz passada. */
NO * menor_no(NO *raiz){
    while (raiz->esq != NULL){
        raiz = raiz->esq;
    }
    return raiz;
}

/* Até não encontramos o menor, verificamos se o filho esquerdo e o filho esquerdo esquerdo são pretos. Nesse caso, é propagado a aresta para a esquerda (direção do menor elemento). Após isso, é chamado recursivamente com o filho da esquerda. 

Quando o elemento é encontrado, ele é removido.

No fim da recursão, o nó atual é balanceado.
*/
NO * remover_menor(NO **no){
    if((*no)->esq == NULL){
        // Nó atual é o menor
        free(*no);
        *no = NULL;
        return NULL;
    }

    if(!eh_vermelho((*no)->esq) && !eh_vermelho((*no)->esq->esq))
        *no = mover_vermelho_esquerda(*no);
    
    (*no)->esq = remover_menor(&(*no)->esq);
    return balancear(*no);
}

/* Apenas se o elemento estiver na árvore essa função é chamada. 
* Existem três casos na remoção: 
- Caso 1: sem nenhuma subárvore
- Caso 2: uma subárvore
- Caso 3: duas subárvores

Nos dois primeiros casos, o nó pode ser considerado como uma folha, ajustando apenas o encadeamento da subárvore não nula (no caso 2) como filho do pai do nó que estamos removendo. 

No terceiro caso, o nó não pode ser simplesmente removido. Primeiramente precisamos propagar a aresta vermelha para a direita; em seguida, trocar a raiz com o menor elemento da subárvore direita da raiz, e em seguida, remover o menor elemento da subárvore direita. 

Na volta da recursão, a arvore é balanceda.

Caso o nó atual não seja o que queremos remover, é necessário propagar a aresta vermelha para o lado que a chave está.
*/
NO * remover_no(NO **raiz, int chave){
    if(*raiz == NULL)
        return NULL;

    if(chave == (*raiz)->chave){
        if((*raiz)->esq == NULL || (*raiz)->dir == NULL){
            // Caso 1 ou 2 subárvores
            NO *aux = *raiz;
            if((*raiz)->esq == NULL)
                *raiz = (*raiz)->dir;
            else
                *raiz = (*raiz)->esq;

            free(aux);
            aux = NULL;
        }
        else {
            // Caso 2 subárvores não-nulas
            *raiz = mover_vermelho_direita(*raiz);
            NO *x = menor_no((*raiz)->dir);
            (*raiz)->chave = x->chave;
            (*raiz)->dir = remover_menor(&(*raiz)->dir);
        }
    }
    else if(chave < (*raiz)->chave) {
        // Chave está para esquerda
        *raiz = mover_vermelho_esquerda(*raiz);
        (*raiz)->esq = remover_no(&(*raiz)->esq, chave);
    }
    else if(chave > (*raiz)->chave) {
        // Chave está para direita
        *raiz = mover_vermelho_direita(*raiz);
        (*raiz)->dir = remover_no(&(*raiz)->dir, chave);
    }
    
    // Balancear na volta da recursão.
    if(*raiz != NULL)
        *raiz = balancear(*raiz);
    
    return(*raiz);
}

/* Verifica se o elemento está presente na árvore, removendo-o. */
bool rb_remover(RB *t, int chave){
    if(t == NULL || t->raiz == NULL) 
        return false;

    if(!rb_buscar(t, chave)) 
        return false;

    t->raiz = remover_no(&(t->raiz), chave);

    if(t->raiz != NULL)
        t->raiz->cor = PRETO; // Raiz sempre preta

    return true;
}


/* *********************************
Daqui pra frente funcoes criadas pra ajudar nos conjutos!!!!
************************************ */

/* Verifica se a RB não possui elementos. */
bool rb_eh_vazia(RB *t){
    return (t == NULL || t->raiz == NULL);
}

/* Insere todos os elementos na arvore "destino". A inserção é feita na ordem pré-ordem. 
* Caso um elemento já esteja inserido, a função rb_inserir() garante que não ele não vai ser inserido novamente.
*/
void rb_inserir_todos_elementos(NO *raiz, RB *destino){
    if(raiz == NULL)
        return;
    rb_inserir(destino, raiz->chave);
    rb_inserir_todos_elementos(raiz->esq, destino);
    rb_inserir_todos_elementos(raiz->dir, destino);
}

/* Cria uma nova árvore e insere todos os elementos de "a" seguido dos elementos de "b". */
RB * rb_unir(RB *a, RB *b){
    RB *c = rb_criar();
    if(c != NULL){
        if(a->raiz != NULL)
            rb_inserir_todos_elementos(a->raiz, c);
        if(b->raiz != NULL)    
            rb_inserir_todos_elementos(b->raiz, c);
    }

    return c;
}

/* Verifica se a chave de "raiz" (da árvore "a") está presente na árvore "b".
* Se o retorno de rb_buscar() é true, então é inserido na nova árvore.
* É feito essa checagem para todos os elementos de "a". 
*/
void rb_compara_igual_insere(NO *raiz, RB *b, RB *inter){
    if(raiz == NULL)
        return;
    if(rb_buscar(b, raiz->chave))
        rb_inserir(inter, raiz->chave);
    
    rb_compara_igual_insere(raiz->esq, b, inter);
    rb_compara_igual_insere(raiz->dir, b, inter);
}

/* Cria uma nova árvore com a intersecção entre "a" e "b". */
RB * rb_inter(RB *a, RB *b){
    RB *inter = rb_criar();
    if(a != NULL && b != NULL){
        rb_compara_igual_insere(a->raiz, b, inter);
    }
    return inter;
}
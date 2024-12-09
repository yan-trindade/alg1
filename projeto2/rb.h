#ifndef RB_H
    #define RB_H
    
    #include <stdbool.h>
    #include <stdlib.h>
    #include <stdio.h>

    typedef struct rb_ RB;
    typedef struct no_ NO;

    /* Cria uma nova árvore rubro-negra. O ponteiro para ela é retornado. */
    RB * rb_criar(void);

    /* Insere a chave na árvore t. 
    * Retorna `true` se a inserção foi realizada com sucesso; caso contrário, retorna `false`.*/
    bool rb_inserir(RB *t, int chave);

    /* Remove a chave na árvore t. 
    * Retorna `true` se a remoção foi realizada com sucesso; caso contrário, retorna `false`.*/
    bool rb_remover(RB *t, int chave);

    /* Libera a memória utilizada para a árvore. 
    * O parâmetro deve ser o endereço do ponteiro para a árvore, permitindo liberar corretamente a memória.
    * Retorna `true` se foi possível apagar a árvore; caso contrário, retorna `false`.*/
    bool rb_apagar_arvore(RB **t);

    /* Busca a chave na árvore.
    * Retorna `true` se a remoção foi realizada com sucesso; caso contrário, retorna `false`.*/
    bool rb_buscar(RB *t, int chave);

    /* Imprime todos os elementos da árvore, seguindo um percurso em-ordem. */
    void rb_imprimir(RB *t);

    /* Verifica se a árvore está vazia. */
    bool rb_eh_vazia(RB *t);

    /* A função une duas árvores distintas em uma nova árvore. 
    * O ponteiro para a nova árvore é retornada.*/
    RB * rb_unir(RB *a, RB *b);

    /* A função cria uma nova árvore com os elementos em comum das duas árvores distintas. 
    * O ponteiro para a nova árvore é retornada.*/
    RB * rb_inter(RB *a, RB *b);

#endif
#ifndef AVL_H
    #define AVL_H
    
    // Bibliotecas necessárias para o funcionamento da ED
    #include <stdbool.h>
    #include <stdlib.h>
    #include <stdio.h>

    typedef struct avl_ AVL;

    /* Cria e retorna um ponteiro para a Árvore AVL*/
    AVL * avl_criar(void);

    /* Insere o elemento de chave passado pelo parâmetro da função. 
    * Retorna `true` se a inserção foi realizada com sucesso; caso contrário, retorna `false`.*/
    bool avl_inserir(AVL *t, int chave);

    /* Remove a chave passada da AVL. 
    * Retorna `true` se a remoção foi realizada com sucesso; caso contrário, retorna `false`. */
    bool avl_remover(AVL *t, int chave);
    
    /* Libera a memória utilizada para a AVL. 
    * É necessário passar o endereço do ponteiro para a desalocação correta. */
    void avl_apagar_arvore(AVL **t);
    
    /* Procura a chave na árvore t. 
    * Retorna `true` se o elemento está na AVL; caso contrário, retorna `false`.*/
    bool avl_buscar(AVL *t, int chave);
    
    /* Imprime todos os elementos da árvore através do percurso em-ordem. */
    void avl_imprimir(AVL *t);

    /* A função une os elementos de duas árvores distintas em uma nova árvore. 
    * O ponteiro para a nova árvore é retornada.*/
    AVL *avl_unir(AVL *a, AVL *b);

    /* A função cria uma nova árvore com os elementos em comum das duas árvores distintas. 
    * O ponteiro para a nova árvore é retornada.*/
    AVL * avl_inter(AVL *a, AVL *b);

    /* Retorna true se a AVL não possui elementos. */
    bool avl_eh_vazia(AVL *t);

#endif

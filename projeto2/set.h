#ifndef SET_H
    #define SET_H

    #include <stdbool.h>
    #include <stdlib.h>
    #include <stdio.h>

    typedef struct set_ SET;

    /* Cria um novo conjunto com a estrutura interna escolhida pelo parâmetro `estrutura_escolhida`. 
    * O valor 0 representa uma Árvore Binária AVL, e o valor 1 representa uma Árvore Binária Rubro-Negra.
    * Retorna um ponteiro para o conjunto criado ou NULL em caso de falha. */
    SET *set_criar(int estrutura_escolhida);

    /* Libera a memória alocada para o conjunto. 
    * O parâmetro deve ser o endereço do ponteiro para o conjunto, permitindo liberar corretamente a memória.
    * Não possui retorno. */
    void set_apagar(SET **set);

    /* Insere a chave especificada no conjunto. 
    * Retorna `true` se a inserção foi realizada com sucesso; caso contrário, retorna `false`.*/
    bool set_inserir(SET *set, int chave);

    /* Remove a chave do conjunto. 
    * Retorna `true` se a remoção foi realizada com sucesso; caso contrário, retorna `false`. */
    bool set_remover(SET *set, int chave);
    
    /* Verifica se a chave especificada pertence ao conjunto. 
    * Retorna `true` se a chave está presente; caso contrário, retorna `false`. */
    bool set_pertence(SET *set, int chave);

    /* Cria e retorna um novo conjunto representando o união de A e B */
    SET *set_uniao(SET *A, SET *B);

    /* Cria um novo conjunto representando a intersecção entre A e B */
    SET *set_intersecao(SET *A, SET *B);

    /* Imprime todos os elementos do conjunto, seguindo o percurso em-ordem */
    void set_imprimir(SET *set);

#endif

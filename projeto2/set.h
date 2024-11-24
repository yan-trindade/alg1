#ifndef SET_H
    #define SET_H

    #include<stdbool.h>
    #include<stdlib.h>
    #include "avl.h"


    typedef struct set_ SET;

    SET *set_criar(void);
    void set_apagar(SET **set);
    bool set_inserir(SET *set, int chave);
    bool set_remover(SET *set, int chave);
    bool set_pertence(SET *set, int chave);
    SET *set_uniao(SET *A, SET *B);
    SET *set_intersecao(SET *A, SET *B);
    void set_imprimir(SET *set);

#endif

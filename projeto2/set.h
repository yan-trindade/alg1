#ifndef SET_H
    #define SET_H

    #include<stdbool.h>
    #include<stdlib.h>
    #include "avl.h"
    #include "rb.h"


    typedef struct set_ SET;

    SET *set_avl_criar(void);
    void set_avl_apagar(SET **set);
    bool set_avl_inserir(SET *set, int chave);
    bool set_avl_remover(SET *set, int chave);
    bool set_avl_pertence(SET *set, int chave);
    SET *set_avl_uniao(SET *A, SET *B);
    SET *set_avl_intersecao(SET *A, SET *B);
    void set_avl_imprimir(SET *set);

    SET *set_rb_criar(void);
    void set_rb_apagar(SET **set);
    bool set_rb_inserir(SET *set, int chave);
    bool set_rb_remover(SET *set, int chave);
    bool set_rb_pertence(SET *set, int chave);
    SET *set_rb_uniao(SET *A, SET *B);
    SET *set_rb_intersecao(SET *A, SET *B);
    void set_rb_imprimir(SET *set);

#endif

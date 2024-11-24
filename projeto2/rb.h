#ifndef RB_H
    #define RB_H
    
    #include <stdbool.h>
    #include <stdlib.h>
    #include <stdio.h>

    typedef struct rb_ RB;
    typedef struct no_ NO;

    RB * rb_criar(void);
    bool rb_inserir(RB *t, int chave);
    bool rb_remover(RB *t, int chave);
    bool rb_apagar_arvore(RB **t);
    bool rb_buscar(RB *t, int chave);
    void rb_imprimir(RB *t);
    bool rb_eh_vazia(RB *t);
    RB * rb_unir(RB *a, RB *b);
    RB * rb_inter(RB *a, RB *b);

#endif
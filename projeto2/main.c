#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "set.h"

int main(){
    int estrutura_escolhida, tam_set_a, tam_set_b;
    scanf("%d", &estrutura_escolhida);

    SET *A = set_criar(estrutura_escolhida);
    SET *B = set_criar(estrutura_escolhida);
    scanf("%d", &tam_set_a);
    scanf("%d", &tam_set_b);

    for(int i = 1; i <= tam_set_a; i++){
        int chave;
        scanf("%d ", &chave);
        set_inserir(A, chave);
    }

    for(int i = 1; i <= tam_set_b; i++){
        int chave;
        scanf("%d ", &chave);
        set_inserir(B, chave);
    }

    int op;
    scanf("%d", &op);

    switch(op){
        case 1: {
                // Elemento x pertence ao conjunto A
                int x;
                scanf("%d", &x);

                if (set_pertence(A, x))
                    printf("Pertence.\n");
                else
                    printf("Nao pertence.\n");

                break;
        }

        case 2: {
                //União do Conjunto A com B
                SET *C = set_uniao(A, B);
                set_imprimir(C);                
                break;
        }

        case 3: {
                // Intersecção do Conjunto A com B
                SET *C = set_intersecao(A, B);
                set_imprimir(C);
                break;
        }
        
        case 4: {
                //Remoção ------- em a ou b????
                SET *C;
                set_imprimir(C);
        }
    }
    
    set_apagar(&A);
    set_apagar(&B);
    
    return 0;
}

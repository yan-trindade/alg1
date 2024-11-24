#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "set.h"

int main(){
    int estrutura_escolhida, tam_set_a, tam_set_b, elem_pertenc_a;
    scanf("%d", &estrutura_escolhida);
    
    switch(estrutura_escolhida){
        // 0 para AVL, 1 para Rubro-Negra(RB)
        case(0):

            SET *setX = set_avl_criar();
            SET *setY = set_avl_criar();
            scanf("%d", &tam_set_a);
            scanf("%d", &tam_set_b);

            for(int i = 1; i <= tam_set_a; i++){
                int chave;
                scanf("%d ", &chave);
                set_avl_inserir(setX, chave);
            }

            for(int i = 1; i <= tam_set_b; i++){
                int chave;
                scanf("%d ", &chave);
                set_avl_inserir(setY, chave);
            }

            scanf("%d", &elem_pertenc_a);
            
            SET * uniao2 = set_avl_uniao(setX, setY);
            SET *inter2 =  set_avl_intersecao(setX, setY);


            set_avl_imprimir(uniao2);
            set_avl_imprimir(inter2);

            if(set_avl_pertence(setX, elem_pertenc_a))
                printf("Pertence.\n");
            else
                printf("Nao pertence.\n");

            

            break;

        case(1):
            
            SET *setA = set_avl_criar();
            SET *setB = set_avl_criar();
            scanf("%d", &tam_set_a);
            scanf("%d", &tam_set_b);

            for(int i = 1; i <= tam_set_a; i++){
                int chave;
                scanf("%d ", &chave);
                set_avl_inserir(setA, chave);
            }

            for(int i = 1; i <= tam_set_b; i++){
                int chave;
                scanf("%d ", &chave);
                set_avl_inserir(setB, chave);
            }

            scanf("%d", &elem_pertenc_a);
            
            SET * uniao = set_avl_uniao(setA, setB);
            SET *inter =  set_avl_intersecao(setA, setB);



            set_avl_imprimir(uniao);
            set_avl_imprimir(inter);

            if(set_avl_pertence(setA, elem_pertenc_a))
                printf("Pertence.\n");
            else
                printf("Nao pertence.\n");

            

            break;
            
    }
        
    return 0;
}

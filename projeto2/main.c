#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "set.h"

int main(){
    
    SET *setA = set_criar();
    SET *setB = set_criar();
    int n1, n2;

    printf("Numero de elementos A: \n");
    scanf("%d", &n1);
    printf("Insira conjunto A:\n");

    for(int i = 1; i <= n1; i++){
        int chave;
        scanf("%d", &chave);
        set_inserir(setA, chave);
    }

    printf("Numero de elementos B: \n");
    scanf("%d", &n2);
    printf("Insira conjunto B:\n");

    for(int i = 1; i <= n2; i++){
        int chave;
        scanf("%d", &chave);
        set_inserir(setB, chave);
    }
   


    printf("\nConjunto A: ");
    set_imprimir(setA);

    printf("\nConjunto B: ");
    set_imprimir(setB);

    // Operações de união e interseção
    SET *uniao = set_uniao(setA, setB);
    SET *inter= set_intersecao(setA, setB);

    // Imprimindo os resultados
    printf("\nResultado da União entre A e B: ");
    set_imprimir(uniao);

    printf("\nResultado da Interseção entre A e B: ");
    set_imprimir(inter);

    // Verificando pertencimento
    printf("\nVerificando se o elemento 5 pertence ao set A: ");
    if(set_pertence(setA, 5)){
        printf("Pertence.\n");
    } 
    else
        printf("Nao pertence.\n");

    // Apagando os sets
    set_apagar(&setA);
    set_apagar(&setB);
    set_apagar(&uniao);
    set_apagar(&inter);

    return 0;
}

/*
 * PROJETO 2 - ALGORITMOS E ESTRUTURAS DE DADOS I
 * 
 * Este projeto tem como objetivo implementar um Tipo Abstrato de Dado (TAD) 
 * que representa um conjunto, oferecendo operações como inserção, remoção, 
 * interseção e união de dois conjuntos.
 * 
 * O cliente pode escolher entre duas diferentes estruturas de dados para 
 * implementar essas funcionalidades: árvores binárias balanceadas do tipo 
 * AVL ou RUBRO-NEGRA. 
 * 
 * Essas estruturas foram escolhidas devido à sua eficiência na organização 
 * dos elementos, facilitando a verificação de pertencimento de um elemento 
 * e permitindo a recuperação dos elementos de forma ordenada. Essa 
 * ordenação simplifica as operações de união e interseção, tornando-as mais 
 * rápidas e eficientes.
 * 
 * Alunos (grupo 35):
 * - Raí Fernando - 15506968 - raifernando@usp.br 
 * - Yan Trindade Meireles - 13680035 - yan.trindade@usp.br
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "set.h"

/*
Na função main(), são lidos da entrada padrão, na ordem, um valor entre 0 e 1, 
indicando a estrutura escolhida (AVL ou Rubro-Negra), e os tamanhos dos 
conjuntos A e B. Com base nessas informações, os  conjuntos são criados, e os elementos 
de A e B são inseridos nos respectivos conjuntos.

Em seguida, é lido um inteiro OPERAÇÃO (entre 1 e 4), que determina qual operação será realizada 
sobre os conjuntos: (1) verificar se um elemento x pertence ao conjunto A; (2) realizar a união entre 
A e B; (3) calcular a interseção entre A e B; (4) ???????????. 
A operação correspondente é então executada utilizando um bloco switch/case.

Por fim, a memória alocada pelos conjuntos é devidamente liberada.
*/
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
                // União do Conjunto A com B
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
                // Remoção ------- em a ou b????
                SET *C;
                set_imprimir(C);
        }
    }
    
    set_apagar(&A);
    set_apagar(&B);
    
    return 0;
}

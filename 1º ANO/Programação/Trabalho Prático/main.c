#include "utils.h"
#include "paragem.h"
#include "linha.h"

void Menu();

int main() {
    printf("Bem-vindo ao Metro Mondego!\n");

    pg listaParagens = NULL;
    ln listaLinhas = NULL;

    int total = 0;
    int opc;

    do {
        Menu();
        scanf("%d", &opc);
        printf("\n");

        switch (opc) {
            case 1:
                listaParagens = adicionaParagem(listaParagens, &total);
                break;
            case 2:
                listaParagens = eliminaParagem(listaParagens, &total, listaLinhas);
                break;
            case 3:
                visualizaParagens(listaParagens, total);
                break;
            case 4:
                listaLinhas = adicionaLinha(listaLinhas, listaParagens, &total);
                break;
            case 5:
                listaLinhas = atualizaLinha(listaLinhas, listaParagens, &total);
                break;
            case 6:
                visualizaLinhas(listaLinhas);
                break;
            case 7:
                calculaPercurso(listaLinhas, listaParagens, &total);
                break;
            case 8:
                visualizaLinhasParagem(listaLinhas);
                break;
            case 9:
                listaParagens = adicionaParagensFicheiro(listaParagens, &total);
                break;
            case 10:
                listaLinhas = adicionaLinhaFicheiro(listaLinhas, listaParagens, &total);
                break;
            case 0:
                printf("Saindo...\n");
                armazenaBinario(listaLinhas, listaParagens, &total);
                free(listaLinhas);
                free(listaParagens);
                return 0;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opc != 0);
}

void Menu(){
    printf("=== MENU ===\n");
    printf("1. Adicionar Paragem\n");
    printf("2. Eliminar Paragem\n");
    printf("3. Visualizar Paragens\n");
    printf("4. Adicionar Linha\n");
    printf("5. Atualizar Linha\n");
    printf("6. Visualizar Linhas\n");
    printf("7. Calcular Percurso\n");
    printf("8. Visualizar Linhas que passam numa Paragem\n");
    printf("9. Adicionar Paragens (Ficheiro de Texto)\n");
    printf("10. Adicionar Linha (Ficheiro de Texto)\n");
    printf("0. Sair\n");
    printf("============\n");
    printf("Escolha uma option: ");
}
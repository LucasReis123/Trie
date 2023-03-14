#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define max_simbulos 26


typedef struct No{

    struct No *filhos[max_simbulos];
    int final;
    
}no;

no *criaNo();
int mapeia(char letra);
void inserir(no *raiz, char chave[30]);
int buscar(no *raiz, char chave[30]);
void listagem(no *raiz, char palavra[30], int nivel, int *altura_trie);
void autocomplete(no *raiz, char palavra_autocomplete[30]);
void listagem_Autocomplete(no *raiz, char palavra[30], int nivel);

int main(){
    no *raiz = criaNo();

// ------------------------------------- Parte do codigo que insere palavras na trie ----------------------------------------------------------------------------------

    char palavras[10][30] = {"vermelho", "azul", "purpura", "branco", "violeta", "prata", "preto", "rosa", "rosachoque"};
    
    int i = 0;
    for(i=0; i < 9; i++){
        inserir(raiz, palavras[i]);
    }
    
// ------------------------------------- Parte do codigo que verifica se tem uma palavra na trie ------------------------------------------------------------------------
    printf("\n");
    
    char palavrasBusca[5][30] = {"azul","verde", "preto", "amarelo"};
    int buscou = 0;

    for(i = 0; i < 4; i++){
        buscou = 0;
        buscou = buscar(raiz, palavrasBusca[i]);
        if(buscou == 0){
            printf("A palavra %s nao foi encontrada\n", palavrasBusca[i]);
        }else{
            printf("A palavra %s foi encontrada\n", palavrasBusca[i]);
        }    
    }

    char palavra[30] = "";

    int *altura_trie = malloc(sizeof(int));

    (*altura_trie) = 0;
// --------------------------------------- Parte do codigo que faz a listagem e bsuca a altura da trie -----------------------------------------------------------
    printf("\n");
    printf("LISTAGEM DAS PALAVRAS DA TRIE:\n");

    listagem(raiz, palavra, 0, altura_trie);

    printf("\n");
    printf("Altura da trie: %d\n", *altura_trie);
    
    
// ---------------------------------------- Parte do codigo que faz o autocomplete ------------------------------------------------------------------------------
    char palavra_autocomplete[30] = "pr";
    printf("\n");
    printf("Palavras que podem ser completadas que comecam com %s:\n", palavra_autocomplete);

    autocomplete(raiz, palavra_autocomplete);

    free(raiz);
    free(altura_trie);
}


no *criaNo(){
    /*
        Initializes a node and returns it
    */

    no *aux = malloc(sizeof(no));
    int i = 0;
    for(i = 0; i < max_simbulos; i++){
        aux->filhos[i] = NULL;
    }
    
    aux->final = 0;
    return (aux);
}

int mapeia(char letra){
    return ((int)letra - (int)'a');
}

void inserir(no *raiz, char chave[30]){
    /*
        Inserts a node in the tree according to the idea of ​​a "trie" tree 
        (tree where each key element is separated by block)
    */

    no *aux = malloc(sizeof(no));
    aux = raiz;

    int i = 0, k = 0;
    int tamanho = strlen(chave);
    for(i = 0; i < tamanho; i++){
        k = mapeia(chave[i]);
        if(!aux->filhos[k]){
            aux->filhos[k] = criaNo();
        }
        aux = aux->filhos[k];
    }

    aux->final = 1;
}

int buscar(no *raiz, char chave[30]){
    /*
        This function looks for a key in a trie
    */

    no *aux = malloc(sizeof(no));
    aux = raiz;

    int i = 0, k = 0;
    int tamanho = strlen(chave);
    for(i = 0; i < tamanho; i++){
        k = mapeia(chave[i]);
        if(!aux->filhos[k]){
            return 0;
        }
        aux = aux->filhos[k];
    }

    return aux->final;
}

void listagem(no *raiz, char palavra[30], int nivel, int *altura_trie){
    /*
        list the keys in order
    */
    if(nivel > (*altura_trie)){
        (*altura_trie) = nivel;
    }

    int i = 0;

    if(raiz->final != 0){
        palavra[nivel] = '\0';
        printf("%s\n", palavra);

    }

    for(i = 0; i < max_simbulos; i++){
        if(raiz->filhos[i] != NULL){
            palavra[nivel] = i + 'a';
            listagem(raiz->filhos[i], palavra, nivel + 1, altura_trie);
        }
    }
}

void autocomplete(no *raiz, char palavra_autocomplete[30]){
    /*
        receives as a parameter a tree and a part of a word to be 
        completed and prints the words that have the same prefix.
    */
    no *aux = malloc(sizeof(no));
    aux = raiz;

    int tamanho = 0, i = 0, k = 0;
    tamanho = strlen(palavra_autocomplete);


    for(i = 0; i < tamanho; i++){
        k = mapeia(palavra_autocomplete[i]);
        if(!aux->filhos[k]){
            printf("Palavra nao esta inserida na trie\n");
            return;
        }
        aux = aux->filhos[k];
    }
    listagem_Autocomplete(aux, palavra_autocomplete, tamanho);

}

void listagem_Autocomplete(no *raiz, char palavra[30], int nivel){
    /*
        prints the words that have the prefix.
    */
    int i = 0;

    if(raiz->final != 0){
        palavra[nivel] = '\0';
        printf("%s\n", palavra);

    }

    for(i = 0; i < max_simbulos; i++){
        if(raiz->filhos[i] != NULL){
            palavra[nivel] = i + 'a';
            listagem_Autocomplete(raiz->filhos[i], palavra, nivel + 1);
        }
    }
}
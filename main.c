#include "grafo.h"
#include "FilaDinamica.h"

//funcao que determina a posicao de um elemento no mapa//
int posicao(int i, int j, int M) {
    int x = i * M + j; //as posicoes vao de 0 ate tamanho do mapa - 1//
    return x;
}

//funcao que cria um vetor que armazena os pais da "arvore"//
int *cria_pai(int Tamanho) {
    int i;
    int *pai = (int *)malloc(Tamanho * sizeof(int)); //o espaco alocado eh o tamanho do mapa//
    for(i=0;i<Tamanho;i++)
        pai[i] = -1; //todos as posicoes do vetor recebem o numero -1, pois ele nao eh pai de ninguem//
    return pai;
}

//funcao que percorre toda a ilha de uma posicao (por meio da busca em profundidade) e retorna o tamanho dessa ilha//
int DFS_ilhas(grafo *mapa, int *visitado, int x, int tam) {

    nodo *lista;
    visitado[x] = 1; //a posicao do mapa eh visitada e seu lugar no vetor de vertices visitados recebe 1//
    tam++; //incrementa em 1 o tamanho da ilha sempre que um ponto eh visitado//

    /*laco cujo inicio eh a lista de vizinhos da posicao que a funcao recebeu. Enquanto a lista nao for nula,
    ou seja, enquanto houver vizinhos, vai para o proximo nodo da lista, o proximo vizinho*/
    for(lista = mapa->lista[x]; lista != NULL; lista = lista->prox) {
        if(visitado[lista->pos] == 0) { //verifica se o vizinho nao foi visitado//

            /*caso nao tenha sido visitado, ele eh visitado pela funcao novamente de forma recursiva
            e retorna o tamanho dessa "sub-ilha"*/
            tam = DFS_ilhas(mapa, visitado, lista->pos, tam);
        }
    }
    return tam; //retorna o tamanho da ilha//
}

//funcao que executa a busca em profundidade e retorna 1 ou 0 (se ha ou nao caminho para o tesouro)//
int DFS_caminho(grafo *mapa, int *visitado, int *pai, int L, int X) {

    nodo *lista;
    visitado[L] = 1; //a posicao do mapa recebida pela funcao eh visitado//
    if(L == X) return 1; //se a posicao for a mesma do tesouro, retorna 1//

    /*laco cujo inicio eh a lista de vizinhos da posicao que a funcao recebeu. Enquanto a lista nao for nula,
    ou seja, enquanto houver vizinhos, vai para o proximo nodo da lista, o proximo vizinho*/
    for(lista = mapa->lista[L]; lista != NULL; lista = lista->prox) {
        if(visitado[lista->pos] == 0) { //verifica se o vizinho nao foi visitado//
            
            /*o numero da posicao do vizinho no vetor de pais recebe a posicao recebida pela funcao,
            ou seja, o pai desse vizinho vai ser a posicao recebida pela funcao, que inicialmente eh o L*/
            pai[lista->pos] = L;

            /*alem disso, ele eh visitado pela funcao novamente de forma recursiva
            e retorna se ha ou nao caminho para o tesouro a partir desse vizinho*/
            if(DFS_caminho(mapa, visitado, pai, lista->pos, X) == 1)
                return 1;
        }
    }
    return 0; //caso nao encontre o tesouro apos percorrer toda a ilha, a funcao retorna 0//
}

//funcao que executa a busca em largura//
void BFS_caminho(grafo *mapa, Fila *f, int *distancia, int *visitado, int *pai, int L) {

    int k;
    nodo *lista;
    distancia[L] = 0; //o "nivel" da arvore para a primeira posicao recebe 0//
    push_Fila(f, L); //a posicao eh inserida na fila//
    visitado[L] = 1; //a posicao eh visitada//

    //laco que roda enquanto a fila nao estiver vazia//
    while(vazia_Fila(f) != 1) {

        k = pop_Fila(f); //retira o primeiro elemento da fila//

        /*laco cujo inicio eh a lista de vizinhos da posicao que a funcao recebeu. Enquanto a lista nao for nula,
        ou seja, enquanto houver vizinhos, vai para o proximo nodo da lista, o proximo vizinho*/
        for(lista = mapa->lista[k]; lista != NULL; lista = lista->prox) {

            if(visitado[lista->pos] == 0) { //verifica se o vizinho nao foi visitado//

                push_Fila(f, lista->pos); //se nao tiver sido, insere ele na fila//
                visitado[lista->pos] = 1; //o vizinho eh visitado//
                distancia[lista->pos] = distancia[k] + 1; //o nivel dele eh o nivel do pai dele acrescido de 1//
                pai[lista->pos] = k; //no vetor de pais, o vizinho recebe a posicao retirada da fila como pai//
            }
        }
    }
}

/*funcao que altera o mapa de modo que mostre o caminho da busca (em profundidade ou em largura) quando
a funcao Imprime_Busca for chamada, e retorna a quantidade de passos necessaria para chegar ao tesouro.
Essa funcao faz o caminho inverso, recebe a posicao do tesouro e vai percorrendo os pais ate chegar em L
(localizacao inicial no mapa)*/
int Caminho_Busca(char locais[][MAX], int *pai, int L, int X, int M) {

    int i, j, passos;
    i = j = passos = 0;
    if(X == L) //se a posicao recebida pela funcao for igual a da localizacao (L), retorna a quantidade de passos//
        return passos;
    /*senao, executa a funcao recursivamente para o pai da posicao recebida (que inicialmente eh o tesouro),
    e a quantidade de passos atual recebe a si mesma somada com a da recursao*/
    passos = passos + Caminho_Busca(locais, pai, L, pai[X], M);

    /*laco que executa enquanto a posicao de i e j for diferente do pai da posicao recebida pela funcao.
    Serve para encontrar o i e o j da posicao do pai para alterar no mapa*/
    while(posicao(i, j, M) != pai[X]) {
        j++;
        if(j == M) {
            j=0;
            i++;
        }
    }

    passos++; //incrementa a quantidade de passos em 1//

    //se o pai da posicao recebida estiver em cima, a posicao dele no mapa recebe uma seta apontando para baixo//
    if(pai[X]-X < -1)
        locais[i][j] = 'v';

    //se estiver na esquerda, recebe a seta apontando para a direita//
    else if(pai[X]-X == -1)
        locais[i][j] = '>';

    //se estiver na direita, recebe a seta apontando para a esquerda//
    else if(pai[X]-X == 1)
        locais[i][j] = '<';

    //se estiver em baixo, recebe a seta apontando para cima//
    else
        locais[i][j] = '^';

    return passos; //retorna a quantidade de passos para o tesouro//
}

void Imprime_Busca(char locais[][MAX], int N, int M, int k) {
    int i, j;

    //laco para percorrer o mapa//
    for(i=0;i<N;i++) {
        for(j=0;j<M;j++){
            printf("%c", locais[i][j]); //imprime os pontos do mapa//
            if(j == M-1) //quando chega na borda, imprime uma nova linha//
                printf("\n");
        }
    }
    printf("%d passo(s)\n", k); //imprime a quantidade de passos para o tesouro//
}

int main() {

    /*cria as variaveis N e M que armazenam o numero de linhas e colunas, respectivamente, as variaveis L e X 
    que armazenam a posicao da localizacao inicial e do tesouro, respectivamente, alem das variaveis i, j, k 
    para lacos e para armazenar outros valores. Alem disso, cria uma variavel cont que serve para contar
    o numero de ilhas do mapa, duas variaveis maior e menor, que identificam o tamanho da maior e da menor ilha,
    respectivamente, uma variavel Tamanho que identifica o tamanho do mapa e uma variavel tam que serve para 
    receber os tamanhos das ilhas. Cria tambem 3 vetores, um que registra os vertices que ja foram visitados,
    um que registra o pai de cada vertice na "arvore" e um que diz a distancia entre dois vertices ("niveis
    da arvore"). Cria tambem dois vetores de strings, sendo que ambos armazenam os caracteres do mapa.*/
    int N, M, L, X, i, j, k, cont, maior, menor, Tamanho, tam;
    int *visitado, *pai, *distancia;
    char locais[MAX][MAX], locais_aux[MAX][MAX];
    grafo *mapa = cria_grafo(); //cria o grafo (lista de adjacencia)//
    Fila *f = cria_Fila(); //cria a fila//

    k = cont = maior = menor = tam = 0;
    L = X = -1; //as variaveis L e X recebem -1 pois nao existe essa posicao no mapa//

    scanf("%d", &N); //recebe o numero de linhas N do mapa//
    scanf("%d", &M); //recebe o numero de colunas M do mapa//

    Tamanho = N * M;

    visitado = (int *)calloc(Tamanho, sizeof(int)); //aloca espaco do tamanho do mapa para o vetor de vertices visitados//
    pai = cria_pai(Tamanho); //chama a funcao que cria o vetor de pais//
    distancia = (int *)calloc(Tamanho, sizeof(int)); //aloca espaco do tamanho do mapa para o vetor de distancia entre os vertices//

    //laco para receber os simbolos do mapa//
    for(i=0;i<N;i++)
        scanf("%s", locais[i]);

    //laco para inserir os simbolos no mapa (grafo)//
    for(i=0;i<N;i++) {
        for(j=0;j<M;j++) {

            locais_aux[i][j] = locais[i][j];

            //verifica se o simbolo do mapa eh diferente de oceano//
            if(locais[i][j] != '.') {

                k = posicao(i, j, M); //a variavel k recebe a posicao do simbolo se ele for diferente de oceano//

                if(locais[i][j] == 'L') //se o ponto do mapa for L, a variavel recebe a posicao//
                    L = k;
                else if(locais[i][j] == 'X') //o mesmo vale para o X//
                    X = k;

                //verifica se os vizinhos sao diferentes de oceano, se forem, insere eles na lista//
                if(locais[i+1][j] != '.' && i < N-1)
                    mapa = push_grafo(mapa, k, posicao(i+1, j, M)); //adiciona o vizinho de baixo, caso exista//
                if(locais[i][j+1] != '.' && j < M-1)
                    mapa = push_grafo(mapa, k, posicao(i, j+1, M)); //adiciona o da direita, caso exista//
                if(locais[i][j-1] != '.' && j > 0)
                    mapa = push_grafo(mapa, k, posicao(i, j-1, M)); //adiciona o da esquerda, caso exista//
                if(locais[i-1][j] != '.' && i > 0)
                    mapa = push_grafo(mapa, k, posicao(i-1, j, M)); //adiciona o de cima, caso exista//
            }
        }
    }

    //laco para percorrer as posicoes do mapa//
    for(i=0;i<N;i++) {
        for(j=0;j<M;j++) {

            k = posicao(i, j, M); //a variavel k recebe a posicao do local [i][j]//
            
            //se o local for diferente de oceano e ainda nao foi visitado, visita ele e a ilha dele//
            if(locais[i][j] != '.' && visitado[k] == 0) {

                tam = DFS_ilhas(mapa, visitado, k, 0); //chama funcao que visita toda a ilha e retorna o tamanho dela//
                
                if(menor == 0) //se houver ao menos uma ilha no mapa, a variavel menor recebe o tamanho dela//
                    menor = tam;

                cont++; //sempre que uma ilha eh visitada a variavel cont eh incrementada//

                /*se o tamanho da ilha visitada for maior do que a maior ja visitada, a variavel maior
                recebe o tamanho dessa nova ilha*/
                if(tam > maior)
                    maior = tam;
                //a mesma logica se aplica a menor//
                if(tam < menor)
                    menor = tam;
            }
        }
    }

    //imprime o numero de ilhas, o tamanho da maior e da menor ilha, respectivamente//
    printf("Ha %d ilha(s)\n", cont);
    printf("A maior tem tamanho %d\n", maior);
    printf("A menor tem tamanho %d\n", menor);

    //laco para zerar novamente o vetor de visitados, pois ele sera usado novamente//
    for(k=0;k<Tamanho;k++)
        visitado[k] = 0;

    //chama a funcao que identifica se ha um caminho para o tesouro, e a variavel k recebe a resposta (1 ou 0)//
    k = DFS_caminho(mapa, visitado, pai, L, X);

    /*se k for zero, ou se nao ha ilhas, ou se nao ha o L ou o X, nao existe caminho para o tesouro, 
    portanto imprime isso na tela e encerra o programa*/
    if(k == 0 || cont == 0 || L == -1 || X == -1) {
        printf("Nao ha caminho para o tesouro\n");
        exit(1);
    }

    /*caso exista um caminho, vai executar uma funcao que altera o mapa para mostrar o caminho,
    obtido com o vetor de pais da busca em profundidade feita anteriormente, e depois imprime 
    o novo mapa com o caminho, alem da quantidade de passos que eh retornada pela funcao*/
    printf("\nBusca em profundidade:\n");
    k = Caminho_Busca(locais, pai, L, X, M);
    Imprime_Busca(locais, N, M, k);

    /*laco para zerar novamente o vetor de visitados e atribuir -1 a todos os espacos do vetor de pais,
    para que sejam utilizados na busca em largura*/
    for(k=0;k<Tamanho;k++) {
        visitado[k] = 0;
        pai[k] = -1;
    }

    //chama a funcao que executa o caminho mais curto para o tesouro (busca em largura)//
    BFS_caminho(mapa, f, distancia, visitado, pai, L);

    /*vai executar a funcao que altera o mapa para mostrar o caminho,
    obtido com o vetor de pais da busca em largura feita anteriormente, e depois imprime 
    o novo mapa com o caminho, alem da quantidade de passos que eh retornada pela funcao*/
    printf("\nBusca em largura:\n");
    k = Caminho_Busca(locais_aux, pai, L, X, M);
    Imprime_Busca(locais_aux, N, M, k);

    free(visitado); //libera o vetor de vertices visitados//
    free(pai); //libera o vetor de pais//
    free(distancia); //libera o vetor de distancia//
    free(f); //libera a fila//
    free(mapa); //libera o grafo//

    return 0;
}
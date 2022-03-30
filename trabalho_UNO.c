#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define max 25

//string global
 char A[25] = "amarelo";
 char Z[25] = "azul";
 char V[25] = "verde";
 char R[25] = "vermelho";
 char CQ[25] = "curinga +4";
 char CT[25] = "curinga troca maos";
 char CR[25] = "curinga escolher cor";

//Criando a estrutura das cartas
typedef struct carta{
    int naipe;
    char cor[max];
    struct carta *proximo;
}Carta;
//Criando a estrutura do baralho
typedef struct baralho{
    Carta monte[110];
    int topo;
}Baralho;
//Criando os Jogadores
typedef struct mao{
    struct carta *inicio;
    int cont;
}Mao;
typedef struct player{
    char nome[50];
    int pontos;
    Mao *jogador;
}Player;
//Criando mesa de descare
typedef struct descarte{
    Carta monte_descarte[110];
    int topo;
}Descarte;

//Funções de criação das cartas, baralho e embarlhar
Baralho *cria_baralho();
int cartas_baralho(Baralho *B,int v, char *naipe, int tam);
void embaralhar(Baralho *B);
int retirar_carta(Baralho *B, Carta *c);

//Funções da mão dos jogadores
Mao *criar_mao();
int distribuir_cartas(Player *j, Carta c);

//Funções de Descarte
Descarte *criar_descarte();
int remover_mao(Player *j,Carta *descartada,int n,char c);
int cartas_descarte(int cont, Descarte *D,Carta descartada);
//Funções de inserir carta e compra carta
int inserir_carta_mao(Carta C, Player *j);
int retirar_descarte(Descarte *D, Carta *c);
int conferencia_mao(Descarte *D, Player *j);
//Funções das cartas especiais
int compra_dois(Baralho *B, Player *a);
//Funções das Jogadas
void imprime_mao(Player *j);
void descarta_mao(int *naipe, char *cor);
void pontuacao(Player *um, Player *dois);
void retira_carta_mao(Player *j, Baralho *B);
int confere_baralho(Baralho *B);
int troca_descarte(Baralho *B, Descarte *D);
void troca_maos(Player *um, Player *dois);
void salvar_jogadas(Descarte *D,Player *j,FILE *fp);
//Função principal
int main(){
    Baralho *B;
    B = cria_baralho();
    Descarte *D;
    D = criar_descarte();
    int retorno;
    Player *um;
    um = (Player*)malloc(sizeof(Player));
    um->jogador = criar_mao();
    Player *dois;
    dois = (Player*)malloc(sizeof(Player));
    dois->jogador = criar_mao();
    Carta c;
    FILE *fp;


    //Variavel de jogadas
    Carta jogadas;
    int naipe;
    char cor;
    int contador = 0;

    //Criando as cartas Amarelas
    for(int i=0;i<2;i++){
        for(int j=0;j<=12;j++){
            retorno = cartas_baralho(B,j,A,max);
            if(retorno == 1);
            else
                printf("\n\tOcorreu um erro!\n\n");
        }
    }
    //Criando as cartas Azuis
    for(int i=0;i<2;i++){
        for(int j=0;j<=12;j++){
            retorno = cartas_baralho(B,j,Z,max);
            if(retorno == 1);
            else
                printf("\n\tOcorreu um erro!\n\n");
        }
    }
    //Criando as cartas Verde
    for(int i=0;i<2;i++){
        for(int j=0;j<=12;j++){
            retorno = cartas_baralho(B,j,V,max);
            if(retorno == 1);
            else
                printf("\n\tOcorreu um erro!\n\n");
        }
    }
    //Criando as cartas Vermelho
    for(int i=0;i<2;i++){
        for(int j=0;j<=12;j++){
            retorno = cartas_baralho(B,j,R,max);
            if(retorno == 1);
            else
                printf("\n\tOcorreu um erro!\n\n");
        }
    }
    //Criando as cartas corigas
    for(int i = 0; i < 3; i++){
        if(i == 0){
            int c = 50;
            for(int j = 0; j < 2; j++){
                retorno = cartas_baralho(B,c,CQ,max);
                    if(retorno == 1);
                    else
                        printf("\n\tOcorreu um erro!\n\n");
            }
        }
        else if(i == 1){
            int c = 51;
            for(int j = 0; j < 2; j++){
                retorno = cartas_baralho(B,c,CR,max);
                    if(retorno == 1);
                    else
                        printf("\n\tOcorreu um erro!\n\n");
            }
        }
        else{
            int c = 52;
            for(int j = 0; j < 2; j++){
                retorno = cartas_baralho(B,c,CT,max);
                    if(retorno == 1);
                    else
                        printf("\n\tOcorreu um erro!\n\n");
            }
        }
    }
        embaralhar(B);

        //Inicio do Jogo
        printf("\n\t****Bem Vindo ao UNO.c****\n\n");
        //Coletando dados dos jogdores
        printf("\n\tDigite o nome do Player Um: ");
        setbuf(stdin,NULL);
        gets(um->nome);
        um->pontos = 0;

        printf("\n\tDigite o nome do Player Dois: ");
        setbuf(stdin,NULL);
        gets(dois->nome);
        dois->pontos = 0;
    do{
        //Distribuição de cartas
        for(int i = 0; i < 7; i++){
        //Distribuindo as cartas do primeiro jogdor
            retorno = retirar_carta(B, &c);
            if(retorno == 1){
                retorno = distribuir_cartas(um,c);
                if(retorno == 1){}
                else
                    printf("\n\tOcorreu um erro!\n\n");
            }
            else
                printf("\n\tOcorreu um erro!\n\n");
        //Distribuindo as cartas do segundo jogador
         retorno = retirar_carta(B, &c);
            if(retorno == 1){
                retorno = distribuir_cartas(dois,c);
                if(retorno == 1){}
                else
                    printf("\n\tOcorreu um erro!\n\n");
            }
            else
                printf("\n\tOcorreu um erro!\n\n");
        }


        printf("\n\t***Inicio das jogadas!***\n\n");
        printf("\n\tAs Cartas Especiais sao:\n\t[10]-Inverter\n\t[11]-Passa a Vez\n\t[12]-Comprar +2");
        printf("\n\tOS Curingas sao:\n\t[50]-%s\n\t[51]-%s\n\t[52]-%s\n\n",CQ, CR, CT);
        //primeira jogada
        do{
            //Mostrando a Mão do Jogador 1
            imprime_mao(um);
            //Definindo a primeira jogada
            printf("\n\n\tEscolha a primeira carta a ser descartada!\n\tLembrando que nesta jogada nao podem ser utilizados cartas especiais!\n\n");
            descarta_mao(&naipe,&cor);
            //retirando a carta da mão do jogador
            retorno = remover_mao(um,&c,naipe,cor);
            if(retorno == 1){
                //Colocando a carta no monte de descarte
                retorno = cartas_descarte(contador,D,c);
                if(retorno == 1){
                    salvar_jogadas(D,um,fp);
                    printf("\n\tDescarte realizado!\n\n");
                    contador++;
                }
                else if(retorno == 0){
                    printf("\n\tOcorreu algum erro no descarte!\n\n");
                }
                else{
                    retorno = retirar_descarte(D,&c);
                    retorno = inserir_carta_mao(c,um);
                    printf("\n\tCarta Especial ou Curinga escolha outra carta!\n\n");
                }
            }
            else
                printf("\n\tOcorreu algum erro ao remover a carta da mao do Jogador %s", um->nome);

        }while(contador == 0 );
        //inicio das demais jogadas
        do{
            system("cls");
            //confere se a mesa de compras ainda tem cartas
            retorno = confere_baralho(B);
            //se não tiver cartas na mesa de compra
            if(retorno == 0){
                //Função que pega a mesa de descarte e devolve para a mesa de compras
                retorno = troca_descarte(B,D);
                if(retorno == 1){
                    //Função retornando 1 a proxima embraralha novamente a mesa de compras
                    embaralhar(B);
                    printf("\n\tTroca de mesa descarte com mesa baralho realizada!\n\n");
                }
                else
                    printf("\n\tOcorreu um erro ao trocar as mesas!\n\n");
            }
            //conferindo a mão do jogdor dois na 1ºjogada
            retorno = conferencia_mao(D,dois);
            //se não houver carta possivel de jogada o sistema compra cartas até que uma seja aceita para ser descartada
            while(retorno == 0){
                retirar_carta(B,&c);
                inserir_carta_mao(c,dois);
                retorno = conferencia_mao(D,dois);
            }
            //Especificando as cartas
            printf("\n\tAs Cartas Especiais sao:\n\t[10]-Inverter\n\t[11]-Passa a Vez\n\t[12]-Comprar +2");
            printf("\n\tOS Curingas sao:\n\t[50]-%s\n\t[51]-%s\n\t[52]-%s\n\n",CQ, CR, CT);
            //Mostrando a Mão do Jogador 2
            imprime_mao(dois);
            printf("\n\tA carta na mesa de descarte e :%i[%s]\n\n",D->monte_descarte[D->topo-1].naipe, D->monte_descarte[D->topo-1].cor);
            //Definindo a  jogada do Jogdor 2
            printf("\n\n");
            descarta_mao(&naipe,&cor);
            //retirando a carta da mão do jogador 2 na 1ªjogada
            retorno = remover_mao(dois,&c,naipe,cor);
            if(retorno == 1){
                //Colocando a carta no monte de descarte na 1ªjogada
                retorno = cartas_descarte(contador,D,c);
                if(retorno == 1){
                    //Salvando a jogada feita na 1ªjogada
                    salvar_jogadas(D,dois,fp);
                    //Conferindo se a carta é passa a vez ou inverter para a 2ªjogada
                    if(naipe == 11 || naipe == 10){
                        retorno = conferencia_mao(D,dois);
                        while(retorno == 0){
                            retirar_carta(B,&c);
                            inserir_carta_mao(c,dois);
                            retorno = conferencia_mao(D,dois);
                        }
                        //Especificando as cartas na 2ª jogada carta especial usada
                        printf("\n\tAs Cartas Especiais sao:\n\t[10]-Inverter\n\t[11]-Passa a Vez\n\t[12]-Comprar +2");
                        printf("\n\tOS Curingas sao:\n\t[50]-%s\n\t[51]-%s\n\t[52]-%s\n\n",CQ, CR, CT);
                        //Mostrando a Mão do Jogador 2 na 2ªjogada
                        imprime_mao(dois);
                        printf("\n\tA carta na mesa de descarte e :%i[%s]\n\n",D->monte_descarte[D->topo-1].naipe, D->monte_descarte[D->topo-1].cor);
                        //Definindo a  jogada do Jogdor 2 na 2ª jogada carta especial usada
                        printf("\n\n");
                        descarta_mao(&naipe,&cor);
                        //retirando a carta da mão do jogador 2 na 2ª jogada carta especial usada
                        retorno = remover_mao(dois,&c,naipe,cor);
                        if(retorno == 1){
                            //Colocando a carta no monte de descarte na 2ª jogada carta especial usada
                            retorno = cartas_descarte(contador,D,c);
                            if(retorno == 1){
                                contador++;
                                //salvando a jogada feita na 2ª jogada carta especal usada
                                salvar_jogadas(D,dois,fp);
                                //conferindo se a carta é compra dois na 2ª jogada carta especial usada
                                if(naipe == 12){
                                   compra_dois(B,um);
                                }
                                //conferindo se a carta é curinga +4 na 2ª jogada carta especial usada
                                else if(naipe == 50){
                                    compra_dois(B,um);
                                    compra_dois(B,um);
                                }
                                //Conferindo se a carta é curinga escolhe cor na 2ª jogada carta especial usada
                                else if (naipe == 51){
                                    //conferindo a mão do jogador dois na 2ºjogada carta especial usada
                                    retorno = conferencia_mao(D,dois);
                                    //se não houver carta possivel de jogada o sistema compra cartas até que uma seja aceita para ser descartada
                                    while(retorno == 0){
                                        retirar_carta(B,&c);
                                        inserir_carta_mao(c,dois);
                                        retorno = conferencia_mao(D,dois);
                                    }
                                    //Especificando as cartas na 2º jogada escolhe cor
                                    printf("\n\tAs Cartas Especiais sao:\n\t[10]-Inverter\n\t[11]-Passa a Vez\n\t[12]-Comprar +2");
                                    printf("\n\tOS Curingas sao:\n\t[50]-%s\n\t[51]-%s\n\t[52]-%s\n\n",CQ, CR, CT);
                                    //Mostrando a Mão do Jogador 2 na 2ª jogada escolhe cor
                                    imprime_mao(dois);
                                    printf("\n\tA carta na mesa de descarte e :%i[%s]\n\n",D->monte_descarte[D->topo-1].naipe, D->monte_descarte[D->topo-1].cor);
                                    //Definindo a  jogada do Jogdor 2 na 2ª jogada escolhe cor
                                    printf("\n\n");
                                    descarta_mao(&naipe,&cor);
                                    //retirando a carta da mão do jogador 2 na 2ªjogada escolhe cor
                                    retorno = remover_mao(dois,&c,naipe,cor);
                                    if(retorno == 1){
                                        contador++;
                                        //salvando a jogada feita na 2ª jogada escolhe cor
                                        salvar_jogadas(D,dois,fp);
                                        //conferindo se a carta é compra dois na 2ª jogada escolhe cor
                                        if(naipe == 12){
                                           compra_dois(B,um);
                                        }
                                         //conferindo se a carta é curinga +4 na 2ª jogada escolhe cor
                                        else if(naipe == 50){
                                            compra_dois(B,um);
                                            compra_dois(B,um);
                                        }
                                        //conferindo se a carta é curinga troca maos na 2ª jogada escolhe cor
                                        else if(naipe == 52){
                                            troca_maos(um,dois);
                                        }
                                    }
                                }
                                //conferindo se a carta é curinga troca maos na 2ª jogada
                                else if(naipe == 52){
                                    troca_maos(um,dois);
                                }
                            }
                        }
                    }
                    //conferindo se a carta é compra+2 na 1 jogada
                    else if(naipe == 12){
                        //conferindo se tem carta na mesa de compra
                        retorno = confere_baralho(B);
                        if(retorno == 0){
                            //caso não tenha troca a mesa de descarte pela mesa de compra
                            retorno = troca_descarte(B,D);
                            if(retorno == 1){
                                //embaralha a mesa de compra
                                embaralhar(B);
                                printf("\n\tTroca de mesa descarte com mesa baralho realizada!\n\n");
                            }
                            else
                                printf("\n\tOcorreu um erro ao trocar as mesas!\n\n");
                        }
                        //realisa a função compra dois
                        compra_dois(B,um);
                    }
                    //conferindo se a carta é curinga +4 na 1ª jogada
                    else if(naipe == 50){
                        compra_dois(B,um);
                        compra_dois(B,um);

                    }
                    //conferindo se a carta e curinga escolhe cor na 1ª jogada
                    else if (naipe == 51){
                        //conferindo a mão do jogador dois na 2ºjogada carta especial usada
                        retorno = conferencia_mao(D,dois);
                        //se não houver carta possivel de jogada o sistema compra cartas até que uma seja aceita para ser descartada
                        while(retorno == 0){
                            retirar_carta(B,&c);
                            inserir_carta_mao(c,dois);
                            retorno = conferencia_mao(D,dois);
                        }
                        //Especificando as cartas na 2º jogada escolhe cor
                        printf("\n\tAs Cartas Especiais sao:\n\t[10]-Inverter\n\t[11]-Passa a Vez\n\t[12]-Comprar +2");
                        printf("\n\tOS Curingas sao:\n\t[50]-%s\n\t[51]-%s\n\t[52]-%s\n\n",CQ, CR, CT);
                        //Mostrando a Mão do Jogador 2 na 2ª jogada escolhe cor
                        imprime_mao(dois);
                        printf("\n\tA carta na mesa de descarte e :%i[%s]\n\n",D->monte_descarte[D->topo-1].naipe, D->monte_descarte[D->topo-1].cor);
                        //Definindo a  jogada do Jogdor 2 na 2ª jogada escolhe cor
                        printf("\n\n");
                        descarta_mao(&naipe,&cor);
                        //retirando a carta da mão do jogador 2 na 2ªjogada escolhe cor
                        retorno = remover_mao(dois,&c,naipe,cor);
                        if(retorno == 1){
                            contador++;
                            //salvando a jogada feita na 2ª jogada escolhe cor
                            salvar_jogadas(D,dois,fp);
                            //conferindo se a carta é compra dois na 2ª jogada escolhe cor
                            if(naipe == 12){
                               compra_dois(B,um);
                            }
                             //conferindo se a carta é curinga +4 na 2ª jogada escolhe cor
                            else if(naipe == 50){
                                compra_dois(B,um);
                                compra_dois(B,um);
                            }
                            //conferindo se a carta é curinga troca maos na 2ª jogada escolhe cor
                            else if(naipe == 52){
                                troca_maos(um,dois);
                            }
                        }
                    }
                    //conferindo se a carta e curinga troca de maos na 1ª jogada
                    else if(naipe == 52){
                        troca_maos(um,dois);

                    }
                    printf("\n\tDescarte realizado!\n\n");
                    contador++;
                }
            }
            system("cls");
            //se preparando para a proxima jogada do jogador 1
            retorno = confere_baralho(B);
            if(retorno == 0){
                retorno = troca_descarte(B,D);
                if(retorno == 1){
                    embaralhar(B);
                    printf("\n\tTroca de mesa descarte com mesa baralho realizada!\n\n");
                }
                else
                    printf("\n\tOcorreu um erro ao trocar as mesas!\n\n");
            }
            //conferindo a mão do jogdor 1 na 1ª jogada
            retorno = conferencia_mao(D,um);
            while(retorno == 0){
                retirar_carta(B,&c);
                inserir_carta_mao(c,um);
                retorno = conferencia_mao(D,um);
            }
            //Especificando as cartas
            printf("\n\tAs Cartas Especiais sao:\n\t[10]-Inverter\n\t[11]-Passa a Vez\n\t[12]-Comprar +2");
            printf("\n\tOS Curingas sao:\n\t[50]-%s\n\t[51]-%s\n\t[52]-%s\n\n",CQ, CR, CT);
            //Mostrando a Mão do Jogador 1 na 1ªjogada
            imprime_mao(um);
            printf("\n\tA carta na mesa de descarte e :%i[%s]\n\n",D->monte_descarte[D->topo-1].naipe, D->monte_descarte[D->topo-1].cor);
            //Definindo a jogada do Jogador 1 na 1ª jogada
            printf("\n\n");
            descarta_mao(&naipe,&cor);
            //retirando a carta da mão do jogador na 1ª jogada
            retorno = remover_mao(um,&c,naipe,cor);
            if(retorno == 1){
                //Colocando a carta no monte de descarte na 1º jogada
                retorno = cartas_descarte(contador,D,c);
                if(retorno == 1){
                    //Conferindo se a carta e Especiais Inverter e Passa Vez na 1ª jogada
                    if(naipe == 11 || naipe == 10){
                        //Conferindo a mao do jogador 1 na 2ª jogada
                        retorno = conferencia_mao(D,um);
                        while(retorno == 0){
                            retirar_carta(B,&c);
                            inserir_carta_mao(c,um);
                            retorno = conferencia_mao(D,um);
                        }
                        //Especificando as cartas na 2ª jogada
                        printf("\n\tAs Cartas Especiais sao:\n\t[10]-Inverter\n\t[11]-Passa a Vez\n\t[12]-Comprar +2");
                        printf("\n\tOS Curingas sao:\n\t[50]-%s\n\t[51]-%s\n\t[52]-%s\n\n",CQ, CR, CT);
                        //Mostrando a Mão do Jogador 1 na 2ª jogada
                        imprime_mao(um);
                        printf("\n\tA carta na mesa de descarte e :%i[%s]\n\n",D->monte_descarte[D->topo-1].naipe, D->monte_descarte[D->topo-1].cor);
                        //Definindo a  jogada do Jogdor 1 na 2ª jogada
                        printf("\n\n");
                        descarta_mao(&naipe,&cor);
                        //retirando a carta da mão do jogador 1 na 2ª jogada
                        retorno = remover_mao(um,&c,naipe,cor);
                        if(retorno == 1){
                            //Colocando a carta no monte de descarte na 2ªjogada
                            retorno = cartas_descarte(contador,D,c);
                            if(retorno == 1){
                                //salvando a 2ªjogada do jogador 1
                                salvar_jogadas(D,um,fp);
                                contador++;
                                //Conferindo se a carta e a compra+2 na 2ª jogada
                                if(naipe == 12){
                                    //conferindo se tem carta na mesa de compra na 2ª jogada
                                    retorno = confere_baralho(B);
                                    if(retorno == 0){
                                        //caso nao tenha trocando a mesa de descarte com a mesa de compra na 2ª jogada
                                        retorno = troca_descarte(B,D);
                                        if(retorno == 1){
                                            //embaralhando a mesa de compra na 2ª jogada
                                            embaralhar(B);
                                            printf("\n\tTroca de mesa descarte com mesa baralho realizada!\n\n");
                                        }
                                        else
                                            printf("\n\tOcorreu um erro ao trocar as mesas!\n\n");
                                    }
                                    //realizando a compra +2 na 2ª jogada
                                    compra_dois(B,dois);
                                }
                                //conferindo se a carta e Curinga +4 na 2ª jogda
                                 else if(naipe == 50){
                                    compra_dois(B,dois);
                                    compra_dois(B,dois);

                                }
                                //Conferindo se a carta e Curinga Escolhe Cor na 2ª jogada
                                else if (naipe == 51){
                                     //Conferindo a mao do jogador 1 na 2ª jogada carta especial usada
                                     retorno = conferencia_mao(D,um);
                                     while(retorno == 0){
                                        retirar_carta(B,&c);
                                        inserir_carta_mao(c,um);
                                        retorno = conferencia_mao(D,um);
                                     }
                                     //Especificando as cartas na 2ª jogada carta especial usada
                                     printf("\n\tAs Cartas Especiais sao:\n\t[10]-Inverter\n\t[11]-Passa a Vez\n\t[12]-Comprar +2");
                                     printf("\n\tOS Curingas sao:\n\t[50]-%s\n\t[51]-%s\n\t[52]-%s\n\n",CQ, CR, CT);
                                     //Mostrando a Mão do Jogador 1 na 2ª jogada carta especial usada
                                     imprime_mao(um);
                                     printf("\n\tA carta na mesa de descarte e :%i[%s]\n\n",D->monte_descarte[D->topo-1].naipe, D->monte_descarte[D->topo-1].cor);
                                     //Definindo a  jogada do Jogdor 1 na 2ª jogada carta especial usada
                                     printf("\n\n");
                                     descarta_mao(&naipe,&cor);
                                     //retirando a carta da mão do jogador 1 na 2ª jogada carta especial usada
                                     retorno = remover_mao(um,&c,naipe,cor);
                                     if(retorno == 1){
                                            //Colocando a carta no monte de descarte na 2ªjogada carta especial usada
                                            retorno = cartas_descarte(contador,D,c);
                                            if(retorno == 1){
                                                //salvando a 2ªjogada do jogador 1 carta especial usada
                                                salvar_jogadas(D,um,fp);
                                                contador++;
                                                //Conferindo se a carta e a compra+2 na 2ª jogada carta especial usada
                                                if(naipe == 12){
                                                    //conferindo se tem carta na mesa de compra na 2ª jogada carta especial usada
                                                    retorno = confere_baralho(B);
                                                    if(retorno == 0){
                                                        //caso nao tenha trocando a mesa de descarte com a mesa de compra na 2ª jogada carta especial usada
                                                        retorno = troca_descarte(B,D);
                                                            if(retorno == 1){
                                                                //embaralhando a mesa de compra na 2ª jogada carta especial usada
                                                                embaralhar(B);
                                                                printf("\n\tTroca de mesa descarte com mesa baralho realizada!\n\n");
                                                            }
                                                            else
                                                                printf("\n\tOcorreu um erro ao trocar as mesas!\n\n");
                                                        //realizando a compra +2 na 2ª jogada carta especial usada
                                                        compra_dois(B,dois);
                                                    }
                                                }
                                                //conferindo se a carta e Curinga +4 na 2ª jogada carta especial usada
                                                else if(naipe == 50){
                                                    compra_dois(B,dois);
                                                    compra_dois(B,dois);
                                                }
                                                //Conferindo se a carta e Curinga Troca Maos na 2ª jogada carta especial usada
                                                else if(naipe == 52){
                                                    troca_maos(um,dois);
                                                }
                                            }
                                     }
                                }
                                //Conferindo se a carta e Curinga Troca Maos na 2ª jogada carta especial usada
                                else if(naipe == 52){
                                    troca_maos(um,dois);
                                }
                            }
                        }
                    }
                    //Conferindo se a carta é Especial Compra 2 na 1ª jogada
                    else if(naipe == 12){
                        retorno = confere_baralho(B);
                        if(retorno == 0){
                            retorno = troca_descarte(B,D);
                            if(retorno == 1){
                                embaralhar(B);
                                printf("\n\tTroca de mesa descarte com mesa baralho realizada!\n\n");
                            }
                            else
                                printf("\n\tOcorreu um erro ao trocar as mesas!\n\n");
                        }
                        compra_dois(B,dois);
                    }
                    //conferindo se carta jogada é Curinga+4 na 1ª jogada
                     else if(naipe == 50){
                        compra_dois(B,dois);
                        compra_dois(B,dois);

                    }
                    //Conferindo se a carta jogada é Curinga escolhe cor na 1ª jogada
                    else if (naipe == 51){

                    }
                    //Conferindo se a carta jogada é a Curinga troca maos na 1ª jogada
                    else if(naipe == 52){
                        troca_maos(um,dois);
                    }
                    //Salvando a jogada na 1ª jogada
                    salvar_jogadas(D,dois,fp);
                    printf("\n\tDescarte realizado!\n\n");
                    contador++;
                }
            }
            system("cls");
        //1ª laço do jogo conferindo se algum jogador tem cartas na mão.
        }while((um->jogador->inicio != NULL) || (dois->jogador->inicio != NULL));
        //caso algum jogador não tenha mais cartas na mão calcula a pontuação.
        pontuacao(um,dois);
        //confere qual jogador tem carta na mão e volta ela para o baralho esvaziando a mão do jogador
        if(um->jogador->inicio != NULL){
            retira_carta_mao(um,B);
        }
        else{
            retira_carta_mao(dois,B);
        }
        //Esvazia a mesa de descarte e devolve a mesa de compra
        troca_descarte(B,D);
        //embaralha a mesa de compra
        embaralhar(B);
    //2ª laço do jogo que confere se tem algum vencedor, caso alcance 500ptos ou mais o jogo encerra
    }while(um->pontos >= 500 || dois->pontos >= 500);
    //Confere quem é o vencedro e enserra o jogo.
    if(um->pontos >= 500){
        printf("\n\tO vencedor foi %s com %i", um->nome, um->pontos);
    }
    else{
        printf("\n\tO vencedor foi %s com %i", dois->nome, dois->pontos);
    }
}

//Funções de criação do baralho e das cartas
Baralho *cria_baralho(){
    Baralho *b;

    b = (Baralho*)malloc(sizeof(Baralho));
    b->topo = 0;
    return b;
}
int cartas_baralho(Baralho *B, int v, char *naipe, int tam){
    if(B->topo == 0){
        Carta *c;
        c = (Carta*)malloc(sizeof(Carta));
        c->naipe = v;
        strcpy(c->cor,naipe);
        B->monte[B->topo] = *c;
        B->monte->proximo = NULL;
        B->topo++;
        return 1;
    }
    else if(B->topo != 0){
        Carta *c;
        c = (Carta*)malloc(sizeof(Carta));
        c->naipe = v;
        strcpy(c->cor,naipe);
        B->monte[B->topo] = *c;
        B->monte->proximo = NULL;
        B->topo++;
        return 1;
    }
    else
        return 0;
}
void embaralhar(Baralho *B){
    int a, b;
    Carta aux;
    srand(time(NULL));
    for(int i = 0; i < 110; i++){
        do{
            a = rand()%110;
            b = rand()%110;
        }while (a == b);
        aux = B->monte[a];
        B->monte[a] = B->monte[b];
        B->monte[b] = aux;
    }
}
//Funções de criação da mão do jogador
Mao *criar_mao(){
    Mao *jogador;
    jogador = (Mao*)malloc(sizeof(Mao));
    jogador->inicio = NULL;
    jogador->cont = 0;
}
int distribuir_cartas(Player *j,Carta c){
    if(j == NULL){
        return 0;
    }
    else{
        Carta *m;
        m=(Carta*)malloc(sizeof(Carta));
        *m = c;
        m->proximo = NULL;
        if(j->jogador->inicio == NULL){
            j->jogador->inicio = m;
            j->jogador->cont++;
            return 1;
        }
        else{
            Carta *aux;
            aux = j->jogador->inicio;
            while(aux->proximo != NULL){
                aux = aux->proximo;
            }
            aux->proximo = m;
            j->jogador->cont++;
            return 1;
        }
    }
}
int retirar_carta(Baralho *B, Carta *c){
    if(B == NULL){
        return 0;
    }
    else{
        B->topo--;
        *c = B->monte[B->topo];
        return 1;
    }
}
//Criação da mesa de descarte e suas jogadas
Descarte *criar_descarte(){
    Descarte *d;
    d = (Descarte*)malloc(sizeof(Descarte));
    d->topo = 0;
    return d;
}
int remover_mao(Player *j,Carta *descartada,int n,char c){
    if(j->jogador->inicio == NULL)
        return 0;

    else{
        char comp[25];
        if(c == 'A'){
            strcpy(comp,A);
        }
        else if(c == 'Z'){
            strcpy(comp,Z);
        }
        else if(c == 'V'){
            strcpy(comp,V);
        }
        else if(c == 'R'){
            strcpy(comp,R);
        }
        else if(c == 'Q'){
            strcpy(comp,CQ);
        }
        else if(c == 'T'){
            strcpy(comp,CT);
        }
        else if(c == 'C'){
            strcpy(comp,CR);
        }

        Carta *aux, *ant;
        aux = j->jogador->inicio;
        int cmp = strcmp(aux->cor,comp);
        if((aux->naipe == n)&&(cmp == 0)){
            *descartada = *aux;
            j->jogador->inicio = aux->proximo;
            free(aux);
            j->jogador->cont--;
        }
        else{
            while(aux->naipe!=n || cmp!=0){
                ant = aux;
                aux = aux->proximo;
                cmp = strcmp(aux->cor,comp);
            }
            ant->proximo = aux->proximo;
            *descartada = *aux;
            free(aux);
            j->jogador->cont--;
        }
        return 1;
    }
}
int cartas_descarte(int cont,Descarte *D,Carta descartada){
    if(D->topo == 0 && cont == 0){
        if((((descartada.naipe != 10)&&(descartada.naipe != 11))&&((descartada.naipe != 12)&&(descartada.naipe != 50)))&&((descartada.naipe != 51)&&(descartada.naipe != 52))){
            D->monte_descarte[D->topo] = descartada;
            D->topo++;
            return 1;
        }
        else{
            return -1;
        }
    }
    else if(D->topo != 0){
        D->monte_descarte[D->topo] = descartada;
        D->topo++;
        return 1;
    }
    else
        return 0;
}
//Funções de inserir carta e compra carta
int inserir_carta_mao(Carta C, Player *j){
    if(j->jogador == NULL)
        return 0;
    else{
        Carta *c = (Carta*)malloc(sizeof(Carta));
        *c = C;
        c->proximo = NULL;
        if(j->jogador->inicio == NULL){
            j->jogador->inicio = c;
            j->jogador->cont++;
            return 1;
        }
        else{
            Carta *a;
            a = j->jogador->inicio;
            while(a->proximo != NULL){
                a = a->proximo;
            }
            a->proximo = c;
            j->jogador->cont++;
            return 1;
        }
    }
}
int retirar_descarte(Descarte *D, Carta *c){
    if(D->topo == 0){
        return 0;
    }
    else{
        D->topo--;
        *c = D->monte_descarte[D->topo];
        return 1;
    }
}
int conferencia_mao(Descarte *D, Player *j){
    Carta *aux;
    aux = j->jogador->inicio;
    int comp;
    comp = strcmp(D->monte_descarte[D->topo-1].cor,aux->cor);
    if(comp == 0 || D->monte_descarte[D->topo-1].naipe == aux->naipe){
        return 1;
    }
    else{
        if((D->monte_descarte[D->topo-1].naipe == 10) || (D->monte_descarte[D->topo-1].naipe == 11) || (D->monte_descarte[D->topo-1].naipe == 12)){
            while(aux != NULL){
            comp = strcmp(D->monte_descarte[D->topo-1].cor,aux->cor);
            if(comp == 0){
                return 1;
            }
            aux = aux->proximo;
        }
        return 0;
        }
        else{
            while(aux != NULL){
                comp = strcmp(D->monte_descarte[D->topo-1].cor,aux->cor);
                if(comp == 0 || (D->monte_descarte[D->topo-1].naipe == aux->naipe)||((D->monte_descarte[D->topo-1].naipe == 50)||(D->monte_descarte[D->topo-1].naipe ==51)||(D->monte_descarte[D->topo-1].naipe == 52))){
                    return 1;
                }
                aux = aux->proximo;
            }
        }
        return 0;
    }
}
int compra_dois(Baralho *B, Player *a){
    Carta c;
    int ret;
    for(int i=0;i<2;i++){
        ret = retirar_carta(B,&c);
        if(ret == 1){
            ret = inserir_carta_mao(c,a);
        }
        else{
            return 0;
        }
    }
    return 1;
}
//Funções das jogadas
void imprime_mao(Player *j){
    Carta *aux;
    printf("\n\tAs cartas que estao na mao de %s sao:\n", j->nome);
    aux = j->jogador->inicio ;
    while(aux != NULL){
        printf("\n\t%i[%s]",aux->naipe,aux->cor);
        aux = aux->proximo;
    }
}
void descarta_mao(int *naipe, char *cor){
    int n;
    char c;
    printf("\n\tDigite o Naipe da Carta: ");
    scanf("%i", &n);
    printf("\n\tDigite a cor de acordo com as opcoes abaixo:\n\t[A]-%s\n\t[Z]-%s\n\t[V]-%s\n\t[R]-%s\n\t[Q]-%s\n\t[C]-%s\n\t[T]-%s: ",A, Z, V, R, CQ, CR, CT);
    setbuf(stdin,NULL);
    scanf("%c", &c);
    *naipe = n;
    *cor = c;
}
void pontuacao(Player *um, Player *dois){
    Carta *aux;
    if(um->jogador->inicio == NULL){
        aux = dois->jogador->inicio;
        um->pontos = 0;
        while(aux != NULL){
            if(aux->naipe == 10 || aux->naipe ==11 || aux->naipe == 12){
                um->pontos += 20;
            }
            else if(aux ->naipe > 49){
                um->pontos += 50;
            }
            else{
                um->pontos += aux->naipe;
            }
            aux = aux->proximo;
        }
    }
    else{
        aux = um->jogador->inicio;
        dois->pontos = 0;
        while(aux != NULL){
            if(aux->naipe == 10 || aux->naipe ==11 || aux->naipe == 12){
                dois->pontos += 20;
            }
            else if(aux ->naipe > 49){
                dois->pontos += 50;
            }
            else{
                dois->pontos += aux->naipe;
            }
            aux = aux->proximo;
        }
    }
}
void retorna_baralho(Baralho *B, Carta c){
    B->monte[B->topo] = c;
    B->topo++;
}
void retira_carta_mao(Player *j, Baralho *B){
    Carta *aux, *prox;
    Carta C;
    aux = j->jogador->inicio;
    while(aux != NULL){
        C=*aux;
        retorna_baralho(B,C);
        prox = aux->proximo;
        free(aux);
        aux = prox;
    }
    free(aux);
    free(prox);
}
int confere_baralho(Baralho *B){
    if(B->topo == 0){
        return 0;
    }
    else{
        return 1;
    }
}
int troca_descarte(Baralho *B, Descarte *D){
    if(B->topo ==0 || D->topo > 0){
        for(int i = B->topo; i<D->topo; i++){
            D->topo--;
            B->monte[i] = D->monte_descarte[D->topo];
            B->topo++;
        }
        return 1;
    }
    else
        return 0;
}
void troca_maos(Player *um, Player *dois){
    Carta auxum, auxdois;
    auxum = *um->jogador->inicio;
    auxdois = *dois->jogador->inicio;
    *dois->jogador->inicio = auxum;
    *um->jogador->inicio = auxdois;
}
void salvar_jogadas(Descarte *D, Player *j, FILE *fp){
    fp = fopen("Jogadas.txt", "w+");
    fprintf(fp,"\n\tJogada %s, %i[%s]\n", j->nome, D->monte_descarte[D->topo-1].naipe,D->monte_descarte[D->topo-1].cor);
    fclose(fp);
}


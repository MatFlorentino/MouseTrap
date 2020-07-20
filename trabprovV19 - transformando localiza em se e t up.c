/*
    Este programa simula o jogo Mouse Trap, originalmente produzido para o Atari.
    Escrito em c, para apresenta��o na disciplina algoritmos e programa��o - Ufrgs - 2018/02
    Programadores: Mateus de Avila Florentino, Maxwell Mendes Dorneles

    Principais regras do jogo:

    -O rato precisa pegar todos os queijos do labirinto
    -Cada queijo adquirido, o jogador recebe 10 pontos
    -Caso um gato pegue o rato, fim de jogo
    -O labirinto possui 7 portas, que podem ser abertas ou fechadas
    -O jogo disponibiliza 4 ossos, os quais, quando adquiridos pelo rato:
    --Transforma o rato em cachorro por 6 segundos aproxmadamente
    --Enquanto em modo cachorro, o rato pode pegar qualquer gato
    --Caso o rato em modo cachorro pegue um gato:
    ---O jogador recebe 100 pontos
    ---Os rator se teletransportam para suas posi��es iniciais

    CONTROLES:

    A,S,D,W => respectivamente: esquerda, baixo, direita, cima

    Setas direcionais => esquerda, baixo, direita, cima

    B => Abre ou fecha as portas

    ESC => Fecha o jogo


    *O jogo nao possui menu, todas informa�oes necess�rias estaram dispostas durante a jogatina

    */

#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#define TAMMATRIZ1 11
#define TAMMATRIZ2 28

#define XX 219      //CONTANSTES RESPONSAVEIS PELO CODIGO ASCII DO CARACTER IMPRIMIDO
#define QQ 46       //EXEMPLO: QQ == 46, SIGNIFICA QUE O 'Q' DO ARQUIVO TEXTO,
#define MM 62       //SERA SUBSTITUIDO PELO CARACTER DE CODIGO 46.
#define TT 178
#define OO 123


typedef struct tipo_informacoes         //Estrutura criada para facilitar o envio/recebimento de informa�oes
{                                       //entre todas as fun��es do jogo
    int posicaorato[2];                             //indica posicao atual do rato, indice 0 = coluna, indice 1 = linha
    int posicaogatos[8];                            //indica posicao atual dos 4 gatos
    int posicaoossos[8];                            //indica posi��o atual dos 4 ossos
    int localizacaoportas[14];                      //indica posi��o atual das 7 portas
    int posicaodasportas;                           //indica se a porta esta aberta ou fechada, 0 ou 1
    int tempocachorro;                              //calcula quanto tempo resta em modo cachorro
    int pontos;                                     //calcula os pontos totais do jogador
    int posicaogatosoriginal[8];                    //grava a posicao inicial dos gatos
    int movgato[8];                                 //grava a dire��o em que cada gato esta indo
} INFM;



/*Funcao dedicada a realizar as intera��es do jogador a partir do teclado

-Movimenta o rato
-Abre ou Fecha as portas
-Verifica, Ativa e Desativa o Modo cachorro

Altera a variavel "cod" por um switch e realiza individualmente a opera��o referente,
inclusive verificando possiveis conflitos, como por exemplo ao se chocar com um gato,
� necessario verificar se o modocachorro esta ativo ou n�o
*/

int swith_movimento(char matriz[TAMMATRIZ1][TAMMATRIZ2], char cod, INFM *originalinformes)
{
    INFM informes;
    informes=*originalinformes;
    char proximoobstaculo= {'a'};
    int pontos=0, i, flag=0, a;

//Varivavel cod possui a entrada do teclado
    switch(cod)
    {
    case 'w':
    case 'W':
    case 72: //tecla cima
    {
        if(matriz[informes.posicaorato[0]-1][(informes.posicaorato[1])]==' ')
        {
            matriz[informes.posicaorato[0]][(informes.posicaorato[1])]=' ';
            matriz[informes.posicaorato[0]-1][(informes.posicaorato[1])]=MM;
            informes.posicaorato[0]=informes.posicaorato[0]-1;
        }
        else if(matriz[informes.posicaorato[0]-1][(informes.posicaorato[1])]==QQ)
        {
            pontos=1;
            matriz[informes.posicaorato[0]][(informes.posicaorato[1])]=' ';
            matriz[informes.posicaorato[0]-1][(informes.posicaorato[1])]=MM;
            informes.posicaorato[0]=informes.posicaorato[0]-1;
        }
        else if(matriz[informes.posicaorato[0]-1][(informes.posicaorato[1])]==OO)
        {
            matriz[informes.posicaorato[0]][(informes.posicaorato[1])]=' ';
            matriz[informes.posicaorato[0]-1][(informes.posicaorato[1])]=MM;
            informes.posicaorato[0]=informes.posicaorato[0]-1;
            informes.tempocachorro=50;
        }
        else if(matriz[informes.posicaorato[0]-1][(informes.posicaorato[1])]=='G')
            if(informes.tempocachorro>0)
            {
                informes.pontos=informes.pontos+10;
                flag=1;
            }



        break;

    }
    case 'a':
    case 'A':
    case 75: //seta esquerda
    {
        if(matriz[informes.posicaorato[0]][(informes.posicaorato[1])-1]==' ')
        {
            matriz[informes.posicaorato[0]][(informes.posicaorato[1])]=' ';
            matriz[informes.posicaorato[0]][(informes.posicaorato[1]-1)]=MM;
            informes.posicaorato[1]=informes.posicaorato[1]-1;
        }
        else if(matriz[informes.posicaorato[0]][(informes.posicaorato[1])-1]==QQ)
        {
            pontos=1;
            matriz[informes.posicaorato[0]][(informes.posicaorato[1])]=' ';
            matriz[informes.posicaorato[0]][(informes.posicaorato[1]-1)]=MM;
            informes.posicaorato[1]=informes.posicaorato[1]-1;
        }
        else if(matriz[informes.posicaorato[0]][(informes.posicaorato[1])-1]==OO)
        {
            matriz[informes.posicaorato[0]][(informes.posicaorato[1])]=' ';
            matriz[informes.posicaorato[0]][(informes.posicaorato[1]-1)]=MM;
            informes.posicaorato[1]=informes.posicaorato[1]-1;
            informes.tempocachorro=50;
        }
        else if(matriz[informes.posicaorato[0]][(informes.posicaorato[1])-1]=='G')
            if(informes.tempocachorro>0)
            {
                informes.pontos=informes.pontos+10;
                flag=1;
            }
        break;
    }
    case 'd':
    case 'D':
    case 77: //seta direira
    {
        if(matriz[informes.posicaorato[0]][(informes.posicaorato[1])+1]==' ')
        {
            matriz[informes.posicaorato[0]][(informes.posicaorato[1])]=' ';
            matriz[informes.posicaorato[0]][(informes.posicaorato[1]+1)]=MM;
            informes.posicaorato[1]=informes.posicaorato[1]+1;
        }
        else if(matriz[informes.posicaorato[0]][(informes.posicaorato[1])+1]==QQ)
        {
            pontos=1;
            matriz[informes.posicaorato[0]][(informes.posicaorato[1])]=' ';
            matriz[informes.posicaorato[0]][(informes.posicaorato[1]+1)]=MM;
            informes.posicaorato[1]=informes.posicaorato[1]+1;
        }
        else if(matriz[informes.posicaorato[0]][(informes.posicaorato[1])+1]==OO)
        {
            matriz[informes.posicaorato[0]][(informes.posicaorato[1])]=' ';
            matriz[informes.posicaorato[0]][(informes.posicaorato[1]+1)]=MM;
            informes.posicaorato[1]=informes.posicaorato[1]+1;
            informes.tempocachorro=50;
        }
        else if(matriz[informes.posicaorato[0]][(informes.posicaorato[1])+1]=='G')
            if(informes.tempocachorro>0)
            {
                informes.pontos=informes.pontos+10;
                flag=1;
            }

        break;
    }
    case 's':
    case 'S':
    case 80: //seta baixo
    {
        if(matriz[informes.posicaorato[0]+1][(informes.posicaorato[1])]==' ')
        {
            matriz[informes.posicaorato[0]][(informes.posicaorato[1])]=' ';
            matriz[informes.posicaorato[0]+1][(informes.posicaorato[1])]=MM;
            informes.posicaorato[0]=informes.posicaorato[0]+1;
        }
        else if(matriz[informes.posicaorato[0]+1][(informes.posicaorato[1])]==QQ)
        {
            pontos=1;
            matriz[informes.posicaorato[0]][(informes.posicaorato[1])]=' ';
            matriz[informes.posicaorato[0]+1][(informes.posicaorato[1])]=MM;
            informes.posicaorato[0]=informes.posicaorato[0]+1;
        }
        else if(matriz[informes.posicaorato[0]+1][(informes.posicaorato[1])]==OO)
        {
            matriz[informes.posicaorato[0]][(informes.posicaorato[1])]=' ';
            matriz[informes.posicaorato[0]+1][(informes.posicaorato[1])]=MM;
            informes.posicaorato[0]=informes.posicaorato[0]+1;
            informes.tempocachorro=50;
        }
        else if(matriz[informes.posicaorato[0]+1][(informes.posicaorato[1])]=='G')
            if(informes.tempocachorro>0)
            {
                informes.pontos=informes.pontos+10;
                flag=1;
            }
        break;
    }
    case 'b':
    case 'B':
    {
        if(informes.posicaodasportas==1)
        {
            informes.posicaodasportas=0;
            for(i=0; i<13; i=i+2)

            {
                matriz[informes.localizacaoportas[i]][informes.localizacaoportas[i+1]]=TT;
                matriz[informes.localizacaoportas[i]+1][informes.localizacaoportas[i+1]+1]=' ';
            }
        }
        else
        {
            informes.posicaodasportas=1;
            for(i=0; i<13; i=i+2)
            {
                matriz[informes.localizacaoportas[i]][informes.localizacaoportas[i+1]]=' ';
                matriz[informes.localizacaoportas[i]+1][informes.localizacaoportas[i+1]+1]=TT;
            }
        }
        break;
    }
    }
    if(flag==1)
    {
        for(a=0; a<8; a=a+2)
        {
            matriz[informes.posicaogatos[a]][informes.posicaogatos[a+1]]=' ';
            informes.posicaogatos[a]=informes.posicaogatosoriginal[a];
            informes.posicaogatos[a+1]=informes.posicaogatosoriginal[a+1];
            matriz[informes.posicaogatos[a]][informes.posicaogatos[a+1]]='G';
        }
        flag=0;
    }

    *originalinformes=informes;
    return (pontos);
}
/*Fun��o dedicada a localizar todos */
void localiza(char matrizentri[TAMMATRIZ1][TAMMATRIZ2], INFM *originalinformes)
{
    /*encontra a posicao do rato, dos gatos, dos ossos e das portas*/

    int a, b, i=0, o=0, g=0;
    INFM informes;
    informes=*originalinformes;

    for(a=0; a<TAMMATRIZ1; a++)
    {
        for(b=0; b<TAMMATRIZ2; b++)
        {
            if(matrizentri[a][b]=='T')
            {
                informes.localizacaoportas[i]=a;
                i=i+1;
                informes.localizacaoportas[i]=b;
                i=i+1;
            }
            else  if(matrizentri[a][b]=='M' || matrizentri[a][b]=='m')
            {
                informes.posicaorato[0]=a;
                informes.posicaorato[1]=b;
            }
            else if(matrizentri[a][b]=='O' || matrizentri[a][b]=='o')
            {
                informes.posicaoossos[o]=a;
                o=o+1;
                informes.posicaoossos[o]=b;
                o=o+1;
            }
            else if(matrizentri[a][b]=='G' || matrizentri[a][b]=='g')
            {
                informes.posicaogatos[g]=a;
                g=g+1;
                informes.posicaogatos[g]=b;
                g=g+1;
            }
        }
    }
    *originalinformes=informes;
}
void movimentogatos(char matriz[TAMMATRIZ1][TAMMATRIZ2], INFM *originalinformes)
{
    INFM informes;
    informes=*originalinformes;
    int i=0, a, flag=0;
    //char temp;



    //movgato=rand() % 4;
    for(i=0; i<8; i=i+2)
    {
        //printf("\n%d\n", movgato);
        switch (informes.movgato[i])
        {
        case 0:
        {

            if(matriz[informes.posicaogatos[i]][(informes.posicaogatos[i+1])+1]==' ')
            {
                matriz[informes.posicaogatos[i]][informes.posicaogatos[i+1]+1]='G';
                matriz[informes.posicaogatos[i]][informes.posicaogatos[i+1]]=' ';
                informes.posicaogatos[i+1]=informes.posicaogatos[i+1]+1;
            }
            else if(matriz[informes.posicaogatos[i]][(informes.posicaogatos[i+1])+1]==QQ)
            {
                matriz[informes.posicaogatos[i]][informes.posicaogatos[i+1]+1]='G';
                matriz[informes.posicaogatos[i]][informes.posicaogatos[i+1]]=QQ;
                informes.posicaogatos[i+1]=informes.posicaogatos[i+1]+1;
            }
            else if(matriz[informes.posicaogatos[i]][(informes.posicaogatos[i+1])+1]==OO)
            {
                matriz[informes.posicaogatos[i]][informes.posicaogatos[i+1]+1]='G';
                matriz[informes.posicaogatos[i]][informes.posicaogatos[i+1]]=OO;
                informes.posicaogatos[i+1]=informes.posicaogatos[i+1]+1;
            }
            else if(matriz[informes.posicaogatos[i]][(informes.posicaogatos[i+1])+1]==MM)
            {
                if(informes.tempocachorro==0)
                {
                    printf("\n\nVoce perdeu!!");
                    Sleep(3000000);
                }
            }
            else
                informes.movgato[i]=rand() % 4;
        }
        break;
        case 1:
        {
            if(matriz[informes.posicaogatos[i]-1][(informes.posicaogatos[i+1])]==' ')
            {
                matriz[informes.posicaogatos[i]-1][(informes.posicaogatos[i+1])]='G';
                matriz[informes.posicaogatos[i]][(informes.posicaogatos[i+1])]=' ';
                informes.posicaogatos[i]=informes.posicaogatos[i]-1;
            }
            else if(matriz[informes.posicaogatos[i]-1][(informes.posicaogatos[i+1])]==QQ)
            {
                matriz[informes.posicaogatos[i]-1][(informes.posicaogatos[i+1])]='G';
                matriz[informes.posicaogatos[i]][(informes.posicaogatos[i+1])]=QQ;
                informes.posicaogatos[i]=informes.posicaogatos[i]-1;
            }
            else if(matriz[informes.posicaogatos[i]-1][(informes.posicaogatos[i+1])]==OO)
            {
                matriz[informes.posicaogatos[i]-1][(informes.posicaogatos[i+1])]='G';
                matriz[informes.posicaogatos[i]][(informes.posicaogatos[i+1])]=OO;
                informes.posicaogatos[i]=informes.posicaogatos[i]-1;
            }
            else if(matriz[informes.posicaogatos[i]-1][(informes.posicaogatos[i+1])]==MM)
            {
                if(informes.tempocachorro==0)
                {
                    printf("\n\nVoce perdeu!!");
                    Sleep(3000000);
                }
            }
            else
                informes.movgato[i]=rand() % 4;
        }
        break;
        case 2:
        {
            if(matriz[informes.posicaogatos[i]][(informes.posicaogatos[i+1])-1]==' ')
            {
                matriz[informes.posicaogatos[i]][(informes.posicaogatos[i+1])-1]='G';
                matriz[informes.posicaogatos[i]][(informes.posicaogatos[i+1])]=' ';
                informes.posicaogatos[i+1]=informes.posicaogatos[i+1]-1;
            }
            else if(matriz[informes.posicaogatos[i]][(informes.posicaogatos[i+1])-1]==QQ)
            {
                matriz[informes.posicaogatos[i]][(informes.posicaogatos[i+1])-1]='G';
                matriz[informes.posicaogatos[i]][(informes.posicaogatos[i+1])]=QQ;
                informes.posicaogatos[i+1]=informes.posicaogatos[i+1]-1;
            }
            else if(matriz[informes.posicaogatos[i]][(informes.posicaogatos[i+1])-1]==OO)
            {
                matriz[informes.posicaogatos[i]][(informes.posicaogatos[i+1])-1]='G';
                matriz[informes.posicaogatos[i]][(informes.posicaogatos[i+1])]=OO;
                informes.posicaogatos[i+1]=informes.posicaogatos[i+1]-1;
            }
            else if(matriz[informes.posicaogatos[i]][(informes.posicaogatos[i+1])-1]==MM)
            {
                if(informes.tempocachorro==0)
                {
                    printf("\n\nVoce perdeu!!");
                    Sleep(3000000);
                }
            }
            else
                informes.movgato[i]=rand() % 4;
        }
        break;
        case 3:
        {
            if(matriz[informes.posicaogatos[i]+1][(informes.posicaogatos[i+1])]==' ')
            {
                matriz[informes.posicaogatos[i]+1][(informes.posicaogatos[i+1])]='G';
                matriz[informes.posicaogatos[i]][(informes.posicaogatos[i+1])]=' ';
                informes.posicaogatos[i]=informes.posicaogatos[i]+1;
            }
            else if(matriz[informes.posicaogatos[i]+1][(informes.posicaogatos[i+1])]==QQ)
            {
                matriz[informes.posicaogatos[i]+1][(informes.posicaogatos[i+1])]='G';
                matriz[informes.posicaogatos[i]][(informes.posicaogatos[i+1])]=QQ;
                informes.posicaogatos[i]=informes.posicaogatos[i]+1;
            }
            else if(matriz[informes.posicaogatos[i]+1][(informes.posicaogatos[i+1])]==OO)
            {
                matriz[informes.posicaogatos[i]+1][(informes.posicaogatos[i+1])]='G';
                matriz[informes.posicaogatos[i]][(informes.posicaogatos[i+1])]=OO;
                informes.posicaogatos[i]=informes.posicaogatos[i]+1;
            }
            else if(matriz[informes.posicaogatos[i]+1][(informes.posicaogatos[i+1])]==MM)
            {
                if(informes.tempocachorro==0)
                {
                    printf("\n\nVoce perdeu!!");
                    Sleep(3000000);
                }
            }
            else
                informes.movgato[i]=rand() % 4;
        }
        break;
        }
    }

    *originalinformes=informes;
}
int main ()
{
    char matrizentri[TAMMATRIZ1][TAMMATRIZ2];
    int  a, b;
    char c = 0;
    INFM informes;
    FILE *arquivo;
    char matriz[TAMMATRIZ1][TAMMATRIZ2];


    arquivo=fopen("nivel.txt", "r");
    informes.tempocachorro=0;
    informes.pontos=0;
    if(arquivo==NULL)
    {
        printf("erro na abertura da matriz!!\n\n");
    }
    else
        fseek(arquivo, 0, 0);
    for(a=0; a<TAMMATRIZ1; a++)
    {
        for(b=0; b<TAMMATRIZ2; b++)
        {
            matrizentri[a][b]=getc(arquivo);
        }
    }

    for(a=0; a<TAMMATRIZ1; a++)
    {
        for(b=0; b<TAMMATRIZ2; b++)
        {
            if(matrizentri[a][b]=='X')
                matriz[a][b]=XX;
            else if(matrizentri[a][b]=='Q')
                matriz[a][b]=QQ;
            else if(matrizentri[a][b]=='T')
                matriz[a][b]=TT;
            else if(matrizentri[a][b]=='O')
                matriz[a][b]=OO;
            else if(matrizentri[a][b]=='M')
                matriz[a][b]=MM;
            else if(matrizentri[a][b]=='\n')
                matriz[a][b]='\n';
            else if(matrizentri[a][b]=='G')
                matriz[a][b]='G';
            else
                matriz[a][b]=' ';
        }
    }

    informes.posicaodasportas=0;     //0=abertas 1=fechadas

    localiza(matrizentri, &informes);

    for(a=0; a<8; a=a+1)  //salva posi��o original dos gatos para ser usado no modo cachorro
    {
        //inicializa movimento dos gatos em 1 (evitar lixo)
        informes.movgato[a]=0;
        informes.posicaogatosoriginal[a]=informes.posicaogatos[a];
    }





    printf("Voce possui %d pontos\n\n%s\n", informes.pontos, matriz);


    while (c!='')                  //TROQUE A TECLA DE FIM DE JOGO
    {
        movimentogatos(matriz, &informes);
        if ( kbhit() )
        {
            c = getch();
            informes.pontos=(swith_movimento(matriz, c, &informes))+informes.pontos;
        }
        system("cls");
        printf("Voce possui %d pontos\n\n%s\n\nTecle ESC para sair do jogo", informes.pontos*10, matriz);
        if(informes.tempocachorro!=0)
        {
            printf("\nTempo restante em modo cachorro: %d",informes.tempocachorro);
            informes.tempocachorro=informes.tempocachorro-1;
        }
    }
}









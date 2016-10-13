#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BLOCK 3
#define MAX 2
/*pretendo fazer um deleta telefone e um deleta e-mail!
Ainda falta fazer o deleta contato, o reorganiza agenda,
e o reseta agenda!*/

typedef struct _strcol{

    char *string;
    int numStrings;
    int numBlocos;

}StrCol;

typedef struct _contato{

    char nome[50];
    StrCol tel;
    StrCol email;

}Contato;

Contato **agenda;
int nBlocos;
int nContatos = 0;


void inicia_agenda(void);
void insere_contato(void);
void lista_contato(void);

void main ()
{
    int item;
    inicia_agenda();
    for(;;)
    {
        item = item_menu();
        switch(item)
        {
        case 1:
            insere_contato();
            break;
        case 2:
            lista_contato();
            break;
        case 3:
            exit(0);
        }

    }

}

int item_menu(void)
{
    char s[80];
    int c;

    printf("\n");
    printf("1. Inserir um contato\n");
    printf("2. Listar contatos\n");
    printf("3. Sair\n");

    do
    {
        printf("\nEntre com sua escolha: ");
        gets(s);
        c = atoi(s);
    }
    while(c<0 || c>4);

    return c;
}

void inicia_agenda(void){

    agenda = (Contato **)malloc((BLOCK) * sizeof(Contato *));
    nBlocos = 1;

    if (agenda == NULL){

        printf("\nMemória insuficiente");
    }
}

void insere_contato(void){

    char  c;
    for(;;){

        if ((nContatos != 0) &&((nContatos%BLOCK) == 0)){

            if (nBlocos >= MAX){

               printf("\nAgenda cheia");
               return;
           }

            agenda = (Contato **)realloc(agenda,(nBlocos + 1) * BLOCK * (sizeof(Contato*)));
            nBlocos++;
        }


        agenda[nContatos] = (Contato*) malloc(sizeof(Contato));

        printf("\nEntre com o nome do contato: ");
        gets(agenda[nContatos]->nome);

        insere_telefone();
        insere_email();

        nContatos++;

        printf("\n\nDeseja continuar? (s/n): ");
        scanf("%c", &c);

        if ((c == 'n') || (c = 'N')){
            break;
        }
    }
}


void insere_telefone(void){

    char c;

    agenda[nContatos]->tel.string = (char *)malloc(BLOCK * sizeof(char)); //optei por fazer o malloc para que um único contato
    agenda[nContatos]->tel.numBlocos = 1;                                     //possa ter n números telefônicos

    if (agenda[nContatos]->tel.string = NULL){
        printf("\nMemória Insuficiente!");
    }

    for(;;){

        printf("\nEntre com o telefone do contato: ");
        scanf("%s", agenda[nContatos]->tel.string[agenda[nContatos]->tel.numStrings]); //usei o scanf pq o gets estava dando problema
        agenda[nContatos]->tel.numStrings++;

        if ((agenda[nContatos]->tel.numBlocos != 0) || (agenda[nContatos]->tel.numBlocos % BLOCK == 0)){

            if(agenda[nContatos]->tel.numBlocos >= MAX){

                    printf("\nTelefone está cheio!");
                    return;
            }

            agenda[nContatos]->tel.string = (char*)realloc(agenda[nContatos]->tel.string,(agenda[nContatos]->tel.numBlocos + 1) * BLOCK * (sizeof(char)));
            agenda[nContatos]->email.numBlocos++;

        }

        if ((c == 'n') || (c = 'N')){
            break;
        }
    }

}

void insere_email(void){

    char c;

    agenda[nContatos]->email.string = (char *)malloc(BLOCK * sizeof(char)); //optei por fazer o malloc para que um único contato
    agenda[nContatos]->email.numBlocos = 1;                                     //possa ter n números telefônicos

    if (agenda[nContatos]->email.string = NULL){
        printf("\nMemória Insuficiente!");
    }

    for(;;){

        printf("\nEntre com o telefone do contato: ");
        scanf("%s", agenda[nContatos]->email.string[agenda[nContatos]->tel.numStrings]); //usei o scanf pq o gets estava dando problema
        agenda[nContatos]->email.numStrings++;

        if ((agenda[nContatos]->email.numBlocos != 0) || (agenda[nContatos]->email.numBlocos % BLOCK == 0)){

            if(agenda[nContatos]->email.numBlocos >= MAX){

                    printf("\nTelefone está cheio!");
                    return;
            }

            agenda[nContatos]->email.string = (char*)realloc(agenda[nContatos]->email.string,(agenda[nContatos]->email.numBlocos + 1) * BLOCK * (sizeof(char)));
            agenda[nContatos]->email.numBlocos++;

        }

        if ((c == 'n') || (c = 'N')){
            break;
        }
    }

}
void ordena_agenda (void){

    Contato *fim = NULL;
    int i;
    int testeC;

    if(nContatos == 0)
        return;

    fim = agenda[nContatos]->nome;

    for (i = nContatos; i >= 0; i--){
        if(i == 0){
            agenda[i] = fim;
            break;
        }
        testeC = strcasecmp(fim->nome, agenda[i-1]->nome);
        if(testeC < 0){
            agenda[i] = agenda[i-1];
            continue;
        } else{
            agenda[i] = fim;
            break;
        }
    }

}

void lista_contato(void){

    ordena_agenda();

    int n;

    if (nContatos == 0){

        printf("\nAgenda vazia\n");
        return;
    }

    for(n = 0; n < nContatos; n++){

        printf("___Contato____");
        printf("\n<%d> %s ", n + 1, agenda[n]->nome);
        lista_tel(n, agenda[n]);
        lista_email(n, agenda[n]);
    }

    printf("\n\n");

}

void lista_tel(int n, Contato *agenda[n]){

    int i;

    if(agenda[n]->tel.numStrings == 0){
        printf("\n\nContato sem telefones!");
        return;
    }
    printf("   \n___Telefones___");
    for (i = 0; i < agenda[n]->tel.numStrings; i++){

            printf("   \n<%d> %s", i + 1, agenda[n]->tel.string[i]);
    }

}

void lista_email(int n, Contato *agenda[n]){

    int i;

    if(agenda[n]->email.numStrings == 0){
        printf("\n\nContato sem emails!");
        return;
    }

    printf("     \n___E-Mails___");

    for (i = 0; i < agenda[n]->email.numStrings; i++){

            printf("     \n<%d> %s", i + 1, agenda[n]->email.string[i]);
    }

}


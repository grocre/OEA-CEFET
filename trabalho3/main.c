#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int compara(const void *e1, const void *e2)
{
	return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);
}

//numero de arquivos em que os ceps serão repartidos na primeira instância
#define arquivos 8

int main()
{
    FILE *cep, *saida;
    Endereco *a;
    long tamanho;

    int i = 0;

    cep = fopen("cep.dat", "r"); // abrindo o arquivo
    fseek(cep, 0, SEEK_END); //determinando o tamanho do aquivo
    tamanho = ftell(cep);

    //mudando o ponteiro para o início para não atrapalhar a leitura
    fseek(cep, 0, SEEK_SET);

    char file[15];

    long linhas = tamanho / sizeof(Endereco);
    long linhasArquivo = linhas / arquivos;


    while(i < arquivos){

        a = (Endereco*) malloc(linhasArquivo*sizeof(Endereco)); 

        qsort(a, linhasArquivo, sizeof(Endereco), compara);

        fread(a, sizeof(Endereco), linhasArquivo, cep);
        sprintf(file,"Cep%d.dat",i);
        saida = fopen(file, "w");
        fwrite(a, sizeof(Endereco), linhasArquivo, saida);
        fclose(saida);
        i++;
    }

    fclose(cep);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

int compara(const void *a, const void *b)
{
    return strncmp(((Endereco *)a)->cep, ((Endereco *)b)->cep, 8);
}

//numero de arquivos em que os ceps serão repartidos na primeira instância
#define arquivos 8

int main()
{
    FILE *cep, *f1, *f2, *saida;
    Endereco *a, e1, e2;
    long tamanho;

    int i = 0;

    cep = fopen("cep.dat", "r"); // abrindo o arquivo
    fseek(cep, 0, SEEK_END);     //determinando o tamanho do aquivo
    tamanho = ftell(cep);

    //mudando o ponteiro para o início para não atrapalhar a leitura
    fseek(cep, 0, SEEK_SET);

    char file[15], file1[15], file2[15];

    long linhas = tamanho / sizeof(Endereco);
    long linhasArquivo = linhas / arquivos;

    while (i < arquivos)
    { // geração e ordenação dos primeiros arquivos .dat

        a = (Endereco *)malloc(linhasArquivo * sizeof(Endereco));

        qsort(a, linhasArquivo, sizeof(Endereco), compara);

        fread(a, sizeof(Endereco), linhasArquivo, cep);
        sprintf(file, "cep%d.dat", i);
        saida = fopen(file, "w");
        fwrite(a, sizeof(Endereco), linhasArquivo, saida);
        fclose(saida);
        i++;
    }

    int k = 0;

    while (k <= arquivos)
    {
        sprintf(file, "cep%d.dat", k);
        sprintf(file1, "cep%d.dat", k + 1);
        sprintf(file2, "cep%d.dat", arquivos + k);

        f1 = fopen(file, "r");
        f2 = fopen(file1, "r");
        saida = fopen(file2, "w");

        fread(&e1, sizeof(Endereco), 1, f1);
        fread(&e2, sizeof(Endereco), 1, f2);

        while (!feof(f1) && !feof(f2))
        {
            if (compara(&e1, &e2) < 0)
            {
                fwrite(&e1, sizeof(Endereco), 1, saida);
                fread(&e1, sizeof(Endereco), 1, f1);
            }
            else
            {
                fwrite(&e2, sizeof(Endereco), 1, saida);
                fread(&e2, sizeof(Endereco), 1, f2);
            }

            while (!feof(f1))
            {
                fwrite(&e1, sizeof(Endereco), 1, saida);
                fread(&e1, sizeof(Endereco), 1, f1);
            }

            while (!feof(f2))
            {
                fwrite(&e2, sizeof(Endereco), 1, saida);
                fread(&e2, sizeof(Endereco), 1, f2);
            }
        }

        fclose(f1);
        fclose(f2);
        fclose(saida);

        k++;
    }

    fclose(cep);

    return 0;
}

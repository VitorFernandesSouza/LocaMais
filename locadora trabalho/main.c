//o código só funfa no codeblocks
#ifdef __WIN32
#define limpar_tela "cls"
#else
#define limpar_tela "clear"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#include <time.h>

char opcao;
float seguro;
float preco_final;

typedef struct veiculo
{
    int id;
    int id_cliente;
    char nome[MAX];
    char descricao[MAX];
    char placa[MAX];
    char cor[MAX];
    int ocupante;
    float preco;
} t_veiculo;


typedef struct cliente
{
    int id;
    char nome[MAX];
    char endereco[MAX];
    char telefone[12];
    char desconto[MAX];
} t_cliente;




char menu();


void cadastrar_cliente();


void cadastrar_veiculo();


void listar_veiculos();


void listar_clientes();


t_veiculo *obter_veiculo(FILE *arq_veiculos, int id_veiculo);


t_cliente *obter_cliente(FILE *arq_clientes, int id_cliente);


void pesquisar_veiculo();

void pesquisar_cliente();


int existe_veiculo(FILE *arq_veiculos, int id_veiculo);


int existe_cliente(FILE *arq_clientes, int id_cliente);


void atualizar_veiculos(FILE *arq_veiculos, t_veiculo *veiculo_alugado);


void alugar_veiculo();

void entregar_veiculo();


void excluir_veiculo();

int str_somente_numeros(char str[]);


int main(int argc, char *argv[])
{
    char resp;


    while(1)
    {

        resp = menu();


        if(resp == '1')
            cadastrar_veiculo();
        else if(resp == '2')
            cadastrar_cliente();
        else if(resp == '3')
            listar_veiculos();
        else if(resp == '4')
            listar_clientes();
        else if(resp == '5')
            pesquisar_veiculo();
        else if(resp == '6')
            pesquisar_cliente();
        else if(resp == '7')
            alugar_veiculo();
        else if(resp == '8')
            entregar_veiculo();
        else if(resp == '9')
            excluir_veiculo();
        else if(resp == '0')
            break;
        else
        {
            printf("\nOpcao invalida! Pressione <Enter> para continuar...");
            scanf("%*c");

            fseek(stdin, 0, SEEK_END);
        }
        system(limpar_tela);
    }

    printf("\nAte logo!\n");
    return 0;
}


char menu()
{
    char resp[2];

    printf("------------------------------------------------- Locadora  LocaMais --------------------------------------------------\n");
    printf("Criadores: Vitor Fernandes e Beatriz de Oliveira");
    printf(" \nEscolha o que voce deseja fazer:");
    printf("\n\n 1 - Cadastrar um veiculo\n");
    printf(" 2 - Cadastrar um cliente\n");
    printf(" 3 - Listar todos os veiculos\n");
    printf(" 4 - Listar todos os clientes\n");
    printf(" 5 - Pesquisar por veiculo\n");
    printf(" 6 - Pesquisar por cliente\n");
    printf(" 7 - Alugar um veiculo\n");
    printf(" 8 - Entregar um veiculo\n");
    printf(" 9 - Excluir um veiculo\n");
    printf(" 0 - Sair\n");
    printf(" Digite o numero da opcao: ");
    scanf("%1s%*c", resp);

    fseek(stdin, 0, SEEK_END);
    return resp[0];
}



int str_somente_numeros(char str[])
{
    int i = 0;
    int len_str = strlen(str);

    for(i = 0; i < len_str; i++)
    {
        if(str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}



void cadastrar_cliente()
{
    int c,desconto;
    int idade = 0;

    FILE *arq_clientes = fopen("clientes.bin", "a+b");


    if(arq_clientes == NULL)
    {
        printf("\nFalha ao abrir arquivo(s)!\n");
        exit(1);
    }

    int cont_bytes = 0;


    fseek(arq_clientes, 0, SEEK_END);

    cont_bytes = ftell(arq_clientes);

    t_cliente cliente;

    if(cont_bytes == 0)
    {

        cliente.id = 1;
    }
    else
    {
        t_cliente ultimo_cliente;


        fseek(arq_clientes, cont_bytes - sizeof(t_cliente), SEEK_SET);


        fread(&ultimo_cliente, sizeof(t_cliente), 1, arq_clientes);


        cliente.id = ultimo_cliente.id + 1;
    }

    printf("\nDigite o nome do cliente: ");
    scanf("%99[^\n]%*c", cliente.nome);
    printf("\nDigite o endereco do cliente: ");
    scanf("%99[^\n]%*c", cliente.endereco);
    printf("\nDigite o telefone do cliente: ");
    scanf("%99[^\n]%*c", cliente.telefone);
    printf("\nDigite a idade do cliente: ");
    scanf("%i", &desconto);
if (desconto>59)
{
    printf("Parabens vc ganhou 5%% de desconto");
}
else
{
    printf("nao foi dessa vez");
}

    fseek(stdin, 0, SEEK_END);

    fseek(arq_clientes, 0, SEEK_END);

    fwrite(&cliente, sizeof(t_cliente), 1, arq_clientes);


    fclose(arq_clientes);

    printf("\nCliente \"%s\" cadastrado com sucesso!\n", cliente.nome);
    printf("\nPressione <Enter> para continuar...");
    scanf("%*c");
    fseek(stdin, 0, SEEK_END);
}



void cadastrar_veiculo()
{
    float soma;
    int dias, diaria;

    FILE *arq_veiculos = fopen("veiculos.bin", "a+b");

    if(arq_veiculos == NULL)
    {
        printf("\nFalha ao abrir arquivo(s)!\n");
        exit(1);
    }
    t_veiculo veiculo;

    int cont_bytes = 0;

    fseek(arq_veiculos, 0, SEEK_END);

    cont_bytes = ftell(arq_veiculos);

    if(cont_bytes == 0)
    {

        veiculo.id = 1;
    }
    else
    {
        t_veiculo ultimo_veiculo;

        fseek(arq_veiculos, cont_bytes - sizeof(t_veiculo), SEEK_SET);

        fread(&ultimo_veiculo, sizeof(t_veiculo), 1, arq_veiculos);

        veiculo.id = ultimo_veiculo.id + 1;
    }

    printf("\nDigite o nome do veiculo: ");
    scanf("%99[^\n]%*c", veiculo.nome);
    printf("\nDigite a descricao do veiculo: ");
    scanf("%99[^\n]%*c", veiculo.descricao);
    printf("\nDigite a cor do veiculo: ");
    scanf("%99[^\n]%*c", veiculo.cor);
    printf("\nDigite a placa do veiculo: ");
    scanf("%99[^\n]%*c", veiculo.placa);
    printf("\nDigite quantos ocupantes podem no veiculo: ");
    scanf("%i", &veiculo.ocupante);
    printf("\nDigite o preco da diaria do veiculo: ");
    scanf("%f", &veiculo.preco);
    printf("\nDigite a quantidade de dias de alocacao: ");
    scanf("%i", &dias);
    printf("-Digite a idade do cliente \n");


    diaria=veiculo.preco*dias;

    fseek(stdin, 0, SEEK_END);

    printf("\nDeseja pagar pelo seguro? (S ou N)");
    opcao = getchar();
    if (opcao >= 'a' && opcao <= 'z')
        opcao = (char)((int)'A' + (int)opcao - (int)'a');


    if (opcao == 'S')
    {
        printf("\nSeguro adiquirido!\n");

        soma=diaria+50;
        printf("O valor do carro com o seguro e de %2.f!\n", soma);
    }

    scanf("%*c");

    if (opcao == 'N')
    {
        printf("Seguro nao adiquirido.\n");
        printf("O valor do carro sem o seguro e de %2.f!\n", veiculo.preco);
    }


    veiculo.id_cliente = -1;
    fseek(arq_veiculos, 0, SEEK_END);
    fwrite(&veiculo, sizeof(t_veiculo), 1, arq_veiculos);
    fclose(arq_veiculos);

    printf("\nveiculo \"%s\" cadastrado com sucesso!\n", veiculo.nome);
    printf("\nPressione <Enter> para continuar...");
    scanf("%*c");

    fseek(stdin, 0, SEEK_END);
}


void listar_clientes()
{
    FILE *arq_clientes = fopen("clientes.bin", "rb");

    if(arq_clientes == NULL)
    {
        printf("\nFalha ao abrir arquivo(s) ou ");
        printf("Nenhum cliente cadastrado.\n");
        printf("\nPressione <Enter> para continuar...");
        scanf("%*c");

        fseek(stdin, 0, SEEK_END);
        return;
    }

    int encontrou_clientes = 0;
    t_cliente cliente;

    printf("\nListando todos os clientes...\n");
    while(1)
    {
        size_t result = fread(&cliente, sizeof(t_cliente), 1, arq_clientes);

        if(result == 0)
            break;

        encontrou_clientes = 1;

        printf("\nID do cliente: %d\n", cliente.id);
        printf("Nome do cliente: %s\n", cliente.nome);
        printf("Endereco do cliente: %s\n", cliente.endereco);
        printf("Telefone do cliente: %s\n", cliente.telefone);


    }

    if(encontrou_clientes == 0)
        printf("\nNenhum cliente cadastrado.\n");

    fclose(arq_clientes);

    printf("\nPressione <Enter> para continuar...");
    scanf("%*c");

    fseek(stdin, 0, SEEK_END);
}


t_cliente *obter_cliente(FILE *arq_clientes, int id_cliente)
{
    rewind(arq_clientes);

    t_cliente *cliente;

    cliente = (t_cliente *)malloc(sizeof(t_cliente));
    while(1)
    {

        size_t result = fread(cliente, sizeof(t_cliente), 1, arq_clientes);

        if(result == 0)
        {
            free(cliente);
            return NULL;
        }
        if(cliente->id == id_cliente)
            break;
    }
    return cliente;
}


void listar_veiculos()
{

    FILE *arq_veiculos = fopen("veiculos.bin", "rb");
    FILE *arq_clientes = fopen("clientes.bin", "rb");

    if(arq_veiculos == NULL)
    {
        printf("\nFalha ao abrir arquivo ou ");
        printf("Nenhum veiculo cadastrado.\n");
        printf("\nPressione <Enter> para continuar...");
        scanf("%*c");
        fseek(stdin, 0, SEEK_END);
        return;
    }
    int encontrou_veiculos = 0;
    printf("\nListando todos os veiculos...\n");
    t_veiculo veiculo;
    while(1)
    {
        size_t result = fread(&veiculo, sizeof(t_veiculo), 1, arq_veiculos);

        if(result == 0)
            break;

        encontrou_veiculos = 1;

        printf("\nID do veiculo: %d\n", veiculo.id);
        printf("Nome do veiculo: %s\n", veiculo.nome);
        printf("Descricao do veiculo: %s\n", veiculo.descricao);
        printf("Cor do veiculo: %s\n", veiculo.cor);
        printf("Placa do veiculo: %s\n", veiculo.placa);
        printf("Ocupantes do veiculo: %i\n", veiculo.ocupante);
        printf("Preco da diaria: R$ %.2f\n", veiculo.preco);

        if(veiculo.id_cliente != -1)
        {

            if(arq_clientes == NULL)
            {
                printf("\nFalha ao abrir arquivo!\n");
                fclose(arq_veiculos);
                exit(1);
            }
            t_cliente *cliente = obter_cliente(arq_clientes, veiculo.id_cliente);
            printf("Alugado? Sim. Cliente: %s\n", cliente->nome);
            free(cliente);
        }
        else
            printf("Disponivel? Sim\n");
    }

    if(encontrou_veiculos == 0)
        printf("\nNenhum veiculo cadastrado.\n");

    if(arq_clientes != NULL)
        fclose(arq_clientes);
    fclose(arq_veiculos);

    printf("\nPressione <Enter> para continuar...");
    scanf("%*c");

    fseek(stdin, 0, SEEK_END);
}


void pesquisar_veiculo()
{
    char nome[MAX];
    int encontrou_veiculo = 0;

    FILE *arq_veiculos = fopen("veiculos.bin", "rb");
    FILE *arq_clientes = fopen("clientes.bin", "rb");

    if(arq_veiculos == NULL)
    {
        printf("\nFalha ao abrir arquivo(s)!\n");
        exit(1);
    }

    printf("\nDigite o nome do veiculo: ");
    scanf("%99[^\n]%*c", nome);

    printf("\nveiculos com o nome \"%s\":\n\n", nome);

    t_veiculo veiculo;
    while(1)
    {
        size_t result = fread(&veiculo, sizeof(t_veiculo), 1, arq_veiculos);

        if(result == 0)
            break;

        char nome_aux[MAX];
        strcpy(nome_aux, veiculo.nome);

        if(strcmp(strupr(nome_aux), strupr(nome)) == 0)
        {
            printf("ID do veiculo: %d\n", veiculo.id);
            printf("Preco: %.2lf\n",veiculo.preco);
            if(veiculo.id_cliente != -1)
            {
                if(arq_clientes == NULL)
                {
                    printf("\nFalha ao abrir arquivo!\n");
                    fclose(arq_veiculos);
                    exit(1);
                }
                t_cliente *cliente = obter_cliente(arq_clientes, veiculo.id_cliente);
                printf("Alugado? Sim. Cliente: %s\n", cliente->nome);
                free(cliente);
            }
            else
                printf("Disponivel? Sim\n");
            encontrou_veiculo = 1;
            printf("\n");
        }
    }

    if(encontrou_veiculo == 0)
        printf("Nenhum veiculo encontrado.\n\n");

    fclose(arq_veiculos);

    printf("Pressione <Enter> para continuar...");
    scanf("%*c");

    fseek(stdin, 0, SEEK_END);
}


void pesquisar_cliente()
{
    char nome[MAX];
    int encontrou_cliente = 0;

    FILE *arq_clientes = fopen("clientes.bin", "rb");

    if(arq_clientes == NULL)
    {
        printf("\nFalha ao abrir arquivo(s)!\n");
        exit(1);
    }

    printf("\nDigite o nome do cliente: ");
    scanf("%99[^\n]%*c", nome);

    printf("\nClientes com o nome \"%s\":\n\n", nome);
    t_cliente cliente;
    while(1)
    {
        size_t result = fread(&cliente, sizeof(t_cliente), 1, arq_clientes);

        if(result == 0)
            break;

        char nome_aux[MAX];
        strcpy(nome_aux, cliente.nome);

        if(strcmp(strupr(nome_aux), strupr(nome)) == 0)
        {
            printf("ID do cliente: %d\n\n", cliente.id);
            encontrou_cliente = 1;
        }
    }

    if(encontrou_cliente == 0)
        printf("Nenhum cliente encontrado.\n\n");

    fclose(arq_clientes);

    printf("Pressione <Enter> para continuar...");
    scanf("%*c");

    fseek(stdin, 0, SEEK_END);
}


int existe_veiculo(FILE *arq_veiculos, int id_veiculo)
{
    rewind(arq_veiculos);

    t_veiculo veiculo;
    while(1)
    {

        size_t result = fread(&veiculo, sizeof(t_veiculo), 1, arq_veiculos);

        if(result == 0)
            break;

        if(veiculo.id == id_veiculo)
            return 1;
    }

    return 0;
}


int existe_cliente(FILE *arq_clientes, int id_cliente)
{
    rewind(arq_clientes);

    t_cliente cliente;

    while(1)
    {
        size_t result = fread(&cliente, sizeof(t_cliente), 1, arq_clientes);

        if(result == 0)
            break;

        if(cliente.id == id_cliente)
            return 1;
    }

    return 0;
}


t_veiculo *obter_veiculo(FILE *arq_veiculos, int id_veiculo)
{
    rewind(arq_veiculos);

    t_veiculo *veiculo;

    veiculo = (t_veiculo *)malloc(sizeof(t_veiculo));
    while(1)
    {

        size_t result = fread(veiculo, sizeof(t_veiculo), 1, arq_veiculos);

        if(result == 0)
            break;

        if(veiculo->id == id_veiculo)
            return veiculo;
    }
    free(veiculo);
    return NULL;
}


void atualizar_veiculos(FILE *arq_veiculos, t_veiculo *veiculo_alugado)
{
    rewind(arq_veiculos);

    t_veiculo veiculo;
    while(1)
    {

        size_t result = fread(&veiculo, sizeof(t_veiculo), 1, arq_veiculos);

        if(result == 0)
            break;

        if(veiculo.id == veiculo_alugado->id)
        {
            fseek(arq_veiculos, - sizeof(t_veiculo), SEEK_CUR);
            fwrite(veiculo_alugado, sizeof(t_veiculo), 1, arq_veiculos);
            break;
        }
    }
}


void alugar_veiculo()
{
    char str_id_cliente[10];
    int id_cliente;

    FILE *arq_veiculos = fopen("veiculos.bin", "rb+");
    FILE *arq_clientes = fopen("clientes.bin", "rb+");

    if(arq_veiculos == NULL)
    {
        arq_veiculos = fopen("veiculos.bin", "wb+");
        if(arq_veiculos == NULL)
        {
            printf("\nFalha ao criar arquivo(s)!\n");
            exit(1);
        }
    }

    if(arq_clientes == NULL)
    {
        arq_clientes = fopen("clientes.bin", "wb+");
        if(arq_clientes == NULL)
        {
            printf("\nFalha ao criar arquivo(s)!\n");
            exit(1);
        }
    }

    printf("\nDigite o ID do cliente: ");
    scanf("%10s%*c", str_id_cliente);

    fseek(stdin, 0, SEEK_END);

    if(str_somente_numeros(str_id_cliente) == 1)
    {
        sscanf(str_id_cliente, "%d", &id_cliente);

        if(existe_cliente(arq_clientes, id_cliente))
        {
            char str_id_veiculo[10];
            int id_veiculo;

            printf("\nDigite o ID do veiculo: ");
            scanf("%10s%*c", str_id_veiculo);


            fseek(stdin, 0, SEEK_END);



            if(str_somente_numeros(str_id_veiculo) == 1)
            {
                sscanf(str_id_veiculo, "%d", &id_veiculo);

                t_veiculo *veiculo = obter_veiculo(arq_veiculos, id_veiculo);

                if(veiculo != NULL)
                {
                    if(veiculo->id_cliente != -1)
                        printf("\nO veiculo \"%s\" ja esta alugado!\n", veiculo->nome);
                    else
                    {
                        veiculo->id_cliente = id_cliente;
                        atualizar_veiculos(arq_veiculos, veiculo);
                        printf("\nveiculo \"%s\" alugado com sucesso!\n", veiculo->nome);
                    }
                    free(veiculo);
                }
                else
                    printf("\nNao existe veiculo com o ID \"%d\".\n", id_veiculo);
            }
            else
                printf("\nO ID so pode conter numeros!\n");
        }
        else
            printf("\nNao existe cliente com o ID \"%d\".\n", id_cliente);
    }
    else

    printf("\nO ID so pode conter numeros!\n");

    fclose(arq_clientes);
    fclose(arq_veiculos);

    printf("\nPressione <Enter> para continuar...");
    scanf("%*c");

    fseek(stdin, 0, SEEK_END);

}


void entregar_veiculo()
{
    char str_id_veiculo[10];
    int id_veiculo;

    FILE *arq_veiculos = fopen("veiculos.bin", "rb+");

    if(arq_veiculos == NULL)
    {
        arq_veiculos = fopen("veiculos.bin", "wb+");
        if(arq_veiculos == NULL)
        {
            printf("\nFalha ao criar arquivo(s)!\n");
            exit(1);
        }
    }

    printf("\nDigite o ID do veiculo: ");
    scanf("%10s%*c", str_id_veiculo);

    fseek(stdin, 0, SEEK_END);

    if(str_somente_numeros(str_id_veiculo) == 1)
    {
        sscanf(str_id_veiculo, "%d", &id_veiculo);

        t_veiculo *veiculo = obter_veiculo(arq_veiculos, id_veiculo);

        if(veiculo != NULL)
        {
            if(veiculo->id_cliente == -1)
                printf("\nO veiculo \"%s\" ja esta disponivel!\n", veiculo->nome);
            else
            {
                veiculo->id_cliente = -1;
                atualizar_veiculos(arq_veiculos, veiculo);
                printf("\nveiculo \"%s\" entregue com sucesso!\n", veiculo->nome);
            }
            free(veiculo);
        }
        else
            printf("\nNao existe veiculo com o ID \"%d\".\n", id_veiculo);
    }
    else
        printf("\nO ID so pode conter numeros!\n");

    fclose(arq_veiculos);

    printf("\nPressione <Enter> para continuar...");
    scanf("%*c");

    fseek(stdin, 0, SEEK_END);
}

void excluir_veiculo()
{
    char str_id_veiculo[10];
    int id_veiculo;

    printf("\nDigite o ID do veiculo: ");
    scanf("%10s%*c", str_id_veiculo);

    fseek(stdin, 0, SEEK_END);
    if(str_somente_numeros(str_id_veiculo) == 1)
    {
        sscanf(str_id_veiculo, "%d", &id_veiculo);

        FILE *arq_veiculos = fopen("veiculos.bin", "rb");

        if(arq_veiculos == NULL)
        {
            printf("\nFalha ao abrir arquivo(s)!\n");
            exit(1);
        }

        if(existe_veiculo(arq_veiculos, id_veiculo) == 1)
        {
            char nome_veiculo[MAX];
            FILE *arq_temp = fopen("temp_veiculos.bin", "a+b");
            if(arq_temp == NULL)
            {
                printf("\nFalha ao criar arquivo temporario!\n");
                fclose(arq_veiculos);
                exit(1);
            }
            rewind(arq_veiculos);
            t_veiculo veiculo;
            while(1)
            {

                size_t result = fread(&veiculo, sizeof(t_veiculo), 1, arq_veiculos);

                if(result == 0)
                    break;

                if(veiculo.id != id_veiculo)
                {
                    fwrite(&veiculo, sizeof(t_veiculo), 1, arq_temp);
                }
                else
                    strcpy(nome_veiculo, veiculo.nome);
            }

            fclose(arq_veiculos);
            fclose(arq_temp);

            if(remove("veiculos.bin") != 0)
                printf("\nErro ao deletar o arquivo \"veiculos.bin\"\n");
            else
            {
                int r = rename("temp_veiculos.bin", "veiculos.bin");
                if(r != 0)
                {
                    printf("\nPermissao negada para renomear o arquivo!\n");
                    printf("Feche esse programa bem como o arquivo \"temp_veiculos.bin\" e renomeie manualmente para \"veiculos.bin\"\n");
                }
                else
                    printf("\nveiculo \"%s\" removido com sucesso!\n", nome_veiculo);
            }
        }
        else
        {
            fclose(arq_veiculos);
            printf("\nNao existe veiculo com o ID \"%d\".\n", id_veiculo);
        }
    }
    else
        printf("\nO ID so pode conter numeros!\n");

    printf("\nPressione <Enter> para continuar...");
    scanf("%*c");
    fseek(stdin, 0, SEEK_END);
}

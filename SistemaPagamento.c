#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h> 
#include <time.h> 
#define TAM 100
#define LIMITE_CREDITO 500.00

//Estrutura de dados 'data'
typedef struct{
	int dia;
	int mes;
	int ano;
} Data;

//Estrutura de dados 'pessoa'
typedef struct{
	char nome[80];
	char cpf[15];
	long int telefone;
	char email[50];
	Data nascimento;
} Pessoa;

//Estrutura de dados 'conta'
typedef struct{
	int num_conta;
	Pessoa cliente;
	float saldo;
	float limite;
	char senha[20];
} Conta;

//Criação de uma variável global para as contas e para o número total de contas
Conta contas[TAM];
int total_contas = 0;

//Função para validar o cpf
int validarCpf(char cpf[15]){
	if(strlen(cpf) != 14 || cpf[3] != '.' || cpf[7] != '.' || cpf[11] != '-'){
        return 0;
    }
    for(int i = 0; i < 14; i++){
        if(i == 3 || i == 7 || i == 11){
            continue;
        }
        if(cpf[i] < '0' || cpf[i] > '9'){
            return 0;
        }
    }
    return 1;
}

//Função para validar a data
int validarData(Data data){
	if(data.dia < 1 || data.dia > 30 || data.mes < 1 || data.mes > 12 || data.ano < 1920 || data.ano > 2020){
		return 0;
	}
	return 1;
}
	
//Função para validar email
int validarEmail(char email[50]){
    int tamanho = strlen(email);

    if(tamanho <= 4){
        return 0;
    }

    char *aroba = strchr(email, '@');
    if(aroba == NULL) {
        return 0;
    }

    int tamanhoDominio = strlen(aroba + 1);
    if(tamanhoDominio <= 3){
        return 0;
    }

    char *ponto = strchr(aroba, '.');
    if (ponto == NULL) {
        return 0;
    }

    char *com = strstr(ponto, "com");
    if(com == NULL || strcasecmp(com, "com") != 0){
        return 0;
    }

    return 1;
}

//Função para validar telefone
int validarTel(long int telefone){
	int tamanho = 0;
    long int temp = telefone;
    
    while(temp != 0){
        temp /= 10;
        tamanho++;
    }

    if(tamanho < 10 || tamanho > 11){
        return 0;
    }

    return 1;
}

//Função para validar senha
int validarSenha(char senha[20]){
	int i;
    int numero = 0, maiuscula = 0, minuscula = 0;
    int tamanho = strlen(senha);

    if(tamanho < 6 || tamanho > 10){
        return 0;
    }
    for(i = 0; i < tamanho; i++){
        if(senha[i] >= '0' && senha[i] <= '9'){
            numero = 1;
        }else if(senha[i] >= 'A' && senha[i] <= 'Z'){
            maiuscula = 1;
        }else if (senha[i] >= 'a' && senha[i] <= 'z'){
            minuscula = 1;
        }
    }
    if(!numero || !maiuscula || !minuscula){
        return 0;
    }
    return 1;
}

//Função para data "automática"
void data(void){
	time_t data;
	data = time(NULL);
	struct tm data_criacao = *localtime(&data);
	printf("Data de criacao da conta: %d/%d/%d\n", data_criacao.tm_mday, data_criacao.tm_mon +1, data_criacao.tm_year +1900);
}

//Função para criar uma conta
void criarConta(void){
	if(total_contas >= TAM){
        printf("\nLimite maximo de contas atingido.\n");
        return;
    }
	
    Conta nova_conta;
	printf("\nDigite seu nome:\n");
	fgets(nova_conta.cliente.nome, sizeof(nova_conta.cliente.nome), stdin);
    nova_conta.cliente.nome[strcspn(nova_conta.cliente.nome, "\n")] = '\0'; 
	
	printf("\nDigite seu CPF (000.000.000-00):\n");
	fgets(nova_conta.cliente.cpf, sizeof(nova_conta.cliente.cpf), stdin);
    nova_conta.cliente.cpf[strcspn(nova_conta.cliente.cpf, "\n")] = '\0';
    getchar();
	while(!validarCpf(nova_conta.cliente.cpf)){
        printf("\nCPF invalido. Digite novamente:\n");
        fgets(nova_conta.cliente.cpf, sizeof(nova_conta.cliente.cpf), stdin);
        nova_conta.cliente.cpf[strcspn(nova_conta.cliente.cpf, "\n")] = '\0';
        getchar();
    }
	
	printf("\nDigite o dia do seu nascimento:\n");
	scanf("%d", &nova_conta.cliente.nascimento.dia);
	printf("\nDigite o mes:\n");
	scanf("%d", &nova_conta.cliente.nascimento.mes);
    printf("\nDigite o ano:\n");
	scanf("%d", &nova_conta.cliente.nascimento.ano);
    getchar();
	while(!validarData(nova_conta.cliente.nascimento)){
        printf("\nData de nascimento invalida. Tente novamente.\n");
        printf("\nDigite o dia do seu nascimento:\n");
	    scanf("%d", &nova_conta.cliente.nascimento.dia);
	    printf("\nDigite o mes:\n");
	    scanf("%d", &nova_conta.cliente.nascimento.mes);
        printf("\nDigite o ano:\n");
	    scanf("%d", &nova_conta.cliente.nascimento.ano);
        getchar();
    }
	
	printf("\nDigite seu email:\n");
	fgets(nova_conta.cliente.email, sizeof(nova_conta.cliente.email), stdin);
    nova_conta.cliente.email[strcspn(nova_conta.cliente.email, "\n")] = '\0';
    while(!validarEmail(nova_conta.cliente.email)){
        printf("\nEmail invalido. Digite novamente:\n");
        fgets(nova_conta.cliente.email, sizeof(nova_conta.cliente.email), stdin);
        nova_conta.cliente.email[strcspn(nova_conta.cliente.email, "\n")] = '\0';
    }
	
	printf("\nDigite seu numero de telefone:\n");
	scanf("%ld", &nova_conta.cliente.telefone);
    getchar();  
    while(!validarTel(nova_conta.cliente.telefone)){
        printf("\nNumero de telefone invalido. Digite novamente:\n");
        scanf("%ld", &nova_conta.cliente.telefone);
        getchar();
    }
	
	printf("\nCrie uma senha entre 6 e 10 caracteres:\n");
	fgets(nova_conta.senha, sizeof(nova_conta.senha), stdin);
    nova_conta.senha[strcspn(nova_conta.senha, "\n")] = '\0';
    while(!validarSenha(nova_conta.senha)){
        printf("\nSenha invalida. Digite novamente:\n");
        fgets(nova_conta.senha, sizeof(nova_conta.senha), stdin);
        nova_conta.senha[strcspn(nova_conta.senha, "\n")] = '\0';
    }

    nova_conta.num_conta = total_contas + 1;
    nova_conta.saldo = 0.00;
    nova_conta.limite = LIMITE_CREDITO;
    
    contas[total_contas] = nova_conta;
    total_contas++;
    
    printf("\nConta criada com sucesso.\n\nNumero da conta: %d\n", nova_conta.num_conta);
    data();
}

//Função para depósitos
void depositar(void){
	int num_conta, conta_encontrada = 0;
    float valor;

    printf("\nDigite o numero da conta:\n");
    scanf("%d", &num_conta);
    getchar();
	
	for(int i = 0; i < total_contas; i++){
        if(contas[i].num_conta == num_conta){
            printf("\nDigite o valor a ser depositado:\n");
            scanf("%f", &valor);
            getchar();
            
            contas[i].saldo += valor;

            printf("\nDeposito realizado com sucesso.\n");
            printf("--------------------------------------------------\n");
            printf("Numero da conta: %d\n", contas[i].num_conta);
		    printf("Nome: %s\n", contas[i].cliente.nome);
            printf("CPF: %s\n", contas[i].cliente.cpf);
            printf("Telefone: %ld\n", contas[i].cliente.telefone);
            printf("Email: %s\n", contas[i].cliente.email);
            printf("Data de nascimento: %02d/%02d/%04d\n", contas[i].cliente.nascimento.dia, contas[i].cliente.nascimento.mes, contas[i].cliente.nascimento.ano);
		    data();
		    printf("Limite de credito: R$%.2f\n", contas[i].limite);
		    printf("Saldo: R$%.2f\n", contas[i].saldo);
		   
            conta_encontrada = 1;
            break;
        }
    }

    if(!conta_encontrada){
        printf("\nConta nao encontrada.\n");
    }
}

//Função para pagamentos
void pagar(void){
	int opt, num_conta_pag, conta_encontrada = 0;
    char chave_pix[50];

    printf("\nDigite o numero da sua conta:\n");
    scanf("%d", &num_conta_pag);
    getchar();
    

    printf("\nPara realizar o pagamento utilizando uma chave Pix, escolha uma opcao:\n");
    printf("1- CPF\n");
    printf("2- Email\n");
    printf("3- Numero de telefone\n");
    scanf("%d", &opt);
    getchar();
	
	if(opt == 1){
        printf("\nDigite o CPF do beneficiario:\n");
        fgets(chave_pix, sizeof(chave_pix), stdin);
        chave_pix[strcspn(chave_pix, "\n")] = '\0';
    }else if(opt == 2){
        printf("\nDigite o Email do beneficiario:\n");
        fgets(chave_pix, sizeof(chave_pix), stdin);
        chave_pix[strcspn(chave_pix, "\n")] = '\0';
    }else if(opt == 3){
        printf("\nDigite o numero de telefone do beneficiario:\n");
        fgets(chave_pix, sizeof(chave_pix), stdin);
        chave_pix[strcspn(chave_pix, "\n")] = '\0';
    }else{
        printf("\nOpcao invalida.\n");
        return;
    }

    for(int i = 0; i < total_contas; i++){
        float valor;
        if((opt == 1 && strcmp(contas[i].cliente.cpf, chave_pix) == 0) || (opt == 2 && strcmp(contas[i].cliente.email, chave_pix) == 0) || (opt == 3 && atol(chave_pix) == contas[i].cliente.telefone)){
            printf("\nDigite o valor do pagamento:\n");
            scanf("%f", &valor);
            getchar();
            
            if(contas[i].saldo + contas[i].limite < valor){
                printf("\nSaldo insuficiente.\n");
                return;
            }
            
            contas[i].saldo += valor;

            printf("\nPagamento realizado com sucesso.\n");
            printf("\n------------------Beneficiario--------------------\n");
            printf("Numero da conta: %d\n", contas[i].num_conta);
		    printf("Nome: %s\n", contas[i].cliente.nome);
		    printf("CPF: %s\n", contas[i].cliente.cpf);
            printf("Telefone: %ld\n", contas[i].cliente.telefone);
            printf("Email: %s\n", contas[i].cliente.email);

            for (int j = 0; j < total_contas; j++) {
                if (contas[j].num_conta == num_conta_pag){
                    contas[j].saldo -= valor;

                    printf("\n---------------------Pagador----------------------\n");
                    printf("Numero da conta: %d\n", contas[j].num_conta);
		            printf("Nome: %s\n", contas[j].cliente.nome);
		            printf("CPF: %s\n", contas[j].cliente.cpf);
                    printf("Telefone: %ld\n", contas[j].cliente.telefone);
                    printf("Email: %s\n", contas[j].cliente.email);
                    printf("Data de nascimento: %02d/%02d/%04d\n", contas[j].cliente.nascimento.dia, contas[j].cliente.nascimento.mes, contas[j].cliente.nascimento.ano);
		            data();
		            printf("Limite de credito: R$%.2f\n", contas[j].limite);
		            printf("Saldo: R$%.2f\n", contas[j].saldo);

                    break;
                }
            }

            conta_encontrada = 1;
            break;
        }
    }

    if(!conta_encontrada){
        printf("\nConta nao encontrada.\n");
    }
}

//Função para ver o extrato 
void extrato(void){
    int opt;

    printf("\nPara consulta o extrato, escolha uma opcao:\n");
    printf("1- Numero da conta\n");
    printf("2- Chave Pix\n");
    scanf("%d", &opt);
    getchar();

	if(opt == 1){
        int num_conta;

        printf("\nDigite o numero da conta:\n");
        scanf("%d", &num_conta);
        while (getchar() != '\n');

        for(int i = 0; i < total_contas; i++){
            if(contas[i].num_conta == num_conta){
                printf("\nExtrato para conferencia\n");
		        printf("--------------------------------------------------\n");
		        printf("Numero da conta: %d\n", contas[i].num_conta);
		        printf("Nome: %s\n", contas[i].cliente.nome);
		        printf("CPF: %s\n", contas[i].cliente.cpf);
                printf("Telefone: %ld\n", contas[i].cliente.telefone);
                printf("Email: %s\n", contas[i].cliente.email);
                printf("Data de nascimento: %02d/%02d/%04d\n", contas[i].cliente.nascimento.dia, contas[i].cliente.nascimento.mes, contas[i].cliente.nascimento.ano);
		        data();
		        printf("Limite de credito: R$%.2f\n", contas[i].limite);
		        printf("Saldo: R$%.2f\n", contas[i].saldo);
                return;
            }
        }

        printf("\nConta nao encontrada.\n");
    }else if(opt == 2){
        char chave_pix[50];

        printf("\nDigite a chave Pix:\n");
        fgets(chave_pix, sizeof(chave_pix), stdin);
        chave_pix[strcspn(chave_pix, "\n")] = '\0';

        for(int i = 0; i < total_contas; i++){
            if(strcmp(contas[i].cliente.cpf, chave_pix) == 0 || strcmp(contas[i].cliente.email, chave_pix) == 0 || atol(chave_pix) == contas[i].cliente.telefone){
                printf("\nExtrato para conferencia\n");
		        printf("--------------------------------------------------\n");
		        printf("Numero da conta: %d\n", contas[i].num_conta);
		        printf("Nome: %s\n", contas[i].cliente.nome);
		        printf("CPF: %s\n", contas[i].cliente.cpf);
                printf("Telefone: %ld\n", contas[i].cliente.telefone);
                printf("Email: %s\n", contas[i].cliente.email);
                printf("Data de nascimento: %02d/%02d/%04d\n", contas[i].cliente.nascimento.dia, contas[i].cliente.nascimento.mes, contas[i].cliente.nascimento.ano);
		        data();
		        printf("Limite de credito: R$%.2f\n", contas[i].limite);
		        printf("Saldo: R$%.2f\n", contas[i].saldo);
                return;
            }
        }

        printf("\nConta nao encontrada.\n");
    }else{
        printf("\nOpcao invalida.\n");
    }
}

//Função para listar contas
void listarContas(void){
    if(total_contas == 0){
        printf("\nNenhuma conta cadastrada.\n");
        return;
    }
    
    printf("\nContas\n");
    printf("--------------------------------------------------\n");
    for(int i=0; i<total_contas; i++) {
        printf("Numero da Conta: %d\n", contas[i].num_conta);
        printf("Nome: %s\n", contas[i].cliente.nome);
        printf("CPF: %s\n", contas[i].cliente.cpf);
        printf("Telefone: %ld\n", contas[i].cliente.telefone);
        printf("Email: %s\n", contas[i].cliente.email);
        printf("Data de Nascimento: %02d/%02d/%04d\n", contas[i].cliente.nascimento.dia, contas[i].cliente.nascimento.mes, contas[i].cliente.nascimento.ano);
        data();
		printf("Limite de credito: R$%.2f\n", contas[i].limite);
		printf("Saldo: R$%.2f\n", contas[i].saldo);
        printf("\n");
    }
}

//Função para excluir conta
void excluir(void){
	int opt;
	
    printf("\nPara excluir uma conta, escolha uma opcao:\n");
    printf("1- Numero da conta\n");
    printf("2- Chave Pix\n");
    scanf("%d", &opt);
    while(getchar() != '\n');

    if(opt == 1){
        int num_conta;

        printf("\nDigite o numero da conta:\n");
        scanf("%d", &num_conta);
        while(getchar() != '\n');
        
        for(int i = 0; i < total_contas; i++) {
            if(contas[i].num_conta == num_conta){
                printf("\nConta excluida:\n\n");
                printf("Numero da Conta: %d\n", contas[i].num_conta);
                printf("Nome: %s\n", contas[i].cliente.nome);
                printf("CPF: %s\n", contas[i].cliente.cpf);
                printf("Telefone: %ld\n", contas[i].cliente.telefone);
                printf("Email: %s\n", contas[i].cliente.email);
                printf("Data de Nascimento: %02d/%02d/%04d\n", contas[i].cliente.nascimento.dia, contas[i].cliente.nascimento.mes, contas[i].cliente.nascimento.ano);
                data();
		        printf("Limite de credito: R$%.2f\n", contas[i].limite);
		        printf("Saldo: R$%.2f\n", contas[i].saldo);
                
                for(int j = i; j < total_contas - 1; j++){
                    contas[j] = contas[j+1];
                }
                total_contas--;
                return;
            }
        }
        
        printf("\nConta nao encontrada.\n");
    }else if(opt == 2){
        char chave_pix[50];

        printf("\nDigite a chave Pix:\n");
        fgets(chave_pix, sizeof(chave_pix), stdin);
        chave_pix[strcspn(chave_pix, "\n")] = '\0';
        
        for(int i = 0; i < total_contas; i++){
            if(strcmp(contas[i].cliente.cpf, chave_pix) == 0 || strcmp(contas[i].cliente.email, chave_pix) == 0 || atol(chave_pix) == contas[i].cliente.telefone){
                printf("\nConta excluida:\n\n");
                printf("Numero da Conta: %d\n", contas[i].num_conta);
                printf("Nome: %s\n", contas[i].cliente.nome);
                printf("CPF: %s\n", contas[i].cliente.cpf);
                printf("Telefone: %ld\n", contas[i].cliente.telefone);
                printf("Email: %s\n", contas[i].cliente.email);
                printf("Data de Nascimento: %02d/%02d/%04d\n", contas[i].cliente.nascimento.dia, contas[i].cliente.nascimento.mes, contas[i].cliente.nascimento.ano);
                data();
		        printf("Limite de credito: R$%.2f\n", contas[i].limite);
		        printf("Saldo: R$%.2f\n", contas[i].saldo);
                
                for(int j = i; j < total_contas - 1; j++) {
                    contas[j] = contas[j+1];
                }
                total_contas--;
                return;
            }
        }
        
        printf("\nConta nao encontrada.\n");
    }else{
        printf("\nOpcao invalida.\n");
    }
}

//FUNÇÃO PRINCIPAL
int main(){
	setlocale(LC_ALL, "");
	
	int opt;
	
    do{
	    printf("\n\nSeja bem-vindo(a) ao Pix, um sistema de pagamentos instantaneo, onde voce pode realizar transacoes a qualquer momento e em questao de segundos.\n\n");
	    printf("Escolha uma das opcoes:\n");
	    printf("1- Criar uma conta\n");
	    printf("2- Realizar depositos\n");
	    printf("3- Realizar pagamentos com uma chave Pix\n");
	    printf("4- Consultar o extrato\n");
	    printf("5- Listar todas as contas\n");
	    printf("6- Excluir uma conta\n");
	    printf("0- Sair\n");
	    scanf("%d", &opt);
        getchar();
		
	    switch(opt){
            case 0:
                exit(0);
            case 1:
                criarConta();
                break;
            case 2:
                depositar();
                break;
            case 3:
                pagar();
                break;
            case 4:
                extrato();
                break;
            case 5:
                listarContas();
                break;
            case 6:
                excluir();
                break;
            default:
                printf("\nOpcao invalida.\n");
        }

        system("pause");
	    system("cls");

    }while(opt != 0);
    
    return 0;
}
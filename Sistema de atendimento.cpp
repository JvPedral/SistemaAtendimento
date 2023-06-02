#include <iostream>
#include <iomanip>
#include <locale.h>

using namespace std;

// Opções menu
#define SAIR 0
#define GERAR_SENHA 1
#define REALIZAR_ATENDIMENTO 2

#pragma region Funcoes Queue

struct No {
	int dado;
	No *prox;
};

struct Fila {
	No *inicial;
	No *final; 
};

Fila* init() {
	Fila *f = new Fila;
	f->inicial = NULL;
	f->final = NULL;
	return f;
}

int isEmpty(Fila *f) {
	return (f->inicial == NULL);
}

int count(Fila *f) {
	int qtd = 0;

	No *no;
	no = f->inicial;
	while (no != NULL) {
		qtd++;
		no = no->prox;
	}
	return qtd;
}

void enqueue(Fila *f, int valor) {
	No *no = new No;
	no->dado = valor;
	no->prox = NULL;

	if (isEmpty(f)) {
		f->inicial = no;
	}
	else {
		f->final->prox = no;
	}
	f->final = no;
}

int dequeue(Fila *f) {
	int ret;

	if (isEmpty(f)) {
		ret = -1;
	}
	else {
		No *no = f->inicial;
		ret = no->dado;
		f->inicial = no->prox;
		if (f->inicial == NULL) {
			f->final = NULL;
		}
		free(no);
	}
	return ret;
}

void freeFila(Fila *f) {
	No *no = f->inicial;
	while (no != NULL) {
		No *temp = no->prox;
		free(no);
		no = temp;
	}
	free(f);
}
#pragma endregion

#pragma region Funcoes genericas

void separador(){
    cout << endl << endl;
    for (int i = 0; i < 20; i++)
    {
        cout << "=";
    }
    cout << endl << endl;
    
}

#pragma endregion

int sair(Fila* senhasGeradas, Fila* senhasAtendidas){

    if(!isEmpty(senhasGeradas)){
        cout << "O programa não pode ser finalizado até que todas as senhas sejam antedidas" << endl;
        return 0;
    }

    int qtdSenhasAtendidas = count(senhasAtendidas);
    string msgSenhasAtendidasEsperando = (qtdSenhasAtendidas == 1
                ? " foi antedida"
                : " foram atendidas");

    cout << qtdSenhasAtendidas << msgSenhasAtendidasEsperando << endl;
    cout << "Obrigado por usar o sistema de filas :)" << endl;
    cout << "Volte sempre!!" << endl;    

    return 1;
}

void gerarSenha(Fila* senhasGeradas){
    int novaSenha;

    if(isEmpty(senhasGeradas)){
        novaSenha = 1;
    }else{
        novaSenha = senhasGeradas->final->dado + 1;
    }

    enqueue(senhasGeradas, novaSenha);

    cout << "Senha " << novaSenha << " gerada com sucesso!" << endl;
}

void realizarAtendimento(Fila* senhasGeradas, Fila* senhasAtendidas){
    int senhaAtendida;

    senhaAtendida = dequeue(senhasGeradas);

    if(senhaAtendida == -1){
        cout << "Não há senhas a serem atendidas " << endl;
    }else{
        enqueue(senhasAtendidas, senhaAtendida);

        cout << "Senha " << senhaAtendida << " atendida com sucesso!" << endl;
    }
}

int selecionarOpcaoMenu(Fila* senhasGeradas){
    int opcao;

    if(!isEmpty(senhasGeradas)){
        int qtdSenhas = count(senhasGeradas);
        string msgSenhasEsperando = (qtdSenhas == 1
                ? " senha esperando para ser atendida"
                : " senhas esperando para serem atendidas");

        cout << qtdSenhas << msgSenhasEsperando << endl << endl;
    }

    cout << "Escolha a opção que deseja visualizar" << endl << endl;

    cout << "0. Sair" << endl;
    cout << "1. Gerar senha" << endl;
    cout << "2. Realizar atendimento" << endl;


    cout << endl << "opção: " ;
    cin >> opcao;

    return opcao;
}

int main(int argc, char** argv){
    setlocale(LC_ALL, "");

    int opcao;
    bool podeSair = false;
    Fila* senhasGeradas = init();
    Fila* senhasAtendidas = init();

    cout << fixed;
    cout << "Bem-vindo ao projeto bilheteria";
    separador();

    while (!podeSair)
    {        
        opcao = selecionarOpcaoMenu(senhasGeradas);
        
        separador();
        switch (opcao)
        {
            case SAIR:
                podeSair = sair(senhasGeradas, senhasAtendidas);
            break;

            case GERAR_SENHA:
                gerarSenha(senhasGeradas);
            break;

            case REALIZAR_ATENDIMENTO:
                realizarAtendimento(senhasGeradas, senhasAtendidas);
            break;

            default:
                cout << endl << "Opção invalida - por favor selecione um valor de 0 até 2" << endl << endl;
            break;
        }

        separador();

    }       

    freeFila(senhasGeradas);
    freeFila(senhasAtendidas);

    return 0;
}
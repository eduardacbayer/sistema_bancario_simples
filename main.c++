#include <iostream>
#include <string>
using namespace std;

// Classe que representa um cliente do banco
class Cliente {
private:
    string nome; // Nome do cliente
    string cpf;  // CPF do cliente

public:
    // Construtor que inicializa os atributos nome e CPF
    Cliente(const string& nome, const string& cpf) 
        : nome(nome), cpf(cpf) {}

    // Métodos getter para obter o nome e CPF
    string getNome() const {
        return nome;
    }

    string getCpf() const {
        return cpf;
    }
};

// Classe que representa uma conta bancária associada a um cliente
class ContaBancaria {
private:
    int numero;           // Número da conta
    double saldo;         // Saldo da conta
    Cliente titular;      // Titular da conta (objeto Cliente)

public:
    // Construtor que inicializa o número da conta, titular e saldo opcional
    ContaBancaria(int numero, const Cliente& titular, double saldo = 0.0)
        : numero(numero), saldo(saldo), titular(titular) {}

    // Método para depositar um valor na conta
    void depositar(double valor) {
        if (valor > 0) {
            saldo += valor;
            cout << "Depositado: R$ " << valor << " na conta " << numero << endl;
        }
    }

    // Método para sacar um valor da conta com verificação de saldo
    void sacar(double valor) {
        if (valor > 0 && valor <= saldo) {
            saldo -= valor;
            cout << "Sacado: R$ " << valor << " da conta " << numero << endl;
        } else {
            cout << "Saldo insuficiente para saque.\n";
        }
    }

    // Método para transferir um valor para outra conta
    void transferir(double valor, ContaBancaria &destino) {
        if (valor > 0 && valor <= saldo) {
            saldo -= valor;
            destino.depositar(valor);
            cout << "Transferido: R$ " << valor << " da conta " << numero 
                 << " para a conta " << destino.getNumero() << endl;
        } else {
            cout << "Saldo insuficiente para transferência.\n";
        }
    }

    // Sobrecarga do método transferir para dividir o valor entre duas contas destino
    void transferir(double valor, ContaBancaria &destino1, ContaBancaria &destino2) {
        double metade = valor / 2;
        if (valor > 0 && valor <= saldo) {
            saldo -= valor;
            destino1.depositar(metade);
            destino2.depositar(metade);
            cout << "Transferido: R$ " << metade << " para cada conta (" 
                 << destino1.getNumero() << " e " << destino2.getNumero() 
                 << ") da conta " << numero << endl;
        } else {
            cout << "Saldo insuficiente para transferência.\n";
        }
    }

    // Método para exibir o saldo atual da conta
    void exibirSaldo() const {
        cout << "Saldo atual da conta " << numero << ": R$ " << saldo << endl;
    }

    // Método para exibir informações do titular e saldo da conta
    void exibirInformacoes() const {
        cout << "Titular: " << titular.getNome() << ", CPF: " << titular.getCpf() << endl;
        cout << "Número da Conta: " << numero << ", Saldo: R$ " << saldo << endl;
    }

    // Método getter para obter o número da conta
    int getNumero() const {
        return numero;
    }
};

int main() {
    // Criação dos clientes
    Cliente cliente1("Ana", "111.111.111-11");
    Cliente cliente2("Bruno", "222.222.222-22");
    Cliente cliente3("Carla", "333.333.333-33");

    // Criação das contas bancárias com saldos iniciais
    ContaBancaria conta1(1001, cliente1, 1000.0);
    ContaBancaria conta2(1002, cliente2);
    ContaBancaria conta3(1003, cliente3);

    // Exibe o saldo inicial da conta de Ana
    conta1.exibirSaldo();

    // Ana transfere R$200 para Bruno
    conta1.transferir(200.0, conta2);

    // Ana transfere R$300 divididos entre Bruno e Carla
    conta1.transferir(300.0, conta2, conta3);

    // Exibição dos saldos finais e informações dos clientes
    cout << endl;
    conta1.exibirInformacoes();
    conta2.exibirInformacoes();
    conta3.exibirInformacoes();

    return 0;
}

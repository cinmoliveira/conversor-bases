#include <iostream> //Inclui a biblioteca padrão de entrada e saída, permitindo o uso de cin e cout.
#include <cstring> //Inclui funções de manipulação de strings.

using namespace std;

// Função que converte um caractere de dígito para o valor numérico correspondente
int caractereParaValor(char caractere) {
    if (caractere >= '0' && caractere <= '9') { // Verifica se o caractere é um dígito ('0' a '9')
        return caractere - '0'; // Converte para valor numérico subtraindo o código ASCII de '0'
    } else if (caractere >= 'A' && caractere <= 'F') { // Verifica se o caractere é uma letra ('A' a 'F')
        return caractere - 'A' + 10; // Converte para valor numérico (10 a 15)
    } else if (caractere >= 'a' && caractere <= 'f') { // Verifica se o caractere é uma letra minúscula ('a' a 'f')
        return caractere - 'a' + 10; // Converte para valor numérico (10 a 15)
    } else {
        return -1; // Retorna -1 se o caractere for inválido
    }
}

// Função inversa da anterior, tem por finalidade converter um valor numérico para o caractere correspondente
char valorParaCaractere(int valor) {
    if (valor >= 0 && valor <= 9) { // Verifica se o número está entre 0 e 9
        return '0' + valor; // Converte para o caractere correspondente
    } else if (valor >= 10 && valor <= 15) { // Verifica se o número está entre 10 e 15
        return 'A' + (valor - 10); // Converte para a letra correspondente (A-F)
    } else {
        return '?'; // Retorna '?' se o valor for inválido
    }
}

// Função que converte um número da base especificada para decimal
unsigned long long paraDecimal(const char numero[], int baseOrigem) {
    unsigned long long valorDecimal = 0; // Variável para armazenar o valor decimal
    for (int i = 0; numero[i] != '\0'; i++) { // Percorre cada caractere até o final da string
        int valor = caractereParaValor(numero[i]); // Converte o caractere para valor numérico
        if (valor < 0 || valor >= baseOrigem) { // Verifica se o valor é válido na base especificada
            cout << "Dígito inválido na base " << baseOrigem << ": " << numero[i] << endl;
            return -1; // Retorna -1 se houver erro
        }
        valorDecimal = valorDecimal * baseOrigem + valor; // Acumula o valor em decimal
    }
    return valorDecimal; // Retorna o valor final em decimal
}

// Função que converte um valor decimal para uma string na base especificada
void deDecimal(unsigned long long decimal, int baseDestino, char resultado[]) {
    if (decimal == 0) { // Se o valor decimal for 0
        resultado[0] = '0'; // Resultado deve ser "0"
        resultado[1] = '\0'; // Finaliza a string
        return;
    }
    int indice = 0; // Índice para armazenar caracteres no resultado
    do {
        int resto = decimal % baseDestino; // Calcula o resto da divisão (dígito na nova base)
        resultado[indice++] = valorParaCaractere(resto); // Armazena o caractere correspondente no resultado
        decimal /= baseDestino; // Divide o número decimal pela base de destino
    } while (decimal > 0); // Continua até que o número decimal seja 0

    resultado[indice] = '\0'; // Adiciona o caractere nulo para marcar o final da string

    // Laço para inverter a string resultante, pois a conversão gera o número na ordem inversa
    for (int i = 0; i < indice / 2; i++) {
        char temp = resultado[i]; // Variável temporária para troca de posições
        resultado[i] = resultado[indice - i - 1]; // Troca o caractere na posição i com o caractere oposto
        resultado[indice - i - 1] = temp; // Completa a troca
    }
}

// Função que verifica se as bases são suportadas (2, 8, 10 e 16)
void converterBase(const char numero[], int baseOrigem, int baseDestino, char resultado[]) {
    if ((baseOrigem != 2 && baseOrigem != 8 && baseOrigem != 10 && baseOrigem != 16) ||
        (baseDestino != 2 && baseDestino != 8 && baseDestino != 10 && baseDestino != 16)) {
        cout << "Base não suportada. Escolha como opção: 2, 8, 10 ou 16." << endl;
        resultado[0] = '\0'; // Define resultado vazio em caso de erro
        return;
    }

    unsigned long long decimal = paraDecimal(numero, baseOrigem); // Converte o número da base de origem para decimal
    if (decimal == -1) { // Verifica erro na conversão
        resultado[0] = '\0';
        return;
    }
    deDecimal(decimal, baseDestino, resultado); // Converte de decimal para a base de destino
}

int main() {
    char numero[65]; // Array para armazenar o número de entrada (máx. 64 caracteres)
    int baseOrigem, baseDestino; // Variáveis para as bases de origem e destino
    char resultado[67]; // Array para armazenar o resultado da conversão

    cout << "Escolha um número: "; // Solicita ao usuário o número a ser convertido
    cin >> numero; // Lê o número da entrada do usuário
    cout << "Insira a base atual (2, 8, 10 ou 16): "; // Solicita a base de origem
    cin >> baseOrigem; // Lê a base de origem
    cout << "Base desejada para conversão (2, 8, 10 ou 16): "; // Solicita a base de destino
    cin >> baseDestino; // Lê a base de destino

    converterBase(numero, baseOrigem, baseDestino, resultado); // Chama a função de conversão de base
    cout << "Resultado: " << resultado << endl; // Exibe o resultado final da conversão

    return 0;
}



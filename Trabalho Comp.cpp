#include <iostream>
#include <vector>
#include <map>
#include <sstream>

// Renan Andrade Gomide // Matricula: 201965187AB

using namespace std;

// Funcao para aplicar o algoritmo RLE
string compressRLE(const string& input)
{
    string compressed;
    int count = 1;
    for (int i = 1; i <= input.size(); ++i)
    {
        if (i == input.size()|| input[i] != input[i - 1])
        {
            compressed += input[i -1] + to_string(count);
            count =1;
        }
        else
        {
            count++;
        }
    }
    return compressed;
}
/*
compressed: a string que armazena a versao comprimida da mensagem
count: mantem a contagem de caracteres repetidos
O loop for percorre a string de entrada
Se o caractere atual é diferente do anterior ou estamos no final da string, concatenamos o caractere anterior e a contagem na string comprimida
Se o caractere atual é igual ao anterior, incrementamos a contagem*/

//Funcao para aplicar o algoritmo LZ78
vector<pair<int, char>> compressLZ78(const string& input)
{
    vector<pair<int, char>> compressed;
    map<string, int> dictionary;
    int nextCode = 1;
    string current;

    for (char c : input)
    {
        current += c;
        if (dictionary.find(current) == dictionary.end())
        {
            dictionary[current]= nextCode++;
            compressed.emplace_back(dictionary[current.substr(0,current.size() -1)], c);
            current = "";
        }
    }

    return compressed;
}
/*
compressed: Vetor de entrada que armazenara a versao comprimida da mensagem
dictionary: vetor de strings que age como o dicionário do LZ78. A entrada vazia é adicionada no indice 0
Entry: Estrutura que armazena o indice do prefixo no dicionário e o proximo caractere
*/

int main()
{
    // Mensagem de entrada
    string mensagemOriginal = "aaaaabbbbcccddeee";

    // Aplicar compressao RLE
    string rleCompressed = compressRLE(mensagemOriginal);

    // Aplicar compressao LZ78 na saída do RLE
    vector<pair<int, char>> lz78Compressed = compressLZ78(rleCompressed);

    // Imprimir mensagem codificada
    cout << "Mensagem Original: " <<mensagemOriginal << endl;
    cout<< "Mensagem Codificada: ";

    for (const auto& entry : lz78Compressed)
    {
        cout << "(" << entry.first << "," << entry.second << ") ";
    }

    // Calcular a razao de compressao
    double razaoCompressao = static_cast<double>(rleCompressed.size()) / lz78Compressed.size();

    cout << "\nRazao de Compressao: " <<razaoCompressao << endl;

    return 0;
}

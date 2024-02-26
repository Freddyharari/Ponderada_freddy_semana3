#include <iostream>
#include <list>
#include <string>
#include <vector>

class ProductHashTable {
private:
    struct Product {
        int id;
        std::string description;
    };

    static const int hashTableSize = 10;
    std::list<Product> table[hashTableSize];

    int hashFunction(int id) {
        return id % hashTableSize;
    }

public:
    void insertProduct(int id, std::string description) {
        int index = hashFunction(id);
        auto& products = table[index];

        for (auto& prod : products) {
            if (prod.id == id) {
                prod.description = description;
                return;
            }
        }

        products.push_back({id, description});
    }

    std::string getProduct(int id) {
        int index = hashFunction(id);
        auto& products = table[index];

        for (auto& prod : products) {
            if (prod.id == id) {
                return prod.description;
            }
        }

        return "Produto não encontrado";
    }

    void printTable() {
        for (int i = 0; i < hashTableSize; ++i) {
            std::cout << "Índice " << i << ": ";
            for (auto& prod : table[i]) {
                std::cout << "{" << prod.id << ", " << prod.description << "} ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    ProductHashTable ht;

    // Teste 1: Adição e Busca de Produto
    // Pré-condição: Tabela hash vazia
    // Etapa: Adicionar um produto com ID 3 e descrição "Caderno"
    // Pós-condição: A busca pelo ID 3 deve retornar "Caderno"
    ht.insertProduct(3, "Caderno");
    std::cout << "Teste 1 - Esperado: Caderno, Obtido: " << ht.getProduct(3) << std::endl;

    // Teste 2: Atualização de Produto
    // Pré-condição: Produto com ID 2 existe com descrição diferente
    // Etapa: Atualizar a descrição do produto com ID 2 para "Apontador"
    // Pós-condição: A busca pelo ID 2 deve retornar "Apontador"
    ht.insertProduct(2, "Apontador");
    std::cout << "Teste 2 - Esperado: Apontador, Obtido: " << ht.getProduct(2) << std::endl;

    // Teste 3: Colisão e Recuperação de Produto
    // Pré-condição: Produto com ID 3 já existe
    // Etapa: Adicionar produto com ID 13, que colide com ID 3, e descrição "Lápis"
    // Pós-condição: Ambos os produtos (IDs 3 e 13) devem ser recuperáveis com suas descrições corretas
    ht.insertProduct(13, "Lápis");
    std::cout << "Teste 3 - Esperado: Caderno, Obtido: " << ht.getProduct(3) << std::endl;
    std::cout << "Teste 3 - Esperado: Lápis, Obtido: " << ht.getProduct(13) << std::endl;

    // Teste 4: Busca de Produto Não Existente
    // Pré-condição: Nenhum produto com ID 99 foi adicionado
    // Etapa: Buscar por produto com ID 99
    // Pós-condição: Deve retornar "Produto não encontrado"
    std::cout << "Teste 4 - Esperado: Produto não encontrado, Obtido: " << ht.getProduct(99) << std::endl;

    // Teste 5: Impressão da Tabela Hash
    // Pré-condição: Vários produtos adicionados à tabela
    // Etapa: Chamar a função printTable
    // Pós-condição: Todos os produtos devem ser impressos em seus respectivos índices
    std::cout << "Teste 5 - Impressão da Tabela: " << std::endl;
    ht.printTable();

    return 0;
}
#include <iostream>
#include <fstream>

#include <string>
#include <stdlib.h>


#define DATABASE_VACINA "database_vacina"


using namespace std;

void create_empty_file(string file_name);
void add_header_to_file(string a_header, string file_name);
void show_file(string file_name);
int find_row(string word, string file_name);
void read_a_line_of_the_file(string name, string file_name);
void criar_estoque(string nome_do_arquivo);

//TODO
/*
 * Adicionar novas linhas
 * Remover linhas existentes
 * Atualizar linhas existentes
 *
 * Restruturar a exibição para aparecer melhor.
 *
 * system("cls") limpa o terminal.
 */
int main() {
    /*
     * voce pode criar um arquivo em branco
     * adicionar um cabeçalho da sua maneira
     * mostrar todas linhas e colunas
     * mostrar só uma linha.
     */

    return 0;
}


void create_empty_file(string file_name) {
    /**
     * O nome do arquivo deve ser passado sem .csv
     *
     * primeiro verifica se já existe um arquivo com o mesmo nome. Se existir retorna um erro.
     * Se não existir criar um arquivo .csv com o nome passado e em branco.
     **/
    file_name.append(".csv");

    fstream file(file_name);

    if(file.fail()) {
        ofstream create_file(file_name);
        create_file.close();
    }
    file.close();
}


void add_header_to_file(string const a_header, string file_name) {
    /**
     * Os itens do header devem ser separados por virgula, e no final deve ter um \n.
     * O nome do arquivo deve ser passado sem .csv.
     *
     * Primeiro verifica se o arquivo existe.
     * Se não existir, exibi mensagem de erro.
     * Se existir adiciona o header no arquivo.
     **/
    file_name.append(".csv");

    fstream file(file_name);

    if (file.fail()) {
        cout << "Arquivo nao existe." << endl;
    }
    else {
        file << a_header;
    }
    file.close();
}


void show_file(string file_name) {
    string line;
    int count = 0;

    file_name.append(".csv");

    fstream file(file_name);

    while (!file.eof()) {
        getline(file, line);
        cout << count << " | " << line << endl;
        count++;
    }
}


int find_row(string const word, string file_name){
    /**
     * recebe uma palavra e um arquivo.
     * retorna a linha em que aquela palavra aparece pela primeira vez.
     *
     * .find() retornar a posição do primeiro caracter. Caso não encontre ele retorna
     * string::npos.
     *
     * Se a função não encontrar nenhuma ocorrencia da palavra passada ela retorna zero, caso contrário retorna
     * o número da linha que ocorre.
     **/
    string line;
    int count = 0, result;
    file_name.append(".csv");

    fstream file(file_name);

    while (!file.eof()) {
        getline(file, line);
        result = line.find(word);
        if (!result) {
            return count;
        }
        count++;
    }
    return 0;
}


void read_a_line_of_the_file(string const name, string file_name) {
    int count = 0, row;
    string line;

    row = find_row(name, file_name);

    file_name.append(".csv");


    fstream file(file_name);

    while (!file.eof()) {
        getline(file, line);
        if (count == row) {
            cout << line << endl;
        }
        count++;
    }
    file.close();
}


void criar_estoque(const string nome_do_arquivo) {
    string arquivo = nome_do_arquivo;
    string a_header = "codigo, nome, quantidade, tecnologia, descrição, tempo entre aplicacoes\n";
    arquivo.append("scv");


    fstream file(arquivo);
    if (file.fail()) {
        create_empty_file(nome_do_arquivo);
        add_header_to_file(a_header, nome_do_arquivo);
    }
    file.close();
}

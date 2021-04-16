#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <filesystem>


#define DATABASE_VACINA "database_vacina"


using namespace std;

// Funções que só podem ser usadas pelo programa
void _create_empty_csv(string file_name);
void _add_header_to_file(string a_header, string file_name);
int _find_row(string word, string file_name);
void _criar_diretorios();
void _criar_estoque(string nome_do_arquivo);                                                                             // CREATE

// Funções que podem ser usadas pelo programador
void criar_estoques();
void show_file(string file_name);                                                                                       // READ
string read_a_line_of_the_file(string name, string file_name);                                                          // READ
void adicionar_item_ao_estoque(string item, string file_name);                                                          // UPDATE
void atualizar_item_do_estoque(string atualizacao, string codigo_do_produto, string file_name);                         // UPDATE
void deletar_item_do_estoque(string codigo_do_produto, string file_name);                                               // DELETE


//TODO
/*
 * Remover linhas existentes
 *
 * Restruturar a exibição para aparecer melhor.
 *
 * system("cls") limpa o terminal.
 */

// codigo, nome, quantidade, tecnologia, descrição, tempo entre aplicacoes
int main() {
    return 0;
}


// Funções que só o programa usa.
void _create_empty_csv(string file_name) {
    /**
     * O argumento recebe uma string que é o nome do arquivo que deve ser criado
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


void _add_header_to_file(string a_header, string file_name) {
    /**
     *
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


int _find_row(string word, string file_name){
    /**
     * o primeiro parametro, word, é a palavra-chave que deve ser pesquisada no arquivo.
     * o segundo parametro, file_name, é o nome do arquivo em que a palavra-chave (word) deve ser pesquisada.
     *
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
        if (result != -1) {
            return count;
        }
        count++;
    }
    return 0;
}


// Funções em que o programador pode usar.
void show_file(string file_name) {
    /**
     * O unico argumento recebe uma variável do tipo string que é o nome do arquivo a ser aberto.
     * Exibi todas as linhas do arquivo passado.
     */
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


string read_a_line_of_the_file(const string name, string file_name) {
    /**
     * o primeiro argumento recebe uma variavel do tipo string e que é a palavra-chave única
     * do item a ser pesquisado.
     *
     * O segundo argumento recebe uma variável do tipo string que é o nome do arquivo a ser pesquisado.
     *
     * retorna 0 se a palavra-chave não for encontrada, e
     * retorna a linha se a palavra-cave for encontrada.
     */
    int count = 0, row;
    string line;

    row = _find_row(name, file_name);
    if (row == 0) {
        return "0";
    }

    file_name.append(".csv");


    fstream file(file_name);

    while (!file.eof()) {
        getline(file, line);
        if (count == row) {
            return line;
        }
        count++;
    }
    file.close();
}


void adicionar_item_ao_estoque(string item, const string file_name) {
    /**
     * primeiro argumento é uma variável do tipo string que recebe uma linha com todas as informações do item.
     * O segundo argumento é uma variável do tipo string que armazena o nome do arquivo que vai ser salvo a linha.
     *
     * A função salva a linha no final do arquivo.
     */
    string arquivo = file_name;
    arquivo.append(".csv");

    ofstream file;
    file.open(arquivo, ios::app);
    file << item << '\n';
    file.close();
}


void _criar_estoque(string nome_do_arquivo) {
    /**
     * O primeiro argumento é o nome do arquivo do estoque a ser criado.
     *
     * Dependente das funções _create_empty_csv e _add_header_to_file.
     */
    string arquivo = nome_do_arquivo;
    arquivo.append(".scv");

    string a_header = "codigo, nome, quantidade, tecnologia, descricao, tempo entre aplicacoes\n";


    fstream file(arquivo);
    if (file.fail()) {
        _create_empty_csv(nome_do_arquivo);
        _add_header_to_file(a_header, nome_do_arquivo);
    }
    file.close();
}


void atualizar_item_do_estoque(const string atualizacao, const string codigo_do_produto, const string file_name) {
    /**
     * O primeiro argumento recebe uma string que vai ser colocada no lugar da string na linha.
     * O segundo argumento recebe o codigo do produto que vai ser usado para encontrar a linha a ser atualizada.
     * O terceiro argumento recebe o nome do arquivo em que a atualização será feita.
     */
    int linha_do_item = _find_row(codigo_do_produto, file_name), linha_atual = 0;
    string arquivo = file_name, novo_arquivo = file_name, line;

    arquivo.append(".csv");
    novo_arquivo.append("_new");

    _create_empty_csv(novo_arquivo);
    novo_arquivo.append(".csv");

    fstream file;
    ofstream new_file;

    file.open(arquivo);
    new_file.open(novo_arquivo, ios::trunc);


    if (file.fail() || new_file.fail()) {
        cout << "DEBUG: não foi possível abrir o arquivo." << endl;
    }
    else {
        while (!file.eof()) {
            getline(file, line);
            string::size_type the_size = line.size();

            if (the_size == 0) continue;

            if (linha_atual == linha_do_item) {
                linha_atual++;
                new_file << atualizacao << '\n';
            }
            else {
                new_file << line << '\n';
                linha_atual++;
            }
        }
    }

    file.close();
    new_file.close();

    remove(arquivo.c_str());
    rename(novo_arquivo.c_str(), arquivo.c_str());
}


void deletar_item_do_estoque(const string codigo_do_produto, const string file_name) {
    string arquivo = file_name, novo_arquivo = file_name, line;
    int linha_do_item = _find_row(codigo_do_produto, file_name), linha_atual = 0;


    arquivo.append(".csv");
    novo_arquivo.append("_new");

    _create_empty_csv(novo_arquivo);
    novo_arquivo.append(".csv");

    fstream file;
    ofstream new_file;

    file.open(arquivo);
    new_file.open(novo_arquivo, ios::trunc);

    if (file.fail() || new_file.fail()) {
        cout << "DEGUB: Erro ao abrir os arquivo." << endl;
    }
    else {
        while (!file.eof()) {
            getline(file, line);

            if (linha_atual == linha_do_item) {
                linha_atual++;
                continue;
            }
            else {
            new_file << line << '\n';
            linha_atual++;
            }
        }
    }

    file.close();
    new_file.close();

    remove(arquivo.c_str());
    rename(novo_arquivo.c_str(), arquivo.c_str());
}


void _criar_diretorios() {
    bool diretorio_existe = filesystem::exists("databases");

    if (!diretorio_existe) {
        filesystem::create_directories("database");
    }
}


void criar_estoques() {
    _criar_estoque(".\\database\\vacina_federal");
    _criar_estoque(".\\database\\EPI_federal");
    _criar_estoque(".\\database\\medicamento_federal");
    _criar_estoque(".\\database\\vacina_AC");
    _criar_estoque(".\\database\\EPI_AC");
    _criar_estoque(".\\database\\medicamento_AC");
    _criar_estoque(".\\database\\vacina_AL");
    _criar_estoque(".\\database\\EPI_AL");
    _criar_estoque(".\\database\\medicamento_AL");
    _criar_estoque(".\\database\\vacina_AP");
    _criar_estoque(".\\database\\EPI_AP");
    _criar_estoque(".\\database\\medicamento_AP");
    _criar_estoque(".\\database\\vacina_AM");
    _criar_estoque(".\\database\\EPI_AM");
    _criar_estoque(".\\database\\medicamento_AM");
    _criar_estoque(".\\database\\vacina_BA");
    _criar_estoque(".\\database\\EPI_BA");
    _criar_estoque(".\\database\\medicamento_BA");
    _criar_estoque(".\\database\\vacina_CE");
    _criar_estoque(".\\database\\EPI_CE");
    _criar_estoque(".\\database\\medicamento_CE");
    _criar_estoque(".\\database\\vacina_ES");
    _criar_estoque(".\\database\\EPI_ES");
    _criar_estoque(".\\database\\medicamento_ES");
    _criar_estoque(".\\database\\vacina_GO");
    _criar_estoque(".\\database\\EPI_GO");
    _criar_estoque(".\\database\\medicamento_GO");
    _criar_estoque(".\\database\\vacina_MA");
    _criar_estoque(".\\database\\EPI_MA");
    _criar_estoque(".\\database\\medicamento_MA");
    _criar_estoque(".\\database\\vacina_MT");
    _criar_estoque(".\\database\\EPI_MT");
    _criar_estoque(".\\database\\medicamento_MT");
    _criar_estoque(".\\database\\vacina_MS");
    _criar_estoque(".\\database\\EPI_MS");
    _criar_estoque(".\\database\\medicamento_MS");
    _criar_estoque(".\\database\\vacina_MG");
    _criar_estoque(".\\database\\EPI_MG");
    _criar_estoque(".\\database\\medicamento_MG");
    _criar_estoque(".\\database\\vacina_PA");
    _criar_estoque(".\\database\\EPI_PA");
    _criar_estoque(".\\database\\medicamento_PA");
    _criar_estoque(".\\database\\vacina_PB");
    _criar_estoque(".\\database\\EPI_PB");
    _criar_estoque(".\\database\\medicamento_PB");
    _criar_estoque(".\\database\\vacina_PR");
    _criar_estoque(".\\database\\EPI_PR");
    _criar_estoque(".\\database\\medicamento_PR");
    _criar_estoque(".\\database\\vacina_PE");
    _criar_estoque(".\\database\\EPI_PE");
    _criar_estoque(".\\database\\medicamento_PE");
    _criar_estoque(".\\database\\vacina_PI");
    _criar_estoque(".\\database\\EPI_PI");
    _criar_estoque(".\\database\\medicamento_PI");
    _criar_estoque(".\\database\\vacina_RJ");
    _criar_estoque(".\\database\\EPI_RJ");
    _criar_estoque(".\\database\\medicamento_RJ");
    _criar_estoque(".\\database\\vacina_RN");
    _criar_estoque(".\\database\\EPI_RN");
    _criar_estoque(".\\database\\medicamento_RN");
    _criar_estoque(".\\database\\vacina_RS");
    _criar_estoque(".\\database\\EPI_RS");
    _criar_estoque(".\\database\\medicamento_RS");
    _criar_estoque(".\\database\\vacina_RO");
    _criar_estoque(".\\database\\EPI_RO");
    _criar_estoque(".\\database\\medicamento_RO");
    _criar_estoque(".\\database\\vacina_RR");
    _criar_estoque(".\\database\\EPI_RR");
    _criar_estoque(".\\database\\medicamento_RR");
    _criar_estoque(".\\database\\vacina_SC");
    _criar_estoque(".\\database\\EPI_SC");
    _criar_estoque(".\\database\\medicamento_SC");
    _criar_estoque(".\\database\\vacina_SP");
    _criar_estoque(".\\database\\EPI_SP");
    _criar_estoque(".\\database\\medicamento_SP");
    _criar_estoque(".\\database\\vacina_SE");
    _criar_estoque(".\\database\\EPI_SE");
    _criar_estoque(".\\database\\medicamento_SE");
    _criar_estoque(".\\database\\vacina_TO");
    _criar_estoque(".\\database\\EPI_TO");
    _criar_estoque(".\\database\\medicamento_TO");
    _criar_estoque(".\\database\\vacina_DF");
    _criar_estoque(".\\database\\EPI_DF");
    _criar_estoque(".\\database\\medicamento_DF");
}
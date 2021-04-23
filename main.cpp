/**
 * Integrantes :
 *      - DAVID WILSON MELO SANTOS
 *      - GABRIEL SOUZA CRUZ ARAUJO
 *      - LUCAS EDUARDO MELO ALVES
 *
 * Versão mínima do compilador C++: 17
 */

#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include <filesystem>
#include <iomanip>


/*
 * TODO
 * Adicionar uma função que formada a saida dos arquivos.
 */


#define TAMAMHO 100
#define DIRETORIO_DATABASE_VACINA_GERAL ".\\database\\vacina_federal"
#define DIRETORIO_DATABASE_EPI_GERAL ".\\database\\EPI_federal"
#define DIRETORIO_DATABASE_MEDICAMENTO_GERAL ".\\database\\medicamento_federal"

#define CABECALHO_VACINA "codigo, nome, valor, quantidade, vencimento, fabricante, tipo, doses, tempo entre doses\n"
#define CABECALHO_MEDICAMENTO "codigo, nome, valor, quantidade, vencimento, fabricante, dosagem, adm, disp\n"
#define CABECALHO_EPI "codigo, nome, valor, quantidade, vencimento, fabricante, info_dtl\n"


using namespace std;


//Nota: eu coloquei um struct de estado e uma funcao pra pegar os itens distribuidos, vejam se eh bom fazer assim
//vou fazer um struct pra vacina, medicamentos e EPIs
/*
    Eu mudei uma das funcoes que Gabreil implementou mas acho que ainda t� dando certo
    � a de consultar estoque local, que ao inv�s de receber o tipo como uma string, eu coloquei como int. A� tem uma condicao que caso seja 1 � vacina,
    2 para medicamento e 3 pra epis, da� ele faz um .append() dependendo do valor inteiro
    Eu implementei ela em um espa�o da consulta do MS
*/

// Porfavor, não mude os campos das structs. Consequencias = Apocalipse.
typedef struct Vacinas{

    string tp_vac;
    int qnt_doses;
    int intervalo;//intervalo entre as doses

}t_vac;

typedef struct Medicamentos{

    //dps dessa variaveis acima s�o as variaveis especificas pra cada struct
    string dosagem;
    string adm; // forma de adm da vacina(aplicacao no bra�o, oral, essas coisas)
    string disp; //Se � liquida, ou e uma capsula, ou sla, tem q ser dissolvida na agua(igual aqle remedio pra azia)

}t_med;

typedef struct EPI{

    //dps dessa variaveis acima s�o as variaveis especificas pra cada struct
    string info_dtl; //informa�oes detalhadas das EPI(Sla, um face shield com material q detecta uma zona q o virus ta muito concentrado)

}t_epis;

typedef struct Insumos{

    string nome;
    float valor;
    int qnt_itens;
    string d_vencimento;
    string nome_fab;
    int cdg;
    string codigo_unico;

    t_vac vac;
    t_med med;
    t_epis epi;

} t_insumos;

//Acho q eh legal agente fazer mais um struct para cadastrar os estados
//Vou deixar ela comentada qualquer coisa


//Dps eh so colocar um array[27] para cada unidade federativa


typedef struct Estados{ // (Gabriel) Aparentemente essa struct não está em uso.

    string nome_do_estado;
    string nome_do_insumo;
    float val;
    int qnt_recebida;
    string data_vencimento;
    string nome_fabricante;
    int cd;
    t_vac vc;
    t_med md;
    t_epis ep;
    //int codigo;
    //coloquem mais uma variavel aqui caso seja necessario, eu nao to conseguindo pensar uehueue

}t_est;


/*
 * Veja o espaço abaixo como um indice das funções.
 */
// Funções que só podem ser usadas pelo programa:
void _create_empty_csv(string file_name);
void _add_header_to_file(string a_header, string file_name);
int _find_row(string word, string file_name);
void _criar_diretorios();
void _criar_estoque(string nome_do_arquivo, int tipo);                                                                             // CREATE


// Funções que podem ser usadas pelo programador:
void criar_estoques();
void show_file(string file_name);                                                                                       // READ
string read_a_line_of_the_file(string name, string file_name);                                                          // READ
void adicionar_item_ao_estoque(string item, string file_name);                                                          // UPDATE
void atualizar_item_do_estoque(string atualizacao, string codigo_do_produto, string file_name);                         // UPDATE
void deletar_item_do_estoque(string codigo_do_produto, string file_name);
string t_insumo_para_string(t_insumos vacina, int tipo);
t_insumos string_para_t_insumo(const string item, const int tipo_do_insumo);


// Funções para exibir informações:
void Boas_vindas();
void Escolhaum();
void Escolhadois();
void subEscolhadois();
void Escolhatres();
void subEscolhatres();
void Escolhaquatro();
void subEscolhaquatro();
void Escolhacinco();
void exibir_estados();
void exibir_formatado(const string local, const int tipo_do_insumo);
void exibir_vacina(t_insumos insumo);
void exibir_medicamento(t_insumos insumo);
void exibir_EPI(t_insumos insumo);
void mostrar_insumo_detalhado(string codigo_unico);
//void ShowStorage(t_insumos *ins); Como tem a fun��o de acessar o estoque por meio de arquivo essa fun��o se torna desnecess�ria.


// Fun��es de Cadastro:
void Cadastro(t_insumos *i, int escolha);
void Cadastro_Est(t_est *est, int escolha, std::string estado);
void cadastrar_vacina(const t_insumos vacina, const string local);
void cadastrar_medicamentos(const t_insumos medicamentos, const string local);
void cadastrar_epis(const t_insumos medicamentos, const string local);


// Fun��es de consulta:
void Consultar_estoque_local(const string local, int choice);
void Consult(t_insumos *ins, int escolha);
void Consult_est(t_est *est, int escolha);
void consult_est_especifico(t_est *est, std::string busca);
int consultar_quantidade_dos_insumos(const string local);
void Consulta(int escolha);
int get_quantidade_de_vacinas(string local);
int get_quantidade_de_medicamentos(string local);
int get_quantidade_de_EPIs(string local);

// Modificar informações:
void diminuir_quantidade(const int quantidade, const string codigo_unico, const string local, const int tipo_do_insumo);
void aumentar_quantidade(const int quantidade, const string codigo_unico, const string local, const int tipo_do_insumo);


// Não sei mais
bool tem_no_estoque(const string codigo_unico, int tipo_do_insumo, const string estoque);
void distribuir_vacina_para(const string local);
void distribuir_medicamento_para(const string local);
void distribuir_EPI_para(const string local);


int main(){
    system("chcp 65001");
    system("cls");
    _criar_diretorios(); // So funciona no C++ +17
    criar_estoques();


    string sigla_do_estado;
    t_insumos insumos[TAMAMHO], insumo;
    t_est Estados[27];
    //eu pensei em usar essa funcao que Gabriel criou como um construtor para toda vez que o programa iniciar todas as variaveis com o banco de dados da gente
    //A� msm que nao tenha nada de primeira, os campos iniciam com um espa�o vazio e quando rodar a segunda vez j� tem os dados e j� inicia as variaveis das structs
    /*insumos = string_para_t_insumo(_find_row(), 1);
    insumos = string_para_t_insumo(_find_row(), 2);
    insumos = string_para_t_insumo(_find_row(), 3);
    */
    int n, escolha;// a variavel escolha eh a respeito da ideia q eu mencionei antes, pra caso seja decidido consultor as paradas especificando
    // se ele quer so a descri��o, tipo e zas
    char E[50];


    while(1){
        system("cls");
        Boas_vindas();
        printf("Digita aqui sua escolha:");
        cin >> n;
        //pra encerrar o programa
        if(n == 0){
            break;
        }
        switch (n){

            case 1:
                while(1){
                    system("cls");
                    Escolhaum();
                    cin >> escolha;
                    if (escolha == 0){
                        break;
                    }else {
                        Cadastro(insumos, escolha);
                    }
                }
                break;
            case 2:
                for(int i= 0; 1; i++){
                    Escolhadois();
                    cin >> escolha;
                    getchar();
                    if(escolha == 0){
                        break;
                    }
                    else if(escolha == 1){
                        exibir_estados();

                        cout << "Digite o nome do Estado: ";

                        getline(cin, sigla_do_estado);

                        subEscolhadois();

                        cin >> escolha; // Qual o tipo de insumo
                        getchar();

                        switch (escolha) {
                            case 1:
                                distribuir_vacina_para(sigla_do_estado);
                                break;
                            case 2:
                                distribuir_medicamento_para(sigla_do_estado);
                                break;
                            case 3:
                                distribuir_EPI_para(sigla_do_estado);
                                break;
                            default:
                                cout << "Essa escolha não existe. Sinto muito." << endl;
                        }
                    }

                }

                break;
            case 3:
                system("cls");
                while(1){
                    Escolhatres();
                    cin >> escolha;
                    if(escolha == 0){
                        break;
                    }
                    else if(escolha == 1){
                        system("cls");
                        Consulta(escolha);
                        system("pause");
                        system("cls");
                    }
                    else if(escolha == 2){
                        system("cls");
                        Consulta(escolha);
                        system("pause");
                        system("cls");
                    }else if(escolha == 3){
                        system("cls");
                        subEscolhatres();
                        Consulta(escolha);
                        system("pause");
                        system("cls");

                    }
                }
                //Consult_disp(vacinas, medicamentos, EPIs, escolha);
                break;
            /*
            case 4:
                system("cls");
                while(1){

                    Escolhaquatro();
                    cin >> escolha;
                    if(escolha == 0){
                        break;
                    }else if(escolha == 1){
                        Consult_est(Estados, escolha);
                    }else if(escolha == 2){
                        Consult_est(Estados, escolha);
                    }else if(escolha == 3){
                        subEscolhatres();
                        Consult_est(Estados, escolha);

                    }

                }
                break;
                */
            case 4:
                system("cls");
                while(1){
                Escolhacinco();
                cin >> escolha;
                getchar();

                if(escolha == 0){
                    break;
                }
                else if(escolha == 1){
                    std::string busca;


                    exibir_estados();
                    cout << "Digite a sigla do Estado: ";

                    getline(cin, busca);

                    if (busca == "federal")  {
                        cout << "Você não pode consultar o estoque federal por aqui." << endl;
                        cout << "Para isso vá nas opções 3 -> 2" << endl;
                        system("pause");
                        break;
                    }
                    if (filesystem::exists(".\\database\\vacina_"+busca+".csv")) {
                        cout << "\n\nVacinas:______________________________________________________________________________________________\n";
                        exibir_formatado(busca, 1);
                        cout << "\n\nmedicamentos:_________________________________________________________________________________________\n";
                        exibir_formatado(busca, 2);
                        cout << "\n\nEPI:__________________________________________________________________________________________________\n";
                        exibir_formatado(busca, 3);
                        system("pause");
                        system("cls");
                    }
                    else {
                        cout << "\nestoque não encontrar. Você pode ter digitado a sigla do estado de forma incorreta.\n"
                                "lembre-se de que tem que ser EXATAMENTE igual ao que foi lhe passado." << endl;
                        system("pause");
                        system("cls");
                    }
                }
            }
                break;

        }
    }


    return 0;
}


void exibir_estados() {
    cout << "| AC - Acre      | AL - Alagoas        | AP - Amapá               | AM - Amazonas          |\n";
    cout << "| BA - Bahia     | CE - Ceará          | ES - Espírito santo      | GO - Goiás             |\n";
    cout << "| MA - Maranhão  | MT - Mato Grosso    | MS - Mato Grosso do Sul  | MG - Minas Gerais      |\n";
    cout << "| PA - Pará      | PB - Paraíba        | PR - Paraná              | PE - Pernambuco        |\n";
    cout << "| PI - Piauí     | RJ - Rio de Janeiro | RN - Rio Grande do Norte | RS - Rio Grande do Sul |\n";
    cout << "| RO - Rondônia  | RR - Roraima        | SC - Santa Catarina      | SP - São Paulo         |\n";
    cout << "| SE - Sergipe   | TO - Tocantins      | DF - Distrito Federal    |                        |\n";
}



// Fun��es que s� o programa usa.
void _create_empty_csv(string file_name) {
    /**
     * O argumento recebe uma string que � o nome do arquivo que deve ser criado
     * O nome do arquivo deve ser passado sem .csv
     *
     * primeiro verifica se j� existe um arquivo com o mesmo nome. Se existir retorna um erro.
     * Se n�o existir criar um arquivo .csv com o nome passado e em branco.
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
     * Se n�o existir, exibi mensagem de erro.
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
     * o primeiro parametro, word, � a palavra-chave que deve ser pesquisada no arquivo.
     * o segundo parametro, file_name, � o nome do arquivo em que a palavra-chave (word) deve ser pesquisada.
     *
     *
     * .find() retornar a posi��o do primeiro caracter. Caso n�o encontre ele retorna
     * string::npos.
     *
     * Se a função não encontrar nenhuma ocorrencia da palavra passada ela retorna zero, caso contr�rio retorna
     * o número da linha que ocorre.
     **/
    string line;
    int count = 0, result;
    file_name.append(".csv");

    if (!filesystem::exists(file_name)) {
        return -1;
    }
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


// Fun��es em que o programador pode usar.
void show_file(string file_name) {
    /**
     * O unico argumento recebe uma vari�vel do tipo string que � o nome do arquivo a ser aberto.
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
     * o primeiro argumento recebe uma variavel do tipo string e que � a palavra-chave �nica
     * do item a ser pesquisado.
     *
     * O segundo argumento recebe uma vari�vel do tipo string que � o nome do arquivo a ser pesquisado.
     *
     * retorna 0 se a palavra-chave n�o for encontrada, e
     * retorna a linha se a palavra-cave for encontrada.
     */
    int count = 0, row;
    string line;

    row = _find_row(name, file_name);
    if (row == 0) {
        return "0";
    }
    else if (row == -1) {
        return "-1";
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

    return 0;
}


void adicionar_item_ao_estoque(string item, const string file_name) {
    /**
     * primeiro argumento � uma vari�vel do tipo string que recebe uma linha com todas as informa��es do item.
     * O segundo argumento � uma vari�vel do tipo string que armazena o nome do arquivo que vai ser salvo a linha.
     *
     * A fun��o salva a linha no final do arquivo.
     */
    string arquivo = file_name;
    arquivo.append(".csv");

    if (filesystem::exists(arquivo)) {
        cout << "Error";
    }
    ofstream file;
    file.open(arquivo, ios::app);
    file << item << '\n';
    file.close();
}


void _criar_estoque(string nome_do_arquivo, int tipo) {
    /**
     * O primeiro argumento � o nome do arquivo do estoque a ser criado.
     *
     * Dependente das fun��es _create_empty_csv e _add_header_to_file.
     *
     * tipo 1 = vacina
     * tipo 2 = medicamentos
     * tipo 3 = EPI
     */
    string arquivo = nome_do_arquivo, a_header;
    arquivo.append(".scv");

    if (tipo == 1) {
        a_header = CABECALHO_VACINA;
    }
    else if (tipo == 2) {
        a_header = CABECALHO_MEDICAMENTO;
    }
    else if (tipo == 3) {
        a_header = CABECALHO_EPI;
    }


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
     * O terceiro argumento recebe o nome do arquivo em que a atualiza��o ser� feita.
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
        cout << "DEBUG: nao foi possivel abrir o arquivo. | Erro na funcao: atualizar_item_do_estoque." << endl;
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


//  Só funciona para C++ +17
void _criar_diretorios() {
    bool diretorio_existe = filesystem::exists("databases");

    if (!diretorio_existe) {
        filesystem::create_directories("database");
    }
}


void criar_estoques() {
    _criar_estoque(".\\database\\vacina_federal", 1);
    _criar_estoque(".\\database\\medicamento_federal", 2);
    _criar_estoque(".\\database\\EPI_federal", 3);
    _criar_estoque(".\\database\\vacina_AC", 1);
    _criar_estoque(".\\database\\medicamento_AC", 2);
    _criar_estoque(".\\database\\EPI_AC", 3);
    _criar_estoque(".\\database\\vacina_AL", 1);
    _criar_estoque(".\\database\\medicamento_AL", 2);
    _criar_estoque(".\\database\\EPI_AL", 3);
    _criar_estoque(".\\database\\vacina_AP", 1);
    _criar_estoque(".\\database\\medicamento_AP", 2);
    _criar_estoque(".\\database\\EPI_AP", 3);
    _criar_estoque(".\\database\\vacina_AM", 1);
    _criar_estoque(".\\database\\medicamento_AM", 2);
    _criar_estoque(".\\database\\EPI_AM", 3);
    _criar_estoque(".\\database\\vacina_BA", 1);
    _criar_estoque(".\\database\\medicamento_BA", 2);
    _criar_estoque(".\\database\\EPI_BA", 3);
    _criar_estoque(".\\database\\vacina_CE", 1);
    _criar_estoque(".\\database\\medicamento_CE", 2);
    _criar_estoque(".\\database\\EPI_CE", 3);
    _criar_estoque(".\\database\\vacina_ES", 1);
    _criar_estoque(".\\database\\medicamento_ES", 2);
    _criar_estoque(".\\database\\EPI_ES", 3);
    _criar_estoque(".\\database\\vacina_GO", 1);
    _criar_estoque(".\\database\\medicamento_GO", 2);
    _criar_estoque(".\\database\\EPI_GO", 3);
    _criar_estoque(".\\database\\vacina_MA", 1);
    _criar_estoque(".\\database\\medicamento_MA", 2);
    _criar_estoque(".\\database\\EPI_MA", 3);
    _criar_estoque(".\\database\\vacina_MT", 1);
    _criar_estoque(".\\database\\medicamento_MT", 2);
    _criar_estoque(".\\database\\EPI_MT", 3);
    _criar_estoque(".\\database\\vacina_MS", 1);
    _criar_estoque(".\\database\\medicamento_MS", 2);
    _criar_estoque(".\\database\\EPI_MS", 3);
    _criar_estoque(".\\database\\vacina_MG", 1);
    _criar_estoque(".\\database\\medicamento_MG", 2);
    _criar_estoque(".\\database\\EPI_MG", 3);
    _criar_estoque(".\\database\\vacina_PA", 1);
    _criar_estoque(".\\database\\medicamento_PA", 2);
    _criar_estoque(".\\database\\EPI_PA", 3);
    _criar_estoque(".\\database\\vacina_PB", 1);
    _criar_estoque(".\\database\\medicamento_PB", 2);
    _criar_estoque(".\\database\\EPI_PB", 3);
    _criar_estoque(".\\database\\vacina_PR", 1);
    _criar_estoque(".\\database\\medicamento_PR", 2);
    _criar_estoque(".\\database\\EPI_PR", 3);
    _criar_estoque(".\\database\\vacina_PE", 1);
    _criar_estoque(".\\database\\medicamento_PE", 2);
    _criar_estoque(".\\database\\EPI_PE", 3);
    _criar_estoque(".\\database\\vacina_PI", 1);
    _criar_estoque(".\\database\\medicamento_PI", 2);
    _criar_estoque(".\\database\\EPI_PI", 3);
    _criar_estoque(".\\database\\vacina_RJ", 1);
    _criar_estoque(".\\database\\medicamento_RJ", 2);
    _criar_estoque(".\\database\\EPI_RJ", 3);
    _criar_estoque(".\\database\\vacina_RN", 1);
    _criar_estoque(".\\database\\medicamento_RN", 2);
    _criar_estoque(".\\database\\EPI_RN", 3);
    _criar_estoque(".\\database\\vacina_RS", 1);
    _criar_estoque(".\\database\\medicamento_RS", 2);
    _criar_estoque(".\\database\\EPI_RS", 3);
    _criar_estoque(".\\database\\vacina_RO", 1);
    _criar_estoque(".\\database\\medicamento_RO", 2);
    _criar_estoque(".\\database\\EPI_RO", 3);
    _criar_estoque(".\\database\\vacina_RR", 1);
    _criar_estoque(".\\database\\medicamento_RR", 2);
    _criar_estoque(".\\database\\EPI_RR", 3);
    _criar_estoque(".\\database\\vacina_SC", 1);
    _criar_estoque(".\\database\\medicamento_SC", 2);
    _criar_estoque(".\\database\\EPI_SC", 3);
    _criar_estoque(".\\database\\vacina_SP", 1);
    _criar_estoque(".\\database\\medicamento_SP" ,2);
    _criar_estoque(".\\database\\EPI_SP", 3);
    _criar_estoque(".\\database\\vacina_SE", 1);
    _criar_estoque(".\\database\\medicamento_SE", 2);
    _criar_estoque(".\\database\\EPI_SE", 3);
    _criar_estoque(".\\database\\vacina_TO", 1);
    _criar_estoque(".\\database\\medicamento_TO", 2);
    _criar_estoque(".\\database\\EPI_TO", 3);
    _criar_estoque(".\\database\\vacina_DF", 1);
    _criar_estoque(".\\database\\medicamento_DF", 2);
    _criar_estoque(".\\database\\EPI_DF", 3);
}


//funcao de inicio do programa para apresenta��o
void Boas_vindas(){

    printf("----------------------------------------------------------------------------------\n");
    printf("\t\t Boas vindas ao sistema de vacinacao\n");
    printf("-----------------------------------------------------------------------------------\n");
    printf("\n Aqui você poderá cadastrar e consultar as informações acerca das vacinas, medicamentos e EPI\n");
    printf("-----------------------------------------------------------------------------------\n");
    printf("\t Digite 1 para cadastrar os insumos.\n\n");
    printf("\t Digite 2 para distribuir os insumos disponíveis no estoque.\n\n");
    printf("\t Digite 3 para consultar os insumos disponíveis no estoque da União.\n\n");
    //printf("\t Digite 4 para saber quantas unidades foram destribuidas para os Estados.\n\n");
    printf("\t Digite 4 para consultar os insumos distribuidos por Estado.\n\n");// esse aqui eh mais especifico entao acho q cabe deixar ele
    printf("Digite 0 para sair\n");
    printf("-----------------------------------------------------------------------------------\n");
}


void Escolhaum(){

    printf("\n\n----------------------------------------------------------------------------------\n");
    printf("Como você escolheu o item 1, qual tipo de insumo você deseja cadastrar:\n\n");
    printf("----------------------------------------------------------------------------------\n");
    printf("Digite 1 caso queira cadastrar vacinas\n");
    printf("Digite 2 caso queira cadastrar medicamentos\n");
    printf("Digite 3 caso queira cadastrar EPIs\n");
    printf("Digite 0 para sair\n");
    printf("Digite aqui sua escolha:");

}


void Escolhadois(){

    printf("\n\n----------------------------------------------------------------------------------\n");
    printf("Como você escolheu o item 2, nos informe para qual você deseja destribuir:\n\n");
    printf("----------------------------------------------------------------------------------\n");
    printf("Digite 1 para cadastrar a distribuição para os Estados:\n");
    printf("Caso nao queira distribuir mais para nenhum Estado, digite 0:\n");


}


void subEscolhadois(){

    printf("\n\n----------------------------------------------------------------------------------\n");
    printf("Como você escolheu o item 1, qual tipo de insumo você deseja destribuir para o Estado:\n\n");
    printf("----------------------------------------------------------------------------------\n");
    printf("Digite 1 caso queira distribuir vacinas\n");
    printf("Digite 2 caso queira distribuir medicamentos\n");
    printf("Digite 3 caso queira distribuir EPIs\n");
    printf("Digite 0 para sair\n");
    printf("Digite aqui sua escolha:");

}


//funcao caso o usuario escolha o item 3 da funcao acima
void Escolhatres(){

    printf("\n\n----------------------------------------------------------------------------------\n");
    printf("Como você escolheu o item 3, nos diga como você quer receber a informacão:\n\n");
    printf("----------------------------------------------------------------------------------\n");
    printf("Digite 1 caso queira receber a quantidade de itens disponíveis em estoque no geral\n");
    printf("Digite 2 caso queira receber a descricao detalhada dos itens disponíveis em estoque\n");
    printf("Digite 3 caso queira receber tanto a descricao e quantidade do tipo de insumo disponível\n");
    printf("Digite 0 para sair\n");
    printf("Digita aqui sua escolha:");

}


//funcao caso o usuario escolher a opcao 3, escolha novamente a opcao 3, coloca dentro da funcao de insumos disponiveis se a funcao for necessaria
void subEscolhatres(){

    printf("\n\n----------------------------------------------------------------------------------\n");
    printf("Como voce escolheu o item 3.3, nos diga como voce quer receber a informação:\n\n");
    printf("\n\n----------------------------------------------------------------------------------\n");
    printf("Digite 1 caso queira receber a descrição e quantidade das vacinas\n ");
    printf("Digite 2 caso queira receber a descrição e quantidade dos medicamentos\n ");
    printf("Digite 3 caso queira receber a descrição e quantidade das EPIs\n ");
    printf("----------------------------------------------------------------------------------\n");
    printf("Digite 0 para sair\n");
    printf("Digita aqui sua escolha:");
}


//funcao caso o usario escolha o item 4
void Escolhaquatro(){

    printf("\n\n----------------------------------------------------------------------------------\n");
    printf("Como você escolheu o item 4, nos diga como você quer receber a informação:\n\n");
    printf("----------------------------------------------------------------------------------\n");
    printf("Digite 1 caso queira receber a quantidade de itens distribuidos para os Estados no geral\n");
    printf("Digite 2 caso queira receber a descricao dos itens distribuidos para os Estados\n");
    printf("Digite 3 caso queira receber tanto a descricao e quantidade do tipo de insumo distribuido\n");
    printf("Digite 0 para sair\n");
    printf("Digita aqui sua escolha:");


}


//funcao caso o usuario escolher a opcao 4, escolha a opcao 3, coloca dentro da funcao de insumos distribuidos se a funcao for necessaria
void subEscolhaquatro(){

    printf("\n\n----------------------------------------------------------------------------------\n");
    printf("Como você escolheu o item 3, nos diga como você quer receber a informação:\n\n");
    printf("\n\n----------------------------------------------------------------------------------\n");
    printf("Digite 1 caso queira receber a descricao e quantidade das vacinas\n ");
    printf("Digite 2 caso queira receber a descricao e quantidade dos medicamentos\n ");
    printf("Digite 3 caso queira receber a descricao e quantidade das EPIs\n ");
    printf("----------------------------------------------------------------------------------\n");
    printf("Digite 0 para sair\n");
    printf("Digita aqui sua escolha:");

}


void Escolhacinco()
{
    printf("\n\n----------------------------------------------------------------------------------\n");
    printf("Como voce escolheu o item 4, informe qual Unidade Federativa voce deseja obter as informações\n");
    printf("\n----------------------------------------------------------------------------------\n");
    printf("Digite 1 e logo em seguida informe a unidade federativa: \n");
    printf("Digite 0 para sair\n");
    printf("----------------------------------------------------------------------------------\n");
    printf("Digita aqui sua escolha:");

}
/*void ShowStorage(t_insumos *ins){

    printf("\n\n----------------------------------------------------------------------------------\n");
    cout << "Disponivel no estoque do MS:" << endl;
    for(int i = 0; i< 100; i++){
        if(ins[i].nome != ""){
            if(ins[i].cdg == 1){
                printf("----------------------------------------------------------------------------------\n");
                    cout << "Nome: " << ins[i].nome << ", " << "Valor: " << ins[i].valor << ", " << "Quantidade de vacinas: " << ins[i].qnt_itens << ", " <<
                            "Data de vencimento: "<< ins[i].d_vencimento<< ", " <<"Nome do fabricante: "<< ins[i].nome_fab << endl;

                    cout << "Tipo da vacina: "<<ins[i].vac.tp_vac << ", " << "Quantidade de doses: " << ins[i].vac.qnt_doses << ", " << "Intervalo de dias: "<<
                            ins[i].vac.intervalo << endl;
            }else if(ins[i].cdg == 2){
                printf("----------------------------------------------------------------------------------\n");
                    cout << "Nome: " << ins[i].nome << ", " << "Valor: " << ins[i].valor << ", " << "Quantidade de medicamentos: " << ins[i].qnt_itens << ", " <<
                            "Data de vencimento: "<< ins[i].d_vencimento<< ", " <<"Nome do fabricante: "<< ins[i].nome_fab << endl;

                    cout << "Dosagem: "<<ins[i].med.dosagem << ", " << "Forma de administracao: " << ins[i].med.adm << ", " << "Forma de disponibilizacao: "<<
                            ins[i].med.disp << endl;
            }else if(ins[i].cdg == 3){
                printf("----------------------------------------------------------------------------------\n");
                    cout << "Nome: " << ins[i].nome << ", " << "Valor: " << ins[i].valor << ", " << "Quantidade de vacinas: " << ins[i].qnt_itens << ", " <<
                            "Data de vencimento: "<< ins[i].d_vencimento<< ", " <<"Nome do fabricante: "<< ins[i].nome_fab << endl;

                    cout << "Informacao adicionais: " << ins[i].epi.info_dtl << endl;
                    printf("----------------------------------------------------------------------------------\n");
            }

        }else{
            break;
        }
    }
}
*/


int parte;
void Cadastro(t_insumos *i, int escolha){ 


    if (escolha == 1){
        cout << "Digite o nome da vacina:\n";
        cin >> i[parte].nome;
        cout << "digite o valor unit�rio:\n";
        cin >> i[parte].valor;
        cout << "Digite a quantidade da vacina:\n";
        cin >> i[parte].qnt_itens;
        cout << "Digite a data de vencimento:\n";
        cin >> i[parte].d_vencimento; // Transformar em string//
        getchar();
        cout << "Digite o nome do fabricante:\n";
        getline(cin, i[parte].nome_fab);
        cout << "Digite o tipo da vacina:\n";
        cin >> i[parte].vac.tp_vac;
        cout << "Digite a quantidade de doses:\n";
        cin >> i[parte].vac.qnt_doses;
        cout << "Digite o intervalo das doses em dias:\n";
        cin >> i[parte].vac.intervalo;
        cout << "Digito o código do produto (único):" << endl;
        cin >> i[parte].codigo_unico;
        i[parte].cdg = 1;

        cadastrar_vacina(i[parte], "federal");

    }else if (escolha == 2){
        cout << "Digite o nome do medicamento\n";
        cin >> i[parte].nome;
        cout << "digite o valor unit�rio\n";
        cin >> i[parte].valor;
        cout << "Digite a quantidade de medicamentos:\n";
        cin >> i[parte].qnt_itens;
        cout << "Digite a data de vencimento:\n";
        cin >> i[parte].d_vencimento; // Transformar em string//
        getchar();
        cout << "Digite o nome do fabricante:\n";
        getline(cin, i[parte].nome_fab);
        cout << "Digite a dosagem:\n";
        getline(cin, i[parte].med.dosagem);
        cout << "Digite a administracao:\n";
        getline(cin, i[parte].med.adm);
        cout << "Digite a disposicao do medicamento (Se eh soluvel ou liquido, etc...):\n";
        getline(cin, i[parte].med.disp);
        cout << "Digito o código do produto (único):" << endl;
        cin >> i[parte].codigo_unico;
        i[parte].cdg = 2;

        cadastrar_medicamentos(i[parte],  "federal");

    }else if(escolha == 3){

        cout << "Digite o nome do EPI\n";
        cin >> i[parte].nome;
        cout << "digite o valor unit�rio:\n";
        cin >> i[parte].valor;
        cout << "Digite a quantidade dos EPIs:\n";
        cin >> i[parte].qnt_itens;
        cout << "Digite a data de vencimento:\n";
        cin >> i[parte].d_vencimento; // Transformar em string//
        getchar();
        cout << "Digite o nome do fabricante:\n";
        getline(cin, i[parte].nome_fab);
        cout << "Digite a informcao detalhada do EPI:\n";
        getline(cin, i[parte].epi.info_dtl);
        cout << "Digito o código do produto (único):" << endl;
        cin >> i[parte].codigo_unico;
        i[parte].cdg = 3;

        cadastrar_epis(i[parte],  "federal");

    }
    parte++;

}


int part_est;
void Cadastro_Est(t_est *est, int escolha, std::string estado){

    if (escolha == 1){
        cout << "Digite o nome da vacina:\n";
        cin >> est[part_est].nome_do_insumo;
        cout << "digite o valor unit�rio:\n";
        cin >> est[part_est].val;
        cout << "Digite a quantidade de vacina que deseja distribuir:\n";
        cin >> est[part_est].qnt_recebida;
        cout << "Digite a data de vencimento:\n";
        cin >> est[part_est].data_vencimento; // Transformar em string//
        getchar();
        cout << "Digite o nome do fabricante:\n";
        getline(cin, est[part_est].nome_fabricante);
        cout << "Digite o tipo da vacina:\n";
        cin >> est[part_est].vc.tp_vac;
        cout << "Digite a quantidade de doses:\n";
        cin >> est[part_est].vc.qnt_doses;
        cout << "Digite o intervalo das doses em dias:\n";
        cin >> est[part_est].vc.intervalo;
        est[part_est].cd = 1;

        //cadastrar_vacina(est[part_est], estado);

    }if (escolha == 2){
        cout << "Digite o nome do medicamento\n";
        cin >> est[parte].nome_do_insumo;
        cout << "digite o valor unit�rio\n";
        cin >> est[parte].val;
        cout << "Digite a quantidade de medicamentos que deseja distribuir:\n";
        cin >> est[part_est].qnt_recebida;
        cout << "Digite a data de vencimento:\n";
        cin >> est[part_est].data_vencimento; // Transformar em string//
        getchar();
        cout << "Digite o nome do fabricante:\n";
        getline(cin, est[part_est].nome_fabricante);
        cout << "Digite a dosagem:\n";
        getline(cin, est[part_est].md.dosagem);
        cout << "Digite a administracao:\n";
        getline(cin, est[part_est].md.adm);
        cout << "Digite a disposicao do medicamento (Se eh soluvel ou liquido, etc...):\n";
        getline(cin, est[part_est].md.disp);
        est[part_est].cd = 2;

        //cadastrar_medicamentos(est[part_est], estado);
    }else if(escolha == 3){

        cout << "Digite o nome do EPI\n";
        cin >> est[part_est].nome_do_insumo;
        cout << "digite o valor unit�rio:\n";
        cin >> est[part_est].val;
        cout << "Digite a quantidade dos EPIs que deseja distribuir:\n";
        cin >> est[part_est].qnt_recebida;
        cout << "Digite a data de vencimento:\n";
        cin >> est[part_est].data_vencimento; // Transformar em string//
        getchar();
        cout << "Digite o nome do fabricante:\n";
        getline(cin, est[part_est].nome_fabricante);
        cout << "Digite a informcao detalhada do EPI:\n";
        getline(cin, est[part_est].ep.info_dtl);
        est[part_est].cd = 3;

        //cadastrar_epis(est[part_est], estado);
    }

    part_est++;
}

void Consulta(int escolha) {
    /**
     * Alternativa para a função Consult(t_insumo *ins, int escolha)
     */
    if (escolha == 1) {
        cout << "Quantidade de insumos (Vacinas, Medicamentos e EPIs)." << endl;
        cout << "___________________________________________________________________________________________________________\n";
        cout << "Quantidade de vacinas (em unidades):" << get_quantidade_de_vacinas("federal") << endl;
        cout << "\nQuantidade de medicamentos (em unidades):" << get_quantidade_de_medicamentos("federal") << endl;
        cout << "\nQuantidade de EPIs (em unidades):" << get_quantidade_de_EPIs("federal") << endl;

        cout << "\nQuantidade total (em unidades): " << consultar_quantidade_dos_insumos("federal") << endl;
    }
    if (escolha == 2) {
        string escolha_2;
        cout << "\n\nVacinas:______________________________________________________________________________________________\n";
        exibir_formatado("federal", 1);
        cout << "\n\nmedicamentos:_________________________________________________________________________________________\n";
        exibir_formatado("federal", 2);
        cout << "\n\nEPI:__________________________________________________________________________________________________\n";
        exibir_formatado("federal", 3);
        cout << "Digite o codigo unico do insumo: ";
        cin >> escolha_2;
        system("cls");
        mostrar_insumo_detalhado(escolha_2);
    }
    if (escolha == 3) {
        int escolha_3;
        cin >> escolha_3;


        system("cls");
        switch (escolha_3) {
            case 1:
                cout << "\nQuantidade de vacinas: " << get_quantidade_de_vacinas("federal") <<
                "\n_____________________________________________________________________________________________________\n" << endl;
                Consultar_estoque_local("federal", 1);
                break;
            case 2:
                cout << "\nQuantidade de medicamentos: " << get_quantidade_de_medicamentos("federal") <<
                "\n_____________________________________________________________________________________________________\n" << endl;
                Consultar_estoque_local("federal", 2);
                break;
            case 3:
                cout << "\nQuantiade de EPIs: " << get_quantidade_de_EPIs("federal") <<
               "\n______________________________________________________________________________________________________\n" << endl;
                Consultar_estoque_local("federal", 3);
                break;
            default:
                cout << "Entrada incorreta." << endl;
        }
    }
}


void Consult(t_insumos *ins, int escolha){

    int soma_insumo = 0;
    if(escolha == 1){
        for(int i = 0; i < parte; i++){
            soma_insumo += ins[i].qnt_itens;
        }
        cout << "Total de insumos (Vacinas, Medicamentos e EPis)\n";
        cout << "Quantidade: " << soma_insumo;
    }else if(escolha == 2){
        for(int i = 0; i < parte; i++){
            if(ins[i].qnt_itens != 0){
                cout << ins[i].nome << ", " << ins[i].valor << ", " << ins[i].qnt_itens << ", " << ins[i].d_vencimento<< ", " << ins[i].nome_fab <<endl;
            }else{
                cout << ins[i].nome << "Nao estah disponivel, pois nao ha itens\n";
            }
        }
    }else if(escolha == 3){
        int n;
        cin >> n;
        if(n == 1){
            for(int i = 0; i < parte; i++){
                if(ins[i].cdg == 1){
                    /*printf("\n\n----------------------------------------------------------------------------------\n");
                    cout << "Nome: " << ins[i].nome << ", " << "Valor: " << ins[i].valor << ", " << "Quantidade de vacinas: " << ins[i].qnt_itens << ", " <<
                            "Data de vencimento: "<< ins[i].d_vencimento<< ", " <<"Nome do fabricante: "<< ins[i].nome_fab << endl;

                    cout << "Tipo da vacina: "<<ins[i].vac.tp_vac << ", " << "Quantidade de doses: " << ins[i].vac.qnt_doses << ", " << "Intervalo de dias: "<<
                            ins[i].vac.intervalo << endl;
                    printf("\n----------------------------------------------------------------------------------\n");*/
                    Consultar_estoque_local("federal", n);
                }
            }
        }else if(n == 2){
            for(int i = 0; i < parte; i++){
                if(ins[i].cdg == 2){
                    /*printf("\n\n----------------------------------------------------------------------------------\n");
                    cout << "Nome: " << ins[i].nome << ", " << "Valor: " << ins[i].valor << ", " << "Quantidade de medicamentos: " << ins[i].qnt_itens << ", " <<
                            "Data de vencimento: "<< ins[i].d_vencimento<< ", " <<"Nome do fabricante: "<< ins[i].nome_fab << endl;

                    cout << "Dosagem: "<<ins[i].med.dosagem << ", " << "Forma de administracao: " << ins[i].med.adm << ", " << "Forma de disponibilizacao: "<<
                            ins[i].med.disp << endl;
                    printf("\n----------------------------------------------------------------------------------\n");*/
                    Consultar_estoque_local("federal", n);
                }
            }
        }else if(n == 3){
            for(int i = 0; i < parte; i++){
                if(ins[i].cdg == 3){
                    /*printf("\n\n----------------------------------------------------------------------------------\n");
                    cout << "Nome: " << ins[i].nome << ", " << "Valor: " << ins[i].valor << ", " << "Quantidade de vacinas: " << ins[i].qnt_itens << ", " <<
                            "Data de vencimento: "<< ins[i].d_vencimento<< ", " <<"Nome do fabricante: "<< ins[i].nome_fab << endl;

                    cout << "Informacao adicionais: " << ins[i].epi.info_dtl << endl;
                    printf("\n----------------------------------------------------------------------------------\n");*/
                    Consultar_estoque_local("federal", n);
                }
            }
        }
    }


}


void Consult_est(t_est *est, int escolha){

    int soma_insumo = 0;
    if(escolha == 1){
        for(int i = 0; i < part_est; i++){
            soma_insumo += est[i].qnt_recebida;
        }
        cout << "Total de insumos distribuidos para os Estados: \n";
        cout << "A quantidade de insumos distribuidos: " << soma_insumo;

    }else if(escolha == 2){
        for(int i = 0; i < part_est; i++){
            if(est[i].qnt_recebida != 0){
                cout << "Nome do Estado: ";
                cout << est->nome_do_estado;
                cout << est[i].nome_do_insumo << ", " << est[i].val << ", " << est[i].qnt_recebida << ", " << est[i].data_vencimento<< ", " << est[i].nome_fabricante <<endl;
            }else{
                cout << "Nome do Estado: ";
                cout << est->nome_do_estado;
                cout << est[i].nome_do_insumo << "Nao estah disponivel, pois nao foi distribuido\n";
            }
        }
    }else if(escolha == 3){
        int n;
        cin >> n;
        if(n == 1){
            for(int i = 0; i < part_est; i++){
                if(est[i].cd == 1){
                    cout << "Nome do Estado: ";
                    cout << est->nome_do_estado;
                    printf("\n\n----------------------------------------------------------------------------------\n");
                    cout << "Nome: " << est[i].nome_do_insumo << ", " << "Valor: " << est[i].val << ", " << "Quantidade de vacinas: " << est[i].qnt_recebida << ", " <<
                            "Data de vencimento: "<< est[i].data_vencimento<< ", " <<"Nome do fabricante: "<< est[i].nome_fabricante << endl;

                    cout << "Tipo da vacina: " << est[i].vc.tp_vac << ", " << "Quantidade de doses: " << est[i].vc.qnt_doses << ", " << "Intervalo de dias: "<<
                            est[i].vc.intervalo << endl;
                    printf("\n----------------------------------------------------------------------------------\n");
                }
            }
        }else if(n == 2){
            for(int i = 0; i < part_est; i++){
                if(est[i].cd == 2){
                    cout << "Nome do Estado: ";
                    cout << est->nome_do_estado;
                    printf("\n\n----------------------------------------------------------------------------------\n");
                    cout << "Nome: " << est[i].nome_do_insumo << ", " << "Valor: " << est[i].val << ", " << "Quantidade de medicamentos: " << est[i].qnt_recebida << ", " <<
                            "Data de vencimento: "<< est[i].data_vencimento << ", " <<"Nome do fabricante: "<< est[i].nome_fabricante << endl;

                    cout << "Dosagem: "<<est[i].md.dosagem << ", " << "Forma de administracao: " << est[i].md.adm << ", " << "Forma de disponibilizacao: "<<
                            est[i].md.disp << endl;
                    printf("\n----------------------------------------------------------------------------------\n");
                }
            }
        }else if(n == 3){
            for(int i = 0; i < part_est; i++){
                if(est[i].cd == 3){
                    printf("\n\n----------------------------------------------------------------------------------\n");
                    cout << "Nome: " << est[i].nome_do_insumo << ", " << "Valor: " << est[i].val << ", " << "Quantidade de vacinas: " << est[i].qnt_recebida << ", " <<
                            "Data de vencimento: "<< est[i].data_vencimento<< ", " <<"Nome do fabricante: "<< est[i].nome_fabricante << endl;

                    cout << "Informacao adicionais: " << est[i].ep.info_dtl << endl;
                    printf("\n----------------------------------------------------------------------------------\n");
                }
            }
        }
    }


}


void consult_est_especifico(t_est *est, std::string busca){

    for(int i = 0; i < 27; i++){
        if(est[i].nome_do_estado == busca){
            if(est[i].cd == 1){
                    cout << "Nome do Estado: ";
                    cout << est->nome_do_estado;
                    printf("\n\n----------------------------------------------------------------------------------\n");
                    cout << "Nome: " << est[i].nome_do_insumo << ", " << "Valor: " << est[i].val << ", " << "Quantidade de vacinas: " << est[i].qnt_recebida << ", " <<
                            "Data de vencimento: "<< est[i].data_vencimento<< ", " <<"Nome do fabricante: "<< est[i].nome_fabricante << endl;

                    cout << "Tipo da vacina: " << est[i].vc.tp_vac << ", " << "Quantidade de doses: " << est[i].vc.qnt_doses << ", " << "Intervalo de dias: "<<
                            est[i].vc.intervalo << endl;
                    printf("\n----------------------------------------------------------------------------------\n");
            }else if(est[i].cd == 2){
                    cout << "Nome do Estado: ";
                    cout << est->nome_do_estado;
                    printf("\n\n----------------------------------------------------------------------------------\n");
                    cout << "Nome: " << est[i].nome_do_insumo << ", " << "Valor: " << est[i].val << ", " << "Quantidade de medicamentos: " << est[i].qnt_recebida << ", " <<
                            "Data de vencimento: "<< est[i].data_vencimento << ", " <<"Nome do fabricante: "<< est[i].nome_fabricante << endl;

                    cout << "Dosagem: "<<est[i].md.dosagem << ", " << "Forma de administracao: " << est[i].md.adm << ", " << "Forma de disponibilizacao: "<<
                            est[i].md.disp << endl;
                    printf("\n----------------------------------------------------------------------------------\n");
            }else if(est[i].cd == 3){
                    printf("\n\n----------------------------------------------------------------------------------\n");
                    cout << "Nome: " << est[i].nome_do_insumo << ", " << "Valor: " << est[i].val << ", " << "Quantidade de vacinas: " << est[i].qnt_recebida << ", " <<
                            "Data de vencimento: "<< est[i].data_vencimento<< ", " <<"Nome do fabricante: "<< est[i].nome_fabricante << endl;

                    cout << "Informacao adicionais: " << est[i].ep.info_dtl << endl;
                    printf("\n----------------------------------------------------------------------------------\n");
            }
        }
    }

}


void Consultar_estoque_local(const string local, int escolha) {
    string arquivo = ".\\database\\";
    if(escolha == 1){
        arquivo.append("vacina");
    }else if(escolha == 2){
        arquivo.append("medicamento");
    }else if(escolha == 3){
        arquivo.append("EPI");
    }

    arquivo.append("_");
    arquivo.append(local);

    show_file(arquivo);
}


void cadastrar_vacina(const t_insumos vacina, const string local) {
    /*
    * Recebe uma struct e um uma string como local.
    * 
    * salva a struct no arquivo.
    */
    string arquivo = ".\\database\\vacina_";
    arquivo.append(local);

    string item = t_insumo_para_string(vacina, 1);

    adicionar_item_ao_estoque(item, arquivo);
}


void cadastrar_medicamentos(const t_insumos medicamentos, const string local) {
    string arquivo = ".\\database\\medicamento_";
    arquivo.append(local);

    string item = t_insumo_para_string(medicamentos, 2);

    adicionar_item_ao_estoque(item, arquivo);
}


void cadastrar_epis(const t_insumos epis, const string local) {
    string arquivo = ".\\database\\EPI_";
    arquivo.append(local);

    string item = t_insumo_para_string(epis, 3);

    adicionar_item_ao_estoque(item, arquivo);
}


/**
 * As fun��es a seguir transformar cada tipo de struct para string e vice-versa
 * Embora eu n�o entenda o que eu to fazendo
 */

string t_insumo_para_string(const t_insumos insumo, const int tipo) {
    /**
     * 1 = vacina
     * 2 = medicamento
     * 3 = EPI
     *
     * O primeiro argumento recebe o struct insumo
     * O segundo argumento recebe tipo do struct
     *
     * retorna uma string que corresponde a esse struct
     */
    string frase_de_retorno;


    frase_de_retorno.append(insumo.codigo_unico + ", ");
    frase_de_retorno.append(insumo.nome + ", ");
    frase_de_retorno.append(to_string(insumo.valor) + ", ");
    frase_de_retorno.append(to_string(insumo.qnt_itens) + ", ");
    frase_de_retorno.append(insumo.d_vencimento + ", ");
    frase_de_retorno.append(insumo.nome_fab + ", ");

    switch (tipo) {
        case 1:
            frase_de_retorno.append(insumo.vac.tp_vac + ", ");
            frase_de_retorno.append(to_string(insumo.vac.qnt_doses) + ", ");
            frase_de_retorno.append(to_string(insumo.vac.intervalo));

            break;

        case 2:
            frase_de_retorno.append(insumo.med.dosagem + ", ");
            frase_de_retorno.append(insumo.med.adm + ", ");
            frase_de_retorno.append(insumo.med.disp);

            break;

        case 3:
            frase_de_retorno.append(insumo.epi.info_dtl);
            break;
    }

    return frase_de_retorno;
}


t_insumos string_para_t_insumo(const string item, const int tipo_do_insumo) {
    /**
     * Recebe, como primeiro argumento, um string que � a linha inteira de um item
     * Recebe, como segundo argumento, um int que � o tipo de insumo, sendo:
     * 1 para vacina;
     * 2 para medicamento;
     * 3 para EPI;
     *
     * retorna uma varia do tipo struct t_insumo.
     */
    t_insumos insumo_de_retorno;
    string insumo = item;
    int index;

    index = insumo.find(", ");
    insumo_de_retorno.codigo_unico = insumo.substr(0, index);
    insumo = insumo.substr(index+2, insumo.size());

    index = insumo.find(", ");
    insumo_de_retorno.nome = insumo.substr(0, index);
    insumo = insumo.substr(index+2, insumo.size());

    index = insumo.find(", ");
    insumo_de_retorno.valor = stoi(insumo.substr(0, index));
    insumo = insumo.substr(index+2, insumo.size());

    index = insumo.find(", ");
    insumo_de_retorno.qnt_itens = stoi(insumo.substr(0, index));
    insumo = insumo.substr(index+2, insumo.size());

    index = insumo.find(", ");
    insumo_de_retorno.d_vencimento = insumo.substr(0, index);
    insumo = insumo.substr(index+2, insumo.size());

    index = insumo.find(", ");
    insumo_de_retorno.nome_fab = insumo.substr(0, index);
    insumo = insumo.substr(index+2, insumo.size());


    switch (tipo_do_insumo) {
        case 1: //vacina
            index = insumo.find(", ");
            insumo_de_retorno.vac.tp_vac = insumo.substr(0, index);
            insumo = insumo.substr(index+2, insumo.size());

            index = insumo.find(", ");
            insumo_de_retorno.vac.qnt_doses = stoi(insumo.substr(0, index));
            insumo = insumo.substr(index+2, insumo.size());

            index = insumo.find(", ");
            insumo_de_retorno.vac.intervalo = stoi(insumo.substr(0, index-1));

            insumo_de_retorno.cdg = 1;
            break;


        case 2: //medicamento
            index = insumo.find(", ");
            insumo_de_retorno.med.dosagem = insumo.substr(0, index);
            insumo = insumo.substr(index+2, insumo.size());

            index = insumo.find(", ");
            insumo_de_retorno.med.adm = insumo.substr(0, index);
            insumo = insumo.substr(index+2, insumo.size());

            insumo_de_retorno.med.disp = insumo.substr(0, insumo.size());

            insumo_de_retorno.cdg = 2;
            break;


        case 3: // EPI
            insumo_de_retorno.epi.info_dtl = insumo.substr(0, insumo.size());
            insumo_de_retorno.cdg = 3;
            break;

    }
    return insumo_de_retorno;
}


int consultar_quantidade_dos_insumos(const string local) {
    int quantidade = 0;

    quantidade += get_quantidade_de_vacinas(local);
    quantidade += get_quantidade_de_medicamentos(local);
    quantidade += get_quantidade_de_EPIs(local);


    return quantidade;
}


int get_quantidade_de_vacinas(const string local) {
    string diretorio = ".\\database\\vacina_", line;
    string cabecalho = CABECALHO_VACINA;
    t_insumos insumo;

    cabecalho = cabecalho.substr(0, cabecalho.size()-1);

    int quantidade = 0;

    diretorio.append(local);
    diretorio.append(".csv");

    fstream vacina_file (diretorio);

    while (!vacina_file.eof()) {
        getline(vacina_file, line);

        size_t resultado = line == cabecalho;
        if (resultado) {
            continue;
        }
        else if (line.empty()) {
            break;
        }
        else{
            insumo = string_para_t_insumo(line, 1);
            quantidade += insumo.qnt_itens;
        }
    }

    vacina_file.close();

    return quantidade;
}


int get_quantidade_de_medicamentos(const string local) {
    string diretorio = ".\\database\\medicamento_", line;
    string cabecalho = CABECALHO_MEDICAMENTO;
    t_insumos insumo;

    cabecalho = cabecalho.substr(0, cabecalho.size()-1);

    int quantidade = 0;

    diretorio.append(local);
    diretorio.append(".csv");

    fstream file (diretorio);

    while (!file.eof()) {
        getline(file, line);

        size_t resultado = line == cabecalho;
        if (resultado) {
            continue;
        }
        else if (line.empty()) {
            break;
        }
        else{
            insumo = string_para_t_insumo(line, 2);
            quantidade += insumo.qnt_itens;
        }
    }

    file.close();

    return quantidade;
}

int get_quantidade_de_EPIs(const string local) {
    string diretorio = ".\\database\\EPI_", line;
    string cabecalho = CABECALHO_EPI;
    t_insumos insumo;

    cabecalho = cabecalho.substr(0, cabecalho.size()-1);

    int quantidade = 0;

    diretorio.append(local);
    diretorio.append(".csv");

    fstream file (diretorio);

    while (!file.eof()) {
        getline(file, line);

        size_t resultado = line == cabecalho;
        if (resultado) {
            continue;
        }
        else if (line.empty()) {
            break;
        }
        else{
            insumo = string_para_t_insumo(line, 3);
            quantidade += insumo.qnt_itens;
        }
    }

    file.close();

    return quantidade;
}

void mostrar_insumo_detalhado(const string codigo_unico) {
    string vacina_diretorio = DIRETORIO_DATABASE_VACINA_GERAL;
    string medicamentos_diretorio = DIRETORIO_DATABASE_MEDICAMENTO_GERAL;
    string EPI_diretorio = DIRETORIO_DATABASE_EPI_GERAL;
    t_insumos insumo;

    string vacina_item = read_a_line_of_the_file(codigo_unico, vacina_diretorio);
    string medicamento_item = read_a_line_of_the_file(codigo_unico, medicamentos_diretorio);
    string EPI_item = read_a_line_of_the_file(codigo_unico, EPI_diretorio);

    if (!(vacina_item == "0")) {
        insumo = string_para_t_insumo(vacina_item, 1);
        exibir_vacina(insumo);
    }
    if (!(medicamento_item == "0")) {
        insumo = string_para_t_insumo(medicamento_item, 2);
        exibir_medicamento(insumo);
    }
    if (!(EPI_item == "0")) {
        insumo = string_para_t_insumo(EPI_item, 3);
        exibir_EPI(insumo);
    }
}


void exibir_vacina(const t_insumos insumo) {
    cout << "\t\tInformações da vacina escolhida:" << endl;
    cout << "codigo do insumo: " << insumo.codigo_unico << endl;
    cout << "nome da vacina: " << insumo.nome << endl;
    cout << "Preço: R$ " << insumo.valor << endl;
    cout << "data de vencimento: " << insumo.d_vencimento << endl;
    cout << "fabricante: " << insumo.nome_fab << endl;
    cout << "quantidade de doses: " << insumo.vac.qnt_doses << endl;
    cout << "tempo entre doses: " << insumo.vac.intervalo << endl;
    cout << "tipo de tecnologia: " << insumo.vac.tp_vac << endl;
}


void exibir_medicamento(const t_insumos insumo) {
    cout << "\t\tInformações do medicamento escolhida:" << endl;
    cout << "codigo do insumo: " << insumo.codigo_unico << endl;
    cout << "nome da vacina: " << insumo.nome << endl;
    cout << "Preço: R$ " << insumo.valor << endl;
    cout << "data de vencimento: " << insumo.d_vencimento << endl;
    cout << "fabricante: " << insumo.nome_fab << endl;
    cout << "dosagem: " << insumo.med.dosagem << endl;
    cout << "administracao: " << insumo.med.adm << endl;
    cout << "disposicao: " << insumo.med.disp << endl;
}



void exibir_EPI(const t_insumos insumo) {
    cout << "\t\tInformações da EPI escolhida:" << endl;
    cout << "codigo do insumo: " << insumo.codigo_unico << endl;
    cout << "nome da vacina: " << insumo.nome << endl;
    cout << "Preço: R$ " << insumo.valor << endl;
    cout << "data de vencimento: " << insumo.d_vencimento << endl;
    cout << "fabricante: " << insumo.nome_fab << endl;
    cout << "Informacoes detalhadas: \n\t" << insumo.epi.info_dtl << endl;
}


void diminuir_quantidade(const int quantidade, const string codigo_unico, const string local, const int tipo_do_insumo) {
    int linha;
    string arquivo = ".\\database\\", line;
    t_insumos insumo;

    switch (tipo_do_insumo) {
        case 1:
            arquivo.append("vacina_");
            arquivo.append(local);
            break;
        case 2:
            arquivo.append("medicamento_");
            arquivo.append(local);
            break;
        case 3:
            arquivo.append("EPI_");
            arquivo.append(local);
            break;
        default:
            cout << "Tipo expecificado invalido. | DEBUG: ERRO na função diminuir_quantidade." << endl;
    }

    linha = _find_row(codigo_unico, arquivo);

    insumo = string_para_t_insumo(read_a_line_of_the_file(codigo_unico, arquivo), tipo_do_insumo);

    insumo.qnt_itens -= quantidade;

    line = t_insumo_para_string(insumo, tipo_do_insumo);

    atualizar_item_do_estoque(line, codigo_unico, arquivo);
}


void aumentar_quantidade(const int quantidade, const string codigo_unico, const string local, const int tipo_do_insumo) {
    int linha;
    string arquivo = ".\\database\\", line;
    t_insumos insumo;


    switch (tipo_do_insumo) {
        case 1:
            arquivo.append("vacina_");
            arquivo.append(local);
            break;
        case 2:
            arquivo.append("medicamento_");
            arquivo.append(local);
            break;
        case 3:
            arquivo.append("EPI_");
            arquivo.append(local);
            break;
        default:
            cout << "Tipo expecificado invalido. | DEBUG: ERRO na função diminuir_quantidade." << endl;
    }

    linha = _find_row(codigo_unico, arquivo);

    insumo = string_para_t_insumo(read_a_line_of_the_file(codigo_unico, arquivo), tipo_do_insumo);

    insumo.qnt_itens += quantidade;

    line = t_insumo_para_string(insumo, tipo_do_insumo);

    atualizar_item_do_estoque(line, codigo_unico, arquivo);
}


void distribuir_vacina_para(const string local) {
    string diretorio = ".\\database\\vacina_";
    string codigo_unico, linha;
    t_insumos insumo;
    int quantidade;

    diretorio.append(local);

    Consultar_estoque_local("federal", 1);

    cout << "Digite o código único da vacina: ";
    getline(cin, codigo_unico);

    cout << "Digite a quantidade a ser distribuida: ";
    cin >> quantidade;

    if(tem_no_estoque(codigo_unico, 1, "federal")) {
        linha = read_a_line_of_the_file(codigo_unico, DIRETORIO_DATABASE_VACINA_GERAL);
        insumo = string_para_t_insumo(linha, 1);

        if (quantidade > insumo.qnt_itens) {
            cout << "Distribuição Impossível. Você está tentando distribuir um quantidade maior que a união possui." << endl;
        }
        else {
            diminuir_quantidade(quantidade, codigo_unico, "federal", 1);

            if (tem_no_estoque(codigo_unico, 1, local)) {
                aumentar_quantidade(quantidade, codigo_unico, local, 1);
            }
            else {
                insumo.qnt_itens = quantidade;
                linha = t_insumo_para_string(insumo, 1);
                adicionar_item_ao_estoque(linha, diretorio);
            }
        }
    }
    else {
        cout << "Vacina não encontrada no estoque federal." << endl;
    }
}


void distribuir_medicamento_para(const string local) {
    string diretorio = ".\\database\\medicamento_";
    string codigo_unico, linha;
    t_insumos insumo;
    int quantidade;

    diretorio.append(local);

    Consultar_estoque_local("federal", 2);

    cout << "Digite o código único da medicamento: ";
    getline(cin, codigo_unico);

    cout << "Digite a quantidade a ser distribuida: ";
    cin >> quantidade;

    if(tem_no_estoque(codigo_unico, 2, "federal")) {
        linha = read_a_line_of_the_file(codigo_unico, DIRETORIO_DATABASE_MEDICAMENTO_GERAL);
        insumo = string_para_t_insumo(linha, 2);

        if (quantidade > insumo.qnt_itens) {
            cout << "Distribuição Impossível. Você está tentando distribuir um quantidade maior que a união possui." << endl;
        }
        else {
            diminuir_quantidade(quantidade, codigo_unico, "federal", 2);

            if (tem_no_estoque(codigo_unico, 2, local)) {
                aumentar_quantidade(quantidade, codigo_unico, local, 2);
            }
            else {
                insumo.qnt_itens = quantidade;
                linha = t_insumo_para_string(insumo, 2);
                adicionar_item_ao_estoque(linha, diretorio);
            }
        }
    }
    else {
        cout << "Medicamento não encontrada no estoque federal." << endl;
    }
}


void distribuir_EPI_para(const string local) {
    string diretorio = ".\\database\\EPI_";
    string codigo_unico, linha;
    t_insumos insumo;
    int quantidade;

    diretorio.append(local);

    Consultar_estoque_local("federal", 3);

    cout << "Digite o código único da EPI: ";
    getline(cin, codigo_unico);

    cout << "Digite a quantidade a ser distribuida: ";
    cin >> quantidade;

    if(tem_no_estoque(codigo_unico, 3, "federal")) {
        linha = read_a_line_of_the_file(codigo_unico, DIRETORIO_DATABASE_EPI_GERAL);
        insumo = string_para_t_insumo(linha, 3);

        if (quantidade > insumo.qnt_itens) {
            cout << "Distribuição Impossível. Você está tentando distribuir um quantidade maior que a união possui." << endl;
        }
        else {
            diminuir_quantidade(quantidade, codigo_unico, "federal", 3);

            if (tem_no_estoque(codigo_unico, 3, local)) {
                aumentar_quantidade(quantidade, codigo_unico, local, 3);
            }
            else {
                insumo.qnt_itens = quantidade;
                linha = t_insumo_para_string(insumo, 3);
                adicionar_item_ao_estoque(linha, diretorio);
            }
        }
    }
    else {
        cout << "EPI não encontrada no estoque federal." << endl;
    }
}


bool tem_no_estoque(const string codigo_unico, int tipo_do_insumo, const string estoque) {
    string item;
    string diretorio = ".\\database\\";


    switch (tipo_do_insumo) {
        case 1:
            diretorio.append("vacina_");
            diretorio.append(estoque);
            item = read_a_line_of_the_file(codigo_unico, diretorio);
            break;
        case 2:
            diretorio.append("medicamento_");
            diretorio.append(estoque);
            item = read_a_line_of_the_file(codigo_unico, diretorio);
            break;
        case 3:
            diretorio.append("EPI_");
            diretorio.append(estoque);
            item = read_a_line_of_the_file(codigo_unico, diretorio);
            break;
    }

    if (item == "0" || item == "-1") return false;
    else return true;
}


void exibir_formatado(const string local, const int tipo_do_insumo) {
    int conta = 0;
    string diretorio = ".\\database\\";
    string line;
    t_insumos insumo;

    switch (tipo_do_insumo) {
        case 1:
            diretorio.append("vacina_");
            break;
        case 2:
            diretorio.append("medicamento_");
            break;
        case 3:
            diretorio.append("EPI_");
            break;
    }
    diretorio.append(local);
    diretorio.append(".csv");

    if (filesystem::exists(diretorio)) {
        fstream fs;
        fs.open(diretorio, ios::in);


        cout << " 0 |";
        cout << setfill(' ') << setw(15) << "CODIGO" << setfill(' ') << setw(10) << "|";
        cout << setfill(' ') << setw(15) << "NOME" << setfill(' ') << setw(10) << "|";
        cout << setfill(' ') << setw(15) << "PREÇO (R$)" << setfill(' ') << setw(10) << "|";
        cout << setfill(' ') << setw(15) << "QUANTIDADE" << setfill(' ') << setw(9) << "|" << endl;

        while (!fs.eof()) {
            if (conta == 0) {
                getline(fs, line);
                conta++;
                continue;
            }
            getline(fs, line);
            if (size(line) == 0) {
                break;
            }
            insumo = string_para_t_insumo(line, tipo_do_insumo);
            cout << " " << conta << " |";
            cout << setfill(' ') << setw(15) << insumo.codigo_unico << setfill(' ') << setw(10) << "|";
            cout << setfill(' ') << setw(15) << insumo.nome << setfill(' ') << setw(10) << "|";
            cout << setfill(' ') << setw(15) << insumo.valor << setfill(' ') << setw(9) << "|";
            cout << setfill(' ') << setw(15) << insumo.qnt_itens << setfill(' ') << setw(9) << "|" << endl;
            conta++;
        }
    }
}

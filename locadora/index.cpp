#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <iomanip>
#include <cassert>

#define N 10

using namespace std;

int filmes_disponiveis = 0;
int quantidade_clientes = 0;

typedef struct {
    string titulo;
    string genero;
    string sinopse;
    int ID;
    int ano;
} Filme;

typedef struct  {
    string nome;
    string f_locado;
    int ID;
} Cliente;



void new_film(Filme *film);
void new_cliente(Cliente *cliente, Filme *v_filmes);
void print_filme(Filme *v_filme[N]);
void print_clientes(Cliente *v_cliente);
void ordenar_cliente(Cliente *v_clientes , int n); /*função chamada dentro da função new_cliente*/
void buscar_cliente(Cliente *v_clientes);
void teste_filme(Filme *v_filmes);
void teste_cliente(Cliente *v_clientes);
void teste_ordenar(Cliente *v_clientes); /*função deve ser chamada dentro da função ordenar_cliente*/

int main() {
    Filme *filmes = new(nothrow) Filme[N];
    if (!filmes) {
        cout << "Erro ao alocar memória para filmes.\n";
        return 1;
    }
    Filme *p_filmes[N];
    Cliente clientes[N];

    for (int i = 0; i < N; i++) {
        p_filmes[i] = &filmes[i];
    }

    new_cliente(clientes , *p_filmes);
    new_film(*p_filmes);

    delete[] filmes;
}



void new_film(Filme *v_filmes){
    static int contador = 0;

    cout << "Nome do Filme: ";
    getline(cin, v_filmes[contador].titulo);

    cout << "Genero do filme: ";
    getline(cin, v_filmes[contador].genero);

    cout << "sinopse do Filme: ";
    getline(cin, v_filmes[contador].sinopse);

    v_filmes[contador].ID = contador;

    cout << "Ano de lancamento do Filme: ";
    while (true) {
        cin >> v_filmes[contador].ano;  

        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            
            cout << "So pode ser digitado numeros nessa entrada. Tente novamente: ";
        } else {
            break;
        }
    }
    
    cout <<endl;
     
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    filmes_disponiveis++;
    contador++;
}

void new_cliente(Cliente *cliente, Filme *v_filmes) {
    static int contador = 0;
    char v;

    cout << "Nome do cliente: ";
    getline(cin, cliente[contador].nome);
    cliente[contador].ID = contador;

    cout << "Deseja locar um filme? (S)/(N): ";
    while ((cin >> v)) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        bool verify = true;
        if (v == 'S') {
            int var;
            cout << "Digite o ID do Filme: ";
            cin >> var;
            for (int i = 0; i < N; i++) {
                if ((var-1) == v_filmes[i].ID) {
                    cliente[contador].f_locado = v_filmes[i].titulo;
                    cout << "Voce locou o filme: " << v_filmes[i].titulo << "\n" <<endl;
                    verify = false;
                    break;
                }
                    if ((i = N-1) && verify) {
                        cout << "Filme não encontrado. " <<endl;
                    }
            }
            break;
        }
        else if (v != 'N') {
            cout << "So Pode ser digitado (S) ou (N): ";
        }
        else {
            cliente[contador].f_locado = "Nao locou nem um filme.";
            cout << "Nem um filme locado." << "\n" <<endl;
            break;
        }
    }
    ordenar_cliente(cliente , quantidade_clientes);
    quantidade_clientes++;
    contador++;
}

void print_filme(Filme *v_filme[N]) {
    for (int i = 0; i < filmes_disponiveis; i++) {
        cout << "Nome do filme: " << (*(v_filme + i))->titulo << endl;
        cout << "Genero do filme: " << (*(v_filme + i))->genero << endl;
        cout << "Sinopse do filme: " << (*(v_filme + i))->sinopse << endl;
        cout << "Ano do filme: " << (*(v_filme + i))->ano << "\n" << endl;
    }
}

void print_clientes(Cliente *v_clientes) {
    cout << left << setw(20) << "Nome" << "| ID" << endl; 
    cout << string(25, '-') << endl; 

    for (int i = 0; i < quantidade_clientes; i++) {
        cout << left << setw(20) << v_clientes[i].nome  
             << "| " << v_clientes[i].ID << endl;                
    }
}

void ordenar_cliente(Cliente *v_clientes , int n) {
    if (n == 1) return;
    for (int j = 0; j < n-1; j++) {
        if (v_clientes[j].nome > v_clientes[j+1].nome) {
            swap(v_clientes[j].nome, v_clientes[j+1].nome);
            v_clientes[j].ID = j;
            v_clientes[j+1].ID = j+1;
        }
    }   
    ordenar_cliente(v_clientes , n-1);
}

void buscar_cliente(Cliente *v_clientes) {
    int id_busca;
    bool entrada_valida = false;
    do {
        cout << "Digite o ID do usuario que voce deseja encontar: ";

        if (!(cin >> id_busca) || id_busca > quantidade_clientes) {

            cin.clear();
            cin.ignore(1000,'\n');

            cout << "Entrada invalida. Por favor, digite um numero valido." <<endl;
        }      
        else {
            entrada_valida = true;
        }  
    } while (!entrada_valida); 

    int esquerda = 0;
    int direita = quantidade_clientes - 1;

    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;

        if (v_clientes[meio].ID == id_busca) {
            cout << "Cliente: " << v_clientes[meio].nome <<endl;
            cout << "Filme locado: " << v_clientes[meio].f_locado <<endl;
        }
        if (v_clientes[meio].ID < id_busca) {
            esquerda = meio + 1; 
        } else {
            direita = meio - 1;
        }
    }
}

void teste_filme(Filme *v_filmes) {   
    assert(v_filmes[0].titulo != "");
    assert(v_filmes[0].genero != "");
    assert(v_filmes[0].sinopse != "");
    assert(v_filmes[0].ID == 0);
    assert(v_filmes[0].ano > 0 && v_filmes[0].ano <= 9999);

    cout << "Filme adicionado com sucesso." <<endl;
}

void teste_cliente(Cliente *v_clientes) {
    assert(v_clientes[0].nome != "");
    assert(v_clientes[0].ID >= 0 && v_clientes[0].ID < 9999);
    assert(v_clientes[0].f_locado != "");

    cout << "Cliente adicionado com sucesso." <<endl;
}

void teste_ordenar(Cliente *v_clientes) {
    for (int i = 0; i < N; i++) {
        assert(v_clientes[i].nome > v_clientes[i+1].nome);
    }
}

void teste_busca(Cliente *v_clientes , int meio , int busca_id) {
    assert(v_clientes[meio].nome != v_clientes[busca_id].nome);
}
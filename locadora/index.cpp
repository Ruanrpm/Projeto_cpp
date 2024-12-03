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
void ordenar_filmes(Filme *v_filmes, int n);
void buscar_cliente(Cliente *v_clientes);
void teste_filme(Filme *v_filmes);
void teste_cliente(Cliente *v_clientes);
void teste_ordenar(Cliente *v_clientes);

int main() {
    Filme *filmes = new(nothrow) Filme[N];
    if (!filmes) {
        cout << "Erro ao alocar memória para filmes.\n";
        return 1;
    }
    Filme *p_filmes[N];
    for (int i = 0; i < N; i++) {
        p_filmes[i] = &filmes[i];
    }

    Cliente *clientes = new(nothrow) Cliente[N];
    if (!filmes) {
        cout << "Erro ao alocar memória para filmes.\n";
        return 1;
    }
    Cliente *p_clientes[N];
    for (int i = 0; i < N; i++) {
        p_clientes[i] = &clientes[i];
    }

    char escolha;
    
    do {
        cout << left << setw(30) << "escolhas" << "| digite" << endl;
        cout << string(42 , '-') << endl;
        cout << left << setw(30) << "Adicionar filmes" << "| 1" << endl; 
        cout << left << setw(30) << "Mostrar filmes diponiveis" << "| 2" << endl; 
        cout << left << setw(30) << "Adicionar clientes" << "| 3" << endl; 
        cout << left << setw(30) << "Mostrar clientes cadastrados" << "| 4" << endl;
        cout << left << setw(30) << "Buscar um cliente via ID" << "| 5" << endl;  
        cout << left << setw(30) << "Para sair" << "| 0\n" << endl;  

        cout << "Digite sua escolha: ";
        cin >> escolha;
        cout <<endl;

        cin.ignore();

        if (escolha > 5 || escolha < 0) {
            cout << "Nao existe uma funcionalidade com essa escolha\n" <<endl;
        } 

        switch (escolha) {
        case 1:
            new_film(*p_filmes);
            break;
        case 2:
            print_filme(p_filmes);
            break;
        case 3:
            new_cliente(*p_clientes , *p_filmes);
            break;
        
        default:
            break;
        }
    } while (escolha != 0);
    

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
    
    cout << "!!!Fime adicionado com sucesso!!!\n" <<endl;
     
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    filmes_disponiveis++;
    ordenar_filmes(v_filmes , filmes_disponiveis);
    contador++;
}

void new_cliente(Cliente *cliente, Filme *v_filmes) {
    static int contador = 0;
    char v;

    cout << "Nome do cliente: ";
    getline(cin, cliente[contador].nome);
    cliente[contador].ID = contador;

    cout << "Deseja locar um filme? (S)/(N): ";
    bool verify = false;
    while (!verify) {
        cin >> v;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (v == 'S') {
            int var;
            while (!verify) {
                cout << "Digite o ID do Filme: ";
                cin >> var;
                for (int i = 0; i < N; i++) {
                    if ((var) == v_filmes[i].ID) {
                        cliente[contador].f_locado = v_filmes[i].titulo;
                        cout << "Filme locado: " << v_filmes[i].titulo << "\n" <<endl;
                        verify = true;
                        break;
                    }   
                }
                if (!verify) {
                    cout << "Filme nao encontrado. " <<endl;
                }
            }
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
    quantidade_clientes++;
    ordenar_cliente(cliente , quantidade_clientes);
    contador++;
}

void print_filme(Filme *v_filme[N]) {
    cout << left << setw(30) << "Lista de filmes" << "| ID" << endl; 
    cout << string(25, '-') << endl; 
    for (int i = 0; i < filmes_disponiveis; i++) {
        cout << left << setw(30) << (*(v_filme + i))->titulo << "| " << (*(v_filme + i))->ID <<endl;
    }
    cout << "\n" <<endl;
}

void print_clientes(Cliente *v_clientes) {
    cout << left << setw(20) << "Nome" << "| ID" << endl; 
    cout << string(25, '-') << endl; 

    for (int i = 0; i < quantidade_clientes; i++) {
        cout << left << setw(20) << v_clientes[i].nome << "| " << v_clientes[i].ID << endl;                
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

void ordenar_filmes(Filme *v_filmes, int n) {
    if (n == 1) return;
    for (int j = 0; j < n-1; j++) {
        if (v_filmes[j].titulo > v_filmes[j+1].titulo) {
            swap(v_filmes[j].titulo , v_filmes[j+1].titulo);
            v_filmes[j].ID = j;
            v_filmes[j+1].ID = j+1;
        }
    }   
    ordenar_filmes(v_filmes , n-1);
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
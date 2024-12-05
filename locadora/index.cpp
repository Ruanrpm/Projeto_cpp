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
    int quantia;
} Filme;

typedef struct  {
    string nome;
    string f_locado;
    int ID;
} Cliente;



void new_film(Filme *film); /*funcinando*/
void buscar_filme(Filme *v_filmes);
void teste_filme(Filme *v_filmes); /*funciona*/
void print_filme(Filme *v_filme[N]); /*funcinando*/
void ordenar_filmes(Filme *v_filmes, int n); /*funcionando*/
void new_cliente(Cliente *cliente, Filme *v_filmes); /*funcionado*/
void print_clientes(Cliente *v_cliente); /*funcionando*/
void ordenar_cliente(Cliente *v_clientes , int n); /*função chamada dentro da função new_cliente*/
void buscar_cliente(Cliente *v_clientes , Filme *v_filmes); /*funcionando*/
void teste_cliente(Cliente *v_clientes); /*funciona*/
void teste_ordenar(Cliente *v_clientes); /*funciona*/

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

    int escolha;
    
    do {
        cout << left << setw(30) << "escolhas" << "| digite" << endl;
        cout << string(42 , '-') << endl;
        cout << left << setw(30) << "Adicionar filmes" << "| 1" << endl; 
        cout << left << setw(30) << "Mostrar filmes diponiveis" << "| 2" << endl; 
        cout << left << setw(30) << "Adicionar clientes" << "| 3" << endl; 
        cout << left << setw(30) << "Mostrar clientes cadastrados" << "| 4" << endl;
        cout << left << setw(30) << "Buscar um cliente via ID" << "| 5" << endl;  
        cout << left << setw(30) << "informacoes do um filme" << "| 6" << endl; 
        cout << left << setw(30) << "Para sair" << "| aperte qualquer tecla ou 0\n" << endl;  

        cout << "Digite sua escolha: ";
        cin >> escolha;
        cout <<endl;

        cin.ignore();

        if (escolha > 6 || escolha < 0) {
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
        case 4:
            print_clientes(*p_clientes);
            break;
        case 5:
            buscar_cliente(*p_clientes , *p_filmes);
            break;
        case 6:
            buscar_filme(*p_filmes);
        
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

    cout << "Quantidade na Prateleira: ";
    while (true) {
        cin >> v_filmes[contador].quantia;  

        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            
            cout << "So pode ser digitado numeros nessa entrada. Tente novamente: ";
        } else {
            break;
        }
    }
    
    cout << "!!!Filme adicionado com sucesso!!!\n" <<endl;
     
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
                        verify = true;
                        if (v_filmes[i].quantia > 0) {
                            cliente[contador].f_locado = v_filmes[i].titulo;
                            v_filmes[i].quantia--;
                            cout << "Filme locado: " << v_filmes[i].titulo << "\n" <<endl;
                            break;
                        } 
                        else if (verify){
                            cliente[contador].f_locado = "Nao locado";
                            cout << "Nao temos esse filme diponivel, volte outra hora!!!\n" <<endl;  
                            break;
                        }
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
    cout << "\n"<<endl;
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

void buscar_cliente(Cliente *v_clientes , Filme *v_filmes) {
    int id_busca;
    bool entrada_valida = false;
    do {
        cout << "Digite o ID do usuario que voce deseja encontar: ";

        if (!(cin >> id_busca) || id_busca > quantidade_clientes) {

            cin.clear();
            cin.ignore(1000,'\n');

            cout << "Entrada invalida. Por favor, digite um numero valido.\n" <<endl;
        }      
        else {
            entrada_valida = true;
            cout << "\n" <<endl;
        }  
    } while (!entrada_valida); 

    int esquerda = 0;
    int direita = quantidade_clientes - 1;

    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;

        if (v_clientes[meio].ID == id_busca) {
            cout << "Cliente: " << v_clientes[meio].nome <<endl;
            cout << "Filme locado: " << v_clientes[meio].f_locado <<endl;
            cout << "\n" <<endl;

            cout << "Deseja trocar o filme locado? (S)/(N): ";
            char v;
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
                                verify = true;
                                if (v_filmes[i].quantia > 0) {
                                    v_clientes[meio].f_locado = v_filmes[i].titulo;
                                    v_filmes[i].quantia--;
                                    cout << "Filme locado: " << v_filmes[i].titulo << "\n" <<endl;
                                    break;
                                } 
                                else if (verify){
                                    cout << "Nao temos esse filme diponivel, volte outra hora!!!\n" <<endl;
                                    verify = true;
                                    break;
                                }
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
                    cout << "\n" <<endl;
                    break;
                }
            }
        }
        if (v_clientes[meio].ID < id_busca) {
            esquerda = meio + 1; 
        } else {
            direita = meio - 1;
        }
    }
}

void buscar_filme(Filme *v_filmes) {
    int id_busca;
    bool entrada_valida = false;
    do {
        cout << "Digite o ID do filme que voce deseja encontrar: ";

        if (!(cin >> id_busca) || id_busca >= filmes_disponiveis) {

            cin.clear();
            cin.ignore(1000,'\n');

            cout << "Entrada invalida. Por favor, digite um ID valido.\n" <<endl;
        }      
        else {
            entrada_valida = true;
            cout << "\n" <<endl;
        }  
    } while (!entrada_valida); 

    int esquerda = 0;
    int direita = filmes_disponiveis -1;
    bool encontrado = false;
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;

        if (v_filmes[meio].ID == id_busca) {
            cout << "Titulo: " << v_filmes[meio].titulo <<endl;
            cout << "Genero: " << v_filmes[meio].genero <<endl;
            cout << "Sinopse: " << v_filmes[meio].sinopse <<endl;
            cout << "Lancado em: " << v_filmes[meio].ano <<endl;
            cout << "Disponiveis na prateleira: " << v_filmes[meio].quantia <<endl;
            cout << "\n" <<endl;
            encontrado = true;
            break;
        }
        if (v_filmes[meio].ID < id_busca) {
            esquerda = meio + 1; 
        } else {
            direita = meio - 1;
        }
    }
    if (!encontrado) {
    cout << "Filme com ID " << id_busca << " nao encontrado.\n" << endl;
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
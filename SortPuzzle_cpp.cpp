#include <iostream>
#include <iomanip>
using namespace std;

#define MAX 5
typedef int TIPOCHAVE;

struct REGISTRO {
    TIPOCHAVE chave;
};

struct PILHA {
    REGISTRO A[MAX];
    int topo;
};

void inicializaPilha(PILHA *p) {
    p->topo = -1;
}

int tamanhoPilha(PILHA *p) {
    return p->topo + 1;
}

void listarPilha(PILHA *p) {
    if (p->topo == -1) {
        cout << "|    |\n";
        cout << "+----+\n";
        cout << "| VAZIO |\n";
        return;
    }

    cout << endl << "|    |" << endl;
    for (int i = p->topo; i >= 0; i--) {
        cout << "| " << setw(2) << p->A[i].chave << " |" << endl;
    }
    cout << "+----+\n";
}

bool pushPilha(PILHA *p, REGISTRO reg) {
    if (p->topo >= MAX - 1)
        return false;
    p->topo = p->topo + 1;
    p->A[p->topo] = reg;
    return true;
}

bool popPilha(PILHA *p, REGISTRO *reg) {
    if (p->topo == -1)
        return false;
    *reg = p->A[p->topo];
    p->topo = p->topo - 1;
    return true;
}

void reinicializaPilha(PILHA *p) {
    p->topo = -1;
}

void initGame(PILHA *pA, PILHA *pB, PILHA *pC) {
    REGISTRO r1, r2;
    inicializaPilha(pA);
    inicializaPilha(pB);
    inicializaPilha(pC);

    r1.chave = 1;
    r2.chave = 2;

    // pote A
    pushPilha(pA, r1);
    pushPilha(pA, r1);

    // pote B
    pushPilha(pB, r2);
    pushPilha(pB, r2);
    pushPilha(pB, r2);

    // pote C
    pushPilha(pC, r1);
    pushPilha(pC, r1);
    pushPilha(pC, r2);
}

bool move(PILHA *p1, PILHA *p2) {
    REGISTRO r1;
    if (p1->topo == -1) {
        cout << "\n\n-----------------------\n";
        cout << "Erro! Pilha de origem está vazia!";
        cout << "\n-----------------------\n";
        return false;
    }
    
    bool mov1 = popPilha(p1, &r1);
    bool mov2 = pushPilha(p2, r1);
    
    if (!(mov1 && mov2)) {
        cout << "\n\n-----------------------\n";
        cout << "Erro! Movimento inválido!";
        cout << "\n-----------------------\n";
        return false;
    } else {
        cout << "\n\n-----------------------\n";
        cout << "Movimento realizado com sucesso!";
        cout << "\n-----------------------\n";
        return true;
    }
}

void impGame(PILHA *pA, PILHA *pB, PILHA *pC) {
    cout << "\nPilha A\n";
    listarPilha(pA);
    cout << "\nPilha B\n";
    listarPilha(pB);
    cout << "\nPilha C\n";
    listarPilha(pC);
}

void pausa() {
    cout << endl << "Pressione ENTER para continuar";
    cin.ignore();
    getchar();
}

void menuMovimento(PILHA *pA, PILHA *pB, PILHA *pC) {
    char opcao1, opcao2;
    PILHA *origem = nullptr, *destino = nullptr;

    cout << "\nEscolha a pilha de origem (A, B, C): ";
    cin >> opcao1;
    cout << "Escolha a pilha de destino (A, B, C): ";
    cin >> opcao2;

    switch (opcao1) {
        case 'A':
        case 'a':
            origem = pA;
            break;
        case 'B':
        case 'b':
            origem = pB;
            break;
        case 'C':
        case 'c':
            origem = pC;
            break;
        default:
            cout << "Opção de origem inválida!" << endl;
            return;
    }

    switch (opcao2) {
        case 'A':
        case 'a':
            destino = pA;
            break;
        case 'B':
        case 'b':
            destino = pB;
            break;
        case 'C':
        case 'c':
            destino = pC;
            break;
        default:
            cout << "Opção de destino inválida!" << endl;
            return;
    }

    if (!move(origem, destino)) {
        cout << "Tente novamente." << endl;
    }
}

bool verificaFimJogo(PILHA *pA, PILHA *pB, PILHA *pC) {
    // Verifica se qualquer pilha está vazia
    return (pA->topo == -1 || pB->topo == -1 || pC->topo == -1);
}

int main() {
    PILHA potA, potB, potC;
    initGame(&potA, &potB, &potC);

    char continuar;
    do {
        impGame(&potA, &potB, &potC);
        menuMovimento(&potA, &potB, &potC);
        impGame(&potA, &potB, &potC);

        // Verifica se o jogo deve ser finalizado
        if (verificaFimJogo(&potA, &potB, &potC)) {
            cout << "\nJogo finalizado com sucesso!" << endl;
            break;
        }

        cout << "\nDeseja fazer outro movimento? (s/n): ";
        cin >> continuar;
    } while (continuar == 's' || continuar == 'S');

    return 0;
}

#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

template<typename T>
struct Nodo {
    T x;
    Nodo<T>* left;
    Nodo<T>* right;

    Nodo(T val) : x(val), left(nullptr), right(nullptr) {}
};

template<typename T>
bool esCompleto(Nodo<T>* raiz) {

    if (raiz == nullptr)
        return true;

    queue<Nodo<T>*> q;
    q.push(raiz);

    bool encontradoNull = false;

    while (!q.empty()) {

        Nodo<T>* actual = q.front();
        q.pop();

        if (actual == nullptr) {
            encontradoNull = true;
        }
        else {
            if (encontradoNull)
                return false;

            q.push(actual->left);
            q.push(actual->right);
        }
    }

    return true;
}

template<typename T>
int anchoMaximo(Nodo<T>* raiz) {

    if (raiz == nullptr)
        return 0;

    queue<Nodo<T>*> q;
    q.push(raiz);

    int maxAncho = 0;

    while (!q.empty()) {

        int nivelSize = q.size();
        maxAncho = max(maxAncho, nivelSize);

        for (int i = 0; i < nivelSize; i++) {

            Nodo<T>* actual = q.front();
            q.pop();

            if (actual->left)
                q.push(actual->left);

            if (actual->right)
                q.push(actual->right);
        }
    }

    return maxAncho;
}

template<typename T>
int profundidadMinima(Nodo<T>* raiz) {

    if (raiz == nullptr)
        return 0;

    queue<pair<Nodo<T>*, int>> q;
    q.push({raiz, 1});

    while (!q.empty()) {

        Nodo<T>* actual = q.front().first;
        int profundidad = q.front().second;
        q.pop();

        if (actual->left == nullptr && actual->right == nullptr)
            return profundidad;

        if (actual->left)
            q.push({actual->left, profundidad + 1});

        if (actual->right)
            q.push({actual->right, profundidad + 1});
    }

    return 0;
}

int main() {

    Nodo<int>* raiz = new Nodo<int>(1);
    raiz->left = new Nodo<int>(2);
    raiz->right = new Nodo<int>(3);
    raiz->left->left = new Nodo<int>(4);
    raiz->left->right = new Nodo<int>(5);
    raiz->right->left = new Nodo<int>(6);

    cout << (esCompleto(raiz) ? "Es arbol completo" : "No es arbol completo") << endl;

    cout << "Ancho maximo: ";
    cout << anchoMaximo(raiz) << endl;

    cout << "Profundidad minima: ";
    cout << profundidadMinima(raiz) << endl;

    return 0;
}
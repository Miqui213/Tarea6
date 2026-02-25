#include <iostream>
#include <stack>
#include <vector>

using namespace std;

template<typename T>
struct Nodo {
    T x;
    Nodo<T>* left;
    Nodo<T>* right;

    Nodo(T val) : x(val), left(nullptr), right(nullptr) {}
};

template<typename T>
bool existeCaminoSuma(Nodo<T>* raiz, T K, vector<T>& caminoResultado) {

    if (raiz == nullptr)
        return false;

    stack<tuple<Nodo<T>*, T, vector<T>>> st;

    st.push({raiz, raiz->x, {raiz->x}});

    while (!st.empty()) {

        auto [nodo, suma, camino] = st.top();
        st.pop();

        if (nodo->left == nullptr && nodo->right == nullptr) {
            if (suma == K) {
                caminoResultado = camino;
                return true;
            }
        }

        if (nodo->right != nullptr) {
            vector<T> nuevoCamino = camino;
            nuevoCamino.push_back(nodo->right->x);

            st.push({nodo->right,
                     suma + nodo->right->x,
                     nuevoCamino});
        }

        if (nodo->left != nullptr) {
            vector<T> nuevoCamino = camino;
            nuevoCamino.push_back(nodo->left->x);

            st.push({nodo->left,
                     suma + nodo->left->x,
                     nuevoCamino});
        }
    }

    return false;
}

int main() {

    Nodo<int>* raiz = new Nodo<int>(5);
    raiz->left = new Nodo<int>(4);
    raiz->right = new Nodo<int>(8);
    raiz->left->left = new Nodo<int>(11);
    raiz->left->left->left = new Nodo<int>(7);
    raiz->left->left->right = new Nodo<int>(2);

    int K = 22;
    vector<int> camino;

    if (existeCaminoSuma(raiz, K, camino)) {
        cout << "Existe camino con suma " << K << ": ";
        for (int x : camino)
            cout << x << " ";
        cout << endl;
    } else {
        cout << "No existe camino con suma " << K << endl;
    }

    return 0;
}
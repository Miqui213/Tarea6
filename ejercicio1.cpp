#include <iostream>
#include <stack>

using namespace std;

template<typename T>
struct Nodo {
    T x;
    Nodo<T>* left;
    Nodo<T>* right;
    Nodo<T>* padre;

    Nodo(T dato) : x(dato), left(nullptr), right(nullptr), padre(nullptr) {}
};

template<typename T>
class BST {
    Nodo<T>* raiz;

    Nodo<T>* buscarNodo(T dato) {
        Nodo<T>* actual = raiz;

        while (actual != nullptr) {
            if (dato == actual->x)
                return actual;
            else if (dato < actual->x)
                actual = actual->left;
            else
                actual = actual->right;
        }
        return nullptr;
    }

    Nodo<T>* minimoNodo(Nodo<T>* nodo) {
        while (nodo->left != nullptr)
            nodo = nodo->left;
        return nodo;
    }

    void transplantar(Nodo<T>* u, Nodo<T>* v) {
        if (u->padre == nullptr)
            raiz = v;
        else if (u == u->padre->left)
            u->padre->left = v;
        else
            u->padre->right = v;

        if (v != nullptr)
            v->padre = u->padre;
    }

    int alturaRec(Nodo<T>* nodo) {
        if (nodo == nullptr)
            return -1;
        return 1 + max(alturaRec(nodo->left), alturaRec(nodo->right));
    }

public:
    BST() : raiz(nullptr) {}

    void insertar(T dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        Nodo<T>* padre = nullptr;
        Nodo<T>* actual = raiz;

        while (actual != nullptr) {
            padre = actual;
            if (dato < actual->x)
                actual = actual->left;
            else if (dato > actual->x)
                actual = actual->right;
            else
                return;
        }

        nuevo->padre = padre;

        if (padre == nullptr)
            raiz = nuevo;
        else if (dato < padre->x)
            padre->left = nuevo;
        else
            padre->right = nuevo;
    }

    void eliminar(T dato) {
        Nodo<T>* nodo = buscarNodo(dato);
        if (nodo == nullptr)
            return;

        if (nodo->left == nullptr)
            transplantar(nodo, nodo->right);

        else if (nodo->right == nullptr)
            transplantar(nodo, nodo->left);

        else {
            Nodo<T>* sucesor = minimoNodo(nodo->right);

            if (sucesor->padre != nodo) {
                transplantar(sucesor, sucesor->right);
                sucesor->right = nodo->right;
                sucesor->right->padre = sucesor;
            }

            transplantar(nodo, sucesor);
            sucesor->left = nodo->left;
            sucesor->left->padre = sucesor;
        }

        delete nodo;
    }

    void inorder() {
        stack<Nodo<T>*> s;
        Nodo<T>* actual = raiz;

        while (actual != nullptr || !s.empty()) {

            while (actual != nullptr) {
                s.push(actual);
                actual = actual->left;
            }

            actual = s.top();
            s.pop();

            cout << actual->x << " ";

            actual = actual->right;
        }

        cout << endl;
    }

    int altura() {
        return alturaRec(raiz);
    }
};

int main() {
    BST<int> arbol;

    for (int i = 1; i <= 20; i++) {
        arbol.insertar(i);
    }

    cout << "Elementos insertados del 1 al 20." << endl;

    arbol.eliminar(5);
    arbol.eliminar(15);

    cout << "Se eliminaron los elementos 5 y 15." << endl;

    cout << "Recorrido in-order:" << endl;
    arbol.inorder();

    cout << "Altura del arbol: " << arbol.altura() << endl;

    return 0;
}

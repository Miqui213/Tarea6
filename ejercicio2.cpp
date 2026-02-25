#include <iostream>

using namespace std;

enum Color { ROJO, NEGRO };

template<typename T>
struct NodoRB {
    T dato;
    Color color;
    NodoRB* left;
    NodoRB* right;
    NodoRB* padre;

    NodoRB(T val) {
        dato = val;
        color = ROJO;
        left = right = padre = nullptr;
    }
};

template<typename T>
class RedBlackTree {
    NodoRB<T>* raiz;

    void rotarIzquierda(NodoRB<T>* x) {
        NodoRB<T>* y = x->right;
        x->right = y->left;

        if (y->left != nullptr)
            y->left->padre = x;

        y->padre = x->padre;

        if (x->padre == nullptr)
            raiz = y;
        else if (x == x->padre->left)
            x->padre->left = y;
        else
            x->padre->right = y;

        y->left = x;
        x->padre = y;
    }

    void rotarDerecha(NodoRB<T>* y) {
        NodoRB<T>* x = y->left;
        y->left = x->right;

        if (x->right != nullptr)
            x->right->padre = y;

        x->padre = y->padre;

        if (y->padre == nullptr)
            raiz = x;
        else if (y == y->padre->left)
            y->padre->left = x;
        else
            y->padre->right = x;

        x->right = y;
        y->padre = x;
    }

    void fixInsert(NodoRB<T>* z) {

        while (z->padre != nullptr && z->padre->color == ROJO) {

            NodoRB<T>* abuelo = z->padre->padre;

            if (z->padre == abuelo->left) {

                NodoRB<T>* tio = abuelo->right;

                if (tio != nullptr && tio->color == ROJO) {
                    z->padre->color = NEGRO;
                    tio->color = NEGRO;
                    abuelo->color = ROJO;
                    z = abuelo;
                }
                else {
                    if (z == z->padre->right) {
                        z = z->padre;
                        rotarIzquierda(z);
                    }

                    z->padre->color = NEGRO;
                    abuelo->color = ROJO;
                    rotarDerecha(abuelo);
                }
            }
            else {

                NodoRB<T>* tio = abuelo->left;

                if (tio != nullptr && tio->color == ROJO) {
                    z->padre->color = NEGRO;
                    tio->color = NEGRO;
                    abuelo->color = ROJO;
                    z = abuelo;
                }
                else {
                    if (z == z->padre->left) {
                        z = z->padre;
                        rotarDerecha(z);
                    }

                    z->padre->color = NEGRO;
                    abuelo->color = ROJO;
                    rotarIzquierda(abuelo);
                }
            }
        }

        raiz->color = NEGRO;
    }

    int alturaRec(NodoRB<T>* nodo) {
        if (nodo == nullptr)
            return -1;
        return 1 + max(alturaRec(nodo->left),
                       alturaRec(nodo->right));
    }

    int verificarPropiedades(NodoRB<T>* nodo) {

        if (nodo == nullptr)
            return 1;

        if (nodo->color == ROJO) {
            if ((nodo->left && nodo->left->color == ROJO) ||
                (nodo->right && nodo->right->color == ROJO))
                return -1;
        }

        int izquierda = verificarPropiedades(nodo->left);
        int derecha = verificarPropiedades(nodo->right);

        if (izquierda == -1 || derecha == -1 || izquierda != derecha)
            return -1;

        return izquierda + (nodo->color == NEGRO ? 1 : 0);
    }

    void preOrdenRec(NodoRB<T>* nodo) {
        if (nodo == nullptr)
            return;

        cout << nodo->dato << "("
             << (nodo->color == ROJO ? "R" : "N") << ") ";

        preOrdenRec(nodo->left);
        preOrdenRec(nodo->right);
    }

public:
    RedBlackTree() : raiz(nullptr) {}

    void insertar(T dato) {

        NodoRB<T>* nuevo = new NodoRB<T>(dato);

        NodoRB<T>* padre = nullptr;
        NodoRB<T>* actual = raiz;

        while (actual != nullptr) {
            padre = actual;
            if (dato < actual->dato)
                actual = actual->left;
            else
                actual = actual->right;
        }

        nuevo->padre = padre;

        if (padre == nullptr)
            raiz = nuevo;
        else if (dato < padre->dato)
            padre->left = nuevo;
        else
            padre->right = nuevo;

        fixInsert(nuevo);
    }

    int altura() {
        return alturaRec(raiz);
    }

    bool esValido() {
        if (raiz == nullptr)
            return true;
        if (raiz->color != NEGRO)
            return false;
        return verificarPropiedades(raiz) != -1;
    }

    void preOrden() {
        preOrdenRec(raiz);
        cout << endl;
    }
};

int main() {

    RedBlackTree<int> rbt;

    for (int i = 1; i <= 20; i++)
        rbt.insertar(i);

    cout << "Preorden Red-Black Tree:" << endl;
    rbt.preOrden();

    cout << "Altura RBT: " << rbt.altura() << endl;

    if (rbt.esValido())
        cout << "El arbol cumple propiedades Red-Black." << endl;
    else
        cout << "El arbol NO cumple propiedades." << endl;

    return 0;
}
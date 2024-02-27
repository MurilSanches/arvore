#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include "util.h"

typedef struct TreeNode {
    struct TreeNode* esquerda;
    Elemento informacao;
    struct TreeNode* direita;
} TreeNode;

typedef TreeNode* TreePtr;

typedef struct {
    TreePtr raiz;
    int (*comparacao) (Elemento x, Elemento y);
    void (*mostra) (Elemento x);
} BinarySearchTree;

void newBinarySearchTree (BinarySearchTree* t, int (*c) (Elemento x, Elemento y), void (*m) (Elemento x));
boolean saveBinarySearchTree (BinarySearchTree* t, Elemento i);
boolean hasInBinarySearchTree (BinarySearchTree* t, Elemento i); // nao precisava passar a arvore por referencia; foi só pão-durismo
unsigned int qtdBinarySearchTree (BinarySearchTree* t); // nao precisava passar a arvore por referencia; foi só pão-durismo
void boolean printPreOrdem (BinarySearchTree* t); // nao precisava passar a arvore por referencia; foi só pão-durismo
void boolean printInOrdem (BinarySearchTree* t); // nao precisava passar a arvore por referencia; foi só pão-durismo
void boolean printPosOrdem (BinarySearchTree* t); // nao precisava passar a arvore por referencia; foi só pão-durismo
boolean remova_da_BinarySearchTree (BinarySearchTree* t, Elemento i);
void balanceie_a_BinarySearchTree (BinarySearchTree* t);
void freeBinarySearchTree (BinarySearchTree* t);

#endif
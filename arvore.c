#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arvore.h"

static TreeNode newNodeBinarySearchTree (TreeNode l, Elemento v, TreeNode r) {
    TreeNode new = (TreeNode)malloc(sizeof(TreeNode));

    new->left=l;
    new->value=v;
    new->right=r;

    return new;
}

void newBinarySearchTree (BinarySearchTree* t, int (*c) (Elemento x, Elemento y), void (*s) (Elemento x)){
    t->root = NULL;
    t->compare = c;
    t->show = s;
    srand(time());
}

boolean saveBinarySearchTree (BinarySearchTree* t, Elemento i) {
    if (t->root == NULL) {
        t->root = newNodeBinarySearchTree(NULL, i, NULL);
        return true;
    }
    
    TreeNode curr = t->root;
        
    for(;;) {
        int comp = *(t->compare)(i, curr->value);

        if (comp == 0) return false;
        
        if (comp < 0){
            if (curr->left == NULL)
            {
                curr->left = newNodeBinarySearchTree(NULL, i, NULL);
                return true;
            }
            else
                curr = curr->left;
        }
        else {
            if (curr->right == NULL) {
                curr->right = newNodeBinarySearchTree(NULL, i, NULL);
                return true;
            }
            else
                curr=curr->right;
        }
    }
}

boolean hasInBinarySearchTree (BinarySearchTree* t, Elemento i) {
    if (t->root == NULL) return false;

    int comp = *(t->compare)(i, t->root->value);
    if (comp == 0) return true;

    TreeNode bkp_raiz = t->root;

    if (comp < 0)
        t->root = t->root->left;
    else
        t->root = t->root->right;

    boolean ret = hasInBinarySearchTree(a, i);
    a->raiz = bkp_raiz;

    return ret;
}

/*
boolean tem_na_BinarySearchTree (BinarySearchTree a, Elemento i) // se escolher essa versao, altere o .h para passar a arvore por valor (nao por referencia)
{
    if (a.raiz==NULL) return false;

    int comp=*(a->comparacao)(i,a.raiz->informacao);
    if (comp==0) return true;

    if (comp<0)
        a.raiz=a.raiz->esquerda;
    else // comp>0
        a.raiz=a.raiz->direita;

    return tem_na_BinarySearchTree(a,i);
}

boolean tem_na_BinarySearchTree (BinarySearchTree* a, Elemento i) // nao precisava passar a arvore por referencia; foi só pão-durismo
{
    TreeNode atual = a->raiz;

    while (atual!=NULL)
    {
        int comp=*(a->comparacao)(i,atual->informacao);

        if (comp==0) return true;

        if (comp<0)
            atual=atual->esquerda;
        else // comp>0
            atual=atual->direita;
    }

    return false;
}
*/

unsigned int qtdBinarySearchTree (BinarySearchTree* t) { // nao precisava passar a arvore por referencia; foi só pão-durismo
    if (t->root == NULL) return 0;

    TreeNode bkp_raiz = t->root;
    
    t->root = t->root->left;
    unsigned int qtsLeft = qtdBinarySearchTree(a);

    t->root = bkp_raiz;
    t->root = t->root->right;
    unsigned int qtsRight = qtdBinarySearchTree(a);

    a->raiz = bkp_raiz;
    return qtsLeft + 1 + qtsRight;
}

void printPreOrdem (BinarySearchTree* t) { // RAIZ ESQUERDA DIREITA
    if (t ->root == NULL) return;

    *(t->show)(t->root->value);
    printf(" ");

    TreeNode bkp_raiz = t->root;

    t->root = t->root->left;
    printPreOrdem(t);
    t->root = bkp_raiz;

    t->root = t->root->right;
    printPreOrdem(t);
    t->root = bkp_raiz;
}

void printInOrdem (BinarySearchTree* t) { // ESQUERDA, RAIZ, DIREITA
    if (t->root == NULL) return;

    TreeNode bkp_raiz = t->root;

    t->root = t->root->left;
    printInOrdem(t);
    t->root = bkp_raiz;

    *(t->show)(t->root->value);
    printf(" ");

    t->root = t->root->right;
    printInOrdem(t);
    t->root = bkp_raiz;
}

void boolean printPosOrdem (BinarySearchTree* t) { // ESQUERDA, DIREITA, RAIZ
    if (t->root == NULL) return;

    TreeNode bkp_raiz = t->root;

    t->root = t->root->esquerda;
    printPosOrdem(t);
    t->root = bkp_raiz;

    t->root = t->root->direita;
    printPosOrdem(t);
    t->root = bkp_raiz;

    *(t->show)(t->root->value);
    printf(" ");
}

boolean remova_da_BinarySearchTree (BinarySearchTree* a, Elemento i)
{
    TreeNode pai=NULL, atual=a->raiz, *ligacao_do_atual_com_pai;

    for(;;) // forever
    {
        if (atual==NULL) return false;

        int comp=*(a->comparacao)(i,atual->informacao);

        if (comp==0)
        {
            if (atual->esquerda==NULL && atual->direita==NULL)
            {
                free(atual->informacao);
                free(atual);
                if (pai==NULL) // a informacao a ser removida foi encontrada na raiz
                    a->raiz=NULL;
                else
                    *ligacao_do_atual_com_o_pai=NULL;
            }
            else if (atual->esquerda!=NULL && atual->direita==NULL)
            {
                *ligacao_do_atual_com_o_pai=atual->esquerda;
                free(atual->informacao);
                free(atual);
            }
            else if (atual->esquerda==NULL && atual->direita!=NULL)
            {
                *ligacao_do_atual_com_o_pai=atual->direita;
                free(atual->informacao);
                free(atual);
            }
            else
            {
                TreeNode a_excluir=atual;
                free(a_excluir->informacao);
                unsigned long int aleatorio=rand()%2;
                if (aleatorio==0) // vou p a esq, procurar a extrema dir
                {
                    if (atual->esquerda->direita!=NULL)
                    {
                        pai=atual;
                        atual=atual->esquerda;
                        ligacao_do_atual_com_o_pai=&atual->esquerda;
                        while (atual->direita!=NULL)
                        {
                            pai=atual;
                            atual=atual->direita;
                            ligacao_do_atual_com_o_pai=&atual->direita;
                        }
                        a_excluir->informacao=atual->informacao;
                        *ligacao_do_atual_com_o_pai=atual->esquerda;
                        free(atual);
                    }
                } 
                else // (aleatorio==1)  vou p a dir, procurar a extrema esq
                {
                    if (atual->direita->esquerda!=NULL)
                    {
                        pai=atual;
                        atual=atual->direita;
                        ligacao_do_atual_com_o_pai=&atual->esquerda;
                        while (atual->esquerda!=NULL)
                        {
                            pai=atual;
                            atual=atual->esquerda;
                            ligacao_do_atual_com_o_pai=&atual->esquerda;
                        }
                        a_excluir->informacao=atual->informacao;
                        *ligacao_do_atual_com_o_pai=atual->direita;
                        free(atual);
                    }
                }
            }
            return true;
        }

        pai=atual;
        if (comp<0)
        {
            atual=atual->esquerda;
            ligacao_do_atual_com_o_pai=&pai->esquerda;
        }
        else // comp>0
        {
            atual=atual->direita;
            ligacao_do_atual_com_o_pai=&pai->direita;
        }      
    }
} 

#define abs(x) ((x)<0?-(x):(x))

void balanceie_a_BinarySearchTree (BinarySearchTree* a)
{
    TreeNode bkp_raiz=a->raiz;

    a->raiz=bkp_raiz->esquerda;
    unsigned int qtd_esquerda=quantas_info_tem_na_BinarySearchTree(a);

    a->raiz=bkp_raiz->direita;
    unsigned int qtd_direita=quantas_info_tem_na_BinarySearchTree(a);

    unsigned int diferenca  = abs(qtd_esquerda-qtd_direita);
    unsigned int transferir = diferenca/2;

    if (qtd_esquerda>qtd_direita)
        for (int i=0; i<transferir; i++)
        {
            pai=bkp_raiz;
            atual=bkp_raiz->esquerda;
            ligacao_do_atual_com_o_pai=&atual->esquerda;
            while (atual->direita!=NULL)
            {
                pai=atual;
                atual=atual->direita;
                ligacao_do_atual_com_o_pai=&atual->direita;
            }
            elemento substituto=atual->informacao;
            *ligacao_do_atual_com_o_pai=atual->esquerda;
            free(atual);
            a->raiz=bkp_raiz;
            elemento raiz_original=a->raiz->informacao;
            a->raiz->informacao=substituto;
            guarde_na_BinarySearchTree(a,raiz_original->informacao);
       }
    else // qtd_direita>qtd_esquerda
        for (int i=0; i<transferir; i++)
            // faça

    bkp_raiz=a->raiz;

    a->raiz=bkp_raiz->esquerda;
    balanceie_a_BinarySearchTree(a);
    bkp_raiz->esquerda=a->raiz;

    a->raiz=bkp_raiz->direita;
    balanceie_a_BinarySearchTree(a);
    bkp_raiz->direita=a->raiz;

    a->raiz=bkp_raiz;    
}

unsigned int heightBinarySearchTree (BinarySearchTree* t) {
    if (t->root == NULL) return 0;
    
    TreeNode bkp_raiz = t->root;
    t->root = t->root->left;
    unsigned int qtdLeft = 1 + heightBinarySearchTree(t);
    
    t->root = bkp_raiz;
    t->root = t->root->right;
    unsigned int qtdRight = 1 + heightBinarySearchTree(t);
    
    t->root = bkp_raiz;
    return (qtdLeft >= qtdRight) ? qtdLeft : qtdRight;
}

void freeBinarySearchTree (BinarySearchTree* t) {
    if (t->root == NULL) return;
    
    TreeNode left  = t->root->left;
    TreeNode right = t->root->right;
    
    free(t->root->informacao);
    free(t->root);
    
    t->root = left;
    freeBinarySearchTree(t);
    
    t->root = right;
    freeBinarySearchTree(t);
}

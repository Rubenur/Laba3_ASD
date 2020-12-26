#ifndef _TREE_H
#define _TREE_H

template <class NODETYPE> class Tree;
#include <vector>
#include "node.h"

template <class NODETYPE>
class Tree
{
public:
    class iterator_width;
    class iterator_deep;

    Tree();                                                    // constructor 
    void insert(const NODETYPE&);                         // inserts a node 
    void remove(NODETYPE key);     // deletes a node
    void inorder_walk(TreeNode<NODETYPE>*);   /* печатает все ключи в неубывающем порядке */
    void dft_walk(TreeNode<NODETYPE>*);
    void bft_walk(TreeNode<NODETYPE>*, int& level);
    TreeNode<NODETYPE>* find_max(TreeNode<NODETYPE>*);         /* находит узел с минимальным значением ключа и возвращает указатель на него */
    TreeNode<NODETYPE>* find_min(TreeNode<NODETYPE>*);
    bool contains(NODETYPE key);
    TreeNode<NODETYPE>* find_node(TreeNode<NODETYPE>*, const NODETYPE&);
    TreeNode<NODETYPE>* find_succsessor(const NODETYPE&);     /* находит элемент с ключем, следующим за данным числом */
    TreeNode<NODETYPE>* get_root();                            /* возвращает указатель на корень дерева */
    std::vector <TreeNode<NODETYPE>* > dft_vector;
    std::vector < std::vector< TreeNode<NODETYPE>* > > bft_matrix;
    iterator_deep& create_dtf_iterator()
    {
        dft_vector.clear();
        dft_walk(root);
        iterator_deep di(*this);
        return di;
    }
    iterator_width& create_bft_iterator()
    {
        bft_matrix.clear();
        int level = 0;
        bft_walk(root, level);
        iterator_width wi(*this);
        return wi;
    }
private:
    TreeNode<NODETYPE>* root;                                  /* собственно, сам корень */
public:
    class iterator_width
    {
    private:
        TreeNode<NODETYPE>* node;
        int nString;
        int nRow;
        Tree<NODETYPE>& tree;
    public:

        iterator_width(Tree<NODETYPE>& tree_) : nString(1), nRow(0), tree(tree_)
        {
                node = tree.root;
        }
        iterator_width& operator++()
        {
            while (tree.bft_matrix.size() > nString)
            {
                if (tree.bft_matrix[nString].size() > nRow)
                {
                    node = tree.bft_matrix[nString][nRow];
                    nRow++;
                    return *this;
                }
                nRow = 0;
                nString++;
            }
            node = 0;
            return *this;
        }
        TreeNode<NODETYPE>* get()
        {
            return node;
        }
    };
    class iterator_deep
    {
    private:
        TreeNode<NODETYPE>* node;
        int count;
        Tree<NODETYPE>& tree;
    public:

        iterator_deep(Tree<NODETYPE>& tree_) : count(0), tree(tree_)
        {
            if (!tree.dft_vector.empty())
              node = tree.dft_vector[count];
            else
              node = 0;
        }
        TreeNode<NODETYPE>* get()
        {
            return node;
        }
        iterator_deep& operator++()
        {
            if (tree.dft_vector.size()-1 > count)
            {
                node = tree.dft_vector[++count];
            }
            else
            {
                node = 0;
            }
            return *this;
        }
    };
};

template<class NODETYPE>
Tree<NODETYPE>::Tree()
{
    root = 0;                      /* в начале дерево пусто */
}

template<class NODETYPE>
void Tree<NODETYPE>::insert(const NODETYPE& x)
{
    TreeNode<NODETYPE>* n = new TreeNode<NODETYPE>(x);  /* создаем новый узел, его мы будем вставлять */
    TreeNode<NODETYPE>* ptr;
    TreeNode<NODETYPE>* ptr1;

    n->parent = n->left = n->right = 0;          /* он - лист */
    ptr = ptr1 = root;
    while (ptr != 0)                     /* идем от корня и ищем подходящее место для нашего нового элемента, оно должно быть свободно */
    {
        ptr1 = ptr;                 /* будущий родитель нового узла */
        if (x < ptr->get_data())  /* по определению нашего дерева - слева значение ключа меньше родителя, */
            ptr = ptr->left;
        else
            ptr = ptr->right;   /* справа - больше */
    }
    n->parent = ptr1;
    if (ptr1 == 0)                       /* дерево было пусто? */
        root = n;
    else
    {
        if (x < ptr1->get_data())
            ptr1->left = n;
        else
            ptr1->right = n;
    }
}

template<class NODETYPE>
void Tree<NODETYPE>::remove(NODETYPE key)
{
    TreeNode<NODETYPE>* z = find_node(get_root(), key);
    if (!z) return;
    TreeNode<NODETYPE>* y;
    TreeNode<NODETYPE>* x;
    if (z->left == 0 || z->right == 0)               /* в этой и следующих двух строках ищем вершину y, которую мы потом вырежем из дерева. Это либо z, либо следующий за z */
        y = z;
    else
        y = find_succsessor(z->get_data());
    if (y->left != 0)                                  /* x - указатель на существующего ребенка y или 0 если таковых нет */
        x = y->left;
    else
        x = y->right;
    if (x != 0)                                        /* эта и следующие 9 строк - вырезание y */
        x->parent = y->parent;
    if (y->parent == 0)
        root = x;
    else
    {
        if (y == (y->parent)->left)
            (y->parent)->left = x;
        else
            (y->parent)->right = x;
    }
    if (y != z)                                        /* если мы вырезали вершин, отличную от z, то ее данные перемещаем в z */
        z->data = y->get_data();
}

template<class NODETYPE>
TreeNode<NODETYPE>* Tree<NODETYPE>::find_max(TreeNode<NODETYPE>* x)
{
    while (x->right != 0)                              // здесь все очевидно - самыое максимальное значение у самого правого 
        x = x->right;
    return x;
}

template<class NODETYPE>
TreeNode<NODETYPE>* Tree<NODETYPE>::find_min(TreeNode<NODETYPE>* x)
{
    while (x->left != 0)
        x = x->left;
    return x;
}

template<class NODETYPE>
TreeNode<NODETYPE>* Tree<NODETYPE>::find_succsessor(const NODETYPE& val)
{
    TreeNode<NODETYPE>* x = find_node(root, val);                     /* получим указатель на ноду с ключем val */
    TreeNode<NODETYPE>* y;
    if (x == 0)
        return 0;
    if (x->right != 0)                                                /* если у нее есть правые дети, то следующий элемент - минимальный в правом поддереве */
        return find_min(x->right);
    y = x->parent;
    while (y != 0 && x == y->right)                                   /* иначе - идем вверх и ищем первый элемент, являющийся левым
потомком своего родителя */
    {
        x = y;
        y = y->parent;
    }
    return y;
}

template<class NODETYPE>
bool Tree<NODETYPE>::contains(NODETYPE key)
{
    TreeNode<NODETYPE>* foundNode = find_node(get_root(), key);
    if (!foundNode)
    {
        return false;
    }
    else
    {
        return true;
    }
}

template<class NODETYPE>
TreeNode<NODETYPE>* Tree<NODETYPE>::find_node(TreeNode<NODETYPE>* n, const NODETYPE& val)
{
    if (n == 0 || val == n->get_data())
        return n;
    if (val > n->get_data())
        return find_node(n->right, val);
    else
        return find_node(n->left, val);
}

template<class NODETYPE>
void Tree<NODETYPE>::bft_walk(TreeNode<NODETYPE>* n, int &level)
{
    if (n != 0)
    {
        std::vector< TreeNode<NODETYPE>* > temp;
        bft_matrix.push_back(temp);
        bft_matrix[level].push_back(n);
        if (n->left)
        {
            level++;
        }
        bft_walk(n->left, level);
        if (n->right)
        {
            level++;
        }
        bft_walk(n->right, level);
        level--;
    }
}

template<class NODETYPE>
void Tree<NODETYPE>::dft_walk(TreeNode<NODETYPE>* n)
{
    if (n != 0)
    {
        dft_vector.push_back(n);
        dft_walk(n->left);
        dft_walk(n->right);
    }
}

template<class NODETYPE>
void Tree<NODETYPE>::inorder_walk(TreeNode<NODETYPE>* n)
{
    if (n != 0)
    {
        inorder_walk(n->left);
        std::cout << n->get_data() << std::endl;
        inorder_walk(n->right);
    }
}

template<class NODETYPE>
TreeNode<NODETYPE>* Tree<NODETYPE>::get_root()
{
    return root;
}

#endif
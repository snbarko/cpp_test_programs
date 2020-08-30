#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

class Node
{
public:
    Node(int _data):mData(_data), mLeft(NULL), mRight(NULL)
    {
        cout << "Creating node: " << mData << endl;
    }
    int getData() { return mData; }
    Node* getLeft() { return mLeft; }
    Node* getRight() { return mRight; }
    void setLeft(Node* node) { mLeft = node; }
    void setRight(Node* node) { mRight = node; }
private:
    int mData;
    Node* mLeft;
    Node* mRight;
};

class Tree
{
public:
    Tree():mRoot(NULL) {}
    virtual ~Tree()
    {
        cout << "Need to remove all elements in tree and free up." << endl;
    }
    virtual void insert(Node* node) = 0;
    virtual bool remove(int elem) = 0;
    virtual bool search(int elem) = 0;
    virtual void display() = 0;

protected:
    Node* mRoot;
};

class BST : public Tree
{
public:
    BST() = default;
    ~BST() = default;
    void insert(Node* node);
    bool remove(int elem);
    bool search(int elem);
    void display();
private:
    bool removeNode(Node* node, int num);
    bool searchNode(Node* node, int num);
    void printNode(Node* node, int num = 0);
};

void BST::insert(Node* node)
{
    if (mRoot == NULL)
    {
        mRoot = node;
        return;
    }
    Node* temp = mRoot;
    Node* prev;
    while(temp)
    {
        prev = temp;
        if (node->getData() < temp->getData())
        {
            temp = temp->getLeft();
        }
        else
        {
            temp = temp->getRight();
        }
    }

    if (node->getData() < prev->getData())
    {
        prev->setLeft(node);
    }
    else
    {
        prev->setRight(node);
    }
}

bool BST::removeNode(Node* node, int num)
{
    if (node->getData() == num)
    {
        return true;
    }
    if ((node->getLeft() != NULL) && removeNode(node->getLeft(), num))
    {
        cout << "Parent node " << node->getData() << endl;
        if (!node->getLeft()->getLeft() && !node->getLeft()->getRight())
        {
            cout << "No children of node " << node->getLeft()->getData() << endl;
            delete(node->getLeft());
            node->setLeft(NULL);
        }
        return true;
    }
    if ((node->getRight() != NULL) && removeNode(node->getRight(), num))
    {
        cout << "Parent node " << node->getData() << endl;
        if (!node->getRight()->getLeft() && !node->getRight()->getRight())
        {
            cout << "No children of node " << node->getRight()->getData() << endl;
            delete(node->getLeft());
            node->setLeft(NULL);
        }
        return true;
    }
    return false;
}

bool BST::remove(int elem)
{
    Node* node = mRoot;
    Node* parent = NULL;
    while (1)
    {
        if (node->getData() == elem)
        {
            if (!node->getLeft() && !node->getRight())
            {
                delete(node);
                if (parent)
                {
                    parent->setLeft(NULL);
                    parent->setRight(NULL);
                }
                else
                {
                    mRoot = NULL;
                }
            }
            else if (!node->getLeft() && node->getRight())
            {
                if (parent)
                    parent->setRight(node->getRight());
                else
                    mRoot = node->getRight();
                delete node;
            }
            else if (node->getLeft() && !node->getRight())
            {
                if (parent)
                    parent->setLeft(node->getLeft());
                else
                    mRoot = node->getLeft();
                delete node;
            }
            else
            {
                Node* localparent = NULL;
                Node* temp;
                if (node->getLeft())
                {
                    temp = node->getLeft();
                    while (temp->getRight())
                    {
                        localparent = temp;
                        temp = temp->getRight();
                    }
                    if (localparent)
                        localparent->setRight(NULL);
                    else
                    {
                        node->setLeft(NULL);
                    }
                }
                else if (node->getRight())
                {
                    temp = node->getRight();
                    while (temp->getLeft())
                    {
                        localparent = temp;
                        temp = temp->getLeft();
                    }
                    if (localparent)
                    {
                        localparent->setLeft(NULL);
                    }
                    else
                    {
                        node->setRight(NULL);
                    }
                }
                
                if(parent)
                {
                    if (parent->getLeft() && (parent->getLeft()->getData() == node->getData()))
                    {
                        parent->setLeft(temp);
                    }
                    else
                    {
                        parent->setRight(temp);
                    }
                }
                else
                {
                    mRoot = temp;
                }
                if (node->getRight())
                    temp->setRight(node->getRight());
                if (node->getLeft())
                    temp->setLeft(node->getLeft());
                delete node;
            }
            return true;
        }
        if (elem < node->getData())
        {
             if (!node->getLeft())
             {
                 return false;
             }
            parent = node;
            node = node->getLeft();
        }
        else
        {
             if (!node->getRight())
             {
                 return false;
             }
            parent = node;
            node = node->getRight();
        }
    }
}

bool BST::searchNode(Node* node, int num)
{
    if (node->getData() == num)
    {
        return true;
    }
    if (node->getLeft() != NULL)
    {
        if (searchNode(node->getLeft(), num))
        {
            return true;
        }
    }
    if (node->getRight() != NULL)
    {
        if (searchNode(node->getRight(), num))
        {
            return true;
        }
    }
    return false;
}

bool BST::search(int elem)
{
    return searchNode(mRoot, elem);
}

void BST::printNode(Node* node, int num)
{
    cout << node->getData() << endl;
    if (node->getLeft() != NULL)
    {
        int tmp = 0;
        while(tmp++ < num)
        {
            cout << " ";
        }
        cout << "L ";
        printNode(node->getLeft(), num + 1);
    }
    if (node->getRight() != NULL)
    {
        int tmp = 0;
        while(tmp++ < num)
        {
            cout << " ";
        }
        cout << "R ";
        printNode(node->getRight(), num + 1);
    }
}

void BST::display()
{
    cout << "Binary Search Tree:" << endl;
    Node* node = mRoot;
    if (!node)
    {
        return;
    }
    printNode(node);
}

int main()
{
    Tree* bst = new BST();
    while (1)
    {
        cout << "1. Insert ";
        cout << "2. Remove ";
        cout << "3. Search ";
        cout << "4. Display ";
        cout << "5. Exit ";
        cout << "Enter option: ";
        int op = 0;
        cin >> op;
        int elem = 0;
        bool ret = false;
        Node* node = NULL;
        switch(op)
        {
        case 1:
            cout << "Enter element ";
            cin >> elem;
            node = new Node(elem);
            if (node == NULL)
            {
                cout << "Memory allocation failed" << endl;
                break;
            }
            bst->insert(node);
            bst->display();
            break;
        case 2:
            cout << "Enter element ";
            cin >> elem;
            ret = bst->remove(elem);
            cout << "Tree removal status: " << (ret ? "success" : "failed") << endl;
            bst->display();
            break;
        case 3:
            cout << "Enter element ";
            cin >> elem;
            ret = bst->search(elem);
            cout << "Tree search status: " << ret << endl;
            break;
        case 4:
            bst->display();
            break;
        case 5:
            delete bst;
            exit(0);
            break;
        default:
            cout << "Wrong option provided" << endl;
        }
    }
    delete bst;
    return 0;
}

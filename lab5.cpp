#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

const int right_overweight = 2;
const int left_overweight = -2;
const int indent = 0;

typedef struct Node {
    int key;
    unsigned char height;
    Node* left;
    Node* right;

    Node(int k) {
        key = k;
        left = right = 0;
        height = 1;
    }
}node;

unsigned char height(Node* p) {
    return p ? p->height : 0;
}

int bFactor(Node* p) {
    return height(p->right) - height(p->left);
}

void fixHeight(Node* p) {
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

Node* rotateRight(Node* p) {
    Node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixHeight(p);
    fixHeight(q);
    return q;
}

Node* rotateLeft(Node* q) {
    Node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixHeight(q);
    fixHeight(p);
    return p;
}

Node* balance(Node* p) {
    fixHeight(p);
    if (bFactor(p) == right_overweight) {
        if (bFactor(p->right) < 0)
            p->right = rotateRight(p->right);
        return rotateLeft(p);
    }
    if (bFactor(p) == left_overweight) {
        if (bFactor(p->left) > 0)
            p->left = rotateLeft(p->left);
        return rotateRight(p);
    }
    return p; // балансировка не нужна
}

Node* insert(Node* p, int k) {
    if (!p) return new Node(k);
    if (k < p->key)
        p->left = insert(p->left, k);
    else
        p->right = insert(p->right, k);
    return balance(p);
}

void printAVLTree(Node* p, int maxHeight) {

    for (int i = 0; i < maxHeight; ++i) {
        std::cout << ' ';
    }
    std::cout << p->key;
    std::cout << "\n";
    if (p->right) {
        printAVLTree(p->right, maxHeight + 1);
    }
    if (p->left) {
        printAVLTree(p->left, maxHeight + 1);
    }

}

void deleteTree(Node* p) {
    if (p->left) {
        deleteTree(p->left);
    }
    if (p->right) {
        deleteTree(p->right);
    }
    delete p;
}

bool checkExpression(std::string& name, int& my_length) {
    int length = name.length();
    for (int j = 0; j < length; ++j) {
        if (!isdigit(name[j]) && name[j] != ',') {
            return false;
        }
        if (name[j] == ',') {
            name[j] = ' ';
            (my_length)++;
        }
    }

    return true;
}


node* mainCheck(std::string& name) {

    int my_lenght = 0;
    if (checkExpression(name, my_lenght)) {
        std::istringstream iss;
        std::string strvalues = name;
        iss.str(strvalues);
        int now;
        iss >> now;
        node* myTree = new Node(now);
        for (int i = 0; i < my_lenght; i++) {
            int val;
            iss >> val;
            myTree = insert(myTree, val);
        }
        printAVLTree(myTree, indent);
        std::cout << '\n';
        myTree = balance(myTree);
        return myTree;
    }
    else {
        std::cout << "Unwanted characters\n";
    }
}

int isIn(node* p, int k) {
    int result = 0;
    if (p->key == k) return 1;
    else if (p->left) result += isIn(p->left, k);
    else if (p->right) result += isIn(p->right, k);
    return result;
}

void chek_and_add(node* p) {
    std::cout << "Enter elem: ";
    int elem;
    std::cin >> elem;
    if (isIn(p, elem)) {
        std::cout << "This elem already in!";
    }
    else {
        insert(p, elem);
        std::cout << "Result is: \n";
        printAVLTree(p, 0);
    }
};

int main() {

    int your_choose = 0;
    node* myTree;
    std::cout << "Enter data \n";
    std::string str;
    std::cin >> str;
    myTree = mainCheck(str);
    bool flag = true;
    while (flag) {
        chek_and_add(myTree);
        std::cout << "Do you want to repeat? (1 - yes, another - no)";
        int choose;
        std::cin >> choose;
        if (choose != 1) flag = false;
    }
    deleteTree(myTree);
    return 0;
       
}

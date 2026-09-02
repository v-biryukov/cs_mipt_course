#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct node {
    int value;
    int height;
    struct node* left;
    struct node* right;
};
typedef struct node Node;


void print_tree(Node* root) {
    if (root == NULL)
        return;

    print_tree(root->left);
    printf("%d ", root->value);
    print_tree(root->right);
}

int tree_height(Node* root) {
    if (root == NULL)
        return 0;
    else
        return root->height;
}


int tree_compute_height(Node* root) {
    if(root == NULL)
        return 0;

    // ! Преполагаем, что высота потомков верна
    // Обратите внимание, что это не реккурсивная функция
    // Если бы мы вычисляли hleft и hright с помощью tree_compute_height,
    //      то дерево бы работало намного медленней
    int hleft = tree_height(root->left);
    int hright = tree_height(root->right);
    return 1 + (hleft > hright ? hleft : hright);
}

int tree_fix_height(Node* root) {
    if (root)
        root->height = tree_compute_height(root);
}


int tree_size(Node* root) {
    if (root == NULL)
        return 0;
    
    int sleft = tree_size(root->left);
    int sright = tree_size(root->right);
    return 1 + sleft + sright;
}


void tree_rotate(Node** proot, int direction) {
    Node* x;
    Node* y;
    Node* B;

    if (direction == 0) 
    {
        // LR - левое вращение
        /*   
         *       x               y     
         *      / \             / \     
         *     A   y    =>     x   C    
         *        / \         / \       
         *       B   C       A   B      
         */

        x = *proot;
        y = x->right;
        B = y->left;
    
        *proot = y;
        y->left = x;
        x->right = B;

        tree_fix_height(x);
        tree_fix_height(y);
    }
    else {
        // RR - правое вращение
        /*   
         *        y            x 
         *       / \          / \
         *      x   C   =>   A   y
         *     / \              / \
         *    A   B            B   C
         */  
    
        y = *proot;
        x = y->left;
        B = x->right;
    
        *proot = x;
        x->right = y;
        y->left = B;

        tree_fix_height(y);
        tree_fix_height(x);
    }

}


void tree_rebalance(Node** proot) {
    if (*proot)
    {
        // Если правое поддерево сильно больше по высоте
        if (tree_height((*proot)->right) > tree_height((*proot)->left) + 1) {

            // Если высота (*proot)->right->left > высоты (*proot)->right->right
            // Это Зиг-Заг случай (или двойное вращение, или большое вращение - по разному называется)
            // В этом случае нужно провести дополнительное правое вращение вокруг z
                /*         
                 *       x                 x                      y                  
                 *      / \               / \                    / \                  
                 *     A   z     RR(z)   A   y       LR(x)      x   z                 
                 *        / \     =>        / \       =>       / \  /\                        
                 *       y   D             B   z              A  B C  D                          
                 *      / \                   / \                                        
                 *     B   C                 C   D                                         
                 */

            if (tree_height((*proot)->right->left) > tree_height((*proot)->right->right))
                tree_rotate(&(*proot)->right, 1); // RR(z)
                
            tree_rotate(proot, 0); // LR(x)
        }
        

        // Если левое поддерево сильно больше по высоте
        // В этом случае всё зеркально симметрично
        if (tree_height((*proot)->left) > tree_height((*proot)->right) + 1) {
            if (tree_height((*proot)->left->right) > tree_height((*proot)->left->left))
                tree_rotate(&(*proot)->left, 0); // LR(z)
                
            tree_rotate(proot, 1); // RR(x)
        }
    }
}


void tree_insert(Node** proot, int val) {
    if (*proot == NULL) {
        Node* temp;
        temp = (Node*)malloc(sizeof(Node));
        temp->value = val;
        // temp->height = 1; // tree_fix_height всё равно установит это поле равным 1
        temp->left = NULL;
        temp->right = NULL;
        *proot = temp;
    }
    else if  ((*proot)->value == val) {
        return;
    }
    else {
        if (val > (*proot)->value)
            tree_insert(&(*proot)->right, val);
        else
            tree_insert(&(*proot)->left, val);
    }

    // Дополнение по сравнению с BST
    // Обратите внимание, что эти 2 функции вызываются для каждого
    //       реккурсивного вызова tree_insert
    // Таким образом tree_rebalance может быть вызван несколько раз для вставки одного элемента
    tree_fix_height(*proot);
    tree_rebalance(proot);
}


void tree_destroy(Node* root) {
    if (root) {
        tree_destroy(root->left);
        tree_destroy(root->right);
        free(root);
    }
}

int main() {
    printf("AVL(self balancing) binary search tree:\n");
    printf("Random numbers:\n");
    srand(time(0));
    Node* root = 0;

    for (int i = 0; i < 1e6; ++i)
        tree_insert(&root, rand() % (int)1e9);    

    // print_tree(root);
    // printf("\n");

    int size = tree_size(root);
    printf("\tSize = %d\n", size);
    printf("\tOptimal height = %d\n", (int)(log(size)/log(2)) + 1);
    printf("\tHeight = %d\n", tree_height(root));
    tree_destroy(root);

    // |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

    printf("Consecutive numbers:\n");
    root = 0;

    for (int i = 0; i < 1e6; ++i)
        tree_insert(&root, i);  

    // print_tree(root);
    // printf("\n");


    size = tree_size(root);
    printf("\tSize = %d\n", size);
    printf("\tOptimal height = %d\n", (int)(log(size)/log(2)) + 1);
    printf("\tHeight = %d\n", tree_height(root));
    tree_destroy(root);
}



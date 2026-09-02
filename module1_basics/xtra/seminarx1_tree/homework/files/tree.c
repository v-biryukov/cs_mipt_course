#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "tree.h"
#include "prettyprint.h"
#include "queue.h"

// Функция bst_insert вставляет элемент в бинарное дерево поиска
// и возвращает указатель на корень этого дерева
// (если дерево было пустым, то root изменится)
// Чтобы использовать: root = bst_insert_return(root, 100)
Node* bst_insert(Node* root, int x) {
    if (root == NULL) {
        root = (Node*)malloc(sizeof(Node));
        root->value = x;
        root->left = NULL;
        root->right = NULL;
    }
    else if (x < root->value) {
        root->left = bst_insert(root->left, x);
    }
    else if (x > root->value) {
        root->right = bst_insert(root->right, x);
    }
    return root;
}

void bst_destroy(Node* root){
    if (root != NULL) {
        bst_destroy(root->left);
        bst_destroy(root->right);
        free(root);
    }
}

Node* create_test_tree() {
    Node* test = NULL;
    test = bst_insert(test, 20);
    test = bst_insert(test, 15);
    test = bst_insert(test, 60);
    test = bst_insert(test, 5);
    test = bst_insert(test, 10);
    test = bst_insert(test, 40);
    test = bst_insert(test, 80);
    test = bst_insert(test, 25);
    test = bst_insert(test, 50);
    test = bst_insert(test, 90);
    return test;
}

Node* create_random_tree(int num_of_elements, int max_element) {
    Node* test = NULL;
    for (int i = 0; i < num_of_elements; i++)
        test = bst_insert(test, (rand() * RAND_MAX + rand()) % max_element);
    return test;
}


int bst_size(const Node* root) {
    if (root == NULL)
        return 0;
    else
        return 1 + bst_size(root->left) + bst_size(root->right);
}

int max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

int bst_height(const Node* root) {
    if (root == NULL)
        return 0;
    else
        return 1 + max(bst_height(root->left), bst_height(root->right));
}

void bst_print_dfs(const Node* root) {
    if (root == NULL)
        return;

    bst_print_dfs(root->left);
    printf("%d ", root->value);
    bst_print_dfs(root->right);
}

Node* bst_search(Node* root, int val) {
    if (root == NULL || val == root->value)
        return root;

    if (val < root->value)
        return bst_search(root->left, val);

    return bst_search(root->right, val);
}


Node* bst_get_min(Node* root) {
    if (root == NULL)
        return NULL;

    Node* ptr = root;
    while (ptr->left)
        ptr = ptr->left;
    return ptr;
}


Node* bst_remove(Node* root, int val)
{
    if (root == NULL)
        return root;

    if (val < root->value) {
        root->left = bst_remove(root->left, val);
    }
    else if (val > root->value) {
        root->right = bst_remove(root->right, val);
    }
    else if (!root->left && !root->right) {
        free(root);
        root = NULL;
    }
    else if (root->left && !root->right) {
        Node* temp = root->left;
        free(root);
        root = temp;
    }
    else if (!root->left && root->right) {
        Node* temp = root->right;
        free(root);
        root = temp;
    }
    else {
        Node* pmin = bst_get_min(root->right);
        root->value = pmin->value;
        root->right = bst_remove(root->right, pmin->value);
    }

    return root;
}


void bst_print_bfs(Node* root) {
    // Создаём очередь q, которая будет хранить элементы типа Node* 
    // и ложим в неё указатель root
    Queue q;
    queue_init(&q);
    enqueue(&q, root);

    // Пока очередь не пуста
    while (!queue_is_empty(&q)) {
        // Находим размер очереди
        int size = queue_size(&q);
        // Вытаскиваем size элементов, печатаем и ложим в очередь их детей
        for (int i = 0; i < size; ++i) {
            Node* ptr = dequeue(&q);
            printf("%d ", ptr->value);
            if (ptr->left)
                enqueue(&q, ptr->left);
            if (ptr->right)
                enqueue(&q, ptr->right);
        }
    }
    queue_destroy(&q);
}


Node* create_tree_with_consecutive_numbers(int num_of_elements) {
    Node* root = NULL;
    for (int i = 0; i < num_of_elements; i++)
        root = bst_insert(root, i);
    return root;
}


int main() {
    srand(time(0));

    Node* root = create_test_tree();
    //Node* root = create_random_tree(26);
    bst_insert(root, 70);
    print_ascii_tree(root);
    printf("\n");

    printf("Size = %d\n", bst_size(root));
    printf("Height = %d\n", bst_height(root));
    printf("Minimum = %d\n", bst_get_min(root)->value);


    printf("Removing 60:\n\n");
    bst_remove(root, 60);
    print_ascii_tree(root);

    printf("\nRemoving 20:\n\n");
    bst_remove(root, 20);
    print_ascii_tree(root);

    printf("Breadth first search Print:\n");
    bst_print_bfs(root);
    printf("OK\n");
    
    bst_destroy(root);

    int n = 20000;
    printf("\nRandom tree:\n");
    Node* tree_random = create_random_tree(n, 10 * n);
    printf("Size = %d\n", bst_size(tree_random));
    printf("Height = %d\n", bst_height(tree_random));
    bst_destroy(tree_random);

    printf("\nConsecutive tree:\n");
    Node* tree_consecutive = create_tree_with_consecutive_numbers(n);
    printf("Size = %d\n", bst_size(tree_consecutive));
    printf("Height = %d\n", bst_height(tree_consecutive));
    bst_destroy(tree_consecutive);


    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// Бинарное дерево поиска
// Binary search tree (BST)
struct node
{
	int value;
	struct node* left;
	struct node* right;
};
typedef struct node Node;

#include "prettyprint.h"



// Функция bst_insert вставляет элемент в бинарное дерево поиска
// и возвращает указатель на корень этого дерева
// (если дерево было пустым, то root изменится)
// Чтобы использовать: root = bst_insert_return(root, 100)
Node* bst_insert(Node* root, int x)
{
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

void bst_destroy(Node* root)
{
	if (root != NULL) {
		bst_destroy(root->left);
		bst_destroy(root->right);
		free(root);
	}
}

Node* create_test_tree()
{
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

Node* create_random_tree(int num_of_elements)
{
	Node* test = NULL;
	for (int i = 0; i < num_of_elements; i++) {
		test = bst_insert(test, rand() % 1000);
	}
	return test;
}



int main()
{
	srand(time(0));

	Node* root = create_test_tree();
	//Node* root = create_random_tree(100);
	bst_insert(root, 70);
	print_ascii_tree(root);

	printf("OK\n");
	return 0;
}
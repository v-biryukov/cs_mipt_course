#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// AVL - дерево
// Самобалансирующееся бинарное дерево поиска


struct node {
	int val;
	struct node* left;
	struct node* right;
	int height;
};
typedef struct node Node;

#include "prettyprint.h"

int min(int x, int y) {
	return (x < y) ? x : y;
}

int max(int x, int y) {
	return (x > y) ? x : y;
}

Node* bst_insert(Node* root, int x) {
	if (root == NULL) {
		root = (Node*)malloc(sizeof(Node));
		root->val = x;
		root->left = NULL;
		root->right = NULL;
	}
	else if (x < root->val) {
		root->left = bst_insert(root->left, x);
	}
	else if (x > root->val) {
		root->right = bst_insert(root->right, x);
	}
	return root;
}

void bst_destroy(Node* root) {
	if (root == NULL)
		return;
	bst_destroy(root->left);
	bst_destroy(root->right);
	free(root);
}




Node* create_test_tree() {
	Node* test = NULL;
	test = bst_insert(test, 9);
	test = bst_insert(test, 5);
	test = bst_insert(test, 41);
	test = bst_insert(test, 1);
	test = bst_insert(test, 2);
	test = bst_insert(test, 6);
	test = bst_insert(test, 37);
	test = bst_insert(test, 54);
	test = bst_insert(test, 97);
	test = bst_insert(test, 22);
	test = bst_insert(test, 16);
	test = bst_insert(test, 31);
	test = bst_insert(test, 14);
	test = bst_insert(test, 17);
	test = bst_insert(test, 10);
	test = bst_insert(test, 15);
	return test;
}

Node* create_random_tree(int num_of_elements) {
	Node* test = NULL;
	for (int i = 0; i < num_of_elements; i++)
		test = bst_insert(test, rand() % 1000);
	return test;
}



int main() {
	srand(time(0));

	Node* t = create_test_tree();
	print_ascii_tree(t);
	bst_destroy(t);
	
	return 0;
}
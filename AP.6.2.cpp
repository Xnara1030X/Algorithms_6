
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

#define INF 1000000

typedef vector<int> matrix_1d;
typedef vector<vector<int>> matrix_2d;

typedef struct node* treePointer;
typedef struct node {
	int key;
	treePointer leftChild, rightChild;
} node;
treePointer tree_root;

int g_minavg, g_count, g_num;

void optsearchtree(int n, matrix_1d& p, matrix_2d& A, matrix_2d& R);
int minimum(int i, int j, int& min_k, matrix_1d& p, matrix_2d& A);
void printmatrix_2d(matrix_2d matrix);

treePointer optimalBST(int i, int j, matrix_1d& keys, matrix_2d& R);
treePointer makeTree(int key);
void preorder(treePointer ptr);
void inorder(treePointer ptr);

int main() {
	cin >> g_num;

	matrix_1d key(g_num + 1, 0);
	matrix_1d probability(g_num + 1, 0);
	matrix_2d dp(g_num + 2, matrix_1d(g_num + 2, 0));
	matrix_2d root(g_num + 2, matrix_1d(g_num + 2, 0));

	for (int i = 1; i <= g_num; i++) {
		cin >> key[i];
	}

	for (int i = 1; i <= g_num; i++) {
		cin >> probability[i];
	}

	optsearchtree(g_num, probability, dp, root);

	printmatrix_2d(dp);
	printmatrix_2d(root);
	cout << g_minavg << endl;

	tree_root = optimalBST(1, g_num, key, root);

	g_count = 1;
	preorder(tree_root);
	cout << endl;
	g_count = 1;
	inorder(tree_root);

	return 0;
}

void optsearchtree(int n, matrix_1d& p, matrix_2d& A, matrix_2d& R) {
	for (int i = 1; i <= n; i++) {
		A[i][i - 1] = 0;
		A[i][i] = p[i];
		R[i][i - 1] = 0;
		R[i][i] = i;
	}

	for (int diagonal = 1; diagonal <= n - 1; diagonal++) {
		for (int i = 1; i <= n - diagonal; i++) {
			int j = i + diagonal;
			int k;
			A[i][j] = minimum(i, j, k, p, A);
			R[i][j] = k;
		}
	}

	g_minavg = A[1][n];
}

int minimum(int i, int j, int& min_k, matrix_1d& p, matrix_2d& A) {
	if (i < j) {
		int minValue = INF;
		int value;

		for (int k = i; k <= j; k++) {
			value = A[i][k - 1] + A[k + 1][j];
			if (minValue > value) {
				minValue = value;
				min_k = k;
			}
		}

		for (int m = i; m <= j; m++) {
			minValue += p[m];
		}

		return minValue;
	}
	else if (i == j) {
		return p[i];
	}
	else {
		return 0;
	}
}

void printmatrix_2d(matrix_2d matrix) {
	for (int i = 1; i < matrix.size(); i++) {
		for (int j = i - 1; j < matrix[i].size() - 1; j++) {
			if (j != matrix[i].size() - 2) {
				cout << matrix[i][j] << " ";
			}
			else {
				cout << matrix[i][j];
			}
		}
		cout << endl;
	}
}

treePointer optimalBST(int i, int j, matrix_1d& keys, matrix_2d& R) {
	int k = R[i][j];

	if (k == 0) {
		return NULL;
	}
	else {
		treePointer newNode = makeTree(keys[k]);
		newNode->leftChild = optimalBST(i, k - 1, keys, R);
		newNode->rightChild = optimalBST(k + 1, j, keys, R);
		
		return newNode;
	}
}

treePointer makeTree(int key) {
	treePointer newNode = new node;
	newNode->key = key;
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;

	return newNode;
}

void preorder(treePointer ptr) {
	if (ptr) {
		cout << ptr->key;
		if (g_num != g_count) {
			cout << " ";
		}
		g_count++;

		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
}

void inorder(treePointer ptr) {
	if (ptr) {
		inorder(ptr->leftChild);

		cout << ptr->key;
		if (g_num != g_count) {
			cout << " ";
		}
		g_count++;

		inorder(ptr->rightChild);
	}
}

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

typedef vector<vector<int>> matrix;

#define INF 1000000

void minmult(int n, vector<int>& d, matrix& M, matrix& P);
int minimum(int i, int j, int& mink, vector<int>& d, matrix& M);
void printMatrix(matrix M);
void order(int i, int j, matrix& P, string& s);

int main() {
	int n;
	cin >> n;

	vector<int> d(n + 1);

	for (int i = 0; i <= n; i++) {
		cin >> d[i];
	}

	matrix M(n + 1, vector<int>(n + 1, 0));
	matrix P(n + 1, vector<int>(n + 1, 0));

	minmult(n, d, M, P);
	printMatrix(M);
	printMatrix(P);
	cout << M[1][n] << endl;

	string s;
	order(1, n, P, s);
	cout << s;

	return 0;
}

void minmult(int n, vector<int>& d, matrix& M, matrix& P) {
	for (int i = 1; i <= n; i++) {
		M[i][i] = 0;
	}

	for (int diagonal = 1; diagonal <= n - 1; diagonal++) {
		for (int i = 1; i <= n - diagonal; i++) {
			int j = i + diagonal;
			int k;

			M[i][j] = minimum(i, j, k, d, M);
			P[i][j] = k;
		}
	}
}

int minimum(int i, int j, int& mink, vector<int>& d, matrix& M) {
	int minValue = INF;
	int value;

	for (int k = i; k <= j - 1; k++) {
		value = M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j];

		if (minValue > value) {
			minValue = value;
			mink = k;
		}
	}

	return minValue;
}

void printMatrix(matrix M) {
	for (int i = 1; i < M.size(); i++) {
		for (int j = i; j < M[i].size(); j++) {
			if (j != M[i].size() - 1) {
				cout << M[i][j] << " ";
			}
			else {
				cout << M[i][j];
			}
		}
		cout << endl;
	}
}

void order(int i, int j, matrix& P, string& s) {
	if (i == j) {
		s += string("(");
		s += string("A") + to_string(i);
		s += string(")");
	}
	else {
		int k = P[i][j];
		s += string("(");
		order(i, k, P, s);
		order(k + 1, j, P, s);
		s += string(")");
	}
}

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

typedef vector<vector<int>> matrix_2d;

string result;
int g_m, g_n;

void lcs(string X, string Y, matrix_2d& count, matrix_2d& path);
void get_lcs(string& result, int i, int j, matrix_2d path, string X);

int main() {
	string X, Y;
	cin >> X >> Y;

	X = " " + X;
	Y = " " + Y;

	g_m = X.length();
	g_n = Y.length();

	matrix_2d count(g_m, vector<int>(g_n, 0));
	matrix_2d path(g_m, vector<int>(g_n, 0));

	lcs(X, Y, count, path);
	cout << count[g_m - 1][g_n - 1] << endl;
	if (count[g_m - 1][g_n - 1] != 0) {
		get_lcs(result, g_m - 1, g_n - 1, path, X);
		cout << result;
	}

	return 0;
}

void lcs(string X, string Y, matrix_2d& count, matrix_2d& path) {
	for (int i = 1; i < g_m; i++) {
		for (int j = 1; j < g_n; j++) {
			if (X[i] == Y[j]) {
				count[i][j] = count[i - 1][j - 1] + 1;
				path[i][j] = 1;
			}
			else {
				count[i][j] = max(count[i - 1][j], count[i][j - 1]);
				
				if (count[i - 1][j] < count[i][j - 1]) {
					path[i][j] = 2;
				}
				else {
					path[i][j] = 3;
				}
			}
		}
	}	
}

void get_lcs(string& result, int i, int j, matrix_2d path, string X) {
	if (i == 0 || j == 0) {
		return;
	}
	else {
		if (path[i][j] == 1) {
			get_lcs(result, i - 1, j - 1, path, X);
			result += X[i];
		}
		else if (path[i][j] == 2) {
			get_lcs(result, i, j - 1, path, X);
		}
		else {
			get_lcs(result, i - 1, j, path, X);
		}
	}
}
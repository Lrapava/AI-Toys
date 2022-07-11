#include <bits/stdc++.h>
using namespace std;

inline set <int> intersect(set <int> a, set <int> b) {
	set <int> res;
	for (auto x : a) if (b.find(x) != b.end()) res.insert(x);
	return res;
}

inline set <int> intersect(set <int> a, set <int> b, set <int> c) { 
	return intersect(a, intersect(b, c)); 
}

inline vector <int> options(set <int> can[3][9], int i) {
	vector <int> res;
	set <int> st = intersect(can[0][i/9], can[1][i%9], can[2][i/27*3+i%9/3]);
	for (int x : st) res.push_back(x);
	return res;
}

string visualize(vector <int> mx) {
	string res = "";
	for (int i = 0; i < 81; i++) {
		if (mx[i] > 0) res += to_string(mx[i]); else res += '.';
		if (i % 9 == 8) res += "\n";
	}
	return res;
}

int main() {

	cout << "Enter your sudoku:\n";
	vector <int> mx(81, -1);
	int known = 0;

	// input
	{
		for (int i = 0; i < 81; i++) {
			char c; cin >> c;
			if (c > '0' && c <= '9') mx[i] = c-'0', known++;
			else mx[i] = -1;
		}
	}

	// Processing restrictions
	// 0 - row, 1 - columns, 2 - boxes
	set <int> can[3][9];
	{
		for (int i = 0; i < 3*9*9; i++) 
			can[i%3][i/3%9].insert(i/27+1);

		for (int i = 0; i < 81; i++)
			if (mx[i] != -1) 
				can[0][i/9].erase(mx[i]), 
				can[1][i%9].erase(mx[i]), 
				can[2][i/27*3+i%9/3].erase(mx[i]);
	}

	
	vector <int> state(81, -1), cell(81, -1);
	int point = 0;

	// while not all cells are filled
	while (known < 81) {

		// if we are trying to fill a new cell
		if (cell[point] == -1) {

			// Find available cell with minimal entropy
			int entropy[81], mEnt = 0; 
			for (int i = 0; i < 81; i++) {
				if (mx[i] == -1) entropy[i] = options(can, i).size(); else entropy[i] = 999;
				if (entropy[mEnt] > entropy[i]) mEnt = i;
			}

			// If entopy of the cell is 0, something's wrong, go back
			if (entropy[mEnt] == 0) {
				point--; continue;
			// else pick the smallest value that fits
			} else {
				int r = mEnt/9, c = mEnt%9, b = mEnt/27*3+mEnt%9/3;
				cell[point] = mEnt; state[point] = 0;
				mx[mEnt] = options(can, mEnt)[0];
				known++;
				
				can[0][r].erase(mx[mEnt]); 
				can[1][c].erase(mx[mEnt]); 
				can[2][b].erase(mx[mEnt]);
			}
		// else, aka if we are trying to *replace* the value of a cell
		} else {

			int r = cell[point]/9, c = cell[point]%9, b = cell[point]/27*3+cell[point]%9/3;
			can[0][r].insert(mx[cell[point]]); 
			can[1][c].insert(mx[cell[point]]); 
			can[2][b].insert(mx[cell[point]]);
			
			auto opt = options(can, cell[point]);

			// if there are available options for the cell we haven't tried yet, 
			// try to replace the current value one of those
			if (state[point]+1 < (int)opt.size()) {
				state[point]++;
				mx[cell[point]] = opt[state[point]];
				can[0][r].erase(mx[cell[point]]); 
				can[1][c].erase(mx[cell[point]]); 
				can[2][b].erase(mx[cell[point]]);
			// else something's wong, go back
			} else {
				state[point] = cell[point] = mx[cell[point]] = -1;
				point--; known--; continue;
			}
		}
		point++;
	}

	// ouput
	cout << "\nSolution:\n" << visualize(mx);
}

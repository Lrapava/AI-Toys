#include <bits/stdc++.h>
using namespace std;

#define ACTION_TYPE if (true) cout 
#define POSITION if (true) cout 
#define LOG_POINT if (true) cout
#define VISUALIZE_STEPS if (true) cout

set <int> intersect(set <int> a, set <int> b) {
	set <int> res;
	for (auto x : a) if (b.find(x) != b.end()) res.insert(x);
	return res;
}
set <int> intersect(set <int> a, set <int> b, set <int> c) { return intersect(a, intersect(b, c)); }

vector <int> vectorize(set <int> st) {
	vector <int> res;
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

int known(vector <int> mx) { int k = 0; for (int x : mx) if (x > 0) k++; return k; }
string pos(int i) { return "(" + to_string(i/9) + ", " + to_string(i%9) + ")"; }

vector <int> options(set <int> can[3][9], int i) {
	return vectorize(intersect(can[0][i/9], can[1][i%9], can[2][i/27*3+i%9/3]));
}

int main() {

	cout << "Enter your sudoku:\n";
	vector <int> mx(81, -1);
	
	{
		for (int i = 0; i < 81; i++) {
			char c; cin >> c;
			if (c > '0' && c <= '9') mx[i] = c-'0';
			else mx[i] = -1;
		}
	}

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
	
	while (known(mx) < 81) {

		VISUALIZE_STEPS << visualize(mx);
		LOG_POINT << "> [" << point << "] " << known(mx) << "\n\n";
		if (point < 0) { cout << "!!!!\n"; exit(0); }
		
		if (cell[point] == -1) {
			ACTION_TYPE << "A" << flush;

			int entropy[81], mEnt = 0; 
			for (int i = 0; i < 81; i++) {
				if (mx[i] == -1) entropy[i] = options(can, i).size(); else entropy[i] = 999;
				if (entropy[mEnt] > entropy[i]) mEnt = i;
			}

			if (entropy[mEnt] == 0) {
				ACTION_TYPE << "1 (go back)\n"; 
				POSITION << pos(mEnt) << "\n";
				point--; continue;
			} else {
				ACTION_TYPE << "2 (next)\n"; 
				POSITION << pos(mEnt) << " [" << entropy[mEnt] << "]" << "\n";
				int r = mEnt/9, c = mEnt%9, b = mEnt/27*3+mEnt%9/3;
				cell[point] = mEnt; state[point] = 0;
				mx[mEnt] = options(can, mEnt)[0];

				can[0][r].erase(mx[mEnt]); 
				can[1][c].erase(mx[mEnt]); 
				can[2][b].erase(mx[mEnt]);
			}
		} else {
			ACTION_TYPE << "B" << flush;

			int r = cell[point]/9, c = cell[point]%9, b = cell[point]/27*3+cell[point]%9/3;
			can[0][r].insert(mx[cell[point]]); 
			can[1][c].insert(mx[cell[point]]); 
			can[2][b].insert(mx[cell[point]]);
			
			auto opt = vectorize(intersect(can[0][r], can[1][c], can[2][b]));

			if (state[point] + 1 < (int)opt.size()) {
				ACTION_TYPE << "1 (fixed)\n"; 
				POSITION << pos(cell[point]) << " [" << opt.size() << "]\n";
				state[point]++;
				mx[cell[point]] = opt[state[point]];
				can[0][r].erase(mx[cell[point]]); 
				can[1][c].erase(mx[cell[point]]); 
				can[2][b].erase(mx[cell[point]]);
			} else {
				ACTION_TYPE << "2 (go back)\n"; 
				POSITION << pos(cell[point]) << " [" << opt.size() << "]\n";
				state[point] = cell[point] = mx[cell[point]] = -1;
				point--; continue;
			}
		}
		point++;
	}

	cout << "Solution:\n" << visualize(mx);
}

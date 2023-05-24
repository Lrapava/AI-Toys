#include "Luke.cpp"
using namespace std;

vector <int> x,y;
int n,coinX,coinY,somex,somey,pdp[20][20];

int poss2go(int _x, int _y) {
	
	if (_x<0 || _y<0 || _x>19 || _y>19) return 0;
	
	if (pdp[_x][_y]==1) return 0;
	
	for (int i = 1; i < n; i++) {
		if (x[i]==_x && y[i]==_y) return 0;
	}
	
	pdp[_x][_y]=1;
	
//	cout << _x << " " << _y << endl;
	
	poss2go(_x+1,_y);
	poss2go(_x-1,_y);
	poss2go(_x,_y+1);
	poss2go(_x,_y-1);
	
}

bool in_cage() {
	
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			pdp[i][j]=0;
		}
	}
	
	poss2go(x[0],y[0]);
	
	return !pdp[coinX][coinY];
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> somex >> somey;
		x.push_back(somex);
		y.push_back(somey);
	}
	
	cout << "Coin coords: ";
	
	cin >> coinX >> coinY;
	
	if (!in_cage()) cout << "NOT ";
	
	cout << "IN CAGE" << endl;
	
	system("pause");
	
}

#include "Luke.cpp"
using namespace std;

vector <int> x,y;
int coinX, coinY,n,lX,lY,len;
bool alive,kb;
char c = ' ';

int dp[20][20];

string path;

bool suicide() {
	for (int i = 1; i < n; i++) {
		if (x[0] == x[i] && y[0] == y[i]) return true;
	}
	return false;
}

char next() {
	len--;
	return path[len];
}

int rec(int _x, int _y, int p, string s) {
	
	if (_x<0 || _y<0 || _x>=20 || _y>=20) return 0;
	
	for (int i = 0; i < n; i++) {
		if (x[i]==_x && y[i]==_y) return 0;
	}
	
	if (dp[_x][_y] < p + 1) return 0;
	
	dp[_x][_y] = p + 1;
	
	if (_x==coinX && _y==coinY) path = s;
	
	rec(_x+1,_y,p+1,s+"d");
	rec(_x-1,_y,p+1,s+"a");
	rec(_x,_y+1,p+1,s+"s");
	rec(_x,_y-1,p+1,s+"w");
	
}

void calculate() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			dp[i][j]=400;
		}
	}
	
	dp[x[0]][y[0]]=0;
		
	rec(x[0],y[0],0,"");
		
}

void arena() {
	SetColor(7);
	gotoxy(0,0);
	cout << "############################################ " << endl;
	cout << "#                                          #  score :    " << endl;
	cout << "#                                          # " << endl;
	cout << "#                                          #  W - up" << endl;
	cout << "#                                          #  A - left" << endl;
	cout << "#                                          #  S - down" << endl;
	cout << "#                                          #  D - right" << endl;
	cout << "#                                          #  R - reset" << endl;
	cout << "#                                          # " << endl;
	cout << "#                                          # " << endl;
	cout << "#                                          # " << endl;
	cout << "#                                          # " << endl;
	cout << "#                                          # " << endl;
	cout << "#                                          # " << endl;
	cout << "#                                          # " << endl;
	cout << "#                                          # " << endl;
	cout << "#                                          # " << endl;
	cout << "#                                          # " << endl;
	cout << "#                                          # " << endl;
	cout << "#                                          # " << endl;
	cout << "#                                          # " << endl;
	cout << "#                                          # " << endl;
	cout << "############################################ " << endl;
}

void getcoin() {
	coinX=rand()%20;
	coinY=rand()%20;
}

void move() {
	for(int i = n-1; i>0; i--) {
		x[i]=x[i-1];
		y[i]=y[i-1];
	}
}

void draw() {
	SetColor(2);
	gotoxy(x[0]*2+1,y[0]+1);
	cout << "()";
	for(int i = 1; i < n; i++) {
		gotoxy(x[i]*2+1,y[i]+1);
		cout << "[]";
	}
}

int main() {
	again:
	
	cls();
	
	n = 1;
	alive = true;
	
	x.resize(0);
	y.resize(0);
	
	c='q';
	
	x.push_back(10);
	y.push_back(10);
	
	while (1) {
		
		c = next();
//		kbget(c);
		
		if (c=='w' || c=='W' || c=='s' || c=='S' || c=='a' || c=='A' || c=='d' || c=='D') move(); else if (c=='r' || c=='R') alive=false;
		
		if (c=='w' || c=='W') {
			y[0]--;
		}
		if (c=='s' || c=='S') {
			y[0]++;
		}
		if (c=='a' || c=='A') {
			x[0]--;
		}
		if (c=='d' || c=='D') {
			x[0]++;
		}
		
		if (suicide()) alive = false;
		if (x[0]<0 || x[0]>20 || y[0]<0 || y[0]>20) alive = false;
		if (!alive) break;
				
		arena();
		
		gotoxy(54,1);
		cout << n;
		
		gotoxy(coinX*2+1,coinY+1);
		SetColor(6);
		cout << "()";
		
		draw();
		
		if (coinX==x[0] && coinY==y[0]) {
			n++;
			x.push_back(0);
			y.push_back(0);
			getcoin();
			calculate();
			len = path.size();
		}
		
		gotoxy(0,21);
		cout << path;
		
		gotoxy(43,22);
		usleep(100000);
	}
	
	goto again;
	
}

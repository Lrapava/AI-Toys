#include "Luke.cpp"
using namespace std;

vector <int> x, y;
int coinX, coinY, n, m, dp[20][20], dp0[20][20], pdp[20][20], bp[20][20];
bool alive, b[20][20];
char c = ' ';
string ans;

//bool _calc;

/*

	ispolzuemie funkcii itd is Luke.cpp itd kotorie ti, vozmojno, ne znayesh:
	
	1. gotoxy - menyayet poziciyu kursora
	
	2. system("pause") - ostanavlivayet programmu poka na chto-nibud ne nazhmyosh
	
	3. goto <something> - pereprigivayet na kakoy kusok koda gde napisanno <something>:
		primeri:
		1)
			start:
			cout << 1;
			goto start;
		2)
			start:
			...
			if (something) goto end;
			goto start
			end:
			some code...
	
	4. usleep - ostanavlivayet kod na vremya	
	
	arena() - resuet kvadrat (void)
	getcoin() - vibirayet novuyu lokaciyu dlya manetki (char)
	move() - "dvigayet zmeyku" (void)
	draw() - risuyet zmeyku (void)
	suicide() - proveryayet ne ubila li sebya zmeyka (bool)
	
	f() - rekursivnaya procedura kotoraya v dp[20][20] sokhranyayet grubo govorya kolichestvo shagov chtobi dayti (void)
	calculate() - vizivayet f() i v string ans sokhranyayet darogu (void)
	mid4dir() - iz sosediy nakhodit (x,y) viberayet minimalnogo i vozvrahsyet char kotoriy vpisivayetsya v ans (char)
	next() - chitayet ans i vozvrashyayet w, a, s ili d (simuliruyet najatie) (char)
	
	ans - spisok dvijeniy dlya zmeyki
	vector <int> x,y - tut hranyatsya koordinati kvadratikov tela zmeyki
	coinX, coinY - koordinati maneti
	n - dlina zmeyki
	m - index chara v ans +1
	dp - 2D masiv. yego redaktiruyet f(). tut hronyatsya min. ceni chtobi dayti do kajdoy kletki
	dp0 - dp masiv do vizivaniya f().
	alive - alive == true yesli zmeyka jiva.
	b - 2D masiv. yesli b[x][y]==true, znachit na (x,y) chast tela kletki
	c - "ta knopka na kotoruyu najmyot kompyuter"
	
*/

bool sim();

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

bool in_cage(int tX, int tY) {
	
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			pdp[i][j]=0;
		}
	}
	
	poss2go(x[0],y[0]);
	
	return !pdp[tX][tY];
}

int can_go(int hX, int hY) {
	
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			pdp[i][j]=0;
		}
	}
	
	poss2go(hX,hY);
	
	int ans = 0;
	
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			ans+=pdp[i][j];
		}
	}
	
	return ans;
	
}


char min4dir(int x, int y) {
	pair <int,char> a[4];
	if (x>0 && !bp[x-1][y]) {
		a[0].first=dp[x-1][y];
	} else {
		a[0].first=-1;
	}
	
	if (x<19 && !bp[x+1][y]) {
		a[1].first=dp[x+1][y];
	} else {
		a[1].first=-1;
	}
	
	if (y>0 && !bp[x][y-1]) {
		a[2].first=dp[x][y-1];
	} else {
		a[2].first=-1;
	}
	
	if (y<19 && !bp[x][y+1]) {
		a[3].first=dp[x][y+1];
	} else {
		a[3].first=-1;
	}
	
	a[0].second='d'; //left
	a[1].second='a'; //right
	a[2].second='s'; //top
	a[3].second='w'; //bottom
	
	return max(max(a[0],a[1]),max(a[2],a[3])).second;
	
}

void f(int x, int y) {
	
	if (x>0) {
		
		if (!b[x-1][y]) {
			if (dp[x][y]+1 < dp[x-1][y]) {
				dp[x-1][y]=dp[x][y]+1;
				f(x-1,y);
			} 
		} else {
			if (dp[x-1][y]==dp0[x-1][y]) {
				dp[x-1][y]=dp[x][y]+dp0[x-1][y]+1;
				f(x-1,y);
			} else {
				if (dp[x][y]+dp0[x-1][y]+1<dp[x-1][y]) {
					dp[x-1][y]=dp[x][y]+dp0[x-1][y]+1;
					f(x-1,y);
				}
			}
		}
	}
	
	if (x<19) {
		
		if (!b[x+1][y]) {
			if (dp[x][y]+1 < dp[x+1][y]) {
				dp[x+1][y]=dp[x][y]+1;
				f(x+1,y);
			} 
		} else {
			if (dp[x+1][y]==dp0[x+1][y]) {
				dp[x+1][y]=dp[x][y]+dp0[x+1][y]+1;
				f(x+1,y);
			} else {
				if (dp[x][y]+dp0[x+1][y]+1<dp[x+1][y]) {
					dp[x+1][y]=dp[x][y]+dp0[x+1][y]+1;
					f(x+1,y);
				}
			}
		}
	}
	
	if (y>0) {
		
		if (!b[x][y-1]) {
			if (dp[x][y]+1 < dp[x][y-1]) {
				dp[x][y-1]=dp[x][y]+1;
				f(x,y-1);
			} 
		} else {
			if (dp[x][y-1]==dp0[x][y-1]) {
				dp[x][y-1]=dp[x][y]+dp0[x][y-1]+1;
				f(x,y-1);
			} else {
				if (dp[x][y]+dp0[x][y-1]+1<dp[x][y-1]) {
					dp[x][y-1]=dp[x][y]+dp0[x][y-1]+1;
					f(x,y-1);
				}
			}
		}
	}
	
	if (y<19) {
		
		if (!b[x][y+1]) {
			if (dp[x][y]+1 < dp[x][y+1]) {
				dp[x][y+1]=dp[x][y]+1;
				f(x,y+1);
			} 
		} else {
			if (dp[x][y+1]==dp0[x][y+1]) {
				dp[x][y+1]=dp[x][y]+dp0[x][y+1]+1;
				f(x,y+1);
			} else {
				if (dp[x][y]+dp0[x][y+1]+1<dp[x][y+1]) {
					dp[x][y+1]=dp[x][y]+dp0[x][y+1]+1;
					f(x,y+1);
				}
			}
		}
	}
}

void calculate() {
	
	ans="";
	
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			b[i][j]=0;
			dp[i][j]=200;
			dp0[i][j]=200;
		}
	}
	
	
	for (int i = 0; i < n; i++) {
		b[x[i]][y[i]]=1;
		dp[x[i]][y[i]]=i*200;
		dp0[x[i]][y[i]]=i*200;
	}
	
	b[x[0]][y[0]]=0;
	
	gotoxy(0,0);
	cout << "f";
	
	f(x[0],y[0]);
	
	int cx=coinX, cy=coinY;
	
	m = 0;
	
	char dir;
	
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			bp[i][j]=0;
		}
	}
	
	for(;;) {
		
		if (cy==y[0] && cx==x[0]) break;
		
		dir = min4dir(cx,cy);
		
		ans=dir+ans;
		
		// cx - current x
		// cy - current y
		
		if (dir=='w') {
			cy++;
		}
		if (dir=='a') {
			cx++;
		}
		if (dir=='s') {
			cy--;
		}
		if (dir=='d') {
			cx--;
		}
		
		bp[cx][cy] = 1;
		
	}
	
	gotoxy(0,20);
//	cout << sim();
	
}

char next() {
	m++;
	return ans[m-1];
}

void arena() {
	SetColor(7);
	gotoxy(0,0);
	cout << "############################################ " << endl;
	cout << "#                                          #  score :    " << endl;
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
	cout << "#                                          # " << endl;
	cout << "#                                          # " << endl;
	cout << "#                                          # " << endl;
	cout << "#                                          # " << endl;
	cout << "#                                          # " << endl;
	cout << "#                                          # " << endl;
	cout << "############################################ " << endl;
}

void getcoin() {
	bool b = 1;
	while (b) {
		coinX=rand()%20;
		coinY=rand()%20;
		b = 0;
		if (in_cage(coinX,coinY)) b = 1;
	}
	gotoxy(2,0);
	cout << coinX << "," << coinY;
}

void move() {
	for(int i = n; i>0; i--) {
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

bool suicide() {
	for (int i = 1; i < n; i++) {
		if (x[0] == x[i] && y[0] == y[i]) return true;
	}
	return false;
}

//bool sim() {
//	vector <int> _x, _y;
//	_x = x;
//	_y = y;
//	int len = ans.size();
//	
//	while (m<len) {
//		
//		c = next();
//		
//		move();
//		
//		if (c=='w' || c=='W') {
//			y[0]--;
//		}
//		if (c=='s' || c=='S') {
//			y[0]++;
//		}
//		if (c=='a' || c=='A') {
//			x[0]--;
//		}
//		if (c=='d' || c=='D') {
//			x[0]++;
//		}
//		
//		if (coinX==x[0] && coinY==y[0]) {
//			n++;
//			x.push_back(0);
//			y.push_back(0);
//			break;
//		}
//		
//		calculate();
//		
//		if (x[0]<0 || x[0]>20 || y[0]<0 || y[0]>20) alive = false;
//	}
//	
//	x = _x;
//	y = _y;
//	m = 0;
//	n--;
//	
//	if (can_go(coinX,coinY)<n) return 0;
//	return 1;
//
//}

int main() {
	again:
	
	cls();
	
	n = 1;
	alive = true;
	
//	_calc=true;
	
	x.resize(0);
	y.resize(0);
	
	c='q';
	x.push_back(10);
	y.push_back(11);
	x.push_back(10);
	y.push_back(10);
	
	getcoin();
	
	calculate();
	
	while (alive) {
		
		arena();
		
		gotoxy(54,1);
		cout << n;
		
		gotoxy(coinX*2+1,coinY+1);
		SetColor(6);
		
		cout << "()";
		
		draw();
		
		gotoxy(0,24);
		
		c = next();
		gotoxy(0,0);
		cout << c;
		
		move();
		
//		if (_calc==true) {
//			calculate();
//			_calc=false;
//		}
		
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
		
		if (coinX==x[0] && coinY==y[0]) {
			n++;
			x.push_back(0);
			y.push_back(0);
			getcoin();
//			_calc=true;
		}
		
		calculate();
		
		if (x[0]<0 || x[0]>20 || y[0]<0 || y[0]>20) alive = false;
		gotoxy(43,22);
		usleep(100000);
//		system("pause");
	}
	
	goto again;
	
}

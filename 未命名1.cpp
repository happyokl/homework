//this is a new 
#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<vector>
#include<time.h>
#include<queue>
using namespace std;

int min(int a, int b) {
	return a < b ? a : b;
}
class map {
public:
	int mar[110][110] = { {0} };//0为源点，最后为汇点
	int n, m;
	int a, b;
	int size;
	
	int path[1100];
	int flow[1100] = { 100000 };
	int level[1100] = { 0 };
	map(int x1, int x2, int x3, int x4) {
		n = x1, m = x2, a = x3, b = x4;
		size = n + m + 2;
		for (int i = 1; i <= n; i++)
			mar[0][i] = b;
		for (int i = 1; i <= n; i++) {
			for (int j = n + 1; j <= n + m; j++)
				mar[i][j] = 1;
		}
		for (int i = n + 1; i <= m + n; i++) {
			mar[i][m + n + 1] = a;
		}
	}
	int EK() {
		int f = 0;
		while (1) {
			
			int t = bfs();
			cout << t << " ";
			if (!t)
				break;
			f += t;
			int i = size - 1;
			while (i != 0) {
				int j = path[i];
				mar[j][i] -= t;
				mar[i][j] += t;
				i = j;
			}
		}
		return f;
	}
	int bfs() {
		int i, t;
		memset(path, -1, sizeof(path));
		queue<int> q;
		q.push(0);
		path[0] = 0;

		while (!q.empty()) {
			t = q.front();
			q.pop();
			if (t == size - 1)//找到汇点停止
				break;
			for (int i = 0; i < size; i++) {

				if (mar[t][i] && path[i] == -1)
				{	//选择当前路径上最少的流容量	
					flow[i] = flow[t] < mar[t][i] ? flow[t] : mar[t][i];
					q.push(i);
					
					
					path[i] = t;
				}
			}
		}
		if (path[size - 1] == -1)
			return 0;
		return flow[size - 1];
	}
	int Dinic() {
		int f = 0;
		while (bfs2()) {
			while (1) {
				int r = dfs(0, 100000);
				f += r;
				if (r == 0)
					break;
			}
		}
		return f;
	}
	int bfs2() {
		queue<int> q;
		memset(level, 0, sizeof(level));
		int visit[1100] = { 0 };
		q.push(0);
		visit[0] = 1;
		while (!q.empty()) {
			int t = q.front();
			
			q.pop();
			for(int i=0;i<size;i++)
				if (mar[t][i] && !visit[i])
				{
					q.push(i);
					
					level[i] = level[t] + 1;
					visit[i] = 1;
				}
				
				
		}
		
		
		return level[size - 1] != 0;
	}

	int dfs(int x, int f) {
		int t = f;
		int temp;
		if (x == size - 1)
			return f;
		if (f) {
			for (int i = 1; i < size; i++) {
				if (mar[x][i] && level[i] == level[x] + 1) {
					temp = dfs(i, min(t, mar[x][i]));
					mar[x][i] -= temp;
					mar[i][x] += temp;
					return temp;
				}
			}
		}
		return 0;
	}
	int dfs2(int x, int f) {//dinic+多路增广
		int t = f;
		int temp;
		if (x == size - 1)
			return f;
		if (f) {
			for (int i = 1; i < size; i++) {
				if (mar[x][i] && level[i] == level[x] + 1) {
					temp = dfs(i, min(t, mar[x][i]));
					if (temp != 0) {
						mar[x][i] -= temp;
						mar[i][x] += temp;
						
						t-=temp;
						return t;
					}
				}
			}
		}
		return 0;
	}
	int Dinic2() {
		int f = 0;
		while (bfs2()) {
			while (1) {
				int r = dfs2(0, 100000);
				f += r;
				if (r == 0)
					break;
			}
		}
		return f;
	}
	
};

int main() {
	map a(30,10,3,10);    //n,m,a,b;
	cout << a.Dinic() << " " ;
}






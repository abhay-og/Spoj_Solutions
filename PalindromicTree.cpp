#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

#define For(i, j, k) for(int i = j; i <= k; i++)
#define Forr(i, j, k) for(int i = j; i >= k; i--)
#define Set(i, v) memset(i, v, sizeof i)

using namespace std;

const int N = 1e5+10;

typedef long long LL;

char S[N];

struct Palindromic_Tree{

	int lst, e, p;
	int S[N], fail[N], rt[N], half[N], val[N], len[N], ch[N][26];

	void init(){
		lst = e = 1, p = 0;
		fail[0] = fail[1] = 1, len[1] = -1;
		Set(rt, 0), Set(ch, 0);
		S[0] = -1;
	}

	int getfail(int o){
		while(S[p] != S[p - len[o] - 1]) o = fail[o];
		return o;
	}

	void add(int c){
		S[++p] = c;
		int cur = getfail(lst);
		if(!ch[cur][c]){
			fail[++e] = ch[getfail(fail[cur])][c];
			len[e] = len[cur] + 2;
			ch[cur][c] = e;
			int q = ch[getfail(half[lst])][c];
			while(len[q] > len[e] / 2) q = fail[q];
			val[e] = len[q] > 0 && len[q] == len[e] / 2 ? val[q] + 1 : 1;
			half[e] = q;
		}
		int o = ch[cur][c];
		rt[o]++;
		lst = o;
	}
	
	int Ans[N]={};

	void calc(){
		Forr(i, e, 2) rt[fail[i]] += rt[i], Ans[val[i]] += rt[i];
		Forr(i, p, 1) Ans[i] += Ans[i + 1]; 
		long long res=0;
		for(int i=0;i<N;i++)res+=Ans[i];
		cout<<res<<'\n';
	}
};

int main(){
	int t;
	cin>>t;
	while(t--){
	    Palindromic_Tree T;
	    T.init();
	    scanf("%s", S);
	    int n = strlen(S) - 1;
	    For(i, 0, n) T.add(S[i] - 'a');
	    T.calc();
	}
	return 0;
}

// idk the solution or its usage lmao

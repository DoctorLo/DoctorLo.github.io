#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
const int N = 1e5+10;
int son[N],s[N];
int t,n,k;
int pos[N];
int a[N],st[N][25],Log[N];//2^20就过一百万了，完全够用 
//初始化st表 
void init(){
	Log[1] = 0;//预处理log函数 
	for(int i = 2;i <= n+1;i++) Log[i] = Log[i/2]+1;
	for(int i = 1;i <= n;i++) st[i][0] = a[i];
	for(int j = 1; (1<<j) <= n;j++){	//涉及到位运算多加括号! 
		for(int i = 1;i + (1<<(j-1)) <= n;i++){
			st[i][j] = max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
		}
	}
}
int ask(int l,int r){
	l = max(l,1); r = min(n,r); 
	int kk = Log[r-l+1];
	int mx = max(st[l][kk],st[r-(1<<kk)+1][kk]);
	printf("%d %d\n",k,mx);
	return mx;
}
int cal(int x){
	if(son[x] != -1) return x;
	int y = ask(pos[x]-k,pos[x]-1);
	y = max(y,ask(pos[x]+1,pos[x]+k));
	son[x] = cal(y); s[x] = s[y]+1;
	return x;
}
void solve(){
	init();
	memset(son,-1,sizeof son);
	for(int i = 1;i <= n;i++){
		printf("y");
		cal(i);
	}
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);
		for(int i = 1;i <= n;i++) scanf("%d",a+i),pos[a[i]] = i;
		solve();
		for(int i = 1;i < n;i++) printf("%d ",s[i]);
		printf("%d\n",s[n]);
	}
	return 0;
}
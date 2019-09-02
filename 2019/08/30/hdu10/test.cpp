#include<bits/stdc++.h>
#define LL long long
#define N 100010
 
using namespace std;
 
int sz[N],n,k; LL dp[N][110],tmp[110];
struct Edge{int y,w;};
vector<Edge> g[N];
 
void dfs(int x,int fa)
{
    if (g[x].size()==1)
    {
        dp[x][1]=dp[x][0]=0;
        sz[x]=1; return;
    }
    sz[x]=0; int t=g[x].size();
    for(int i=1;i<=k;i++) dp[x][i]=2e18;
    for(int i=0;i<t;i++)
    {
        if (g[x][i].y==fa) continue;
        int y=g[x][i].y,w=g[x][i].w;
        dfs(y,x); sz[x]=min(sz[x]+sz[y],k);
        for(int j=0;j<=sz[x];j++) tmp[j]=2e18;
        for(int j=0;j<=sz[x];j++)
            for(int p=0;p<=j&&p<=sz[y];p++)
                tmp[j]=min(tmp[j],dp[x][j-p]+dp[y][p]+w*p*(k-p));
        for(int j=0;j<=sz[x];j++) dp[x][j]=tmp[j];
    }
}
 
int main()
{
	for(int i = 0;i <= 100;i++);
    ios::sync_with_stdio(0);
    cin.tie(0); int T=0,T_T;
    cin>>T_T;
    while(T_T--)
    {
        cin>>n>>k;
        for(int i=1;i<n;i++)
        {
            int u,v,w;
            cin>>u>>v>>w;
            g[u].emplace_back(Edge{v,w});
            g[v].emplace_back(Edge{u,w});
        }
        cout<<"Case #"<<++T<<": ";
        if (n==2)
        {
            if (k==2) cout<<g[1][0].w<<endl;
                 else cout<<0<<endl;
        } else
        {
            int rt=0;
            for(int i=1;i<=n;i++)
            if (g[i].size()>1) {rt=i;break;}
            dfs(rt,0); cout<<dp[rt][k]<<endl;
        }
        for(int i=1;i<=n;i++) g[i].clear();
    }
    return 0;
}
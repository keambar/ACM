/*
    hdu 5452
    ˼·:����ÿ�ζ�Ҫɾ��ǡ��һ�����ߣ���ô���ͼ�ĸ�ɵ���������Ӧ�ø�������һ��������
    �Ը���Խڵ�xΪ����������˵����������������������������ıߡ�
    ���ǣ�ֻҪ���ÿ����������������ıߵ�����sum[]�����ˡ�
    ÿ�μ���һ�������ߣ�u��v��������u,v��·���ϵĳ��˹������ȵ����е��sum��һ�����ڵ���Ҫ����
*/
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define pf push_front
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define SZ(x) ((int)(x).size())
#define LL long long
#define se second
#define fi first
const int N = 20004;
const int Mod = ( int ) 1e9 + 7;

struct node {
    int v, ne;
} E[N << 1];
int head[N], cnt;
void add( int u, int v )
{
    E[++cnt].v = v, E[cnt].ne = head[u];
    head[u] = cnt;
}

int fat[N], dfn[N], ti;
int sum[N];
int n, m;

void dfs( int u, int from )
{
    dfn[u] = ++ti;
    fat[u] = from;
    for( int i = head[u]; i; i = E[i].ne ) {
        int v = E[i].v;
        if( v == from ) continue ;
        dfs( v, u );
    }
}

void make( int u, int v )
{
    if( dfn[u] < dfn[v] ) swap( u, v );
    if( dfn[v] == 1 ) ++sum[1];
    while( dfn[u] > dfn[v] ) {
        ++sum[u];
        u = fat[u];
    }
    while( dfn[v] > dfn[u] ) {
        ++sum[v];
        v = fat[v];
    }
}
int main()
{
    int T, cs = 0;
    scanf( "%d", &T );
    while( T-- ) {
        scanf( "%d %d" , &n, &m );
        memset( sum, 0, sizeof sum );
        memset( head, 0, sizeof head );
        cnt = ti = 0;
        for( int i = 1, u, v; i < n; ++i ) {
            scanf( "%d %d", &u, &v );
            add( u, v ), add( v, u );
        }
        dfs( 1, 0 );
        for( int i = n, u, v; i <= m; ++i ) {
            scanf( "%d %d", &u, &v );
            make( u, v );
        }
        int ans = m;
        for( int i = 1; i <= n; ++i ) {
            ans = min( ans, sum[i] );
        }
        printf( "Case #%d: %d\n", ++cs, ans + 1 );
    }
    return 0;
}

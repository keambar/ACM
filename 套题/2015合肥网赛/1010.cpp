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
const int N = 200005;
const int Mod = ( int ) 1e9 + 7;


const int MAXN = 111111, INF = 0x7fffffff;
struct sj {
    int x, k;
} a[N];

struct node {
    //��Ҫ�ļ�¼��Ϣ
    int  key, Size;
    //ָ����Ӻ͸��׵�ָ��
    node *ch[2], *pre;
    node()
    {
        pre = ch[0] = ch [1] = 0;
        Size = 1;
        key = 0;
    }
    node ( int key ) : key ( key )
    {
        pre = ch[0] = ch[1] = 0;
        key = key;
        Size = 1;
    }
    void Csize()
    {
        Size = 1;
        if ( ch[0] != NULL ) Size += ch[0]->Size;
        if ( ch[1] != NULL ) Size += ch[1]->Size;
    }

} nil ( 0 ), *NIL = &nil;

struct Splay {
    node *root, nod[MAXN];
    int ncnt;//����keyֵ��ͬ�Ľ��������ȥ��
    Splay()
    {
        ncnt = 0;
        root = & ( nod[ncnt++] = node ( INF ) );
        root->pre = NIL;
    }

    void Update ( node *x )
    {
        x->Csize();
    }

    void Rotate ( node *x, int sta ) //����ת������0������1����
    {
        node *p = x->pre, *g = p->pre;
        p->ch[!sta] = x->ch[sta];
        if ( x->ch[sta] != NULL )  x->ch[sta]->pre = p;
        x->pre = g;
        if ( g != NIL )
            if ( g->ch[0] == p )  g->ch[0] = x;
            else g->ch[1] = x;
        x->ch[sta] = p, p->pre = x, Update ( p );
        if ( p == root ) root = x;
    }

    void splay ( node *x, node *y ) //Splay ��������ʾ�ѽ��x,ת����
    {
        for ( ; x->pre != y; ) { //��x�ı�����´�
            if ( x->pre->pre == y ) { //Ŀ����Ϊ�����
                if ( x->pre->ch[0] == x )       Rotate ( x, 1 );
                else   Rotate ( x, 0 );
            } else {
                node *p = x->pre, *g = p->pre;
                if ( g->ch[0] == p )
                    if ( p->ch[0] == x )
                        Rotate ( p, 1 ), Rotate ( x, 1 ); //   / һ����˫��ת
                    else
                        Rotate ( x, 0 ), Rotate ( x, 1 ); //  < ֮����˫��ת

                else if ( p ->ch[1] == x )
                    Rotate ( p, 0 ), Rotate ( x, 0 ); //    \ һ������ת
                else
                    Rotate ( x, 1 ), Rotate ( x, 0 ); //   >֮������ת
            }
        }
        Update ( x ); //ά��x���
    }
    //�ҵ���������ĵ�K����㣬����ת�����y�����档
    void Select ( int k, int x )
    {
        int tem ;
        node *t = & ( nod[++ncnt] = node ( a[x].x ) );
        node *p ;
        for ( p = root; ; ) {
            if(p->ch[0]==0) tem=0;
            else
            tem = p->ch[0]->Size ;
            if ( k == tem + 1 ) break ; //�ҵ��˵�k����� t
            if ( k <= tem )
                p = p->ch[0] ; //��k�������������
            else
                k -= tem + 1 , p = p->ch[1] ;//��������
        }
        t->pre = p;
        t->ch[0] = p->ch[0];
        if( p->ch[0] != 0 ) {
            p->ch[0]->pre = t;
        }
        p->ch[0] = t;
        splay( t, root );
    }
    void outp( node *p )
    {
        if( p->ch[0] != 0 ) {
            outp( p->ch[0] );
        }
        if( p != root ) {
            printf( " %d", p->key );
        }
        if( p->ch[1] != 0 ) {
            outp( p->ch[1] );
        }

    }
} sp;


bool cmp( sj a, sj b )
{
    return a.x > b.x;
}

int n;
int main()
{
    int T, cs = 0;
    scanf( "%d", &T );
    while( T-- ) {
        sp.ncnt = 0;
        sp.root = & ( sp.nod[sp.ncnt++] = node ( INF ) );
        sp.root->pre = NIL;
        scanf( "%d", &n );
        for( int i = 1; i <= n; ++i ) {
            scanf( "%d %d", &a[i].x, &a[i].k );
        }
        sort( a + 1, a + 1 + n, cmp );
        bool flag = 0;
        for( int i = 1; i <= n; ++i ) {
            if( a[i].k >= i ) {
                flag = 1;
                break;
            }
            if( a[i].k + 1 <= i - a[i].k ) {
                sp.Select( a[i].k + 1, i );
            } else {
                sp.Select( i - a[i].k, i );
            }
        }
        printf( "Case #%d:", ++cs );
        if( flag ) {
            puts( " impossible" );
        } else {
            sp.outp( sp.root );
            puts("");
        }
    }
}

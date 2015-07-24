/*
      ���������½��������㷨
         1)cap(u,v)Ϊu��v�ıߵ�����
         2)Gup(u,v)Ϊu��v�ı������Ͻ�
         3)Glow(u,v)Ϊu��v�ı������½�
         4)st(u)�����u�����г��ߵ��½�֮��
         5)ed(u)�����u��������ߵ��½�֮��
         6)SΪԴ�㣬TΪ���
       ������D�Ĺ��췽��:
         1)��������Դ��SS,ST
         2)�����(u,v)������cap(u,v)=Gup(u,v)-Glow(u,v)
         3)����ÿ����v,�����(SS,v)=ed(v);
         4)����ÿ����u,�����(u,ST)=st(u);
         5)cap(T,S)=+��;
         6)tflowΪ���бߵ��½�֮��
       ��SS��ST����������������������tflow���򲻴��ڿ��������������޽⡣
       ��������D��ȥ��������SS��ST�����ıߡ����������
       ���������ֵ���
       ��С�����ڶ����������T��S���С�

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#define ms(a,b) memset(a,b,sizeof a)
using namespace std;
const int INF = 111;
struct node {
    int u, v, c, next;
} edge[INF * INF << 2];
int Gup[INF][INF], Glow[INF][INF], st[INF], ed[INF], cap[INF][INF], tflow;
int  pHead[INF*INF], SS, ST, S, T, nCnt, ans;
//ͬʱ��ӻ��ͷ����, ����߳�ʼ����Ϊ0
void addEdge (int u, int v, int c) {
    edge[++nCnt].v = v, edge[nCnt].u = u, edge[nCnt].c = c;
    edge[nCnt].next = pHead[u]; pHead[u] = nCnt;
    edge[++nCnt].v = u, edge[nCnt].u = v, edge[nCnt].c = 0;
    edge[nCnt].next = pHead[v]; pHead[v] = nCnt;
}
int SAP (int pStart, int pEnd, int N) {
    int numh[INF], h[INF], curEdge[INF], pre[INF];
    int cur_flow, flow_ans = 0, u, neck, i, tmp;
    ms (h, 0); ms (numh, 0); ms (pre, -1);
    for (i = 0; i <= N; i++) curEdge[i] = pHead[i];
    numh[0] = N;
    u = pStart;
    while (h[pStart] <= N) {
        if (u == pEnd) {
            cur_flow = 1e9;
            for (i = pStart; i != pEnd; i = edge[curEdge[i]].v)
                if (cur_flow > edge[curEdge[i]].c) neck = i, cur_flow = edge[curEdge[i]].c;
            for (i = pStart; i != pEnd; i = edge[curEdge[i]].v) {
                tmp = curEdge[i];
                edge[tmp].c -= cur_flow, edge[tmp ^ 1].c += cur_flow;
            }
            flow_ans += cur_flow;
            u = neck;
        }
        for ( i = curEdge[u]; i != 0; i = edge[i].next) {
            if (edge[i].v > N) continue; //��Ҫ!!!
            if (edge[i].c && h[u] == h[edge[i].v] + 1)     break;
        }
        if (i != 0) {
            curEdge[u] = i, pre[edge[i].v] = u;
            u = edge[i].v;
        }
        else {
            if (0 == --numh[h[u]]) continue;
            curEdge[u] = pHead[u];
            for (tmp = N, i = pHead[u]; i != 0; i = edge[i].next) {
                if (edge[i].v > N) continue; //��Ҫ!!!
                if (edge[i].c)  tmp = min (tmp, h[edge[i].v]);
            }
            h[u] = tmp + 1;
            ++numh[h[u]];
            if (u != pStart) u = pre[u];
        }
    }
    return flow_ans;
}
int solve (int n) {
    //������������
    SS = n + 1, ST = n + 2;
    for (int i = 1; i <= n; i++) {
        if (ed[i]) addEdge (SS, i, ed[i]);
        if (st[i]) addEdge (i, ST, st[i]);
    }
    //T��S���һ������������
    addEdge (T, S, 0x7ffffff);
    //�жϿ�����
    int tem = SAP (SS, ST, ST);
    if (tem != tflow) return -1;
    else {
        edge[nCnt].c = edge[nCnt - 1].c = 0; //ɾ��S��T������������
        int kkk = SAP (T, S, T);
        return 1;
    }
}
int n, m, x, y, c, sta;
int main() {
    /*
           ��ͼ,ǰ���Ǵ�ߣ���ͷ��pHead[],�߼��� nCnt.
           S,T�ֱ�ΪԴ��ͻ��
    */
    scanf ("%d %d", &n, &m);
    nCnt = 1;
    for (int i = 1; i <= m; i++) {
        scanf ("%d %d %d %d", &x, &y, &c, &sta);
        Gup[x][y] = c;
        if (sta) {
            Glow[x][y] = c;
            st[x] += c, ed[y] += c;
            tflow += c;
        }
        addEdge (x, y, Gup[x][y] - Glow[x][y]);
    }
    S = 1, T = n;
    ans = 0;
    if (solve (n) > 0) {
        for (int i = 2; i <= nCnt; i += 2) {
            if (edge[i].v <= T && edge[i].u == 1)
                ans += Gup[edge[i].u][edge[i].v] - edge[i].c;
            if (edge[i].u <= T && edge[i].v == 1)
                ans -= Gup[edge[i].u][edge[i].v] - edge[i].c;
        }
        if (ans < 0) {
            S = 0;
            addEdge (S, 1, -ans);
            ans = 0;
            SAP (S, T, T);
        }
        printf ("%d\n", ans);
        for (int i = 2; i <= 2 * m; i += 2)
            printf ("%d ", Gup[edge[i].u][edge[i].v] - edge[i].c);
    }
    else puts ("Impossible");
    return 0;
}
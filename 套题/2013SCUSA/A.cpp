/*
      �����SAP
      �ڽӱ�
      ˼·������Դ��FF��������ÿ�������趨��α�ţ���������
      �Ż�:
      1����ǰ���Ż�����Ҫ����
      1��ÿ�ҵ���������·���˵��ϵ㣨�����Ż�����
      2����γ��ֶϲ㣬�޷��õ���������Ҫ����
      ʱ�临�Ӷȣ�m*n^2��
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>
#define ms(a,b) memset(a,b,sizeof a)
using namespace std;
const int INF = 6111;
struct node {
	int v, c, next;
} edge[100000];
int  pHead[100000], SS, ST, nCnt;
int n, m;
int g[200][200];
int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
//ͬʱ��ӻ��ͷ����, ����߳�ʼ����Ϊ0
void addEdge (int u, int v, int c) {
	edge[++nCnt].v = v; edge[nCnt].c = c, edge[nCnt].next = pHead[u]; pHead[u] = nCnt;
	edge[++nCnt].v = u; edge[nCnt].c = 0, edge[nCnt].next = pHead[v]; pHead[v] = nCnt;
}
inline int SAP (int pStart, int pEnd, int N) {
	//��ε������  ��Ĳ��   �������     ��ǰ�߹��ߵ�ջ
	int numh[INF], h[INF], curEdge[INF], pre[INF];
	//��ǰ�ҵ�����, �ۼƵ�����, ��ǰ��, �ϵ�, �м����
	int cur_flow, flow_ans = 0, u, neck, i, tmp;
	//��ղ������,
	ms (h, 0); ms (numh, 0); ms (pre, -1);
	//��������Ϊ�ڽӱ������һ����
	for (i = 0; i <= N; i++) curEdge[i] = pHead[i];
	numh[0] = N;//��ʼȫ����Ĳ��Ϊ0
	u = pStart;//��Դ�㿪ʼ
	//�����Դ�����ҵ�����·
	while (h[pStart] <= N) {
		//�ҵ�����·
		if (u == pEnd) {
			cur_flow = 1e9;
			//�ҵ���ǰ����·�е��������, ���¶ϵ�
			for (i = pStart; i != pEnd; i = edge[curEdge[i]].v)
				if (cur_flow > edge[curEdge[i]].c) neck = i, cur_flow = edge[curEdge[i]].c;
			//���ӷ���ߵ�����
			for (i = pStart; i != pEnd; i = edge[curEdge[i]].v) {
				tmp = curEdge[i];
				edge[tmp].c -= cur_flow, edge[tmp ^ 1].c += cur_flow;
			}
			flow_ans += cur_flow;//�ۼ�����
			u = neck;//�Ӷϵ㿪ʼ���µ�����·
		}
		//�ҵ�һ������
		for ( i = curEdge[u]; i != 0; i = edge[i].next)
			if (edge[i].c && h[u] == h[edge[i].v] + 1)     break;
		//����DFS
		if (i != 0) {
			curEdge[u] = i, pre[edge[i].v] = u;
			u = edge[i].v;
		}
		//��ǰ���û������,��u�Ҳ�������·
		else {
			//u���ڵĲ�ε����һ,�����û���뵱ǰ��һ����εĵ�, �˳�.
			if (0 == --numh[h[u]]) continue;
			//����u��ͬ��εĵ�, ����u�Ĳ�� ,�ص���һ����
			curEdge[u] = pHead[u];
			for (tmp = N, i = pHead[u]; i != 0; i = edge[i].next)
				if (edge[i].c)  tmp = min (tmp, h[edge[i].v]);
			h[u] = tmp + 1;
			++numh[h[u]];
			if (u != pStart) u = pre[u];
		}
	}
	return flow_ans;
}
inline void build() {
	char ch;
	scanf ("%d %d", &n, &m);
	ms (g, -1), ms (pHead, 0), nCnt = 1;
	for (int i = 1; i <= n; i++) {
		getchar();
		for (int j = 1; j <= m; j++) {
			ch = getchar();
			if (ch == '.')  g[i][j] = 0;
			if (ch == 'D') g[i][j] = 1;
		}
	}
	n += 2, m += 2;
	SS = n * m, ST = SS + 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int u = i * m + j;
			if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
				addEdge (u, ST, 4);
				continue;
			}
			if (g[i][j] == 0)  {
				for (int k = 0; k < 4; k++) {
					int x = i + dx[k], y = j + dy[k];
					int v = m * x + y;
					if (g[x][y] != 1)	addEdge (u, v, 1);
				}
			}
			if (g[i][j] == 1) {
				addEdge (SS, u, 4);
				for (int k = 0; k < 4; k++) {
					int x = i + dx[k], y = j + dy[k];
					int v = m * x + y;
					if (g[x][y] != 1 ) 	addEdge (u, v, 1);
				}
			}
		}
	}
}
int cs;
int main() {
	/*
	       ��ͼ,ǰ���Ǵ�ߣ���ͷ��pHead[],�߼��� nCnt.
	       SS,ST�ֱ�ΪԴ��ͻ��
	*/
	scanf ("%d", &cs);
	while (cs--) {
		build();
		printf ("%d\n", SAP (SS, ST, n * m + 1) );
	}
	return 0;
}

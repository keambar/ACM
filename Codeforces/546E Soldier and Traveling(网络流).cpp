#include <bits/stdc++.h>
#define LL long long
using namespace std;
#define ms(a,b) memset(a,b,sizeof a)
using namespace std;
const int INF = 3111;
struct node {
	int u, v, c, next;
} edge[INF*INF];
int  pHead[INF*INF], SS, ST, nCnt = 1;
int n, m;
//ͬʱ��ӻ��ͷ����, ����߳�ʼ����Ϊ0
void addEdge (int u, int v, int c) {
	edge[++nCnt].v = v; edge[nCnt].c = c, edge[nCnt].next = pHead[u]; pHead[u] = nCnt;
	edge[nCnt].u = u;
	edge[++nCnt].v = u; edge[nCnt].c = 0, edge[nCnt].next = pHead[v]; pHead[v] = nCnt;
	edge[nCnt].u = v;
}
int SAP (int pStart, int pEnd, int N) {
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

int out[INF][INF];
int s[INF], t[INF];
int need;
int main() {
	ios::sync_with_stdio (0);

	cin >> n >> m;
	SS = 0, ST = n * 2 + 1;
	int tem=0;
	for (int i = 1; i <= n; ++i) {
		cin >> s[i];
		tem+=s[i];
		addEdge (SS, i, s[i]);
		addEdge (i, i + n, s[i]);
	}
	for (int i = 1; i <= n; ++i) {
		cin >> t[i];
		need += t[i];
		addEdge (n + i, ST, t[i]);
	}
	for (int i = 1, u, v; i <= m; ++i) {
		cin >> u >> v;
		addEdge (u, n + v, s[u]);
		addEdge (v, n + u, s[v]);
	}
	int ans = SAP (SS, ST, 2 * n + 1);
	if (ans != need||tem!=need) {
		cout << "NO" << endl;
		return 0;
	}
	cout << "YES" << endl;
	for (int i = 3; i <= nCnt; i += 2) {
		int u = edge[i].u - n, v = edge[i].v;
		if (v <= n && u <= n)
			out[v][u] += edge[i].c;
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cout << out[i][j] << ' ';
		}
		cout << endl;
	}
}
#include <iostream>
#include <algorithm>
#include <vector>

#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef long long L;
typedef vector<L> VL;
typedef vector<VL> VVL;
typedef pair<int, int> PII;
typedef vector<PII> VPII;

const L INF = numeric_limits<L>::max() / 4;

struct MinCostMaxFlow {
	int N;
	VVL cap, flow, cost;
	VI found;
	VL dist, pi, width;
	VPII dad;

	MinCostMaxFlow(int N) :
		N(N), cap(N, VL(N)), flow(N, VL(N)), cost(N, VL(N)),
		found(N), dist(N), pi(N), width(N), dad(N) {}

	void AddEdge(int from, int to, L cap, L cost) {
		this->cap[from][to] = cap;
		this->cost[from][to] = cost;
	}

	void Relax(int s, int k, L cap, L cost, int dir) {
		L val = dist[s] + pi[s] - pi[k] + cost;
		if (cap && val < dist[k]) {
			dist[k] = val;
			dad[k] = make_pair(s, dir);
			width[k] = min(cap, width[s]);
		}
	}

	L Dijkstra(int s, int t) {
		fill(found.begin(), found.end(), false);
		fill(dist.begin(), dist.end(), INF);
		fill(width.begin(), width.end(), 0);
		dist[s] = 0;
		width[s] = INF;

		while (s != -1) {
			int best = -1;
			found[s] = true;
			for (int k = 0; k < N; k++) {
				if (found[k]) continue;
				Relax(s, k, cap[s][k] - flow[s][k], cost[s][k], 1);
				Relax(s, k, flow[k][s], -cost[k][s], -1);
				if (best == -1 || dist[k] < dist[best]) best = k;
			}
			s = best;
		}

		for (int k = 0; k < N; k++)
			pi[k] = min(pi[k] + dist[k], INF);
		return width[t];
	}

	pair<L, L> GetMaxFlow(int s, int t) {
		L totflow = 0, totcost = 0;
		while (L amt = Dijkstra(s, t)) {
			totflow += amt;
			for (int x = t; x != s; x = dad[x].first) {
				if (dad[x].second == 1) {
					flow[dad[x].first][x] += amt;
					totcost += amt * cost[dad[x].first][x];
				}
				else {
					flow[x][dad[x].first] -= amt;
					totcost -= amt * cost[x][dad[x].first];
				}
			}
		}
		return make_pair(totflow, totcost);
	}
};
int main()
{
	MinCostMaxFlow flow(14);
	
	flow.AddEdge(0, 1, 3, 2);
	flow.AddEdge(0, 2, 5, 4);
	flow.AddEdge(0, 3, 10, 5);


	flow.AddEdge(1, 4, 3, 4);
	flow.AddEdge(1, 5, 5, 5);
	flow.AddEdge(1, 6, 10, 2);

	flow.AddEdge(2, 4, 3, 4);
	flow.AddEdge(2, 5, 5, 2);
	flow.AddEdge(2, 6, 10, 5);

	flow.AddEdge(3, 4, 3, 2);
	flow.AddEdge(3, 5, 5, 5);
	flow.AddEdge(3, 6, 10, 4);


	flow.AddEdge(4, 7, 3, 5);
	flow.AddEdge(4, 8, 5, 2);
	flow.AddEdge(4, 9, 10, 4);

	flow.AddEdge(5, 7, 3, 2);
	flow.AddEdge(5, 8, 5, 5);
	flow.AddEdge(5, 9, 10, 2);

	flow.AddEdge(6, 7, 3, 2);
	flow.AddEdge(6, 8, 5, 4);
	flow.AddEdge(6, 9, 10, 5);


	flow.AddEdge(7, 10, 3, 2);
	flow.AddEdge(7, 11, 5, 5);
	flow.AddEdge(7, 12, 10, 2);

	flow.AddEdge(8, 10, 3, 2);
	flow.AddEdge(8, 11, 5, 4);
	flow.AddEdge(8, 12, 10, 5);

	flow.AddEdge(9, 10, 3, 2);
	flow.AddEdge(9, 11, 5, 4);
	flow.AddEdge(9, 12, 10, 2);


	flow.AddEdge(10, 13, 3, 4);

	flow.AddEdge(11, 13, 3, 5);

	flow.AddEdge(12, 13, 3, 2);

	flow.AddEdge(0, 13, 9, 1);

	pair<L, L> p = flow.GetMaxFlow(0, 13);

	cout << p.first << " " << p.second << endl;
}
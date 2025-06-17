#include <cpp-util.h>


vector<i64> dijkstra(vector<vector<pair<int, i64>>> graph, int source) {
  int n = graph.size();
  i64 inf = 1e18;
  vector<i64> dist(n, inf);
  dist[source] = 0;
  priority_queue<pair<i64, int>, vector<pair<i64, int>>, greater<>> pq;
  vector<bool> vis(n, false);
  pq.emplace(dist[source], source);
  while (!pq.empty()) {
    i64 d = pq.top().first;
    int u = pq.top().second;
    pq.pop();
    if (vis[u]) {
      continue;
    }
    vis[u] = true;
    for (auto &[v, w]: graph[u]) {
      if (dist[v] > d + w) {
        dist[v] = d + w;
        pq.emplace(dist[v], v);
      }
    }
  }
  return dist;
}

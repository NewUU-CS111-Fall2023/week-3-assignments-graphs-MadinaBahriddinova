#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 1e9;

vector<vector<int>> graph;
vector<vector<int>> forbidden;
vector<int> dist;
vector<int> pred;
vector<int> path;

bool isValidTriple(int a, int b, int c) {
    for (int i = 0; i < forbidden.size(); i++) {
        if (forbidden[i][0] == a && forbidden[i][1] == b && forbidden[i][2] == c)
            return false;
    }
    return true;
}

void shortestPath(int source, int destination) {
    dist[source] = 0;
    pred[source] = -1;

    queue<int> q;
    q.push(source);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        for (int neighbor : graph[curr]) {
            if (dist[neighbor] == INF) {
                dist[neighbor] = dist[curr] + 1;
                pred[neighbor] = curr;
                q.push(neighbor);
            }
        }
    }

    if (dist[destination] == INF) {
        cout << -1 << endl;
        return;
    }

    int curr = destination;
    while (curr != -1) {
        path.push_back(curr);
        curr = pred[curr];
    }

    reverse(path.begin(), path.end());

    cout << dist[destination] << endl;
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << " ";
    }
    cout << endl;
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    graph.resize(n + 1);
    dist.assign(n + 1, INF);
    pred.assign(n + 1, -1);

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    forbidden.resize(k);
    for (int i = 0; i < k; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        forbidden[i] = {a, b, c};
    }

    shortestPath(1, n);

    return 0;
}

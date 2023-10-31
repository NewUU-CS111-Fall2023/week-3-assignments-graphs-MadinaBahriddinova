#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int inf = 1e9;

vector<vector<int>> graph;
vector<vector<int>> forbidden;
vector<int> dist;
vector<int> pred;
vector<int> path;

bool isValidTriple(int x, int y, int z) {
    for (int i = 0; i < forbidden.size(); i++) {
        if (forbidden[i][0] == x && forbidden[i][1] == y && forbidden[i][2] == z)
            return false;
    }
    return true;
}

void shortestWay(int source, int destination) {
    dist[source] = 0;
    pred[source] = -1;

    queue<int> q;
    q.push(source);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int beside : graph[current]) {
            if (dist[beside] == inf) {
                dist[beside] = dist[current] + 1;
                pred[beside] = current;
                q.push(beside);
            }
        }
    }

    if (dist[destination] == inf) {
        cout << -1 << endl;
        return;
    }

    int current = destination;
    while (current != -1) {
        path.push_back(current);
        current = pred[current];
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
    dist.assign(n + 1, inf);
    pred.assign(n + 1, -1);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    forbidden.resize(k);
    for (int i = 0; i < k; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        forbidden[i] = {x, y, z};
    }

    shortestWay(1, n);

    return 0;
}

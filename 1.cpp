#include <iostream>
#include <vector>
#include <queue>
#include <climits> // INT_MAX 정의하기 위함

using namespace std;

typedef pair<int, int> pii; // 첫번째는 거리, 두번째는 정점 번호

void dijkstra(vector<vector<pii>> &graph, int source)
{
    int n = graph.size();
    vector<int> dist;
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    dist[source];
    pq.push({0, source});

    while (!pq.empty())
    {

        int currDist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (currDist > dist[u])
        {
            continue;
        }

        for (auto &neighber : graph[u])
        {
            int v = neighber.first;
            int weight = neighber.second;

            if (currDist + weight < dist[v])
            {
                dist[v] = currDist + weight;
                pq.push({dist[v], v});
            }
        }
    }
    // 결과 출력
    for (int i = 0; i < n; ++i)
    {
        if (dist[i] == INT_MAX)
        {
            cout << "Vertex " << i << ": Unreachable" << endl;
        }
        else
        {
            cout << "Vertex " << i << ": " << dist[i] << endl;
        }
    }
}

int main()
{
    int n = 5;
    vector<vector<pii>> graph(n);

    graph[0].push_back({1, 10});
    graph[0].push_back({2, 5});
    graph[1].push_back({2, 2});
    graph[1].push_back({3, 1});
    graph[2].push_back({1, 3});
    graph[2].push_back({3, 9});
    graph[2].push_back({4, 2});
    graph[3].push_back({4, 4});
    graph[4].push_back({0, 7});
    graph[4].push_back({3, 6});

    int source = 0;
    dijkstra(graph, source);

    return 0;
}

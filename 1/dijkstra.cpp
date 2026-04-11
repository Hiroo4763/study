#include <iostream>
#include <vector>
#include <queue>
#include <climits> // INT_MAX 정의하기 위함

using namespace std;

typedef pair<int, int> pii; // 첫번째는 거리, 두번째는 정점 번호

void dijkstra(vector<vector<pii>>& graph, int source) {
    int n = graph.size();
    vector<int> dist;
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    dist[source];
    pq.push({ 0, source });

    while (!pq.empty()){

        int currDist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (currDist > dist[u]) {
            continue;
        }

        for (auto& neighber : graph[u]) {
            int v = neighber.first;
            int weight = neighber.second;

            if (currDist + weight < dist[v]) {
                dist[v] = currDist + weight;
                pq.push({ dist[v], v });
            }
        }
 
    }
    // 결과 출력
    for (int i = 0; i < n; ++i) {
        if (dist[i] == INT_MAX) {
            cout << "Vertex " << i << ": Unreachable" << endl;
        }
        else {
            cout << "Vertex " << i << ": " << dist[i] << endl;
        }
    }
}

int main() {
    int n = 5;
    vector<vector<pii>> graph(n);

    graph[0].push_back({ 1, 10 });
    graph[0].push_back({ 2, 5 });
    graph[1].push_back({ 2, 2 });
    graph[1].push_back({ 3, 1 });
    graph[2].push_back({ 1, 3 });
    graph[2].push_back({ 3, 9 });
    graph[2].push_back({ 4, 2 });
    graph[3].push_back({ 4, 4 });
    graph[4].push_back({ 0, 7 });
    graph[4].push_back({ 3, 6 });

    int source = 0;
    dijkstra(graph, source);

    return 0;
}

/*
#include <iostream>
#include <vector>
#include <queue>
#include <climits> // INT_MAX 정의하기 위함

using namespace std;

typedef pair<int, int> pii; // 첫번째는 거리, 두번째는 정점 번호

void dijkstra(vector<vector<pii>>& graph, int source) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX); // 거리 배열 초기화 (무한대로 설정)
    priority_queue<pii, vector<pii>, greater<pii>> pq; // 우선순위 큐

    // dist: 최단 거리를 기록하는 배열
    dist[source] = 0; // 출발점의 거리는 0
    pq.push({ 0, source }); // (거리, 정점) 형태로 큐에 삽입

    while (!pq.empty()) {
        // HINT
        // pq.top() -> 큐의 맨 앞에 있는 요소
        // pq.top().first -> 큐의 맨 앞에 있는 요소의 첫번째 값
        // pq.top().second -> 큐의 맨 앞에 있는 요소의 두번째 값

        // 여기에 프로그램을 작성하시오


        // graph[u] 벡터의 각 (v, weight) 쌍을 반복하여 하나씩 neighbor로 가져옴
        // HINT: pq.push() -> 큐에 값 삽입
        for (auto& neighbor : graph[u]) {
            // 여기에 프로그램을 작성하시오

        }
    }
}

// 결과 출력
for (int i = 0; i < n; ++i) {
    if (dist[i] == INT_MAX) {
        cout << "Vertex " << i << ": Unreachable" << endl;
    }
    else {
        cout << "Vertex " << i << ": " << dist[i] << endl;
    }
}
}

int main() {
    // 그래프 생성 (인접 리스트 형태)
    int n = 5; // 정점 수
    vector<vector<pii>> graph(n);

    // 간선 추가: 
    graph[0].push_back({ 1, 10 }); // 0번 정점에서 1번 정점으로 가는 거리 10
    graph[0].push_back({ 2, 5 });
    graph[1].push_back({ 2, 2 });
    graph[1].push_back({ 3, 1 });
    graph[2].push_back({ 1, 3 });
    graph[2].push_back({ 3, 9 });
    graph[2].push_back({ 4, 2 });
    graph[3].push_back({ 4, 4 });
    graph[4].push_back({ 0, 7 });
    graph[4].push_back({ 3, 6 });

    int source = 0; // 출발 정점
    dijkstra(graph, source);

    return 0;
}


// HINT 채우기
        int currDist = pq.top().first;   // 현재 거리
        int u = pq.top().second;  // 현재 정점
        pq.pop();

        // 이미 더 짧은 경로가 존재하면 무시 (중복 제거)
        if (currDist > dist[u])
            continue;

        // graph[u]의 각 (v, weight) 검사
        for (auto& neighbor : graph[u]) {
            int v = neighbor.first;   // 이웃 정점 번호
            int weight = neighbor.second;   // 가중치

            // 새로운 거리 계산

            // 더 짧은 거리 발견 시 갱신
            if (currDist + weight < dist[v]) {
                dist[v] = currDist + weight;
                pq.push({ dist[v], v});
            }
        }


*/
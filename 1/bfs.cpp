#include <iostream>
#include <queue>

using namespace std;

void bfs(int graph[8][8], int n, int start) {
    bool visited[8] = { false }; // 방문 여부를 추적하는 배열
    queue<int> q;              // BFS 큐

    // 여기에 코드를 작성하시오.
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        cout << curr + 1 << " ";

        for (int i = 0; i < n; i++) {
            if (graph[curr][i] == 1 && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
}

int main() {
    int n = 8;
    int start = 0;
    int graph[8][8] = {
        // 여기에 코드를 작성하세요.
        {0,0,0,1,0,0,1,0},
        {0,0,0,0,1,1,0,0},
        {0,0,0,0,0,0,1,0},
        {1,0,0,0,0,1,0,0},
        {0,1,0,0,0,1,0,0},
        {0,1,0,1,1,0,0,0},
        {1,0,1,0,0,0,0,1},
        {0,0,0,0,0,0,1,0}
    };

    bfs(graph, n, start); // bfs 함수 인자 : 그래프(2차원 행렬), BFS 노드 수, BFS 시작 노드

    return 0;
}


/*
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        cout << curr + 1 << " ";

        for (int i = 0; i < n; i++) {
            if (graph[curr][i] == 1 && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
    */
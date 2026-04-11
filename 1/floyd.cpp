#include <iostream>
#include <vector>
using namespace std;

const int INF = 1e9;

int main() {
    // 정점 수 (1~6)
    int V = 6;
    vector<vector<int>> dist(V + 1, vector<int>(V + 1, INF));

    // 자기 자신까지의 거리는 0
    for (int i = 1; i <= V; i++) {
        dist[i][i] = 0;
    }
    // 문제 그림의 간선 그대로 입력
    // 1-2(2), 1-3(5), 1-4(1)
    // 2-3(3)
    // 3-4(2), 3-5(1), 3-6(5)
    // 4-5(1)
    // 5-6(2)

    dist[1][2] = dist[2][1] = 2;
    dist[1][3] = dist[3][1] = 5;
    dist[1][4] = dist[4][1] = 1;

    dist[2][3] = dist[3][2] = 3;

    dist[3][4] = dist[4][3] = 2;
    dist[3][5] = dist[5][3] = 1;
    dist[3][6] = dist[6][3] = 5;

    dist[4][5] = dist[5][4] = 1;

    dist[5][6] = dist[6][5] = 2;

    // Floyd-Warshall
    for (int k = 1; k <= V; k++) {
        for (int i = 1; i <= V; i++) {
            for (int j = 1; j <= V; j++) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // 결과 출력
    for (int i = 1; i <= V; i++) {
        for (int j = 1; j <= V; j++) {
            if (dist[i][j] >= INF) cout << "INF ";
            else cout << dist[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}

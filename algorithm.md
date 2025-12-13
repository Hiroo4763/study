# 이진탐색트리

삽입

3가지 경우의 수를 생각한다.

``` C++
function bst.insert(x)
    set node = bst.root          // root에서 시작합니다.
    set parent = bst.root        // parent도 root로 설정하고 시작합니다.

    while node != null           // node가 null이 되기 전까지 반복합니다.
        parent = node            // parent는 항상 node가 움직이기 직전의 위치로 갱신해줍니다. 
        if node.value > x        // node에 적혀있는 값이 x보다 크다면
            node = node.left     // 왼쪽 자식으로 이동해야 합니다. 
        else                     // node에 적혀있는 값이 x보다 작다면
            node = node.right    // 오른쪽 자식으로 이동해야 합니다.
    
    if parent == null            // Case 1. 비어있는 tree라면
        bst.root = node(x)       // root를 node(x)로 설정해줍니다.
    else if parent.value > x     // Case 2. parent에 적혀있는 값이 추가하려는 값 x보다 크다면
        parent.left = node(x)    // parent의 왼쪽에 node(x)를 넣어줍니다.
    else                         // Case 3. parent에 적혀있는 값이 추가하려는 값 x보다 작다면
        parent.right = node(x)   // parent의 오른쪽에 node(x)를 넣어줍니다.
```

삭제

``` c++
function bst.search(x)
    set node = bst.root                     
    while node != null and node.value != x 
        if node.value > x                
            node = node.left           
        else                               
            node = node.right           
    
    return node            

function bst.minimum(node)                  // node 하위 트리에서 최솟값을 구합니다.
    while node.left != null                 // node의 left가 null이 아니면 계속 내려갑니다.
        node = node.left
    return node                             // 최종 node의 위치를 반환합니다.

function bst.delete(x)                      // x를 찾아 삭제하는 함수입니다.
    set node = bst.search(x)                // x 값을 찾습니다.
    
    if node.left == null                    // Case 1. node의 왼쪽 자식이 비어있다면
        move(node.right, node)              // 오른쪽 자식을 위로 올려줍니다.
    else if node.right == null              // Case 2. node의 오른쪽 자식이 비어있다면
        move(node.left, node)               // 왼쪽 자식을 위로 올려줍니다.
    else                                    // Case 3. 왼쪽 오른쪽 자식이 모두 채워져있다면
        set succ = bst.minimum(node.right)  // 해당 노드의 successor를 구합니다.
                                            // 이는 현재 노드의 오른쪽 자식에서 시작하여 계속 왼쪽으로 내려가는 것을
                                            // 반복하면 가능합니다.
        if succ == node.right               // 만약 successor가 현재 노드의 오른쪽 자식이라면 
            move(node.right, node)          // 오른쪽 자식을 위로 올려줍니다.
        else                                // 그렇지 않은 일반적인 경우라면
            node.value = succ.value         // node의 값을 successor의 값으로 대체시켜준 뒤,
            move(succ.right, succ)          // successor의 오른쪽 자식을 위로 끌어올려줍니다.
```

최악 O(n)
평균 O(log n)

균형잡힌 BST 쓰면 항상 log n

# 힙

삽입
``` C++
function insert(arr[], n, x)
  arr.append(x)                          // 가장 끝에 노드 x를 추가합니다.

  set i = n + 1                          // 마지막 노드에서 시작합니다.
  while i > 1 and arr[i / 2] < arr[i]    // 부모가 자식보다 값이 작은 경우라면
                                         // max-heap 조건에 어긋나므로
    swap(arr[i], arr[i / 2])             // 두 값을 교환하고
    i = i / 2                            // 부모 위치로 올라갑니다.
```

삭제
```C++
function heapify(arr[], n, i)
  set largest = i                     // 최대 노드가 i번이라고 가정합니다.
  set l = i * 2                       // 왼쪽 자식 노드 번호입니다.
  set r = i * 2 + 1                   // 오른쪽 자식 노드 번호입니다.

  if l <= n && arr[l] > arr[largest]  // 왼쪽 자식이 크다면, 최대 번호를 수정합니다.
    largest = l

  if r <= n && arr[r] > arr[largest] // 오른쪽 자식이 크다면, 최대 번호를 수정합니다.
    largest = r

  if largest != i                   // 최대 노드가 자식 노드라면
    swap(arr[i], arr[largest])      // 해당 자식과 현재 노드를 교환해준 뒤
    heapify(arr, n, largest)        // 내려간 위치에서 다시 heapify를 진행합니다.

function remove(arr[], n)
  arr[1] = arr[n]                   // 가장 끝에 있는 노드를 첫 번째 노드에 옮겨주고
  delete arr[n]                     // 가장 마지막 노드를 삭제합니다.
  heapify(arr, n - 1, 1)            // 직후에 1번 노드를 기준으로 heapify를 진행하여
                                    // max-heap 상태를 계속 유지해줍니다. 
```

# DP

## 가장 긴 증가하는 부분 수열

그러니까, i번째 원소보다 작은 값이면서 가장 긴 dp[i] 값에 + 1을 해주면 됨
```c++
[20, 80, 10, 50, 55, 20, 60, 70, 5, 90]
```
DP[i] = max(DP[j] + 1) // j는 i 이전 값들

## 아이템을 적절히 고르는 문제

i원을 만들기 위해 마지막 동전으로 coin[j]을 사용했다고 가정하면
이전에는 i - coin[j]원을 만들어야 한다
- coin[j]보다 i가 작다면 그 동전을 쓸 수 없다
- coin[j]보다 i가 크다면 가능한 경우들 중 최소값을 선택해야 한다

DP[i] = min(DP[i - coin[j]] + 1)

그러니까, 구할 금액에서 경우의 수(1, 4, 5)를 뺀 값을 테이블에서 찾아서 + 1한다.

## Knapsack

dp[i][j] = i번째 보석까지 고려했을 때, 총 무게가 j일 때 얻을 수 있는 최대 가치. 두 가지 경우의 수를 생각하면된다.

1. 보석 i를 선택한다. (+value을 해줘야함)
2. 보석 i를 선택하지 않는다.

**이 둘을 꼭 비교해서 큰 값으로 정할것**

테이블에서 가장 큰 값을 찾아서 알잘딱 한다. 

## String Matching
dp[i][j] = A의 앞 i글자와 B의 앞 j글자를 비교했을 때 만들어지는 LCS 길이

CASE 1: 글자가 같으면 → LCS 1 증가
CASE 2: 글자가 다르면 → 둘 중 큰 값 선택

## Greedy Algorithm

-------------------------------------------------------------------

# 그래프

## DFS

```
시간복잡도  V+E
```

## BFS

```
시간복잡도  V+E
```

**큐를 따라가는거다**
정점 방문 후, 큐에 넣는다. 큐에 넣고 큐에서 빠지면 그 주변 정점을 큐에 넣는다(숫자 낮은 순)

# Dijkstra
다익스트라는 하나의 정점에서 시작하여 모든 정점까지의 최단 거리를 구하는 알고리즘이다. 우선순위 큐(힙)을 사용한다.

*V는 정점 수*
*E는 간선 수*

``` 
시간복잡도  O(E log V), 또는 O(V^2)
```

### 주요코드
``` C++
void dijkstra(vector<vector<pii>>& graph, int source) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX); // 거리 배열 초기화 (무한대로 설정)
    priority_queue<pii, vector<pii>, greater<pii>> pq; // 우선순위 큐

    dist[source] = 0; // 출발점의 거리는 0
    pq.push({0, source}); // (거리, 정점)

    while (!pq.empty()) {

        // HINT 채우기
        int currDist = pq.top().first;   // 현재 거리
        int u        = pq.top().second;  // 현재 정점
        pq.pop();

        // 이미 더 짧은 경로가 존재하면 무시 (중복 제거)
        if (currDist > dist[u])
            continue;

        // graph[u]의 각 (v, weight) 검사
        for (auto& neighbor : graph[u]) {
            int v = neighbor.first;      // 이웃 정점 번호
            int weight = neighbor.second; // 가중치

            // 새로운 거리 계산
            int newDist = currDist + weight;

            // 더 짧은 거리 발견 시 갱신
            if (newDist < dist[v]) {
                dist[v] = newDist;
                pq.push({newDist, v});
            }
        }
    }
}
```

``` C++
function dijkstra(graph, source)
    set Q = Queue()

    for each vertex in graph
        set dist[v] = (1)
        Q.push(v)

    set dist[source] = (2)

    while Q is not empty
        set u = vertex in Q with min dist
        Q.remove((3))

        for each neighbor v of u
            set alt = dist[u] + length(u, v)
            if alt (4) dist[v]
                set dist[v] = (5)
```



### 특징
- 하나의 출발점에서 모든 정점까지 최단 거리를 구함
- 우선순위 큐(힙)을 사용하면 매우 빠름
- 희소 그래프(Sparse)일 때 성능이 최적 (E log V 구조)
- 음수 간선 불가 
- 출발점이 여러 개면 정점을 바꿔서 여러 번 수행해야 함
- 플로이드에 비해 구현 복잡도가 약간 높음 (큐 사용)

---------------------------------------------------------------

# Floyd-Warshall

다익스트라가 정점 대 정점 최소 거리를 구한다면, 플로이드는 각 정점별로 정점마다 최소 거리를 구한다.
```
시간복잡도 |V|^3
```
정점 수 V가 작을 때(보통 400 이하) 매우 효율적이며,
그래프 형태(Dense/Sparse)에 상관 없이 일정한 성능을 유지한다.

### 주요코드
``` C++
for (int k = 1; k <= V; k++) { // 경유할 정점
    for (int i = 1; i <= V; i++) { // 출발점
        for (int j = 1; j <= V; j++) {  // 도착점
            if (dist[i][j] > dist[i][k] + dist[k][j]) { // 만약 경유 지점을 포함한 경로가 더 작다면,
                dist[i][j] = dist[i][k] + dist[k][j]; // 대입
            }
        }
    }
}
```

### 특징

- 단순함.
- 만약 밀집 형태라면 다익스트라보다 빠를 가능성 높음
- 한 번의 알고리즘 수행만으로 모든 정점의 최단 경로를 찾음
- 음수 간선 허용
- 결과 조회가 O(1)


---------------------------------------------------------------

# Kruskal


## MST(Minimum Spanning Tree)

> Spannig Tree : N개의 정점, N-1개의 간선을 가지고 있고, 사이클이 없음 <-- 그냥 트리랑 똑같은듯?

가중치가 있을때 최소한의 비용을 사용한 Spanning Tree를 MST라고 부름


### 특징
- MST도 여러개가 나올 수도 있음
- 크루스컬이나 프림이든 뭘 쓰든 MST의 가중치 합은 항상 동일하다.

## Union-find
원소들을 집합으로 묶고, 두 원소가 같은 집합에 속하는지를 매우 빠르게 판단하는 자료구조

```
시간복잡도 O(N), 개선된 알고리즘 사용시 O(log N)
```

``` C++
// 개선 전 Union-find
function union(x, y)
  set X = find(x), Y = find(y)
  uf[X] = Y

function find(x)
  if uf[x] == x        // x가 루트 노드라면
    return x           // x 값을 반환합니다.
  return find(uf[x])   // x가 루트 노드가 아니라면, x의 부모인 uf[x]에서 더 탐색을 진행합니다.
```

개선책은 find를 호출할 때 조상을 찾아내면, 현재 값의 부모값을 조상으로 바꾼다.

``` C++
// 개선 후 Union-find(경로 압축)
function find(x)
  if uf[x] == x                 // x가 루트 노드라면
    return x                    // x 값을 반환합니다.
  set root_node = find(uf[x])   // x가 루트 노드가 아니라면, x의 부모인 uf[x]에서 더 탐색을 진행합니다.
  uf[x] = root_node             // 노드 x에 부모를 루트 노드로 설정해줍니다.
  return root_node              // 찾아낸 루트 노드를 반환합니다.

```


## 크루스컬

결국 MST를 만들기 위해 크루스컬 알고리즘이 필요한것. Union-find를 이용하여 MST를 만든다.

크루스칼은 간선의 가중치가 작은 것부터 순서대로 보면서 해당 간선 양 끝에 있는 두 노드 x, y에 대해 find(x), find(y)값을 비교하여 일치하지 않는 경 우에만 간선을 선택해주고 union(x, y)를 진행해주는 식으로 계속 진행한다.

```
시간복잡도 O(E log E).
(간선 정렬 O(E log E), 간선 Union-find O(log N))
```

### 주요코드

``` C
function kruskal()
    mst = []                       // mst를 담을 배열입니다.
    sort edge[] by length          // 간선을 가중치 기준으로 오름차순 정렬합니다.
    uf = uf_init(|V|)              // uf 배열을 노드의 수 |V|만큼 초기화합니다.

    for E in edge[]                // 각각의 간선에 대해 
        u, v = E                   // 간선을 이루고 있는 두 노드 u, v를 보며
        if find(u) != find(v)      // u, v의 루트 노드가 다른 경우에만
            mst.push(E)            // mst에 해당 간선을 넣어주고
            union(u, v)            // u, v를 같은 루트 노드를 갖도록 만들어줍니다.
    
    return mst
```

# Prim

전체에서 간선을 선택하는 크루스컬과 반대로, 프림 알고리즘은 한 지점에서 시작하여 점점 확장하는 방법 **다익스트라**랑 매우 비슷함, 간선을 정한다 정도 차이

```
시간복잡도 O(E log V)
```

### 주요코드
``` C++
function prim(graph)                          // 그래프와 시작점 정보가 주어집니다.
    set Q = Queue()                           // 우선순위 큐를 만들어줍니다.

    for each vertex in graph                  // 그래프에 있는 모든 노드들에 대해
        set dist[v] = INF                     // 초기값을 전부 아주 큰 값으로 설정해주고 
        Q.push(v)                             // 우선순위큐에 각 노드를 넣어줍니다.
    set source = |V|                          // 시작점을 임의로 마지막 노드로 설정합니다.
    set dist[source] = 0                      // 시작점 대해서만 dist 값을 0으로 초기화해줍니다.
    while Q is not empty                      // 우선순위 큐가 비어있지 않을 때까지 반복합니다.
        set u = vertex in Q with min dist     // 우선순위 큐에서 dist값이 가장 작은 노드를 선택합니다.
        Q.remove(u)                           // 우선순위 큐에서 해당 노드를 제거해줍니다.

        for each neighbor v of u              // u번 노드와 연결된 노드들을 전부 살펴보면서
            set alt = length(u, v)            // *핵심* 간선 가중치를 확인
            if alt < dist[v]                  // 기존 dist값보다 더 alt값이 작다면
                set dist[v] = alt             // dist값을 갱신해줍니다.
```


### 특징
- 다익스트라 알고리즘과 아예 동일(단, dist 배열의 정의가 다익스트라랑 다름 dist[x]는 현재까지 만들어진 MST와 노드 x를 연결하기 위해 필요한 최소 비용. !!누적거리가 아님)
- 다익스트라랑 2줄 차이
- 우선순위 큐 사용
- dist 값 중 최소인 값이 여러개라면 아무거나 선택해도 된다.
- 간선을 보는거다 명심하자 


# Topological Sort (위상 정렬)

방향성 그래프가 있고 앞에 일이 끝나야 뒤에 일이 진행 될 수 있는 문제라면? 가능한 순서들 중 하나를 뽑아주는 방법

크게 두 가지 방법
1. DFS 이용
2. in-degree를 이용

## DFS 이용
stack을 이용하여 구현, 모든 탐색이 진행된 이후에는 stack에서 순서대로 값을 빼내어준 순서가 위상정렬 순서

```
시간복잡도 O(V + E)
```

### 특징
- 1번 정점부터 n번 정점까지 순서대로 보면서 아직 방문한 적이 없는 정점에 대해서는 dfs를 추가적으로 진행해 줘야함

## in-degree 이용
큐를 이용하여 구현, in-degree란 정점마다 해당 정점으로 들어오는 간선의 수를 의미. in-degree가 0인 지점이 항상 시작점

```
시간복잡도 O(V + E)
```

그래프에서 in-degree가 0인 지점을 전부 queue에 넣고 시작합니다. 이
그래프에서는 1번 정점만이 처음 in-degree 값이 0이므로 1번 정점을 queue
에 넣어주게 됩니다.

이제 queue에서 가장 앞에 있는 값을 뽑아, 해당 정점에 연결되어 있는 모든 간
선을 살펴봅니다. 이때, 해당 간선이 가리키는 곳에 있는 정점의 in-degree를 1
감소시켜줍니다.

### 특징
- 무방향 그래프에서 사용 X
- 사이클을 이루는 그래프에서 사용 X
- 사이클 탐지가 쉬움
- 큐를 사용(배열 뭐시기하면 우선순위 큐 사용)
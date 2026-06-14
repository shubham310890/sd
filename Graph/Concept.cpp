/*1. Normal BFS Topological Sort Template
Use this when you need:

- Check if graph has cycle
- Return topological order
- Longest path in DAG
- DP on dependency graph

*/
vector<int> topoSort(int n, vector<pair<int, int>> &edges) {
    vector<vector<int>> graph(n + 1);
    vector<int> indegree(n + 1, 0);

    // edge: u -> v
    for (auto &edge : edges) {
        int u = edge.first;
        int v = edge.second;

        graph[u].push_back(v);
        indegree[v]++;
    }

    queue<int> q;

    // Start with all nodes having no dependency
    for (int node = 1; node <= n; node++) {
        if (indegree[node] == 0) {
            q.push(node);
        }
    }

    vector<int> topoOrder;

    while (q.empty() == false) {
        int current = q.front();
        q.pop();

        topoOrder.push_back(current);

        for (int next : graph[current]) {
            indegree[next]--;

            if (indegree[next] == 0) {
                q.push(next);
            }
        }
    }

    // Cycle exists
    if (topoOrder.size() != n) {
        return {};
    }

    return topoOrder;
}

/*Mental model 

Process one available node.
Remove its dependency effect from next nodes.
If some next node becomes dependency-free, push it into queue.

2. Queue Size Based Topological Sort Template

Use this when one BFS level has meaning, like:

- Minimum semesters
- Parallel task batches
- Which tasks can run together
- Dependency levels
*/
int topoSortByLevels(int n, vector<pair<int, int>> &edges) {
    vector<vector<int>> graph(n + 1);
    vector<int> indegree(n + 1, 0);

    // edge: u -> v
    for (auto &edge : edges) {
        int u = edge.first;
        int v = edge.second;

        graph[u].push_back(v);
        indegree[v]++;
    }

    queue<int> q;

    for (int node = 1; node <= n; node++) {
        if (indegree[node] == 0) {
            q.push(node);
        }
    }

    int completed = 0;
    int levels = 0;

    while (q.empty() == false) {
        int size = q.size();

        // One queue level starts here
        levels++;

        for (int i = 0; i < size; i++) {
            int current = q.front();
            q.pop();

            completed++;

            for (int next : graph[current]) {
                indegree[next]--;

                if (indegree[next] == 0) {
                    q.push(next);
                }
            }
        }
    }

    // Cycle exists
    if (completed != n) {
        return -1;
    }

    return levels;
}
/*
Mental model
All nodes currently in queue can be processed together.
Newly unlocked nodes are pushed into queue.
But they are processed in next while iteration.

Use this for:

Minimum semesters
Minimum rounds
Parallel execution batches
Dependency stages
*/

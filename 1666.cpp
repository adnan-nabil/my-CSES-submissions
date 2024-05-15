#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> graph(100000);
int visited[100000 + 2];

void dfs(int vertex)
{
    visited[vertex] = 1;

    for (auto child : graph[vertex])
    {
        if (visited[child] == 0)
        {
            dfs(child);
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int count = 0;
    vector<int> v;
    for (int i = 1; i <= n; i++)
    {
        if (visited[i] == 0)
        {
            v.push_back(i);
            count += 1;
            dfs(i);
        }
    }

    cout << count - 1 << endl;
    for (int i = 0; i < v.size() - 1; i++)
    {
        cout << v[i] << " " << v[i + 1] << endl;
    }
}
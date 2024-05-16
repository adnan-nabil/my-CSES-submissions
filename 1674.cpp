#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> graph(200005);
int visited[200005];
int answer[200005];

void dfs(int vertex)
{
    visited[vertex] = 1;
    if (graph[vertex].size() == 1)
    {
        answer[vertex] = 0;
    }

    for (auto child : graph[vertex])
    {
        if (visited[child] == 0)
        {
            dfs(child);
            answer[vertex] += answer[child] + 1;
        }
    }
}

int main()
{
    int n;
    cin >> n;
    int a[n + 5];
    a[0] = -1;
    a[1] = -1;
    for (int i = 2; i <= n; i++)
    {
        cin >> a[i];
        graph[i].push_back(a[i]);
        graph[a[i]].push_back(i);
    }

    dfs(1);

    for (int i = 1; i <= n; i++)
    {
        cout << answer[i] << " ";
    }
}

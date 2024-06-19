#include <bits/stdc++.h>
using namespace std;

vector<int> g[200005];
queue<int> b;
vector<int> parent(200005);
int n, m;
int visited[200005];

void bfs()
{
    b.push(1);
    visited[1] = 1;
    while (!b.empty())
    {
        int x = b.front();
        b.pop();
        for (auto child : g[x])
        {
            if (visited[child] == 0)
            {
                parent[child] = x;
                b.push(child);
                visited[child] = 1;
            }
        }
    }
}

int main()
{

    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    bfs();

    vector<int> ans;
    ans.push_back(n);
    int x = n;

    if (visited[n] == 0)
    {
        cout << "IMPOSSIBLE" << endl;
    }
    else
    {
        while (x != 1)
        {
            ans.push_back(parent[x]);
            x = parent[x];
        }

        reverse(ans.begin(), ans.end());

        cout << ans.size() << endl;

        for (auto i : ans)
        {
            cout << i << " ";
        }
    }
}
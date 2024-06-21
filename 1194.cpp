#include <bits/stdc++.h>
using namespace std;

int n, m, a, b, exita, exitb, dist;
vector<vector<int>> box;
vector<vector<int>> visited;
vector<pair<int, int>> monster;
vector<vector<pair<int, int>>> timer;
vector<vector<pair<int, int>>> par;
vector<char> path;

int xx[4] = {1, -1, 0, 0};
int yy[4] = {0, 0, 1, -1};

bool is_valid(int x, int y)
{

    if (x >= n || y >= m || x < 0 || y < 0 || visited[x][y] == 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void monster_move()
{
    queue<pair<int, int>> q;
    for (auto x : monster)
    {
        q.push({x.first, x.second});
    }

    while (!q.empty())
    {
        pair<int, int> parent = q.front();
        pair<int, int> child;
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            child.first = parent.first + xx[i];
            child.second = parent.second + yy[i];

            if (is_valid(child.first, child.second))
            {
                visited[child.first][child.second] = 1;
                timer[child.first][child.second].first = timer[parent.first][parent.second].first + 1;
                q.push(child);
            }
        }
    }
}

void my_move(int i, int j)
{
    par[i][j].first = -1;
    par[i][j].second = -1;
    queue<pair<int, int>> q;
    q.push({i, j});

    while (!q.empty())
    {
        pair<int, int> parent = q.front();
        pair<int, int> child;
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            child.first = parent.first + xx[i];
            child.second = parent.second + yy[i];

            if (is_valid(child.first, child.second))
            {
                visited[child.first][child.second] = 1;
                timer[child.first][child.second].second = timer[parent.first][parent.second].second + 1;
                par[child.first][child.second] = {parent.first, parent.second};
                q.push(child);
            }
        }
    }
}

vector<char> find_path()
{
    vector<char> path;
    vector<pair<int, int>> temp;

    int x = exita, y = exitb;
    // pair<int, int> z;

    while (x != -1 && y != -1)
    {
        temp.push_back({x, y});
        auto p = par[x][y];
        x = p.first;
        y = p.second;
    }

    reverse(temp.begin(), temp.end());
    for (size_t i = 1; i < temp.size(); ++i)
    {
        int dx = temp[i].first - temp[i - 1].first;
        int dy = temp[i].second - temp[i - 1].second;

        if (dx == 1 && dy == 0)
            path.push_back('D');
        else if (dx == -1 && dy == 0)
            path.push_back('U');
        else if (dx == 0 && dy == 1)
            path.push_back('R');
        else if (dx == 0 && dy == -1)
            path.push_back('L');
    }

    return path;
}

int main()
{

    cin >> n >> m;
    box.resize(n, vector<int>(m, 0));
    timer.resize(n, vector<pair<int, int>>(m, {0, 0}));
    par.resize(n, vector<pair<int, int>>(m, {0, 0}));
    visited.resize(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            char x;
            cin >> x;
            if (x == '.')
            {
                box[i][j] = 0;
            }
            else if (x == '#')
            {
                box[i][j] = 1;
            }
            else if (x == 'M')
            {
                box[i][j] = 0;
                monster.push_back({i, j});
            }
            else if (x == 'A')
            {
                box[i][j] = 0;
                a = i;
                b = j;
            }
        }
    }

    visited = box;
    for (auto i : monster)
    {
        visited[i.first][i.second] = 1;
    }
    monster_move();

    visited = box;
    for (auto i : monster)
    {
        visited[i.first][i.second] = 0;
    }
    visited[a][b] = 1;
    my_move(a, b);

    bool ans = false;
    for (int i = 0, k = n - 1, j = 0; j < m; j++)
    {
        if (timer[i][j].first > timer[i][j].second)
        {
            ans = true;
            exita = i;
            exitb = j;
            dist = timer[i][j].second;
            break;
        }
        if (timer[k][j].first > timer[k][j].second)
        {
            ans = true;
            exita = k;
            exitb = j;
            dist = timer[k][j].second;
            break;
        }
    }
    if (ans == false)
    {
        for (int j = 0, k = m - 1, i = 0; i < n; i++)
        {
            if (timer[i][j].first > timer[i][j].second)
            {
                ans = true;
                exita = i;
                exitb = j;
                dist = timer[i][j].second;
                break;
            }
            if (timer[i][k].first > timer[i][k].second)
            {
                ans = true;
                exita = i;
                exitb = k;
                dist = timer[i][k].second;
                break;
            }
        }
    }

    if (ans == false)
    {
        cout << "NO" << endl;
    }
    else
    {
        visited = box;
        cout << "YES" << endl;
        cout << dist << endl;
        vector<char> path = find_path();
        for (auto x : path)
        {
            cout << x;
        }
    }
}
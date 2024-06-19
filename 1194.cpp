#include <bits/stdc++.h>
using namespace std;

int n, m, a, b, exita, exitb, dist;
vector<vector<int>> box;
vector<vector<int>> visited;
vector<pair<int, int>> monster;
vector<vector<pair<int, int>>> timer;
vector<char> path;

int xx[4] = {1, -1, 0, 0};
int yy[4] = {0, 0, 1, -1};

bool is_valid(int x, int y)
{
    bool flag = false;
    if (x >= n || y >= m || x < 0 || y < 0 || visited[x][y] == 1)
    {
        return flag;
    }
    else
    {
        flag = true;
    }

    return flag;
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
                q.push(child);
            }
        }
    }
}

void find_path()
{
    visited[a][b] = 1;
    int ta = a, tb = b;

    for (int i = 0; i < 4; i++)
    {
        ta += xx[i];
        tb += yy[i];
        if (timer[ta][tb].first > timer[ta][tb].second && visited[ta][tb] == 0)
        {
            visited[ta][tb] = 1;
            switch (i)
            {
            case 0:
                path.push_back('D');
                //break;
            case 1:
                path.push_back('U');
                // break;
            case 2:
                path.push_back('R');
                // break;
            case 3:
                path.push_back('L');
                // break;
            }
        }

        if (ta == exita && tb == exitb)
        {
            break;
        }
    }
}

int main()
{

    cin >> n >> m;
    box.resize(n, vector<int>(m, 0));
    timer.resize(n, vector<pair<int, int>>(m, {0, 0}));
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

    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < m; j++)
    //     {
    //         cout << timer[i][j].first << " ";
    //     }
    //     cout << endl;
    // }
    visited = box;
    for (auto i : monster)
    {
        visited[i.first][i.second] = 0;
    }
    visited[a][b] = 1;
    my_move(a, b);

    // cout << "\n\n";

    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < m; j++)
    //     {
    //         cout << timer[i][j].second << " ";
    //     }
    //     cout << endl;
    // }

    bool ans = false;
    for (int i = 0, k = n - 1, j = 0; j < m; j++)
    {
        if (timer[i][j].first > timer[i][j].second)
        {
            ans = true;
            exita = i;
            exitb = j;
            break;
        }
        if (timer[k][j].first > timer[k][j].second)
        {
            ans = true;
            exita = k;
            exitb = j;
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
                break;
            }
            if (timer[i][k].first > timer[i][k].second)
            {
                ans = true;
                exita = i;
                exitb = k;
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
        find_path();
        cout << "YES" << endl;
        for (auto x : path)
        {
            cout << x;
        }
    }


}
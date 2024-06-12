#include <bits/stdc++.h>
using namespace std;

int b[1005][1005];
int p, q;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

bool isvalid(int x, int y)
{
    if (x > p-1 || x < 0 || y > q-1 || y < 0)
    {
        return false;
    }

    if (b[x][y] == 1)
    {
        return false;
    }

    return true;
}

void dfs(int vx, int vy)
{
    b[vx][vy] = 1;
    // cout << vx << " " << vy << endl;
    for (int i = 0; i < 4; i++)
    {
        int nx = vx + dx[i], ny = vy + dy[i];
        if (isvalid(nx, ny))
        {
            dfs(nx, ny);
        }
    }
}

int main()
{

    cin >> p >> q;

    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < q; j++)
        {
            char x;
            cin >> x;
            if (x == '#')
            {
                b[i][j] = 1;
            }
        }
    }

    int answer = 0;

    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < q; j++)
        {
            if (b[i][j] == 0)
            {
                answer++;
                dfs(i, j);
            }
        }
    }

    // for (int i = 0; i < p; i++)
    // {
    //     for (int j = 0; j < q; j++)
    //     {
    //         cout << b[i][j];
    //     }

    //     cout << endl;
    // }

    cout << answer << endl;
}

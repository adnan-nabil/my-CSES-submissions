from collections import deque

n, m = map(int, input().split())
board = [list(input().strip()) for _ in range(n)]


def isvalid(newx, newy, minimum_step, px, py):
    
    return (
        0 <= newx < n
        and 0 <= newy < m
        and board[newx][newy] != "#"
        and  (minimum_step[px][py] + 1) < minimum_step[newx][newy] 
    )


def multisource_bfs(sources):
    minimum_step = [[1000000] * (m+1) for _ in range(n+1)]
    q = deque(sources)
    for x, y in sources:
        minimum_step[x][y] = 0

    directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]

    while q:
        x, y = q.popleft()
        for dx, dy in directions:
            nx, ny = x + dx, y + dy
            if isvalid(nx, ny, minimum_step, x, y):
                minimum_step[nx][ny] = minimum_step[x][y] + 1
                q.append((nx, ny))

    return minimum_step


def find_path(b, x, y):
    cur = b[x][y]
    path = []

    while cur > 0:
        if 0 <= x + 1 < n and b[x + 1][y] == cur - 1:
            path.append("U")
            x += 1
        elif 0 <= x - 1 < n and b[x - 1][y] == cur - 1:
            path.append("D")
            x -= 1
        elif 0 <= y + 1 < m and b[x][y + 1] == cur - 1:
            path.append("L")
            y += 1
        elif 0 <= y - 1 < m and b[x][y - 1] == cur - 1:
            path.append("R")
            y -= 1
        cur -= 1

    return len(path), "".join(reversed(path))


def main():
    monster_source = [(i, j) for i in range(n) for j in range(m) if board[i][j] == "M"]
    my_position = [(i, j) for i in range(n) for j in range(m) if board[i][j] == "A"][0]

    row, col = my_position
    if row == 0 or row == n - 1 or col == 0 or col == m - 1:
        print("YES")
        print(0)
        return

    
    minimum_step_monster = multisource_bfs(monster_source)
    minimum_step_me = multisource_bfs([my_position])

    
    for row in range(n):
        for col in range(m):
            if (row == 0 or row == n - 1 or col == 0 or col == m - 1) and board[row][col] == "." and (minimum_step_me[row][col] < minimum_step_monster[row][col]):
                    l, path = find_path(minimum_step_me, row, col)
                    if (l > 0):
                        print("YES")
                        print(l)
                        print(path)
                        return

    
    print("NO")


main()

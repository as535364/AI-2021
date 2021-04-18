import sys

n, m = map(int, input().split())

field = []

for _ in range(n + 2):
    row = list(input())
    row = [int(x) if x.isnumeric() else -1 for x in row]
    field.append(row)


x = 1
y = 1
cost = 0

while not(x == n and y == m):
    nx, ny = map(int, input().split())
    if nx == 1 and ny == 1:
        continue
    if abs(nx - x) + abs(ny - y) == 1 and field[nx][ny] != -1:
        cost += 10 + (field[nx][ny] - field[x][y]) * (field[nx][ny] - field[x][y])
        x = nx
        y = ny
    else:
        print('Path Error')
        raise ValueError

print(True, cost)
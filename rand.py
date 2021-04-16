import random

H = 5000; W = 5000

maze=['*']*(H+2)*(W+2)

random.seed(1)

print(H, W)

for i in range(H+2):
    for j in range(W+2):
        if (1<=i<=H) and (1<=j<=W):
            maze[i*(W+2)+j]=random.choice('0123456789**')
        print(maze[i*(W+2)+j], end="")
    print()
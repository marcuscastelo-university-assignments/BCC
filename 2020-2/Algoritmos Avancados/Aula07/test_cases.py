import random
import datetime

random.seed(datetime.datetime.now())

N=int(input())

print(N)
for n in range(N):
    # V=random.randint(0, 100000)
    V=random.randint(50, 10000)
    Q=random.randint(1,30)
    # Q=random.randint(1,10)

    print(V)
    print(Q)
    for m in range(Q):
        print(random.randint(1, 100))
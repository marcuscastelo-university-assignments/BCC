import numpy as np

N=int(input())
print(N)
for i in [i for l in np.eye(N) for i in l]: print(i, end=' ')
print()
for i in range(N**2): print(float(i), end=' ')
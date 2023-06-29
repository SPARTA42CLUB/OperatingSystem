import random
i = random.randrange(1, 11)
t = random.randrange(1, 101)

resource = []
print (i, t)
	
for _ in range(t):
	resource.append(random.randrange(1, 101))	
for _ in range(t):
	print(resource[_], end=" ")
print()

all_thread = []
for _ in range(i):
	thread = []
	for j in range(t):
		thread.append(random.randrange(1, 11))
	all_thread.append(thread)
for n in range(i):
	for m in range(t):
		print(all_thread[n][m], end=' ')
	print()
all_aloc = []
for _ in range(i):
	aloc = []
	for j in range(t):
		aloc.append(random.randrange(0, int(all_thread[_][j])))
	all_aloc.append(aloc)
# print(all_aloc)
for n in range(i):
	for m in range(t):
		print(all_aloc[n][m], end=' ')
	print()
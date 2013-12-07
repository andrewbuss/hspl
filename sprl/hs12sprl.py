import sys

ifile = sys.stdin.read()
lines = ifile.strip('\n').replace('\r','').split('\n')
ntests = int(lines.pop(0))

for line in lines:
	n = int(line)
	a = [[0 for _ in range(n)] for _ in range(n)]
	x = 0
	y = 0
	d = 0
	i = 2
	a[0][0]=1
	while i<=n*n:
		turn = 1
		if d==0 and x+1<n and not a[x+1][y]: turn=0
		elif d==1 and y+1<n and not a[x][y+1]: turn=0
		elif d==2 and x-1<n and not a[x-1][y]: turn=0
		elif d==3 and y-1<n and not a[x][y-1]: turn=0
		if turn: d=(d+1)%4
		if d==0: x+=1
		elif d==1: y+=1
		elif d==2: x-=1
		elif d==3: y-=1
		a[x][y]=i
		i+=1
	for y in range(n):
		for x in range(n):
			print a[x][y],
		print
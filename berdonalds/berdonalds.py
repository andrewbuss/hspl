import sys

ifile = sys.stdin.read()
lines = ifile.strip('\n').replace('\r','').split('\n')
line = lines.pop(0).split(' ')
n = int(line[0])
m = int(line[1])

js = [[0,0,0,[(2<<30) for __ in range(n+1)]] for _ in range(n+1)]

print js

for r in range(m):
	line = [int(p) for p in lines.pop(0).split(' ')]
	js[line[0]][3][line[1]] = min(js[line[0]][3][line[1]],line[2])
	js[line[1]][3][line[0]] = min(js[line[1]][3][line[0]],line[2])

print js
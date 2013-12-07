import sys

ifile = sys.stdin.read()
lines = ifile.strip('\n').replace('\r','').split('\n')
line = lines.pop(0).split(' ')
n = int(line[0])

free = [(i,i-1) for i in range(1,n)]
ones = []
ops = []

def swap(d,a,b):
	if a==b: return
	ops.append((d, a+1, b+1))
	for one in ones:
		if one[d-1] == a: one[d-1] = b
		elif one[d-1] == b: one[d-1] = a

for _ in range(n-1):
	line = [int(p) for p in lines.pop(0).split(' ')]
	ones.append([line[0]-1, line[1]-1])

for one in ones:
	f = free.pop(0)
	swap(1,one[0],0)
	swap(2,one[1],n-1)
	swap(1,f[0], 0)
	swap(2,f[1], n-1)

print len(ops)
for op in ops:
	print op[0], op[1], op[2]
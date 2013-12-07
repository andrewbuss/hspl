import sys

ifile = sys.stdin.read()
lines = ifile.strip('\n').replace('\r','').split('\n')
lines[0] = lines[0].split(' ')
r = int(lines[0][0])
m = int(lines[0][1])
ntests = int(lines.pop(0)[2])

def digitsum(i):
	total = 0
	while i:
		total += i%r
		i/=r
	return total

for test in range(ntests):
	s = int(lines.pop(0))
	n = 0
	while s<m:
		s+=digitsum(s)
		n+=1
		if s == m: print n
	if s>m: print -1
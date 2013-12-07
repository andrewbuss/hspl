import sys

ifile = sys.stdin.read()
lines = ifile.strip('\n').replace('\r','').split('\n')
nstones = int(lines.pop(0))

nremovals = 0
laststone = 'A'
for stone in lines[0]:
	if stone == laststone:
		nremovals+=1
	laststone = stone

print nremovals
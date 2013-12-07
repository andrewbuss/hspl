import sys

ifile = sys.stdin.read()
lines = ifile.strip('\n').replace('\r','').split('\n')
line = lines.pop(0).split(' ')
n = int(line[0])
t = int(line[1])
queue = []
newqueue = []

for person in lines[0]:
	queue.append(person)

for time in range(t):
	newqueue = list(queue)
	for i in range(n-1):
		if queue[i] == 'B' and queue[i+1] == 'G':
			newqueue[i+1] = 'B'
			newqueue[i] = 'G'
	queue = newqueue

for person in queue:
	sys.stdout.write(person)

print
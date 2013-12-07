import sys

ifile = sys.stdin.read()
lines = ifile.strip('\n').replace('\r','').split('\n')
n = int(lines.pop(0))
next = [0]+map(int,lines.pop(0).split(' '))
m = int(lines.pop(0))

for t in range(m):
	line = map(int,lines.pop(0).split(' '))
	if line[0] == 2:
		if line[1]==line[2]:
			print "-1"
			break
		visited = []
		c = 0
		i = line[1]
		#print "Starting at", i
		while 1:
			print c, i, visited
			#print "At", i
			if next[i]:
				if i in visited: 
					#print "Looped without end"
					print "-1"
					break
				elif i == line[2]:
					print c
					break
				visited.append(i)
				i = next[i]
				c += 1
			else: 
				#print "Reached end of path"
				print "-1"
				break
	else: next[line[1]] = 0
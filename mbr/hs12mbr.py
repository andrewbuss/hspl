import sys

ifile = sys.stdin.read()
lines = ifile.strip('\n').replace('\r','').split('\n')
ntests = int(lines.pop(0))

for test in range(ntests):
	minx = 1000
	miny = 1000
	maxx = -1000
	maxy = -1000
	n = int(lines.pop(0))
	for o in range(n):
		line = lines.pop(0).split(' ')
		line[1:] = [int(i) for i in line[1:] if i]
		if line[0] == 'p':
			minx = min(line[1],minx)
			miny = min(line[2],miny)
			maxx = max(line[1],maxx)
			maxy = max(line[2],maxy)
		elif line[0] == 'c':
			minx = min(line[1]-line[3],minx)
			miny = min(line[2]-line[3],miny)
			maxx = max(line[1]+line[3],maxx)
			maxy = max(line[2]+line[3],maxy)
		elif line[0] == 'l':
			minx = min(line[1],minx)
			miny = min(line[2],miny)
			maxx = max(line[1],maxx)
			maxy = max(line[2],maxy)
			minx = min(line[3],minx)
			miny = min(line[4],miny)
			maxx = max(line[3],maxx)
			maxy = max(line[4],maxy)
	if lines: lines.pop(0)
	print minx,miny,maxx,maxy
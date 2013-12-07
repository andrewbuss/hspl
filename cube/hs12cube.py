import sys, re, copy

def newcube():
	c=[[0 for _ in range(9)] for __ in range(12)]
	for x in range(3):
		for y in range(3):
			c[3+x][3+y] = 1
			c[9+x][3+y] = 2
			c[0+x][3+y] = 3
			c[6+x][3+y] = 4
			c[3+x][0+y] = 5
			c[3+x][6+y] = 6
	return c

def printcube(c):
	for y in range(9):
		for x in range(12):
			if c[x][y] != 0: sys.stdout.write(str(c[x][y])+' ')
			else: sys.stdout.write('  ')
		sys.stdout.write('\n')
	sys.stdout.write('\n')

def cw(xo, yo):
	global c
	
	c[xo+0][yo+0] = n[0]
	c[xo+1][yo+0] = n[1]
	c[xo+2][yo+0] = n[2]
	c[xo+2][yo+1] = n[3]
	c[xo+2][yo+2] = n[4]
	c[xo+1][yo+2] = n[5]
	c[xo+0][yo+2] = n[6]
	c[xo+0][yo+1] = n[7]

def fcw():
	global c
	cw(3,3)
	for i in range(3): 
		n = (c[2][5-i], c[3+i][2], c[6][3+i], c[5-i][6])
		c[3+i][2] = n[0]
		c[6][3+i] = n[1]
		c[5-i][6] = n[2]
		c[2][5-i] = n[3]

def bcw():
	global c
	cw(9,3)
	for i in range(3): 
		n=(c[8][5-i],c[5-i][0],c[0][3+i],c[3+i][8])
		c[5-i][0] = n[0]
		c[0][3+i] = n[1]
		c[3+i][8] = n[2]
		c[8][5-i] = n[3]

def lcw():
	global c
	cw(0,3)
	for i in range(3): 
		n=( c[11][5-i], c[3][i], c[3][3+i], c[3][6+i])
		c[3][i] = n[0]
		c[3][3+i] = n[1]
		c[3][6+i] = n[2]
		c[11][5-i] = n[3]

def rcw():
	global c
	cw(6,3)
	for i in range(3):
		n=(c[5][5-i],c[5][2-i],c[9][3+i],c[5][8-i])
		c[5][2-i] =n[0]
		c[9][3+i] = n[1]
		c[5][8-i] = n[2]
		c[5][5-i] = n[3]

def ucw():
	global c
	cw(3,0)
	n = [c[i][3] for i in range(12)]
	for i in range(12): 
		c[i][3]=n[(i+3)%12]

def dcw():
	global c
	cw(3,6)
	n = [c[i][5] for i in range(12)]
	for i in range(12): 
		c[i][5]=n[(i+3)%12]

def dcolors(xo,yo):
	global c
	colors = []
	for x in range(3):
		for y in range(3):
			colors.append(c[xo+x][yo+y])
	return len(set(colors))
ifile = sys.stdin.read()
lines = ifile.strip('\n').replace('\r','').split('\n')
ntests = int(lines.pop(0))
tokenizer = re.compile("[FBLRUD]'?2?")

for line in lines:
	c = newcube()
	for token in tokenizer.findall(line):
		if token == 'F': 
			fcw()
		elif token == 'F\'':
			fcw()
			fcw()
			fcw()
		elif token == 'F2':
			fcw()
			fcw()
		elif token == 'B':
			bcw()
		elif token == 'B\'':
			bcw()
			bcw()
			bcw()
		elif token == 'B2':
			bcw()
			bcw()
		elif token == 'L':
			lcw()
		elif token == 'L\'':
			lcw()
			lcw()
			lcw()
		elif token == 'L2':
			lcw()
			lcw()
		elif token == 'R':
			rcw()
		elif token == 'R\'':
			rcw()
			rcw()
			rcw()
		elif token == 'R2':
			rcw()
			rcw()
		elif token == 'U':
			ucw()
		elif token == 'U\'':
			ucw()
			ucw()
			ucw()
		elif token == 'U2':
			ucw()
			ucw()
		elif token == 'D':
			dcw()
		elif token == 'D\'':
			dcw()
			dcw()
			dcw()
		elif token == 'D2':
			dcw()
			dcw()
	print dcolors(3,3), dcolors(6,3), dcolors(9,3), dcolors(0,3), dcolors(3,0), dcolors(3,6)

import sys

lim = 50000000
prime = [True] * lim  
prime[0] = False
prime[1] = False
for (i, isprime) in enumerate(prime):
    if isprime:
    	print i
        for n in xrange(i*i, lim, i):
        	prime[n] = False

print prime

ifile = sys.stdin.read()
lines = ifile.strip('\n').replace('\r','').split('\n')
ntests = int(lines.pop(0))

for line in lines:
	line = line.split(' ')
	b = int(line.pop())
	a = int(line.pop())
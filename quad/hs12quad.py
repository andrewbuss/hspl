import sys

ifile = sys.stdin
ntests = int(ifile.readline())

def fr(a,b):
	if a==0: return 1L
	if b==0: return 1L<<32
	if b<0:
		a = -a
		b = -b
	if a<0: at = -a
	else: at = a
	bt = b
	while at>0:
		ct = at
		at = bt % at
		bt = ct
	return (((a/bt)<<32)|(b/bt))&0xFFFFFFFFFFFFFFFF

def slope(a,b):
	return fr(b[1]-a[1],b[0]-a[0])

for test in range(ntests):
	slopes = []
	slens = []
	line = ifile.readline().rstrip('\n').replace('\r','').split(' ')
	points = [(int(line[i]),int(line[i+1])) for i in range(0,8,2)]
	for i in range(4):
		slopes.append(slope(points[i],points[(i+1)%4]))
		slens.append((points[(i+1)%4][0]-points[i][0])*(points[(i+1)%4][0]-points[i][0])+
			         (points[(i+1)%4][1]-points[i][1])*(points[(i+1)%4][1]-points[i][1]));
	#print "{:>016X}".format(slopes[0])
	#print "{:>016X}".format(ninv)
	if 0 in slens or slopes[0] == slopes[1] or slopes[1] == slopes[2] or slopes[2] == slopes[3] or slopes[3]==slopes[0]:
		print "None"
		continue
	if slopes[0] == slopes[2] and slopes[1] == slopes[3]: 
		#print "Parallelogram"
		if -(points[0][0]*points[1][0]) + points[1][0]*points[1][0] + points[0][0]*points[2][0] - points[1][0]*points[2][0] == \
		     points[0][1]*points[1][1] - points[1][1]*points[1][1] - points[0][1]*points[2][1] + points[1][1]*points[2][1]:
			if len(set(slens)) == 1: print "Square"
			else: print "Rectangle"
		else:
			if len(set(slens)) == 1: print "Rhombus"
			else: print "Rhomboid"
	elif slopes[0] == slopes[2] or slopes[1] == slopes[3]:
		print "Trapezoid"
	else:
		#print "Not a parallelogram or trapezoid"
		concave = False
		for i in range(4):
			v1x = points[(i+1)%4][0]-points[i][0];
			v1y = points[(i+1)%4][1]-points[i][1];
			v2x = points[(i+1)%4][0]-points[(i+2)%4][0];
			v2y = points[(i+1)%4][1]-points[(i+2)%4][1];
			xp = v1x*v2y-v1y*v2x
			if xp == 0:
				print "XP = 0 - problem!"
				break
			if xp > 0: 
				concave = True
				break
		if (slens[0] == slens[1] and slens[2] == slens[3]) or (slens[1] == slens[2] and slens[3] == slens[0]): 
			if concave: print "Dart"
			else: print "Kite"
		else:
			if concave: print "Concave"
			else: print "Convex"

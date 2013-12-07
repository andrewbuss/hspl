import sys
from itertools import *

scores = {}
relations = []
leaders = {}
triples = []


ifile = sys.stdin.read()
lines = ifile.strip('\n').replace('\r','').split('\n')
n = int(lines.pop(0))
for i in range(n):
	line = lines.pop(0).split(' ')
	scores[line[0]]=int(line[1])
m = int(lines.pop(0))
for i in range(min(m,312)):
	line = lines.pop(0).split(' ')
	relations.append((line[0],line[1]))
for relation in relations:
	if relation[0] not in leaders: leaders[relation[0]] = []
	if relation[1] not in leaders: leaders[relation[1]] = []
	if relation[0] in leaders:
		leaders[relation[0]].append(relation[1])
	if relation[1] in leaders:
		leaders[relation[1]].append(relation[0])
for person in scores:
	if person not in leaders: continue
	if len(leaders[person])<2: del leaders[person]

for leader in leaders:
	for c in combinations(leaders[leader],2):
		triples.append((2*scores[leader]+scores[c[0]]+scores[c[1]],leader,c[0],c[1]))

nts = len(triples)
triples = sorted(triples,key=lambda x: x[0],reverse=True)
compatible = [set() for i in range(nts)]
for i,ti in enumerate(triples):
	for j,tj in enumerate(triples):
		if j!=i:
			if (tj[1] not in ti) and (tj[2] not in ti) and (tj[3] not in ti):
				compatible[i].add(j)

selection = [0]
cts = compatible[selection[0]]
for i in range(nts):
	if i in cts: 
		selection.append(i)
		cts.intersection_update(compatible[i])

score = 0
print len(selection)
for i in selection:
	print triples[i][1], triples[i][2],triples[i][3]
	score += triples[i][0]

print score
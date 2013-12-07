import sys
import pygame
import pygame.gfxdraw
import pygame.time
import pygame.rect
import colorsys

pygame.init()

tfile = open("test","r")
ofile = open("cppout","r")

tlines = tfile.read().split('\n')
olines = ofile.read().split('\n')

ntests = int(tlines.pop(0))

for test in range(ntests):
	line = tlines.pop(0).split(' ')
	bx = int(line[0])
	by = int(line[1])
	
	rects = []
	nrects = int(tlines.pop(0))
	for rect in range(nrects):
		line = tlines.pop(0).split(' ')
		rects.append((int(line[0]),int(line[1])))
	hsvpalette = [colorsys.hsv_to_rgb((i*1.0)/(1.0*nrects),0.7,0.7) for i in range(nrects+1)]
	palette = [(a[0]*255,a[1]*255,a[2]*255) for a in hsvpalette]
	palette[0] = (0,0,0)
	added = []
	addedc = []
	for rect in range(int(olines.pop(0))):
		line = olines.pop(0).split(' ')
		if int(line[3] == 'o'): added.append(pygame.Rect(int(line[1]),int(line[2]),rects[int(line[0])-1][0],rects[int(line[0])-1][1]))
		else: added.append(pygame.Rect(int(line[1]),int(line[2]),rects[int(line[0])-1][1],rects[int(line[0])-1][0]))
		addedc.append(palette[int(line[0])-1])
	if bx<=0 or by<= 0: continue
	
	window = pygame.display.set_mode((bx,by))
	pygame.display.flip()
	
	
	for i in range(len(added)):
		pygame.gfxdraw.box(window,added[i],addedc[i])
		rv = added[i].collidelistall(added)
		if len(rv)>1: print "Collision!", rv
	pygame.display.flip()
	pygame.time.wait(1000)
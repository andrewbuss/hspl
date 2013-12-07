import sys
import pygame
import pygame.gfxdraw
import colorsys

pygame.init() 
size = 64
window = pygame.display.set_mode((size/2, size/2))
pa = pygame.PixelArray(window)
board = [[0 for _ in range(size*2)] for __ in range(size*2)]
even = []
odd = []
hsvpalette = [colorsys.hsv_to_rgb(i/8.0,1,1) for i in range(size)]
palette = [(a[0]*255,a[1]*255,a[2]*255) for a in hsvpalette]
palette = [(255-8*a,255-8*a,255-8*a) for a in range(size)]
palette[0] = (0,0,0)
palette[1] = (255,255,255)
board[0][-2]=1
board[0][-1]=1
board[0][0]=1
board[0][1]=1
board[0][2]=1

odd.append((0,2))
odd.append((0,-2))

i=2
ox = 4
oy = 4

def iterate():
	global even,odd, board, i
	if i%2:
		while len(odd):
			endpoint = odd.pop()
			if board[endpoint[0]][endpoint[1]-1] == 0 or board[endpoint[0]][endpoint[1]+1] == 0:
				if board[endpoint[0]+2][endpoint[1]] == 0: board[endpoint[0]+2][endpoint[1]] = i
				if board[endpoint[0]+1][endpoint[1]] == 0: board[endpoint[0]+1][endpoint[1]] = i
				if board[endpoint[0]][endpoint[1]] == 0: board[endpoint[0]][endpoint[1]] = i
				if board[endpoint[0]-1][endpoint[1]] == 0: board[endpoint[0]-1][endpoint[1]] = i
				if board[endpoint[0]-2][endpoint[1]] == 0: board[endpoint[0]-2][endpoint[1]] = i
				even.append((endpoint[0]+2,endpoint[1]))
				even.append((endpoint[0]-2,endpoint[1]))
	else:
		while len(even):
			endpoint = even.pop()
			if board[endpoint[0]-1][endpoint[1]] == 0 or board[endpoint[0]+1][endpoint[1]] == 0:
				if board[endpoint[0]][endpoint[1]+2] == 0: board[endpoint[0]][endpoint[1]+2] = i
				if board[endpoint[0]][endpoint[1]+1] == 0: board[endpoint[0]][endpoint[1]+1] = i
				if board[endpoint[0]][endpoint[1]] == 0: board[endpoint[0]][endpoint[1]] = i
				if board[endpoint[0]][endpoint[1]-1] == 0: board[endpoint[0]][endpoint[1]-1] = i
				if board[endpoint[0]][endpoint[1]-2] == 0: board[endpoint[0]][endpoint[1]-2] = i
				odd.append((endpoint[0],endpoint[1]+2))
				odd.append((endpoint[0],endpoint[1]-2))

while i<size/2+1:
	iterate()
	i+=1

for x in range(-size/4,size/4):
	for y in range(-size/4,size/4):
		pygame.gfxdraw.pixel(window,size/4+x,size/4+y,palette[board[x*2][y*2]])

pygame.display.flip()
pygame.image.save(window, "out.bmp")

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <algorithm>
#include <stdlib.h>

using namespace std;
string line;
int ntests;

char board[8][8];
unsigned short ms[1000];
unsigned int msi = 0;
bool icv[8][8];

#ifndef HELP
#define HELP 0
#endif

inline char chs(char nb[8][8], int x, int y){
	if(x<0 or x>7 or y<0 or y>7) return 0;
	return nb[y][x];
}

bool cm(char nb[8][8]){
	int kx=99, ky=99;
	for(unsigned int y=0;y<8;y++){
		for(unsigned int x=0;x<8;x++){
			if(nb[y][x] == 8){
				kx=x;
				ky=y;
			}
		}
	}
	if(icv[ky][kx]) return false;

	if(chs(nb,kx+1,ky+2)==19) return false;
	if(chs(nb,kx+1,ky-2)==19) return false;
	if(chs(nb,kx-1,ky+2)==19) return false;
	if(chs(nb,kx-1,ky-2)==19) return false;
	if(chs(nb,kx+2,ky+1)==19) return false;
	if(chs(nb,kx+2,ky-1)==19) return false;
	if(chs(nb,kx-2,ky+1)==19) return false;
	if(chs(nb,kx-2,ky-1)==19) return false;

	if(chs(nb,kx-1,ky-1)==21) return false;
	if(chs(nb,kx+1,ky-1)==21) return false;
	for(int d=1;kx+d<8;d++){
		if(nb[ky][kx+d]){
			if(nb[ky][kx+d]==17 or nb[ky][kx+d]==20) return false;
			else break;
		}
	}
	for(int d=1;kx-d>=0;d++){
		if(nb[ky][kx-d]){
			if(nb[ky][kx-d]==17 or nb[ky][kx-d]==20) return false;
			else break;
		}
	}
	for(int d=1;ky+d<8;d++){
		if(nb[ky+d][kx]){
			if(nb[ky+d][kx]==17 or nb[ky+d][kx]==20) return false;
			else break;
		}
	}
	for(int d=1;ky-d>=0;d++){
		if(nb[ky-d][kx]){
			if(nb[ky-d][kx]==17 or nb[ky-d][kx]==20) return false;
			else break;
		}
	}
	for(int d=1;kx+d<8 and ky+d<8;d++){
		if(nb[ky+d][kx+d]){
			if(nb[ky+d][kx+d]==17 or nb[ky+d][kx+d]==18) return false;
			else break;
		}
	}
	for(int d=1;kx-d>=0 and ky+d<8;d++){
		if(nb[ky+d][kx-d]){
			if(nb[ky+d][kx-d]==17 or nb[ky+d][kx-d]==18) return false;
			else break;
		}
	}
	for(int d=1;kx-d>=0 and ky-d>=0;d++){
		if(nb[ky-d][kx-d]){
			if(nb[ky-d][kx-d]==17 or nb[ky-d][kx-d]==18) return false;
			else break;
		}
	}
	for(int d=1;kx+d<8 and ky-d>=0;d++){
		if(nb[ky-d][kx+d]){
			if(nb[ky-d][kx+d]==17 or nb[ky-d][kx+d]==18) return false;
			else break;
		}
	}
	return true;
}

inline void am(int sx, int sy, int ex, int ey){
	if(ex<0 or ex>7 or ey<0 or ey>7) return;
	if(board[sy][sx]==8 and icv[ey][ex]) return;
	if(board[ey][ex]>0 and board[ey][ex]<16) return;
	ms[msi++]=((sx<<12)|(sy<<8)|(ex<<4)|ey);
	if(HELP)printf("Adding move from %c%u to %c%u\n",'H'-sy, sx+1,'H'-ey, ex+1);
}

int main(){
	getline(cin,line);
	stringstream(line) >> ntests;
	for(unsigned int t=0;t<ntests;t++){
		memset(icv,false,64*sizeof(bool));
		getline(cin,line);
		for(unsigned int y=0;y<8;y++){
			getline(cin,line);
			for(unsigned int x=0;x<8;x++){
				switch(line[x]){
					case '.': board[y][x] = 0; break;
					case 'K': board[y][x] = 8; break;
					case 'D': board[y][x] = 9; break;		
					case 'L': board[y][x] = 10; break;
					case 'S': board[y][x] = 11; break;
					case 'T': board[y][x] = 12; break;
					case 'P': board[y][x] = 13; break;
					case 'k': board[y][x] = 16; break;
					case 'd': board[y][x] = 17; break;
					case 'l': board[y][x] = 18; break;
					case 's': board[y][x] = 19; break;
					case 't': board[y][x] = 20; break;
					case 'p': board[y][x] = 21; break;
				}
			}
		}
		for(int y=0;y<8;y++){
			for(int x=0;x<8;x++){
				if(board[y][x]<16) continue;
				switch(board[y][x]){
				case 16:
					if(x<7) icv[y][x+1] = true;
					if(x<7 and y<7) icv[y+1][x+1] = true;
					if(y<7) icv[y+1][x] = true;
					if(x>0 and y<7) icv[y+1][x-1] = true;
					if(x>0) icv[y][x-1] = true;
					if(x>0 and y>0) icv[y-1][x-1] = true;
					if(y>0) icv[y-1][x] = true;
					if(x<7 and y>0) icv[y-1][x+1] = true;
					break;
				case 17:
					for(int d=1;x+d<8;d++){
						icv[y][x+d] = true;
						if(board[y][x+d]) break;
					}
					for(int d=1;x-d>=0;d++){
						icv[y][x-d] = true;
						if(board[y][x-d]) break;
					}
					for(int d=1;y+d<8;d++){
						icv[y+d][x] = true;
						if(board[y+d][x]) break;
					}
					for(int d=1;y-d>=0;d++){
						icv[y-d][x] = true;
						if(board[y-d][x]) break;
					}
					for(int d=1;x+d<8 and y+d<8;d++){
						icv[y+d][x+d] = true;
						if(board[y+d][x+d]) break;
					}
					for(int d=1;x-d>=0 and y+d<8;d++){
						icv[y+d][x-d] = true;
						if(board[y+d][x-d]) break;
					}
					for(int d=1;x-d>=0 and y-d>=0;d++){
						icv[y-d][x-d] = true;
						if(board[y-d][x-d]) break;
					}
					for(int d=1;x+d<8 and y-d>=0;d++){
						icv[y-d][x+d] = true;
						if(board[y-d][x+d]) break;
					}
					break;
				case 18:
					for(int d=1;x+d<8 and y+d<8;d++){
						icv[y+d][x+d] = true;
						if(board[y+d][x+d]) break;
					}
					for(int d=1;x-d>=0 and y+d<8;d++){
						icv[y+d][x-d] = true;
						if(board[y+d][x-d]) break;
					}
					for(int d=1;x-d>=0 and y-d>=0;d++){
						icv[y-d][x-d] = true;
						if(board[y-d][x-d]) break;
					}
					for(int d=1;x+d<8 and y-d>=0;d++){
						icv[y-d][x+d] = true;
						if(board[y-d][x+d]) break;
					}
					break;
				case 19:
					if(y>1 and x>0) icv[y-2][x-1] = true;
					if(y>0 and x>1) icv[y-1][x-2] = true;
					if(y<6 and x>0) icv[y+2][x-1] = true;
					if(y<7 and x>1) icv[y+1][x-2] = true;
					if(y>1 and x<7) icv[y-2][x+1] = true;
					if(y>0 and x<6) icv[y-1][x+2] = true;
					if(y<6 and x<7) icv[y+2][x+1] = true;
					if(y<7 and x<6) icv[y+1][x+2] = true;
					break;
				case 20:
					for(int d=1;x+d<8;d++){
						icv[y][x+d] = true;
						if(board[y][x+d]) break;
					}
					for(int d=1;x-d>=0;d++){
						icv[y][x-d] = true;
						if(board[y][x-d]) break;
					}
					for(int d=1;y+d<8;d++){
						icv[y+d][x] = true;
						if(board[y+d][x]) break;
					}
					for(int d=1;y-d>=0;d++){
						icv[y-d][x] = true;
						if(board[y-d][x]) break;
					}
					break;
				case 21:
					if(y<7){
						if(x>0) icv[y+1][x-1] = true;
						if(x<7) icv[y+1][x+1] = true;
					}
					break;
				}
			}
		}
		if(HELP){
			for(unsigned int y=0;y<8;y++){
				for(unsigned int x=0;x<8;x++){
					if(icv[y][x]) printf("x");
					else printf(".");
				}
				printf("\n");
			}
		}
		memset(ms,0,2000);
		msi = 0;
		for(int y=0;y<8;y++){
			for(int x=0;x<8;x++){
				if(board[y][x]>13) continue;
				switch(board[y][x]){
				case 8:
					am(x,y,x-1,y);
					am(x,y,x-1,y-1);
					am(x,y,x  ,y-1);
					am(x,y,x+1,y-1);
					am(x,y,x+1,y);
					am(x,y,x+1,y+1);
					am(x,y,x  ,y+1);
					am(x,y,x-1,y+1);
					break;
				case 9:
					for(int d=1;x+d<8;d++){
						am(x,y,x+d,y);
						if(board[y][x+d]) break;
					}
					for(int d=1;x-d>=0;d++){
						am(x,y,x-d,y);
						if(board[y][x-d]) break;
					}
					for(int d=1;y+d<8;d++){
						am(x,y,x,y+d);
						if(board[y+d][x]) break;
					}
					for(int d=1;y-d>=0;d++){
						am(x,y,x,y-d);
						if(board[y-d][x]) break;
					}
					for(int d=1;x+d<8 and y+d<8;d++){
						am(x,y,x+d,y+d);
						if(board[y+d][x+d]) break;
					}
					for(int d=1;x-d>=0 and y+d<8;d++){
						am(x,y,x-d,y+d);
						if(board[y+d][x-d]) break;
					}
					for(int d=1;x-d>=0 and y-d>=0;d++){
						am(x,y,x-d,y-d);
						if(board[y-d][x-d]) break;
					}
					for(int d=1;x+d<8 and y-d>=0;d++){
						am(x,y,x+d,y-d);
						if(board[y-d][x+d]) break;
					}
					break;
				case 10:
					for(int d=1;x+d<8 and y+d<8;d++){
						am(x,y,x+d,y+d);
						if(board[y+d][x+d]) break;
					}
					for(int d=1;x-d>=0 and y+d<8;d++){
						am(x,y,x-d,y+d);
						if(board[y+d][x-d]) break;
					}
					for(int d=1;x-d>=0 and y-d>=0;d++){
						am(x,y,x-d,y-d);
						if(board[y-d][x-d]) break;
					}
					for(int d=1;x+d<8 and y-d>=0;d++){
						am(x,y,x+d,y-d);
						if(board[y-d][x+d]) break;
					}
					break;
				case 11:
					am(x,y,x+1,y-2);
					am(x,y,x+1,y+2);
					am(x,y,x-1,y-2);
					am(x,y,x-1,y+2);
					am(x,y,x+2,y-1);
					am(x,y,x+2,y+1);
					am(x,y,x-2,y-1);
					am(x,y,x-2,y+1);
					break;
				case 12:
					for(int d=1;x+d<8;d++){
						am(x,y,x+d,y);
						if(board[y][x+d]) break;
					}
					for(int d=1;x-d>=0;d++){
						am(x,y,x-d,y);
						if(board[y][x-d]) break;
					}
					for(int d=1;y+d<8;d++){
						am(x,y,x,y+d);
						if(board[y+d][x]) break;
					}
					for(int d=1;y-d>=0;d++){
						am(x,y,x,y-d);
						if(board[y-d][x]) break;
					}
					break;
				case 13:
					if(y==1){
						if(not board[0][x]){
							am(x,y,x,y-1);
							am(x,y,x,y-1);
							am(x,y,x,y-1);
							am(x,y,x,y-1);
						}
						if(x>0 and board[0][x-1]>13){
							am(x,y,x-1,y-1);
							am(x,y,x-1,y-1);
							am(x,y,x-1,y-1);
							am(x,y,x-1,y-1);
						}
						if(x<7 and board[0][x+1]>13){
							am(x,y,x+1,y-1);
							am(x,y,x+1,y-1);
							am(x,y,x+1,y-1);
							am(x,y,x+1,y-1);
						}
					}else{
						if(x<7 and board[y-1][x+1]>13) am(x,y,x+1,y-1);
						if(x>0 and board[y-1][x-1]>13) am(x,y,x-1,y-1);
						if(not board[y-1][x]){
							am(x,y,x,y-1);
							if(y==6 and not board[y-2][x]) am(x,y,x,y-2);
						}
					}
					break;
				}
			}
		}
		unsigned int nmoves = 0;
		if(HELP)printf("%u pseudolegal moves\n",msi);
		char nb[8][8];
		for(unsigned int i=0;i<msi;i++){
			if(HELP) printf("Testing move from %c%u to %c%u\n",'H'-((ms[i]>>8)&7), 1+(ms[i]>>12)&7,'H'-((ms[i])&7), 1+(ms[i]>>4)&7);
			memcpy(nb,board,64);
			nb[(ms[i]>>8)&7][(ms[i]>>12)&7] = 0;
			nb[(ms[i])&7][(ms[i]>>4)&7] = board[(ms[i]>>8)&7][(ms[i]>>12)&7];
			if(cm(nb)) nmoves++;
		}
		printf("%u\n",nmoves);
	}
}

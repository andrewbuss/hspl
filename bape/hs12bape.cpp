#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <set>
#include <time.h>
#include <algorithm>
#include <stdlib.h>

int npot(int i){
	i|=(i>>1);
	i|=(i>>2);
	i|=(i>>4);
	i|=(i>>8);
	i|=(i>>16);
	return i+1;
}

int v(int x, int y){
	if(x<0) x = -x;
	if(y<0) y = -y;
	//printf("v(%u, %u) \n",x,y);
	unsigned int maxd = x>y?x:y;
	unsigned int mind = y<x?x:y;
	if(maxd<4){
		return block[y%4][x%4];
	}
	if(x==0 and y>3){
		if((y-1)&y) return -1;
		else return y*2;
	}
	if(y==0 and x>3){
		if((x+1)&x) return -1;
		else return x*2+1;
	}
	if(!((y-1)&y) and x<y){
		return y*2-x%2;
	}
	if(!((x+1)&x) and y<x){
		return x*2-y%2+1;
	}
	if(!((x-1)&x) and y<x){
		//return -1;
	}
	if(x/4==y/4) if(block[y%4][x%4]>=0) return block[y%4][x%4]+(x/4)*8;
	int d = y-x;
	if(d==1) return 2*x+1;
	if(d==2) return 2*y;
	if(d==-1) return 2*x+1;
	int npotax = npot(x+1);
	int npotay = npot(y);
	int quad4 = npotax>npotay?npotax:npotay;
	int quad1 = quad4/4;
	int quad2 = quad1*2;
	int quad3 = quad1*3;
	int rv = -1;
	if(y<=quad2){
		rv = v(quad2-y,x-quad2+1);
		if(rv>0) return rv+quad4-1;
		else return -1;
	}
	if(x<=quad2){
		rv = v(quad2-x,y-quad2);
		if(rv>0) return rv+quad4;
		else return -1;
	}
	rv = v(x-quad2,y-quad2);
	if(rv>0) return rv+quad4;
	return -1;
}

int main(){
	printf("    ");
	for(int x=0;x<32;x++) printf(" %2d ",x);
	printf("\n\n");
	for(int y=0;y<32;y++){
		printf(" %2d ",y);
		for(int x=0;x<32;x++){
			int r = v(x,y);
			if (board[x][y] and r!= board[x][y]) printf("Error at %u %u\n",x,y);
			bool left = false;
			if(x>0 and (v(x-1,y)-r == 1 or r-v(x-1,y) == 1)){
				printf("=");
				left = true;
			}else{
				printf(" ");
			}
			if(r<=0) printf("  ");
			else if(r>=10) printf("%2d",r);
			else if(left) printf("=%d",r);
			else printf(" %d",r);
			if(v(x+1,y)-r == 1 or r-v(x+1,y) == 1){
				printf("=");
			}else{
				printf(" ");
			}
		}
		printf("\n    ");
		for(int x=0;x<32;x++){
			int r = v(x,y);
			if(r and (v(x,y+1)-r == 1 or r-v(x,y+1) == 1)){
				if(r>10 and v(x,y+1)>10) printf(" || ");
				else printf("  | ");
			}else{
				printf("    ");
			}
		}
		printf("\n");
	}
	unsigned int ntests;
	string line;
	getline(cin,line);
	stringstream(line) >> ntests;
	for(int i=0;i<ntests;i++){
		getline(cin,line);
		int x,y;
		stringstream(line) >> x >> y;
		if(x==0 and y==0) printf("1\n");
		else printf("%d\n",v(x,y));
	}
}
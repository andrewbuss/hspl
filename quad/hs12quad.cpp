#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <set>
#include <stdlib.h>

#ifndef HELP
#define HELP 0
#endif
#ifndef HELP2
#define HELP2 0
#endif

using namespace std;

struct point{
	long long int x;
	long long int y;
};

point points[4];
unsigned long long slopes[4];
unsigned long long slens[4];

unsigned long long fr(int a,int b){
	if(b==0) return 1LL;
	if(a==0) return 1LL<<32;
	if(b<0){
		a = -a;
		b = -b;
	}
	unsigned long long at, bt;
	if(a<0) at = -a;
	else at = a;
	bt = b;
	while(at>0){
		unsigned long long ct = at;
		at = bt % at;
		bt = ct;
	}
	return (((a/bt)<<32)|(b/bt))&0xFFFFFFFFFFFFFFFFLL;
}

inline unsigned long long slope(point a, point b){
	return fr(b.y-a.y,b.x-a.x);
}
	
inline unsigned long long slen(point a,point b){
	long long int dx = b.x-a.x;
	long long int dy = b.y-a.y;
	return dx*dx+dy*dy;
}

int main(){
	string line;
	getline(cin,line);
	unsigned int ntests;
	stringstream(line) >> ntests;
	for(int i=0;i<ntests;i++){
		getline(cin,line);
		stringstream(line) >> points[0].x >> points[0].y >> points[1].x >> points[1].y >> points[2].x >> points[2].y >> points[3].x >> points[3].y;
		bool none = false;
		for(unsigned int i=0;i<4;i++){  
			slopes[i] = slope(points[i],points[(i+1)%4]);
			slens[i] = slen(points[i],points[(i+1)%4]);
			if(HELP){
				printf("Point #%u: (%d %d)\n",i,points[i].x,points[i].y);
				printf("Slope: %016lX\n",slopes[i]);
				printf("SLen: %lu\n",slens[i]);
			}
			if(slens[i] == 0){
				none=true;
				break;
			}
		}
		if(none or slopes[0] == slopes[1] or slopes[1] == slopes[2] or slopes[2] == slopes[3] or slopes[3] == slopes[0]){
			cout << "None\n";
			continue;
		}
		if(slopes[0] == slopes[2] and slopes[1] == slopes[3]){
			//printf("Parallelogram\n");
			set<unsigned long long> lens(slens,slens+4);
			unsigned int nlens = lens.size();
			if(HELP) printf("%u distinct lengths\n",nlens);
			if(-(points[0].x*points[1].x) + points[1].x*points[1].x + points[0].x*points[2].x- points[1].x*points[2].x == points[0].y*points[1].y - points[1].y*points[1].y - points[0].y*points[2].y + points[1].y*points[2].y){
				if(nlens == 1) cout << "Square\n";
				else cout << "Rectangle\n";
			}
			else{
				if(nlens == 1) cout << "Rhombus\n";
				else cout << "Rhomboid\n";
			}
		}
		else if(slopes[0] == slopes[2] || slopes[1] == slopes[3]) cout << "Trapezoid\n";
		else{
			//printf("Not a parallelogram or trapezoid\n");
			bool concave = false;
			for(unsigned int i=0;i<4;i++){
				long long v1x = points[(i+1)%4].x-points[i].x;
				long long v1y = points[(i+1)%4].y-points[i].y;
				long long v2x = points[(i+1)%4].x-points[(i+2)%4].x;
				long long v2y = points[(i+1)%4].y-points[(i+2)%4].y;
				long long xp = v1x*v2y - v1y*v2x;
				if(HELP2) printf("%ld %ld %ld %ld\nXP: %ld\n",v1x,v1y,v2x,v2y,xp);
				if (xp == 0){
					none=true;
					break;
				}
				if (xp > 0){
					concave = true;
					break;
				}
			}
			if(none){
				printf("XP = 0 - problem!\n");
				continue;
			}
			if((slens[0] == slens[1] and slens[2] == slens[3]) || (slens[1] == slens[2] and slens[3] == slens[0])){ 
				if(concave) cout << "Dart\n";
				else cout << "Kite\n";
			}else{
				if(concave) cout << "Concave\n";
				else cout << "Convex\n";
			}
		}
	}
	return 0;
}
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <algorithm>
#include <stdlib.h>

using namespace std;

double cx[10000];
double cy[10000];
double cm[10000];
double cr[10000];

int main(){
	unsigned int ntests;
	scanf("%u\n",&ntests);
	for(unsigned int i=0; i<ntests;i++){
		unsigned int w,l,n;
		scanf("%u %u %u\n",&w,&l,&n);
		double mass = 0;
		double tx = 0;
		double ty = 0;
		for(unsigned int c=0;c<n;c++){
			scanf("%lf %lf %lf %lf\n",cx+c,cy+c,cm+c,cr+c);
			mass += cm[c];
			tx += cx[c]*cm[c];
			ty += cy[c]*cm[c];
		}
		double cmx = tx/mass;
		double cmy = ty/mass;
		unsigned int yis=0, xis = 0;
		for(unsigned int c=0;c<n;c++){
			if(cmx>cx[c]-cr[c] and cmx<cx[c]+cr[c]) xis++;
			if(cmy>cy[c]-cr[c] and cmy<cy[c]+cr[c]) yis++;
		}
		//printf("Cutting along x=%lf causes %u intersections\n",cmx,xis);
		//printf("Cutting along y=%lf causes %u intersections\n",cmy,yis);
		if(xis>yis) printf("WE %.6lf\n",cmy);		
		else printf("NS %.6lf\n",cmx);
	}
}

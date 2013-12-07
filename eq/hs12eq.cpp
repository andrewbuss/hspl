#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <algorithm>
#include <stdlib.h>

using namespace std;
string line;
int ntests;
int ns[10];

#ifndef HELP
#define HELP 0
#endif

int main(){
	getline(cin,line);
	stringstream(line) >> ntests;
	for(unsigned int t=0;t<ntests;t++){
		memset(ns,-1,40);
		getline(cin,line);
		stringstream(line) >> ns[0] >> ns[1] >> ns[2] >> ns[3] >> ns[4] >> ns[5] >> ns[6] >> ns[7] >> ns[8] >> ns[9];
		int nns = 0;
		for(nns=0;nns<10&&ns[nns]>=0;nns++){
			if(HELP)printf("%d ",ns[nns]);
		}
		if(HELP)printf("\n");
		int nos = nns-1;
		for(unsigned int j=0;j<nos;j++){
			for(unsigned int i=0;i<(1<<(nos-1));i++){
				int left = ns[0]; 
				int right = ns[j+1];
				for(unsigned int k=0;k<j;k++){
					if(i&(1<<k)) left+=ns[k+1];
					else left-= ns[k+1];
				}
				for(unsigned int k=j;k<nos-1;k++){
					if(i&(1<<k)) right+=ns[k+2];
					else right -= ns[k+2];
				}
				if(HELP) printf("i %u j %u l %d r %d\n",i, j,left,right);
				if(right==left){
					printf("%u",ns[0]);
					for(unsigned int k=0;k<j;k++){
						if(i&(1<<k)) printf("+");
						else printf("-");
						printf("%u",ns[k+1]);
					}
					printf("=%u",ns[j+1]);
					for(unsigned int k=j;k<nos-1;k++){
						if(i&(1<<k)) printf("+");
						else printf("-");
						printf("%u",ns[k+2]);
					}
					printf("\n");
				}
			}
		}
	}
}

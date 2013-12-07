#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <stdlib.h>

#ifndef HELP
#define HELP 0
#endif

using namespace std;

unsigned int cache[100000];
int cache2[100000];
unsigned int u[100000];

unsigned int r;
unsigned int m;
unsigned int ntests;
unsigned int s;

unsigned int digitsum(unsigned int n){
	if(cache[n]) return cache[n];
	unsigned int nn = n;
	unsigned int total = 0;
	while(nn){
		total += nn%r;
		nn /= r;
	}
	cache[n] = total;
	return total;
}

int main(){
	memset(&cache,0,4*100000);
	memset(&cache2,0,4*100000);
	memset(&u,0,4*100000);
	string line;
	getline(cin,line);
	stringstream(line) >> r >> m >> ntests;
	for(int j=0;j<ntests;j++){
		getline(cin,line);
		unsigned int i;
		stringstream(line) >> i;
		if(i == 0){
			cout << "-1\n";
			continue;
		}
		s = i;
		u[0]=s;
		if(!cache2[s]){
			int n=0;
			while(s<m){
				s+=digitsum(s);
				if(s>m) break;
				if(s == m){
					unsigned int i=1;
					while(n>=0){
						cache2[u[n--]] = i++;
					}
					break;
				}
				if(cache2[s] > 0){
					unsigned int i=cache2[s]+1;
					while(n>=0){
						cache2[u[n--]] = i++;
					}
					break;
				}
				if(cache2[s]<0){
					while(n>=0){
						cache2[u[n--]] = -1;
					}
					break;
				}
				u[++n] = s;
			}
			if(s>m){
				while(n>=0){
					cache2[u[n--]] = -1;
				}
			}
		}
		cout << cache2[i] <<'\n';
	}
}
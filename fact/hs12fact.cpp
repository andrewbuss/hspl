#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <stdlib.h>

using namespace std;
string line;
int ntests;
static vector<unsigned int> factors[1000001];
static unsigned int nfactors[1000001];

#ifndef HELP
#define HELP 0
#endif

void factorize(unsigned int in){
	factors[in] = vector<unsigned int>();
	int n = in;
	for (int i = 2; i <= n / i; i++) {
		if(nfactors[n]){
			for(unsigned int j=0;j<nfactors[n];j++){
				factors[in].push_back(factors[n][j]);
			}  
			goto end;
		}
		while (n % i == 0) {
			factors[in].push_back(i);
			n /= i;
		}
	}
	if (n > 1) {
		factors[in].push_back(n);
	}
	end:
	nfactors[in] = factors[in].size();
}

int main(){
	memset(nfactors,0,400004);
	scanf("%u\n",&ntests);
	for(unsigned int i=2;i<=100000;i++){
		factorize(i);
	}
	for(unsigned int t=0;t<ntests;t++){
		static unsigned int bins[100001];
		memset(bins,0,400004);
		unsigned int an;
		scanf("%u\n",&an);
		for(unsigned int i=0;i<an;i++){
			int j;
			scanf("%u ",&j);
			for(unsigned int k=0;k<nfactors[j];k++) bins[factors[j][k]]++;
		}
		if(HELP){
			printf("Bins:\n");
			for(unsigned int k=0;k<100001;k++){
				if(bins[k]) printf("%u: %u\n",k,bins[k]);
			}
		}
		scanf("\n");
		unsigned int i=2;
		bool stop = false;
		while(1){
			if(i>100000) factorize(i);
			for(unsigned int j=0;j<nfactors[i];j++){
				if(bins[factors[i][j]]>0) bins[factors[i][j]]--;
				else{
					stop = true;
					break;
				}
			}
			if(stop)break;
			else{
				i++;
			}
		}
		printf("%u\n",i-1);
	}
}

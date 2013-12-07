#define MAXPRIME 50000000
#define MAXNPRIMES 3001134

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <algorithm>
#include <stdlib.h>

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
using namespace std;

struct test{
  int lb;
  int ub;
  unsigned int bins[14];
};

struct dv{
  int d;
  unsigned int sums[14];
};

unsigned char classes[MAXPRIME+1];
dv dvs[2000];
dv* ndv = &dvs[0];
test tests[1000];
test* ntest = &tests[0];
unsigned int cbins[14];
string line;
unsigned int ntests,a,b,maxb;

bool cmpdvs(const dv&a, const dv&b){
  if(a.d<b.d) return true; 
  else return false;
}

int main(){
  getline(cin,line);
  stringstream(line) >> ntests;
  for(int i=0;i<ntests;i++){
    getline(cin,line);
    stringstream(line) >> a >> b;
    maxb=max(maxb,b);
    ndv->d = a;
    memset(&(ndv++)->sums,0,14*4);
    ndv->d = b;
    memset(&(ndv++)->sums,0,14*4);
    ntest->lb = a;
    ntest->ub = b;
    memset(&(ntest->bins),0,14*4);
    ntest++;
  }
  sort(dvs,dvs+ntests*2, cmpdvs);
  memset(&classes, 1, 1*MAXPRIME+1);
  memset(&cbins, 0, 14*4);
  classes[0] = 0;
  classes[1] = 0;
  classes[2] = 1;
  classes[3] = 1;

  for(unsigned int i = 4; i <= maxb; i += 2) classes[i] = 0;
  for(unsigned int i = 9; i <= maxb; i += 6){
    classes[i-2] = 1;
    classes[i] = 0;
  }
  for(unsigned int i = 5; i <= maxb; i+=2){
    if(classes[i]){
      for(unsigned int j = 2*i; j <= maxb; j += i){
	if(classes[j+1]!=0) classes[j+1] = max(classes[i]+1,classes[j+1]);
	classes[j] = 0;
      }
    }
  }
  dv* edv = &dvs[ntests*2-1];
  for(ndv=&dvs[0];ndv<edv;ndv++){
    unsigned char* ci = &classes[ndv->d];
    unsigned char* de = &classes[(ndv+1)->d];
    for(int j=1;j<14;j++) ndv->sums[j] = cbins[j];
    while(ci<de) cbins[*(ci++)]++;
  }
  for(int j=1;j<14;j++) edv->sums[j] = cbins[j];
  for(int i=0;i<ntests*2;i++){
    //cout << "dv " << i << ": " << dvs[i].d << '\n';
    for(int j=1;j<14;j++){
      //cout << j << " " << dvs[i].sums[j] << '\n';
    }
  }
  for(int i=0;i<ntests;i++){
    printf("Case %u:\n",i+1);
    dv* bdv = &dvs[0];
    while(bdv->d != tests[i].lb) bdv++;
    edv = bdv+1;
    while(edv->d != tests[i].ub) edv++;
    //cout << "BDV " << bdv-&dvs[0] << '\n';
    //cout << "EDV " << edv-&dvs[0] << '\n';
    for(int j=1;j<14;j++) tests[i].bins[j] = edv->sums[j]-bdv->sums[j];
    tests[i].bins[classes[edv->d]]++;
    for(int j=1;j<14;j++){
      printf("There are %u primes in class %u.\n",tests[i].bins[j],j);
    }
    printf("\n");
  }
  return 0;
}

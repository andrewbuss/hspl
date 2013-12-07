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

struct pr{
  unsigned int p;
  unsigned int q;
  unsigned int s;
};

struct t{
  unsigned int p;
  unsigned int q;
  unsigned int r;
  unsigned int s;
};

pr* prs;
t* ts;
unsigned int ntests,n,m;
char** names;
string line;
unsigned int* w;

bool cmpscores(const pr&a, const pr&b){
  return (a.s<b.s);
}
int main(){
  getline(cin,line);
  stringstream(line) >> n;
  w = (unsigned int*) malloc(n*4);
  names = (char**)malloc(n*sizeof(char**));
  for(int i=0;i<n;i++){
    names[i] = (char*)malloc(16);
    getline(cin,line);
    int j=0;
    while(line[j] != ' ') names[i][j] = line[j++];
    names[i][j] = '\0';
    stringstream(&line[j+1]) >> w[i];
  }
  getline(cin,line);
  stringstream(line) >> m;
  prs = (pr*) malloc(sizeof(pr)*m*2);
  ts = (t*) malloc(sizeof(t)*m*m);
  for(int i=0;i<m*2;i+=2){
    getline(cin,line);
    char a[16];
    char b[16];
    int j=0,k=0;
    while(line[j]!=' ') a[k++]=line[j++];
    a[j++]='\0';
    k=0;
    while(line[j]) b[k++]=line[j++];
    b[k] = '\0';
    for(j=0;j<n;j++){
      if(!strcmp(a,names[j])) prs[i].p = j;
      if(!strcmp(b,names[j])) prs[i].q = j;
    }
    prs[i].s = 2*w[prs[i].p]+w[prs[i].q];
    prs[i+1].p = prs[i].q;
    prs[i+1].q = prs[i].p;
    prs[i+1].s = 2*w[prs[i+1].p]+w[prs[i+1].q];
    
  }
  sort(prs,&prs[m*2],cmpscores);
  for(int i=m;i<m*2;i++) cout << "P: " << names[prs[i].p] << " Q: " << names[prs[i].q] << " WS: " << prs[i].s << '\n';
  return 0;
}

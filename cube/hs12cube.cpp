#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;
unsigned short c[12][9];
unsigned short oc[12][9];

void printcube(){
  for(int y=0;y<9;y++){
    for(int x=0;x<12;x++){
      if(c[x][y] == '\0'){
	cout << "  ";
      }else{
	cout << c[x][y] << ' ';
      }
    }
    cout << '\n';
  }
}

void rotateface(int xo, int yo){
  for(int x=0;x<3;x++) for(int y=0;y<3;y++) oc[xo+x][yo+y]=c[xo+x][yo+y];
  c[xo+0][yo+0] = oc[xo+0][yo+2];
  c[xo+1][yo+0] = oc[xo+0][yo+1];
  c[xo+2][yo+0] = oc[xo+0][yo+0];
  c[xo+2][yo+1] = oc[xo+1][yo+0];
  c[xo+2][yo+2] = oc[xo+2][yo+0];
  c[xo+1][yo+2] = oc[xo+2][yo+1];
  c[xo+0][yo+2] = oc[xo+2][yo+2];
  c[xo+0][yo+1] = oc[xo+1][yo+2];
}

inline void cw(char s){
  switch(s){
  case 'F':
    rotateface(3,3);
    for(int i=0;i<3;i++){
      unsigned short n[4] = {c[2][5-i], c[3+i][2], c[6][3+i], c[5-i][6]};
      c[3+i][2] = n[0];
      c[6][3+i] = n[1];
      c[5-i][6] = n[2];
      c[2][5-i] = n[3];
    }
    break;
  case 'B':
    rotateface(9,3);
    for(int i=0;i<3;i++){
      unsigned short n[4]={c[8][5-i],c[5-i][0],c[0][3+i],c[3+i][8]};
      c[5-i][0] = n[0];
      c[0][3+i] = n[1];
      c[3+i][8] = n[2];
      c[8][5-i] = n[3];
    }
    break;
  case 'L':
    rotateface(0,3);
    for(int i=0;i<3;i++){
      unsigned short n[4]={c[11][5-i], c[3][i], c[3][3+i], c[3][6+i]};
      c[3][i] = n[0];
      c[3][3+i] = n[1];
      c[3][6+i] = n[2];
      c[11][5-i] = n[3];
    }
    break;
  case 'R':
    rotateface(6,3);
    for(int i=0;i<3;i++){
      unsigned short n[4]={c[5][5-i],c[5][2-i],c[9][3+i],c[5][8-i]};
      c[5][2-i] = n[0];
      c[9][3+i] = n[1];
      c[5][8-i] = n[2];
      c[5][5-i] = n[3];
    }
    break;
  case 'U':
    rotateface(3,0);
    for(int i=0;i<12;i++) oc[i][3] = c[i][3];
    for(int i=0;i<12;i++) c[i][3] = oc[(i+3)%12][3];
    break;
  case 'D':
    rotateface(3,6);
    for(int i=0;i<12;i++) oc[i][5] = c[i][5];
    for(int i=0;i<12;i++) c[(i+3)%12][5] = oc[i][5];
  }
}

int dc(int xo, int yo){
  bool cs[7]={false,false,false,false,false,false,false};
  for(int x=0;x<3;x++){
    for(int y=0;y<3;y++){
      cs[c[xo+x][yo+y]]=true;
    }
  }
  int t = 0;
  for(int i=0;i<7;i++) if(cs[i]) t++;
  return t;
}

int main(){
  string line;
  getline(cin,line);
  int nts;
  stringstream(line) >> nts;
  for(int x=0;x<12;x++) for(int y=0;y<9;y++) c[x][y]=0;
  for(int tc=0;tc<nts;tc++){
    getline(cin,line);
    for(int x=0;x<3;x++) for(int y=0;y<3;y++){
	c[3+x][3+y] = 1;
	c[9+x][3+y] = 2;
	c[0+x][3+y] = 3;
	c[6+x][3+y] = 4;
	c[3+x][0+y] = 5;
	c[3+x][6+y] = 6;
      }
    int i = 0;
    while(true){
      char s=line[i];
      if (s=='\0') break;
      else if (s=='\''){}
      else if (line[i+1] == '\''){
	cw(s);
	cw(s);
	cw(s);
      }
      else if(line[i+1] == '2'){
	cw(s);
	cw(s);
      }
      else{
	cw(s);
      }
      i++;
    }
    cout << dc(3,3) << ' ' << dc(6,3) << ' ' << dc(9,3) << ' ' << dc(0,3) << ' ' << dc(3,0) << ' ' << dc(3,6) <<'\n';
  }
  return 0;
}

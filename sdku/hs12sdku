#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <stdlib.h>

#ifndef HELP
#define HELP 0
#endif

using namespace std;
unsigned char board[9][9];
unsigned bool possible[9][9][9];

int main(){
	string line;
	for(unsigned int i=0;i<9;i++){
		getline(cin,line);
		stringstream(line) >> board[i][0] >> board[i][1] >> board[i][2] >> board[i][3] >> board[i][4] >> board[i][5] >> board[i][6] >> board[i][7] >> board[i][8];
	}
	for(int i=0;i<ntests;i++){
		getline(cin,line);
		stringstream(line) >> s;
		cout << cache2[s] <<'\n';
	}
}
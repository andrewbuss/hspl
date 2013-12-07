#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <stdlib.h>

#ifndef HELP
#define HELP 0
#endif

using namespace std;

static const unsigned int maskMax = 1 << 9;
static const unsigned int allSet = maskMax - 1;

static unsigned nset(unsigned int bits) {
	unsigned result = 0;
	unsigned int mask = 1;

	while(mask != maskMax) {
		if (bits & mask) result++;
		mask *= 2;
	}
	return result;
}

static inline unsigned int bitFor(unsigned num) {
	return 1 << (num - 1);
}

class Board {
	unsigned int rows[9];
	unsigned int cols[9];
	unsigned int blocks[3][3];
	unsigned int diag[2];
	unsigned int cells[9][9];

public:
	static const unsigned invalid = 10;

	Board() {
		unsigned i, j;
		for (i = 0; i < 9; i++) rows[i] = allSet;
		for (i = 0; i < 9; i++) cols[i] = allSet;
		diag[0] = allSet;
		diag[1] = allSet;
		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++)
				blocks[i][j] = allSet;
		for (i = 0; i < 9; i++)
			for (j = 0; j < 9; j++)
				cells[i][j] = invalid;
	}

	inline unsigned int candidates(unsigned i, unsigned j) {
		unsigned int rv = rows[i] & cols[j] & blocks[i/3][j/3];
		if(i == j) rv &= diag[0];
		if(i == 8-j) rv &= diag[1];
		return rv;
	}

	inline void set(unsigned i, unsigned j, unsigned n) {
		unsigned int bit = bitFor(n);
		rows[i] &= ~bit;
		cols[j] &= ~bit;
		if(i==j) diag[0] &= ~bit;
		if(i==8-j) diag[1] &= ~bit;
		blocks[i/3][j/3] &= ~bit;
		cells[i][j] = n;
	}

	inline void unset(unsigned i, unsigned j, unsigned n) {
		unsigned int bit = bitFor(n);
		rows[i] |= bit;
		cols[j] |= bit;
		blocks[i/3][j/3] |= bit;
		if(i==j) diag[0] |= bit;
		if(i==8-j) diag[1] |= bit;
		cells[i][j] = invalid;
	}

	bool min(unsigned xmin, unsigned xmax, unsigned ymin, unsigned ymax, unsigned &ox, unsigned &oy){
		bool found = false;
		unsigned count = 0;
		for (unsigned x = xmin; x < xmax; x++)
			for (unsigned y = ymin; y < ymax; y++)
				if (cells[x][y] == invalid &&(!found || nset(candidates(x, y)) < count)) {
					count = nset(candidates(x, y));
					ox = x;
					oy = y;
					found = true;
				}
		return found;
	}
	inline unsigned get(unsigned i, unsigned j) { return cells[i][j]; }
};

bool solve(Board &board, unsigned iMin, unsigned iMax, unsigned jMin, unsigned jMax, bool destructive, bool checkBlocks){
	if (checkBlocks) {
		for (unsigned i = 0; i < 3; i++)
			for (unsigned j = 0; j < 3; j++)
				if (!solve(board, i*3, i*3 + 3, j*3, j*3 + 3, false, false)) return false;
	}
	unsigned i,j;
	if (!board.min(iMin, iMax, jMin, jMax, i, j)) return true;
	unsigned num = 1;
	unsigned mask = bitFor(num);
	while(mask != maskMax) {
		if (board.candidates(i, j) & mask) {
			board.set(i, j, num);
			bool solved = (solve(board, iMin, iMax, jMin, jMax, destructive, checkBlocks));
			if (!solved || !destructive) board.unset(i, j, num);
			if (solved) return true;
		}
		mask *= 2;
		num++;
	}
	return false;
}

void showboard(Board& board){
	for(unsigned y=0;y<9;y++){
		for(unsigned x=0;x<9;x++){
			unsigned char c = board.get(x,y);
			if(c<10) printf("%u",c);
			else printf(" ");
		}
		printf("\n");
	}
}


int main(){
	Board b;
	string line;
	for(unsigned int y=0;y<9;y++){
		for(unsigned int x=0;x<9;){
			char c = getchar();
			if (c >= '1' && c <= '9'){
				b.set(x,y,c-'0');
				x++;
			}
			else if (c == '.'){
				x++;
			}
		}
	}
	if (solve(b, 0, 9, 0, 9, true, true)) showboard(b);
	return 0;
}
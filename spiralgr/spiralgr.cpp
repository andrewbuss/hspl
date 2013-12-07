#include <stdio.h>
#include <string.h>

#define MAXPRIME 40000
#define SQRTMAXPRIME 200
unsigned char board[SQRTMAXPRIME][SQRTMAXPRIME];
bool sieve[MAXPRIME+1];

int main(){
	sieve[0] = false;
	sieve[1] = false;
	sieve[2] = true;
	for(unsigned int i=3;i<=SQRTMAXPRIME;i+=2){
	for(unsigned int i=3;i<=MAXPRIME;i+=2){
		sieve[i] = true;
		sieve[i+1] = false;
	}
	for(unsigned int i=2;i<SQRTMAXPRIME;i++){
		if(!sieve[i]) continue;
		for(unsigned int j=i*3;j<=MAXPRIME;j+=2*i) sieve[j]=false;
	}
	for(unsigned int i=3;i<=100;i+=2){
		board[]
		if(sieve[i]) printf("%d ",i);
	}
	printf("\n");
}
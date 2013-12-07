#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <stdlib.h>

#ifndef HELP
#define HELP 0
#endif

struct Rect{
	int width;
	int height;
	unsigned int tlx;
	unsigned int tly;
	unsigned int i;
	bool rotated;
};

struct Node{
	Node* left;
	Node* right;
	Rect rect;
};

using namespace std;

Rect* insert(Node* node,Rect* rect){
	if(node->left or node->right){
		if(HELP) printf("Node is already split, trying left side\n");
		Rect* newnode = insert(node->left,rect);
		if(!newnode){
			if(HELP)printf("Couldn't fit into left side, trying right side\n");
			newnode = insert(node->right,rect);
		}
		return newnode;
	}else{  
		if(node->rect.i){
			if(HELP) printf("Node is occupied by rect #%u\n",node->rect.i);
			return NULL;
		}
		int dw = node->rect.width - rect->width;
        int dh = node->rect.height - rect->height;
        if(dw<0 or dh<0){
        	if(HELP) printf("Node (%u by %u) cannot fit rectangle\n",node->rect.width,node->rect.height);
			return NULL;
		}
        if(dw==0 and dh==0){
        	if(HELP) printf("Node fits rectangle perfectly\n");
        	return &(node->rect);
        }
        node->left = (Node*)malloc(sizeof(Node));
        node->right = (Node*)malloc(sizeof(Node));
        memset(node->left,0,sizeof(Node));
        memset(node->right,0,sizeof(Node));
        if(dw>dh){
        	if(HELP)printf("Splitting node horizontally\n");
        	node->left->rect.tlx = node->rect.tlx;
        	node->left->rect.tly = node->rect.tly;
        	node->left->rect.width = rect->width;
        	node->left->rect.height = node->rect.height;
        	node->right->rect.tlx = node->rect.tlx + rect->width;
        	node->right->rect.tly = node->rect.tly;
        	node->right->rect.width = node->rect.width-rect->width;
        	node->right->rect.height = node->rect.height;
        }else{
        	if(HELP)printf("Splitting node vertically\n");
        	node->left->rect.tlx = node->rect.tlx;
        	node->left->rect.tly = node->rect.tly;
        	node->left->rect.width = node->rect.width;
        	node->left->rect.height = rect->height;
        	node->right->rect.tlx = node->rect.tlx;
        	node->right->rect.tly = node->rect.tly+rect->height;
        	node->right->rect.width = node->rect.width;
        	node->right->rect.height = node->rect.height-rect->height;
        }
        return insert(node->left,rect);
	}
}

void cleanup(Node* node){
	if(node->left) cleanup(node->left);
	if(node->right) cleanup(node->right);
	free(node);
}

bool rectcmp(const Rect&a, const Rect&b){
	unsigned int la = a.width;
	if(a.height>la) la = a.height;
	unsigned int lb = b.width;
	if(b.height>lb) lb = b.height;
	return (la>lb);
}

int main(){
	int b = 0;
	clock_t st = clock();
	string line;
	getline(cin,line);
	unsigned int ntests;
	stringstream(line) >> ntests;
	for(int i=0;i<ntests;i++){
		getline(cin,line);
		Node root;
		root.rect.tlx = 0;
		root.rect.tly = 0;
		root.rect.i = 0;
		root.rect.rotated = false;
		memset(&root,0,sizeof(Node));
		stringstream(line) >> root.rect.width >> root.rect.height;
		if(HELP) printf("Box size: %u %u\n",root.rect.width,root.rect.height);
		vector<Rect> rects;
		getline(cin,line);
		unsigned int nrects;
		stringstream(line) >> nrects;
		for(unsigned int i=1;i<=nrects;i++){
			Rect r;
			r.i = i;
			r.tlx = 0;
			r.tly = 0;
			getline(cin,line);
			stringstream(line) >> r.width >> r.height;
			if(1 or (r.width>root.rect.width and r.height<root.rect.width) or (r.height>root.rect.height and r.width<root.rect.height)){
				r.rotated = true;
				int t=r.width;
				r.width = r.height;
				r.height = t;
			}else{
				r.rotated = false;
			}
			if(HELP){
				printf("Adding rectangle %i (%u x %u)",r.i,r.width,r.height);
				if(r.rotated) printf(" (rotated)");
				printf("\n");
			}
			rects.push_back(r);
		}
		if(root.rect.width <= 0 or root.rect.height <= 0){
			printf("0\n");
			continue;
		}
		sort(rects.begin(), rects.end(),rectcmp);
		vector<Rect> added;
		for(unsigned int i=0;i<nrects;i++){
			if(HELP) printf("Inserting rect #%u into root\n",rects[i].i);
			if(rects[i].width <= 0 or rects[i].height <= 0){
				if(HELP)printf("Zero area\n");
				continue;
			}
			Rect* r = insert(&root,&rects[i]);
			if(!r) continue;
			r->i = rects[i].i;
			r->rotated = rects[i].rotated;
			added.push_back(*r);
			if(HELP) printf("Rectangle %u (%u x %u) fits into box at (%u, %u)\n",r->i,r->width,r->height,r->tlx,r->tly);
			if(added.size()>2) break;
		}
		unsigned int box[1000][1000];
		memset(box,0,1000*1000*sizeof(int));
		bool error = false;
		for(unsigned int i=0;i<added.size();i++){
			Rect* r = &(added[i]);
			if(1){
				if(r->tlx+r->width>root.rect.width or r->tly+r->height>root.rect.height) error = true;
				for(unsigned int x=r->tlx;x<r->tlx+r->width;x++){
					for(unsigned int y=r->tly;y<r->tly+r->height;y++){
						if(box[x][y]){
							error = true;
						}else{
							box[x][y] = r->i;
						}
					}
				}
			}
		}
		if(0 or error){
			b = 100;
			printf("0\n");
		}
		else{
			printf("%u\n",added.size());
			for(unsigned int i=0;i<added.size();i++){
				Rect* r = &(added[i]);
				printf("%u %u %u ",r->i,r->tlx,r->tly);
				if(r->rotated) printf("o\n");
				else printf("o\n");
			}
		}
		if(root.left)cleanup(root.left);
		if(root.right)cleanup(root.right);
		//if(b) break;
	}
	while(1){
		if(((float)(clock()-st))/CLOCKS_PER_SEC>=(float)b/100) return 0;
	}
} 
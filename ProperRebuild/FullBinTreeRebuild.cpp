#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

const int SZ = 1<<20;  //fast io  
struct fastio{  
    char inbuf[SZ];  
    char outbuf[SZ];  
    fastio(){  
        setvbuf(stdin,inbuf,_IOFBF,SZ);  
        setvbuf(stdout,outbuf,_IOFBF,SZ);  
    }  
}io;  

//maximun number of nodes is 4000000
const size_t max_size = 4000010;
//traversal sequences
int preOrder[max_size]={0};
int postOrder[max_size]={0};
int inOrder[max_size]={0};

void rebuild(int pre_left, int pre_right, int post_left, int post_right){
	if(pre_right == pre_left )
/*		if(last_insert_position == post_left + 1){
			inOrder[post_left] = postOrder[post_left];
*/			return;
/*		}else if(last_insert_position  == post_left - 1){
			inOrder[post_left] = postOrder[post_left];
			return;
		}
*/	
	int i, j, k;
	for(i = post_left, j = 0; postOrder[i] != preOrder[pre_left +1]; ++i, j++)
		;
	
	inOrder[i+1] = preOrder[pre_left];
	for(k = post_right; k > i + 1; --k)
		postOrder[k] = postOrder[k-1];
	if(k != post_right)
		postOrder[k] = 0;
	
	rebuild(pre_left+1, pre_left+1+j, post_left, i);
	rebuild(pre_left+1+j+1, pre_right, i+2, post_right);

	return;
}


int main(){
	#ifndef _OJ_
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif
		int size;
		scanf("%d", &size);
		//get preorder and postorder traversal sequence
		for(int i = 0; i < size; ++i)
			scanf("%d", &preOrder[i]);
		//getchar();
		for(int i = 0; i < size; ++i)
			scanf("%d", &postOrder[i]);
		rebuild(0, size-1, 0, size-1);
		for(int i = 0; i < size; ++i){
			inOrder[i] += postOrder[i];
			printf("%d ", inOrder[i]);
		}
		return 0;
}

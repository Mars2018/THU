#include<iostream>
#include<cstdio>
#include<cstdlib>

//fast io
/*********************
 *  setvbuf(FILE *stream , char *buf, int type, unsigned size)
 *  type:
 *      _IOFBF: read from stream when buffer is empty, or write to stream when buffer is full
 *      _IOLBF: read from or write to stream by lines
 *      _IONBF: read from or write to stream without buffer
 *  size:
 *      size of buffer (bytes)
 *
 * *********************/
const size_t SZ = 1 << 20;
struct fastio{
    char inbuf[SZ];
    char outbuf[SZ];
    fastio(){
        setvbuf(stdin, inbuf, _IOFBF, SZ);
        setvbuf(stdout, outbuf, _IOFBF, SZ);
    }
}io;


const size_t max_number = 1600000;//maximum size is 1600000
int A[max_number];//Entering line A
int B[max_number];//Leaving line B
int S[max_number];//Station S
bool Operation[2*max_number];//store operation historis, TRUE for push(), FALSE for pop()

int main(){
    //IO redirection
#ifndef _OJ_
    freopen("input.txt", "r", stdin);
    freopen("output", "w", stdout);
#endif

    long line_size, station_size;//number of trains and the maximum trains station can contain
    scanf("%ld %ld", &line_size, &station_size);
    for(int i = 0; i < line_size; ++i)
        scanf("%d", &B[i]);
    for(int i = 0; i < line_size; i++)
        A[i] = i + 1;
    //three simulated pointers pointing to three arraies respectively
    size_t pointer_A(0), pointer_B(0), pointer_S(0);
    size_t op_size(0);//operation times
    bool end = false;
    while(end = !end){
        while(pointer_S < station_size && pointer_A < line_size && B[pointer_B] >= A[pointer_A]){
            S[++pointer_S] = A[pointer_A++];
            Operation[op_size++] = true;    
            end = false;
        }
        while(pointer_S > 0 && pointer_B < line_size && S[pointer_S] == B[pointer_B]){
            --pointer_S; ++pointer_B;
            Operation[op_size++] = false;
            end = false;
        }
    }
    if(pointer_B == line_size)
        for(int i = 0; i < op_size; ++i)
            if(Operation[i])
                printf("push\n");
            else
                printf("pop\n");
    else
        printf("No\n");

    return 0;
}

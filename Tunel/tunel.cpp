#include<cstdio>
#include<cstdlib>

using namespace std;

const size_t sz = 1 << 20;
struct fastio{
	char inbuf[sz];
	char outbuf[sz];
	fastio(){
		setvbuf(stdin, inbuf, _IOFBF, sz);
		setvbuf(stdout, outbuf, _IOFBF, sz);
	}
}io;

//maximum tunel length
const size_t max_sz = 2000010;
//simulate a queue by two stacks
long stack_push[max_sz];
long stack_pop[max_sz];
//simulate two pointers for pop and push operations
long stack_push_pointer(0),stack_pop_pointer(0);
//store max value for two stacks
long stack_push_max(0), stack_pop_max(0);

//push elements into enqueue stack
void stack_push_push(long e){
	//store the difference of element and maxvalue
	stack_push[++stack_push_pointer] = e - stack_push_max;
	//if the stored elements is negative, the max value should be the new element
	if(stack_push_max < e)					
		stack_push_max = e;
}

//pop elements to the dequeuing stack to be dequeued
long stack_push_pop(){
	if(stack_push_pointer < 1){
		printf("STACK_PUSH POP ERROR!\n");
		return 0;
	}
	long e;
	//if the poping element is not negative, the top element is the maxvalue
	//then the maxvalue should be changed.
	if(stack_push[stack_push_pointer] >= 0){
		e = stack_push_max;
		stack_push_max = stack_push_max - stack_push[stack_push_pointer];
	}else
		e = stack_push_max + stack_push[stack_push_pointer];//recover the oroginal value
	--stack_push_pointer;
	return e;
}

//push elements into dequeuing stack and record the max value
void stack_pop_push(long e){
	stack_pop[++stack_pop_pointer] = e - stack_pop_max;
	if(stack_pop_max < e)					
		stack_pop_max = e;
}
//dequeue from the dequeuing stack 
long stack_pop_pop(){
	if(stack_pop_pointer < 1){
		printf("STACK_POP POP ERROR!\n");
		return 0;
	}
	long e;
	if(stack_pop[stack_pop_pointer] >= 0){
		e = stack_pop_max;
		stack_pop_max = stack_pop_max - stack_pop[stack_pop_pointer];
	}else
		e = stack_pop_max + stack_pop[stack_pop_pointer];
	--stack_pop_pointer;
	return e;
}

int main(){
	//redirect IO

#ifndef _OJ_
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif	
	long op_size;//operation times;
	scanf("%ld", &op_size);
	getchar();
	char com_char;//command character
	long com_int;//command parameter
	long temp;
	while(op_size-- > 0){

		do{
			com_char = getchar();
		}while(com_char != 'E' && com_char != 'D' && com_char != 'M');
//		scanf("%c", &com_char);//get command character
//		if(com_char == 'E')//if enqueue, read the height of vehical
//			scanf("%ld", &com_int);
//		getchar();
		switch(com_char){
			case('E'):
				scanf("%ld", &com_int);
				stack_push_push(com_int);			
				break;
			case('D'):
				if(stack_pop_pointer == 0){
					for(long i = stack_push_pointer; i > 0; --i)
						stack_pop_push(stack_push_pop());
				}
				temp = stack_pop_pop();
				printf("%ld\n", temp);
				break;
			case('M'):
				temp = stack_push_max >= stack_pop_max ? stack_push_max : stack_pop_max;
				printf("%ld\n", temp);
				break;
			default:
				break;
		};
	
	}
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#define MAX 32

typedef struct{
	char item[MAX];
	int top;
}STACK;

void initStack(STACK *s){
	s->top = 0;
}

int isFull(STACK *s){
	if(s->top == MAX)
		return 1;
	return 0;
}

int isEmpty(STACK *s){
	if(s->top == 0)
		return 1;
	return 0;
}

int push(char x, STACK *s){
	if(isFull(s))
		return 0;
	s->item[s->top] = x;
	s->top++;
	return 1;
}

int pop(STACK *s, char *x){
	if(isEmpty(s))
		return 0;
	--s->top;
	*x = s->item[s->top];
	return 1;
}

char *decimalToBinary(int number, STACK *s, int *length){
	int len, multi_eight_len, i, j;
	char tmp, *binary, sign = '0';
	char *beforeComplement;
	if(number<0){
		sign = '1';
		number*=-1;
	}
	while(number != 0){
		tmp = '0' + number%2;
		push(tmp,s);
		number/=2;
	}
	len = s->top;
	beforeComplement = (char*)malloc(len*sizeof(char));
	i=0;
	while(!isEmpty(s)){
		pop(s,&beforeComplement[i]);
		i++;
	}
	if(sign == '1'){
		for(i=len;i>0;i--){						//Bu aþamada 1's complement tamamlanýyor
			if(beforeComplement[i-1] == '1')
				beforeComplement[i-1] = '0';
			else
				beforeComplement[i-1] = '1';
		}
		i=len;
		tmp = sign;		//çýkýþ kontrolünde sign deðiþmesin diye
		while(tmp == '1' && i>0){				//Burada da 2's complement tamamlanýyor
			if(beforeComplement[i-1] == '1'){
				beforeComplement[i-1] = '0';
				i--;
			}
			else{
				beforeComplement[i-1] = '1';
				tmp = '0';
			}
		}
	}
	multi_eight_len = len;
	while(multi_eight_len%8 != 0){
		multi_eight_len++;
	}
	binary = (char*)malloc(multi_eight_len*sizeof(char));
	for(i=0;i<multi_eight_len - len;i++){
		binary[i] = sign;
	}
	j = i;
	for(i;i<multi_eight_len;i++){
		binary[i] = beforeComplement[i - j];
	}
	free(beforeComplement);
	*length = multi_eight_len;
	return binary;
}

int difference(char *binary, int len, STACK *s){
	int i, diff = 0;
	char trash;
	for(i=0;i<len;i++){
		if(binary[i] == '0'){
			push(binary[i],s);
		}
		else{
			if(!pop(s,&trash)){
				diff--;
			}
		}
	}
	diff += s->top;
	initStack(s);
	return diff;
}

int main(){
	STACK *s = (STACK*)malloc(sizeof(STACK));
	initStack(s);
	int number, len, diff;
	char *binary;
	
	printf("Enter the number: ");
	scanf("%d",&number);
	if(number == 0)
		diff = 8;
	else{
		binary = decimalToBinary(number,s,&len);
		diff = difference(binary,len,s);
	}
	if(diff < 0){
		printf("1'ler fazladir. Ek %d adet 0 gereklidir.\n",diff*-1);
	}
	else if(diff == 0){
		printf("0 ve 1'ler esit sayidadir.\n");
	}
	else{
		printf("0'lar fazladir. Ek %d adet 1 gereklidir.\n",diff);
	}
	return 0;
}

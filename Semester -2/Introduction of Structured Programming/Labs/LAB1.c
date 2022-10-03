#include<stdio.h>

/*
*	This is about finding missing number of
*	a sequential array with O(log(N)) complexity
*/

int main(){
	int n, dizi[100], i, bas, son, orta;
	
	printf("Dizinin eleman sayisini giriniz.\n");
	scanf("%d",&n);
	
	for(i = 0;i < n;i++)
	{
		printf("%d. eleman : ",i+1);
		scanf("%d",&dizi[i]);
	}
	
	if(dizi[0]+n-1==dizi[n-1])
		printf("No missing value");
	else
	{
		bas=0;
		son=n-1;
		orta=(bas+son+1)/2;
		while(orta!=son){
			if(dizi[bas]+(son-bas+1)/2==dizi[orta])
				bas=orta;
			else
				son=orta;
			orta=(bas+son+1)/2;
		}
		printf("%d",dizi[bas]+1);
	}
	
	return 0;
}

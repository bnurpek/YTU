#include <stdio.h>
#include "degerler.h"

int main(){
	int ari[SIZE];
	int i, minMaliyet=1000, j, bestCost;
	
	printf("Population size: %d\n",SIZE);
	printf("Iteration number: %d\n",ITERASYON);
	
	printf("Initial Population:\n");	
	for(i=0;i<SIZE;i++){
		ari[i] = rand() % 20 +5;
		printf("%d	",ari[i]);
	}
	printf("\n");

	for(i=0;i<SIZE;i++){
			if(MALIYET(ari[i]) < minMaliyet){
				minMaliyet = MALIYET(ari[i]);
		}
	}
	printf("Initial Best Cost: %d value\n",minMaliyet);
	
	minMaliyet = 1000;
	bestCost = 1000;
	j=0;
	while(j<ITERASYON){
		printf("Initial Population:\n");
		for(i=0;i<SIZE;i++){
			ari[i] = rand() % 20 + 5;
			printf("%d	",ari[i]);
		}
		printf("\n");
		minMaliyet = 1000;
		for(i=0;i<SIZE;i++){
			if(MALIYET(ari[i]) < minMaliyet){
				minMaliyet = MALIYET(ari[i]);
			}
		}
		printf("Best Cost in iteration-%d: %d value\n",j+1,minMaliyet);
		if(minMaliyet < bestCost){
			bestCost = minMaliyet;
		}
		j++;
	}
	
	printf("Best Cost in all iterations: %d",bestCost);
	
	
	return 0;
}

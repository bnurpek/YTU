#include <stdio.h>

#define max 20

int main(){
	float A[max][max], Aters[max][max];
	float tmp;
	int N;
	int i, j, k;
	
	do{
		printf("Kare matris boyutunu giriniz.\n");
		scanf("%d",&N);
	} while(N > max);
	
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			Aters[i][j] = 0.0;
		}
		Aters[i][i] = 1;
	}
	
	printf("Matris elemanlarini giriniz.\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("eleman[%d][%d]= ",i,j);
			scanf("%f",&A[i][j]);
		}
	}
	
	for(i=0;i<N;i++){
		tmp = A[i][i];
		if(tmp!=0){
			for(j=0;j<N;j++){
				A[i][j]/=tmp;
				Aters[i][j]/=tmp;
			}
		}
		for(k=0;k<i;k++){
			tmp = A[k][i];
			for(j=0;j<N;j++){
				A[k][j]= A[k][j] - tmp*A[i][j];
				Aters[k][j] = Aters[k][j] - tmp*Aters[i][j];
			}
		}
		for(k=i+1;k<N;k++){
			tmp = A[k][i];
			for(j=0;j<N;j++){
				A[k][j]=A[k][j] - tmp*A[i][j];
				Aters[k][j] = Aters[k][j] - tmp*Aters[i][j];
			}
		}
	}
	
	printf("Matrisin Inversi\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("| %.2f ",Aters[i][j]);
		}
		printf("|\n");
	}
	
	
	return 0;
}

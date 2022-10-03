#include <stdio.h>

#define max 20

int main(){
	float A[max][max], C[max];
	float X[max];
	float tmp;
	int N;
	int i, j, k;
	
	do{
		printf("Kare matris boyutunu giriniz.\n");
		scanf("%d",&N);
	} while(N > max);
	
	for(i=0;i<N;i++){
		X[i]=0;
	}
	
	printf("Matris elemanlarini giriniz.\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%d. denklemin %d. bilinmeyeninin katsayisi: ",i+1,j+1);
			scanf("%f",&A[i][j]);
		}
		printf("%d. denklemin sonucu: ",i+1);
		scanf("%f",&C[i]);
	}
	
	for(i=0;i<N;i++){
		tmp = A[i][i];
		if(tmp!=0){
			for(j=0;j<N;j++){
				A[i][j]/=tmp;
			}
			C[i]/=tmp;
		}
		for(k=i+1;k<N;k++){
			tmp = A[k][i];
			for(j=0;j<N;j++){
				A[k][j]=A[k][j] - tmp*A[i][j];
			}
			C[k]=C[k] - tmp*C[i];
		}
	}
	
	printf("Matrisin Inversi\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("| %.2f ",A[i][j]);
		}
		printf("|\n");
	}
	
	X[N-1]=C[N-1];
	for(i=N-2;i>=0;i--){
		tmp=0;
		for(j=N-1;j>=0;j--){
			tmp+=X[j]*A[i][j];
		}
		X[i]=C[i]-tmp;
	}
	
	printf("Kokler\n");
	for(i=0;i<N;i++){
		printf("x%d = %f\n",i+1,X[i]);
	}
	
	return 0;
}

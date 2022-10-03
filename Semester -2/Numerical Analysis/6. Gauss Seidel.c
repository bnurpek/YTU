#include <stdio.h>
#define MAX 10

int kontrol(float arr[MAX], float hata, int N){
	int i=0;
	while(i<N && arr[i]<hata){
		i++;
	}
	if(i==N){
		return 0;
	}
	return 1;
}

void hesapla(float X[MAX], float C[MAX], float A[MAX][MAX], int i, int N, float delta[MAX]){
	int j;
	float ara=0.0;
	float tmp;
	
	tmp = X[i];
	
	for(j=0;j<i;j++){
		ara = ara + A[i][j]*X[j]; 
	}
	for(j=i+1;j<N;j++){
		ara = ara + A[i][j]*X[j];
	}
	
	X[i] = (C[i] - ara) / A[i][i];
	delta[i] = tmp - X[i];
	if(delta[i]<0){
		delta[i] = delta[i] * -1;
	}
}

int main(){
	float A[MAX][MAX], C[MAX];
	float X[MAX], delta[MAX];
	int N, i, j;
	float hata;
	
	printf("Bilinmeyen sayisini giriniz.\n");
	scanf("%d",&N);
	
	printf("Sirayla bilinmeyenlerin bas kat sayilarini ve denklem sonuclarini giriniz.\n");
	printf("Girdiginiz sirada diyagonelde yer alan katlar carpimi mutlak deðerce maksimum olmali.\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%d. denklemin %d. bilinmeyeninin kat sayisi: ",i+1,j+1);
			scanf("%f",&A[i][j]);
		}
		printf("%d. denklem sonucu: ",i+1);
		scanf("%f",&C[i]);
	}
	
	printf("Bilinmeyenlerin baslangic degerlerini giriniz, sirayla.\n");
	for(i=0;i<N;i++){
		scanf("%f",&X[i]);
	}
	
	printf("Hata payini giriniz: ");
	scanf("%f",&hata);
	
	for(i=0;i<N;i++){
		delta[i]=1000;
	}
	
	while(kontrol(delta,hata,N)){
		for(i=0;i<N;i++){
			hesapla(X,C,A,i,N,delta);
		}
	}
	
	for(i=0;i<N;i++){
		printf("x[%d] : %.3f\n",i,X[i]);
	}
	
	return 0;
}

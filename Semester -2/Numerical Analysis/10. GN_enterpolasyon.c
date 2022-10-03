#include <stdio.h>

void hesapla(float mtr[20][20], float x, int derece, float h){
	float k, pay, payda;
	int j;
	float result = 0.0;
	
	k = (x - mtr[0][0]) / h;
	pay = k;
	payda = 1;
	
	for(j=1;j<derece;j++){
		result = result + pay * mtr[j][j+1] / payda;
		pay = pay * (k - j);
		payda = payda * (j+1);
	}
	result = result + mtr[0][1];
	printf("%f'in degeri : %f\n", x, result);
}

int kontrol(int C, int R, float mtr[C][C], int i){
	int j;
	j = R;
	while(j>i&&mtr[j][i]==mtr[j-1][i]){
		j--;
	}
	if(j==i){
		return 0;
	}
	return 1;
}

int main(){
	float tablo[20][20];
	float h;
	float X;
	int i, max;
	int j, s;
	
	printf("Kac deger oldugunu giriniz: ");
	scanf("%d",&max);
	
	for(i=0;i<max;i++){
		printf("%d. x ve y degerini art arda giriniz: ",i+1);
		scanf("%f %f",&tablo[i][0],&tablo[i][1]);
	}
	
	h = tablo[1][0] - tablo[0][0];
	
	i=1;
	while(i<20 && kontrol(20,max,tablo,i)){
		for(j=max-1;j>i-1;j--){
			tablo[j][i+1] = tablo[j][i] - tablo[j-1][i];
		}
		i++;
	}
	
	printf("Hangi degerin hesaplanmasini istiyorsaniz giriniz: ");
	scanf("%f",&X);
	
	hesapla(tablo,X,i,h);
	
	//print Matris
	for(j=0;j<max;j++){
		for(s=0;s<i;s++){
			printf("%.3f ",tablo[j][s]);
		}
		printf("\n");
	}
	
	return 0;
}

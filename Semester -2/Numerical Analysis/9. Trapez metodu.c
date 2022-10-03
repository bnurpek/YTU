#include <stdio.h>

#define MAX 40

float fonksiyon_hesabi(int *kat_sayilar, int derece, float x){
	float sum=kat_sayilar[derece];
	float tmp; 
	int i, j;
	for(i=0;i<derece;i++){
		tmp=1.0;
		for(j=i;j<derece;j++){
			tmp=tmp*x;
		}
		sum = sum + tmp * kat_sayilar[i];
	}
	return sum;
}

int main(){
	float Baslangic, Bitis, degerler[MAX];
	int n, derece, katlar[MAX];
	int i;
	float alan, h;
	float araToplam=0.0;
	
	do{
		printf("Fonksiyonun derecesini giriniz: ");
		scanf("%d", &derece);
	}while(MAX < derece);
	
	for(i = derece;i >= 0;i--){
		printf("%d. derecenin kat sayisini giriniz : ",i);
		scanf("%d",&katlar[derece-i]);
	}
	
	printf("Hesaplanmak istenen araligi giriniz. Ornek: 0 1\n");
	scanf("%f %f",&Baslangic,&Bitis);
	
	printf("n degerini giriniz.\n");
	scanf("%d",&n);
	
	h = (Bitis - Baslangic) / n;
	for(i=0;i<n+1;i++){
		degerler[i]=fonksiyon_hesabi(katlar, derece, Baslangic + i*h);
	}
	
	for(i=1;i<n;i++){
		araToplam+=degerler[i];
	}
	
	alan = h * ((degerler[0]+degerler[n]) / 2 + araToplam);
	
	printf("Integral degeri: %f",alan);
	
	return 0;
}

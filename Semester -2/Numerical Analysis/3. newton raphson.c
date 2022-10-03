#include<stdio.h>

#define MAX_Length 20

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
	int katlar[MAX_Length], turevKatlar[MAX_Length], derece, i;
	float epsilon, hata;
	float ilk, c, id1, id2, idC=1;
	
	do{
		printf("Fonksiyonun derecesini giriniz: ");
		scanf("%d", &derece);
	}while(MAX_Length < derece);
	
	for(i = derece;i >= 0;i--){
		printf("%d. derecenin kat sayisini giriniz : ",i);
		scanf("%d", &katlar[derece-i]);
	}
	
	printf("Turevin katsayilarini giriniz.\n");
	for(i = derece-1;i >= 0;i--){
		printf("%d. derecenin kat sayisini giriniz : ",i);
		scanf("%d", &turevKatlar[derece-1-i]);
	}
	
	printf("Baslangic degeri giriniz. Ornek: 0.75\n");
	scanf("%f", &ilk);
	
	printf("Hata payini giriniz. Ornek: 0.001\n");
	scanf("%f", &epsilon);
	
	do{
		id1 = fonksiyon_hesabi(katlar,derece,ilk);
		id2 = fonksiyon_hesabi(turevKatlar,derece-1,ilk);
		c = ilk - (id1/id2);
		hata = c - ilk;
		ilk = c;
	} while(hata>epsilon);

	printf("Kok : %f",c);
	
	return 0;
}

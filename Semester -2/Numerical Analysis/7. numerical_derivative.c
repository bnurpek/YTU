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
	int katlar[MAX_Length], derece;
	int i;
	float nokta, h, id1, id2, id3, tmp;
	
	do{
		printf("Fonksiyonun derecesini giriniz: ");
		scanf("%d", &derece);
	}while(MAX_Length < derece);
	
	for(i = derece;i >= 0;i--){
		printf("%d. derecenin kat sayisini giriniz : ",i);
		scanf("%d",&katlar[derece-i]);
	}
	
	printf("Hesaplamak istediginiz degeri ve farki (h) giriniz. Ornek: 1 0.5\n");
	scanf("%f %f",&nokta, &h);
	
	id1 = fonksiyon_hesabi(katlar,derece,nokta-h);
	id2 = fonksiyon_hesabi(katlar,derece,nokta);
	id3 = fonksiyon_hesabi(katlar,derece,nokta+h);
	
	tmp = (id3 - id2) / h;
	printf("Ileri fark ile  : %f\n", tmp);
	tmp = (id2 - id1) / h;
	printf("Geri fark ile   : %f\n", tmp);
	tmp = (id3 - id1) / (2*h);
	printf("Merkezi fark ile: %f", tmp);
	
	return 0;
}

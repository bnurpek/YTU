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
	int katlar[MAX_Length], derece, i, iterasyon;
	float bas, son, epsilon, hata, c, id1, id2, idC=1;
	
	do{
		printf("Fonksiyonun derecesini giriniz: ");
		scanf("%d", &derece);
	}while(MAX_Length < derece);
	
	for(i = derece;i >= 0;i--){
		printf("%d. derecenin kat sayisini giriniz : ",i);
		scanf("%d", &katlar[derece-i]);
	}
	
	printf("Aralik degerini giriniz. Ornek: 0 1\n");
	scanf("%f %f",&bas,&son);
	
	printf("Hata payini giriniz. Ornek: 0.001\n");
	scanf("%f",&epsilon);
	
	id1 = fonksiyon_hesabi(katlar,derece,bas);
	id2 = fonksiyon_hesabi(katlar,derece,son);
	do{
		if(id1 * id2 <0){
			iterasyon*=2;
			hata = (son-bas)/iterasyon;
			if(hata < 0)
				hata*=-1;
			
			c  = (bas*id2 - son*id1) / (id2 - id1);
			idC = fonksiyon_hesabi(katlar,derece,c);
			
			if(id1 * idC < 0){
				son = c;
				id2 = idC;
			} else if(idC * id2 < 0){
				bas = c;
				id1 = idC;
			} else
				hata = 0;
		} else if(id1 * id2 > 0){
			printf("Aralikta kök yok.\n");
			hata = -1;
		} else
			hata = 0;
	}while(hata > epsilon);
	
	if(hata == 0){
		if(id1 == 0)
			printf("Kok : %f", bas);
		else if(id2 == 0)
			printf("Kok : %f", son);
		else
			printf("Kok : %f", c);
	}
	else if(hata != -1)
		printf("Kok : %f", c);
	
	return 0;
}

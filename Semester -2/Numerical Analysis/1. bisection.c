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
	int katlar[MAX_Length], derece, iterasyon, i;
	float hata, epsilon;
	float bas, son, orta, id1, id2, id3=1;
	
	do{
		printf("Fonksiyonun derecesini giriniz: ");
		scanf("%d", &derece);
	}while(MAX_Length < derece);
	
	for(i = derece;i >= 0;i--){
		printf("%d. derecenin kat sayisini giriniz : ",i);
		scanf("%d",&katlar[derece-i]);
	}
	
	printf("Aralik degerini giriniz. Ornek: 0 1\n");
	scanf("%f %f",&bas,&son);
	
	printf("Hata payini giriniz. Ornek: 0.001\n");
	scanf("%f",&epsilon);
	
	id1 = fonksiyon_hesabi(katlar,derece,bas);
	id2 = fonksiyon_hesabi(katlar,derece,son);
	iterasyon = 1;
	do{
		if(id1 * id2 < 0){
			iterasyon*=2;
			
			hata = (son - bas) / iterasyon;
			if(hata < 0)
				hata*=-1;
			
			orta = (bas + son) /2;
			id3 = fonksiyon_hesabi(katlar,derece,orta);
			
			if(id1 * id3 <0){
				son = orta;
				id2 = id3;
			} else if(id3 * id2 <0){
				bas = orta;
				id1 = id3;
			} else
				hata = 0;
		} else if(id1 * id2 > 0){
			hata = -1;
			printf("Aralikta kok yok.\n");
		} else
			hata = 0;
	}while(hata > epsilon);
	
	if(hata==0){
		if(id3==0)
			printf("Kok : %f",orta);
		else if(id2 == 0)
			printf("Kok : %f",son);
		else
			printf("Kok : %f",bas);
	}
	else if(hata!=-1){
		printf("Kok : %f",orta);
	}
	
	return 0;
}

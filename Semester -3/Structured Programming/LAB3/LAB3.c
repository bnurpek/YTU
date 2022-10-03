#include <stdio.h>
#include <stdlib.h>
typedef struct arac{
	char *model;
	int yil;
	int fiyat;
	int adet;
}ARAC;

void sort(struct arac arr[], const int N, int(*comp)(char *ch1, char *ch2));
int artan(char *ch1, char *ch2);
int azalan(char *ch1, char *ch2);
void swap(struct arac *a,struct arac *b);


int main(){
	ARAC *ar;
	int i;
	int N=3, secim, sira;
	char *s;
	ar = (ARAC*)malloc(N*sizeof(ARAC));
	
	ar[0].model = "FiatModel1";
	ar[0].yil = 2019;
	ar[0].fiyat = 200000;
	ar[0].adet = 3;
	
	ar[1].model = "Mercedes1";
	ar[1].yil = 2020;
	ar[1].fiyat = 600000;
	ar[1].adet = 10;
	
	ar[2].model = "RenaultModel1";
	ar[2].yil = 2020;
	ar[2].fiyat = 185000;
	ar[2].adet = 5;
	
	printf("MENU\n");
	printf("Arac eklemek icin 1\nVar olan listeyle devam etmek icin 2\nCýkýs icin 3 giriniz.\n");
	scanf("%d",&secim);
	while(secim!=3){
		if(secim==1){
			N++;
			ar = (ARAC*)realloc(ar,N);
			printf("Aracin modelini giriniz: ");	scanf("%s",&s);
			ar[N-1].model = s;
			printf("Aracin yili: ");	scanf("%d",&ar[N-1].yil);
			printf("Aracin fiyati: ");	scanf("%d",&ar[N-1].fiyat);
			printf("Aracin adeti: ");	scanf("%d",&ar[N-1].adet);
		}
		else if(secim==2){
			printf("Artan siralama icin 1, azalan siralama icin 2 giriniz.\n");
			scanf("%d",&sira);
			if(sira == 1)
				sort(ar,N,artan);
			else
				sort(ar,N,azalan);
			printf("Siralandi:\n");
			for(i = 0; i<N; i++){
				printf("%s,\t%d,\t%d,\t%d\n",ar[i].model,ar[i].yil,ar[i].fiyat,ar[i].adet);
			}
		}
		else{
			printf("Gecerli olmayan bir komut girdiniz.\n");
		}
		printf("Arac eklemek icin 1\nVar olan listeyle devam etmek icin 2\nCýkýs icin 3 giriniz.\n");
		scanf("%d",&secim);
	}
	
	
	free(ar);
	
	return 0;
}

void sort(struct arac arr[], const int N, int(*comp)(char *ch1, char *ch2)){
	int i, j, minOrMax;
	for(i=0;i<N-1;i++){
		minOrMax = i;
		for(j=i+1;j<N;j++){
			if(comp(arr[i].model,arr[j].model)){
				minOrMax = j;
			}
		}
	}
	swap(&arr[i], &arr[minOrMax]);
}

int artan(char *ch1, char *ch2){
	return strcmp(ch1,ch2);
}

int azalan(char *ch1, char *ch2){
	return strcmp(ch2,ch1);
}
void swap(struct arac *a,struct arac *b){
	struct arac tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

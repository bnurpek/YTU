#include <stdio.h>
#include <stdlib.h>
#define MAX 30

typedef struct edge{
	int u, v, w;
}EDGE;

typedef struct{
	EDGE data[MAX];
	int n;
}EDGE_LIST;

typedef struct{
	int index[MAX], len;
}DONGU;

EDGE_LIST dosyaEkle(char *dosyaAdi, EDGE_LIST spanlist){
	FILE *fp = fopen(dosyaAdi, "r");
	char buffer[255];
	int i = 0;
	while(fgets(buffer,255,fp)!=NULL){
		sscanf(buffer,"%d %d %d",&spanlist.data[i].w,&spanlist.data[i].u,&spanlist.data[i].v);
		i++;
	}
	spanlist.n = i;
	return spanlist;
}

EDGE_LIST sort(EDGE_LIST list){
	EDGE key;
	int i, j;
	for(i=0;i<list.n;i++){
		key = list.data[i];
		j=i-1;
		while(j>-1 && list.data[j].w > key.w){
			list.data[j+1] = list.data[j];
			j--;
		}
		list.data[j+1] = key;
	}
	return list;
}

DONGU findCycle(EDGE_LIST slist, DONGU dongu, int u, int v){
	int flag = 0, i, j;
	if(u == v)
		return dongu;
	else{
		i=0;
		while(i!=slist.n && flag == 0){
			if(slist.data[i].u == v || slist.data[i].v == v){
				j=0;
				while(j != dongu.len && dongu.index[j] != i){
					j++;
				}
				if(j == dongu.len){
					dongu.index[dongu.len] = i;
					dongu.len++;
					if(slist.data[i].u == v){
						dongu = findCycle(slist,dongu,u,slist.data[i].v);
					}
					else{
						dongu = findCycle(slist,dongu,u,slist.data[i].u);
					}
					if(dongu.len > 0 && (slist.data[dongu.index[dongu.len-1]].u == u || slist.data[dongu.index[dongu.len-1]].v == u))
						return dongu;
				}
			}
			i++;
		}
		if(u != v){
			dongu.len--;
		}
	}
	return dongu;
}

void printMenu(){
	printf("----------MENU----------\n");
	printf(" 1 - Yeni kenar ekleme\n");
	printf("-1 - Cikis\n");
	printf("Created by Buse Nur PEKMEZCI - 20011001\n");
	printf("Secim: ");
}

void print_MST(EDGE_LIST spanlist){
	int i;
	printf("\n\nMST:\n");
	for(i=0;i<spanlist.n;i++){
		printf("%d %d %d\n",spanlist.data[i].w,spanlist.data[i].u,spanlist.data[i].v);
	}
	printf("\n");
}

int find_max_index(int w, DONGU dongu, EDGE_LIST spanlist){
	int max = w, maxIndex = -1;
	int i;
	for(i=0;i<dongu.len;i++){
		if(max < spanlist.data[dongu.index[i]].w){
			max = spanlist.data[dongu.index[i]].w;
			maxIndex = i;
		}
	}
	return maxIndex;
}

int main(){
	char dosyaAdi[MAX];
	EDGE_LIST spanlist;
	DONGU dongu;
	int	secim;
	int max, maxIndex;
	int flag = 1;
	int i, w, u, v;

	printf("----------MENU----------\n");
	printf("Dosya adi giriniz: ");
	scanf("%s",dosyaAdi);
	spanlist = dosyaEkle(dosyaAdi, spanlist);
	print_MST(spanlist);
	
	do{
		printMenu();
		scanf("%d",&secim);
		if(secim == 1){
			printf("Yeni kenar (w, u, v): ");
			scanf("%d %d %d",&w,&u,&v);
			dongu.len = 0;
			dongu = findCycle(spanlist, dongu, u, v);
			maxIndex = find_max_index(w,dongu,spanlist);
			if(maxIndex != -1){
				spanlist.data[dongu.index[maxIndex]].u = u;
				spanlist.data[dongu.index[maxIndex]].v = v;
				spanlist.data[dongu.index[maxIndex]].w = w;
				spanlist = sort(spanlist);
			}
			dongu.len = 0;
			print_MST(spanlist);
		}
	}while(secim!=-1);
	return 0;
}

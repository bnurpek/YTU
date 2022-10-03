#include <stdio.h>

#define R 20
#define C 20

/*
*	This program convert a dense matrix to
*	sparse matrix and sparse to dense
*/

int main(){
	int id, se[R][C], si[R][3], m, n;
	int i, j, k, max;
	
	do{
		printf("Menu:\n");
		printf("(1) Seyrek matristen sikistirilmis matrise\n");
		printf("(2) Sikistirilmis matristen seyrek matrise\n");
		printf("(3) Cikis\n");
		scanf("%d", &id);
		
		if(id==1){
			do{
				printf("Matrisin boyutlarini girin (satir, sutun): ");
				scanf("%d %d", &m, &n);
			}while(m>R && n>C);
	
			printf("Matrisin elemanlarini giriniz\n");
			for(i=0;i<m;i++){
				for(j=0;j<n;j++){
					printf("[%d][%d]: ",i,j);
					scanf("%d", &se[i][j]);
				}
			}
			
			k=0;
			for(i=0;i<m;i++){
				for(j=0;j<n;j++){
					if(se[i][j]!=0){
						si[k][0]=i;
						si[k][1]=j;
						si[k][2]=se[i][j];
						k++;
					}
				}
			}
			for(i=0;i<k;i++){
				for(j=0;j<3;j++){
					printf("| %3d ", si[i][j]);
				}
				printf("|\n");
			}
		}
		
		else if(id==2){
			printf("Matriste kac tane sifirdan farkli eleman var(sikistirilmis matriste satir sayisi)?\n");
			scanf("%d", &k);
			for(i=0;i<k;i++){
					printf("%d. eleman icin satir, sutun ve degeri girin\n",i+1);
					scanf("%d %d %d", &si[i][0], &si[i][1], &si[i][2]);
			}
			
			printf("Sikistirilmis matris\n");
			for(i=0;i<k;i++){
				for(j=0;j<3;j++){
					printf("| %3d ", si[i][j]);
				}
				printf("|\n");
			}
			
			max=0;
			for(i=0;i<k;i++){
				for(j=0;j<2;j++){
					if(max < si[i][j])
						max = si[i][j];
				}
			}
			
			for(i=0;i<=max;i++){
				for(j=0;j<=max;j++){
					se[i][j]=0;
				}
			}
			
			for(i=0;i<=k;i++){
				se[si[i][0]][si[i][1]] = si[i][2];
			}
			
			printf("Seyrek matris\n");
			for(i=0;i<=max;i++){
				for(j=0;j<=max;j++){
					printf("| %3d ", se[i][j]);
				}
				printf("|\n");
			}
		}
	}while(id!=3);
	
	return 0;
}

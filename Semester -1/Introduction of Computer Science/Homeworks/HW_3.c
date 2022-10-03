#include<stdio.h>

/*
*	This project is about basic dictionary sort and search
*	algorithm. I think I used bubble sort in this hw.
*	Cause this is the only sorting algorithm I know really well
*	at first semester.
*/

int main(){
	int n, i, j, k, l, min, alphabet[25], count1, count2, dongu, yer1, yer2, harf; //n=girilen sözcük sayýsý ; alphabet=Baþ harflerin ilk sýrasý
	char dictionary[50][50], word[20], tmp[50][50]; //dictionary=girilen sözcüklerin saklandýðý matris ; word=aranacak kelimeyi tutan dizi ; tmp=sözcükleri sýralamak için kullandýðým ara matris
	printf("Kac kelime oldugunu giriniz.\n");
	scanf("%d", &n);
	printf("\n");
	for(i=0;i<n;i++){
		printf("%d. kelime: ", i+1);
		scanf("%s", &dictionary[i]);
	}
	printf("Aradiginiz kelime: \n");
	scanf("%s", &word);
	for(i=0;i<n-1;i++){
		min=i; //ASCII tablosunu düþünerek harfleri sayý gibi düþünüp alfabede sýrasý daha önce olan harfi en küçük sayýymýþ gibi aldým ve bubble sortun iyileþtirilmiþ versiyonundan faydalandým
		for(j=i+1;j<n;j++){
			k=0;
			while(k<n){
				if(dictionary[j][k]<dictionary[min][k]){
					min=j;
					k=n;
				}
				else if(dictionary[j][k]==dictionary[min][k]){
					k++;
				}
				else{
					k=n;
				}
			}
		}
		if(min!=i){
			for(j=0;j<15;j++){		//en uzun kelime sayýsýný hesaplamak yerine matristeki 15 sütun arasýnda karakter deðiþikliði yapmasýný tercih ettim
				tmp[i][j]=dictionary[i][j];
				dictionary[i][j]=dictionary[min][j];
				dictionary[min][j]=tmp[i][j];
			}
		}
	}
	printf("\n\nKelimelerin sirali hali: \n");
	for(i=0;i<n;i++){
		printf("%d.: %s\n", i+1, dictionary[i]);
	}
	for(i=0;i<26;i++){
		alphabet[i]=0;
	}
	l=65;
	for(i=0;i<n;i++){
		while(dictionary[i][0]!=l){
			l++;
		}
		if(alphabet[l-'A']==0){
			alphabet[l-'A']=i+1;
		}
	}
	for(i=0;i<26;i++){		//Sizin output gösteriminize benzesin diye iki aþamada bastýrdým
		printf(" %c |", i+65);
	}
	printf("\n");
	for(i=0;i<26;i++){
		printf(" %d |", alphabet[i]);
	}
	i=0;
	harf=0;	//string.h kullanmadan harf sayýsýný bulmak için bu kodu yazdým (flowchartta farklý bu kýsým) ve harf: harf sayýsýný tutan bir deðiþken
	while(word[i]!=0){
		harf++;
		i++;
	}

	yer1=word[0]-'A'; //yer1=ilk harfin alphabet dizisindeki yerini tutan deðiþken
	yer2=alphabet[yer1]; //yer2=aranacak kelimenin ilk harfinin dictionary matrisinde hangi sýradan baþladýðýný tutan deðiþken

	dongu=1;
	if(alphabet[yer1]!=0){
		count1=0;
		count2=0;
		while(word[0]==dictionary[yer2-1][0] && count1==0){
			i=1;
			count2=1;
			while(i<harf+1&&count2==1){
				if(word[i]==dictionary[yer2-1][i]){
					i++;
					count1=1;
				} else{
					count2=0;
					count1=0;
					yer2++;
					dongu++;
				}
			}
		}
	}
	if(count2==0){
		printf("\n\n%s kelimesi sozlukte bulunmuyor.\n", word);
	} else{
		printf("\n\n%s kelimesi sozlukte %d. sirada bulunuyor.\n", word, yer2);
	}
	printf("\n%d kez arama yapildi.\n", dongu);
	return 0;
}

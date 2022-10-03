#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct dersler{
	char kod[8], ad[50];
	int kredi, kontenjan, doluluk, *ogrenci;
	struct dersler *next;
}DERS;
typedef struct ogrenciler{
	int id, dersSay, kredi;
	char ad[20], soyad[20];
	struct ogrenciler *next, *past;
}OGRENCI;
typedef struct kayit{
	char ders[8], tarih[11];
	int sira, id, durum;		// durum i�in : 1 = KAYITLI , -1 = DERS KAPANDI, 0 = BIRAKTI
	struct kayit *next;
}KAYIT;

void split_ogrenci(OGRENCI *holder, char buff[255], char delimeter[2]){
	char *token;
	token = strtok(buff,delimeter);		holder->id = atoi(token);
	token = strtok(NULL,delimeter);		strcpy(holder->ad,token);
	token = strtok(NULL,delimeter);		strcpy(holder->soyad,token);
	holder->dersSay = 0;				holder->kredi = 0;
}
void split_ders(DERS *holder, char buff[255], char delimeter[2]){
	char *token;
	token = strtok(buff,delimeter);		strcpy(holder->kod, token);
	token = strtok(NULL,delimeter);		strcpy(holder->ad, token);
	token = strtok(NULL,delimeter);		holder->kredi = atoi(token);
	token = strtok(NULL,delimeter);		token[strlen(token)-1] = '\0';
	holder->kontenjan = atoi(token);	holder->doluluk = 0;
	holder->ogrenci = (int*)calloc(holder->kontenjan,sizeof(int));
}

void split_kayit(KAYIT *holder, char buff[255], char delimeter[2]){
	char *token;
	token = strtok(buff,delimeter);		holder->sira = atoi(token);
	token = strtok(NULL,delimeter);		strcpy(holder->ders, token);
	token = strtok(NULL,delimeter);		holder->id = atoi(token);
	token = strtok(NULL,delimeter);		strcpy(holder->tarih, token);
	token = strtok(NULL,delimeter);		token[strlen(token)-1] = '\0';
	if(!strcmp(token,"kayitli"))
		holder->durum = 1;
	else if(!strcmp(token,"sildi"))
		holder->durum = 0;
	else
		holder->durum = -1;
}

OGRENCI *ogrenciOku(char dosya[20], char delim[2], OGRENCI **end){
	FILE *fp = fopen(dosya,"r");
	char line[255];
	OGRENCI *head = (OGRENCI*)malloc(sizeof(OGRENCI));
	OGRENCI *curr, *prev;
	if(fp == NULL){
		printf("��renci dosyas� a��lamad�.\n");		*end = NULL;	return NULL;
	}
	if(fgets(line,255,fp) != NULL)						
		split_ogrenci(head,line,delim);
	head->past = NULL;			
	prev = head;
	while(fgets(line,255,fp) != NULL){
		curr = (OGRENCI*)malloc(sizeof(OGRENCI));	
		prev->next = curr;							
		split_ogrenci(curr,line,delim);					
		curr->past = prev;		prev = curr;									
	}
	prev->next = NULL;
	*end = prev;				//iki parametre return edemedi�imden end'in adresini yollay�p de�i�tirdim
	fclose(fp);		return head;
}

DERS *dersOku(char dosya[20], char delim[2]){
	FILE *fp = fopen(dosya, "r");
	char line[255];
	DERS *head = (DERS*)malloc(sizeof(DERS));
	DERS *curr, *prev;
	if(fp==NULL){
		printf("Ders dosyas� a��lamad�.\n");		return NULL;
	}
	if(fgets(line,255,fp) != NULL){
		split_ders(head,line,delim);
		prev = head;
		while(fgets(line,255,fp) != NULL){
			curr = (DERS*)malloc(sizeof(DERS));
			prev->next = curr;
			split_ders(curr,line,delim);
			prev = curr;
		}
		prev->next = NULL;
	}
	else{
		head = NULL;
	}
	fclose(fp);		return head;
}

void dersEkle(DERS **head){
	DERS *newD = (DERS*)malloc(sizeof(DERS));
	DERS *tmp = *head;
	DERS *prev;
	printf("Ders kodu: ");		scanf("%s",newD->kod);
	if((*head) != NULL){
		if(strcmp(newD->kod,tmp->kod) < 0){
			newD->next = *head;
			*head = newD;		//newD head
		}
		else{
			prev = tmp;			tmp = tmp->next;
			if(tmp!=NULL){
				while(strcmp(newD->kod,tmp->kod) > 0 && tmp->next != NULL){
					prev = tmp;
					tmp = tmp->next;
				}
				if(strcmp(newD->kod,tmp->kod) < 0){
					prev->next = newD;
					newD->next = tmp;
				}
				else if(!strcmp(newD->kod,tmp->kod)){
					printf("Eklemek istedi�iniz ders zaten var.\n");			return;
				}
				else{
					tmp->next = newD;
					newD->next = NULL;
				}
			}
			else{
				(*head)->next = newD;
				newD->next = NULL;
			}
		}
	}
	else{
		*head = newD;
		newD->next = NULL;
	}
	printf("Dersin ad�: ");				scanf(" %[^\n]s",newD->ad);	//gets d���nda bir ��z�m kullanmak istedim
	printf("Dersin kredisi: ");			scanf("%d",&newD->kredi);
	printf("Dersin kontenjan�: ");		scanf("%d",&newD->kontenjan);
	newD->doluluk = 0;
	newD->ogrenci = (int*)calloc(newD->kontenjan,sizeof(int));
	printf("Ders ba�ar�yla eklendi.\n");
}

int derseOgrenciEkle(DERS *headD, OGRENCI *headO, char *ders, int id, int maxKredi, int maxDers){
	int i=0, j;
	while(strcmp(headD->kod,ders) && headD->next != NULL){
		headD = headD->next;
	}
	if(strcmp(headD->kod,ders)){
		printf("B�yle bir ders bulunmamakta.\n");	return 0;
	}
	while(headO->id != id && headO->next != NULL){
		headO = headO->next;
	}
	if(headO->id != id){
		printf("B�yle bir ��renci bulunmamakta.\n");	return 0;
	}
	if(maxKredi > (headO->kredi + headD->kredi) && maxDers > headO->dersSay){
		if(headD->doluluk != headD->kontenjan){
			while(i<headD->doluluk && headD->ogrenci[i] < id){
				i++;
			}
			if(headD->ogrenci[i] == id){
				printf("Bu ��renci zaten kay�tl�.\n");	return 0;
			}
			else if(headD->ogrenci[i] < id){
				headD->ogrenci[i] = id;
			}
			else{
				for(j=headD->doluluk;j>i;j--){
					headD->ogrenci[j] = headD->ogrenci[j-1];
				}
				headD->ogrenci[j] = id;
			}
			headD->doluluk++;
			headO->kredi += headD->kredi;
			headO->dersSay++;
			printf("Kay�t ba�ar�l�.\n");
			return 1;
		}
		else{
			printf("Ders kontenjan� dolmu�tur. Eklenme yap�lmad�.\n");	return 0;
		}
	}
	else{
		printf("��rencinin dersi alma hakk� yoktur. Ders say�s� ya da kredisi dolmu�tur\n");		return 0;
	}
}

int dersSil(DERS **headD, char *ders, OGRENCI *headO){
	DERS *newHeadD;// = (DERS*)malloc(sizeof(DERS));
	DERS *curr = (DERS*)malloc(sizeof(DERS));
	DERS *prev = (DERS*)malloc(sizeof(DERS));
	if(!strcmp((*headD)->kod,ders)){
		newHeadD = (*headD)->next;		(*headD)->next == NULL;
		while((*headD)->doluluk!=0){
			derstenOgrenciSil(*headD,headO,ders,(*headD)->ogrenci[0]);
		}
		free(*headD);					*headD = newHeadD;
		return 1;
	}
	prev = (*headD);	curr = prev->next;
	while(strcmp(curr->kod,ders) && curr->next != NULL){
		prev = curr;
		curr = curr->next;
	}
	if(!strcmp(curr->kod,ders)){
		while(curr->doluluk!=0){
			derstenOgrenciSil(*headD,headO,ders,curr->ogrenci[0]);
		}
		prev->next = curr->next;		curr->next = NULL;
		free(curr);						return 1;
	}
	else{
		printf("Silmek istedi�iniz ders bulunmamaktad�r.\n");
		return 0;
	}
}

int derstenOgrenciSil(DERS *headD, OGRENCI *headO, char *ders, int id){
	int i,j;
	while(strcmp(headD->kod,ders) && headD!=NULL){
		headD = headD->next;
	}
	if(headD!=NULL){
		while(headO->id < id && headO!=NULL){
			headO = headO->next;
		}
		if(headO!=NULL){
			i=0;
			while(headD->ogrenci[i]!=id && i<headD->doluluk){
				i++;
			}
			if(headD->ogrenci[i]==id){
				for(j=i;j<headD->doluluk-1;j++){
					headD->ogrenci[j] = headD->ogrenci[j+1];
				}
				headD->ogrenci[j] = 0;
				headD->doluluk--;			headO->dersSay--;
				headO->kredi -= headD->kredi;
				printf("��renci dersten silindi.\n");		return 1;
			}
			else{
				printf("Zaten ��renci bu dersi alm�yor.\n");	return 0;
			}
		}
		else{
			printf("��renci bulunmamaktad�r.\n");			return 0;
		}
	}
	else{
		printf("B�yle bir ders bulunmamakta.\n");		return 0;
	}
}

KAYIT *kayitOku(char dosya[20], char delim[2], int *kayitSayisi){
	FILE *fp = fopen(dosya, "r");
	if(fp==NULL){
		printf("Kayit dosyas� a��lamad�.\n");		return NULL;
	}
	char line[255];
	KAYIT *head = (KAYIT*)malloc(sizeof(KAYIT));
	KAYIT *curr, *prev;
	if(fgets(line,255,fp) == NULL){
		fclose(fp);		return NULL;
	}
	else{
		split_kayit(head,line,delim);
		prev = head;
		(*kayitSayisi)++;
		while(fgets(line,255,fp) != NULL){
			curr = (KAYIT*)malloc(sizeof(KAYIT));
			prev->next = curr;
			split_kayit(curr,line,delim);
			prev = curr;
			(*kayitSayisi)++;
		}
		prev->next = NULL;
	}
	fclose(fp);
	return head;
}

void kayitGuncelle(KAYIT *head, char *ders){
	while(head!=NULL){
		if(!strcmp(head->ders,ders))
			head->durum = -1;
		head = head->next;
	}
}

void kayitKontrol(KAYIT *head, DERS **headD, OGRENCI *headO, int maxKredi,int maxDers){
	while(head!=NULL){
		if(head->durum == 1){
			derseOgrenciEkle(*headD,headO,head->ders,head->id,maxKredi,maxDers);
		}
		else if(head->durum == -1){
			dersSil(headD,head->ders,headO);
			kayitGuncelle(head,head->ders);
		}
		else{
			derstenOgrenciSil(*headD,headO,head->ders,head->id);
		}
		head = head->next;
	}
}

void ogrenciEkle(OGRENCI **head, OGRENCI **end){
	OGRENCI *newO = (OGRENCI*)malloc(sizeof(OGRENCI));
	OGRENCI *tmp = *head;
	printf("��renci idsi: ");
	scanf("%d",&newO->id);
	if((*head) != NULL){
		if(newO->id < tmp->id){					//yeni eklenen head olursa
			newO->past = NULL; 				tmp->past = newO; //null olacak
			newO->next = tmp;
			printf("��renci ad�: ");		scanf(" %[^\n]s",newO->ad);		//gets d���nda bir ��z�m yazmak istedim
			printf("��renci soyad�: ");		scanf(" %s",newO->soyad);
			newO->dersSay = 0;				newO->kredi = 0;
			printf("��renci ba�ar�yla eklendi.\n");
			*head = newO;
			return;
		}
		if(tmp->next != NULL){
			tmp = tmp->next;
			while(tmp->id < newO->id && tmp->next != NULL){
				tmp = tmp->next;
			}
			if(tmp->id > newO->id){
				tmp->past->next = newO;
				newO->past = tmp->past;
				tmp->past = newO;
				newO->next = tmp;
			}
			else if(tmp->id == newO->id){
				printf("Eklemek istedi�iniz ��renci zaten var.\n");
				return;
			}
			else{
				newO->next = tmp->next;		//null
				tmp->next = newO;
				newO->past = tmp;
				*end = newO;
			}
		}
		else{
			(*head)->next = newO;		newO->past = *head;
			newO->next = NULL;			*end = newO;
		}
	}
	else{
		newO->next = NULL;	newO->past = NULL;
		*head = newO;		*end = newO;
	}
	printf("��renci ad�: ");
	scanf(" %[^\n]s",newO->ad);
	printf("��renci soyad�: ");
	scanf(" %s",newO->soyad);
	newO->dersSay = 0;
	newO->kredi = 0;
	printf("��renci ba�ar�yla eklendi.\n");
}

void ogrenciSil(OGRENCI **head, OGRENCI **end, DERS *headD){
	int id;
	char *ders;
	OGRENCI *tmp = *head;
	OGRENCI *curr = *head;
	printf("��renci idsi: ");
	scanf("%d",&id);
	if(curr->id == id){
		while(headD!=NULL){
			ders = headD->kod;
			derstenOgrenciSil(headD,curr,ders,id);
			headD = headD->next;
		}
		curr = curr->next;		curr->past = NULL;
		tmp->next = NULL;		free(tmp);
		*head = curr;						//head silinecek
	//	system("cls");
		printf("��renci ba�ar�yla silindi.\n");		return;
	}
	curr = curr->next;
	while(curr->id < id && curr->next != NULL){
		curr = curr->next;
	}
	if(curr->id == id && curr->next != NULL){
		while(headD!=NULL){
			ders = headD->kod;
			derstenOgrenciSil(headD,curr,ders,id);
			headD = headD->next;
		}
		tmp = curr->past;		tmp->next = curr->next;
		tmp = curr->next;		tmp->past = curr->past;
		curr->next = NULL;		curr->past = NULL;		free(curr);
		//system("cls");		
		printf("��renci ba�ar�yla silinci.\n");
	}
	else if(curr->id == id){
		while(headD!=NULL){
			ders = headD->kod;
			derstenOgrenciSil(headD,curr,ders,id);
			headD = headD->next;
		}
		tmp = curr->past;		tmp->next = NULL;
		curr->past = NULL;		free(curr);
		*end = tmp;
		//system("cls");		
		printf("��renci ba�ar�yla silinci.\n");
	}
	else{
		printf("Bu numaraya sahip bir ��renci bulunmamakta.\n");
	}
}

void kayitDosyaYaz(KAYIT *head, char dosya[20], char delim){
	FILE *fp=fopen(dosya,"w");
	char tmp[50];
	while(head!=NULL){
		itoa(head->sira,tmp,10);
		fputs(tmp,fp);				fputc(delim,fp);
		fputs(head->ders,fp);		fputc(delim,fp);
		itoa(head->id,tmp,10);
		fputs(tmp,fp);				fputc(delim,fp);
		fputs(head->tarih,fp);		fputc(delim,fp);
		if(head->durum == 0)
			strcpy(tmp,"sildi");
		else if(head->durum == 1)
			strcpy(tmp,"kayitli");
		else
			strcpy(tmp,"ders kapandi");
		fputs(tmp,fp);				fputc('\n',fp);	
		head=head->next;	
	}
	fclose(fp);
}

void yeniKayit(int *kayitSayisi, KAYIT **head, char *ders, int ogrenci, int durum){
	KAYIT *newK = (KAYIT*)malloc(sizeof(KAYIT));
	KAYIT *tmp = *head;
	newK->next = NULL;
	if(tmp==NULL){
		*head = newK;
	}
	else{
		while(tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = newK;
	}
	newK->id = ogrenci;
	strcpy(newK->ders,ders);
	newK->sira = 10001 + (*kayitSayisi);
	newK->durum = durum;	
	printf("Tarihi g�n.ay.y�l olarak giriniz.\n");
	scanf("%s",newK->tarih);		(*kayitSayisi)++;
	kayitDosyaYaz(*head,"OgrenciDersKayit.txt",',');
}

void derslerDosyaYaz(DERS *head, char dosya[30],char delim){
	FILE *fp=fopen(dosya,"w");
	char tmp[50];
	while(head!=NULL){
		fputs(head->kod,fp);		fputc(delim,fp);
		fputs(head->ad,fp);			fputc(delim,fp);
		itoa(head->kredi,tmp,10);
		fputs(tmp,fp);				fputc(delim,fp);
		itoa(head->kontenjan,tmp,10);
		fputs(tmp,fp);
		fputc('\n',fp);	
		head=head->next;	
	}
	fclose(fp);
}

void ogrencilerDosyaYaz(OGRENCI *head, char dosya[30],char delim){
	FILE *fp=fopen(dosya,"w");
	char tmp[50];
	while(head!=NULL){
		itoa(head->id,tmp,10);
		fputs(tmp,fp);				fputc(delim,fp);
		fputs(head->ad,fp);			fputc(delim,fp);
		fputs(head->soyad,fp);		fputc(delim,fp);
		itoa(head->dersSay,tmp,10);
		fputs(tmp,fp);				fputc(delim,fp);
		itoa(head->kredi,tmp,10);
		fputs(tmp,fp);				fputc('\n',fp);	
		head=head->next;	
	}
	fclose(fp);
}

void dosyaAdiOlustur(char dosyaAdi[30], char *ad, int secim){
	int i=0, j=0;
	char *txt = "_DERSPROGRAMI.txt";
	while(ad[i]!='\0'){
			dosyaAdi[i] = ad[i];		i++;
	}
	if(secim == 1){
		while(txt[j]!='.'){
			dosyaAdi[i] = txt[j];		i++; j++;
		}
	}
	j = 13;
	while(txt[j] != '\0'){
		dosyaAdi[i] = txt[j];			i++; j++;
	}
	dosyaAdi[i] = '\0';
}

void yoklamaListesi(DERS *head, char *ders, OGRENCI *headO){
	char dosyaAdi[20], tmp[50];
	int i;
	OGRENCI *curr;
	while(strcmp(head->kod,ders) < 0 && head != NULL){
		head = head->next;
	}
	if(!strcmp(head->kod,ders)){
		dosyaAdiOlustur(dosyaAdi,ders,0);
		FILE *fp=fopen(dosyaAdi,"w");
		i=0;
		while(head->ogrenci[i] != 0){
			curr = headO;
			while(curr->id < head->ogrenci[i]){
				curr = curr->next;
			}
			itoa(curr->id,tmp,10);
			fputs(tmp,fp);				fputc('\t',fp);			//yoklama listesinde ','�n ��k
			fputs(curr->ad,fp);			fputc('\t',fp);			//durmayaca��n� d���n�p tab ekledim aralar�na
			fputs(curr->soyad,fp);		fputc('\n',fp);	
			i++;
		}
		printf("Liste ba�ar�yla olu�turuldu.\n");
		fclose(fp);
	}
	else{
		printf("B�yle bir ders bulunmamakta.\n");
	}
}

void dersProgram(DERS *head, int ogrenci, OGRENCI *headO){
	char dosyaAdi[20], tmp[50];
	int i, j;
	while(headO->id < ogrenci && headO->next!=NULL){
		headO=headO->next;
	}
	if(headO->id == ogrenci){
		itoa(ogrenci,tmp,10);
		dosyaAdiOlustur(dosyaAdi,tmp,1);
		FILE *fp = fopen(dosyaAdi,"w");
		i = headO->dersSay;
		while(i>0){
			j=0;
			while(j < head->doluluk && head->ogrenci[j] < ogrenci){
				j++;
			}
			if(head->ogrenci[j] == ogrenci){
				i--;
				fputs(head->kod,fp);		fputc('\t',fp);
				fputs(head->ad,fp);			fputc('\t',fp);
				itoa(head->kredi,tmp,10);
				fputs(tmp,fp);				fputc('\t',fp);			//ders program�nda ','�n ��k
				itoa(head->kontenjan,tmp,10);						//durmayaca��n� d���n�p tab ekledim
				fputs(tmp,fp);				fputc('\n',fp);	
			}
			head = head->next;
		}
		printf("Ders program� olu�turuldu.\n");
		fclose(fp);
	}
	else{
		printf("B�yle bir ��renci bulunmamaktad�r.\n");
	}
}

int main(){
	setlocale(LC_ALL,"Turkish");
	int maxKredi, maxDers, ogrenci, kayitSayisi, secim;
	char ders[8];
	OGRENCI *headO, *endO = (OGRENCI*)malloc(sizeof(OGRENCI));
	headO = ogrenciOku("ogrenciler.txt",",\0",&endO);

	DERS *headD;
	headD = dersOku("dersler.txt",",\0");
	
	printf("��rencilerin maksimum kredi hakk�n� ve ders hakk�n� giriniz.\n");
	scanf("%d %d",&maxKredi,&maxDers);		//	system("cls");
	maxKredi++;			maxDers++;			//e�itli�e bakmamak i�in 1 artt�rd�m
	KAYIT *headK;
	headK = kayitOku("OgrenciDersKayit.txt",",\0",&kayitSayisi);
	kayitKontrol(headK,&headD,headO, maxKredi, maxDers);
	
	do{
		printf("Yap�sal Programlama D�nem Projesi\nBuse Nur Pekmezci-20011001\nGRUP NO: 1\n\n");
		printf("L�tfen i�lem se�iniz\n");				printf("1	-	Ders i�lemleri\n");
		printf("2	-	��renci i�lemleri\n");			printf("3	-	S�n�f listesi olu�turma\n");
		printf("4	-	��renci program� olu�turma\n");	printf("-1	-	��k��\n\n");
		printf("Se�im: ");		scanf("%d",&secim);	//	system("cls");
		if(secim == 1){
			printf("Ders i�lemleri\n");			printf("1	-	Ders ekle\n");
			printf("2	-	Ders sil\n");		printf("-1	-	��k��\n\n");
			printf("Se�im: ");		scanf("%d",&secim);		//	system("cls");
			if(secim == 1){
				dersEkle(&headD);
				derslerDosyaYaz(headD,"dersler.txt",',');
			}
			else if(secim==2){
				printf("Dersin kodu: ");		scanf("%s",ders);
				if(dersSil(&headD,ders,headO)){
					kayitGuncelle(headK,ders);
					kayitDosyaYaz(headK,"OgrenciDersKayit.txt",',');
					derslerDosyaYaz(headD,"dersler.txt",',');
					ogrencilerDosyaYaz(headO,"ogrenciler.txt",',');
					//system("cls");		
					printf("Ders ba�ar�yla silindi.\n");
				}
			}
			else if(secim!=-1)
				printf("Ge�erli bir se�im yapmad�n�z.\n");
		}
		else if(secim==2){
			printf("��renci i�lemleri\n");			printf("1	-	Yeni ��renci ekle\n");
			printf("2	-	��renci sil\n");		printf("3	-	Ders se�imi\n");
			printf("4	-	Ders b�rakma\n");		printf("-1	-	��k��\n\n");
			printf("Se�im: ");			scanf("%d",&secim);		//	system("cls");
			if(secim == 1)
				ogrenciEkle(&headO,&endO);
			else if(secim == 2)
				ogrenciSil(&headO,&endO,headD);
			else if(secim == 3){
				printf("Numaran�z� giriniz: ");				scanf("%d",&ogrenci);
				printf("Ders kodunu giriniz: ");			scanf("%s",ders);
			//	system("cls");
				if(derseOgrenciEkle(headD,headO,ders,ogrenci,maxKredi,maxDers)){
					yeniKayit(&kayitSayisi,&headK,ders,ogrenci,1);
				}
			}
			else if(secim == 4){
				printf("Numaran�z� giriniz: ");				scanf("%d",&ogrenci);
				printf("Ders kodunu giriniz: ");			scanf("%s",ders);
	//			system("cls");
				if(derstenOgrenciSil(headD,headO,ders,ogrenci)){
					yeniKayit(&kayitSayisi,&headK,ders,ogrenci,0);
				}
			}
			else if(secim!=-1)
				printf("Ge�erli bir se�im yapmad�n�z.\n");
			if(secim!=-1)
				ogrencilerDosyaYaz(headO,"ogrenciler.txt",',');
		}
		else if(secim==3){
			printf("Ders kodunu giriniz: ");		scanf("%s",ders);
			yoklamaListesi(headD,ders,headO);
		}
		else if(secim == 4){
			printf("��renci idsini giriniz: ");		scanf("%d",&ogrenci);
			dersProgram(headD,ogrenci,headO);
		}
		else if(secim != -1)
			printf("Ge�erli bir se�im yapmad�n�z.\n");
	}while(secim!=-1);
	return 0;
}

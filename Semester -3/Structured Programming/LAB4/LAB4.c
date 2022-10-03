#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ucuslar{
	int id, hat, pist;
	char nereden[20], nereye[20], saat[6];
	struct ucuslar *next;
}UCUS;

void split(UCUS* holder,char buff[255],char delim[2]){
	char *token;
	token=strtok(buff,delim);
	holder->id=atoi(token);
	token=strtok(NULL,delim);
	strcpy(holder->nereden,token);
	token=strtok(NULL,delim);
	strcpy(holder->nereye,token);
	token=strtok(NULL,delim);
	strcpy(holder->saat,token);
	token=strtok(NULL,delim);
	holder->hat=atoi(token);
	token=strtok(NULL,delim);
	token[strlen(token)-1]='\0';
	holder->pist=atoi(token);
}

UCUS* fileRead(char File_Name[20],char delim[2]){
	FILE *fp=fopen(File_Name,"r");
	char buf[255];
	UCUS *head=(UCUS*)malloc(sizeof(UCUS));
	UCUS *curr;
	UCUS *prev;
	if(fgets(buf,255,fp)!=NULL){
		split(head,buf,delim);		
	}
	prev=head;
	while(fgets(buf,255,fp)!=NULL){
		curr=(UCUS*)malloc(sizeof(UCUS));
		curr->next=prev;
		split(curr,buf,delim);
		prev=curr;
	}
	head->next=NULL;
	head = prev;
	fclose(fp);
	return head;
}

void printUcus(UCUS* head){
	while(head!=NULL){
		printf("%d %s %s %s %d %d\n",head->id,head->nereden,head->nereye,head->saat,head->hat,head->pist);
		head=head->next;	
	}
}

void fileWrite(UCUS* prev, char fileName[15]){
	FILE *fp=fopen(fileName,"w");
	int tmp = prev->pist;
	while(prev!=NULL){
		if(prev->pist == tmp)
			fprintf(fp,"%d %s %s %s %d %d\n",prev->id,prev->nereden,prev->nereye,prev->saat,prev->hat,prev->pist);	
		prev = prev->next;	
	}
	fclose(fp);
	return ;
}

int test(int count[20], int pist){			//bu fonksiyon eðer daha önce n. pist için txt oluþturulmuþsa
	int i=0;									//tekrar oluþturmamamýza yardýmcý oluyor
	while(count[i] != '\0'){
		if(count[i] == pist)
			return 0;
		else
			i++;
	}
	return 1;
}

int main(){
	UCUS *head;
	UCUS *prev;
	char nameFile[15];
	int count[20], i;	//count deðiþkeni önceden açtýðýmýz pistlerin kaydýný tutuyor 1, 3, 8, 2 gibi devam ediyor
	head = fileRead("ucusBilgi.txt"," \0");
	
	printUcus(head);
	
	i=0;
	prev = head;
	while(prev!=NULL){
		if(test(count,prev->pist) && prev->pist < 10){					//hocam ben isimleri tek tek kontrol ederek yazmak yerine böyle bir yol izledim
			strcpy(nameFile,"pist0.txt");								//eðer tek haneliyse pist numarasý bu yoldan
			nameFile[4] = prev->pist + '0';
			fileWrite(prev,nameFile);
			count[i] = prev->pist;
		}
		else if(test(count,prev->pist) && prev->pist <100){				//eðer çift haneliyse bu yoldan yazdýrýyor
			strcpy(nameFile, "pist00.txt");
			nameFile[4] = prev->pist / 10;
			nameFile[5] = prev->pist % 10;
			fileWrite(prev,nameFile);
			count[i] = prev->pist;
		}
		prev = prev->next;
		i++;
	}
	
	
	return 0;
}

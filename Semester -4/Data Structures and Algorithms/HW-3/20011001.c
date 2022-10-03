#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

typedef struct tree{
	char kelime[MAX];
	char dosyaAdlari[MAX][MAX];
	int dosyaCounter;
	struct tree *left, *right;
}TREE;

TREE *yeniNodeOlustur(char *kelime, char *dosyaAdi){
	TREE *node = (TREE*)malloc(sizeof(TREE));
	strcpy(node->kelime,kelime);
	strcpy(node->dosyaAdlari[0],dosyaAdi);
	node->dosyaCounter = 1;
	node->left = node->right = NULL;
	return node;
}

TREE *kelimeEkle(char *token, char *dosyaAdi, TREE *root){
	int sonuc = 1, i;
	TREE *curr, *prev;
	if(root == NULL){
		root = yeniNodeOlustur(token,dosyaAdi);
		return root;
	}
	curr = root;
	while(sonuc!=0 && curr != NULL){
		sonuc = strcmp(curr->kelime,token);
		if(sonuc == 0){
			i=0;
			while(i<curr->dosyaCounter && strcmp(curr->dosyaAdlari[i],dosyaAdi) != 0)
				i++;
			if(i==curr->dosyaCounter){
				strcpy(curr->dosyaAdlari[i],dosyaAdi);
				curr->dosyaCounter++;
			}
		}
		else if(sonuc > 0){
			prev = curr;
			curr = curr->left;
		}
		else{
			prev = curr;
			curr = curr->right;
		}
	}
	if(curr == NULL){
		curr = yeniNodeOlustur(token,dosyaAdi);
		if(strcmp(curr->kelime,prev->kelime) < 0)
			prev->left = curr;
		else
			prev->right = curr;
	}
	return root;
}

TREE *datayiAyir(char buffer[255], TREE *root){
	char *token, *dosyaAdi;
	buffer = strtok(buffer,"\n");
	dosyaAdi = strtok(buffer,":\0");
	token = strtok(NULL," ");
	while(token!=NULL){
		root = kelimeEkle(token,dosyaAdi,root);
		token = strtok(NULL," ");
	}
	return root;
}

TREE* dosyaEkle(char *dosyaAdi, TREE *root){
	FILE *fp = fopen(dosyaAdi, "r");
	char buffer[255];
	while(fgets(buffer,255,fp)!=NULL)
		root = datayiAyir(buffer, root);
	return root;
}

TREE *minNode(TREE *node){
	TREE *curr = node;
	while(curr != NULL && curr->left != NULL){
		curr = curr->left;
	}
	return curr;
}

TREE *nodeSil(char *kelime, TREE *root){
	if(root==NULL)		return NULL;
	if(strcmp(kelime,root->kelime) < 0){
		root->left = nodeSil(kelime,root->left);
	}
	else if(strcmp(kelime,root->kelime) > 0)
		root->right = nodeSil(kelime,root->right);
	else{
		if(root->left == NULL){
			TREE *tmp = root->right;
			free(root);
			return tmp;
		}
		else if(root->right == NULL){
			TREE *tmp = root->left;
			free(root);
			return tmp;
		}
		TREE *tmp = minNode(root->right);
		strcpy(root->kelime,tmp->kelime);
		int i = 0;
		while(i<=tmp->dosyaCounter){
			strcpy(root->dosyaAdlari[i],tmp->dosyaAdlari[i]);
			i++;
		}
		root->dosyaCounter = tmp->dosyaCounter;
		root->right = nodeSil(tmp->kelime,root->right);
	}
}

TREE *dosyaSil(char *dosyaAdi, char *kelime, TREE *root){
	int i;
	TREE *tmp;
	if(root == NULL)	return root;
	if(strcmp(kelime,root->kelime) < 0){
		root->left = dosyaSil(dosyaAdi,kelime,root->left);
	}
	else if(strcmp(kelime,root->kelime) > 0){
		root->right = dosyaSil(dosyaAdi,kelime,root->right);
	}
	else{
		if(root->dosyaCounter > 1){
			i = 0;
			while(i<root->dosyaCounter && strcmp(dosyaAdi, root->dosyaAdlari[i])!=0){
				i++;
			}
			if(i!=root->dosyaCounter){
				while(i<root->dosyaCounter){
					strcpy(root->dosyaAdlari[i],root->dosyaAdlari[i+1]);
					i++;
				}
				root->dosyaCounter--;
			}
			else{
				printf("Dosya bulunmamakta.\n");
			}
		}
		else if(strcmp(dosyaAdi, root->dosyaAdlari[0])==0){
			if(root->left == NULL){
				tmp = root->right;
				free(root);
				return tmp;
			}
			else if(root->right == NULL){
				tmp = root->left;
				free(root);
				return tmp;
			}
			tmp = minNode(root->right);
			strcpy(root->kelime,tmp->kelime);
			i = 0;
			while(i<=tmp->dosyaCounter){
				strcpy(root->dosyaAdlari[i],tmp->dosyaAdlari[i]);
				i++;
			}
			root->dosyaCounter = tmp->dosyaCounter;
			root->right = nodeSil(tmp->kelime,root->right);
		}
		return root;
	}
	return root;
}

void kelimeArama(char *kelime, TREE *root){
	TREE *curr=root;
	int i;
	while(curr!= NULL && strcmp(curr->kelime,kelime) != 0){
		if(strcmp(kelime,curr->kelime) < 0)
			curr = curr->left;
		else
			curr = curr->right;
	}
	if(curr == NULL)
		printf("Kelime bulunmuyor.\n");
	else{
		printf("Bulundugu dosyalar: ");
		for(i=0;i<curr->dosyaCounter;i++){
			printf("%s\t",curr->dosyaAdlari[i]);
		}
		printf("\n");
	}
}

void preorder(TREE *root){
	int i;
	if(root == NULL)
		return;
	printf("\n%s: ",root->kelime);
	for(i=0;i<root->dosyaCounter;i++){
		printf("%s\t",root->dosyaAdlari[i]);
	}
	preorder(root->left);
	preorder(root->right);
}

void inorder(TREE *root){
	int i;
	if(root == NULL)
		return;
	inorder(root->left);
	printf("\n%s: ",root->kelime);
	for(i=0;i<root->dosyaCounter;i++){
		printf("%s\t",root->dosyaAdlari[i]);
	}
	inorder(root->right);
}

void postorder(TREE *root){
	int i;
	if(root == NULL)
		return;
	postorder(root->left);
	postorder(root->right);
	printf("\n%s: ",root->kelime);
	for(i=0;i<root->dosyaCounter;i++){
		printf("%s\t",root->dosyaAdlari[i]);
	}
}

void printTree(TREE *root){
	int secim;
	printf("1 - Inorder\n");
	printf("2 - Preorder\n");
	printf("3 - Postorder\n");
	printf("Yazdirma seklini giriniz: ");
	scanf("%d",&secim);
	switch(secim){
		case 1:
			inorder(root);
			break;
		case 2:
			preorder(root);
			break;
		case 3:
			postorder(root);
	}
}

void printMenu(){
	printf("\n\t---MENU---\n");
	printf("1 - Yeni dosya ekleme\n");
	printf("2 - Dosya silme\n");
	printf("3 - Kelime arama\n");
	printf("4 - Agaci yazdir\n");
	printf("-1 - Cikis\n");
	printf("Buse Nur Pekmezci - 20011001\n");
	printf("Secim : ");
}

int main(){
	TREE *root = NULL;
	FILE *fp;
	int secim, flag;
	char okunan[MAX], dosyaAdi[MAX], aranan[MAX], *buff, *kelime, buffer[255];
	
	printMenu();
	scanf("%d",&secim);
	while(secim!=-1){
		switch(secim){
			case 1:
				printf("Dosyalarin okunacagi dosya adini giriniz: ");
				scanf("%s",okunan);
				root = dosyaEkle(okunan,root);
				break;
			case 2:
				printf("Dosya adi giriniz: ");
				scanf("%s",dosyaAdi);
				fp = fopen(okunan,"r");
				flag = 0;
				while(flag==0 && fgets(buffer,255,fp) != NULL){
					buff = strtok(buffer,"\n");
					kelime = strtok(buff,":\0");
					if(strcmp(kelime, dosyaAdi) == 0)
						flag = 1;
				}
				if(flag == 1){
					kelime = strtok(NULL, " ");
					while(kelime!=NULL){
						root = dosyaSil(dosyaAdi,kelime,root);
						kelime = strtok(NULL," ");
					}
				}
				break;
			case 3:
				printf("Kelime giriniz: ");
				scanf("%s",aranan);
				kelimeArama(aranan,root);
				break;
			case 4:
				printTree(root);
		}
		printMenu();
		scanf("%d",&secim);
	}
	return 0;
}

#include <stdio.h>

/*
*	This project about shifting a sentence with
*	given inputs.
*/

int main(){
	int shift, x, i, count;
	char text[500], variable;
	printf("Enter your sentence: \n");
	gets(text);
	printf("Enter 1 if you want to slide right, enter 0 if you want to slide left.\n");
	scanf("%d", &shift);
	printf("Enter shift number:\n");
	scanf("%d", &x);
	x=x%26;
	i=0;
	if(shift==1){
		while(text[i]!='\0'){
			variable=text[i]+x;
			if(text[i]>='A' && text[i]<='Z'){
                if(variable>90){
                    text[i]=text[i]+x-26;
                }
                else{
					text[i]=text[i]+x;
			 	}
            }
            else if(text[i]>='a' && text[i]<='z'){
                if(variable>122){
                    text[i]=text[i]+x-26;
                }
                else{
					text[i]=text[i]+x;
				}
			}
		i++;
		}
	}
	else if(shift==0){
		while(text[i]!='\0'){
			variable=text[i]-x;
			if(text[i]>='A' && text[i]<='Z'){
                if(variable<65){
                    text[i]=text[i]-x+26;
                }
                else{
					text[i]=text[i]-x;
				}
            }
            else if(text[i]>='a' && text[i]<='z'){
                if(variable<97){
                    text[i]=text[i]-x+26;
                }
                else{
					text[i]=text[i]-x;
				}
			}
		i++;
		}
	}
	printf("Encrypted Text: ");
	puts(text);
	i=0;
	if(shift==1){
		while(text[i]!='\0'){
			variable=text[i]-x;
			if(text[i]>='A' && text[i]<='Z'){
                if(variable<65){
                    text[i]=text[i]-x+26;
                }
                else{
					text[i]=text[i]-x;
				}
            }
            else if(text[i]>='a' && text[i]<='z'){
                if(variable<97){
                    text[i]=text[i]-x+26;
                }
                else{
					text[i]=text[i]-x;
				}
			}
		i++;
		}
	}
	else if(shift==0){
		while(text[i]!='\0'){
			variable=text[i]+x;
			if(text[i]>='A' && text[i]<='Z'){
                if(variable>90){
                    text[i]=text[i]+x-26;
                }
                else{
					text[i]=text[i]+x;
			 	}
            }
            else if(text[i]>='a' && text[i]<='z'){
                if(variable>122){
                    text[i]=text[i]+x-26;
                }
                else{
					text[i]=text[i]+x;
				}
			}
		i++;
		}
	}
	printf("Decrypted Text: ");
	puts(text);
	return 0;
}



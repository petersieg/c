//From: https://github.com/timlindquist/Enigma

#include <stdio.h>

char rotor1[2][26]={{'O','L','J','H','K','E','U','Y','B','I','S','A','Q','D','W','Z','T','F','P','N','X','G','R','M','V','C'},
										{'C','J','N','O','L','X','Y','Z','M','W','S','P','D','I','F','K','B','U','T','A','H','Q','E','R','G','V'}};
char rotor2[2][26]={{'J','I','A','F','N','T','E','P','H','W','L','U','B','G','C','M','Y','D','Z','Q','V','K','O','S','X','R'},
										{'M','D','K','B','F','N','G','C','W','Z','Y','O','T','J','I','E','L','X','H','Q','V','U','A','R','S','P'}};
char rotor3[2][26]={{'X','C','U','J','M','I','K','P','S','Y','L','F','R','O','N','V','D','T','E','W','G','B','Q','Z','A','H'},
										{'I','E','G','N','W','J','Q','A','S','X','B','R','P','C','V','K','H','O','L','F','Y','U','Z','D','T','M'}};
int reflector[2][26]={{'O','Y','C','R','E','U','B','Z','N','X','S','V','H','W','A','K','Q','I','D','J','M','P','L','F','T','G'},
										  {'U','G','H','A','N','O','I','Q','E','K','J','L','C','M','R','X','Z','B','P','S','W','D','V','T','F','Y'}};

void rotate(int rotor, int amount);
void print_array(int array[]);
int position(char input);

int main(){
	int r1_pos;
	int r2_pos;
	int r3_pos;
	int i,j,k;
	char input;
	int next_spot;
	printf("Rotor Placement\n");
	printf("Rotor 1: ");
	scanf("%d",&r1_pos);
	r1_pos--;
	rotate(1,r1_pos);
	printf("Rotor 2: ");
	scanf("%d",&r2_pos);
	r2_pos--;
	rotate(2,r2_pos);
	printf("Rotor 3: ");
	scanf("%d",&r3_pos);
	r3_pos--;
	rotate(3,r3_pos);
	printf("\nEnter Text:\n");

	for(;;){
		for(;r3_pos<26;r3_pos++){
			for(;r2_pos<26;r2_pos++){
				for(;r1_pos<26;r1_pos++){
					scanf(" %c",&input);
					while((input<65)||(input>122)||((input>90)&&(input<97))){	//input must be a letter
						scanf(" %c",&input);
					}

					for(i=0;i<26;i++){
						if(rotor1[1][i]==rotor1[0][position(input)]){
							next_spot=i;
							break;
						}
					}
					//rotor transistion 1 to 2
					for(i=0;i<26;i++){
						//printf("%c,%c",rotor2[1][i],rotor2[0][next_spot]);
						if(rotor2[1][i]==rotor2[0][next_spot]){
							next_spot=i;
							break;
						}
					}
					//rotor transition 2 to 3
					for(i=0;i<26;i++){
						if(rotor3[1][i]==rotor3[0][next_spot]){
							next_spot=i;
							break;
						}
					}
					//reflector
					for(i=0;i<26;i++){
						if(reflector[0][i]==reflector[1][next_spot]){
							next_spot=i;
							break;
						}
					}

					//rotor transistion 3 to 2
					for(i=0;i<26;i++){
						if(rotor3[0][i]==rotor3[1][next_spot]){
							next_spot=i;
							break;
						}
					}

					//rotor transition 2 to 1

					for(i=0;i<26;i++){
						if(rotor2[0][i]==rotor2[1][next_spot]){
							next_spot=i;
							break;
						}
					}

					//rotor transition 1 to key
					for(i=0;i<26;i++){
						if(rotor1[0][i]==rotor1[1][next_spot]){
							next_spot=i;
							break;
						}
					}

					//next to convert
					printf("%c",next_spot+65);

				rotate(1,1);
			}
			r1_pos=0;
			rotate(2,1);
		}
		r2_pos=0;
		rotate(3,1);
	}
	r3_pos=0;
	}

return 0;
}


void rotate(int rotor, int amount){
	int i,j,k;
	char temp;
	if(rotor==1){
		for(i=0;i<2;i++){
			for(j=0;j<amount;j++){
					temp=rotor1[i][0];
				for(k=0;k<25;k++){
					rotor1[i][k]=rotor1[i][k+1];
					}
				rotor1[i][25]=temp;
			}
		}
	}
	if(rotor==2){
		for(i=0;i<2;i++){
			for(j=0;j<amount;j++){
					temp=rotor2[i][0];
				for(k=0;k<25;k++){
					rotor2[i][k]=rotor2[i][k+1];
					}
				rotor2[i][25]=temp;
			}
		}
	}
	if(rotor==3){
		for(i=0;i<2;i++){
			for(j=0;j<amount;j++){
					temp=rotor3[i][0];
				for(k=0;k<25;k++){
					rotor3[i][k]=rotor3[i][k+1];
					}
				rotor3[i][25]=temp;
			}
		}
	}

}

int position(char input){
	if(input>96){	//lowercase
		input=input-32;
	}
	input=input-65;	//position in array

return input;
}



#include <stdio.h>
#include <stdlib.h>

int busca(char vetor[],char a){
	int i;
	
	for(i=0;i<3;i++)
	   if(vetor[i]==a)
	      break;
	      
	return i;
}

char* descompacta(char table [][3], unsigned int n, int bits){
	
	int i,j,k;
	
	char vetTexto[bits];
    
    char* original = (char*)malloc(sizeof(char));
    
    for(i=bits-1;i>=0;i--){
       if(n & ((unsigned int)01))
          vetTexto[i] = '1';
          
       else
          vetTexto[i] = '0';   
           n>>=1;  
    }      

    j=0;
    
	for(i=0;i<bits;i+=2){
		
		if(vetTexto[i] =='0' && vetTexto[i+1] =='0'){
		  original[j] = 'a';
		  j++;
		}
		 
		else if(vetTexto[i] =='0' && vetTexto[i+1] =='1'){
		  original[j] = 'b';
		  j++;
		}
		
	    else if(vetTexto[i] =='1' && vetTexto[i+1] =='1'){
		  original[j] = 'c';
		  j++;
	  }
	}
	
	return original;
}

int main()
{
	//FILE *arquivoEntrada = fopen("entrada", "r");
	//FILE *arquivoNovo = fopen("compactado", "w");
	
	int i,j,aux;
	int bits =0;
	char a ='#';
	
	char letras [3];
	char cods [3][3];
	char texto [10];
	
	unsigned long int n = 0;
	
	
	
	letras[0] = 'a';
	letras[1] = 'b';
	letras[2] = 'c';
	
	cods[0][0] = '0';
	cods[0][1] = '0';
	cods[0][2] = 'f';
	
	cods[1][0] = '0';
	cods[1][1] = '1';
	cods[1][2] = 'f';
	
	cods[2][0] = '1';
	cods[2][1] = '1';
	cods[2][2] = 'f';
	
	texto[0] = 'a';
	texto[1] = 'a';
	texto[2] = 'a';
	texto[3] = 'b';
	texto[4] = 'c';
	texto[5] = 'a';
	texto[6] = 'b';
	texto[7] = 'b';
	texto[8] = 'c';
	texto[9] = 'a';
	
	
	
	for(i=0;i<10;i++){
		
		
		int aux=busca(letras,texto[i]);
		
		j=0;
		while(1){
			a = cods[aux][j];
			
			if ( a == 'f')
			   break;
			   
			else if ( a == '0')
			  n<<=1;
			
			else{
			  n<<=1;
			  n|=(unsigned int)01;
			}
			
			bits++;
			j++;   
		} 
		
		
	}
	
	printf("%ld\n", n);
	char* fudeu = descompacta(cods,n,bits);
	
	puts(fudeu);
	
	return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include "datainput.h"
#include <string.h>

int totalBits;
unsigned char bit_buffer;
long totalChar(FILE * file){
	long totalChar = 0;
	char c;

	while(1){
		c = getc(file);
		if(c == EOF)
			break;
		totalChar++;
	}

	return totalChar;
}

LINKEDLIST * createLeafNodes(FILE *file, LINKEDLIST *list){
	NODE *paux;
	char data;

	while(1){
		data = getc(file);
		if(data == EOF)
			break;
		paux = searchData(data,list);
		if(paux == NULL){
			paux = new_node(data);
			insertList(paux,NULL,list);
		}else{
			paux->frequency++;
		}
	}
	return list;

}

void compressFILE(FILE *input, LINKEDLIST* charTable,FILE* output){
	// O bit_buffer eh global, pois ao colocar ele como parametro de funcao cria uma copia dele q sera destruida
	char data;
	while(1){
		data = fgetc(input);
		if(data == 10 || data == EOF)
			break;
		writeBinCode(data,charTable,output);
	}

	if(totalBits != 0){//COMPLETA ESPAÇOS COM 0 ATE FECHAR 1 BYTE, CASO O TOTAL DE BITS N SEJA MULTIPLO DE 8
		while(totalBits != 8){
			bit_buffer <<=1;
			totalBits++;
		}

		fwrite(&bit_buffer,1,1,output);
	}
}

void writeBinCode(char data,LINKEDLIST *charTable,FILE *output){
	char *binCode = searchCode(data, charTable);//PEGA O CODIGO BINARIO DA LETRA
	int i,tempBits;
	totalBits += strlen(binCode);//TOTAL DE BITS LIDOS

	if(totalBits == 8){//SE COMPLETOU 1 BYTE ESCREVE O CHAR NO ARQUIVO
		for(i=0;i<strlen(binCode);i++){
			bit_buffer <<= 1;		//SHIFT DO BUFFER
			if(binCode[i] == '1')	
				bit_buffer |= 1;	//SE TIVER 1 ESCREVE 1 SENAO 0

		}
		fwrite(&bit_buffer,1,1,output); //ESCREVE NO ARQUIVO
		totalBits = 0; //RESETA O TOTAL DE BITS
		bit_buffer = 0; // EU ACHO QUE LIMPA O BUFFER
	}else if(totalBits > 8){ // SE O TOTAL DE BITS FOR MAIOR QUE 1 BYTE PEGA UMA PARTE DO CODIGO E ESCREVE NO ARQUIVO
		tempBits = totalBits - 8;
		for (i = 0; i < strlen(binCode) - tempBits; i++){
			bit_buffer <<= 1;
			if(binCode[i] == '1')
				bit_buffer |= 1;
		}
		fwrite(&bit_buffer,1,1,output);
		bit_buffer = 0;

		totalBits = tempBits;
		for (i; i < strlen(binCode); i++){//ESCREVE RESTO DO CODIGO NO BUFFER
			bit_buffer <<= 1;
			if(binCode[i] == '1')
				bit_buffer |= 1;
		}
	}else{  //SE O TOTAL DE BITS FOR MENOR QUE 1 BYTE APENAS ESCREVE NO BUFFER
		for(i=0;i<strlen(binCode);i++){
			bit_buffer <<= 1;
			if(binCode[i] == '1')
				bit_buffer |= 1;
		}
	}
	 
}
void transformaBinario(char* nomeTexto){
  
  FILE* entrada = fopen(nomeTexto,"r");
  
  int tamanho;
  int shift;
  int i,j;
  
  
  fscanf(entrada,"%d",&tamanho);
  //tamanho aqui é o numero de bits que será capturado;
  
  char binarios[tamanho];
  int tamanhoBin = tamanho;
  
  shift=tamanho%8;
  shift=8-shift;
  tamanho= tamanho/8;
  
  if(shift){
     tamanho++;     
  }
  
  //tamanho agora tem o numero de chars do arquivo;
  unsigned char chars [tamanho];
  
  fscanf(entrada,"%c",&chars[0]);//soh pra pegar o /n, q será sobrescrito abaixo
  for(i=0;i<tamanho;i++)
	 fscanf(entrada,"%c",&chars[i]);
  
  for(i=0;i<shift;i++){
      chars[tamanho-1]>>=1;
  }
  
  int posicao = tamanhoBin-1;
  for(i=0;i<(8-shift);i++){
      if(chars[tamanho-1] & (unsigned int) 1)
        binarios[posicao]='1';
      else
        binarios[posicao]='0';
        
        chars[tamanho-1]>>=1;
        posicao--;   
  }
  
  for(i=tamanho-2;i>=0;i--){
      for(j=0;j<8;j++){
        
        if(chars[i] & (unsigned int) 1)
            binarios[posicao]='1';
        else
          binarios[posicao]='0';
        
        chars[i]>>=1;
        posicao--;   
         
        
     }
  }
}

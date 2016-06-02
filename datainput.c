#include <stdio.h>
#include <stdlib.h>
#include "datainput.h"
#include <string.h>

int totalBits;
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
	output = fopen("saida.txt","w");

	unsigned char bit_buffer;
	char data;
	while(1){
		data = fgetc(input);
		if(data == EOF)
			break;
		writeBinCode(bit_buffer,data,charTable,output);
	}
}

//FUNCAO INCOMPLETA FALTA A A PARTE DE COMPLETAR COM 0 SE NO FINAL AO FOR MULTIPLO DE 8
void writeBinCode(unsigned char bit_buffer,char data,LINKEDLIST *charTable,FILE *output){
	char *binCode = searchCode(data, charTable);//PEGA O CODIGO BINARIO DA LETRA
	int i,tempBits;
	totalBits += strlen(binCode);//TOTAL DE BITS LIDOS

	if(totalBits == 8){//SE COMPLETOU 1 BYTE ESCREVE O CHAR NO ARQUIVO
		for(i=0;i<strlen(binCode);i++){
			bit_buffer <<= 1;		//SHIFT DO BUFFER
			if(binCode[i] == '1')	
				bit_buffer |= 0x1;	//SE TIVER 1 ESCREVE 1 SENAO 0
		}
		fprintf(output, "%c", bit_buffer); //ESCREVE NO ARQUIVO
		totalBits = 0; //RESETA O TOTAL DE BITS
		bit_buffer = 0; // EU ACHO QUE LIMPA O BUFFER
	}else if(totalBits > 8){ // SE O TOTAL DE BITS FOR MAIOR QUE 1 BYTE
		tempBits = totalBits - 8;
		for (i = 0; i < strlen(binCode) - tempBits; i++){
			bit_buffer <<= 1;
			if(binCode[i] == '1')
				bit_buffer |= 0x1;
		}
		fprintf(output, "%c", bit_buffer);
		bit_buffer = 0;

		totalBits = tempBits;
		for (i; i < strlen(binCode); i++){
			bit_buffer <<= 1;
			if(binCode[i] == '1')
				bit_buffer |= 0x1;
		}
	}else{  //SE O TOTAL DE BITS FOR MENOR QUE 1 BYTE
		for(i=0;i<strlen(binCode);i++){
			bit_buffer <<= 1;
			if(binCode[i] == '1'){
				bit_buffer |= 0x1;
		}
	}
	 
}

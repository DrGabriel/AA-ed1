#include <stdio.h>
#include <stdlib.h>
#include "datainput.h"
#include <string.h>
#include <time.h>

long totalBits=0;
unsigned long fileBits;
unsigned char bit_buffer;
char* codebinarios;



long totalChar(char *fileName){
	FILE *file = fopen(fileName,"r");
	long totalChar = 0;
	char c;

	while(1){
		c = getc(file);
		if(c == EOF)
			break;
		totalChar++;
	}
	fclose(file);
	return totalChar;
}

LINKEDLIST * createLeafNodes(char *fileName, LINKEDLIST *list){
	NODE *paux;
	char data;
	FILE *file = fopen(fileName,"r");

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
	fclose(file);
	return list;

}

void compressFILE(char *inputName,char* outputName, LINKEDLIST* charTable){
	// O bit_buffer eh global, pois ao colocar ele como parametro de funcao cria uma copia dele q sera destruida
	CELL *paux = charTable->first;
	char data;
	FILE *input = fopen(inputName,"r");
	FILE *output = fopen(outputName,"w");
	clock_t start, end;
	fprintf(output, "%s\n", inputName);//escreve nome original do arquivo
	//Escreve a tabela no arquivo
	start = clock();
	while(paux != NULL){
		fprintf(output, "%s %c",paux->binCode->bincode,paux->binCode->character);
		paux = paux->next;
	}
	fprintf(output,"G");
	fprintf(output,"\n");

	//Escreve o total de bits
	fileTotalBits(charTable,inputName);
	fprintf(output,"%lu\n",fileBits);
	free(paux);
	while(fileBits%8 !=0){
		fileBits++;
	}
	posix_memalign((void**)&codebinarios,64,fileBits * sizeof *codebinarios);
	copyBinCodes(input,charTable);

	writeBinCode(output);
	end = clock();
	free(codebinarios);
	fclose(input);
	fclose(output);
	double compression = 1 - (fileBits/(double)(totalChar(inputName)*8));
	printf("TAXA DE COMPRESSAO: %lf\n",compression);
	printf("TEMPO DE COMPRESSAO: %lf segundos\n",(double)(end -start)/CLOCKS_PER_SEC);
}


void uncompressFILE(char *inputName){
	FILE * compressed = fopen(inputName,"r"); //arquivo comprimido
	FILE * original; //arquivo descomprimido
	LINKEDLIST* table; // variavel para a tabela de codigos
	long tamanho; // total de bits

	char * name = malloc (256 *sizeof *name); // aloco memoria para o nome original do arquivo
	if(fgets(name,256,compressed)){
		name[strlen(name) - 1] = '\0';
		original = fopen (name,"w"); // cria arquivo descomprimido com o nome original
	}
	table = reCreateTable(compressed); // recria a tabela de codigos e caracteres

	fscanf(compressed,"%ld",&tamanho); // le total de bits armazenados no arquivo excluindo os 0 compelementares
	int *binarios = transformaBinario(compressed,tamanho);//vetor que armazena todos os bits do arquivo comprimido
	int i,j=0,tam=1;
	int * code = malloc(14* sizeof *code);// aloco espaco para variavel que recebe os codigos binarios
	char letra;
	for(i=0;i<tamanho +1;i++){
			code[j] = binarios[i];
		letra = searchBinCode(tam,code, table);//funcao retorna a letra caso encontre o codigo na tabela de codigos
		tam++;
		j++;
		if(letra != '\0'){
			free(code);//libera espaco na memoria e "limpa" a variavel code
			code = malloc(14* sizeof *code); // realoco a mesma quantidade de memoria
			fprintf(original, "%c",letra);// escrevo letra encontrada no arquivo
			fflush(original);
			j = 0; // reseto contador
			tam=1;
		}
	}
}

void copyBinCodes(FILE* input,LINKEDLIST *charTable){
	int j=0;
	char data;
	char *binCode;
	while(1){
		data = fgetc(input);
		if(data == EOF)
			break;
		binCode = searchCode(data,charTable);
		for(j=0;j<strlen(binCode);j++){
			codebinarios[totalBits]=binCode[j];
			totalBits++;
		}
	}

}
void writeBinCode(FILE * output){
	int i;
	while(totalBits != fileBits){
		codebinarios[totalBits] = '0';
		totalBits++;
	}
	for(i=0;i<fileBits;i++){

		bit_buffer <<= 1;
		if(codebinarios[i] == '1')
			bit_buffer |= 1;
		if((i+1)%8 == 0){
			fwrite (&bit_buffer, 1, 1, output);//ESCREVE NO ARQUIVO
			bit_buffer =0;
		}
	
	}

}


int* transformaBinario(FILE * entrada, long tamanho){
  
  //FILE* entrada = fopen(nomeTexto,"r");
  
  //long tamanho;
  int shift;
  int i,j;
    //tamanho aqui é o numero de bits que será capturado;
  
  int* binarios = malloc((tamanho +1) * sizeof *binarios);
  long tamanhoBin = tamanho;
  
  shift=tamanho%8;
  shift=8-shift;
  tamanho= tamanho/8;
  
  if(shift){
     tamanho++;     
  }
  
  //tamanho agora tem o numero de chars do arquivo;
  unsigned char *chars = malloc(tamanho* sizeof * chars);
  
  chars[0] = fgetc(entrada);//soh pra pegar o /n, q será sobrescrito abaixo
  for(i=0;i<tamanho;i++)
  	chars[i] = fgetc(entrada);


  
  for(i=0;i<shift;i++){
      chars[tamanho-1]>>=1;
  }
  
  long posicao = tamanhoBin-1;
  for(i=0;i<(8-shift);i++){
      if(chars[tamanho-1] & (unsigned int) 1)
        binarios[posicao]=1;
      else
        binarios[posicao]=0;
        
        chars[tamanho-1]>>=1;
        posicao--;   
  }
  
  for(i=tamanho-2;i>=0;i--){
      for(j=0;j<8;j++){
        
        if(chars[i] & (unsigned int) 1)
            binarios[posicao]=1;
        else
          binarios[posicao]=0;
        
        chars[i]>>=1;
        posicao--;   
         
        
     }
  }
  //fclose(entrada);
  return binarios;
}

void fileTotalBits(LINKEDLIST *charTable, char *fileName){
	char data;
	char *binCode;
	FILE* input = fopen(fileName,"r");
	while(1){
		data =  fgetc(input);
		if(data == EOF)
			break;
		binCode = searchCode(data,charTable);
		fileBits += strlen(binCode);
	}
	fclose(input);
}


LINKEDLIST* reCreateTable(FILE *input){
	char previous;
	char data ='a';
	char *code = malloc(sizeof(char)*10);
	int i,j=0;
	int newLinelidos = 0,
	spaceLidos = 0; 

	LINKEDLIST * table = new_list(); //Aloca espaço para a tabela
	
	while(1){
		previous = data;
		data = fgetc(input);

		if(previous != '0' && previous != '1' && data =='G')
			break;
		if(data == '\n')
			newLinelidos++;

		if(data != '0' && data != '1' && newLinelidos <= 1){//Eh um char
			CHARBINCODE *paux = (CHARBINCODE*) malloc(sizeof(CHARBINCODE));//Ponteiro auxiliar para criar a tabela
			char * codecpy = malloc(j * sizeof *codecpy);// aloco espaco para nova string
			data = fgetc(input);// vou para o char ja q antes eh espaco
			if(paux != NULL && codecpy!=NULL){	
				for(i=0;i<j;i++)
					codecpy[i] = code[i]; //copio o codigo lido
				paux->character = data; //escrevo o char
				paux->bincode = codecpy;//escrevo o codigo
				insertList(NULL,paux,table);//insiro na tabela
				j=0; //reseta contador
			}else{
				printf("No memory available for new CHARBINCODE or char pointer\n");
			}
		}else{
			if(j>10)
				code = realloc(code,j* sizeof *code);//se for um codigo maior que 10 bits realoco
			if(spaceLidos == 0){
				code[j]=data;//eh 0 ou 1
				j++;
			}

		}
	}
	printf("\n");
	free(code);//code nao eh mais necessario
	return table;
}

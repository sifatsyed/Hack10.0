/*
* Date : 10/25/2018
* Auhtor: Sifat Syed, Asmita Jayswal and Yifan Ren
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#include "file_utils.h"
#include "protein_utils.h"

char *dnaToRNA(const char *sourceFilePath);

void removeChar(char* s, char c);

char **rnaSplit(const char *rna, int n);

int main(int argc, char **argv){
	
	if(argc!=3){
		printf("Usage : %s for conversion", argv[0]);
		exit(1);
	}
	
	char * sourceFilePath = argv[1];
	char * outputFilePath = argv[2];
	
	char *rna = dnaToRNA(sourceFilePath);
	removeChar(rna, '\n');
	char **split = rnaSplit(rna, 3);
	
	
	FILE *f = fopen(outputFilePath, "w");
	int i=0;
	double height = ceil((double)strlen(rna) / 3);
	while(i<height){
	    char prot = rnaToProtein(split[i]);
		if(prot=='x'){
			break;
		} else{
			fprintf(f,"%c", prot);
		}
		i++;
	}
	fclose(f); 
	
    return 0;
	
}

char *dnaToRNA(const char *sourceFilePath){
	FILE *f = fopen(sourceFilePath, "r");
	char c = fgetc(f);
	int size = 1;
	while(c!=EOF){
		size ++;
		c = getc(f);
	}
	//closing the file to prevent any memory leak
	fclose(f);  
	
	FILE *g = fopen(sourceFilePath, "r");
	char *contents = (char *)malloc(sizeof(char) * size);
	contents = getFileContents(sourceFilePath);
	fclose(g);
	for(int i =0; i<size; i++){
		if(contents[i]=='T'){
			contents[i]='U';
		}
	}
	return contents;
}

void removeChar(char* s, char c){
    int i;
	//c = '\n';
    i = 0;
    int j = 0;
    while (i < strlen(s)) {
        if (s[j] != c) {
            s[i] = s[j]; //removing the character from string
            i++;
        }
        j++;
    }
}

// char *rnaSplit (const char * rna){
	// char *splitRNA = (char *)malloc(sizeof(char)* 3)
	// while(rna != EOF){
		// for(int i=0; i<3; i++){
			// splitRNA = rna[i];
		// }
	// }	
	// return splitRNA;
// }
char **rnaSplit(const char* s, int n)
{
    double height = ceil((double)strlen(s) / n);
    char** splitRNA = (char**)malloc(height * sizeof(char*));
    for (int i = 0; i < height; i++) {
        splitRNA[i] = (char*)malloc((n + 1) * sizeof(char));
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < n; j++) {
            splitRNA[i][j] = s[j + i * n];
        }
        splitRNA[i][n] = '\0'; //null termination of string
    }

    return splitRNA;
}

/*
* Author : Sifat Syed, Asmita Jayswal and Yifan Ren
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"file_utils.h"

char *getFileContents(const char *filePath){
	FILE *f = fopen(filePath, "r");
	char c ;//= fgetc(f);
	int size = 1;
	while(c!=EOF){
		c = getc(f);
		size ++;
	}
	//closing the file to prevent any memory leak
	fclose(f);   
	
	FILE *g = fopen(filePath, "r");
	char *s = (char *)malloc(sizeof(char)*size);
	char tmpBuffer[1000]; 
	//Buffer to prevent over-writing on file s
	char *line = fgets(tmpBuffer, 1000, f);                        
	
	//strcpy(s, line);
	//line = fgets(tmpBuffer, 1000, f); 
	while(line!=NULL){
		strcat(s, line);
		line = fgets(tmpBuffer, 1000, f);
	}
    fclose(g);
	return s;
}

char **getFileLines(const char *filePath, int *numLines){
	FILE *f = fopen(filePath, "r");
	char c = fgetc(f);
	int size = 1;
	while(c!=EOF){
		size ++;
		c = getc(f);
		size ++;
	}
	//closing the file to prevent any memory leak
	fclose(f); 
	
	FILE *g = fopen(filePath, "r");
	char **stringArray = (char **)malloc(sizeof(char *) * size);
	for(int i=0; i<size; i++){
		stringArray[i]=(char *)malloc(sizeof(char) *size);
	}
	
	char s[1000];
	char *line = fgets(s, 1000, f);
	int i=0;
	int lineNum = 0;
	while(line != NULL){
		int n = strlen(s);
	    if(s[n-1] == '\n'){
		s[n-1] = '\0';
	    }
		strcpy(stringArray[i], s);
		line = fgets(s, 1000, f);
		i++;
		lineNum ++;
	}
	fclose(g);
	*numLines = lineNum;
	return stringArray;
}
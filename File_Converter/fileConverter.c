
#include <stdio.h>
#include <string.h>

#define MAX_SPACE_TL5 5
#define MAX_SPACE_TR9 9
#define BUFF_SIZE 255

FILE csvTotl5(char *inName, char *outName);
FILE csvTotr9(char *inName, char *outName);
FILE tl5Totr9(char *inName, char *outName);
FILE tr9Totl5(char *inName, char *outName);
FILE tl5Tocsv(char *inName, char *outName);
FILE tr9Tocsv(char *inName, char *outName);


int main(int argc, char* argv[]){

	char *sourceExt = strchr(argv[1],'.');
	char *destExt = strchr(argv[2],'.');

	if(!strcmp(sourceExt,".csv")&&!strcmp(destExt,".tl5")){
		csvTotl5(argv[1],argv[2]);
		printf("Conversion succesfull\n");
		return 1;
	}
	else if (!strcmp(sourceExt,".csv")&&!strcmp(destExt,".tr9")){
		csvTotr9(argv[1],argv[2]);
		printf("Conversion succesfull\n");
		return 1;
	}
	else if (!strcmp(sourceExt,".tl5")&&!strcmp(destExt,".tr9")){
		tl5Totr9(argv[1],argv[2]);
		printf("Conversion succesfull\n");
		return 1;
	}
	else if (!strcmp(sourceExt,".tr9")&&!strcmp(destExt,".tl5")){
		tr9Totl5(argv[1],argv[2]);
		printf("Conversion succesfull\n");
		return 1;
	}
	else if (!strcmp(sourceExt,".tl5")&&!strcmp(destExt,".csv")){
		tl5Tocsv(argv[1],argv[2]);
		printf("Conversion succesfull\n");
		return 1;
	}
	else if (!strcmp(sourceExt,".tr9")&&!strcmp(destExt,".csv")){
		tr9Tocsv(argv[1],argv[2]);
		printf("Conversion succesfull\n");
		return 1;
	}
	
	else if (!strcmp(sourceExt,destExt)){
		printf("No conversion neccesary\n");
		return 0;
	}
	else{
		printf("Error: conversion of %s to %s is not supported\n",argv[1],argv[2]);
		return 0;
	}
}


FILE csvTotl5(char *inName, char *outName){

	char buff[BUFF_SIZE];
	char *delimString;

	FILE *fpIn;
	FILE *fpOut;

	fpIn = fopen(inName,"r");
	fpOut = fopen(outName,"w");

	if(fpIn == NULL){
		perror("File doesn't exist");
	}

	int delimCount = 0;

	while(fgets(buff,BUFF_SIZE,(FILE*)fpIn)!=NULL){

		int numOfDelims = 0;
		char *ptr = buff;

		while((ptr = strchr(ptr,',')) != NULL){
			numOfDelims++;
			ptr++;
		}

		delimString = strtok(buff,",\n");


		while(delimString!=NULL){

			int stringsize = strlen(delimString);


			if(stringsize > MAX_SPACE_TL5){
				for(int x = 0; x < MAX_SPACE_TL5; x++){
					fputc(delimString[x],fpOut);
				}
			}
			else if(stringsize < MAX_SPACE_TL5){
				for (int x = 0; x < stringsize; x++){
					fputc(delimString[x],fpOut);
				}

				for(int x = 0; x < (MAX_SPACE_TL5 - stringsize);x++){
					fputc(' ',fpOut);
				}

			}
			else{
				fprintf(fpOut,"%s",delimString);
			}

			if(delimCount < numOfDelims){
				fputc('|',fpOut);
				delimCount++;
			}


			delimString = strtok(NULL,",\n");
		}

		delimCount = 0;
		fputc('\n',fpOut);
	}

	fclose(fpIn);
	fclose(fpOut);
}


FILE csvTotr9(char *inName, char *outName){

	char buff[BUFF_SIZE];
	char *delimString;

	FILE *fpIn;
	FILE *fpOut;

	fpIn = fopen(inName,"r");
	fpOut = fopen(outName,"w");

	if(fpIn == NULL){
		perror("File doesn't exist");
	}

	int delimCount = 0;

	while(fgets(buff,BUFF_SIZE,(FILE*)fpIn)!=NULL){

		int numOfDelims = 0;
		char *ptr = buff;

		while((ptr = strchr(ptr,',')) != NULL){
			numOfDelims++;
			ptr++;
		}

		delimString = strtok(buff,",\n");


		while(delimString!=NULL){

			int stringsize = strlen(delimString);


			if(stringsize > MAX_SPACE_TR9){
				for(int x = 0; x < MAX_SPACE_TR9; x++){
					fputc(delimString[(stringsize-MAX_SPACE_TR9)+x],fpOut);
				}
			}
			else if(stringsize < MAX_SPACE_TR9){

				for(int x = 0; x < (MAX_SPACE_TR9 - stringsize);x++){
					fputc(' ',fpOut);
				}

				for (int x = 0; x < stringsize; x++){
					fputc(delimString[x],fpOut);
				}

			}
			else{
				fprintf(fpOut,"%s",delimString);
			}

			if(delimCount < numOfDelims){
				fputc('|',fpOut);
				delimCount++;
			}


			delimString = strtok(NULL,",\n");
		}

		delimCount = 0;
		fputc('\n',fpOut);
	}

	fclose(fpIn);
	fclose(fpOut);
}


FILE tl5Totr9(char *inName, char *outName){

	char buff[BUFF_SIZE];
	char *delimString;

	FILE *fpIn;
	FILE *fpOut;

	fpIn = fopen(inName,"r");
	fpOut = fopen(outName,"w");

	if(fpIn == NULL){
		perror("File doesn't exist");
	}

	int delimCount = 0;

	while(fgets(buff,BUFF_SIZE,(FILE*)fpIn)!=NULL){
		
		int numOfDelims = 0;
		char *ptr = buff;

		while((ptr = strchr(ptr,'|')) != NULL){
			numOfDelims++;
			ptr++;
		}

		delimString = strtok(buff,"|\n");


		while(delimString!=NULL){

			int stringsize = strlen(delimString);


			for(int x = 0; x < (MAX_SPACE_TR9 - stringsize);x++){
				fputc(' ',fpOut);
			}

			for (int x = 0; x < stringsize; x++){
				fputc(delimString[x],fpOut);
			}


			if(delimCount < numOfDelims){
				fputc('|',fpOut);
				delimCount++;
			}


			delimString = strtok(NULL,"|\n");
		}

		delimCount = 0;
		fputc('\n',fpOut);
	}

	fclose(fpIn);
	fclose(fpOut);
}



FILE tr9Totl5(char *inName, char *outName){

	char buff[BUFF_SIZE];
	char *delimString;

	FILE *fpIn;
	FILE *fpOut;

	fpIn = fopen(inName,"r");
	fpOut = fopen(outName,"w");

	if(fpIn == NULL){
		perror("File doesn't exist");
	}

	int delimCount = 0;

	while(fgets(buff,BUFF_SIZE,(FILE*)fpIn)!=NULL){

		int numOfDelims = 0;
		char *ptr = buff;

		while((ptr = strchr(ptr,'|')) != NULL){
			numOfDelims++;
			ptr++;
		}

		delimString = strtok(buff,"|\n");


		while(delimString!=NULL){

			int stringsize = strlen(delimString);

			for(int x = 0; x < MAX_SPACE_TL5; x++){
					fputc(delimString[x],fpOut);
				}

			if(delimCount < numOfDelims){
				fputc('|',fpOut);
				delimCount++;
			}


			delimString = strtok(NULL,"|\n");
		}

		delimCount = 0;
		fputc('\n',fpOut);
	}

	fclose(fpIn);
	fclose(fpOut);
}


FILE tl5Tocsv(char *inName, char *outName){


	char buff[BUFF_SIZE];
	char *delimString;

	FILE *fpIn;
	FILE *fpOut;

	fpIn = fopen(inName,"r");
	fpOut = fopen(outName,"w");

	if(fpIn == NULL){
		perror("File doesn't exist");
	}

	int delimCount = 0;

	while(fgets(buff,BUFF_SIZE,(FILE*)fpIn)!=NULL){

		int numOfDelims = 0;
		char *ptr = buff;

		while((ptr = strchr(ptr,'|')) != NULL){
			numOfDelims++;
			ptr++;
		}

		delimString = strtok(buff," |\n");


		while(delimString!=NULL){

			int stringsize = strlen(delimString);
			
			fprintf(fpOut,"%s",delimString);

			if(delimCount < numOfDelims){
				fputc(',',fpOut);
				delimCount++;
			}


			delimString = strtok(NULL," |\n");
		}

		delimCount = 0;
		fputc('\n',fpOut);
	}

	fclose(fpIn);
	fclose(fpOut);
}



FILE tr9Tocsv(char *inName, char *outName){

	char buff[BUFF_SIZE];
	char *delimString;

	FILE *fpIn;
	FILE *fpOut;

	fpIn = fopen(inName,"r");
	fpOut = fopen(outName,"w");

	if(fpIn == NULL){
		perror("File doesn't exist");
	}

	int delimCount = 0;

	while(fgets(buff,BUFF_SIZE,(FILE*)fpIn)!=NULL){

		int numOfDelims = 0;
		char *ptr = buff;

		while((ptr = strchr(ptr,'|')) != NULL){
			numOfDelims++;
			ptr++;
		}

		delimString = strtok(buff," |\n");


		while(delimString!=NULL){

			int stringsize = strlen(delimString);
			
			fprintf(fpOut,"%s",delimString);

			if(delimCount < numOfDelims){
				fputc(',',fpOut);
				delimCount++;
			}


			delimString = strtok(NULL," |\n");
		}

		delimCount = 0;
		fputc('\n',fpOut);
	}

	fclose(fpIn);
	fclose(fpOut);
}


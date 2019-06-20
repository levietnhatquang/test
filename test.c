#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#define N			100
#define MAX_CHAR	2048
#define RAN_LOWER	48
#define RAN_UPPER 	122
#define TRUE		1
#define FALSE		0
#define IS_REMOVE	TRUE

void SaveSubStr(char *str, int low, int high);
int longestPalSubstr(char *str);

const char filename[] = "input.txt";
const char filename_2[] = "output.txt";

int GenInputFile(bool isRm);

int main(){
	GenInputFile(IS_REMOVE);

	char *str = (char *)malloc((MAX_CHAR + 1) * sizeof(char));

	FILE *f;
	f = fopen(filename,"r");
    if(f == NULL){
        fprintf(stderr,"Error writing to %s\n",filename);
        exit(EXIT_FAILURE);
    }

    remove(filename_2);
    printf("Generating output.txt...\n");
	for (int i = 0; i < N; i++){
		int j = 0;
		do{
			fread(str + j, sizeof(char), 1, f);
		}while (*(str + j++) != '\n');
		j--;
		*(str + j) = '\0';
		longestPalSubstr(str);
	}
	printf("Done.\n");

	fclose(f);

	return 0;
}

int GenInputFile(bool isRm)
{
	char a;

	if (isRm == FALSE){
		if(access(filename, F_OK) != -1 ){
    		printf("File input.txt existed.\n");
    		return 0;
		}
		else{
			 printf("File input.txt is not exist\n");
		}
	}

    FILE *f;
    printf("Generating input.txt...\n");
    f = fopen(filename,"w");
    if(f == NULL){
        fprintf(stderr,"Error writing to %s\n",filename);
        exit(EXIT_FAILURE);
    }
    int c;
	for (int i = 0; i < N; i++){
		c = rand() % (MAX_CHAR - 1 + 1) + 1;
		for (int j = 0; j < c; j++){
			do{
				a = rand() % (RAN_UPPER - RAN_LOWER + 1) + RAN_LOWER;
			}while ((58 <= a && a <= 64) || (91 <= a && a <= 96));
			fwrite(&a, sizeof(char), 1, f);
		}
		a = '\n';
		fwrite(&a, sizeof(char), 1, f);
	}
	fclose(f);

	return 0;
}

void SaveSubStr(char *str, int low, int high)
{
	const char NA[] = "N/A";

	FILE *f;
    f = fopen(filename_2,"a");
    if(f == NULL){
        fprintf(stderr,"Error writing to %s\n",filename);
        exit(EXIT_FAILURE);
    }

	if (high - low < 2){
		fwrite(NA, sizeof(char), (int)strlen(NA), f);
		fwrite("\n", sizeof(char), 1, f);
	}
	else{
		fwrite(str + low, sizeof(char), high - low + 1, f);
		fwrite("\n", sizeof(char), 1, f);
	}
	fclose(f);
} 

int longestPalSubstr(char *str) 
{ 
    int maxLength = 1;
    int start = 0; 
    int len = strlen(str); 
    int low, high; 

    for (int i = 1; i < len; ++i){ 
        low = i - 1; 
        high = i; 
        while (low >= 0 && high < len && str[low] == str[high]){ 
            if (high - low + 1 > maxLength){ 
                start = low; 
                maxLength = high - low + 1; 
            } 
            --low; 
            ++high; 
        } 

        low = i - 1; 
        high = i + 1; 
        while (low >= 0 && high < len && str[low] == str[high]){ 
            if (high - low + 1 > maxLength) 
            { 
                start = low; 
                maxLength = high - low + 1; 
            } 
            --low; 
            ++high; 
        } 
    }

    SaveSubStr(str, start, start + maxLength - 1); 
  
    return maxLength; 
} 
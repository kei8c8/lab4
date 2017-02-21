/*
 ============================================================================
 Name        : lab4.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void usage(void);
double* openfile(int);
double* offset(double, double*);
void newFile(char*, double*);
int length=0;
int max=0;


int main(int argc, char *argv[]) {
	int x=1;
	double* inpNum=0;
	int y=1;
	int flag=0;


	while(y < argc){
		if((argv[y][0] == '-') && (argv[y][1] == 'n')){
			printf("\n-n was found\n");
			int num=0;
			num = atoi(argv[y+1]);

			if(num<1 || num>11){
				usage();
			}
			else{
				inpNum = openfile(num);
				flag = 1;
			}

			y++;
		}
		y++;
	}

	if(flag != 1){
		usage();
	}

	while(x < argc){

		if((argv[x][0] == '-') && (argv[x][1] == 'n')){
			x++;
		}
		else if((argv[x][0] == '-') && (argv[x][1] == 'o')){
			printf("\n-o was found\n");
			int num1;
			double* new_array;
			double off=0;
			num1 = sscanf(argv[x+1], "%lf", &off);

			if(num1==0){
				printf("\nError.\n");
				usage();
			}

			new_array = offset(off, inpNum);

			x++;
		}
		else if((argv[x][0] == '-') && (argv[x][1] == 's')){
			printf("\n-s was found\n");
			int num2;
			float offset1=0;
			num2 = sscanf(argv[x+1], "%f", &offset1);

			if(num2==0){
				printf("\nError.\n");
				usage();
			}

			x++;
		}
		else if((argv[x][0] == '-') && (argv[x][1] == 'r')){
			printf("\n-r was found\n");
			int len=0;
			len = strlen(argv[x+1]);

			if(argv[x+1][len-1] != 't'){
				printf("\nError.\n");
				usage();
			}
			if(argv[x+1][len-2] != 'x'){
				printf("\nError.\n");
				usage();
			}
			if(argv[x+1][len-3] != 't'){
				printf("\nError.\n");
				usage();
			}
			if(argv[x+1][len-4] != '.'){
				printf("\nError.\n");
				usage();
			}

			x++;
		}
		else if((argv[x][0] == '-') && (argv[x][1] == 'h')){
			printf("\n-h was found\n");
			usage();

			x++;
		}
		else if((argv[x][0] == '-') && (argv[x][1] == 'S')){
			printf("\n-S was found\n");

			x++;
		}
		else if((argv[x][0] == '-') && (argv[x][1] == 'C')){
			printf("\n-C was found\n");

			x++;
		}
		else if((argv[x][0] == '-') && (argv[x][1] == 'N')){
			printf("\n-N was found\n");

			x++;
		}
		else{
			usage();
		}

		x++;
	}

	free(inpNum);
	return 0;
}

void usage(void){
	printf("\nUsage:");
	printf("\n\t-n <File number between 1 and 11>\tSelects the file to open.");
	printf("\n\t-o <Offset value>                \tOffsets the file numbers by the given value.");
	printf("\n\t-s <scale factor value>          \tScales the file numbers by the given value.");
	printf("\n\t-r <New filename>                \tRenames the file.");
	printf("\n\t-h                               \tHelp. Displays usage.");
	printf("\n\t-S                               \tShows statistics.");
	printf("\n\t-C                               \tCenters the signal.");
	printf("\n\t-N                               \tNormalizes the signal.\n\n");
	exit(0);
}

double* openfile(int num){

	FILE* file=0;
	double* n=0;
	int i=0;

	switch(num){
	case 1:
		file = fopen("Raw_data_01.txt", "r");
		break;
	case 2:
		file = fopen("Raw_data_02.txt", "r");
		break;
	case 3:
		file = fopen("Raw_data_03.txt", "r");
		break;
	case 4:
		file = fopen("Raw_data_04.txt", "r");
		break;
	case 5:
		file = fopen("Raw_data_05.txt", "r");
		break;
	case 6:
		file = fopen("Raw_data_06.txt", "r");
		break;
	case 7:
		file = fopen("Raw_data_07.txt", "r");
		break;
	case 8:
		file = fopen("Raw_data_08.txt", "r");
		break;
	case 9:
		file = fopen("Raw_data_09.txt", "r");
		break;
	case 10:
		file = fopen("Raw_data_10.txt", "r");
		break;
	case 11:
		file = fopen("Raw_data_11.txt", "r");
		break;
	default:
		printf("\nNot a valid option.\n");
		usage();
		break;
	}

	if(file == NULL){
		printf("\nError opening file.\n");
		exit(0);
	}

	fscanf(file, "%d %d", &length, &max);

	n = calloc(length, sizeof(int));

	for(i=0; i<length; i++){
		fscanf(file, "%lf", &n[i]);
	}

	fclose(file);
	return n;
}

double* offset(double off, double* nums){
	int x=0;
	double* new;
	new = calloc(length, sizeof(double));

	for(x=0;x<length;x++){
		new[x] = (double) (nums[x] + off);
	}
	return new;
}

void newFile(char*, double*){

}

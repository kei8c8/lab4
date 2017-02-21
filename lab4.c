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
void newFile(char*, double*, double);
void copyFile(char*, double*);
double* scale(double sca, double* nums);
double average(double*);
double act_max(double*);
int length=0;
int max;


int main(int argc, char *argv[]) {
	int x=1;
	double* inpNum=0;
	int y=1;
	int flag=0;
	int num=0;


	while(y < argc){
		if((argv[y][0] == '-') && (argv[y][1] == 'n')){
			printf("\n-n was found\n");
			num = 0;
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
			char* fn;
			double off=0;
			num1 = sscanf(argv[x+1], "%lf", &off);

			if(num1==0){
				printf("\nError.\n");
				usage();
			}

			new_array = offset(off, inpNum);

			fn = calloc(19, sizeof(char)); //length of filename including null terminator

			sprintf(fn, "Offset_data_%02d.txt", num);//prints to file name char*

			newFile(fn, new_array, off);

			free(new_array);
			free(fn);
			x++;
		}
		else if((argv[x][0] == '-') && (argv[x][1] == 's')){
			printf("\n-s was found\n");
			int num2;
			double sca=0;
			double* array2;
			char* fn2;
			num2 = sscanf(argv[x+1], "%lf", &sca);

			if(num2==0){
				printf("\nError.\n");
				usage();
			}

			array2 = scale(sca, inpNum);

			fn2 = calloc(19, sizeof(char)); //length of filename including null terminator

			sprintf(fn2, "Scaled_data_%02d.txt", num);//prints to file name char*

			newFile(fn2, array2, sca);

			free(array2);
			free(fn2);
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

			copyFile( argv[x+1], inpNum);


			x++;
		}
		else if((argv[x][0] == '-') && (argv[x][1] == 'h')){
			printf("\n-h was found\n");
			usage();

			x++;
		}
		else if((argv[x][0] == '-') && (argv[x][1] == 'S')){
			printf("\n-S was found\n");
			double stats_max=0;
			double stats_avg=0;
			char* fn3;

			stats_max = act_max(inpNum);
			stats_avg = average(inpNum);

			fn3 = calloc(25, sizeof(char));

			sprintf(fn3, "Statistics_data_%02d.txt", num);

			FILE* f;

			f = fopen(fn3, "w+");

			fprintf(f, "%.4lf %.0lf", stats_avg, stats_max);

			fclose(f);
			free(fn3);
			x++;
		}
		else if((argv[x][0] == '-') && (argv[x][1] == 'C')){
			printf("\n-C was found\n");
			double avg=0;
			double * new_centered;
			char* fn4=0;

			new_centered = calloc(length, sizeof(double));
			fn4 = calloc(25, sizeof(char));
			sprintf(fn4, "Centered_data_%02d.txt", num);

			avg = average(inpNum);
			avg *= (-1);
			new_centered = offset(avg, inpNum);

			newFile(fn4, new_centered, avg);

			free(new_centered);
			x++;
		}
		else if((argv[x][0] == '-') && (argv[x][1] == 'N')){
			printf("\n-N was found\n");
			double new_max;
			double * new_normalized;
			char* fn5=0;

			new_normalized = calloc(length, sizeof(double));
			fn5 = calloc(25, sizeof(char));
			sprintf(fn5, "Normalized_data_%02d.txt", num);

			new_max = ((double) 1 / (double) max);
			new_normalized = scale(new_max, inpNum);

			newFile(fn5, new_normalized, new_max);

			free(new_normalized);
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
	//test
	printf("\n%lf", (double)max);

	n = calloc(length, sizeof(double));

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

void newFile(char* filename, double* numbers1, double off_sca){
	FILE* fp=0;
	int x=0;

	fp = fopen(filename, "w+");

	fprintf(fp, "%d %.4lf", length, off_sca);

	for(x=0;x<length;x++){
		fprintf(fp, "\n%.4lf", numbers1[x]);
	}

	fclose(fp);
	return;
}

double* scale(double sca, double* nums){
	int x=0;
	double* new;
	new = calloc(length, sizeof(double));

	for(x=0;x<length;x++){
		new[x] = (double) (nums[x] * sca);
	}

	return new;
}

void copyFile(char* fn, double* nums){
	FILE* fp=0;
	int x=0;

	fp = fopen(fn, "w+");

	fprintf(fp, "%d %d", length, max);
	//test
	printf("\n%lf", (double)max);

	for(x=0;x<length;x++){
		fprintf(fp, "\n%.0d", (int) nums[x]);
	}

	fclose(fp);
	return;
}

double act_max(double* orig_nums){
	int x=0;
	double actual_max=0;

	actual_max = orig_nums[0];

	for(x=0;x<length;x++){
		if(orig_nums[x]>actual_max){
			actual_max = orig_nums[x];
		}
	}

	return actual_max;
}

double average(double* orig_nums){
	int i=0;
	double sum=0;
	double average=0;

	for(i=0;i<length;i++){
		sum += orig_nums[i];
	}

	average = (double) sum / length;

	return average;
}

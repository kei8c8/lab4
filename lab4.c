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

//initialize functions
void usage(void);
int* openfile(int);
double* offset(double, int*);
void newFile(char*, double*, double);
void copyFile(char*, int*);
double* scale(double sca, int* nums);
double average(int*);
double act_max(int*);
//found in one function, but can't return more
//than one variable from that function
//so global to use in multiple functions
int length=0;
int max;


int main(int argc, char *argv[]) {
	//initialize variables
	int x=1;
	int* inpNum=0;
	int y=1;
	int flag=0;
	int num=0;
	int flag1=0;

	//scans through entire command line looking for -n
	while(y < argc){
		if((argv[y][0] == '-') && (argv[y][1] == 'n')){
			num = 0;

			if((y+1) >= argc){ // if no number is entered after -n
				printf("\nError. Not enough information.\n"); //print error
				usage(); //shows usage
			}

			num = atoi(argv[y+1]); // converts character to integer

			if(num<1 || num>11){ //checks if option is out of range
				usage();
			}
			else{ //if in range
				inpNum = openfile(num); //open file specified and get numbers
				flag = 1; //file is found and opened
			}

			y++; //increments past y+1 because it's already found and used
		}
		y++;
	}

	if(flag != 1){ //if file is never found and open
		printf("\nError. Not enough information.\n");
		usage(); //
	}

	while(x < argc){ //looks for other command line arguments

		if((argv[x][0] == '-') && (argv[x][1] == 'n')){
			flag1 = 1;
			x++; //if found, skip because file has already been opened before
		}
		else if((argv[x][0] == '-') && (argv[x][1] == 'o')){
			flag1 = 1;
			//initializes variables
			int num1;
			double* new_array;
			char* fn=0;
			double off=0;

			if((x+1) >= argc){ //checks if there is an argument entered after the -o
				printf("\nError. Not enough information.\n");
				usage();
			}

			num1 = sscanf(argv[x+1], "%lf", &off); //checks if offset contains characters

			if(num1==0){  //if yes, print error
				printf("\nError.\n");
				usage();
			}

			new_array = offset(off, inpNum); //calls offset and returns the new array

			fn = calloc(19, sizeof(char)); //length of filename including null terminator

			sprintf(fn, "Offset_data_%02d.txt", num);//prints to file name char*

			newFile(fn, new_array, off); //puts new array in a new file

			//frees allocated memory
			free(new_array);
			free(fn);
			x++;
		}
		else if((argv[x][0] == '-') && (argv[x][1] == 's')){
			flag1 = 1;
			//initializes variables
			int num2;
			double sca=0;
			double* array2;
			char* fn2=0;

			if((x+1) >= argc){ //prints usage if there is no argument after -s
				printf("\nError. Not enough information.\n");
				usage();
			}

			num2 = sscanf(argv[x+1], "%lf", &sca); //checks if number contains characters

			if(num2==0){ //if yes, print error
				printf("\nError.\n");
				usage();
			}

			array2 = scale(sca, inpNum); //returns new, scaled array

			fn2 = calloc(19, sizeof(char)); //length of filename including null terminator

			sprintf(fn2, "Scaled_data_%02d.txt", num);//prints to file name char*

			newFile(fn2, array2, sca); //puts new array in a new file

			//frees allocated memory
			free(array2);
			free(fn2);
			x++;
		}
		else if((argv[x][0] == '-') && (argv[x][1] == 'r')){
			flag1 = 1;
			//initializes variables
			int len=0;
			char* new_filename;

			new_filename = 0;

			if((x+1) >= argc){ //makes sure there is a string after -r
				printf("\nError. Not enough information.\n");
				usage();
			}

			len = strlen(argv[x+1]); //finds the length of the given string
			//allocates enough memory for the string and the .txt added to it
			new_filename = calloc((len+5), sizeof(char));

			sprintf(new_filename, "%s.txt", argv[x+1]); //prints the new filename to a string
			copyFile( new_filename, inpNum); //copies and renames the file

			//frees allocated memory
			free(new_filename);
			x++;
		}
		else if((argv[x][0] == '-') && (argv[x][1] == 'h')){
			usage(); //prints usage
		}
		else if((argv[x][0] == '-') && (argv[x][1] == 'S')){
			flag1 = 1;
			//initializes variables
			double stats_max=0;
			double stats_avg=0;
			char* fn3=0;

			stats_max = act_max(inpNum); //finds the maximum
			stats_avg = average(inpNum); //determines the average of the array

			fn3 = calloc(25, sizeof(char)); //allocates space for file name

			sprintf(fn3, "Statistics_data_%02d.txt", num); //prints filename to string

			FILE* f;

			f = fopen(fn3, "w+"); //creates a new file

			fprintf(f, "%.4lf %.0lf", stats_avg, stats_max);

			//frees allocated memory
			fclose(f);
			free(fn3);
		}
		else if((argv[x][0] == '-') && (argv[x][1] == 'C')){
			flag1 = 1;
			//initializes variables
			double avg=0;
			double * new_centered;
			char* fn4=0;

			fn4 = calloc(25, sizeof(char)); //allocates memory for new filename
			sprintf(fn4, "Centered_data_%02d.txt", num); //prints new filename to string

			avg = average(inpNum); //finds the average
			avg *= (-1); //so it can be subtracted in the offset
			new_centered = offset(avg, inpNum); //creates new, centered array

			newFile(fn4, new_centered, avg); //put new array into a new file

			//frees allocated memory
			free(fn4);
			free(new_centered);
		}
		else if((argv[x][0] == '-') && (argv[x][1] == 'N')){
			flag1 = 1;
			//initializes variables
			double new_max;
			double * new_normalized;
			char* fn5=0;

			fn5 = calloc(25, sizeof(char)); //allocates memory for filename
			sprintf(fn5, "Normalized_data_%02d.txt", num);

			new_max = ((double) 1 / (double) max); //scale it by dividing by the max
			new_normalized = scale(new_max, inpNum); //creates new array

			newFile(fn5, new_normalized, new_max); //puts new array into a new file

			//frees allocated memory
			free(fn5);
			free(new_normalized);
		}

		if(flag1 != 1){
			usage(); //if doesn't match any, print usage
		}

		x++;
	}

	//frees allocated memory
	free(inpNum);
	return 0;
}

void usage(void){ //prints usage
	printf("\nUsage:");
	printf("\n\t-n <File number between 1 and 11>\tSelects the file to open.");
	printf("\n\t-o <Offset value>                \tOffsets the file numbers by the given value.");
	printf("\n\t-s <scale factor value>          \tScales the file numbers by the given value.");
	printf("\n\t-r <New filename>                \tRenames the file.");
	printf("\n\t-h                               \tHelp. Displays usage.");
	printf("\n\t-S                               \tShows statistics.");
	printf("\n\t-C                               \tCenters the signal.");
	printf("\n\t-N                               \tNormalizes the signal.\n");
	printf("\nExamples:\n   ./lab4 -n 2 - s 6.7\n   ./lab4 -C -n 4\n\n");
	exit(0); //quits program
}

int* openfile(int num){

	FILE* file=0; //creates pointer to file
	int* n=0;
	int i=0;

	switch(num){ //choses file based on number entered on the command line
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
		printf("\nNot a valid option.\n"); //error if out of bounds
		usage(); //prints usage
		break;
	}

	if(file == NULL){
		printf("\nError opening file.\n");
		exit(0); //exit if file couldn't be opened
	}

	fscanf(file, "%d %d", &length, &max); //read in length and max from the file

	n = calloc(length, sizeof(int)); //allocate memory for the array

	for(i=0; i<length; i++){
		fscanf(file, "%d", &n[i]); //read in the numbers from the file
	}

	fclose(file); //closes the file
	return n;
}

double* offset(double off, int* nums){
	int x=0;
	double* new;
	new = calloc(length, sizeof(double)); //allocate memory for the new array

	for(x=0;x<length;x++){
		new[x] = (double) (nums[x] + off); //adds offset to array of numbers
	}

	return new;
}

void newFile(char* filename, double* numbers1, double off_sca){
	FILE* fp=0;
	int x=0;

	fp = fopen(filename, "w+"); //creates new file

	fprintf(fp, "%d %.4lf", length, off_sca); //prints the length and offset/scale

	for(x=0;x<length;x++){
		fprintf(fp, "\n%.4lf", numbers1[x]); //prints all the new numbers from the arrays
	}

	fclose(fp); //closes file
	return;
}

double* scale(double sca, int* nums){
	int x=0;
	double* new;
	new = calloc(length, sizeof(double)); //allocates memory for the array

	for(x=0;x<length;x++){
		new[x] = (double) (nums[x] * sca); //creates the array of scaled numbers
	}

	return new;
}

void copyFile(char* fn, int* nums){
	FILE* fp=0;
	int x=0;

	fp = fopen(fn, "w+"); //opens a file to write to

	fprintf(fp, "%d %d", length, max); //prints the length and max to the file

	for(x=0;x<length;x++){
		fprintf(fp, "\n%d", (int) nums[x]); //prints numbers to the new file
	}

	fclose(fp); //closes file
	return;
}

double act_max(int* orig_nums){
	int x=0;
	double actual_max=0;

	actual_max = (double) orig_nums[0]; //makes initial max the first number in the array

	for(x=0;x<length;x++){
		if((double) orig_nums[x]>actual_max){ //compares each number to the max
			actual_max = (double) orig_nums[x]; //if larger, then make it the max
		}
	}

	return actual_max;
}

double average(int* orig_nums){
	int i=0;
	double sum=0;
	double average=0;

	for(i=0;i<length;i++){
		sum += (double) orig_nums[i]; //adds all the numbers in the array together
	}

	average = (double) sum / length; //divides sum by the amount of numbers in the array

	return average;
}

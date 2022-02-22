

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void exit_with_error(char* error_message);
void check_no_arguments(int no_args, int required_no_args);
void check_file_exists(char* filename);
void check_file_connection(FILE* file, char* filename);
void copy_files(char* filename1, char* filename2);

int main(int argc, char* argv[]) {
	
	// make sure the user only provided two arguments
	check_no_arguments(argc - 1, 2);

	// make sure that both files exist
	check_file_exists(argv[1]);
	check_file_exists(argv[2]);

	// make sure the user did not provide the same file twice	
	if (strcmp(argv[1], argv[2]) == 0)
		exit_with_error("The two files provided are the same file.");
	
	// tell the user what we are doing:
	// copying contents from file1 to file2
	printf("Copying contents from file '%s' to '%s'.\n", argv[1], argv[2]);

	// copy the contents from file1 to file2
	copy_files(argv[1], argv[2]);

	return 0;

}

void exit_with_error(char* error_message) {
	// prints the provided error message to the screen and exits with an error status 1
	
	printf("ERROR: %s\n", error_message);

	exit(1);

}

void check_no_arguments(int no_args, int required_no_args) {
	/*
	
	Checks if no_args is equal to required_no_args

	if not, then it outputs an error message and terminates the program

	*/

	// check if the number of required arguments matches the provided number of arguments
	if (no_args != required_no_args) {

		// format an error message string to be outputed to the console upon exit
		char error_message[256];
		sprintf(error_message, "%d arguments provided, please provide %d", no_args, required_no_args);
		
		// print error message and terminate program
		exit_with_error(error_message);
	}
}

void check_file_exists(char* filename) {

	// attempt to establish a connection with the file
	FILE* file = fopen(filename, "r");

	
	if (!file) {
		
		// if the connection could not be established, then the file does not exist
		
		// format an error message
		char error_message[256];
		sprintf(error_message, "File '%s' does not exist.", filename);
	
		// output an error message and terminate the program
		exit_with_error(error_message);

	}
	
	// close file connection to be safe either way	
	fclose(file);

}

void check_file_connection(FILE* file, char* filename) {
	/*
	
	Checks if a file exists provided the name of the file.
	Assumes that the file is in the same directory as the executable.

	If the file does not exist, it will output an error message and terminate the program.

	*/

	if (!file) {
		
		// close the file stream to be safe
		fclose(file);

		// create and format error message
		char error_message[256];
		sprintf(error_message, "Connection with file '%s' failed.", filename);
		
		// if the file does not exist, raise an error
		exit_with_error(error_message);

	}

}

void copy_files(char* filename1, char* filename2) {
	/*

	Copies the contents of filename1 and writes (overrides) the contents of filename2.

	It assumes that both files exist in the same directory as the executable.

	*/

	// source file is the file we are reading from
	FILE* source = fopen(filename1, "r");

	// make sure the source file exists and can be accessed
	check_file_connection(source, filename1);

	// dest file is the file we are writing to
	FILE* dest = fopen(filename2, "w");
	
	// make sure the dest file exists and can be accessed
	check_file_connection(dest, filename2);

	// read each character from filename1 and write it to filename2... until it encounters EOF
	for (char c = fgetc(source); !feof(source); c = fgetc(source))
		fputc(c, dest);

	// close the connections with both files
	fclose(source);
	fclose(dest);

}



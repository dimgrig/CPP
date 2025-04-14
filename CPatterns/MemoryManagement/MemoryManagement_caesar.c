#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <dirent.h> 

#define MAX_TEXT_SIZE 100

char EXE_NAME[MAX_TEXT_SIZE];

/* Performs a Caesar encryption with the fixed key 3.
The parameter 'text' must contain a text with only capital letters.
The parameter 'length' must contain the length of the text excluding
NULL termination. */
void caesar_encrypt(char* text, int length) {
	for(int i=0; i<length; i++) {
		text[i] = text[i]+3;
		if(text[i] > 'Z') {
			text[i] = text[i] - 'Z' + 'A' - 1;
		}
	}
}

void caesar_decrypt(char* text, int length) {
	for(int i=0; i<length; i++) {
		text[i] = text[i]-3;
		if(text[i] < 'A') {
			text[i] = text[i] + 'Z' - 'A' + 1;
		}
	}
}

void encryptCaesarText_stack() {
	char text[MAX_TEXT_SIZE];
	strncpy(text, "PLAINTEXT", MAX_TEXT_SIZE);
	caesar_encrypt(text, strnlen(text, MAX_TEXT_SIZE));
	printf("Encrypted text: %s\n", text);
	caesar_decrypt(text, strnlen(text, MAX_TEXT_SIZE));
	printf("Decrypted text: %s\n", text);
}

void encryptCaesarText_static() {
	static char text[MAX_TEXT_SIZE];
	strncpy(text, "PLAINTEXT", MAX_TEXT_SIZE);
	caesar_encrypt(text, strnlen(text, MAX_TEXT_SIZE));
	printf("Encrypted text: %s\n", text);
	caesar_decrypt(text, strnlen(text, MAX_TEXT_SIZE));
	printf("Decrypted text: %s\n", text);
}

/* Returns the length of the file with the provided 'filename' */
int getFileLength(char* filename) {
	FILE* f = fopen(filename, "r");
	fseek(f, 0, SEEK_END);
	int file_length = ftell(f);
	fclose(f);
	return file_length;
}
/* Stores the content of the file with the provided 'filename' into the
provided 'buffer' (which has to be least of size 'file_length'). The
file must only contain capital letters with no newline in between
(that's what our caesar function accepts as input). */
void readFileContent(char* filename, char* buffer, int file_length) {
	FILE* f = fopen(filename, "r");
	fseek(f, 0, SEEK_SET);
	int read_elements = fread(buffer, 1, file_length, f);
	buffer[read_elements] = '\0';
	fclose(f);
}

/* For the provided 'filename', this function reads text from the file and
prints the Caesar-encrypted text. This function is responsible for
allocating and deallocating the required buffers for storing the
file content */
void encryptCaesar_file(char* filename) {
	printf("File: %s\n", filename);
	if (strcmp(filename, EXE_NAME) != 0) {
		int size = getFileLength(filename);
		if(size>0) {
			char* text;
			text = malloc(size);
			readFileContent(filename, text, size);
			caesar_encrypt(text, strnlen(text, size));
			printf("Encrypted text: %s\n", text);
			free(text);
		}
	}
}

/* For all files in the current directory, this function reads text
from the file and prints the Caesar-encrypted text. */
void encryptCaesar_dir() {
	struct dirent *directory_entry;
	DIR *directory = opendir(".");
	while ((directory_entry = readdir(directory)) != NULL) {
		encryptCaesar_file(directory_entry->d_name);
	}
	closedir(directory);
}

/* Allocates memory and asserts if no memory is available */
void* safeMalloc(size_t size) {
	void* pointer = malloc(size);
	assert(pointer);
	return pointer;
}

/* Deallocates the memory of the provided 'pointer' */
void safeFree(void *pointer) {
	free(pointer);
}

void encryptCaesar_file_safe(char* filename) {
	printf("File: %s\n", filename);
	if (strcmp(filename, EXE_NAME) != 0) {
		int size = getFileLength(filename);
		if(size>0) {
			char* text = NULL;
			text = safeMalloc(size);
			if(text != NULL) {
				readFileContent(filename, text, size);
				caesar_encrypt(text, strnlen(text, size));
				printf("Encrypted text: %s\n", text);
			}
			safeFree(text);
			text = NULL;
		}
	}
}

void encryptCaesar_dir_safe() {
	struct dirent *directory_entry;
	DIR *directory = opendir(".");
	while ((directory_entry = readdir(directory)) != NULL) {
		encryptCaesar_file_safe(directory_entry->d_name);
	}
	closedir(directory);
}

int main(int argc, char *argv[]) {
	// if (argc != 2) {
	// 	printf("Usage: ErrorHandling filename\r\n");
	// 	exit(0);
	// }

	strncpy(EXE_NAME, argv[0], MAX_TEXT_SIZE);
	char *ps = EXE_NAME;
	for (; *ps != '\0'; ps++) {
    	*ps = *(ps+2);
	}
	*ps = '\0';
	printf("EXE_NAME %s\r\n", EXE_NAME);
	//encryptCaesarText_stack();
	//encryptCaesarText_static();
	//encryptCaesar_file("readme.txt");
	//encryptCaesar_dir();
	encryptCaesar_dir_safe();

	return 0;
}
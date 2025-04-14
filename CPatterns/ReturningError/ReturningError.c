#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define STRING_SIZE 100
#define MAX_KEYS 40

/* Error codes returned by this registry */
typedef enum {
	OK,
	OUT_OF_MEMORY,
	INVALID_PARAMETER,
	STRING_TOO_LONG,
	CANNOT_ADD_KEY
} RegError;

/* Handle for registry keys */
typedef struct Key* RegKey;
/* Create a new registry key identified via the provided 'key_name'.
Returns OK if no problem occurs, INVALID_KEY if the 'key'
parameter is NULL, INVALID_STRING if 'key_name' is NULL,
STRING_TOO_LONG if 'key_name' is too long, or OUT_OF_MEMORY
if no memory resources are available. */
RegError createKey(char* key_name, RegKey* key);
/* Store the provided 'value' to the provided 'key'.
Returns OK if no problem occurs, INVALID_KEY if the 'key'
parameter is NULL, INVALID_STRING if 'value' is NULL, or
STRING_TOO_LONG if 'value' is too long. */
RegError storeValue(RegKey key, char* value);
/* Make the key available for being read. Returns OK if no
problem occurs, INVALID_KEY if 'key' is NULL, or CANNOT_ADD_KEY
if the registry is full and no more keys can be published. */
RegError publishKey(RegKey key);

struct Key {
	char key_name[STRING_SIZE];
	char key_value[STRING_SIZE];
};

/* file-global array holding all registry keys */
static struct Key* key_list[MAX_KEYS];

RegError createKey(char* key_name, RegKey* key) {
	// if(key == NULL || key_name == NULL) {
	// 	return INVALID_PARAMETER;
	// }
	// if(STRING_SIZE <= strlen(key_name)) {
	// 	return STRING_TOO_LONG;
	// }
	assert(key != NULL && key_name != NULL);
	assert(STRING_SIZE > strlen(key_name));
	RegKey newKey = calloc(1, sizeof(struct Key));
	if(newKey == NULL) {
		return OUT_OF_MEMORY;
	}
	strcpy(newKey->key_name, key_name);
	*key = newKey;
	return OK;
}

RegError storeValue(RegKey key, char* value) {
	// if(key == NULL || value == NULL) {
	// 	return INVALID_PARAMETER;
	// }
	// if(STRING_SIZE <= strlen(value)) {
	// 	return STRING_TOO_LONG;
	// }
	assert(key != NULL && value != NULL);
	assert(STRING_SIZE > strlen(value));
	strcpy(key->key_value, value);
	return OK;
}

RegError publishKey(RegKey key) {
	int i;
	// if(key == NULL) {
	// 	return INVALID_PARAMETER;
	// }
	assert(key != NULL);
	for(i=0; i<MAX_KEYS; i++) {
		if(key_list[i] == NULL) {
			key_list[i] = key;
			return OK;
		}
	}
	return CANNOT_ADD_KEY;
}

// int main(int argc, char *argv[]) {
// 	// if (argc != 2) {
// 	// 	printf("Usage: ErrorHandling filename\r\n");
// 	// 	exit(0);
// 	// }
// 	RegError err;
// 	{
// 		RegKey my_key;
// 		err = createKey("myKey", &my_key);
// 		if (err == INVALID_PARAMETER) {
// 			printf("Internal application error\n");
// 		}
// 		if (err == STRING_TOO_LONG) {
// 			printf("Provided registry key name too long\n");
// 		}
// 		if (err == OUT_OF_MEMORY) {
// 			printf("Insufficient resources to create key\n");
// 		}
// 		err = storeValue(my_key, "A");
// 		if (err == INVALID_PARAMETER) {
// 			printf("Internal application error\n");
// 		}
// 		if (err == STRING_TOO_LONG) 	{
// 			printf("Provided registry value to long to be stored to this key\n");
// 		}
// 		err = publishKey(my_key);
// 		if (err == INVALID_PARAMETER)	{
// 			printf("Internal application error\n");
// 		}
// 		if(err == CANNOT_ADD_KEY) {
// 			printf("Key cannot be published, because the registry is full\n");
// 		}
// 	}
// 	{
// 		RegKey my_key;
// 		err = createKey(NULL, &my_key);
// 		if (err == INVALID_PARAMETER) {
// 			printf("Internal application error\n");
// 		}
// 		if (err == STRING_TOO_LONG) {
// 			printf("Provided registry key name too long\n");
// 		}
// 		if (err == OUT_OF_MEMORY) {
// 			printf("Insufficient resources to create key\n");
// 		}
// 	}
// 	{
// 		err = createKey("myKey", NULL);
// 		if (err == INVALID_PARAMETER) {
// 			printf("Internal application error\n");
// 		}
// 		if (err == STRING_TOO_LONG) {
// 			printf("Provided registry key name too long\n");
// 		}
// 		if (err == OUT_OF_MEMORY) {
// 			printf("Insufficient resources to create key\n");
// 		}
// 	}
// 	{
// 		RegKey my_key;
// 		err = createKey("myKey", &my_key);
// 		if (err == INVALID_PARAMETER) {
// 			printf("Internal application error\n");
// 		}
// 		if (err == STRING_TOO_LONG) {
// 			printf("Provided registry key name too long\n");
// 		}
// 		if (err == OUT_OF_MEMORY) {
// 			printf("Insufficient resources to create key\n");
// 		}
// 		err = storeValue(my_key, "1241251295129610296719026719245819025871290571290571279034812094812094812904127591275192410248790214");
// 		if (err == INVALID_PARAMETER) {
// 			printf("Internal application error\n");
// 		}
// 		if (err == STRING_TOO_LONG) 	{
// 			printf("Provided registry value to long to be stored to this key\n");
// 		}
// 	}
// 	return 0;
// }

int main(int argc, char *argv[]) {
	// if (argc != 2) {
	// 	printf("Usage: ErrorHandling filename\r\n");
	// 	exit(0);
	// }
	RegError err;
	{
		RegKey my_key;
		err = createKey("myKey", &my_key);
		if (err == OUT_OF_MEMORY) {
			printf("Insufficient resources to create key\n");
		}
		err = storeValue(my_key, "A");
		err = publishKey(my_key);
		if(err == CANNOT_ADD_KEY) {
			printf("Key cannot be published, because the registry is full\n");
		}
	}
	{
		RegKey my_key;
		err = createKey("myKey", &my_key);
		if (err == OUT_OF_MEMORY) {
			printf("Insufficient resources to create key\n");
		}
		err = storeValue(my_key, "A");
	}
	return 0;
}
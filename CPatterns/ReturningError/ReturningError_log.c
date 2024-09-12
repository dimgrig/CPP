#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h> 
#include <stdbool.h>

#define STRING_SIZE 100
#define MAX_KEYS 40

/* macro to log debug info and to assert */
#define logAssert(X) \
	if(!(X)) { \
		printf("Error at line %i", __LINE__); \
		assert(false); \
	}

/* Error codes returned by this registry */
typedef enum {	
	OK,
	CANNOT_ADD_KEY
} RegError;

/* Handle for registry keys */
typedef struct Key* RegKey;
/* Create a new registry key identified via the provided 'key_name'.
Returns OK if no problem occurs, INVALID_KEY if the 'key'
parameter is NULL, INVALID_STRING if 'key_name' is NULL,
STRING_TOO_LONG if 'key_name' is too long, or OUT_OF_MEMORY
if no memory resources are available. */
RegKey createKey(char* key_name);
/* Store the provided 'value' to the provided 'key'.
Returns OK if no problem occurs, INVALID_KEY if the 'key'
parameter is NULL, INVALID_STRING if 'value' is NULL, or
STRING_TOO_LONG if 'value' is too long. */
void storeValue(RegKey key, char* value);
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

RegKey createKey(char* key_name) {
	logAssert(key_name != NULL);
	logAssert(STRING_SIZE > strlen(key_name));
	RegKey newKey = calloc(1, sizeof(struct Key));
	if(newKey == NULL) {
		return NULL;
	}
	strcpy(newKey->key_name, key_name);
	return newKey;
}

void storeValue(RegKey key, char* value) {
	logAssert(key != NULL && value != NULL);
	logAssert(STRING_SIZE > strlen(value));
	strcpy(key->key_value, value);
}

RegError publishKey(RegKey key) {
	int i;
	logAssert(key != NULL);
	for(i=0; i<MAX_KEYS; i++) {
		if(key_list[i] == NULL) {
			key_list[i] = key;
			return OK;
		}
	}
	return CANNOT_ADD_KEY;
}

int main(int argc, char *argv[]) {
	RegError err;
	{
		RegKey my_key = createKey("myKey");
		if(my_key == NULL) {
			printf("Cannot create key\n");
		}
		storeValue(my_key, "A");
		RegError err = publishKey(my_key);
		if(err == CANNOT_ADD_KEY) {
			printf("Key cannot be published, because the registry is full\n");
		}
	}
	{
		RegKey my_key = createKey("myKey");
		if(my_key == NULL) {
			printf("Cannot create key\n");
		}
		storeValue(my_key, NULL);
		RegError err = publishKey(my_key);
		if(err == CANNOT_ADD_KEY) {
			printf("Key cannot be published, because the registry is full\n");
		}
	}
	return 0;
}
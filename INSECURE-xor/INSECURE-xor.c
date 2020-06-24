#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *read_file(const char *filename) {
    long int size = 0;
    FILE *file = fopen(filename, "r");

    if(!file) {
	printf("The file %s doesn't exsist!!!", filename);
	exit(1);
    }

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);

    char *result = (char *) malloc(size);
    if(!result) {
        fputs("Memory error.\n", stderr);
        return NULL;
    }

    if(fread(result, 1, size, file) != size) {
        fputs("Read error.\n", stderr);
        return NULL;
    }

    fclose(file);
    return result;
}


void write_file(char *filename, char *contents) {
	FILE *fp = fopen(filename, "w");
	if (fputs(contents, fp) < 0) {
		printf("write_file error");
	}
}


char *cipher(char *key, char *text) {
	for (int i = 0; i < strlen(text); i++) {
		text[i] = text[i] ^ key[i % 512];
	}
}


int main(int argc, char *argv[]) {
	if (argc != 4) {
		printf("Usage: ./feistel <key file> <pt|ct file> <out file>\n");
		exit(1);
	}

	char *key = read_file(argv[1]);
	char *text = read_file(argv[2]);

	if (strlen(key) != 512) {
		printf("Key size must be 512 bytes (Size is : %ld)\n", strlen(key));
	}
	
	printf("Processing %ld bytes... ", strlen(text));

	cipher(key, text);
	write_file(argv[3], text);

	printf("done\n");

	return 0;
}


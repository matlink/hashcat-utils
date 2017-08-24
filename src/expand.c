#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void expand(char* line){
        int occ = atoi(strtok(line, " "));
        const char* word  = strtok(NULL, "\0\n");
        for(; occ!=0; occ--){
                printf("%s", word);
        }
        return;
}

int main(int argc, char** argv){
        FILE* fp = fopen(argv[1], "r");
        char* line = NULL;
        size_t len;
        ssize_t read;
        if (fp == NULL) { exit(EXIT_FAILURE); }
        while ((read = getline(&line, &len, fp)) != -1) {
                expand(line);
        }
        fclose(fp);
        if (line) { free(line); }
        return EXIT_SUCCESS;
}

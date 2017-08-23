#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void expand(char* line, size_t len){
        int copying = 0;
        int i = 0;
        for(; i < len; i++){
                if (! copying && line[i] != ' '){
                        continue;
                }
                break;
        }
        char occ_str[i];
        memcpy( occ_str, line, i);
        int occurences = atoi(occ_str);
        i++;
        char* output = (char*) malloc(len-i);
        for(int j=0; j < (len-i); j++){
                output[j] = line[j+i];
        }
        for(;occurences!=0; occurences--){
                printf("%s", output);
        }
}

int main(int argc, char** argv){
        FILE* fp = fopen(argv[1], "r");
        char* line = NULL;
        size_t len = 0;
        ssize_t read;
        if (fp == NULL) { exit(EXIT_FAILURE); }
        while ((read = getline(&line, &len, fp)) != -1) {
                expand(line, len);
        }
        fclose(fp);
        if (line) { free(line); }
        return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu_rules.h"

#define HCBUFSIZ_LARGE      0xb0000
#define WORD_BUFF 256

int max_len = 0;

int fgetl (FILE *fp, char *line_buf)
{
  int line_len = 0;

  while (!feof (fp))
  {
    const int c = fgetc (fp);

    if (c == EOF) break;

    line_buf[line_len] = (char) c;

    line_len++;

    if (line_len == HCBUFSIZ_LARGE) line_len--;

    if (c == '\n') break;
  }

  if (line_len == 0) return 0;

  while (line_len)
  {
    if (line_buf[line_len - 1] == '\n')
    {
      line_len--;

      continue;
    }

    if (line_buf[line_len - 1] == '\r')
    {
      line_len--;

      continue;
    }

    break;
  }

  line_buf[line_len] = 0;

  return (line_len);
}


int main(int argc, char **argv){
        if (argc <= 1){
                fprintf(stderr, "Usage: %s [rulefile, ...]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
        FILE *fp = fopen(argv[1], "r");
        if (fp == NULL){
                fprintf(stderr, "File %s cannot be found\n", argv[1]);
                fclose(fp);
                exit(EXIT_FAILURE);
        }

        char **words = (char**) malloc(WORD_BUFF * sizeof(char*));
        size_t wordstab_size = WORD_BUFF;
        unsigned int nb_words = 0;
        char rule[RP_RULE_BUFSIZ];
        unsigned int rule_len;
        char in[BLOCK_SIZE];
        unsigned int in_len;
        char out[BLOCK_SIZE];
        unsigned int wordit;

        // get every words from stdin in dynamic array
        while((in_len = fgetl(stdin, in))){
                words[nb_words] = (char*) malloc(in_len * sizeof(char));
                memcpy(words[nb_words], in, in_len);
                nb_words++;
                //realloc when array is too small
                if(nb_words > wordstab_size){
                        words = (char**) realloc(words, sizeof(char*) * wordstab_size * 2);
                        wordstab_size *= 2;
                }
        }

        // take a rule and apply it to every words
        while(!feof (fp)){
                rule_len = fgetl(fp, rule);
                if(rule[0] == '#') continue;
                if(rule[0] == ' ') continue;
                for(wordit=0; wordit < nb_words; wordit++){
                        apply_rule_cpu(rule, rule_len, words[wordit], strlen(words[wordit]), out);
                        printf("%s\n", out);
                }
        }

        fclose(fp);

        for(wordit=0; wordit < nb_words; wordit++){
                free(words[wordit]);
        }
        free(words);

        return 0;
}

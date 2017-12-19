#include <stdio.h>
#include <stdlib.h>

#include "cpu_rules.h"

#define HCBUFSIZ_LARGE      0xb0000

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

int main(void){
        char* rule = "r";
        int rule_len = 1;
        char in[BLOCK_SIZE];
        int in_len;
        char out[BLOCK_SIZE];
        while((in_len = fgetl(stdin, in))){
                apply_rule_cpu(rule, rule_len, in, in_len, out);
                printf("%s\n", out);
        }
        return 0;
}

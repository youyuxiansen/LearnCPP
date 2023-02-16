#include <stdio.h>

int main(void)
{
  char str[13] = "Hi, I'm odd!";
//   char str[] = "Hi, I'm odd!";
//   char *str = "Hi, I'm odd!";
  int exclamationCheck = 0;
  for(int i = 0; str[i] != '\0'; ++i)
  {
    if(str[i] == '!')
    {
      exclamationCheck = 1;
      break;
    }
  }
  printf("exclamationCheck = %d\n", exclamationCheck);
  return 0;
}
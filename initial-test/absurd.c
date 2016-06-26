#include <stdio.h>
#include <stdlib.h>

int stringFunc(char *p1, char *p2)
{
   int first, second;
   
   first = atoi(*p1);
   second = atoi (*p2);
   
   if(first < second)
      return -1;
   
   else if(first > second)
      return 1;
   
   return 0;
}

int main(int argc, char** argv)
{
   int count;
   
   qsort((void *)&argv[1], argc -1, sizeof(char *),
      (int (*)(void *, void *))stringFunc);
   
   for(count = 1; count < argc; count++)
      printf("%s\n", argv[count]);
   
   return 0;
}

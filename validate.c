/* code for validating textbox */
#include <stdio.h>
#include <stdlib.h>
 int check(char data[9])
 {
  int flag=0;
  int i=0;
  for(i=0;i<9;i++)
  {
   if(data[i]>=48 && data[i]<=57)
    { }
    else
    { flag=1; }
  }
  if(flag==0)
  { return 0; }
  else
  { return 1; }  
}  

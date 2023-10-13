#include <stdio.h>

#include <string.h>

#include <math.h>

#include <stdlib.h>

int main() {
char sentence[500];
scanf("%[^\n]s",&sentence);
int length;
length=strlen(sentence);
for (int i=0; i<length; i++)
{
if(sentence[i] !=' ')
{
printf("%c", sentence[i]);
}
else
{
printf("\n");
}
}
}


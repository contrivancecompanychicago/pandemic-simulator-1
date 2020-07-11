#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void logHour(FILE* file, int totalCases, int activeCases, int deaths, int recoveries){
  static int hour = 1;
  char* data = malloc(35*sizeof(char));
  sprintf(data, "%d,%d,%d,%d,%d\n", hour, totalCases, activeCases, deaths, recoveries);
  fwrite(data, strlen(data), 1, file);
  hour++;
  free(data);
}

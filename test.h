#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define couleur(param) printf("\033[%sm", param)

void FileRead(double time_save);
void FileWrite(double new_time);
void save_best_time(double new_result);
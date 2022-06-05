#include "test.h"

#define TAILLE_MAX 1000 // Tableau de taille 1000

void FileRead(double time_save) {
  FILE *fFile;
  char chaine[TAILLE_MAX] = {0};

  fFile = fopen("C:\\Dorian\\info\\stockage.txt", "r+");
  if (fFile != NULL) {

    fgets(chaine, TAILLE_MAX, fFile);
    time_save = atoi(chaine);
    fclose(fFile);
  } else
    printf("\n\nERROR readind file test.txt");
}

void FileWrite(double new_time) {
  char meilleur_temps[TAILLE_MAX] = {0};
  FILE *fFile;
  
  fFile = fopen("C:\\Dorian\\info\\stockage.txt", "w+");
  if (fFile != NULL) {
    
    sprintf(meilleur_temps, "%02d", (int) new_time);       
    fputs(meilleur_temps, fFile);
    fclose(fFile);
  } else
    printf("\n\nERROR Writting file test.txt");
}
void save_best_time(double new_result) {
  double res =0;
  double old_res =10000;
  // recherche dernier chrono saugardé

  FileRead(old_res);
  res = old_res - new_result;
  if (res > 0) { // si le nouveau resultat est plus petit que l'encien
    printf("bravo vous avez le  meilleur score");
    FileWrite(new_result);
  } 
   else {
    time_t diff = old_res;
    struct tm tm_diff = *gmtime(&diff);
    couleur("34;1");
    printf("\n\nle meilleur temps est de : min: %02d sec : %02d ",
           tm_diff.tm_min, tm_diff.tm_sec);
    couleur("0");
  }
}
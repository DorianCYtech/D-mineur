
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "test.h"

#define couleur(param) printf("\033[%sm", param)
#define BOMB -88

void clear(FILE *file) {
  char character;
  do {
    character = fgetc(file); // This function allows you to exclude certain
                             // characters from being taken into account
  } while (character != EOF && character != '\n');
}

void vide_buffer() {
  while (getc(stdin) != '\n') {
  }
}

int **construct_grille(int line, int column,
                       int choice) { /*The function creates and returns an array
                                        of variable size, filled with bombs*/

  int i, j, a, b, n;
  int **grid =
      malloc(line * sizeof(int *)); /*declaration of the variable-size array*/
  for (i = 0; i < line; i++) {      /*loop that fills the array in 2D by 0*/
    grid[i] = malloc(column * sizeof(int));
    for (j = 0; j < column; j++) {
      grid[i][j] = -9;
    }
  }

  if (choice == 1) { /* loop that places 10 bombs randomly in the 2D array */
    n = 10;
    while (n != 0) {
      a = rand() % 9;
      b = rand() % 9;

      if (grid[a][b] == -9) {
        grid[a][b] = BOMB;
        n = n - 1;
      }
     printf("\n");
    }

  } else { /* loop that places 40 bombs randomly in the 2D array*/
    n = 40;
    while (n != 0) {
      a = rand() % 16;
      b = rand() % 16;
      if (grid[a][b] == -9) {
        grid[a][b] = BOMB;
        n = n - 1;
      }
    }
  }

  /* top right corner*/
  if (grid[0][column - 1] == -9) {
    n = 0;
    if (grid[0][column - 2] == BOMB) {
      n--;
    }
    if (grid[1][column - 2] == BOMB) {
      n--;
    }
    if (grid[1][column - 1] == BOMB) {
      n--;
    }
    if (n == 0) {
      grid[0][column - 1] = -9;
    } else {
      grid[0][column - 1] = n;
    }
  }
  /*top left corner*/
  if (grid[0][0] == -9) {
    n = 0;
    if (grid[0][1] == BOMB) {
      n--;
    }
    if (grid[1][0] == BOMB) {
      n--;
    }
    if (grid[1][1] == BOMB) {
      n--;
    }
    if (n == 0) {
      grid[0][0] = -9;
      ;
    } else {
      grid[0][0] = n;
    }
  }

  /* top line without corners */
  for (i = 1; i < column - 1; i++) {
    if (grid[0][i] == -9) {
      n = 0;
      if (grid[0][i - 1] == BOMB) {
        n--;
      }
      if (grid[0][i + 1] == BOMB) {
        n--;
      }
      if (grid[1][i] == BOMB) {
        n--;
      }
      if (grid[1][i - 1] == BOMB) {
        n--;
      }
      if (grid[1][i + 1] == BOMB) {
        n--;
      }
      if (n == 0) {
        grid[0][i] = -9;
      } else {
        grid[0][i] = n;
      }
    }
  }
  /* central square without rows and columns at the edge */
  for (i = 1; i < line - 1; i++) {
    for (j = 1; j < column - 1; j++) {
      if (grid[i][j] == -9) {
        n = 0;
        if (grid[i - 1][j] == BOMB) {
          n--;
        }
        if (grid[i - 1][j - 1] == BOMB) {
          n--;
        }
        if (grid[i - 1][j + 1] == BOMB) {
          n--;
        }
        if (grid[i][j - 1] == BOMB) {
          n--;
        }
        if (grid[i][j + 1] == BOMB) {
          n--;
        }
        if (grid[i + 1][j] == BOMB) {
          n--;
        }
        if (grid[i + 1][j - 1] == BOMB) {
          n--;
        }
        if (grid[i + 1][j + 1] == BOMB) {
          n--;
        }
        if (n == 0) {
          grid[i][j] = -9;
        } else {
          grid[i][j] = n;
        }
      }
    }
  }
  /* bottom line without corners */
  for (i = 1; i < column - 1; i++) {
    if (grid[line - 1][i] == -9) {
      n = 0;
      if (grid[line - 1][i - 1] == BOMB) {
        n--;
      }
      if (grid[line - 1][i + 1] == BOMB) {
        n--;
      }
      if (grid[line - 2][i] == BOMB) {
        n--;
      }
      if (grid[line - 2][i - 1] == BOMB) {
        n--;
      }
      if (grid[line - 2][i + 1] == BOMB) {
        n--;
      }
      if (n == 0) {
        grid[line - 1][i] = -9;
      } else {
        grid[line - 1][i] = n;
      }
    }
  }
  /*  bottom left corner */
  if (grid[line - 1][0] == -9) {
    n = 0;
    if (grid[line - 1][1] == BOMB) {
      n--;
    }
    if (grid[line - 2][0] == BOMB) {
      n--;
    }
    if (grid[line - 2][1] == BOMB) {
      n--;
    }
    if (n == 0) {
      grid[line - 1][0] = -9;
    } else {
      grid[line - 1][0] = n;
    }
  }
  /*  bottom right corner */
  if (grid[line - 1][column - 1] == -9) {
    n = 0;
    if (grid[line - 1][column - 2] == BOMB) {
      n--;
    }
    if (grid[line - 2][column - 2] == BOMB) {
      n--;
    }
    if (grid[line - 2][column - 1] == BOMB) {
      n--;
    }
    if (n == 0) {
      grid[line - 1][column - 1] = -9;
    } else {
      grid[line - 1][column - 1] = n;
    }
  }
  /* left-hand column */
  for (i = 1; i < line - 1; i++) {
    if (grid[i][0] == -9) {
      n = 0;
      if (grid[i + 1][0] == BOMB) {
        n--;
      }
      if (grid[i - 1][0] == BOMB) {
        n--;
      }
      if (grid[i][1] == BOMB) {
        n--;
      }
      if (grid[i + 1][1] == BOMB) {
        n--;
      }
      if (grid[i - 1][1] == BOMB) {
        n--;
      }
      if (n == 0) {
        grid[i][0] = -9;
      } else {
        grid[i][0] = n;
      }
    }
  }
  /* right-hand column */
  for (i = 1; i < line - 1; i++) {
    if (grid[i][column - 1] == -9) {
      n = 0;
      if (grid[i - 1][column - 1] == BOMB) {
        n--;
      }
      if (grid[i - 1][column - 2] == BOMB) {
        n--;
      }
      if (grid[i][column - 2] == BOMB) {
        n--;
      }
      if (grid[i + 1][column - 2] == BOMB) {
        n--;
      }
      if (grid[i + 1][column - 1] == BOMB) {
        n--;
      }
      if (n == 0) {
        grid[i][column - 1] = -9;
      } else {
        grid[i][column - 1] = n;
      }
    }
  }
  return grid;
}

unsigned long getTimeMicroSec() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (1 * tv.tv_usec);
}

void regle() {
  printf("You have a grid with hidden mines.\n"

         "By clicking on a square you can see how many mines are in the "
         "surrounding squares (maximum 8).\n"

         "The aim of the game is to find all the free box without exploding "
         "the mines, i.e. without selecting the squares that hide them. \n\n");
}
/*
 Algorithm
*/

int decouvrirRec(int **grid, int a, int b, int line, int counter) {

  /*printf("counter=%d",counterr);*/
  if (grid[a][b] == -9) {
    grid[a][b] = grid[a][b] * (-1);
    counter++;
    if (a >= 1) {
      counter = decouvrirRec(grid, a - 1, b, line, counter);
    }
    if (a < line - 1) {
      counter = decouvrirRec(grid, a + 1, b, line, counter);
    }
    if (b >= 1) {
      counter = decouvrirRec(grid, a, b - 1, line, counter);
    }
    if (b < line - 1) {
      counter = decouvrirRec(grid, a, b + 1, line, counter);
    }
    if (a >= 1 && b >= 1) {
      counter = decouvrirRec(grid, a - 1, b - 1, line, counter);
    }
    if (a < line - 1 && b < line - 1) {
      counter = decouvrirRec(grid, a + 1, b + 1, line, counter);
    }
    if (a >= 1 && b < line - 1) {
      counter = decouvrirRec(grid, a - 1, b + 1, line, counter);
    }
    if (a < line - 1 && b >= 1) {
      counter = decouvrirRec(grid, a + 1, b - 1, line, counter);
    }

  } else if (grid[a][b] < 0 && grid[a][b] > -9) {
    grid[a][b] = grid[a][b] * (-1);
    counter++;
  }
  return counter;
}

void affiche_grille(int party_level, int **grid) {
  int line, column, verification, i, j, k, a, c, counter = 0;
  char letter = 64;
  int beacon;
  int victory_condition = 0;
  char b;
  time_t start_time, end_time;
  a = 0;
  b = a;
  time(&start_time);
  if (party_level == 1) {
    column = 9;
    line = column;
    grid = construct_grille(
        line, column,
        party_level);
    // we call the function that generates a 2D array
    do { // allows the display process to be repeated until a win or loss
         // condition is met
      letter = 64;
      // letter line  details
      printf(" "); /*allows the columns to be aligned*/
      for (i = 0; i < 9; i++) {
        letter++;
        couleur("31");
        printf("   %c ", letter); /*displays the letter of the column*/
        couleur("0");
      }
      printf("\n_");
      for (i = 0; i < 9; i++) {
        printf("_____");
      }
      for (i = 0; i < line; i++) {
        couleur("31");
        printf("\n %d", i + 1); /*displays the number of the line*/
        couleur("0");
        for (j = 0; j < column; j++) {
          if (grid[i][j] <= 0) { // condition which allows to hide the not yet
                                 // discovered cells (negative cells)
            printf("| *  ");
          } else {
            if (grid[i][j] == -BOMB) {
              printf("|");
              couleur("33 ");
              printf(" %d ", grid[i][j]);
              couleur("0");
            } else if (grid[i][j] == 1) {
              printf("|");
              couleur("34");
              printf(" %d  ", grid[i][j]);
              couleur("0");
            } else if (grid[i][j] == 2) {
              printf("|");
              couleur("32");
              printf(" %d  ", grid[i][j]);
              couleur("0");
            } else if (grid[i][j] == 9) {
              printf("|    ");
            } else if (grid[i][j] >= 10) { // allows you to display the beacons
              printf("|");
              couleur("31");
              printf(" !  ");
              couleur("0");
            } else {
              printf("|");
              couleur("31");
              printf(" %d  ", grid[i][j]);
              couleur("0");
            }
          }
        }
      }
      printf("\n\n");
      beacon = 3;
      do {
        printf(
            "Do you want to place a beacon? (type 1 for YES and 2 for NO)\n");
        scanf("%d", &beacon);
        clear(stdin);
        if (beacon < 1 || beacon > 2) {
          couleur("33");
          printf("ERROR RESPECT INPUT VALUES ! \n\n");
          couleur("0");
        }
      } while (beacon < 1 || beacon > 2);
      if (beacon == 1) {
        do {
          printf("Enter the line number :\n ");
          scanf("%d", &a);
          clear(stdin);
          printf("Enter the letter of the column :\n ");
          scanf("%c", &b);
          clear(stdin);
          if (a < 1 || a > 9 || b - 65 < 0 || b - 65 > 8) {
            couleur("33");
            printf("ERROR RESPECT INPUT VALUES !\n\n");
            couleur("0");
          }
        } while (a < 1 || a > 9 || b - 65 < 0 || b - 65 > 8);
        if (grid[a - 1][b - 65] >= 10 && grid[a - 1][b - 65] <= 20) {
          grid[a - 1][b - 65] = grid[a - 1][b - 65] - 20;
        } else if (grid[a - 1][b - 65] == 21) {
          grid[a - 1][b - 65] = BOMB;
        } else {
          if (grid[a - 1][b - 65] == BOMB) {
            grid[a - 1][b - 65] = 21;
          } else if (grid[a - 1][b - 65] == -1) {
            grid[a - 1][b - 65] = 19;
          } else if (grid[a - 1][b - 65] == -2) {
            grid[a - 1][b - 65] = 18;
          } else if (grid[a - 1][b - 65] == -3) {
            grid[a - 1][b - 65] = 17;
          } else if (grid[a - 1][b - 65] == -4) {
            grid[a - 1][b - 65] = 16;
          } else if (grid[a - 1][b - 65] == -5) {
            grid[a - 1][b - 65] = 15;
          } else if (grid[a - 1][b - 65] == -6) {
            grid[a - 1][b - 65] = 14;
          } else if (grid[a - 1][b - 65] == -7) {
            grid[a - 1][b - 65] = 13;
          } else if (grid[a - 1][b - 65] == -8) {
            grid[a - 1][b - 65] = 12;
          } else if (grid[a - 1][b - 65] == -9) {
            grid[a - 1][b - 65] = 11;
          }
        }
      }

      // placing a flag does not count as a turn because no new squares are
      // discovered
      if (beacon == 2) {
        do {
          couleur("47;35");
          printf("\nDiscover a new box !");
          couleur("0");
          printf("\nChoose a line number :\n ");
          scanf("%d", &a);
          clear(stdin);
          printf("Choose a column letter :\n ");
          scanf("%c", &b);
          clear(stdin);
          if (a < 1 || a > 9 || b - 65 < 0 || b - 65 > 8) {
            couleur("33");
            printf("ERROR START AGAIN !\n");
            couleur("0");
          }
        } while (a < 1 || a > 9 || b - 65 < 0 || b - 65 > 8);
        if (grid[a - 1][b - 65] != -9 && victory_condition == 0) {
          while (grid[a - 1][b - 65] != -9) {
            grid = construct_grille(line, column, party_level);
          }
        }

        victory_condition += decouvrirRec(grid, a - 1, b - 65, line, counter);
        c = grid[a - 1][b - 65];
        if (grid[a - 1][b - 65] == BOMB) {
          c = -c;
        }
      }
      verification = c;
      if (verification == -BOMB) {
        letter = 64;
        couleur("35;1");
        printf("YOU HAVE LOST!!!\n\n");
        couleur("0");
        printf(" "); /*allows the columns to be aligned*/
        for (i = 0; i < 9; i++) {
          letter++;
          couleur("31");
          printf("   %c ", letter); /*displays the letter of the column*/
          couleur("0");
        }
        printf("\n_");
        for (i = 0; i < 9; i++) {
          printf("_____");
        }

        for (i = 0; i < line; i++) {
          couleur("31");
          printf("\n %d", i + 1); /*displays the number of the line*/
          couleur("0");
          for (j = 0; j < column; j++) {
            if (grid[i][j] < 0) {
              grid[i][j] = grid[i][j] * (-1);
            }
            if (grid[i][j] == -BOMB) {
              printf("|");
              couleur("33");
              printf(" B  ");
              couleur("0");
            } else if (grid[i][j] == 1) {
              printf("|");
              couleur("34");
              printf(" %d  ", grid[i][j]);
              couleur("0");
            } else if (grid[i][j] == 2) {
              printf("|");
              couleur("32");
              printf(" %d  ", grid[i][j]);
              couleur("0");
            } else if (grid[i][j] == 9) {
              printf("|    ");
            } else if (grid[i][j]>=10 && grid[i][j]<=21) {
              printf("|");
              couleur("31");
              printf(" !  ");
              couleur("0");
            } else {
              printf("|");
              couleur("31");
              printf(" %d  ", grid[i][j]);
              couleur("0");
            }
          }
        }
      }
      if (victory_condition == 71) {
        time(&end_time);

  time_t diff = difftime(end_time, start_time);
  struct tm tm_diff = *gmtime(&diff);
        save_best_time(diff);
        couleur("34;1");
  printf("\n\nYour time is : min: %02d sec : %02d ", tm_diff.tm_min,
         tm_diff.tm_sec);
  couleur("0");
        couleur("36;1");
        printf("\nWELL DONE, YOU HAVE WON!!!\n");
        couleur("0");
      }
    } while (verification != -BOMB && victory_condition < 71);
  }

  else {

    /*loop that takes care of displaying the 2D array for an intermediate part*/
    column = 16;
    line = column;
    grid = construct_grille(line, column, party_level);
    // letter line details
    do {
      letter = 64;
      printf("  ");
      for (i = 0; i < 16; i++) {
        letter++;
        couleur("31");
        printf("  %c ", letter); /*displays the letter of the column*/
        couleur("0");
      }
      printf("\n_");
      for (i = 0; i < 16; i++) {
        printf("____");
      }

      for (i = 0; i < 16; i++) {
        if (i < 9) {
          couleur("31");
          printf("\n %d", i + 1); /*displays the number of the line*/
          couleur("0");
          for (j = 0; j < column; j++) {
            if (grid[i][j] <= 0) {
              printf("| * ");
            } else {
              if (grid[i][j] == 1) {
                printf("|");
                couleur("34");
                printf(" %d ", grid[i][j]);
                couleur("0");
              } else if (grid[i][j] == 2) {
                printf("|");
                couleur("32");
                printf(" %d ", grid[i][j]);
                couleur("0");
              } else if (grid[i][j] == 9) {
                printf("|   ");
              } else if (grid[i][j] >= 10) { // allows you to display the
                                             // beacons
                printf("|");
                couleur("31");
                printf(" ! ");
                couleur("0");
              } else {
                printf("|");
                couleur("31");
                printf(" %d ", grid[i][j]);
                couleur("0");
              }
            }
          }
        } else {
          couleur("31");
          printf("\n%d", i + 1); /*displays the number of the line*/
          couleur("0");
          for (j = 0; j < column; j++) {
            if (grid[i][j] <= 0) {
              printf("| * ");
            }

            else {
              if (grid[i][j] == 1) {
                printf("|");
                couleur("34");
                printf(" %d ", grid[i][j]);
                couleur("0");
              } else if (grid[i][j] == 2) {
                printf("|");
                couleur("32");
                printf(" %d ", grid[i][j]);
                couleur("0");
              } else if (grid[i][j] == 9) {
                printf("|   ");
              } else if (grid[i][j] >= 10) { // allows you to display the flags
                printf("|");
                couleur("31");
                printf(" ! ");
                couleur("0");
              } else {
                printf("|");
                couleur("31");
                printf(" %d ", grid[i][j]);
                couleur("0");
              }
            }
          }
        }
      }
      printf("\n\n");
      do {
        printf(
            "Do you want to place a beacon? (type 1 for YES and 2 for NO)\n");
        scanf("%d", &beacon);
        clear(stdin);
        if (beacon < 1 || beacon > 2) {
          couleur("33");
          printf("ERROR TRY AGAIN ! \n\n");
          couleur("0");
        }
      } while (beacon < 1 || beacon > 2);
      if (beacon == 1) {
        do {
          printf("Enter the line number :\n ");
          scanf("%d", &a);
          clear(stdin);
          printf("Enter the letter of the column :\n ");
          scanf("%c", &b);
          clear(stdin);
          if (a < 1 || a > 16 || b < 65 || b > 80) {
            couleur("33");
            printf("ERROR TRY AGAIN ! \n\n");
            couleur("0");
          }
        } while (a < 1 || a > 16 || b < 65 || b > 80);
        if (grid[a - 1][b - 65] >= 10 && grid[a - 1][b - 65] <= 20) {
          grid[a - 1][b - 65] = grid[a - 1][b - 65] - 20;
        } else if (grid[a - 1][b - 65] == 21) {
          grid[a - 1][b - 65] = BOMB;
        } else {
          if (grid[a - 1][b - 65] == BOMB) {
            grid[a - 1][b - 65] = 21;
          } else if (grid[a - 1][b - 65] == -1) {
            grid[a - 1][b - 65] = 19;
          } else if (grid[a - 1][b - 65] == -2) {
            grid[a - 1][b - 65] = 18;
          } else if (grid[a - 1][b - 65] == -3) {
            grid[a - 1][b - 65] = 17;
          } else if (grid[a - 1][b - 65] == -4) {
            grid[a - 1][b - 65] = 16;
          } else if (grid[a - 1][b - 65] == -5) {
            grid[a - 1][b - 65] = 15;
          } else if (grid[a - 1][b - 65] == -6) {
            grid[a - 1][b - 65] = 14;
          } else if (grid[a - 1][b - 65] == -7) {
            grid[a - 1][b - 65] = 13;
          } else if (grid[a - 1][b - 65] == -8) {
            grid[a - 1][b - 65] = 12;
          } else if (grid[a - 1][b - 65] == -9) {
            grid[a - 1][b - 65] = 11;
          }
        }
        victory_condition--;
      }

      if (beacon == 2) {
        do {
          couleur("47;35");
          printf("\nDiscover a new box !");
          couleur("0");
          printf("\nEnter the line number :\n ");
          scanf("%d", &a);
          clear(stdin);
          printf("Enter the letter of the column :\n ");
          scanf("%c", &b);
          clear(stdin);
          if (a < 0 || a > 16 || b - 65 < 0 || b - 65 > 16) {
            couleur("33");
            printf("ERROR TRY AGAIN ! \n\n");
            couleur("0");
          }
        } while (a < 1 || a - 1 > 15 || b - 65 < 0 || b - 65 > 15);
        if (grid[a - 1][b - 65] != -9 && victory_condition == 0) {
          while (grid[a - 1][b - 65] != -9) {
            grid = construct_grille(line, column, party_level);
          }
        }
        
        victory_condition += decouvrirRec(grid, a - 1, b - 65, line, counter);
        c = grid[a - 1][b - 65];
        if (grid[a - 1][b - 65] == BOMB) {
          c = -c;
        }

        // printf("the value of %d; %d is : %d\n", a, b, grid[a][b]);
      }
      verification = c;
      if (verification == -BOMB) {
        letter = 64;
        couleur("35;1");
        printf("YOU HAVE LOST!!!\n\n");
        couleur("0");
        printf(" ");
        for (i = 0; i < 16; i++) {
          letter++;
          couleur("31");
          printf("   %c ", letter); /*displays the letter of the column*/
          couleur("0");
        }
        printf("\n_");
        for (i = 0; i < 16; i++) {
          printf("_____");
        }
        for (i = 0; i < 16; i++) {
          if (i < 9) {
            couleur("31");
            printf("\n %d", i + 1); /*displays the line number*/
            couleur("0");
            for (j = 0; j < column; j++) {
              if (grid[i][j] < 0) {
                grid[i][j] = grid[i][j] * (-1);
              }
              if (grid[i][j] == -BOMB) {
                printf("|");
                couleur("33");
                printf(" B  ");
                couleur("0");
              } else if (grid[i][j] == 1) {
                printf("|");
                couleur("34");
                printf(" %d  ", grid[i][j]);
                couleur("0");
              } else if (grid[i][j] == 2) {
                printf("|");
                couleur("32");
                printf(" %d  ", grid[i][j]);
                couleur("0");
              } else if (grid[i][j] == 9) {
                printf("|    ");
              } else if (grid[i][j]>=10 && grid[i][j]<=21){
                printf("|");
                couleur("31");
                printf(" !  ");
                couleur("0");
              } else {
                printf("|");
                couleur("31");
                printf(" %d  ", grid[i][j]);
                couleur("0");
              }
            }
          } else {
            couleur("31");
            printf("\n%d", i + 1); /*displays the number of the line*/
            couleur("0");
            for (j = 0; j < column; j++) {
              if (grid[i][j] < 0) {
                grid[i][j] = grid[i][j] * (-1);
              }
              if (grid[i][j] == -BOMB) {
                printf("|");
                couleur("33");
                printf(" B  ", grid[i][j]);
                couleur("0");
              } else if (grid[i][j] == 1) {
                printf("|");
                couleur("34");
                printf(" %d  ", grid[i][j]);
                couleur("0");
              } else if (grid[i][j] == 2) {
                printf("|");
                couleur("32");
                printf(" %d  ", grid[i][j]);
                couleur("0");
              } else if (grid[i][j] == 9) {
                printf("|    ");
              } else if (grid[i][j]>=10 && grid[i][j]<=21) {
                printf("|");
                couleur("31");
                printf(" !  ");
                couleur("0");
              }

              else {
                printf("|");
                couleur("31");
                printf(" %d  ", grid[i][j]);
                couleur("0");
              }
            }
          }
        }
      }
      if (victory_condition ==216 ) {
        time(&end_time);

  time_t diff = difftime(end_time, start_time);
  struct tm tm_diff = *gmtime(&diff);
        save_best_time(diff);
        couleur("34;1");
  printf("\n\nYour time is : min: %02d sec : %02d ", tm_diff.tm_min,
         tm_diff.tm_sec);
  couleur("0");
        couleur("36;1");
        printf("\nCONGRATULATIONS, YOU HAVE WON!!!\n");
        couleur("0");
      }
    } while (verification != -BOMB && victory_condition < 216);
  }
}

int main() {
FILE *fFile;
  fFile = fopen("C:\\Dorian\\info\\stockage.txt", "w");


  
  /*declaration of the different variables*/
  int party_level, choice2;
  char pseudo[50], lettre = 64; /*table ascii*/
  char pseudo_record[50];
  int **grid = NULL;
  int column, line, i, j;
  //long timer1, timer2, time1;
  //time_t start_time, end_time;
  double temp_saved=0;
  //double chrono;

  srand(time(NULL));
  couleur("31;1");
  printf("_____________________________\n|");
  couleur("34;1");
  printf(" Welcome to the Démineur   ");
  couleur("31;1");
  printf("|\n|___________________________|\n\n");
  couleur("0");
  printf("Choose a pseudo :) \n");
  scanf("%s", pseudo);
  /*loop that asks you to choose between the two levels until either 1 or 2 is
   * set*/
  do {
    printf("\nDo you want to see the rules of the games ?\n(Type 1 for YES "
           "and 2 for NO)\n");
    scanf("%d", &choice2);
    clear(stdin);
    if (choice2 < 1 || choice2 > 2) {
      couleur("33");
      printf("ERROR TRY AGAIN");
      couleur("0");
    }
  } while (choice2 < 1 || choice2 > 2);
  if (choice2 == 1) {
    regle();
  }

  do {
    couleur("34");
    printf("\n%s, please choose a level: type 1 for beginner or 2 for"
           " intermediate\n",
           pseudo);
    couleur("0");
    scanf("%d", &party_level);
    clear(stdin);
  }

  while(party_level != 1 && party_level != 2);
  
  
  affiche_grille(party_level, grid);

  return 0;
}

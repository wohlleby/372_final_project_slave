#include "drinks.h"
#include <string.h>
#include <stdlib.h>

using namespace std;


int** initDrinks() {

   int** drinkList = (int **)malloc(20 * sizeof(int));

  for(int i = 0; i < 20; i++) {
     drinkList[i] = (int*)malloc(20 * sizeof(int));
  }

  //mango pinapple cranbery apple water

  //prime/purge
  drinkList[0][0] = 2;drinkList[0][1] = 2;drinkList[0][2] = 2;drinkList[0][3] = 2;drinkList[0][4] = 2;
  //run pump1
  drinkList[1][0] = 6;drinkList[1][1] = 0;drinkList[1][2] = 0;drinkList[1][3] = 0;drinkList[1][4] = 0;
  //run pump2
  drinkList[2][0] = 0;drinkList[2][1] = 6;drinkList[2][2] = 0;drinkList[2][3] = 0;drinkList[2][4] = 0;
  //run pump3
  drinkList[3][0] = 0;drinkList[3][1] = 0;drinkList[3][2] = 6;drinkList[3][3] = 0;drinkList[3][4] = 0;
  //run pump4
  drinkList[4][0] = 0;drinkList[4][1] = 0;drinkList[4][2] = 0;drinkList[4][3] = 6;drinkList[4][4] = 0;
  //run pump5
  drinkList[5][0] = 0;drinkList[5][1] = 0;drinkList[5][2] = 0;drinkList[5][3] = 0;drinkList[5][4] = 6;
  //run 3 and 4, mango pineapple
  drinkList[6][0] = 2;drinkList[6][1] = 4;drinkList[6][2] = 0;drinkList[6][3] = 0;drinkList[6][4] = 0;
  //run 4 and 5, sparkling apple
  drinkList[7][0] = 0;drinkList[7][1] = 0;drinkList[7][2] = 0;drinkList[7][3] = 4;drinkList[7][4] = 4;
  //cran apple, 3 and 4
  drinkList[8][0] = 0;drinkList[8][1] = 0;drinkList[8][2] = 4;drinkList[8][3] = 4;drinkList[8][4] = 0;
  //Everything
  drinkList[9][0] = 2;drinkList[9][1] = 2;drinkList[9][2] = 2;drinkList[9][3] = 2;drinkList[9][4] = 1;

  return drinkList;
}

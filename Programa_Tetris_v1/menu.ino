
#include <Arduino.h>
#include "biblioteca.h"
#include "menu.h"

byte posicao_cursor = 0;

// sprites 5x6
byte sprite_T[5][5] = {
  {1,1,1,1,1},
  {0,0,1,0,0},
  {0,0,1,0,0},
  {0,0,1,0,0},
  {0,0,1,0,0}
};

byte sprite_B[5][5] = {
  {1,0,0,0,1},
  {0,1,0,1,0},
  {0,0,1,0,0},
  {0,1,0,1,0},
  {1,0,0,0,1}
};

byte sprite_S[5][5] = {
  {1,1,1,0,1},
  {1,0,0,0,0},
  {1,1,1,1,0},
  {0,0,0,1,0},
  {1,1,1,1,0}
};


byte seta[3][4] = {
  {0,0,1,0},
  {1,1,1,1},
  {0,0,1,0}
};

void main_menu(){ 

    if(button_press[down]==true){
      button_press[down]=false;
      posicao_cursor++;
      if(posicao_cursor == 3){
        posicao_cursor = 2;
      }
    }

    if(button_press[up]==true){
      button_press[up]=false;
      posicao_cursor--;
      if(posicao_cursor == 255){
        posicao_cursor = 0;
      }
    }

    if(button_press[enter]==true){
      button_press[enter]=false;
      if(posicao_cursor == 0){
        estado_atual = estado_tetris;
      }else if(posicao_cursor == 1){
        estado_atual = estado_efeito;
      }else if(posicao_cursor == 2){
        //
      }
    }

  desenhaMenu();

}

void desenhaMenu() {

  limpa_matrix();

  // desenha sprite T
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      if (sprite_T[i][j])
        matrix[i+1][j+5] = 1;

  // desenha sprite B
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      if (sprite_B[i][j])
        matrix[i+7][j+5] = 1;

  // desenha sprite S
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      if (sprite_S[i][j])
        matrix[i+13][j+5] = 1;

  // desenha cursor
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      if (seta[i][j] == 1){
        matrix[posicao_cursor * 6 + 2 + i][j] = 1;
      }                  
    }
  }

}
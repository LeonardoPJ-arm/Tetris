
#include <Arduino.h>
#include "biblioteca.h"
#include "snake.h"

//extern byte matrix[18][10];

#define MAX_SNAKE 180     // 10×18 = 180 células
#define UP    0
#define DOWN  1
#define LEFT  2
#define RIGHT 3

byte snake_x[MAX_SNAKE];
byte snake_y[MAX_SNAKE];
byte direcao = RIGHT;
byte snake_len = 3;
byte food_x, food_y;
int relogio = 0;

void  main_snake(){

  static bool iniciado  = true;
  if (iniciado) {
    snake_x[0] = 5; snake_y[0] = 9;  // cabeça
    snake_x[1] = 4; snake_y[1] = 9;
    snake_x[2] = 3; snake_y[2] = 9;
    snake_len = 3;
    food_x = random(0, 10);
    food_y = random(0, 18);
    relogio = 49;

    limpa_matrix();
    iniciado  = false;
  }

  relogio++;
  if (relogio >= 30) {            // 600ms 
    relogio = 0;

    // move o corpo
    for (int i = snake_len - 1; i > 0; i--) {
      snake_x[i] = snake_x[i - 1];
      snake_y[i] = snake_y[i - 1];
    }
    // move a cabeça
    if (direcao == UP)    snake_y[0]--;
    if (direcao == DOWN)  snake_y[0]++;
    if (direcao == LEFT)  snake_x[0]--;
    if (direcao == RIGHT) snake_x[0]++;

    // quando a cobra come
    if (snake_x[0] == food_x && snake_y[0] == food_y) {
      // aumenta o corpo
      snake_x[snake_len] = snake_x[snake_len - 1];
      snake_y[snake_len] = snake_y[snake_len - 1];
      snake_len++;
      // gera a comida
      food_x = random(0, 10);
      food_y = random(0, 18);
    }

    // colisão com parede
    if (snake_x[0] >= 10 || snake_y[0] >= 18) {
      snake_x[0] = 5; snake_y[0] = 9; 
      snake_x[1] = 4; snake_y[1] = 9;
      snake_x[2] = 3; snake_y[2] = 9;
      snake_len = 3;
      direcao = RIGHT;
      food_x = random(0, 10);
      food_y = random(0, 18);
    }

    // colisão com o próprio corpo
    for (int i = 1; i < snake_len; i++) {
      if (snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i]) {
        snake_x[0] = 5; snake_y[0] = 9;  // cabeça
        snake_x[1] = 4; snake_y[1] = 9;
        snake_x[2] = 3; snake_y[2] = 9;
        snake_len = 3;
        direcao = RIGHT;
        food_x = random(0, 10);
        food_y = random(0, 18);
      }
    }

    limpa_matrix();
    // desenha comida
    matrix[food_y][food_x] = 1;
    // desenha cobra
    for (int i = 0; i < snake_len; i++) {
      matrix[snake_y[i]][snake_x[i]] = 1;
    }

  }

  // le os botoes (evita se sobrepor)
  if (button_press[up]) {
    button_press[up] = false;
    if (direcao != DOWN) direcao = UP;
  }
  else if (button_press[down]) {
    button_press[down] = false;
    if (direcao != UP) direcao = DOWN;
  }
  else if (button_press[left]) {
    button_press[left] = false;
    if (direcao != RIGHT) direcao = LEFT;
  }
  else if (button_press[right]) {
    button_press[right] = false;
    if (direcao != LEFT) direcao = RIGHT;
  }

  // retorna ao menu
  if(button_press[back]==true){
    button_press[back]=false;
    limpa_matrix();
    iniciado  = true;
    estado_atual = estado_menu;      // return
    return;
  }

  // Piscar a cabeça
  if (relogio % 4 == 0) {
    matrix[snake_y[0]][snake_x[0]] = 0;
  }
  if (relogio % 8 == 0) {
    matrix[snake_y[0]][snake_x[0]] = 1;
  }

}
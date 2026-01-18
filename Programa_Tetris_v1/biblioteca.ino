#include <Arduino.h>
#include "biblioteca.h"

enum estado_programa estado_atual = estado_menu;

volatile unsigned long relogio_20ms = 0;    

bool flag_tocar_musica = false;

byte matrix[18][10] = {
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 0
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 1
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 2
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 3
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 4
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 5
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 6
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 7
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 8
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 9
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 10
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 11
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 12
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 13
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 14
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 15
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 16
  {0,0,0,0,0,0,0,0,0,0}   // Coluna 17
};

byte vector[48] = {
  0,0,0,0,0,0,0,0,0,0,                      // Linha 10
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,      // Coluna 18
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0   //
};

byte button_press[6] = {0,0,0,0,0,0};

byte button_hold[6] = {0,0,0,0,0,0};

void init_hardware(){
  pinMode(sr_enable_pin, OUTPUT);
  pinMode(sr_clock_pin, OUTPUT);
  pinMode(sr_latch_pin, OUTPUT);
  pinMode(sr_data_pin, OUTPUT);
  pinMode(sr_reset_pin, OUTPUT);

  digitalWrite(sr_enable_pin, HIGH);        // Disable display 
  digitalWrite(sr_reset_pin, LOW);          // Reset
  digitalWrite(sr_latch_pin, LOW);
  digitalWrite(sr_latch_pin, HIGH);         // Clock latch
  digitalWrite(sr_reset_pin, HIGH);

  pinMode(debug_2_int_pin, OUTPUT);
  pinMode(debug_3_loop_pin, OUTPUT);
  pinMode(debug_4_display_pin, OUTPUT);
  pinMode(led_pin, OUTPUT);
  randomSeed(analogRead(A6));

  pinMode(button_right_pin, INPUT);
  pinMode(button_left_pin, INPUT);
  pinMode(button_down_pin, INPUT);
  pinMode(button_up_pin, INPUT);
  pinMode(button_enter_pin, INPUT);
  pinMode(button_back_pin, INPUT);

}

void limpa_matrix(){
    for (int col = 0; col < 18; col++) {          // limpa a matriz
      for (int lin = 0; lin < 10; lin++) {
        matrix[col][lin] = 0;
      } 
    }
}


/*

byte matrix[18][10] = {
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 0
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 1
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 2
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 3
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 4
  {0,0,1,0,0,0,0,1,0,0},  // Coluna 5
  {0,0,0,1,1,1,1,0,0,0},  // Coluna 6
  {0,0,1,1,1,1,1,1,0,0},  // Coluna 7
  {0,1,1,0,1,1,0,1,1,0},  // Coluna 8
  {0,1,1,1,1,1,1,1,1,0},  // Coluna 9
  {0,0,1,1,0,0,1,1,0,0},  // Coluna 10
  {0,1,0,1,0,0,1,0,1,0},  // Coluna 11
  {0,1,0,0,0,0,0,0,1,0},  // Coluna 12
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 13
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 14
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 15
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 16
  {0,0,0,0,0,0,0,0,0,0}   // Coluna 17
};


byte matrix[18][10] = {
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 0
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 1
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 2
  {0,0,0,1,0,1,0,0,0,0},  // Coluna 3
  {1,0,1,1,1,1,1,0,1,0},  // Coluna 4
  {0,1,1,1,1,1,1,1,0,0},  // Coluna 5
  {0,1,1,0,1,0,1,1,0,0},  // Coluna 6
  {1,1,1,1,1,1,1,1,1,0},  // Coluna 7
  {0,1,1,0,0,0,1,1,0,0},  // Coluna 8
  {0,1,1,1,0,0,1,1,0,0},  // Coluna 9
  {0,0,1,1,1,1,1,0,0,0},  // Coluna 10
  {0,0,0,1,1,1,0,0,0,1},  // Coluna 11
  {0,0,0,1,1,1,1,0,1,0},  // Coluna 12
  {0,0,0,0,1,1,1,1,1,0},  // Coluna 13
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 14
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 15
  {0,0,0,0,0,0,0,0,0,0},  // Coluna 16
  {0,0,0,0,0,0,0,0,0,0}   // Coluna 17
};

byte matrix[18][10] = {
  {1,1,1,1,1,1,1,1,1,1},  // Coluna 0
  {1,0,0,0,0,0,0,0,0,0},  // Coluna 1
  {1,0,0,0,0,0,0,0,0,0},  // Coluna 2
  {1,0,0,0,0,0,0,0,0,0},  // Coluna 3
  {1,0,0,0,0,0,0,0,0,0},  // Coluna 4
  {1,0,0,0,0,0,0,0,0,0},  // Coluna 5
  {1,0,0,0,0,0,0,0,0,0},  // Coluna 6
  {1,0,0,0,0,0,0,0,0,0},  // Coluna 7
  {1,0,0,0,0,0,0,0,0,0},  // Coluna 8
  {1,0,0,0,0,0,0,0,0,0},  // Coluna 9
  {1,0,0,0,0,0,0,0,0,0},  // Coluna 10
  {1,0,0,0,0,0,0,0,0,0},  // Coluna 11
  {1,0,0,0,0,0,0,0,0,0},  // Coluna 12
  {1,0,0,0,0,0,0,0,0,0},  // Coluna 13
  {1,0,0,0,0,0,0,0,0,0},  // Coluna 14
  {1,0,0,0,0,0,0,0,0,0},  // Coluna 15
  {1,0,0,0,0,0,0,0,0,0},  // Coluna 16
  {1,0,0,0,0,0,0,0,0,0}   // Coluna 17
};

*/





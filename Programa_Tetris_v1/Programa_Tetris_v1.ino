
// Board: Arduino Nano
// Processor: ATmega328P (old bootloader)

#include "interrupcao.h"
#include "musica.h"
#include "display.h"
#include "input.h"
#include "tetris.h"
#include "biblioteca.h"

#define DEBUG

volatile unsigned long relogio_20ms_anterior = 0;

void setup() {
  
  init_hardware();
  init_interrupcao();                  // Interrupção

  Serial.begin(115200);
  Serial.println("Hello Tetris");
 
}

void loop() {       // manipular a matrix e botões, não usar delay e deixar modular para usar outros jogos
  
  #ifdef DEBUG
    digitalWrite(debug_3_loop_pin, HIGH);
  #endif

  if (relogio_20ms != relogio_20ms_anterior) {         // 20ms / 50 Hz
    relogio_20ms_anterior = relogio_20ms;  

    switch (estado_atual) {
      case estado_menu:
        main_menu();
        break;

      case estado_tetris:
        main_tetris();
        break;

      case estado_efeito:
        efeitoBrowniano();
        break;

      case estado_snake:
        main_snake();
        break;
    }
  }

  #ifdef DEBUG
    digitalWrite(debug_3_loop_pin, LOW);
  #endif
  
}

void efeitoBrowniano(){
  static bool iniciado  = true;
  if (iniciado) {
    Serial.println("efeitoBrowniano");
    limpa_matrix();
    iniciado  = false;
  }
  
  if(button_press[back]==true){
    button_press[back]=false;
    limpa_matrix();
    iniciado  = true;
    estado_atual = estado_menu;      // return
    return;
  }

  byte col = random(0, 18);  // coluna (0 a 17)
  byte lin = random(0, 10);  // linha  (0 a 9)
  matrix[col][lin] = 1;
  col = random(0, 18);  // coluna (0 a 17)
  lin = random(0, 10);  // linha  (0 a 9)
  matrix[col][lin] = 0;     
  
  if(button_hold[up]==true){
    col = random(0, 18);  // coluna (0 a 17)
    lin = random(0, 10);  // linha  (0 a 9)
    matrix[col][lin] = 1;
  }

  if(button_hold[down]==true){
    col = random(0, 18);  // coluna (0 a 17)
    lin = random(0, 10);  // linha  (0 a 9)
    matrix[col][lin] = 0;
  }

  
}




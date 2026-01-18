/*
  2us por bit. 
  100 us para enviar 48 bits, 
  20 ms para enviar e acender 200 leds.
  O tempo do led acesso é o tempo de enviar os bits para 595. 
  50hz de taxa de atualização do display
*/

// Timer2 a 20 ms → refresh do display 10×18 via 74HC595

#include <Arduino.h>
#include "biblioteca.h"

byte counter = 0;

void atualizar_display() {

  //Serial.println("atualizando display ");

  if (counter == 1){              // Blink LED (100ms)
    //digitalWrite(led_pin, HIGH);
    PORTD |=  (1 << PB5);      // led_pin 13 HIGH
  }else if (counter == 6){
    //digitalWrite(led_pin, LOW);
    PORTD &= ~(1 << PB5);      // led_pin 13 LOW
  }else if (counter == 11){
      counter = 0;
  }
  counter++;
  
  matrix_to_vector();
  
}


void matrix_to_vector(){

    for (int col = 0; col < 18; col++) {      // varre a matrix
      for (int lin = 0; lin < 10; lin++) {

        if (matrix[col][lin] == 1) {          // Se for 1
        
          for (int i = 0; i < 28; i++) {        // Reinicia o vetor de saida
            if (i < 10) {
              vector[i] = 0;          // 10 primeiros -> zeros (linhas)
            } else {
              vector[i] = 1;          // próximos 18 -> uns (colunas)
            }
          }
          
          vector[lin] = 1;               // seta bit da linha correspondente (linha (0–9))
          vector[10 + col] = 0;          // seta bit da coluna correspondente (coluna (10–27))
        
          vector_to_shift_register();     // Envia ao shift register
          
        }
      }
    }
    
    // Desabilita a saida
    PORTD |= (1 << PD3);   // sr_enable_pin HIGH
}

void vector_to_shift_register() {
    // Habilita saída (sr_enable LOW)
    PORTD &= ~(1 << PD3);   // sr_enable_pin LOW

    // Inicializa clock e latch em LOW
    PORTD &= ~(1 << PD5);   // sr_clock_pin LOW
    PORTD &= ~(1 << PD4);   // sr_latch_pin LOW

    // Envia os 48 bits do vetor
    for (int i = 47; i >= 0; i--) {
        if (vector[i]) {
            PORTD |=  (1 << PD2);  // sr_data_pin HIGH
        } else {
            PORTD &= ~(1 << PD2);  // sr_data_pin LOW
        }

        // Pulso de clock
        PORTD |=  (1 << PD5);      // sr_clock_pin HIGH
        PORTD &= ~(1 << PD5);      // sr_clock_pin LOW
    }

    // Pulso de latch para atualizar saída
    PORTD |=  (1 << PD4);   // sr_latch_pin HIGH
    PORTD &= ~(1 << PD4);   // sr_latch_pin LOW

    // Mantém saída habilitada
    PORTD &= ~(1 << PD3);   // sr_enable_pin LOW
}











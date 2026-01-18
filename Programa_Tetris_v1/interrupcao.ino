

#include <Arduino.h>

#include "interrupcao.h"
#include "musica.h"
#include "display.h"
#include "biblioteca.h"

ISR(TIMER0_COMPA_vect) {      // Timer 0
  noInterrupts();
  #ifdef DEBUG
    //digitalWrite(debug_2_int_pin, HIGH);
    PORTD |=  (1 << PD7);   // debug_2_int_pin HIGH
  #endif
  
  atualizar_display();

  if(flag_tocar_musica == true){
    atualizar_musica();
  }else{
    noTone(buzzer_pin);
  }

  debounce_botoes();
  
  relogio_20ms++;
  
  // Verficar botão precionado, ativa uma flag se o botao ficar alguns ciclos

  #ifdef DEBUG
    //digitalWrite(debug_2_int_pin, LOW);
    PORTD &= ~(1 << PD7);   // debug_2_int_pin LOW
  #endif
  
  interrupts(); 
} 


#define BUTTON_MASK 0b00111111    // PC0..PC5 -> A0..A5

ISR(PCINT1_vect) {      // Botões

  noInterrupts();
  
  leitura_botao();

  interrupts(); 

}
 
void init_interrupcao() {

  noInterrupts();           // desabilita interrupções globais
  // Interrupção do Timer0
  TCCR0A = 0;               // modo normal
  TCCR0B = 0;
  TCCR0B |= (1 << WGM12);   // Timer em modo CTC
  TCCR0B |= (1 << CS12) | (1 << CS10);    // Prescaler 1024 → cada "tick" = 64 us
  OCR0A =311;                             // 20 ms / 64 us = 311 = 20ms (validado no osciloscopio)
  TIMSK0 |= (1 << OCIE0A);                // Habilita interrupção por comparação

  // Interrupção dos Botões
  DDRC &= ~BUTTON_MASK;   // define A0..A5 como entrada
  PORTC &= ~BUTTON_MASK;   // sem pull-up (usando pull-down externo)
  PCICR |= (1 << PCIE1);        // habilita interrupções de mudança na porta C
  PCMSK1 |= BUTTON_MASK;      

  interrupts();             // habilita interrupções globais
}

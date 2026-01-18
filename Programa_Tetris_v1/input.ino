/*
Button_press
Button_hold

000001 back   A0
000010 enter
  A1
000100 up     A2
001000 down   A3
010000 left   A4
100000 right  A5

*/

#include <Arduino.h>
#include "tetris.h"

#define BUTTON_MASK 0b00111111    // PC0..PC5 -> A0..A5

#define HOLD_TICKS 50   // 50 x 20ms = 1 segundo
#define DEBOUNCE_TICKS 5
byte debounce_cnt[6];
byte leitura;
byte stable_state = 0;  
byte hold_cnt[6];


void leitura_botao(){
  leitura = PINC & BUTTON_MASK;     // Leitura da porta C
}

void debounce_botoes() {

  for (int i = 0; i < 6; i++) {

    bool raw    = leitura & (1 << i);
    bool stable = stable_state & (1 << i);

    /* ---------- DEBOUNCE ---------- */
    if (raw != stable) {
      debounce_cnt[i]++;

      if (debounce_cnt[i] >= DEBOUNCE_TICKS) {
        debounce_cnt[i] = 0;

        if (raw) {
          stable_state |= (1 << i);
          button_press[i] = true;          // evento PRESS
        } else {
          stable_state &= ~(1 << i);
          hold_cnt[i] = 0;                // soltou → zera hold
          button_hold[i] = false;
        }
      }
    } else {
      debounce_cnt[i] = 0;
    }

    /* ---------- HOLD ---------- */
    if (stable_state & (1 << i)) {        // botão pressionado estável
      if (hold_cnt[i] < HOLD_TICKS) {
        hold_cnt[i]++;
        if (hold_cnt[i] == HOLD_TICKS) {
          button_hold[i] = true;          // evento HOLD
        }
      }
    }
  }
}



/*
mudou?
 ├─ não → ignora
 └─ sim
    ├─ ainda pressionado?
    │    ├─ conta tempo
    │    └─ tempo suficiente → evento
    └─ soltou antes → zera contador
*/
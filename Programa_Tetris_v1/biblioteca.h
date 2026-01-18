#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#define sound_pin 11
#define buzzer_pin 9    // Pino do buzzer
#define pin 12  

#define sr_data_pin 2
#define sr_enable_pin 3
#define sr_latch_pin 4
#define sr_clock_pin 5
#define sr_reset_pin 6

#define random_pin A6
#define button_right_pin A5
#define button_left_pin A4
#define button_down_pin A3
#define button_up_pin A2
#define button_enter_pin A1
#define button_back_pin A0

#define led_pin 13                  // LED arduino
#define debug_1_latch_pin 4
#define debug_2_int_pin 7
#define debug_3_loop_pin 8
#define debug_4_display_pin 10

#define ROW 18 
#define COL 10

#define back 0
#define enter 1
#define up 2
#define down 3
#define left 4
#define right 5

extern byte matrix[18][10];

extern byte vector[48];

enum estado_programa {
  estado_menu,
  estado_tetris,
  estado_efeito,
  estado_snake
};

extern enum estado_programa estado_atual;


extern byte button_press[6];

extern byte button_hold[6];

extern volatile unsigned long relogio_20ms;    // 32bits

extern bool flag_tocar_musica;

void init_hardware();

void limpa_matrix();

#endif


#include <Arduino.h>
#include "tetris.h"
#include "biblioteca.h"

int bloco_x = 9;   // coluna
int bloco_y = 4;   // linha superior do bloco

byte matrix_tetris[18][10];         // matriz auxiliar, salva os itens solidos 
byte indice_peca = 0;
int8_t posy = 0;       
int8_t posx = 3;
int pontos = 0;
bool descer_peca = false;
int relogio_1hz = 0;

void main_tetris(){

  static byte (*pecas[7])[4] = {
    peca_linha, peca_bloco, peca_tetra,
    peca_s, peca_z, peca_j, peca_l
  };

  static byte (*peca_escolhida)[4];

  static bool iniciado = true;

  if (iniciado) {
    Serial.println("main Tetris");
    limpa_matrix();
    flag_tocar_musica = true;

    // Escolhe uma peça aleatoria
    indice_peca = 0;
    posy = 0;       
    posx = 3;
    indice_peca = random(0, 7);
    peca_escolhida = pecas[indice_peca];
    // Insere a peça na matrix
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (peca_escolhida[i][j] == 1) {
          matrix[posy + i][posx + j] = 1;
        }
      }
    }
    iniciado = false;
  }

    relogio_1hz++;
    if (relogio_1hz == 50 || descer_peca==true) {            // 1000ms / 1 Hz
      relogio_1hz = 0;
      descer_peca = false;
      //Serial.println(relogio_1hz);
      
      bool bateu = false;
      bool perdeu = false;
      
    // Verifica a colisao
      for (int i = 3; i >= 0; i--) {        // detecta colisão
        for (int j = 0; j < 4; j++) {
          if (peca_escolhida[i][j] == 1) {
            int y_next = posy + i + 1;
            int x_next = posx + j;
            if (y_next >= 18 || matrix_tetris[y_next][x_next] == 1) {
              bateu = true;
              if(posy==0){      // colisao na posiçao inicial
                perdeu = true;
                bateu = false;
              }
            }

          }
        }
      }
    
    // Fim de jogo
      if(perdeu == true){
        for (int col = 0; col < 18; col++) {          // limpa a matriz auxiliar, reinicia o jogo
          for (int lin = 0; lin < 10; lin++) {
            matrix_tetris[col][lin] = 0;
          } 
        }
        
      // Gera nova peça
        posy = 0;         
        posx = 3;
        indice_peca = random(0, 7);
        peca_escolhida = pecas[indice_peca];

      }

    // Colisao
      if(bateu == true){                   

        for (int i = 0; i < 4; i++) {
          for (int j = 0; j < 4; j++) {
            if (peca_escolhida[i][j] == 1) {
              matrix_tetris[posy + i][posx + j] = 1;        // Guarda a peça na matrix_tetris (aux)
            }
          }
        }

        // Gera nova peça
        posy = 0;         
        posx = 3;
        indice_peca = random(0, 7);
        peca_escolhida = pecas[indice_peca];

      }else{
        posy++;
      }


    // Verifica se alguma linha está preenchida
      for (int i = 17; i >= 0; i--) {
        bool linha_cheia = true;
        for (int j = 0; j < 10; j++) {
          if (matrix_tetris[i][j] == 0) {
            linha_cheia = false;
            break;
          }
        }
        if (linha_cheia) { // desce tudo uma linha
          pontos++;
          Serial.println(pontos);
          for (int k = i; k > 0; k--){
            memcpy(matrix_tetris[k], matrix_tetris[k - 1], 10);
          }
          memset(matrix_tetris[0], 0, 10);
          i++; // reavalia mesma linha
        }
      }

    }

    //if (relogio_20ms != relogio_20ms_anterior) {         // 20ms / 50 Hz
    //  relogio_20ms_anterior = relogio_20ms;  

    // Desce peça
      if(button_press[down]==true){
        button_press[down]=false;
        descer_peca = true;
      }

    // Musica (on/off)
        if(button_press[enter]==true){
          button_press[enter]=false;
          if(flag_tocar_musica == true){
            flag_tocar_musica = false;
          }else if(flag_tocar_musica == false){
            flag_tocar_musica = true;
          }
        }

    // Esquerda
      if(button_press[left]==true){
        button_press[left]=false;
        
        bool bateu_esq = false;
        for (int i = 0; i < 4; i++) {
          for (int j = 0; j < 4; j++) {
            if (peca_escolhida[i][j] == 1) {
              int y_next = posy + i;
              int x_next = posx + j - 1;
              if (x_next < 0 || matrix_tetris[y_next][x_next] == 1) {
                bateu_esq = true;
              }
            }
          }
        }
        if(bateu_esq == true){
          
        }else{
          posx--;
        }
       
      }

    // Direita
      if(button_press[right]==true){
        button_press[right]=false;
        bool bateu_dir = false;
        for (int i = 0; i < 4; i++) {
          for (int j = 3; j >= 0; j--) {
            if (peca_escolhida[i][j] == 1) {
              int y_next = posy + i;
              int x_next = posx + j + 1;
              if (x_next >= 10 || matrix_tetris[y_next][x_next] == 1) {
                bateu_dir = true;
              }
            }
          }
        }
        if(bateu_dir == true){

        }else{
          posx++;
        }
        
      }

    // Rotaciona
      if(button_press[up]==true){      
        button_press[up]=false;
        
        byte rotacionada[4][4];
        for (int i = 0; i < 4; i++) {
          for (int j = 0; j < 4; j++) {
            rotacionada[j][3 - i] = peca_escolhida[i][j];
          }
        }
        memcpy(peca_escolhida, rotacionada, 16);

      }  

    // Volta pro menu
      if(button_press[back]==true){
        button_press[back]=false;
        limpa_matrix();
        flag_tocar_musica = false;
        // limpar matrix_tetris ou manter jogo salvo se sair 
        //loop();
        iniciado = true;
        estado_atual = estado_menu ; //return
        return;
      }

    // Atualiza a matrix do display, inserindo as peças fixas e a peça caindo
      limpa_matrix();
      for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 10; j++) {
          matrix[i][j] = matrix_tetris[i][j]; // base fixa
        }
      }
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
          if (peca_escolhida[i][j] == 1)
            matrix[posy + i][posx + j] = 1;      // adiciona peça atual
        }
      }
      
    //}
  
}
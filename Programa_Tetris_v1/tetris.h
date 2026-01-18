#ifndef TETRIS_H
#define TETRIS_H

void main_tetris();

const byte peca_linha[4][4] = {
  {0, 0, 0, 0},
  {1, 1, 1, 1},
  {0, 0, 0, 0},
  {0, 0, 0, 0}
};

const byte peca_bloco[4][4] = {
  {0, 0, 0, 0},
  {0, 1, 1, 0},
  {0, 1, 1, 0},
  {0, 0, 0, 0}
};

const byte peca_tetra[4][4] = {
  {0, 0, 0, 0},
  {0, 1, 0, 0},
  {1, 1, 1, 0},
  {0, 0, 0, 0}
};

const byte peca_s[4][4] = {
  {0, 0, 0, 0},
  {0, 1, 1, 0},
  {1, 1, 0, 0},
  {0, 0, 0, 0}
};

const byte peca_z[4][4] = {
  {0, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 0, 0}
};

const byte peca_j[4][4] = {
  {0, 0, 0, 0},
  {1, 0, 0, 0},
  {1, 1, 1, 0},
  {0, 0, 0, 0}
};

const byte peca_l[4][4] = {
  {0, 0, 0, 0},
  {0, 0, 1, 0},
  {1, 1, 1, 0},
  {0, 0, 0, 0}
};


#endif


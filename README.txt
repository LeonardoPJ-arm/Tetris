Projeto Tetris
	Este repositório contém o firmware completo e a documentação de hardware para uma implementação do jogo Tetris, rodando em um Arduino Nano. O projeto destaca-se pelo controle direto de hardware via registradores de deslocamento e uma arquitetura de software baseada em interrupções de tempo.

🛠️ Hardware e Eletrônica
	O sistema é projetado para controlar uma matriz de LEDs customizada e gerenciar entradas de usuário.
• Microcontrolador: Arduino Nano (baseado no ATmega328P).
• Controle de Display (Shift Registers): Utilização de registradores de deslocamento 74HC595. Eles permitem o controle seriais dos LEDs.
• Matriz de LEDs: O display possui uma resolução de 18 linhas por 10 colunas, totalizando 180 LEDs controlados individualmente.
• Entrada de Usuário: 6 Botões (push buttons) configurados para navegação e jogo.
    ◦ Funções: Cima, Baixo, Esquerda, Direita, Voltar, Enter.
• Áudio: Saída para efeitos sonoros com buzzer, em especial a reprodução da musica classica do Tetris.

Consulte os diagramas para detalhes das conexões elétricas:
• Tetris_diagrama_geral-Esquematico.drawio.png
• Tetris_diagrama_geral-Geral.drawio.png

💻 Firmware: Arquitetura e Lógica
	O firmware não utiliza o loop principal (void loop) da maneira tradicional para o timing. Ele é guiado por um Timer com interrupção de 20ms, garantindo uma taxa de atualização de 50Hz e constante para o display e leitura de inputs.

1. Renderização de Vídeo (Display)
A lógica de exibição é abstraída para facilitar o desenvolvimento:
• Matriz Virtual: Existe uma matriz de dados de 18x10 na memória.
• Atualização Automática: Para imprimir algo no display, o código apenas escreve nesta matriz. A rotina de interrupção do timer (a cada 20ms) lê automaticamente esses dados e os envia para os Shift Registers (74HC595), atualizando a imagem física nos 180 LEDs a 50Hz, controlando individualmente cada LED.

2. Leitura de Botões (Input)
O sistema de entrada implementa interrupção para fazer a leitura dos botões e com tratamento de debounce.
• Vetor de Estados: O status de todos os 6 botões é armazenado e acessível através de um vetor simples.
• Press & Hold: O firmware diferencia um toque rápido (Press) de um toque contínuo (Hold).

3. Menu e Máquina de Estados
O sistema opera como uma Máquina de Estados, gerenciando a transição entre diferentes "Programas":
	1. Tetris: O jogo principal.
	2. Efeito Browniano: Um modo de demonstração visual onde LEDs acendem e apagam aleatoriamente na tela (ruído visual).
	3. Snake: O clássico jogo da cobrinha (atualmente em fase de desenvolvimento).

🎮 Lógica do Tetris
	O núcleo do jogo Tetris implementa as regras clássicas com otimizações para o hardware. A cada 1 segundo há o movimento da peça, conforme os botões e detectadas as colisões. 

• Mecânica de Peças: As peças (tetrominós) são geradas e inseridas no topo da matriz 18x10. Uma segunda matrix armazena as peças já posicionadas.
• Gravidade e Colisão: O sistema verifica constantemente se a peça pode descer. A colisão é detectada contra as paredes laterais, o chão e contra outras peças já fixadas na matriz (pilha).
• Limpeza de Linhas: Quando uma linha horizontal de 10 blocos é preenchida, o algoritmo a remove, desce todos os blocos acima dela e incrementa a pontuação.
O fluxo detalhado desta lógica pode ser visualizado em:
• Tetris_diagrama_geral-Tetris.drawio.png

# Simulador de Braço Robótico - OpenGL

Este projeto é uma simulação gráfica de um braço robótico, desenvolvida como atividade prática para a disciplina de **Computação Gráfica**. O simulador permite controlar um braço robótico com três segmentos articulados, utilizando teclado para movimentação e HUD para exibição de informações.

## 🛠️ Tecnologias e Ferramentas

- Linguagem: C++
- Biblioteca gráfica: OpenGL (GL, GLUT, GLU)

## 🎮 Controles

- **Setas ↑ / ↓**: Rotaciona os segmentos do braço
- **Limites de rotação**:
  - Segmento 1: até 40°
  - Segmento 2: até 80°
  - Segmento 3: até 60°

## 🔧 Funcionalidades

- Três segmentos de braço com articulações
- Articulações visuais (cilindros) entre os segmentos
- HUD com informações renderizadas em tempo real
- Estrutura modular (funções separadas para desenho de cada parte)

## 📚 Objetivo

Explorar transformações geométricas, renderização 3D e interação com o usuário usando OpenGL, reforçando conceitos teóricos de Computação Gráfica.

## 📷 Captura de Tela

![Simulação do braço robótico](imgs/screenshot.png)

## 🚀 Execução

Certifique-se de ter o OpenGL e GLUT instalados. Compile com:

```bash
g++ -o main.exe main.cpp -I"./include" -L"./lib/x64" -lfreeglut -lopengl32 -lglu32
.\main.exe

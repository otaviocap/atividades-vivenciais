# 🎮 Jogo - Módulo 6 (PGCCHIB - Processamento Gráfico)

Este diretório contém o projeto do jogo desenvolvido como parte do **Módulo 6** da disciplina **Processamento Gráfico (PGCCHIB)** — 2025/1.

Trabalho realizado por: **Natália Chies** e **Otávio Henrique**

## 🧠 Objetivo

O jogo serve como culminação prática dos conhecimentos adquiridos ao longo do curso, incorporando conceitos como:

- Criação e manipulação de buffers
- Uso de shaders customizados
- Mapeamento de texturas
- Animação de sprites
- Sistema de movimentação com teclado

## 📁 Estrutura de Pastas

```
game/
├── include/      # Headers do projeto e do GLAD
├── common/       # Arquivos auxiliares como glad.c
├── src/          # Código-fonte principal do jogo
├── assets/       # Sprites, texturas e recursos visuais (se aplicável)
└── CMakeLists.txt
```

## ⚙️ Compilação com CMake

Para compilar o projeto do jogo, execute os seguintes comandos no terminal:

```bash
mkdir build
cd build
cmake ..
make
./jogo
```

> **Nota:** Certifique-se de que os arquivos do GLAD estejam corretamente posicionados em `include/` e `common/`.

## 🕹️ Controles do Jogo

- `W`, `A`, `S`, `D` ou `↑`, `↓`, `→`, `←` – Movimentam o personagem principal
- `ESC` – Encerra o jogo

## 📌 Observações

- Este projeto foi compilado e testado em **Pop!_OS 22.04 LTS**
- A engine gráfica é baseada em OpenGL 3.3

## 🛠️ Dependências

- **GLFW**
- **GLAD**
- **CMake**
- **OpenGL 3.3**

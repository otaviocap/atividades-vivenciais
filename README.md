# 🧿 PGCCHIB - Processamento Gráfico (2025/1) - Atividades Vivenciais

Este repositório contém as soluções das atividades vivenciais da disciplina **Processamento Gráfico** (2025/1), desenvolvidas em **Pop!_OS 22.04 LTS**.

Trabalhos realizados por: **Natália Chies** e **Otávio Henrique**

## 🗂️ Organização do Repositório

O repositório está organizado em duas principais pastas:

- `activities/`: contém as atividades dos módulos da disciplina (como os exercícios de buffers, texturas, parallax, etc.).
- `game/`: contém o jogo desenvolvido como parte do **Módulo 6**, reunindo os conhecimentos aplicados ao longo da disciplina.

## 📌 Atividades

### Módulo 2
Revisão sobre buffers de geometria e envio de dados ao shader:
1. Clique na tela para criar 1 vértice.
2. A cada 3 vértices, forma-se um triângulo.
3. Cada triângulo usa uma cor diferente.

### Módulo 3
Revisão de mapeamento de texturas e transformações:
1. Um sprite é controlado pelo jogador via teclado.
2. O fundo da cena tem várias camadas.
3. As camadas se movem com parallax — mais próximas se movem mais rápido que as distantes.

## 📁 Estrutura de Pastas (Essencial)

```
PGCCHIB/
├── activities/       # Atividades dos módulos (m2, m3, m4, etc.)
│   ├── include/      # GLAD e headers
│   ├── common/       # glad.c
│   ├── src/          # Códigos das atividades
│   └── CMakeLists.txt
├── game/             # Jogo do Módulo 6
│   ├── include/
│   ├── common/
│   ├── src/
│   └── CMakeLists.txt
```

## ⚠️ Instruções para o GLAD
Copie os arquivos do GLAD gerados para:
- `include/glad/`
- `include/glad/KHR/`
- `common/glad.c`

## ⚙️ Compilação com CMake
Acesse uma das pastas (activities, game)

```bash
mkdir build
cd build
cmake ..
make
./nome_do_exec
```

## 📚 Exercícios Disponíveis em `activities`
- `m2`: Exercício de triângulos com cores diferentes
- `m3`: Exercício de parallax com camadas
- `m4`: (Descrever se aplicável)

O jogo completo está em `game/` e será documentado separadamente.
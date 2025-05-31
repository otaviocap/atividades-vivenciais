# 🧿 PGCCHIB - Processamento Gráfico (2025/1) - Atividades Vivenciais

Repositório com as soluções das atividades vivencias da disciplina **Processamento Gráfico** (2025/1), compilado em **Pop!_OS 22.04 LTS**.

Trabalhos feitos por: **Natália Chies** e **Otávio Henrique**

## 📌 Atividades

### Modulo 2
O objetivo do exercício é revisar o conteúdo sobre criação de buffers de geometria e envio de informações para o
programa de shader. Para isso, você vai fazer uma versão modificada do Exercício 3 da resposta ao desafio, que
atende os seguintes requisitos:
1) Ao clicar na tela, você agora estará criando apenas 1 vértice
2) A cada 3 vértices criados, você criará um triângulo
3) Para cada novo triângulo criado, você deve usar uma cor nova


## 📁 Estrutura

```
PGCCHIB/
├── include/         # GLAD e dependências
├── common/          # glad.c
├── src/             # Códigos das atividades
├── CMakeLists.txt
```

## ⚠️ GLAD manual
Coloque os arquivos gerados em:
- `include/glad/`
- `include/glad/KHR/`
- `common/glad.c`

## ⚙️ Compilação (via CMake)

```bash
mkdir build
cd build
cmake ..
make
./nome_do_exec
```

## 📚 Exercícios Disponíveis
- `m2`: Implementa o primeiro exercício vivencial
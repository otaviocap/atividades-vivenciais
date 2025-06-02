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

### Modulo 3
O objetivo do exercício é revisar o conteúdo sobre mapeamento de texturas e transformações nos objetos. Para
isso, você vai fazer uma extensão no exercício proposto no desafio, que atenda os seguintes requisitos:
1) Você escolherá um dos sprites como sendo o “personagem” do jogador. Este personagem deverá se
   mover para os lados ou para cima e para baixo utilizando o teclado.
2) O fundo da cena será um cenário construído em camadas. Inicialmente, o cenário
   terá todas as camadas posicionadas igualmente.
3) Ao mover o personagem, as camadas deverão deslocar-se junto com ele. As camadas mais próximas do
   personagem (exemplo: chão, árvores...) deverão se deslocar mais rápido (offset maior), enquanto as
   camadas mais distantes do personagem (exemplo: montanha, nuvens) irão se deslocar mais
   lentamente

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
- `m3`: Implementado a atividade com parallax
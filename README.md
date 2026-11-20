#  Space Traffic

Jogo casual desenvolvido em **C** com a biblioteca **[Raylib](https://www.raylib.com/)**, como projeto da disciplina PIF na **CESAR School**.

##  Sobre o jogo

Você pilota uma nave que atravessa um cinturão de asteroides em alta velocidade. Para sobreviver, use o canhão de laser para destruir os asteroides que aparecem no caminho.

Mas cuidado:

- **A munição é finita.** Colete energia pelo caminho para recarregar os lasers.
- **Colidir com um asteroide** faz você perder uma vida e velocidade.

**Objetivo:** manter-se o maior tempo possível em alta velocidade e destruir o máximo de asteroides, alcançando uma pontuação recorde.

##  Mecânicas

| Elemento | Descrição |
|---|---|
|  Nave | Controlada pelo jogador; possui vidas, munição e velocidade |
|  Lasers | Disparados pela nave; consomem munição e destroem asteroides |
|  Asteroides | Surgem no caminho da nave; a colisão tira vida e velocidade |
|  Energia | Item coletável que recarrega a munição |
|  Recorde | A melhor pontuação fica salva em arquivo |

## 🕹️ Controles

| Tecla | Ação |
|---|---|
| "Setinhas" | Mover a nave |
| "espaço" | Atirar |

##  Tecnologias

- Linguagem **C**
- **Raylib 5.5**
- **GCC** (MinGW-w64 no Windows)
- **Make** para compilação

##  Instalação

### Windows

1. Baixe o compilador em [winlibs.com](https://winlibs.com/): **GCC 16.2.0 (POSIX, UCRT)**, versão **Win64 → Zip archive**.
2. Extraia de forma que exista a pasta `C:\mingw64\bin`.
3. Adicione `C:\mingw64\bin` à variável de ambiente **Path** e mova para o topo da lista.
4. Baixe a Raylib em [github.com/raysan5/raylib/releases](https://github.com/raysan5/raylib/releases): arquivo `raylib-5.5_win64_mingw-w64.zip`.
5. Extraia e renomeie a pasta para que fique em `C:\raylib` (com as pastas `include` e `lib` dentro).
6. Confira em um terminal novo: `gcc --version` deve mostrar a versão 16.2.0.

### Linux (Ubuntu/Debian)

```bash
sudo apt update
sudo apt install build-essential libraylib-dev
```

> Se o pacote `libraylib-dev` não estiver disponível na sua versão, compile a Raylib a partir do [código-fonte](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux).

### macOS

```bash
brew install raylib
```

##  Como compilar e executar

Clone o repositório:

```bash
git clone https://github.com/Joao-Bezerra22/SpaceTraffic.git
cd SpaceTraffic
```

**Windows:**

```bash
mingw32-make
.\jogo.exe
```

**Linux:**

```bash
gcc src/*.c -o jogo -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./jogo
```

**macOS:**

```bash
clang src/*.c -o jogo -I$(brew --prefix)/include -L$(brew --prefix)/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
./jogo
```

> O suporte do Makefile para Linux e macOS está em andamento. Até lá, use os comandos acima.

##  Estrutura do projeto

```
SpaceTraffic/
├── src/
│   ├── main.c        # Loop principal e estados do jogo (menu / jogando)
│   ├── cenario.c     # Fundo de estrelas em movimento
│   └── cenario.h
├── Makefile
└── README.md
```

##  Conceitos de C aplicados

-  Estruturas (`struct`)
-  Ponteiros
-  Alocação dinâmica de memória
-  Listas encadeadas
-  Matrizes
-  Escrita e leitura em arquivo (recorde)

## Vídeo

https://youtu.be/9QRvR-LmYUE

## 👥 Equipe

- Luiz Eduardo Albuquerque Alves de Lima – https://github.com/Eduardo-Albuquerque1
- João Bezerra de Barros Neto – https://github.com/Joao-Bezerra22
- Luiz Eduardo da Silva Moreira – https://github.com/lesm-fut

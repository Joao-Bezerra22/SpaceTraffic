ARQUIVOS = src/main.c src/cenario.c src/nave.c src/asteroides.c src/tiro.c src/jogo.c src/placar.c

ifeq ($(OS),Windows_NT)
    EXE   = jogo.exe
    FLAGS = -I C:\raylib\include -L C:\raylib\lib -lraylib -lopengl32 -lgdi32 -lwinmm
else
    EXE = jogo
    SISTEMA := $(shell uname -s)
    ifeq ($(SISTEMA),Darwin)
        FLAGS = -I$(shell brew --prefix)/include -L$(shell brew --prefix)/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
    else
        FLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
    endif
endif

$(EXE): $(ARQUIVOS)
	gcc $(ARQUIVOS) -o $(EXE) $(FLAGS)
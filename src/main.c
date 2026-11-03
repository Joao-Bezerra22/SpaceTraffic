#include "raylib.h"
#include <raymath.h>
#include "cenario.h"
#include "nave.h"
#include "asteroides.h"
typedef enum {
    TELA_INICIAL,
    JOGANDO,
    GAMEOVER
} EstadoJogo;

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 450, "Space Traffic");
    SetTargetFPS(60);

    Estrela estrelas[NUM_ESTRELAS];
    iniciarEstrelas(estrelas);

    EstadoJogo estado = TELA_INICIAL;

    Rectangle botao = { (GetScreenWidth() - 200) / 2, 250, 200, 60 };

    Nave nave;
    iniciarNave(&nave);

    Asteroide asteroides[MAX_ASTEROIDES] = {0};
    float tempoContagem = 3.0f;
    float tempoUltimoSpawn = 0.0f;

    float velocidadeKMH = 100.0f;
    float velocidadeMaxKMH = 350.0f;     
    float taxaAceleracao = 15.0f;        
    float velocidadeExtraAsteroides = 0.0f;

    int lapAtual = 1;
    int lapMax = 3;

    float tempoParaLap = 20.0f;
    bool linhaLapAtiva = false;
    float posicaoLinhaLapY = -10.0f;

    float spawnRateAtual = 0.8f;
    float spawnRateMinimoLap1 = 0.4f;
    float spawnRateMinimoLap2 = 0.25f;
    float spawnRateMinimoLap3 = 0.1f;
    float limiteMinimoAtual = spawnRateMinimoLap1;

    while (!WindowShouldClose()) {
        if(IsKeyPressed(KEY_F11)){
            ToggleFullscreen();
            iniciarEstrelas(estrelas);
            nave.posicao.x = (GetScreenWidth() - nave.largura) / 2;
            nave.posicao.y = GetScreenHeight() - 120.0f;
        }
        if(IsWindowResized()){
            iniciarEstrelas(estrelas);
            nave.posicao.x = (GetScreenWidth() - nave.largura) / 2;
            nave.posicao.y = GetScreenHeight() - 120.0f;
        }
        float dt = GetFrameTime();
        atualizarEstrelas(estrelas, velocidadeExtraAsteroides);
        if (estado == TELA_INICIAL) {
            
            botao.x = (GetScreenWidth() - 200) / 2.0f;

            if (CheckCollisionPointRec(GetMousePosition(), botao) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                estado = JOGANDO;
            }
        } 
        else if (estado == JOGANDO) {
            atualizarNave(&nave);

            if (tempoContagem > 0) {
                tempoContagem -= dt;
            } else {
                if (velocidadeKMH < velocidadeMaxKMH){
                    velocidadeKMH += taxaAceleracao*dt;
                    if (velocidadeKMH > velocidadeMaxKMH) velocidadeKMH = velocidadeMaxKMH;
                }
                
                velocidadeExtraAsteroides = (velocidadeKMH - 100.0f) * 1.5f;

                if (spawnRateAtual > limiteMinimoAtual) {
                    spawnRateAtual -= 0.25f * dt; 
                }
                if (spawnRateAtual < limiteMinimoAtual) {
                    spawnRateAtual = limiteMinimoAtual;
                }

                tempoUltimoSpawn += dt;
                
                if (tempoUltimoSpawn > spawnRateAtual) { 
                    iniciarAsteroides(asteroides, MAX_ASTEROIDES, velocidadeExtraAsteroides);
                    tempoUltimoSpawn = 0.0f;
                }

                for (int i = 0; i < MAX_ASTEROIDES; i++) {
                    AsteroidAtualizar(&asteroides[i], dt);
                    if (asteroides[i].posicao.y > GetScreenHeight() + 100) {
                        asteroides[i].ativo = false;
                    }

                    if (asteroides[i].ativo) {
                        Vector2 pontoMaisProximo;
                        pontoMaisProximo.x = Clamp(asteroides[i].posicao.x, nave.posicao.x, nave.posicao.x + nave.largura);
                        pontoMaisProximo.y = Clamp(asteroides[i].posicao.y, nave.posicao.y, nave.posicao.y + nave.altura);
                        
                        float distancia = Vector2Distance(asteroides[i].posicao, pontoMaisProximo);
                        float raioColisao = 15.0f;
                        if (asteroides[i].tipo == ASTEROIDE_PEQUENO) raioColisao = 10.0f;
                        else if (asteroides[i].tipo == ASTEROIDE_MEDIO) raioColisao = 20.0f;
                        else if (asteroides[i].tipo == ASTEROIDE_GRANDE) raioColisao = 35.0f;

                        if (distancia < raioColisao) {
                            spawnRateAtual += spawnRateAtual / 3.0f;
                            asteroides[i].ativo = false;
                            
                            velocidadeKMH -= 150.0f; 
                            if (velocidadeKMH < 100.0f) {
                                velocidadeKMH = 100.0f;
                            }
                        }
                    }
                }
                if (!linhaLapAtiva && lapAtual < lapMax) {
                    tempoParaLap -= dt;
                    if (tempoParaLap <= 0) {
                        linhaLapAtiva = true;
                        posicaoLinhaLapY = -10.0f;
                    }
                }

                if (linhaLapAtiva) {
                    posicaoLinhaLapY += (100.0f + velocidadeExtraAsteroides) * dt;
                    if (posicaoLinhaLapY >= nave.posicao.y && posicaoLinhaLapY <= nave.posicao.y + nave.altura) {
                        lapAtual++;
                        linhaLapAtiva = false;
                        tempoParaLap = 20.0f;

                        if (lapAtual == 2) limiteMinimoAtual = spawnRateMinimoLap2;
                        if (lapAtual == 3) limiteMinimoAtual = spawnRateMinimoLap3;
                    }
                    
                    if (posicaoLinhaLapY > GetScreenHeight() + 50) {
                        linhaLapAtiva = false;
                        tempoParaLap = 20.0f;
                    }
                }
            }
        }

        BeginDrawing();
            ClearBackground(BLACK);
            desenharEstrelas(estrelas);

            if (estado == TELA_INICIAL) {

            int larguraTitulo = MeasureText("Space Traffic", 50);
            DrawText("Space Traffic", (GetScreenWidth() - larguraTitulo) / 2, 130, 50, WHITE);

            DrawRectangleRec(botao, DARKGRAY);

            int larguraStart = MeasureText("START", 30);
            DrawText("START", botao.x + (botao.width - larguraStart) / 2, botao.y + 15, 30, WHITE);
        }

        if(estado == JOGANDO){
            desenharNave(nave);

            if (tempoContagem > 0) {
                int numero = (int)(tempoContagem + 0.9f); 
                const char* textoTempo = TextFormat("%d", numero);
                int larguraTexto = MeasureText(textoTempo, 80);
                DrawText(textoTempo, (GetScreenWidth() - larguraTexto) / 2, GetScreenHeight() / 2 - 40, 80, RED);
            } else {
                desenharAsteroide(asteroides, MAX_ASTEROIDES);

                if(linhaLapAtiva){
                    DrawLine(0, (int)posicaoLinhaLapY, GetScreenWidth(), (int)posicaoLinhaLapY, YELLOW);
                }

                const char* textoVelocidade = TextFormat("KM/H %03i", (int)velocidadeKMH);
                DrawText(textoVelocidade, 10, 10, 20, LIGHTGRAY);

                const char* textoLap = TextFormat("LAP %i/%i", lapAtual, lapMax);
                DrawText(textoLap, GetScreenWidth() - 100, 10, 20, LIGHTGRAY);
            }
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
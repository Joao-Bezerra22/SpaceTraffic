#include "raylib.h"
#include <raymath.h>
#include "cenario.h"
#include "nave.h"
#include "asteroides.h"
#include "tiro.h"

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
    Tiro *listaTiros = NULL;
    iniciarNave(&nave);

    Asteroide asteroides[MAX_ASTEROIDES] = {0};
    float tempoContagem = 3.0f;
    float tempoUltimoSpawn = 0.0f;

    float velocidadeKMH = 100.0f;
    float velocidadeMaxKMH = 350.0f;     
    float taxaAceleracao = 15.0f;        
    float velocidadeExtraAsteroides = 0.0f;

    float tempoJogo = 0.0f;

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
                iniciarNave(&nave);
                liberarTiros(listaTiros);
                listaTiros = NULL;
                tempoJogo = 0.0f;
                tempoContagem = 3.0f;
                velocidadeKMH = 100.0f;
                lapAtual = 1;

                for (int i = 0; i < MAX_ASTEROIDES; i++) {
                    asteroides[i].ativo = false;
                }
            }
        } 
        else if (estado == JOGANDO) {
            atualizarNave(&nave);

            if (IsKeyPressed(KEY_SPACE)) {
                Vector2 saida = { nave.posicao.x + nave.largura / 2 - 2, nave.posicao.y };
                listaTiros = adicionarTiro(listaTiros, saida);
            }

            atualizarTiros(listaTiros);
            listaTiros = removerTirosForaDaTela(listaTiros);

            if (tempoContagem > 0) {
                tempoContagem -= dt;
            } else {
                tempoJogo += dt;
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
                    AsteroidAtualizar(&asteroides[i], dt, velocidadeExtraAsteroides);
                    if (asteroides[i].posicao.y > GetScreenHeight() + 100 || 
                        asteroides[i].posicao.x < -100 || 
                        asteroides[i].posicao.x > GetScreenWidth() + 100) {
                        asteroides[i].ativo = false;
                    }
                    if (asteroides[i].ativo) {
                        float raioColisaoAst = 15.0f;
                        if (asteroides[i].tipo == ASTEROIDE_PEQUENO) raioColisaoAst = 10.0f;
                        else if (asteroides[i].tipo == ASTEROIDE_MEDIO) raioColisaoAst = 20.0f;
                        else if (asteroides[i].tipo == ASTEROIDE_GRANDE) raioColisaoAst = 35.0f;

                        Tiro *anteriorTiro = NULL;
                        Tiro *atualTiro = listaTiros;

                        while (atualTiro != NULL) {
                            
                            Vector2 centroTiro = { atualTiro->posicao.x + 2.0f, atualTiro->posicao.y + 6.0f };
                            float distanciaTiro = Vector2Distance(asteroides[i].posicao, centroTiro);

                            if (distanciaTiro < raioColisaoAst + 2.0f) { 
                                
                                Tiro *removido = atualTiro;
                                if (anteriorTiro == NULL) {
                                    listaTiros = atualTiro->next;
                                } else {
                                    anteriorTiro->next = atualTiro->next;
                                }
                                atualTiro = atualTiro->next;
                                free(removido);

                                
                                Vector2 posOriginal = asteroides[i].posicao;
                                bool eraGrandeOuMedio = (asteroides[i].tipo == ASTEROIDE_GRANDE || asteroides[i].tipo == ASTEROIDE_MEDIO);
                                AsteroideTipo novoTipo = (asteroides[i].tipo == ASTEROIDE_GRANDE) ? ASTEROIDE_MEDIO : ASTEROIDE_PEQUENO;
                                
                                asteroides[i].ativo = false; // Libera este slot imediatamente

                                // 3. Dividir o asteroide e jogar em diagonal para cima
                                if (eraGrandeOuMedio) {
                                    int gerados = 0;
                                    
                                    for (int k = 0; k < MAX_ASTEROIDES && gerados < 2; k++) {
                                        if (!asteroides[k].ativo) {
                                            Vector2 novaVel;
                                            novaVel.x = (gerados == 0) ? -150.0f : 150.0f; // Afasta rápido para os lados
                                            novaVel.y = -100.0f; // Eixo Y negativo faz os pedaços pularem para cima
                                            
                                            Vector2 novaPos = posOriginal;
                                            novaPos.x += (gerados == 0) ? -20.0f : 20.0f; // Pequeno deslocamento lateral para evitar sobreposição
                                            asteroides[k] = criarAsteroide(novoTipo, novaPos, novaVel);
                                            gerados++;
                                        }
                                    }
                                }
                                
                                
                                break; 
                            } else {
                                anteriorTiro = atualTiro;
                                atualTiro = atualTiro->next;
                            }
                        }
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

                            for (int j = 0; j < MAX_ASTEROIDES; j++) {
                                if (asteroides[j].ativo && asteroides[j].posicao.y < 0) {
                                    asteroides[j].ativo = false;
                                }
                            }
                            
                            velocidadeKMH -= 150.0f; 
                            if (velocidadeKMH < 100.0f) {
                                velocidadeKMH = 100.0f;
                            }

                            nave.vidas--;

                            if (nave.vidas <= 0) {
                                estado = GAMEOVER;
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
        else if (estado == GAMEOVER) {
            if (IsKeyPressed(KEY_ENTER)) {
                estado = TELA_INICIAL;
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
            desenharTiros(listaTiros);

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

                DrawText("LIFE:", 160, 10, 20, RED);
                for (int i = 0; i < nave.vidas; i++) {
                    DrawCircle(245 + (i * 20), 20, 7, RED);
                }

                int minutos = (int)tempoJogo / 60;
                int segundos = (int)tempoJogo % 60;
                const char* textoTempoJogo = TextFormat("TEMPO: %02i:%02i", minutos, segundos);
                DrawText(textoTempoJogo, 320, 10, 20, YELLOW);

                const char* textoLap = TextFormat("LAP %i/%i", lapAtual, lapMax);
                DrawText(textoLap, GetScreenWidth() - 100, 10, 20, LIGHTGRAY);
            }
        }

        if (estado == GAMEOVER) {
            int larguraGO = MeasureText("GAME OVER", 50);
            DrawText("GAME OVER", (GetScreenWidth() - larguraGO) / 2, 150, 50, RED);

            const char* subTexto = "Pressione ENTER para tentar novamente";
            int larguraSub = MeasureText(subTexto, 20);
            DrawText(subTexto, (GetScreenWidth() - larguraSub) / 2, 230, 20, LIGHTGRAY);
        }

        EndDrawing();
    }

    liberarTiros(listaTiros);
    CloseWindow();
    return 0;
}
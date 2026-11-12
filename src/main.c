#include "raylib.h"
#include <raymath.h>
#include "cenario.h"
#include "jogo.h"

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

    Jogo jogo;
    jogo.listaTiros = NULL;
    reiniciarJogo(&jogo);

    Rectangle botao = { (GetScreenWidth() - 200) / 2, 250, 200, 60 };

    while (!WindowShouldClose()) {
        if(IsKeyPressed(KEY_F11)){
            ToggleFullscreen();
            iniciarEstrelas(estrelas);
            jogo.nave.posicao.x = (GetScreenWidth() - jogo.nave.largura) / 2;
            jogo.nave.posicao.y = GetScreenHeight() - 120.0f;
        }
        if(IsWindowResized()){
            iniciarEstrelas(estrelas);
            jogo.nave.posicao.x = (GetScreenWidth() - jogo.nave.largura) / 2;
            jogo.nave.posicao.y = GetScreenHeight() - 120.0f;
        }
        float dt = GetFrameTime();
        atualizarEstrelas(estrelas, jogo.velocidadeExtraAsteroides);
        if (estado == TELA_INICIAL) {
            
            botao.x = (GetScreenWidth() - 200) / 2.0f;

            if (CheckCollisionPointRec(GetMousePosition(), botao) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                estado = JOGANDO;
                reiniciarJogo(&jogo);
            }
        } 
        else if (estado == JOGANDO) {
            atualizarNave(&jogo.nave);

            if (IsKeyPressed(KEY_SPACE)) {
                Vector2 saida = { jogo.nave.posicao.x + jogo.nave.largura / 2 - 2, jogo.nave.posicao.y };
                jogo.listaTiros = adicionarTiro(jogo.listaTiros, saida);
            }

            atualizarTiros(jogo.listaTiros);
            jogo.listaTiros = removerTirosForaDaTela(jogo.listaTiros);

            if (jogo.tempoContagem > 0) {
                jogo.tempoContagem -= dt;
            } else {
                jogo.tempoJogo += dt;
                if (jogo.velocidadeKMH < VELOCIDADE_MAX_KMH){
                    jogo.velocidadeKMH += TAXA_ACELERACAO*dt;
                    if (jogo.velocidadeKMH > VELOCIDADE_MAX_KMH) jogo.velocidadeKMH = VELOCIDADE_MAX_KMH;
                }
                
                jogo.velocidadeExtraAsteroides = (jogo.velocidadeKMH - 100.0f) * 1.5f;

                if (jogo.spawnRateAtual > jogo.limiteMinimoAtual) {
                    jogo.spawnRateAtual -= 0.25f * dt; 
                }
                if (jogo.spawnRateAtual < jogo.limiteMinimoAtual) {
                    jogo.spawnRateAtual = jogo.limiteMinimoAtual;
                }

                jogo.tempoUltimoSpawn += dt;
                
                if (jogo.tempoUltimoSpawn > jogo.spawnRateAtual) { 
                    iniciarAsteroides(jogo.asteroides, MAX_ASTEROIDES, jogo.velocidadeExtraAsteroides);
                    jogo.tempoUltimoSpawn = 0.0f;
                }

                for (int i = 0; i < MAX_ASTEROIDES; i++) {
                    AsteroidAtualizar(&jogo.asteroides[i], dt, jogo.velocidadeExtraAsteroides);
                    if (jogo.asteroides[i].posicao.y > GetScreenHeight() + 100 || 
                        jogo.asteroides[i].posicao.x < -100 || 
                        jogo.asteroides[i].posicao.x > GetScreenWidth() + 100) {
                        jogo.asteroides[i].ativo = false;
                    }
                    if (jogo.asteroides[i].ativo) {
                        float raioColisaoAst = 15.0f;
                        if (jogo.asteroides[i].tipo == ASTEROIDE_PEQUENO) raioColisaoAst = 10.0f;
                        else if (jogo.asteroides[i].tipo == ASTEROIDE_MEDIO) raioColisaoAst = 20.0f;
                        else if (jogo.asteroides[i].tipo == ASTEROIDE_GRANDE) raioColisaoAst = 35.0f;

                        Tiro *anteriorTiro = NULL;
                        Tiro *atualTiro = jogo.listaTiros;

                        while (atualTiro != NULL) {
                            
                            Vector2 centroTiro = { atualTiro->posicao.x + 2.0f, atualTiro->posicao.y + 6.0f };
                            float distanciaTiro = Vector2Distance(jogo.asteroides[i].posicao, centroTiro);

                            if (distanciaTiro < raioColisaoAst + 2.0f) { 
                                
                                Tiro *removido = atualTiro;
                                if (anteriorTiro == NULL) {
                                    jogo.listaTiros = atualTiro->next;
                                } else {
                                    anteriorTiro->next = atualTiro->next;
                                }
                                atualTiro = atualTiro->next;
                                free(removido);

                                
                                Vector2 posOriginal = jogo.asteroides[i].posicao;
                                bool eraGrandeOuMedio = (jogo.asteroides[i].tipo == ASTEROIDE_GRANDE || jogo.asteroides[i].tipo == ASTEROIDE_MEDIO);
                                AsteroideTipo novoTipo = (jogo.asteroides[i].tipo == ASTEROIDE_GRANDE) ? ASTEROIDE_MEDIO : ASTEROIDE_PEQUENO;
                                
                                jogo.asteroides[i].ativo = false; // Libera este slot imediatamente

                                // 3. Dividir o asteroide e jogar em diagonal para cima
                                if (eraGrandeOuMedio) {
                                    int gerados = 0;
                                    
                                    for (int k = 0; k < MAX_ASTEROIDES && gerados < 2; k++) {
                                        if (!jogo.asteroides[k].ativo) {
                                            Vector2 novaVel;
                                            novaVel.x = (gerados == 0) ? -150.0f : 150.0f; // Afasta rápido para os lados
                                            novaVel.y = -100.0f; // Eixo Y negativo faz os pedaços pularem para cima
                                            
                                            Vector2 novaPos = posOriginal;
                                            novaPos.x += (gerados == 0) ? -20.0f : 20.0f; // Pequeno deslocamento lateral para evitar sobreposição
                                            jogo.asteroides[k] = criarAsteroide(novoTipo, novaPos, novaVel);
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


                    if (jogo.asteroides[i].ativo) {
                        Vector2 pontoMaisProximo;
                        pontoMaisProximo.x = Clamp(jogo.asteroides[i].posicao.x, jogo.nave.posicao.x, jogo.nave.posicao.x + jogo.nave.largura);
                        pontoMaisProximo.y = Clamp(jogo.asteroides[i].posicao.y, jogo.nave.posicao.y, jogo.nave.posicao.y + jogo.nave.altura);
                        
                        float distancia = Vector2Distance(jogo.asteroides[i].posicao, pontoMaisProximo);
                        float raioColisao = 15.0f;
                        if (jogo.asteroides[i].tipo == ASTEROIDE_PEQUENO) raioColisao = 10.0f;
                        else if (jogo.asteroides[i].tipo == ASTEROIDE_MEDIO) raioColisao = 20.0f;
                        else if (jogo.asteroides[i].tipo == ASTEROIDE_GRANDE) raioColisao = 35.0f;

                        if (distancia < raioColisao) {
                            jogo.spawnRateAtual += jogo.spawnRateAtual / 3.0f;
                            jogo.asteroides[i].ativo = false;

                            for (int j = 0; j < MAX_ASTEROIDES; j++) {
                                if (jogo.asteroides[j].ativo && jogo.asteroides[j].posicao.y < 0) {
                                    jogo.asteroides[j].ativo = false;
                                }
                            }
                            
                            jogo.velocidadeKMH -= 150.0f; 
                            if (jogo.velocidadeKMH < 100.0f) {
                                jogo.velocidadeKMH = 100.0f;
                            }

                            jogo.nave.vidas--;

                            if (jogo.nave.vidas <= 0) {
                                estado = GAMEOVER;
                            }
                        }
                    }
                }
                if (!jogo.linhaLapAtiva && jogo.lapAtual < LAP_MAX) {
                    jogo.tempoParaLap -= dt;
                    if (jogo.tempoParaLap <= 0) {
                        jogo.linhaLapAtiva = true;
                        jogo.posicaoLinhaLapY = -10.0f;
                    }
                }

                if (jogo.linhaLapAtiva) {
                    jogo.posicaoLinhaLapY += (100.0f + jogo.velocidadeExtraAsteroides) * dt;
                    if (jogo.posicaoLinhaLapY >= jogo.nave.posicao.y && jogo.posicaoLinhaLapY <= jogo.nave.posicao.y + jogo.nave.altura) {
                        jogo.lapAtual++;
                        jogo.linhaLapAtiva = false;
                        jogo.tempoParaLap = 20.0f;

                        if (jogo.lapAtual == 2) jogo.limiteMinimoAtual = SPAWN_MINIMO_LAP2;
                        if (jogo.lapAtual == 3) jogo.limiteMinimoAtual = SPAWN_MINIMO_LAP3;
                    }
                    
                    if (jogo.posicaoLinhaLapY > GetScreenHeight() + 50) {
                        jogo.linhaLapAtiva = false;
                        jogo.tempoParaLap = 20.0f;
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
            desenharNave(jogo.nave);
            desenharTiros(jogo.listaTiros);

            if (jogo.tempoContagem > 0) {
                int numero = (int)(jogo.tempoContagem + 0.9f); 
                const char* textoTempo = TextFormat("%d", numero);
                int larguraTexto = MeasureText(textoTempo, 80);
                DrawText(textoTempo, (GetScreenWidth() - larguraTexto) / 2, GetScreenHeight() / 2 - 40, 80, RED);
            } else {
                desenharAsteroide(jogo.asteroides, MAX_ASTEROIDES);

                if(jogo.linhaLapAtiva){
                    DrawLine(0, (int)jogo.posicaoLinhaLapY, GetScreenWidth(), (int)jogo.posicaoLinhaLapY, YELLOW);
                }

                const char* textoVelocidade = TextFormat("KM/H %03i", (int)jogo.velocidadeKMH);
                DrawText(textoVelocidade, 10, 10, 20, LIGHTGRAY);

                DrawText("LIFE:", 160, 10, 20, RED);
                for (int i = 0; i < jogo.nave.vidas; i++) {
                    DrawCircle(245 + (i * 20), 20, 7, RED);
                }

                int minutos = (int)jogo.tempoJogo / 60;
                int segundos = (int)jogo.tempoJogo % 60;
                const char* textoTempoJogo = TextFormat("TEMPO: %02i:%02i", minutos, segundos);
                DrawText(textoTempoJogo, 320, 10, 20, YELLOW);

                const char* textoLap = TextFormat("LAP %i/%i", jogo.lapAtual, LAP_MAX);
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

    liberarTiros(jogo.listaTiros);
    CloseWindow();
    return 0;
}
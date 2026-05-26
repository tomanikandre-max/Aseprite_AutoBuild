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
#include <mutex>
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
std::vector<std::string> ultimasLinhas;
std::mutex logMutex;
std::atomic<bool> processandoOtimizacao = false;
std::string etapaAtual = "";
bool editMode = false;
int passo = 0;
double tempoInicio = GetTime();
float tempoRestante = 0; 
char pasta[300] = "C:\Aseprite";
bool prontoParaProximo = false;
int pagina = 0;
void ExecutarComLog(std::string comando);
void Thread(char lingua);
int main() {
    bool prontoParaProximo = false;
    int contagemLetras = 11;
    int comandoEnviado = 2;
    char lingua2 = ' ';
    bool jaDisparado = false;
    int letras = 11;
    char caminho;
    int seila = 1;
    int i = 0;
    char lingua = ' ';
    int caixa_de_texto = 10;
    char path[500];
    int x = 600, y = 450;
    int x2 = 500, y2 = 600;
    char comando1[560];
    char comando2[560];
    char comando3[560];
    char comando[2048];
    Vector2 posicaoTexto2 = { 310, 20 };
    Vector2 posicaoTexto55 = { 320, 350 };
    _getcwd(path, sizeof(path));
    while (path[i] != '\0') {
        i++;
    }
    Rectangle botao3 = { 320, 350, 150, 70 };
    bool mouseEmCima3 = false;
    InitWindow(x, y, "Instalador Aseprite");
    GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
    SetTargetFPS(60);
    sprintf_s(comando2, "%s\\Roboto\\Roboto-VariableFont_wdth,wght.ttf", path);
    Font Roboto = LoadFontEx(comando2, 800, 0, 800);
    sprintf_s(comando1, "%s\\Icones\\icon1.png", path);
    Texture2D logo = LoadTexture(comando1);
    sprintf_s(comando1, "%s\\Icones\\icon2.png", path);
    Texture2D logo2 = LoadTexture(comando1);
    sprintf_s(comando2, "%s\\Icones\\icon1.png", path);
    Image icone = LoadImage(comando2);
    sprintf_s(comando3, "%s\\Icones\\file.png", path);
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
                lingua2 = 'p';
                pagina = 1;
            }
            if (GuiButton({ 370, 350, 190, 70 }, "English")) {
                lingua2 = 'e';
                pagina = 1;
            }
        }            
        else if (pagina == 1) {
            if (!processandoOtimizacao) {
                const char* titulo = (lingua2 == 'p') ? "DIRETORIO DE INSTALACAO:" : "SETUP DIRECTORY:";
                const char* btnTexto = (lingua2 == 'p') ? "INSTALAR" : "INSTALL";
                DrawRectangleRounded({ 25, 115, 550, 40 }, 0.2f, 10, { 25, 28, 35, 255 });
                if (GuiTextBox({ 30, 120, 540, 30 }, pasta, 512, editMode)) {
                    editMode = !editMode;
                }
                DrawTexture(arquivo, 370, 140, WHITE);
                GuiLabel({ 30, 50, 500, 40 }, titulo);

                if (GuiTextBox({ 30, 120, 540, 30 }, pasta, 512, editMode)) {
                    editMode = !editMode;
                }
                if (GuiButton({ 30, 380, 100, 40 }, (lingua2 == 'p' ? "Voltar" : "Back"))) {
                    pagina = 0;
                }
                if (GuiButton({ 150, 250, 300, 70 }, lingua2 == 'p' ? "Compilar" : "START")) {
                    std::thread(Thread, lingua2).detach();
                }
            }
            else
            {
                DrawRectangle(25, 25, 550, 380, { 20, 22, 26, 255 });
                GuiSetStyle(DEFAULT, TEXT_SIZE, 18);
                std::string etapaCopia;
                {
                    std::lock_guard<std::mutex> trava(logMutex);
                    etapaCopia = etapaAtual;
                }

                if (etapaCopia.empty()) {
                    DrawText(lingua2 == 'p' ? "Iniciando..." : "Starting...", 40, 45, 22, LIME);
                }
                else {
                    DrawText(etapaCopia.c_str(), 40, 45, 22, LIME);
                }

                int espacamentoY = 95;
                {
                    std::lock_guard<std::mutex> trava(logMutex);
                    for (const auto& linhaLog : ultimasLinhas) {
                        if (!linhaLog.empty()) {
                            std::string linhaCurta = linhaLog.substr(0, 52);
                            DrawText(linhaCurta.c_str(), 40, espacamentoY, 15, RAYWHITE);
                            espacamentoY += 32;
                        }
                    }
                }
                GuiLock();
                GuiButton({ 380, 330, 180, 60 }, lingua2 == 'p' ? "RODANDO..." : "RUNNING...");
                GuiUnlock();
                GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
            }
        }
            if (pagina == 2) {
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
                const char* titulo = (lingua2 == 'p') ? "INSTALADO\n\nCOM SUCESSO:" : "SUCESS:";
                const char* btnTexto = (lingua2 == 'p') ? "OK" : "OK";
                GuiLabel({ 200, 100, 500, 40 }, titulo);
                GuiButton({ 150, 250, 300, 70 }, btnTexto);
                if (GuiButton({ 150, 250, 300, 70 }, btnTexto)) {
                    return 0;
                    break;
                }
            }
            EndDrawing();
        }
        CloseWindow();
        return 0;
    }
void ExecutarComLog(std::string comando)
{
    FILE* pipe = _popen(comando.c_str(), "r");
    if (!pipe) return;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL)
    {
        std::string linha = buffer;
        if (!linha.empty() && linha.back() == '\n') linha.pop_back();

        if (!linha.empty())
        {
            std::lock_guard<std::mutex> trava(logMutex);
            ultimasLinhas.push_back(linha);
            if (ultimasLinhas.size() > 8)
            {
                ultimasLinhas.erase(ultimasLinhas.begin());
            }
        }
    }
    _pclose(pipe);
}
void Thread(char lingua)
{
    std::string p = fs::path(pasta).make_preferred().string();
    processandoOtimizacao = true;
    {
        std::lock_guard<std::mutex> trava(logMutex);
        ultimasLinhas.clear();
    }

    if (passo == 0) {
        {
            std::lock_guard<std::mutex> trava(logMutex);
            etapaAtual = (lingua == 'p') ? "Baixando Visual Studio..." : "Downloading Visual Studio";
        }
        if (!DirectoryExists(TextFormat("%s", pasta))) {
            std::string copiapasta = pasta;
                char comando90[2000];
                std::string pasta45 = pasta;
                fs::create_directory(pasta45);
        }
        if (lingua == 'p') {
            MessageBoxA(NULL, "Estamos prosseguindo\ncom a instalacao\ndo Visual Studio,\ncaso ja tenha intalado\ncertifiquece de que\nestá marcado:\ndesenvolvimento para desktop com C++\nsdk do Windows 10 e 11\nferramentas de CMake", "Aviso", MB_OK | MB_ICONINFORMATION);
        }
        else {
            MessageBoxA(NULL, "We are proceeding with\nthe installation\nof Visual Studio.\nIf you have already installed it,\nmake sure that the following is checked:\nDesktop development with C++\nWindows 10 and 11 SDK\nCMake tools.", "Aviso", MB_OK | MB_ICONINFORMATION);
        }
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
            if (prontoParaProximo) passo = 1;
    }
    if (passo == 1) {
        prontoParaProximo = false;
        {
            std::lock_guard<std::mutex> trava(logMutex);
            etapaAtual = (lingua == 'p') ? "Baixando CMake..." : "Downloading CMake...";
        }
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
            if (prontoParaProximo) passo = 2;
    }
    if (passo == 2) {
        prontoParaProximo = false;
        {
            std::lock_guard<std::mutex> trava(logMutex);
            etapaAtual = (lingua == 'p') ? "Baixando Skia..." : "Downloading Skia...";
        }
            std::string pastaSkia = p + "\\skia";
            if (!fs::exists(pastaSkia)) fs::create_directory(pastaSkia);
            std::string skiaInstall = "cmd.exe /c curl -L -o \"" + p + "\\skia.zip\" https://github.com/aseprite/skia/releases/download/m124-08a5439a6b/Skia-Windows-Release-x64.zip && "
                "tar -xf \"" + p + "\\skia.zip\" -C \"" + p + "\\skia\" && "
                "del \"" + p + "\\skia.zip\" 2>&1";
            ExecutarComLog(skiaInstall);
    char path3[512];
    sprintf_s(path3, "%s\\skia\\out\\Release-x64\\skia.lib", pasta);

    if (FileExists(path3)) {
        passo = 3;
    }
    }
    if (passo == 3) {
        prontoParaProximo = false;
        {
            std::lock_guard<std::mutex> trava(logMutex);
            etapaAtual = (lingua == 'p') ? "Baixando Git..." : "Downloading Git...";
        }
        std::string gitCmd = "cmd.exe /c curl -L -o \"" + p + "\\Git.7z.exe\" https://github.com/git-for-windows/git/releases/download/v2.53.0.windows.3/PortableGit-2.53.0.3-64-bit.7z.exe && \"" + p + "\\Git.7z.exe\" -y -gm2 -InstallPath=\"" + p + "\" 2>&1";
        ExecutarComLog(gitCmd);
        prontoParaProximo = true;
        if (prontoParaProximo) passo = 4;
    }
    if (passo == 4) {
        prontoParaProximo = false;
        {
            std::lock_guard<std::mutex> trava(logMutex);
            etapaAtual = (lingua == 'p') ? "Baixando Ninja..." : "Downloading Ninja...";
        }
        std::string Ninja = "cmd.exe /c \"mkdir \"" + p + "\\ninja\" && curl -fL -k -o \"" + p + "\\ninja-win.zip\" https://github.com/ninja-build/ninja/releases/download/v1.13.1/ninja-win.zip && tar -xf \"" + p + "\\ninja-win.zip\" -C \"" + p + "\\ninja\" && tar -xf \"" + p + "\\ninja-win.zip\" -C \"" + p + "\\Cmake\\bin\" && del \"" + p + "\\ninja-win.zip\"";
        ExecutarComLog(Ninja);
        prontoParaProximo = true;
        if (prontoParaProximo) passo = 5;
    }
    if (passo == 5) {
        prontoParaProximo = false;
        {
            std::lock_guard<std::mutex> trava(logMutex);
            etapaAtual = (lingua == 'p') ? "Clonando repositorio Github..." : "Cloning Github repository...";
        }
        std::string install = "cmd.exe /c \"cd /d \"" + p + "\" && \"" + p + "\"\\PortableGit\\bin\\git.exe clone --recursive --progress https://github.com/aseprite/aseprite.git && cd aseprite && \"" + p + "\"\\PortableGit\\bin\\git.exe pull && \"" + p + "\"\\PortableGit\\bin\\git.exe submodule update --init --recursive 2>&1";
        ExecutarComLog(install);
        prontoParaProximo = true;
        if (prontoParaProximo) passo = 6;
    }
    if (passo == 6) {
        {
            std::lock_guard<std::mutex> trava(logMutex);
            etapaAtual = (lingua == 'p') ? "Compilando..." : "Compilando...";
        }
        std::string final = "call \"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\Common7\\Tools\\VsDevCmd.bat\" -arch=x64 && cd /d \"" + p + "\\aseprite\" && mkdir build && cd build && \"" + p + "\\Cmake\\bin\\cmake.exe\" -DCMAKE_BUILD_TYPE=RelWithDebInfo -G Ninja -DLAF_BACKEND=skia -DSKIA_DIR=\"" + p + "\"\\skia -DSKIA_LIBRARY_DIR=\"" + p + "\"\\skia\\out\\Release-x64 -DSKIA_LIBRARY=\"" + p + "\"\\skia\\out\\Release-x64\\skia.lib .. && \"" + p + "\"\\ninja\\ninja.exe aseprite 2>&1";
        ExecutarComLog(final);
        prontoParaProximo = true;
        if (prontoParaProximo) passo = 7;
        processandoOtimizacao = false;
    }
    if (passo == 7) pagina = 2;
    {
        std::lock_guard<std::mutex> trava(logMutex);
        etapaAtual = "";
    }
}
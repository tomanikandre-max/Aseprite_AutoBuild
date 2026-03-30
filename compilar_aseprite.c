#include <stdio.h>
#include <Windows.h>
int main(){
    char lingua=' ';
    char path[MAX_PATH];
    char comando[MAX_PATH + 300];
    int comando2;
    GetCurrentDirectory(MAX_PATH, path);
    MessageBox(NULL, "por favor execute como adiminitrador\ncaso contrario nao vai funcionar", "Aviso", MB_OK);
    MessageBox(NULL, "do you speak\nvoce fala:\nenglish(e)\nportugues(p)", "lingua", MB_OK);
    printf("lingua: ");
    scanf(" %c", &lingua);
    if(lingua=='p' || lingua=='P'){
        MessageBox(NULL, "Vai demorar\naguarde.", "Aviso", MB_OK);
    }
    else{
        MessageBox(NULL, "It will take a while\nplease wait.", "Warning", MB_OK);
    }
    system("git clone --recursive https://github.com/aseprite/aseprite.git");
    system("cd aseprite && git pull && git submodule update --init --recursive");
    system("cls");
    printf("gerando a build...");
    sprintf(comando, "call \"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\Common7\\Tools\\VsDevCmd.bat\" -arch=x64 && cd aseprite && mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo -G Ninja -DLAF_BACKEND=skia -DSKIA_DIR=\"%s\"\\skia -DSKIA_LIBRARY_DIR=\"%s\"\\skia\\out\\Release-x64 -DSKIA_LIBRARY=\"%s\"\\skia\\out\\Release-x64\\skia.lib .. && \"%s\"\\ninja\\ninja.exe aseprite", path, path, path, path);
    comando2 = system(comando);
    if(lingua=='p' || lingua=='P'){
    if(comando2==0){
        MessageBox(NULL, "Compilacao\nconcluida!!", "sucesso", MB_OK);
    }
    else{
        MessageBox(NULL, "erro impediu a compilacao", "erro", MB_OK);
    }
}
    else{
            if(comando2==0){
        MessageBox(NULL, "success", "success", MB_OK);
    }
    else{
        MessageBox(NULL, "error", "error", MB_OK);
    }
    }
    system("pause");
}

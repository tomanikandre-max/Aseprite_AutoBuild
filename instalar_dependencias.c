#include <stdio.h>
#include <windows.h>
int main(){
    char eng=' ';
    char seila=' ';
    MessageBox(NULL, "por favor execute como adiminitrador\ncaso contrario nao vai funcionar", "Aviso", MB_OK);
    MessageBox(NULL, "Voce fala:\ndo you speak:\nportugues(p)\nenglish(e)\n", "lingua", MB_OK);
    printf("lingua: ");
    scanf(" %c", &eng);
    if(eng=='p' || eng=='P'){
    MessageBox(NULL, "instale o Cmake...\n", "dependencias", MB_OK);
}
else{
    MessageBox(NULL, "install the Cmake...\n", "Cmake", MB_OK);
}
    system("pause");
    system("curl -L -o cmake-3.31.11-windows-x86_64.msi https://github.com/Kitware/CMake/releases/download/v3.31.11/cmake-3.31.11-windows-x86_64.msi");
    system("mkdir cmake");
    system("move \"cmake-3.31.11-windows-x86_64.msi\" \"cmake\\\"");
    system(".\\cmake\\cmake-3.31.11-windows-x86_64.msi");
    system("cls");
    if(eng=='p' || eng=='P'){
    MessageBox(NULL, "instale o Visual Studio e marque:\nDesenvolvimento para desktop com C++\nSdks do Windows 10 ou 11\n", "No Visual Studio", MB_OK);
    }
    else{
        MessageBox(NULL, "Install Visual Studio and check:\nDesktop development with C++\nWindows 10 or 11 SDKs\n", "In Visual Studio", MB_OK);
    }
    system("pause");
    system("curl -L -o vs_community.exe https://aka.ms/vs/17/release/vs_community.exe");
    system("mkdir Visual_Studio");
    system("move \"vs_Community.exe\" \"Visual_Studio\\\"");
    system(".\\Visual_Studio\\vs_Community.exe");
    system("cls");
    if(eng=='p' || eng=='P'){
    printf("voce marcou as opcoes indicadas?(s/n): ");
    scanf(" %c", &seila);
    }
    else{
    printf("You selected the indicated options?(s/n): ");
    scanf(" %c", &seila);
    }
    system("cls");
    if(eng=='p' || eng=='P'){
    if(seila=='s' || seila=='S'){
        printf("vamos parea o proximo passo!!\n");
    }
    else{
        printf("e obrigatorio, se der erro a culpa nao e minha\n");
    }
    system("pause");
    system("cls");
}
    else{
            if(seila=='y' || seila=='Y'){
        printf("Let's move on to the next step!!\n");
    }
    else{
        printf("It's mandatory; if there's an error, it's not my fault.\n");
    }
    }
    system("pause");
    system("cls");
    if(eng=='p' || eng=='P'){
    MessageBox(NULL, "instale o git\n", "Git", MB_OK);
    }
    else{
        MessageBox(NULL, "install git...\n", "Git", MB_OK);
    }
    system("pause");
    system("curl -L -o Git-2.53.0.2-64-bit.exe https://github.com/git-for-windows/git/releases/download/v2.53.0.windows.2/Git-2.53.0.2-64-bit.exe");
    system("mkdir Git");
    system("move \"Git-2.53.0.2-64-bit.exe\" \"Git\\\"");
    system(".\\Git\\Git-2.53.0.2-64-bit.exe");
    system("cls");
    system("mkdir ninja");
    system("cd ninja && curl -L -o ninja.zip https://github.com/ninja-build/ninja/releases/download/v1.13.2/ninja-win.zip && tar -xf ninja.zip && del ninja.zip");
    system("mkdir skia");
    system("cd skia && curl -L -o skia.zip https://github.com/aseprite/skia/releases/download/m124-08a5439a6b/Skia-Windows-Release-x64.zip && tar -xf skia.zip && del skia.zip");
    if(eng=='p' || eng=='P'){
    MessageBox(NULL, "agora reinicie o pc\ne execute o compilar_aseprite.exe\n", "sucesso", MB_OK);
    }
    else{
    MessageBox(NULL, "Now restart your PC\nand run compilar_aseprite.exe.\n", "success", MB_OK);
    }
    system("pause");
}

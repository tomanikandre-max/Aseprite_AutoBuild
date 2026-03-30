# 🚀 Aseprite Auto-Compilador (C)

Este é um automatizado feito em **C** para facilitar a construção oficial do Aseprite no Windows. Ele configura todas as dependências complexas (Skia e Ninja) de forma "blindada".

### 💡 O que este projeto faz?
Compilar o Aseprite manualmente é famoso por dar muitos erros, principalmente com a biblioteca **Skia**. Este script resolve isso:

*   Baixa automaticamente a versão correta do **Skia (M102)** pré-compilada.
*   Configura o **Ninja** e o **CMake** sem que você precise mexer em variáveis de ambiente.
*   Clona a versão mais recentev **1.3.16** e realiza o build completo.

### 🛠️ Requisitos
*   **Windows 10 ou 11 x64**.
*   **Visual Studio 2022 Community** instalado no caminho padrão (`C:\Program Files`).
*   Conexão com a internet.

### 🚀 Como usar:
1. Vá na aba **Releases** aqui no GitHub e baixe o arquivo `.zip` ou baixe o código fonte e use o compilador que prefere para compilar.
2. Extraia tudo para uma pasta na sua Área de Trabalho.
3. Clique com o botão direito em `instalar_dependencias.exe` e selecione **Executar como Administrador**.
4. Siga as instruções e, ao final, **reinicie o seu computador**.
5. Execute o `compilador_aseprite.exe` para iniciar a geração do `aseprite.exe`.

### 📂 Onde encontro o programa pronto?
Após o término da compilação, o executável estará em:
`pasta_do_projeto\aseprite\build\bin\aseprite.exe`

---

### 🧑‍💻 Sobre o Autor
Sou um desenvolvedor de 11 anos apaixonado por **C** e automação de sistemas. Criei este instalador para ajudar artistas e desenvolvedores a terem acesso ao Aseprite através da compilação oficial de forma simples e rápida!# Aseprite_AutoBuild

# 🆘 Guia de Ajuda e Solução de Problemas



---

## 1. Guia de Instalação (O Arquivo ZIP)

O seu projeto é empacotado como um **Módulo Magisk** para garantir a injeção "systemless" no sistema.

### Pré-requisitos
* Um dispositivo Android com **Bootloader Desbloqueado**.
* O framework **Magisk** instalado e funcionando (ele fornece o binário `su`).

### Processo de Instalação
O arquivo final do módulo é um pacote ZIP: `AOSP-ROOT-TOOLS.zip`.

1.  **Transferência:** Transfira o arquivo `AOSP-ROOT-TOOLS.zip` (que você compilou) para o armazenamento interno do seu dispositivo.
2.  **Instalação via Magisk Manager:**
    * Abra o aplicativo **Magisk Manager**.
    * Vá para a seção **Módulos**.
    * Selecione **Instalar do armazenamento** e navegue até o `AOSP-ROOT-TOOLS.zip`.
    * O Magisk executará o seu script `customize.sh` para copiar os binários.
3.  **Reinicialização:** Após a instalação bem-sucedida, o Magisk pedirá para **Reiniciar**. Esta etapa é **obrigatória** para que o seu script de serviço (`.rc`) e os seus binários (`bootctl_mod`) sejam carregados no sistema de inicialização com permissões de root e as regras SELinux customizadas.

---

## 2. Requisitos de Compilação (Entendendo as Ferramentas)

Seu projeto tem duas partes que exigem ambientes de compilação **diferentes**:

### A. Compilação dos Binários de Baixo Nível (C++)

*Isso se aplica a `bootctl_mod.cpp` e `su_simple.cpp`.*

**Ferramenta Necessária: Ambiente de Build AOSP (ou NDK Avançado)**

Você **NÃO PODE** usar apenas o Android Studio para compilar esses binários. Eles dependem de bibliotecas e cabeçalhos internos do Android, como o **Hardware Abstraction Layer (HAL)**.

1.  **Ambiente:** Você deve usar uma máquina Linux (Ubuntu, Debian, etc.) com o **ambiente de compilação do AOSP** configurado.
2.  **Processo:** Use o arquivo `Android.bp` junto com os comandos de build do AOSP (`m <nome_do_módulo>`). Este processo garante que o binário seja compilado de forma estática, incluindo todas as dependências do HAL.

### B. Compilação do Aplicativo de Monitoramento (Kotlin/Java)

*Isso se aplica a `MainActivity.kt` e `activity_main.xml`.*

**Ferramenta Necessária: Android Studio**

O aplicativo de interface (UI) é um projeto Android padrão.

1.  **Ambiente:** Use o **Android Studio** com o projeto aberto.
2.  **Processo:** O Android Studio usa o sistema **Gradle** (`build.gradle.kts`) para compilar e empacotar o arquivo APK (`.apk`). Este aplicativo é usado apenas para se comunicar com os binários de baixo nível (que você compilou no Passo A).

---

## 3. Solução de Problemas Técnicos

### Problema: O Binário `bootctl_mod` Falha com "Permissão Negada"

**Causa:** É quase sempre uma falha de **SELinux**.

**Diagnóstico:**
1.  Instale um emulador de terminal (como Termux) no dispositivo.
2.  Execute `su` para obter root.
3.  Execute o comando de auditoria SELinux: `dmesg | grep 'avc: denied'`
4.  Procure a linha que lista o seu binário (`bootctl_mod`) e qual ação (`write`, `read`, `getattr`) está sendo negada em qual objeto (`block_device`, `boot_partition`).

**Ação:** Edite seu arquivo `aosp_root_tools.te` para incluir a permissão negada e reempacote o módulo ZIP.

### Problema: O Aplicativo Kotlin Trava ao Clicar no Botão

**Causa:** A chamada `Runtime.getRuntime().exec(arrayOf("su", "-c", ...))` falhou.

**Ação:**
1.  Verifique se o Magisk Manager está funcionando e se o binário `su` está no PATH do sistema.
2.  Teste manualmente: Abra um terminal e digite apenas `su -c id`. Se isso falhar, o problema está na sua solução de root, não no seu aplicativo.

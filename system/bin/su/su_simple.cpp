#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

// Função principal que tenta elevar as permissões
int main(int argc, char* argv[]) {
    // 1. Obter o UID (User ID) atual do processo
    uid_t current_uid = getuid();

    std::cout << "--- Binário SU Simples ---" << std::endl;
    std::cout << "UID atual do processo: " << current_uid << std::endl;

    // 2. Verificar se já somos root (Root tem UID 0)
    if (current_uid == 0) {
        std::cout << "Você já é o usuário Root. Execução permitida." << std::endl;
        // Se já for root, apenas continua ou executa um shell
    } else {
        std::cout << "Tentando obter permissões de Superusuário..." << std::endl;

        // 3. Tentar obter as permissões de Root
        // setuid(0) tenta mudar o User ID efetivo para 0 (Root)
        if (setuid(0) == 0) {
            std::cout << "SUCESSO! Permissões de Root obtidas." << std::endl;
        } else {
            // setuid(0) falhará se o binário não tiver sido executado com as capacidades necessárias (SELinux e Permissões de arquivo)
            perror("ERRO: Falha ao obter Root. Verifique SELinux e Capabilities.");
            return 1;
        }
    }

    // 4. Se o binário foi bem-sucedido, ele executa um shell (como /system/bin/sh)
    // Isso é o que a ferramenta 'su' faz: transforma a sua sessão em uma sessão de root.
    std::cout << "Iniciando shell com permissões de Root..." << std::endl;
    
    // O comando 'execl' substitui o processo atual (su) pelo shell.
    execl("/system/bin/sh", "sh", NULL);

    // Se o execl falhar, isso é um erro.
    perror("ERRO: Falha ao executar o shell.");

    return 0;
}

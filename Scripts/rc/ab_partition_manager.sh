#!/system/bin/sh

# Caminho para o seu binário de controle de boot
BOOTCTL_BIN="/system/bin/bootctl_mod"

echo "--- Gerenciador de Partições A/B AOSP-Root-Tools ---"

# 1. VERIFICAR SLOTS
# Usa o seu binário bootctl_mod para obter o slot ativo e o slot atualizável.
echo "1. Status Atual dos Slots:"
echo "------------------------------------------------"

# Slot Ativo (Onde o sistema está rodando agora)
ACTIVE_SLOT=$($BOOTCTL_BIN get-active-boot-slot)
echo "Slot Ativo (Rodando Agora): $ACTIVE_SLOT"

# Slot Inativo (Onde a próxima atualização seria instalada)
# O bootctl do AOSP pode não ter um comando 'get-inactive-boot-slot',
# então usamos a lógica para deduzir o slot oposto.
if [ "$ACTIVE_SLOT" == "a" ]; then
    INACTIVE_SLOT="b"
else
    INACTIVE_SLOT="a"
fi
echo "Slot Inativo (Alvo de Próxima Atualização): $INACTIVE_SLOT"

echo "------------------------------------------------"

# 2. DEFINIR O PRÓXIMO SLOT DE BOOT
# Esta é a principal função de baixo nível que um projeto de root manipula
# para garantir que a imagem de boot modificada seja carregada após a atualização OTA.

# Exemplo de lógica: se o usuário quiser que o sistema reinicie no Slot B na próxima vez.

if [ "$1" == "switch_to_b" ]; then
    echo "2. Solicitando Alternância para o Slot B..."
    # O comando set-active-boot-slot marca o slot 'b' como o alvo da próxima inicialização.
    RESULT=$($BOOTCTL_BIN set-active-boot-slot b)

    if [ $? -eq 0 ]; then
        echo "SUCESSO: O Slot B foi marcado para o próximo boot."
        echo "Você precisa REINICIAR o dispositivo para que a mudança ocorra."
    else
        echo "FALHA: Não foi possível marcar o Slot B. Erro: $RESULT"
    fi

fi

echo "--- Fim do Script ---"

# Exemplo de como rodar o script (após obter root):
# sh ab_partition_manager.sh switch_to_b

#!/system/bin/sh

# Ferramenta para ler propriedades do sistema (do binário /system/bin/getprop)
PROP_TOOL="/system/bin/getprop"

# A propriedade-chave que indica o estado do bootloader e da verificação.
# O valor '0' ou 'orange' geralmente indica desbloqueado/inseguro.
BOOT_STATE_PROP="ro.boot.flash.locked"
VERIFY_STATE_PROP="ro.boot.verifiedbootstate"

echo "--- Status de Desbloqueio do Bootloader ---"

# 1. Obter o valor da Propriedade de Bloqueio (Locked)
LOCKED_STATUS=$($PROP_TOOL $BOOT_STATE_PROP)

if [ "$LOCKED_STATUS" == "0" ]; then
    echo "STATUS DO BOOTLOADER: Desbloqueado (LOCKED=0)"
    echo "Acesso a modificações de baixo nível e fastboot é permitido."
elif [ "$LOCKED_STATUS" == "1" ]; then
    echo "STATUS DO BOOTLOADER: Bloqueado (LOCKED=1)"
    echo "Modificações na partição de boot serão rejeitadas."
else
    echo "ERRO: Não foi possível determinar a propriedade $BOOT_STATE_PROP"
fi

echo "----------------------------------------------"

# 2. Obter o estado de Verificação de Boot (Verified Boot)
VERIFY_STATUS=$($PROP_TOOL $VERIFY_STATE_PROP)

if [ "$VERIFY_STATUS" == "orange" ] || [ "$VERIFY_STATUS" == "yellow" ]; then
    echo "VERIFIED BOOT: WARNING (Orange/Yellow)"
    echo "O dispositivo está usando uma imagem de boot não oficial (customizada ou rooteada)."
elif [ "$VERIFY_STATUS" == "green" ]; then
    echo "VERIFIED BOOT: OK (Green)"
    echo "O dispositivo está usando uma imagem de boot oficial e não modificada."
fi

# A chave para o root: o binário Magisk (ou o seu su_simple)
# é injetado na imagem de boot (boot.img), o que causa o status "orange".

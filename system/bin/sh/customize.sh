# Esse é o script customize.sh, executado pelo Magisk durante a instalação.
# O Magisk fornece variáveis como $MODPATH, que aponta para a pasta
# onde seu módulo será instalado (/data/adb/modules/AOSP_ROOT_TOOLS).

# 1. Definições Iniciais
ui_print "- Configurando o módulo AOSP-Root-Tools..."

# 2. Definição da Arquitetura
# Verifica a arquitetura do dispositivo (arm64, x86, etc.).
# Você pode usar $ARCH para decidir qual binário C++ (bootctl_mod) instalar.
ui_print "- Arquitetura do dispositivo: $ARCH"

# 3. Criar e Copiar Binários Customizados (O Seu Trabalho!)

# Se o seu binário bootctl_mod estiver no seu zip em /system/bin/bootctl_mod
# O Magisk irá instalá-lo automaticamente, mas é sempre bom verificar.

# Garante que os caminhos existam dentro do seu módulo:
mkdir -p $MODPATH/system/bin

# Copia seu binário bootctl_mod (assumindo que ele foi compilado para a arquitetura correta)
ui_print "- Copiando binário bootctl_mod..."
# Você copiaria seu binário COMPILADO aqui, ex:
# cp $TMPDIR/seu_zip/binarios/bootctl_mod.$ARCH $MODPATH/system/bin/bootctl_mod

# 4. Injetar Scripts de Serviço e Política SELinux

# O Magisk tem um mecanismo "Systemless" para injetar arquivos .rc e .te
# Você copiaria o seu arquivo .rc (serviço) e .te (SELinux) para a pasta de injeção.
ui_print "- Injetando scripts de serviço e política SELinux..."
mkdir -p $MODPATH/init.d
cp $TMPDIR/seu_zip/init_scripts/aosp_root_tools.rc $MODPATH/init.d/

# 5. Definir Permissões
# Garante que seus binários sejam executáveis (permissão 755).
ui_print "- Definindo permissões..."
set_perm $MODPATH/system/bin/bootctl_mod 0 0 0755 u:object_r:system_file:s0

# 6. Finalização
ui_print "- Instalação concluída com sucesso. Reinicie o dispositivo."

exit 0

#include <iostream>
#include <string>

// Inclui a interface do HIDL (a camada do HAL)
#include <android/hardware/boot/1.0/IBoot.h>
#include <android/hardware/boot/1.0/types.h>

using ::android::hardware::boot::V1_0::IBoot;
using ::android::hardware::boot::V1_0::CommandResult;
using ::android::hardware::boot::V1_0::Slot;
using ::android::hardware::Return;
using ::android::sp;

// Função principal que executa a lógica
int main(int argc, char* argv[]) {
    // 1. Tenta obter o serviço HAL de Boot
    // O IBoot é a interface que foi definida no HIDL
    sp<IBoot> boot_hal = IBoot::getService();

    if (boot_hal == nullptr) {
        std::cerr << "ERRO: Não foi possível obter o serviço IBoot HAL." << std::endl;
        std::cerr << "O dispositivo não suporta a interface de boot 1.0 ou o serviço não está rodando." << std::endl;
        return 1;
    }

    std::cout << "Serviço IBoot HAL conectado com sucesso!" << std::endl;

    // 2. Chama a função getActiveBootSlot()
    // Esta chamada vai do seu código C++ -> através do HAL -> para o driver do Kernel
    Return<void> ret = boot_hal->getActiveBootSlot(
        [&](const CommandResult& result, Slot slot) {
            if (result.success) {
                // slot é uma string (ex: "a" ou "b")
                std::cout << "\nStatus de Partição:\n";
                std::cout << "-----------------------\n";
                std::cout << "Slot de Boot Ativo: " << slot.c_str() << std::endl;

                // Aqui você adicionaria lógica para alternar o slot, se fosse o caso.
            } else {
                std::cerr << "ERRO HAL: Falha ao obter o slot ativo. Mensagem: " << result.errMsg.c_str() << std::endl;
            }
        });

    if (!ret.isOk()) {
        std::cerr << "ERRO HIDL: Falha na comunicação com o serviço HAL. " << ret.description() << std::endl;
        return 1;
    }

    return 0;
}

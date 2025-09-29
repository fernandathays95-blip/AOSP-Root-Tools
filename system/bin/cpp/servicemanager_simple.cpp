#include <iostream>
#include <string>
#include <map>
#include <unistd.h>
#include <sys/types.h>

// SIMULAÇÃO: O Handle é um ID numérico que o Binder usa para identificar o serviço.
using ServiceHandle = int;

// SIMULAÇÃO: O ServiceManager mantém um mapa de nomes de serviços para seus Handles.
std::map<std::string, ServiceHandle> service_registry;
ServiceHandle next_handle = 100;

/**
 * Função principal do ServiceManager: Registra um serviço com um nome.
 * * No Android real, o 'service' seria um objeto Binder. Aqui, é apenas um int (Handle).
 */
void registerService(const std::string& name, ServiceHandle service) {
    if (service_registry.count(name)) {
        std::cout << "[ServiceManager] Aviso: Serviço '" << name << "' já registrado. Sobrescrevendo..." << std::endl;
    }
    service_registry[name] = service;
    std::cout << "[ServiceManager] SUCESSO: Serviço '" << name << "' registrado com Handle: " << service << std::endl;
}

/**
 * Função principal do ServiceManager: Localiza um serviço pelo nome.
 * * É assim que o seu app Android encontraria o HAL de Boot.
 */
ServiceHandle getService(const std::string& name) {
    if (service_registry.count(name)) {
        std::cout << "[ServiceManager] SUCESSO: Encontrado o Handle do serviço '" << name << "'." << std::endl;
        return service_registry[name];
    }
    std::cout << "[ServiceManager] ERRO: Serviço '" << name << "' não encontrado no registro." << std::endl;
    return 0; // 0 (NULL) indica falha
}

// --- Demonstração ---
int main() {
    std::cout << "--- ServiceManager Simples Iniciado (PID " << getpid() << ") ---" << std::endl;
    
    // 1. O Serviço HAL de Boot (Seu alvo) se registra
    std::string boot_hal_name = "android.hardware.boot@1.1::IBoot/default";
    registerService(boot_hal_name, next_handle++);

    // 2. Um serviço padrão do Android se registra
    std::string power_service_name = "android.os.IPowerManager";
    registerService(power_service_name, next_handle++);

    std::cout << "\n--- Teste de Chamada de Serviço (Binder) ---\n";

    // 3. O seu aplicativo de Root (ou o seu binário bootctl_mod) tenta encontrar o HAL:
    ServiceHandle hal_handle = getService(boot_hal_name);

    if (hal_handle > 0) {
        std::cout << "SUCCESS: O cliente pode agora se comunicar com o HAL de Boot através do Handle " << hal_handle << std::endl;
    }

    // 4. Uma chamada falha
    ServiceHandle fake_handle = getService("android.hardware.fake_service");
    
    return 0;
}

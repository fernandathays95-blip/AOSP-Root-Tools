# 🛠️ AOSP-Root-Tools

## Visão Geral do Projeto

O **AOSP-Root-Tools** é um kit de desenvolvimento de código aberto focado em engenharia de baixo nível no Android. Nosso objetivo é criar e analisar binários e serviços que interagem diretamente com o **Kernel** e o **Hardware Abstraction Layer (HAL)**.

Este repositório fornece a estrutura completa para o desenvolvimento de ferramentas customizadas, focando em modificações **"systemless"** (sem modificar a partição `/system` original) através de um **Módulo Magisk**.

---

## 🎯 Componentes Chave

| Módulo | Tipo | Função Primária | Localização de Exemplo |
| :--- | :--- | :--- | :--- |
| **`bootctl-mod`** | Binário C++ | Interage com o **HAL de Boot** para ler e definir o slot de boot (A/B). | `src/bootctl-mod/` |
| **`su_simple`** | Binário C++ | Simulação de um binário de **Superusuário** (`su`) para elevação de permissões de processo. | `src/su_simple/` |
| **`root_service`**| Scripts de Sistema | Scripts de inicialização (`.rc`) e regras de segurança **SELinux** (`.te`) para injeção de serviços de root. | `magisk-module/init.d/` |
| **`Root Monitor App`**| Aplicação Kotlin | Interface de usuário para executar comandos `bootctl-mod` via `su` e exibir status. | _(Fora deste repositório)_ |

---

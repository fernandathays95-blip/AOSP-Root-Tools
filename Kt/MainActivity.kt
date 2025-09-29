package com.aosp_root_monitor

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.TextView
import java.io.BufferedReader
import java.io.InputStreamReader

class MainActivity : AppCompatActivity() {

    private lateinit var bootSlotText: TextView
    private lateinit var logText: TextView
    private lateinit var switchButton: Button

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        bootSlotText = findViewById(R.id.text_boot_slot)
        logText = findViewById(R.id.text_log)
        switchButton = findViewById(R.id.button_switch_slot)

        // 1. Lógica para o Botão
        switchButton.setOnClickListener {
            // Verifica o slot ativo e tenta alternar
            val currentSlot = bootSlotText.text.toString().lowercase()
            val targetSlot = if (currentSlot == "a") "b" else "a"
            executeRootCommand("set-active-boot-slot $targetSlot")
        }

        // 2. Inicialização: Exibe o slot ativo ao carregar
        val currentSlot = executeRootCommand("get-active-boot-slot")
        if (currentSlot.startsWith("SUCCESS")) {
             // O Magisk ou seu bootctl_mod retorna o slot
            val slot = currentSlot.substringAfterLast(" ").trim().uppercase()
            bootSlotText.text = slot
            logText.text = "Slot de boot lido: $slot. Pronto para alternar."
        } else {
             bootSlotText.text = "ERRO"
             logText.text = "Erro ao ler slot: ${currentSlot}. Root necessário?"
        }
    }

    /**
     * FUNÇÃO CHAVE: Executa o comando de baixo nível (binário bootctl_mod)
     * Requer o binário 'su' para funcionar!
     */
    private fun executeRootCommand(command: String): String {
        val fullCommand = "bootctl_mod $command"
        val output = StringBuilder()

        try {
            // O binário 'su' é usado para elevar as permissões antes de executar seu binário.
            val process = Runtime.getRuntime().exec(arrayOf("su", "-c", fullCommand))

            // Lê a saída do seu binário C++ (bootctl_mod)
            val reader = BufferedReader(InputStreamReader(process.inputStream))
            var line: String?
            while (reader.readLine().also { line = it } != null) {
                output.append(line).append("\n")
            }
            process.waitFor()
            
            // Retorna o resultado para a UI (com um prefixo de sucesso para fácil análise)
            return "SUCCESS: $output" 

        } catch (e: Exception) {
            e.printStackTrace()
            // Retorna o erro se o binário 'su' não puder ser encontrado ou falhar
            return "FAILURE: ${e.message}"
        }
    }
}

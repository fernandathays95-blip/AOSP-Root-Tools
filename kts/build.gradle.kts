plugins {
    id("com.android.application")
    kotlin("android")
}

android {
    namespace = "com.exemplo.aosp_root_monitor"
    compileSdk = 34 // Compilar usando a API 34 (Android 14)

    defaultConfig {
        applicationId = "com.exemplo.aosp_root_monitor"
        minSdk = 29 // O app roda em dispositivos com API 29 (Android 10) ou superior
        targetSdk = 34 // O alvo de teste é a API 34
        versionCode = 1
        versionName = "1.0-root-monitor"

        // Para projetos de baixo nível, você pode precisar de flags de compilação C++
        // externalNativeBuild {
        //     cmake {
        //         cppFlags += ""
        //     }
        // }
    }

    buildTypes {
        release {
            isMinifyEnabled = true // Otimização de código
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
        }
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_1_8
        targetCompatibility = JavaVersion.VERSION_1_8
    }
    kotlinOptions {
        jvmTarget = "1.8"
    }
}

dependencies {
    // Bibliotecas Essenciais da UI (Interface do Usuário)
    implementation("androidx.core:core-ktx:1.13.1")
    implementation("androidx.appcompat:appcompat:1.7.0")
    implementation("com.google.android.material:material:1.12.0")
    implementation("androidx.constraintlayout:constraintlayout:2.1.4")

    // Dependências de Teste
    testImplementation("junit:junit:4.13.2")
    androidTestImplementation("androidx.test.ext:junit:1.2.1")
    androidTestImplementation("androidx.test.espresso:espresso-core:3.6.1")
}

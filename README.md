# 🌡️ Monitor de Temperatura e Umidade com ESP
Este projeto utiliza um microcontrolador **ESP32** para ler dados de um sensor de temperatura e umidade e exibe numa interface web em tempo real.
## Tecnologias e Componentes
 * **Microcontrolador:** ESP32-WROOM
 * **Sensor:** DHT11
 * **Linguagem:** C++, HTML e JavaScript
 * **Bibliotecas Principais:** DHT sensor library, Adafruit Unified Sensor
## Esquema de Ligação (Pinout)
| Componente | Pino do Sensor | Pino da ESP (GPIO) |
|---|---|---|
| **VCC** | 1 | 3.3V |
| **Dados** | 2 | GPIO 27 |
| **GND** | 4 | GND |
## Modos de Operação
O projeto possui três estados de funcionamento, indicados por LEDs coloridos:
 * 🔴 *Desligado:* O sensor não realiza leituras.
 * 🟢 *Ligado (Manual):* Leitura através de solicitação do usuario.
 * 🟡 *Automático:* O sistema monitora os níveis de 2 em 2 segundos.
## Circuito Atualizado (LEDs)
| Componente | Cor | Pino ESP (GPIO) |
|---|---|---|
| *LED 1* | Vermelho | GPIO 17 |
| *LED 2* | Verde | GPIO 18 |
| *LED 3* | Amarelo | GPIO 5 |
## Como usar
 1. **Instalação de Bibliotecas:**
    * Instale a extensão PlatformIO no VsCode
    * Adicione as bibliotecas no platform.ini
    * adafruit/DHT sensor library
    * adafruit/Adafruit Unified Sensor
 3. **Configuração do Código:**
   * Clone o repositório: git clone [https://github.com/Jorgehtg/PS-EletronJun]
   * Abra o arquivo main.cpp
   * No código, ajuste o nome e senha do wifi.
 3. **Upload:**
   * Conecte sua ESP via USB, selecione a placa e a porta corretas e clique em **Upload**.
4. **Ajuste no Index.html**
     *Substitua o codigo de ip no index.html pelo exibido no serial monitor.

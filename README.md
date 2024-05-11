# Lorawan-Network

- #### Configuração de gravação **ESP32C3**
	- Primeiro vá em **Arquivo -> Preferências**
	- Adicionar os link na aba "URLs do Gerenciador de Placas Adicionais":
		1. https://dl.espressif.com/dl/package_esp32_index.json
		2. https://resource.heltec.cn/download/package_heltec_esp32_index.json
	- Após isso vá em **Ferramentas**
	- Seleciona a porta e placa(Wireless Mini Shell) corretas e altere a opção **Upload Speed** para 112500

- **Após isso as configurações estão prontas**

- #### Modo de Bootloader
	- Primeiro fazemos as conexões de alimentação 
		- VCC -> 3V
		- GND - GND
	- Depois conectamos o TX e RX do gravador(FT232RL) no RX e TX do ESP respectivamente
		- RX -> TX
		- TX -> RX
	- Após isso conectamos o EN no RTS e DTR no GPIO9
		- EN -> RTS
		- GPIO9 -> DTR                                                                            

- #### Modo de execução
	- **Obs. A alimentação do gravador(FT232RL) e do ESP devem necessariamente ser distintas**
	- Conexões de alimentação
		- VCC - 3V
		- GND - GND
	- Conexões de envio e recebimento de dados(TX e RX)
		- TX -> RX
		- RX -> TX
	- Após isso conectamos o EN e GPIO9 no 3V
		- EN -> 3V
		- GPIO9 -> 3V
- # Pinout
![HT-CT62](https://github.com/PauloVGDS/Lorawan-Network/assets/122188615/25a5f814-eac0-40c4-a5cb-483e5455ce16)

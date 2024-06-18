# Lorawan-Network

## Configuração Inicial
- #### Configuração ambiente 
	- Primeiro vá em **Arquivo -> Preferências**
	- Adicionar os link na aba "URLs do Gerenciador de Placas Adicionais":
	- E adicione o link: https://dl.espressif.com/dl/package_esp32_index.json
	- Ao adicionar o link vá na opção **GERENCIADOR DE PLACAS**
 	- Baixe as placas **esp32 por _Espressif Systems_** versão 3.0.1
	- Vá na opção **GERENCIADOR DE BIBLIOTECAS**
    	- E baixe a biblioteca **Heltec ESP32 Dev-Boards _por Heltec Automation_** versão 2.0.1

- #### Biblioteca externa MAX6675
	- Baixe o arquivo _.zip_ da biblioteca em: https://downloads.arduino.cc/libraries/github.com/adafruit/MAX6675_library-1.1.2.zip
 	- Em **Rascunho** vá na opção **Incluir Biblioteca**
  	- E selecione a opção **Adicionar Biblioteca .ZIP**
  	- Após isso procure o local de download do arquivo _.zip_ da biblioteca

- #### Configuração da Placa **ESP32C3**
	- Após isso vá em **Ferramentas**
	- Seleciona a porta e placa(Wireless Mini Shell)
 	- Altere a opção **Upload Speed**(caso for usar o Monitor Serial) para 112500
  	- Altere a opção **LoRaWan DevEUl** para _Generate By ChipiD_
  	- Altere a opção **LoRaWan Region** para _REGION_AU915_(ou para região de preferência)
  
**OBS: É fundamental usar as versões de bibliotecas e gerenciadores de placas mostradas**

- **Após isso as configurações estão prontas**
## Conexões
- #### Modo de Bootloader
	- Primeiro fazemos as conexões de alimentação 
		- VCC -> 3V
		- GND - GND
	- Depois conectamos o TX e RX do gravador(FT232RL) no RX e TX do ESP respectivamente
		- RX -> TX
		- TX -> RX
	- Após isso conectamos o EN no RST e DTR no GPIO9
		- EN -> RST
		- GPIO9 -> DTR


- #### Modo de execução
	- Conexões de alimentação
		- VCC - 3V
		- GND - GND
	- Conexões de envio e recebimento de dados(TX e RX)
		- TX -> RX
		- RX -> TX
	- Após isso conectamos o EN e GPIO9 no 3V
		- EN -> 3V
		- GPIO9 -> 3V
    
**OBS: A alimentação do gravador(FT232RL) e do ESP devem necessariamente ser distintas**
  
- ## Pinout
![HT-CT62](https://github.com/PauloVGDS/Lorawan-Network/assets/122188615/25a5f814-eac0-40c4-a5cb-483e5455ce16)

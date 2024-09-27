//inclusão da biblioteca que permite utilizar o LCD
#include <LiquidCrystal.h>

//atribuição das portas digitais do componente LCD em uma variável
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int ledGreen = 13; //atribuição da porta digital do LED em uma variável
int ledRed = 8; //atribuição da porta digital do LED em uma variável
int sensMov = 6; //atribuição da porta digital do Sensor de Movimento em uma variável
int estadoSensMov = 0; //definição do estado inicial do Sensor de Movimento
int echoPort = 10; //atribuição da porta digital do Sensor Ultrassônico em uma variável
int trigPort = 9; //atribuição da porta digital do Sensor Ultrassônico em uma variável
int duracao = 0; //declaração da variável que permitirá realizar o cálculo de reconhecimento da distância do Sensor Ultrassônico
int distancia = 0; //declaração da variável que irá armazenar a distância identificada pelo Sensor Ultrassônico

void setup() {

  lcd.begin(16, 2);
  lcd.print("Lixeira Automatizada");
  pinMode(ledGreen, OUTPUT); //definindo o estado da variável ledGreen como OUTPUT
  pinMode(ledRed, OUTPUT); //definindo o estado da variável ledRed como OUTPUT
  pinMode(sensMov, INPUT); //definindo o estado da variável sensMov como INPUT
  pinMode(echoPort, INPUT); //definindo o estado da variável echoPort como INPUT
  pinMode(trigPort, OUTPUT); //definindo o estado da variável trigPort como OUTPUT
}

void loop() {
  
  estadoSensMov = digitalRead(sensMov);
  
  //estrutura condicional que irá operar de acordo com o estado do Sensor de Movimento, estabelecido pela variável estadoSensMov
  if (estadoSensMov == HIGH)
  {
    //se estadoSensMov for alto, o LED Verde será ativado e o LED Vermelho será desativado
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
    //junto com a ativação do LED Verde, será exibida a mensagem "Tampa Aberta!" no LCD
    lcd.clear();
    lcd.print("Tampa Aberta!");
  	delay(1000);
  }
  else
  {
    //se estadoSensMov for baixo, o LED Verde será desativado e o LED Vermelho será ativado
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, HIGH);
    //junto com a ativação do LED Vermelho, será exibida a mensagem "Tampa Fechada!" no LCD
    lcd.clear();
    lcd.print("Tampa Fechada!");
  	delay(1000);
  }
  
  //período de ativação do Sensor Ultrassônico
  digitalWrite(trigPort, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPort, LOW);
  
  duracao = pulseIn(echoPort, HIGH);
  
  //cálculo de identificação da distância do objeto identificado pelo Sensor Ultrassônico
  distancia = duracao*0.017;
  
  //estrutura condicional que irá operar de acordo com a distância identificada pelo Sensor Ultrassônico, estabelecido pela variável distancia
  if (distancia < 25) 
  {
    //se a distância entre o Sensor Ultrassônico e o objeto for menor do que 25cm, o LED Verde será desativado e o LED Vermelho será ativado
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, HIGH);
    //junto com a ativação do LED Vermelho, será exibida a mensagem "Lixeira Cheia!" no LCD
    lcd.clear();
    lcd.print("Lixeira Cheia!");
  	delay(1000);
  }
  
}
#include <LiquidCrystal.h>

// Inicializa a biblioteca de LCD com os pinos usados no Arduino
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int ledVermelho = 2;
const int ledAmarelo = 3;
const int ledVerde = 4;
const int pinoBotao = 5;

unsigned long tempoInicial;
unsigned long tempoDeReacao;
bool esperarPressionar = false;

// Custom characters for progress bar
byte customChar[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

void setup() {
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(pinoBotao, INPUT_PULLUP);
  
  lcd.begin(16, 2);
  lcd.createChar(0, customChar);
  
  telaInicial();
  delay(2000);
  lcd.clear();
  
  iniciarSequencia();
}

void loop() {
  if (esperarPressionar && digitalRead(pinoBotao) == LOW) {
    tempoDeReacao = millis() - tempoInicial;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tempo de Reacao:");
    lcd.setCursor(0, 1);
    lcd.print(tempoDeReacao);
    lcd.print(" ms");
    esperarPressionar = false;
    delay(5000); // Mostra o tempo por 5 segundos antes de reiniciar a sequência
    lcd.clear();
    iniciarSequencia();
  }
}

void telaInicial() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Teste de Reacao");
  lcd.setCursor(0, 1);
  lcd.print("Formula E");

  // Animação de barra de progresso
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, 1);
    lcd.write(byte(0));
    delay(100);
  }
}

void iniciarSequencia() {
  // Desligar todos os LEDs no início da sequência
  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVerde, LOW);

  // Contagem regressiva com LEDs, LCD e barras de progresso
  digitalWrite(ledVermelho, HIGH);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Aguarde:");
  lcd.setCursor(0, 1);
  lcd.print("3 ");
  exibirBarraProgresso(0);
  delay(1000);
  
  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledAmarelo, HIGH);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Aguarde:");
  lcd.setCursor(0, 1);
  lcd.print("2 ");
  exibirBarraProgresso(1);
  delay(1000);
  
  digitalWrite(ledAmarelo, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Aguarde:");
  lcd.setCursor(0, 1);
  lcd.print("1 ");
  exibirBarraProgresso(2);
  delay(1000);
  
  // Início do teste de reação após a contagem regressiva
  digitalWrite(ledVerde, HIGH);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pressione o botao!");
  tempoInicial = millis();
  esperarPressionar = true;
}

void exibirBarraProgresso(int etapa) {
  for (int i = 0; i <= etapa; i++) {
    lcd.setCursor(2 + i, 1);
    lcd.write(byte(0));
  }
}

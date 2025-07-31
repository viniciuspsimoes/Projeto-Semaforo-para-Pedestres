#include <LiquidCrystal_I2C.h>
#include <stdio.h>
#include <time.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

#define red 2
#define verde 0
#define amarelo 4
#define botao 17
#define buzzer 19
#define pedred 5
#define pedverde 18
#define ledmulta 15
#define botaomulta 16

void limpalinha(int x){

lcd.setCursor(0,x);
lcd.println("                  ");
lcd.setCursor(0,x);
//
}

/*void contagem( int x, int regress, int t ){

  if((millis()-t>1000) && (regress>=0)){

    limpalinha(2);
    lcd.print("tempo = "); lcd.print(regress);
    regress--;
    t=millis();
  }

  if( regress == 0 ){ limpalinha(x); }

  contagem(x, regress, t);
}
*/

void setup() {
  // put your setup code here, to run once:
  srand(time(NULL));
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");

  pinMode(botao, INPUT_PULLUP);
  pinMode(verde,OUTPUT);
  pinMode(red,OUTPUT);
  pinMode(amarelo, OUTPUT);
  pinMode(pedred,OUTPUT);
  pinMode(pedverde, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(botaomulta, INPUT_PULLUP);
  pinMode(ledmulta, OUTPUT );

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Semaforo\nIniciado");
  delay(2500);
  lcd.clear();

  digitalWrite(red, LOW);
  digitalWrite(amarelo, LOW);
  digitalWrite(verde, LOW);
  digitalWrite(pedred, LOW);
  digitalWrite(pedverde, LOW);
  digitalWrite(ledmulta, LOW);

// Exibe inicialmente 0 multas
  lcd.setCursor(0, 3);  // Linha onde as multas serão exibidas
  lcd.print("Numero de multas: 0");
  
}

//use TONE para tocar o buzzer 

void loop() {
  static unsigned int t;
  static int modo=0;
  static unsigned int multa=0;
  static int multe=0;
  static int liberabotao=true;
  static bool bmulta_ultimo=HIGH; //Inicia como se o botao estivesse solto, pega o valor do ultimo botao
  static unsigned int regress=0;
  static int l;

if((millis()-t>5000) && modo==0 ){ //verde carros
    
    digitalWrite(pedverde, LOW);
    digitalWrite(red, LOW);
    digitalWrite(ledmulta, LOW);

    digitalWrite(pedred, HIGH);
    digitalWrite(verde, HIGH);
    
    digitalWrite(buzzer, LOW);
    tone(buzzer,0);
      
      lcd.clear();
      limpalinha(0);
      lcd.print("Semaforo fechado");

      limpalinha(1);
      lcd.print("Aperte o bota para ");

      limpalinha (2);
      lcd.print("travessia");
      
      limpalinha(3);
      lcd.print("Numero de multas: ");
      lcd.print(multa);

      modo=1;
      multe=0;
      t=millis();

    }

if((!digitalRead(botao)) && (millis()-t>1000) && modo==1 ){ //amarelo carros

    digitalWrite(verde, LOW);
    digitalWrite(amarelo, HIGH);
    digitalWrite(buzzer, LOW);
    
    //lcd.print("Atencao: travessia em tempo");
    limpalinha(0);
    lcd.print("Semaforo fechando");
    limpalinha(1);
    lcd.print("travessia em:");
    //lcd.print("travessia em ");
    modo=2;
    l=2;
    regress=5;

    t=millis();

  }
 

    if( (millis()-t>5000) && modo==2 ){ //vermelho carros

      digitalWrite(amarelo, LOW);
      digitalWrite(red, HIGH);

      digitalWrite(pedred, LOW);
      digitalWrite(pedverde, HIGH);

      limpalinha(0);
      lcd.print("Semaforo aberto");
      
      limpalinha(1);
      lcd.print("Atravesse");
      
      tone(buzzer,800);

        

    t=millis();
      modo=0;
      multe=1;

      l=2;
      regress=10;
    }



if((millis()-t>1000) && (regress>0) && (modo==0 || modo==2) ) {  //contagem regressiva

    limpalinha(l);
    lcd.print("tempo = "); lcd.print(regress);
    regress--;
    t=millis();

     if( regress == 0 ){ limpalinha(l); t=millis()+5000;} 
  }



 // Verifica o estado do botão de multa e incrementa a contagem
 if (digitalRead(red) == HIGH) {  // Funciona somente com semaforo fechado
     bool estado_bmulta = digitalRead(botaomulta);  // Variavel pra ler o estado atual do botão
  if (estado_bmulta == LOW && bmulta_ultimo == HIGH && liberabotao) {
    // botao pressionado
    digitalWrite(ledmulta, HIGH);  // Liga o LED 
    multa++;  // Incrementa o contador de multas

    // Atualiza o LCD
    lcd.setCursor(0, 3);  
    lcd.print("Numero de multas: ");
    lcd.print(multa);  // Exibe o número de multas atualizado
    Serial.print(multa); //multas exibidas no serial

    liberabotao = false;  // trava a contagem até ser liberado
  }

  if (estado_bmulta == HIGH) {
    // Botão solto
    liberabotao = true;
  }
digitalWrite(ledmulta, LOW);
  // reseta o botao pra rodar de novo
  bmulta_ultimo = estado_bmulta;
}

delay(10);
}

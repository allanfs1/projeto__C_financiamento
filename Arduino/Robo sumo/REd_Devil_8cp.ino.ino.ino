

#define switche_1 2
#define contEsquiva 50///Esquivar constante
#define  Desabilitar_Es 10////Desabilitar constante(Esquivar)
//---------------------------------------------------------------------------------------------------------------------------------------------
#include<QTRSensors.h>
int valor;
long tempoSet = 0;///Tempo millis()
//----------------------------------
unsigned long tempo;
boolean trava = true;
int cont = 0,cont2=0,cont3=0,velocidadePadrao = 1000; 
//-------------------------------
/*ultrassonico*/
boolean atack = true;
#define trig  A5
#define echo A4
int  CM;
float duracao;
//----------------------------
/*Motores child(1 e 2)*/
////QTR Analogicos//////
#define NumeroSensores 4
#define AmostraQRT 4
#define CMNC 5
//------------------------------
int delayIA=0;
/*SW 420) Modulo de ColisÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â£o*/
#define pinoSC 6
//-----------------------------
boolean  corrigir  = false;
// --- Mapeamento de Hardware ---
#define   dir_clk      4     //clock do registrador no digital  4
#define   dir_ser      8     //dados do registrador no digital  8
#define   dir_latch   12     //latch do registrador no digital 12
#define   dir_en       7     //enable do registrador no digital 7
#define   pwmMotor1       11     //pwm motor1
#define   pwmMotor4        5     //pwm motor4
//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
////////Cetagem dos Pinos Analogicos//////
QTRSensorsAnalog QRT6((unsigned char[]) {
  0, 1, 2, 3
}, NumeroSensores, AmostraQRT, CMNC);
unsigned int MatrizSensores[NumeroSensores];
//-------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);///Serial port//
  pinMode(switche_1, INPUT);
  pinMode(13, OUTPUT); //--Led--//
  pinMode(trig,OUTPUT); ////E a saida para ultassonico
  pinMode(echo,INPUT);  
  ///-----------------------------------------------------------------------------------------////////////////////////////////
  /*Pinos l293d*/
  pinMode(dir_clk,   OUTPUT);    //saÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­da para clock
  pinMode(dir_ser,   OUTPUT);    //saÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­da para dados
  pinMode(dir_latch, OUTPUT);    //saÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­da para latch
  pinMode(dir_en,    OUTPUT);    //saÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­da para enable
  pinMode(pwmMotor1,     OUTPUT);    //saÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­da para pwm motor1
  pinMode(pwmMotor4,     OUTPUT);    //saÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­da para pwm motor4
  digitalWrite(dir_en, LOW);
  //-------------------------------------------------------------------------------------------------------------------------
  // --- Calibramentos dos QTR8 Analogicos---
  QTR_analogico_calibra();
}

// --- ProtÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â³tipo das FunÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â§ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Âµes Auxiliares ---
void EviarComandos0b (unsigned char value);   //FunÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â§ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â£o para enviar o byte para saÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­da do registrador l293d
int Dados_SW420(int sn);
unsigned long Ultrassonico(unsigned long CM);
//-------------------------------------------------------------------------------------------------------------------

void loop() {
  // put your main code here, to run repeatedly:
  /*SW 420) Modulo de ColisÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â£o*/
  /*Modo para desligar e ligar o Carrinho*/

  valor = digitalRead(switche_1);
  if (valor == LOW) {
    //  Serial.println("ligado");
    if ( millis() - tempoSet < 5000 ) {
      digitalWrite(13, HIGH);
      Parar_Motores();
      // Serial.println("Menor que 5000");
    }

    if ( millis() - tempoSet > 5000) {
      QTR_analogicoLoop();///Chamar QTR 8 ///
      digitalWrite(13, LOW);
      // Serial.println("Maior que 5000");
    }
    if ( millis() - tempoSet >= 10000000) { ///1 Hora
      tempoSet = millis();

    }

  }

  else {
    Parar_Motores();
    tempoSet = millis();
    // Serial.println("desligado");
  }

}


// --- Desenvolvimento das FunÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â§ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Âµes Auxiliares l293d---
void EviarComandos0b(unsigned char value)
{
  boolean verify;                  //bit de controle

  digitalWrite(dir_latch, LOW);    //desliga latch
  digitalWrite(dir_clk,   LOW);    //desabilita o clock

  for (unsigned char i = 0x0; i < 0x08; i++) //loop finito para enviar os 8 bits
  {
    digitalWrite(dir_clk, LOW);   //clock em low

    if (value & (1 << i)) verify = HIGH;
    else verify = LOW;

    digitalWrite(dir_ser, verify); //Habilita saÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â­da de dados conforme condiÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â§ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â£o acima
    digitalWrite(dir_clk, HIGH);
  }

  digitalWrite(dir_clk, LOW);
  digitalWrite(dir_latch, HIGH);
}

////Motores Shild////
void para_frente(int velocidadeX) {
  analogWrite(pwmMotor1, velocidadeX);  //*\ Motor M1*/
  analogWrite(pwmMotor4, velocidadeX);  //*\ Motor M2*/
  EviarComandos0b(0b10101100);
}

void para_traz(int velocidadeX) {
  analogWrite(pwmMotor1, velocidadeX);  //*\ Motor M1*/
  analogWrite(pwmMotor4, velocidadeX);  //*\ Motor M2*/
  EviarComandos0b(0b01010011);
}
void girar_esquerda(int velocidadeX) {
  analogWrite(pwmMotor1,  velocidadeX);  //*\ Motor M1*/
  analogWrite(pwmMotor4,  velocidadeX);  //*\ Motor M2*/
  EviarComandos0b(0b00100010);
}

void girar_direita(int velocidadeX) {
  analogWrite(pwmMotor1,  velocidadeX);  //*\ Motor M1*/
  analogWrite(pwmMotor4,  velocidadeX);  //*\ Motor M2*/
  EviarComandos0b(0b11011101);
}


void Parar_Motores() {
  analogWrite(pwmMotor1, 0xFF);  //*\ Motor M1*/
  analogWrite(pwmMotor4, 0xFF);  //*\ Motor M2*/
  EviarComandos0b(0b11111111);
}

/*QTR calibracao*/
void QTR_analogico_calibra() {
  Parar_Motores();

  Serial.println("Iniciando Calibracao");
  /*QTR calibracao e Movimentacao dos Motores 1 e 2*/
  do {
    if ( millis() - tempoSet < 400) {
      girar_esquerda(1000);

    }

    if ( millis() - tempoSet > 400) {
      girar_direita(1000);
    }


    if ( millis() - tempoSet > 800) {
      tempoSet = millis();
      cont++;
      if (cont > 4)
        trava = false;
    }
    QRT6.calibrate();
  } while (trava == true);
  Parar_Motores();

  /*QTR calibracao*/
  for (int i = 0; i < NumeroSensores; i++) {
    Serial.print(QRT6.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();

  for (int i = 0; i < NumeroSensores; i++) {
    Serial.print(QRT6.calibratedMaximumOn[i]);
    Serial.print(' ');
  }

}

/*QTR calibracao qtr e Modo Ultrassonico*/
void QTR_analogicoLoop() {
  /*Modo Ultrassonico Chamar*/
  velocidadePadrao = 1000; //velocidade//
  ///////////////////////////////////////
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);
  float duracao = pulseIn(echo, HIGH);
  CM = microcegundos_CM(duracao);
  delay(5);
 // Serial.println(CM);
  //--------------------------------------------------------------------------------------------------------------------
  // read calibrated sensor values and obtain a measure of the line position from 0 to 5000
  // To get raw sensor values, call:
  //QRT6.read(MatrizSensores); //instead of unsigned int position = qtra.readLine(sensorValues);
  unsigned int valor;
  // QRT6.readLine(MatrizSensores);
  // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
  // 1000 means minimum reflectance, followed by the line position

  
  for (unsigned char i = 0; i < NumeroSensores; i++)
  {
    /*QTR condicionais*/
    //Serial.print(MatrizSensores[i]);
    //Serial.print('\t');
  }
   //Serial.println(); // uncomment this line if you are using raw values
  //Serial.println(position); // comment this line out if you are using raw values
  valor = QRT6.readLine(MatrizSensores);/*Ler dados dos QTR 8*/
  /*Condicoes if Ultrassonico */

  /*Atacar Alvo se for maior que CM(40)*/
    if(CM < 15 ) {
       Serial.println("\n\n Andar para frente (Atack)");
        para_traz(velocidadePadrao);
      

    }

    else { 
        girar_esquerda(velocidadePadrao);
        Serial.println("\n\n Girar em 360");
       
           
    }
    
 
  //--------------------------------------------------------------------------------------------------------------------
  ///////Fucoes condicionais////////
  /*QTR condicionais*/
   /*Atacar Alvo se for maior que CM(40)*/
  if(MatrizSensores[0] <= 700 || MatrizSensores[1] <= 700 || MatrizSensores[2] <= 700 || MatrizSensores[3] <=700  ) {
            velocidadePadrao = velocidadePadrao - 100;
             para_frente(velocidadePadrao);
           // Serial.print("para traz");
     
  }
     //else
      //para_frente(velocidadePadrao);
      
     
}
 
        /*Ultrassonico*/
  int microcegundos_CM(float microCM){
  return microCM / 58;
}





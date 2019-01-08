
#include <IRremote.h>
// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!




// Motor Shield L293D sem Biblioteca
// --- Mapeamento de Hardware ---
#define   dir_clk      4     //clock do registrador no digital  4
#define   dir_ser      8     //dados do registrador no digital  8
#define   dir_latch   12     //latch do registrador no digital 12
#define   dir_en       7     //enable do registrador no digital 7   ///motor 2 e pino (3),motor 3 e pino( 6) motor 4 e (5)
#define   pwmMotor1      11    //pwm motor1
#define   pwmMotor2     5   //pwm motor2


///Cariaveis Globais///
int aux,aux2;
//----------------------------------------

void sendCommand(unsigned char value); 

const int  RECV_PIN = A5;
IRrecv n1839b (RECV_PIN);
decode_results results;

void setup() { 

  Serial.begin(115200);  // set up Serial library at 115200 bps
  n1839b.enableIRIn(); // Inicializa o receptor IR  
  
  pinMode(dir_clk,   OUTPUT);    //saída para clock
  pinMode(dir_ser,   OUTPUT);    //saída para dados
  pinMode(dir_latch, OUTPUT);    //saída para latch
  pinMode(dir_en,    OUTPUT);    //saída para enable 
  pinMode(pwmMotor1,     OUTPUT);    //saída para pwm motor1
  pinMode(pwmMotor2,     OUTPUT);    //saída para pwm motor4
  digitalWrite(dir_en, LOW);   
  Serial.println("Tramicao Iniciar!");
  Parar_Motores();
 
}

void para_frente();
void para_traz();
void girar_esquerda();
void girar_direita();
void sendCommand(unsigned char value);


void loop() {
   

  if (n1839b.decode(&results))
  {
     n1839b.resume(); //Le o próximo valor
     aux = results.value;
     Serial.println(aux, HEX);
     
             ////Botao 2//
    if (aux == 0x4B1B){ //Verifica se a tecla 1 foi acionado
      para_frente();
    }


                      ////Botao 1
    if (aux == 0xFFFFD41F) { //Verifica se a tecla 2 foi acionada
     para_traz();
    }

   if(aux == 0xFFFFE57B)  //Verifica se a tecla 2 foi acionada
   Parar_Motores();

   ///Vira Para esquerda///
   if(aux == 0x3BFB)
   girar_direita();

   //vira para direita///
  if(aux == 0x1643)
  girar_esquerda();

  }
  
}


// --- Desenvolvimento das Funções Auxiliares ---
void sendCommand(unsigned char value)
{
    boolean verify;                  //bit de controle

    digitalWrite(dir_latch, LOW);    //desliga latch
    digitalWrite(dir_clk,   LOW);    //desabilita o clock
    
    for(unsigned char i=0x0; i<0x08; i++)    //loop finito para enviar os 8 bits
    {
       digitalWrite(dir_clk, LOW);   //clock em low
       
       if(value & (1<<i)) verify = HIGH;
       else verify = LOW;
       
       digitalWrite(dir_ser, verify); //Habilita saída de dados conforme condição acima
       digitalWrite(dir_clk, HIGH);
    } 
    
    digitalWrite(dir_clk, LOW); 
    digitalWrite(dir_latch, HIGH);
} 


void para_frente(){
analogWrite(pwmMotor1, 0xFF);  //*\ Motor M1*/
analogWrite(pwmMotor2, 0xFF);  //*\ Motor M2*/
sendCommand(0b10101100);
}

void para_traz(){
analogWrite(pwmMotor1, 0xFF);  //*\ Motor M1*/
analogWrite(pwmMotor2, 0xFF);  //*\ Motor M2*/ 
sendCommand(0b01010011);
}
void girar_esquerda(){
 
analogWrite(pwmMotor1, 0xFF);  //*\ Motor M1*/
analogWrite(pwmMotor2, 0xFF);  //*\ Motor M2*/ 
sendCommand(0b00100010);
}
void girar_direita() {
  
  analogWrite(pwmMotor1, 0xFF);  //*\ Motor M1*/
  analogWrite(pwmMotor2,  0xFF);  //*\ Motor M2*/
 sendCommand(0b11011101);
}

void Parar_Motores(){
analogWrite(pwmMotor1, 0xFF);  //*\ Motor M1*/
analogWrite(pwmMotor2, 0xFF);  //*\ Motor M2*/ 
sendCommand(0b11111111);
}








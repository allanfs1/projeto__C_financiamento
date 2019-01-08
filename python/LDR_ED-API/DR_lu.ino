#define LDR A5



int ldrval[10] = {0,0,0,0,0,0,0,0,0,0};
int corte= 800;
unsigned long deltat = 60000;//  Delta Tempo de um minuto(60 segundos)
unsigned long conttime = millis();

void atualiza_interval(bool start);
void atualiza_interval();
void send();/// Criar uma matriz

void setup() {
  Serial.begin(9600);
   atualiza_interval(true);
}

void loop() {
  atualiza_interval();
  send();
}

////// Gerador
void send(){
  Serial.print("[");
  for(int i = 0; i <=8; i++){
    Serial.print(ldrval[i]);Serial.print(',');
 
  }
  Serial.print(ldrval[9]);  Serial.println("]");

}

//?/Atualizar a posição ldrval[9] nove como 1/0

void atualiza_interval(bool start){
  int tmp;
  if(start == true){
    tmp = analogRead(LDR);
    if(tmp >= corte)
      ldrval[9] = 0;
    
    else
      ldrval[9] = 1;
    
    
  }
  
 atualiza_interval();
  
}

//?/Atualizar a posição do array nove como 1/0

void atualiza_interval(){
  if(millis() - conttime >= deltat){    
    conttime  = millis();
    for(int i = 0; i <= 8; i++)
      ldrval[i] = ldrval[i+1];
     
    int tmp = analogRead(LDR);  
    if(tmp >= corte)
      ldrval[9] = 0;
    
    else
      ldrval[9] = 1;
    
      
  }
  
}





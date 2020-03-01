//Proposta: Medição de caixa d'água, projeto nivel 
//Alunos: Diego F. Leal
/*
Medição de caixa d'água, pensamos em uma caixa com medidas de 300cm de altura,
300cm de largura e 300cm de profundidade, o que totalizará 27000 litros de capacidade,
o circuito é composto de um lcd 16x2 onde informará o volume de água na caixa, uma bomba
de emergencia simbolizado atravez de um motor cc, que em caso de o sistema de abastacimento
de água por alguma razão for interrompido, ele entrará em ação enchendo a caixa apartir
uma segunda fonte de abastecimento como por exemplo um poço artesiano. A medição será 
feita atravez de um sensor ultrasonico, 
*/

#include <LiquidCrystal.h> //incluindo a biblioteca para o LCD

#define CaixaLar 300.00 
#define CaixaProf 300.00
#define CaixaAlt 300.00 // definindo as medidade da caixa d'água
String texto1;
float distancia, capacidade;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void leitura();


void setup(){
  lcd.begin(16, 2);
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW); 
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  /*
  Iniciamos os pinos 8 e 13 em modo LOW pois não queremos que 
  a valvula solenoide nem a bomba d'água acionem no momento
  que ligamos o cirtcuito.
  */
}


void loop(){
  leitura();


  distancia = distancia/2; // Divide por 2 pois esse é o tempo da onda ir e voltar
  distancia = distancia*0.034029; // Multiplicamos por 0,034029 por causa da velocidade do som (d=v*t)
  capacidade = CaixaLar*CaixaProf*(CaixaAlt-distancia);
  delay(100);
  if (capacidade<25000000){
   digitalWrite(13, HIGH);
  }else{
    digitalWrite(13, LOW);
  }
  
  lcd.clear(); 
  lcd.setCursor(0, 0); //Posiciona o cursor na coluna 0, linha 0;
  lcd.print(capacidade/1000);//Envia a medição para o lcd já convertendo cm3 para litros
  lcd.print(" Litros");// Concatenamos para que facilite o entendimento da leitura
  lcd.setCursor(0, 1);
  lcd.print(texto1);
  if (capacidade>=25000000){
    texto1="CAIXA CHEIA";
  }
  if (capacidade<8000000){
    texto1="REDE EMERGENCIA";
  }  
  if (capacidade>16000000 && capacidade<25000000){
    texto1="REDE PRIMARIA";
  }  
  delay(100);
  
  
  if (capacidade<8000000){
    digitalWrite(8, HIGH);    

  }else if(capacidade>16000000)
    digitalWrite(8, LOW);

   
  /*controla o ligamento da bomba de emergêcia
  ligando em 8000 litros e desligando em 16000 litros
  mantando assim uma faixa de segurança emergencial de água
  até o retorno do funcionamento do abastecimento primário
    
  */
  
}


void leitura(){
  // função para o funcionamento correto do senso ultrassonico de 3 pinos.
  pinMode(7, OUTPUT); // Define o pino como saida
  digitalWrite(7, HIGH); // Manda um sinal de nível alto de 5 ms
  delayMicroseconds(5);
  digitalWrite(7, LOW);

  pinMode(7, INPUT); // Define o pino como entrada para fazer a leitura
  distancia = pulseIn(7, HIGH); // Lê o comprimento de onda em alta
}

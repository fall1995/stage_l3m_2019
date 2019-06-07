/* cablage des broches de la carte de puissance TB6612FNG vers la carte arduino */
#define PWMA D7
#define AIN1 D1
#define AIN2 D0
#define STBY D3

 
void setup()
{
  /* definition des broches de la carte de puissance en tant que sortie */
  pinMode(PWMA,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(STBY,OUTPUT);
  // Ouvre la voie série avec l'ordinateur
    Serial.begin(115200);
}
 
void loop() 
{
  Serial.println("Debut");
  delay(5000);
  digitalWrite(STBY,HIGH);
  Serial.println("STBY");
  delay(5000);
  analogWrite(PWMA,500); //0-1023
  Serial.println("PWMA");
  delay(5000);
  
  digitalWrite (AIN1,LOW);
  digitalWrite (AIN2,HIGH);
  Serial.println("Sens 1");
  delay(5000);
  
  digitalWrite(STBY,LOW);
  Serial.println("STBY LOW");
  delay(5000);

  digitalWrite (AIN1,HIGH);
  digitalWrite (AIN2,LOW);
  digitalWrite(STBY,HIGH);
  Serial.println("Sens 2");
  delay(5000);

  analogWrite(PWMA,750); //0-1023
  Serial.println("PWMA");
  delay(5000);
  
  analogWrite(PWMA,1000); //0-1023
  Serial.println("PWMA");
  delay(5000);
  
  digitalWrite(STBY,LOW);
  Serial.println("STBY LOW");
  delay(5000);
  
  /*startUp(); // on met la broche standby à HIGH
  goForward(50); // on avance avec une PWM de 30 pour les deux moteurs, donc on avance droit
  delay(5000); // on attend 5 secondes
  rotateRight(50); // on tourne a droite avec une pwm de 2*30 pour la roue gauche (moteur A) et de 30 pour la roue droite
  delay(5000); // on attend 2 secondes  
  rotateLeft(50); // on tourne a gauche avec une pwm de 30 pour la roue gauche et de 2*30 pour la roue droite
  delay(5000); // on attend 2 secondes
  shutDown(); // on met la broche standby à LOW, donc le moetr s'arrete
  startUp(); // on met la broche standby à HIGH
  goForward(50); // on avance avec une PWM de 30 pour les deux moteurs, donc on avance droit
  //goBackward(50); // on applique une PWD de 30 en ayant changé la polarité des tensions à appliquer aux moteurs pour faire tourner les moteurs dans le sens inverse
  delay(5000); // on attend 5 secondes
  shutDown(); // on arrete les moteurs avec broche standby à LOW*/
}


void startUp ()
{
  Serial.println("in startUp");
  digitalWrite(STBY,HIGH);
}

void shutDown ()
{
  Serial.println("in shutDown");
  digitalWrite(STBY,LOW);
}

void goForward (int pwm)
{
  Serial.println("in goForward");
  digitalWrite (AIN1,LOW);
  digitalWrite (AIN2,HIGH);
  analogWrite(PWMA,pwm);
    
}

void goBackward (int pwm)
{
  Serial.println("in goBackward");
  digitalWrite (AIN1,HIGH);
  digitalWrite (AIN2,LOW);
  analogWrite(PWMA,pwm);
     
}

void rotateRight (int pwm)
{
 Serial.println("in rotateRight");
 analogWrite(PWMA,2*pwm);
 
}

void rotateLeft (int pwm)
{
  Serial.println("in rotateLeft");
  analogWrite(PWMA,pwm);
     
}

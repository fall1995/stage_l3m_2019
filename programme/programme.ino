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
  startUp(); // on met la broche standby à HIGH
  goForward(30); // on avance avec une PWM de 30 pour les deux moteurs, donc on avance droit
  delay(5000); // on attend 5 secondes
  rotateRight(30); // on tourne a droite avec une pwm de 2*30 pour la roue gauche (moteur A) et de 30 pour la roue droite
  delay(2000); // on attend 2 secondes  
  rotateLeft(30); // on tourne a gauche avec une pwm de 30 pour la roue gauche et de 2*30 pour la roue droite
  delay(2000); // on attend 2 secondes
  shutDown(); // on met la broche standby à LOW, donc le moetr s'arrete
  startUp(); // on met la broche standby à HIGH
  goBackward(30); // on applique une PWD de 30 en ayant changé la polarité des tensions à appliquer aux moteurs pour faire tourner les moteurs dans le sens inverse
  delay(5000); // on attend 5 secondes
  shutDown(); // on arrete les moteurs avec broche standby à LOW
}


void startUp ()
{
  Serial.println("in startUp");
  digitalWrite(STBY,LOW);
}

void shutDown ()
{
  Serial.println("in shutDown");
  digitalWrite(STBY,HIGH);
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

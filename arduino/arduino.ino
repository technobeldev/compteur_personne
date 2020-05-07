int sensorpin1 = 0; 
int sensorpin2 = 1;
int val1 = 0;
int val2 = 0;
int level = 150; //set the good level of your sensor
int max_nbr_person = 3; // number of people max for a room
int green_led = 3;
int red_led = 4;

int nbr_person = 0;
int temp_in = 0;
int temp_out = 0;

void go(int temp){ //led switch
  if (temp == true){
    digitalWrite(green_led,HIGH);  
    digitalWrite(red_led,LOW);  
  }else{
    digitalWrite(red_led,HIGH);
    digitalWrite(green_led,LOW);
  }
}


void setup()
{
  Serial.begin(9600); 
  pinMode(green_led, OUTPUT);
  pinMode(red_led, OUTPUT);
  digitalWrite(green_led,HIGH);  
  digitalWrite(red_led,LOW);            
}
 
void loop()
{
  val1 = analogRead(sensorpin1); 
  val2 = analogRead(sensorpin2); 

  //in
  if (val1 > level && val2 <= level && temp_out == 0 && temp_in == 0){
    delay(50);
    val1 = analogRead(sensorpin1); 
    if (val1 > level){
      temp_in = 1;
    }
  }
  if (val1 < level && val2 < level && temp_in == 1){
    temp_in = 0;
    nbr_person++;
    Serial.println(nbr_person);
    if (nbr_person >= max_nbr_person){
      go(false);
    }else{
      go(true);
    }
  }

  //out
  if (val2 > level && val1 <= level && temp_in == 0 && temp_out == 0){
    delay(50);
    val2 = analogRead(sensorpin2); 
    if (val2 > level){
      temp_out = 1;
    }
  }
  if (val2 < level && val1 < level && temp_out == 1){
    temp_out = 0;
    if (nbr_person > 0){
      nbr_person--;
    }
    Serial.println(nbr_person);
    if (nbr_person >= max_nbr_person){
      go(false);
    }else{
      go(true);
    }
  }
 
  delay(10);                    
}

int sensorpin1 = 0; 
int sensorpin2 = 1;
int val1 = 0;
int val2 = 0;
int level = 100; //set the good level of your sensor
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

bool check_measure(int sensor){
  int average = 0;
  for (int i=0; i<10; i++){
    delay(5);
    int temp1 = analogRead(sensor);
    average+=temp1;
  }
  if ((average/10)>level){
    return true;
  }else{
    return false;
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
    if (check_measure(sensorpin1)){
      delay(1000);
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
    if (check_measure(sensorpin2)){
      delay(1000);
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
}

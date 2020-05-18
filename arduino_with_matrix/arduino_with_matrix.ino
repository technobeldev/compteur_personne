#include <LEDMatrixDriver.hpp>

int sensorpin1 = 0; 
int sensorpin2 = 1;
int val1 = 0;
int val2 = 0;
int level = 100; //set the good level of your sensor
int max_nbr_person = 2; // number of people max for a room

int nbr_person = 0;
int temp_in = 0;
int temp_out = 0;

const uint8_t LEDMATRIX_CS_PIN = 9;

// Number of 8x8 segments you are connecting
const int LEDMATRIX_SEGMENTS = 1;
const int LEDMATRIX_WIDTH    = LEDMATRIX_SEGMENTS * 8;

// The LEDMatrixDriver class instance
LEDMatrixDriver lmd(LEDMATRIX_SEGMENTS, LEDMATRIX_CS_PIN);


byte a[8]={
  B10000001,
  B01000010,
  B00100100,
  B00011000,
  B00011000,
  B00100100,
  B01000010,
  B10000001};

  byte a2[8]={ B00011000,
  B00100100,
  B01110010,
  B10111001,
  B10011101,
  B01001110,
  B00100100,
  B00011000};

byte b[8]={ B01100110,
  B01100110,
  B00000000,
  B00011000,
  B10011001,
  B11000011,
  B01100110,
  B00111100};

  byte b2[8]={ B00110000,
  B01100011,
  B11000011,
  B10011000,
  B10011000,
  B11000011,
  B01100011,
  B00110000};

void setup()
{
  Serial.begin(9600);
  // init the display
  lmd.setEnabled(true);
  lmd.setIntensity(10);   // 0 = low, 10 = high
  go(true);            
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

bool check_measure(int sensor){
  int average = 0;
  for (int i=0; i<20; i++){
    delay(5);
    int temp1 = analogRead(sensor);
    average+=temp1;
  }
  if ((average/20)>level){
    return true;
  }else{
    return false;
  }
}

void go(int temp){ //led_matrix switch
  if (temp == true){
    drawSprite( (byte*)&b2, 0, 0, 8, 8 );
    lmd.display();
  }else{
    drawSprite( (byte*)&a, 0, 0, 8, 8 );
    lmd.display();
  }
}

void drawSprite( byte* sprite, int x, int y, int width, int height )
{
  byte mask = B10000000;
  for( int iy = 0; iy < height; iy++ )
  {
    for( int ix = 0; ix < width; ix++ )
    {
      lmd.setPixel(x + ix, y + iy, (bool)(sprite[iy] & mask ));
      mask = mask >> 1;
    }
    mask = B10000000;
  }
}

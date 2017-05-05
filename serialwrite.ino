const int BTN_DELAY = 500;

int candle1 = 0x6F;
int candle2 = 0x72;
int candle3 = 0xFB;
int candle4 = 0x8D;

const int btnPin1 = 2;
const int btnPin2 = 4;
const int btnPin3 = 3;
const int btnPin4 = 5;

int btnState1;
int btnState2;
int btnState3;
int btnState4;

int curState1 = LOW;
int curState2 = LOW;
int curState3 = LOW;
int curState4 = LOW;

int delayMS = 500;

void setup() {

  pinMode(btnPin1, INPUT);
  pinMode(btnPin2, INPUT);
  pinMode(btnPin3, INPUT);
  pinMode(btnPin4, INPUT);
  
  Serial.begin(57600);

  delay(3000);

  //reset all to LOW
  remote(candle1, 0x4);
  remote(candle2, 0x4);
  remote(candle3, 0x4);
  remote(candle4, 0x4);
  
}

void loop() {

  btnState1 = digitalRead(btnPin1);
  btnState2 = digitalRead(btnPin2);
  btnState3 = digitalRead(btnPin3);
  btnState4 = digitalRead(btnPin4);
  
  if(btnState1 == HIGH) {
    if(curState1 == LOW) {
      remote(candle1, 0x5);
      curState1 = HIGH;
      delay(BTN_DELAY);
    }
    else {
      remote(candle1, 0x4);
      curState1 = LOW;
      delay(BTN_DELAY);
    }
    
  }

  if(btnState2 == HIGH) {
    if(curState2 == LOW) {
      remote(candle2, 0x5);
      curState2 = HIGH;
      delay(BTN_DELAY);
    }
    else {
      remote(candle2, 0x4);
      curState2 = LOW;
      delay(BTN_DELAY);
    }
  }

  if(btnState3 == HIGH) {
    if(curState3 == LOW) {
      remote(candle3, 0x5);
      curState3 = HIGH;
      delay(BTN_DELAY);
    }
    else {
      remote(candle3, 0x4);
      curState3 = LOW;
      delay(BTN_DELAY);
    }
  }

  if(btnState4 == HIGH) {
    if(curState4 == LOW) {
      remote(candle4, 0x5);
      curState4 = HIGH;
      delay(BTN_DELAY);
    }
    else {
      remote(candle4, 0x4);
      curState4 = LOW;
      delay(BTN_DELAY);
    }
  }
  
}

void remote(int rLSB, int value)
{
  Serial.write(0x7E);         //start bit
  Serial.write((byte)0x0);    //length MSB (always 0x0)
  Serial.write(0x10);         //length LSB 
  Serial.write(0x17);         //AT Command
  Serial.write((byte)0x0);    //frame ID (not needed because not expecting response

  Serial.write((byte) 0x0);   //destination address (64-bit, all same except last byte)
  Serial.write(0x13);
  Serial.write(0xA2);
  Serial.write((byte) 0x0);
  Serial.write(0x40);
  Serial.write(0xF9);
  Serial.write(0xD5);
  Serial.write(rLSB);

  //destination network address (for subnets, FFFE default broadcast)
  Serial.write(0xFF);
  Serial.write(0xFE);

  Serial.write(0x02);           //apply immediately

  Serial.write('D');            //pin
  Serial.write('3');

  Serial.write(value);        //pin value (0x4 for LOW, 0x5 for HIGH)

  long sum = 0x17 + 0x13 + 0xA2 + 0x40 + 0xF9 + 0xD5 + rLSB + 0xFF + 0xFE + 0x02 + 'D' + '3' + value;
  Serial.write(0xFF - (sum & 0xFF)); //checksum calculation
  
}


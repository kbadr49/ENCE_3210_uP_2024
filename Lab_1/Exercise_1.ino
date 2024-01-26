/*
Kareem Badr
Lab 2 - Exercise 1
*/

#define BUTTON_1 2
#define BUTTON_2 3

#define GREEN_LED 4
#define RED_LED 5

volatile unsigned int gCount[2] = {0,0};

volatile unsigned char gFlag[2] = {0};

//unsigned int gCount1 = 0;
//unsigned int gCount2 = 0;
//---------------------------------------------

void setup() {
  Serial.begin(9600);
  
  //initializing LEDs
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  //initializing Buttons
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(BUTTON_1), ISR_button1, RISING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_2), ISR_button2, RISING);
} 

//---------------------------------------------

void ISR_button1(){
  if(digitalRead(BUTTON_1)){
    
    gFlag[0] = 1;
    gCount[0] += 1;
  }
   
}

void ISR_button2(){
  if(digitalRead(BUTTON_2)){
    gFlag[1] = 1;
    gCount[1] += 1;
  } 
}


//---------------------------------------------

void loop() {
  //checkte arrays
  //Counter 1 is greater
  if(gCount[0] > gCount[1]){
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
  }
  
  //Counter 2 is greater
  if(gCount[1] > gCount[0]){
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
  }
  //both counters are equal
  if(gCount[0] == gCount[1]){
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
  }
   
  //print results
  if(gFlag[0] == 1 || gFlag[1] == 1){

    //setting flags to call button press function
    gFlag[0] = 0;
    gFlag[1] = 0;

    //print statements
    Serial.print("Counter 1 value: ");
    Serial.print(gCount[0]);

    Serial.print(" Counter 2 value: ");
    Serial.println(gCount[1]);

    delay(500);
  }
  
}

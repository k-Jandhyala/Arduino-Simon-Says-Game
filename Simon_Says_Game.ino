
/*
   Arduino Joystick
   7-segment display
   4 leds
   Rotary Encoder
   Buzzer
   Touch sensor
*/

//ADD FUNCTIONALTIY FOR DELAY
int pause = 2500;
int fast = 0;

//For Reed Switch / Find if the player got something wrong
int buttonpin = 10; //define switch port
int val; //define digital variable val
bool ON = false;

bool reedStart = false;
bool stillPlaying = true;

// For the code
const int codeLength = 4;
int sequence[codeLength];
int your_sequence[codeLength];

//For Difficulty Buttons
int Button3 = 47;
int Button5 = 45;
int Button7 = 49;

int prevDirection = 9;
int currentDirection = 8;

const int UP = 6;
const int DOWN = 4;
const int LEFT = 7;
const int RIGHT = 5;

// Joystick pin numbers
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output

//LED Pin Numbers
const int redLED = 4;
const int greenLED = 5;
const int blueLED = 6;
const int yellowLED = 7;

//Buzzer Pins
const int buzzer = 9;

//set delay 500
unsigned long int initTime = millis();

void setup() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);

  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);

  pinMode(buttonpin, INPUT);//define switch as a output port

  pinMode(Button3, INPUT_PULLUP);
  pinMode(Button5, INPUT_PULLUP);
  pinMode(Button7, INPUT_PULLUP);

  /////////////////////////////////

  while (fast == 0) {
    if (digitalRead(Button3) == LOW) {
      fast = 1500;
      tone(buzzer, 1000);
      delay(100);
      noTone(buzzer);
    } else if (digitalRead(Button5) == LOW) {
      fast = 1000;
      tone(buzzer, 1000);
      delay(100);
      noTone(buzzer);
    } else if (digitalRead(Button7) == LOW) {
      fast = 500;
      tone(buzzer, 1000);
      delay(100);
      noTone(buzzer);
    }
  }

  Serial.println(fast);
}

void loop() {


  if (ON == 1 && stillPlaying == true) {

    pause -= 20;


    tone(buzzer, 500);
    delay(500);
    noTone(buzzer);
    tone(buzzer, 900);
    delay(500);
    noTone(buzzer);

    delay(200);
    digitalWrite(redLED, HIGH);
    digitalWrite(blueLED, HIGH);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, HIGH);
    delay(300);
    digitalWrite(redLED, LOW);
    digitalWrite(blueLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
    delay(200);
    digitalWrite(redLED, HIGH);
    digitalWrite(blueLED, HIGH);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, HIGH);
    delay(300);
    digitalWrite(redLED, LOW);
    digitalWrite(blueLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);


    delay(2000);


    generateSequence();

    Serial.println("Sqeuence Generated");

    delay(200);
    tone(buzzer, 3000);
    digitalWrite(redLED, HIGH);
    digitalWrite(blueLED, HIGH);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, HIGH);
    delay(300);
    digitalWrite(redLED, LOW);
    digitalWrite(blueLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
    noTone(buzzer);


    getSequence();


    for (int i = 0; i < codeLength; i++) {
      Serial.println(your_sequence[i]);
    }


    delay(300);

    checkSequence();
    Serial.println(stillPlaying);
  }

  val = digitalRead(buttonpin); //read the value of the digital interface 3 assigned to val
  //Serial.println(ON);
  if (val == LOW) {
    ON = true;
  }

}


void playTone(int led_num) {
  if (led_num == UP) {
    tone(buzzer, 3000);
    delay(100);
  } else if (led_num == DOWN) {
    tone(buzzer, 4000);
    delay(100);
  } else if (led_num == LEFT) {
    tone(buzzer, 1000);
    delay(100);
  } else if (led_num == RIGHT) {
    tone(buzzer, 2000);
    delay(100);
  }

  noTone(buzzer);

}

void generateSequence() {
  for (int i = 0; i < codeLength; i++) {
    randomSeed(analogRead(A13));
    int randNumber = random(4, 8);

    sequence[i] = randNumber;

    Serial.println(sequence[i]);
  }

  tone(buzzer, 1000);

  for (int i = 0; i < codeLength; i++) {
    //Serial.print("Hello");
    digitalWrite(sequence[i], HIGH);
    playTone(sequence[i]);
    delay(fast);
    digitalWrite(sequence[i], LOW);
    delay(fast);

  }

}

void getSequence() {

  Serial.println("Getting sequence");

  int i = 0;

  while (i < codeLength) {
    //Serial.println(i);
    int xPos = analogRead(X_pin);
    int yPos = analogRead(Y_pin);
    int SW_pin = digitalRead(SW_pin);

    if (xPos >= 1020 && yPos >= 480) {
      Serial.println("Red LED on");

      your_sequence[i] = DOWN;
      tone(buzzer, 4000);
      delay(200);
      noTone(buzzer);

      digitalWrite(redLED, HIGH);
      digitalWrite(blueLED, LOW);
      digitalWrite(yellowLED, LOW);
      digitalWrite(greenLED, LOW);
      delay(300);
      digitalWrite(redLED, LOW);
      digitalWrite(blueLED, LOW);
      digitalWrite(yellowLED, LOW);
      digitalWrite(greenLED, LOW);

      delay(1000);

      i++;

    } else if (xPos <= 10 && yPos >= 480) {
      Serial.println("Blue LED on");

      your_sequence[i] = UP;
      tone(buzzer, 3000);
      delay(200);
      noTone(buzzer);

      digitalWrite(redLED, LOW);
      digitalWrite(blueLED, HIGH);
      digitalWrite(yellowLED, LOW);
      digitalWrite(greenLED, LOW);
      delay(300);
      digitalWrite(redLED, LOW);
      digitalWrite(blueLED, LOW);
      digitalWrite(yellowLED, LOW);
      digitalWrite(greenLED, LOW);

      delay(1000);

      i++;

    } else if (xPos >= 510 && yPos <= 10) {
      Serial.println("Green LED on");

      your_sequence[i] = RIGHT;
      tone(buzzer, 2000);
      delay(200);
      noTone(buzzer);

      digitalWrite(redLED, LOW);
      digitalWrite(blueLED, LOW);
      digitalWrite(yellowLED, LOW);
      digitalWrite(greenLED, HIGH);
      delay(300);
      digitalWrite(redLED, LOW);
      digitalWrite(blueLED, LOW);
      digitalWrite(yellowLED, LOW);
      digitalWrite(greenLED, LOW);

      delay(1000);

      i++;

    } else if (xPos >= 510 && yPos >= 1020) {
      Serial.println("Yellow LED on");

      your_sequence[i] = LEFT;
      tone(buzzer, 1000);
      delay(200);
      noTone(buzzer);

      digitalWrite(redLED, LOW);
      digitalWrite(blueLED, LOW);
      digitalWrite(yellowLED, HIGH);
      digitalWrite(greenLED, LOW);
      delay(300);
      digitalWrite(redLED, LOW);
      digitalWrite(blueLED, LOW);
      digitalWrite(yellowLED, LOW);
      digitalWrite(greenLED, LOW);

      delay(1000);

      i++;

    }

  }
}

void checkSequence() {
  for (int i = 0; i < codeLength; i++) {
    if (your_sequence[i] != sequence[i]) {
      stillPlaying = false;
      digitalWrite(redLED, HIGH);
      digitalWrite(blueLED, HIGH);
      digitalWrite(yellowLED, HIGH);
      digitalWrite(greenLED, HIGH);

      tone(buzzer, 2000);
      delay(700);
      noTone(buzzer);
      delay(200);
      tone(buzzer, 1000);
      delay(700);
      noTone(buzzer);

    }
  }
}

#include <SparkFun_MMA8452Q.h>
#include <Wire.h>
MMA8452Q accel;

int columnArray [5] = {9, 10, 11, 12, 13};
int rowArray[7] = {2, 3, 4, 5, 6, 7, 8};

int columnArray2 [5] = {9, 10, 11, 12, 13};
int rowArray2 [7] = {2, 3, 4, 5, 6, 7, 8};

int currentRow = 4;
int currentColumn = 4;

int currentRow1P = 0;
int currentRow2P = 1;
int currentColumn1P = 0;
int currentColumn2P = 1;

int preyScore = 0;
int predatorScore = 0;

char keyboard;

void setup() {

  Serial.begin(9600);
  accel.init(SCALE_8G, ODR_6);
  //columns
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  //rows
  pinMode( 2, OUTPUT );
  pinMode( 3, OUTPUT );
  pinMode( 4, OUTPUT );
  pinMode( 5, OUTPUT );
  pinMode( 6, OUTPUT );
  pinMode( 7, OUTPUT );
  pinMode( 8, OUTPUT );

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);

  randomSeed(analogRead(0));
}

unsigned long x;
long delta = 15000; 

void loop() {

    resetGame();

    while (millis() - x < 15000) { 
    movePrey();
    delay(6);
    turnOff();
    movePredator();
    delay(6);
    turnOff();
    }
  
  preyWins();
  x += delta;

}

void turnOff() {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
}

void movePrey() {

  digitalWrite(rowArray[currentRow], HIGH);
  digitalWrite(columnArray[currentColumn], LOW);

  if (accel.available()) {
    accel.read();
  }
  
  delay(250); // ------ CONTROLS THE FLASHING OF PREDATOR ------
  
  if (accel.cy < .200) {
    //move backwards
    //incrementing row
    if (currentRow != 6) {
      digitalWrite(rowArray[currentRow], LOW);
      currentRow = currentRow + 1;
    }
  }

  if (accel.cy > -.200) {
    //move forwards
    //decrement row
    if (currentRow != 0) {
      digitalWrite(rowArray[currentRow], LOW);
      currentRow = currentRow - 1;
    }
  }

  if (accel.cx > -.300) {
    //move left
    //decrementing column
    if (currentColumn != 4) {
      digitalWrite(columnArray[currentColumn], HIGH);
      currentColumn = currentColumn + 1;
    }
  }

  if (accel.cx < .300) {
    //move right
    //incrementing column
    if (currentColumn != 0) {
      digitalWrite(columnArray[currentColumn], HIGH);
      currentColumn = currentColumn - 1;
    }
  }
   
    digitalWrite(columnArray[currentColumn], LOW);
    digitalWrite(rowArray[currentRow], HIGH);
  
  checkGame(currentColumn, currentRow, currentRow1P, currentColumn1P, currentRow2P, currentColumn2P);

}

void movePredator() {
  digitalWrite(columnArray2[currentColumn1P], LOW);
  digitalWrite(rowArray2[currentRow1P], HIGH);
  digitalWrite(columnArray2[currentColumn2P], LOW);
  digitalWrite(rowArray2[currentRow2P], HIGH);

  if (Serial.available() > 0) {
    keyboard = Serial.read();
  }
  
  //delay(50);  ------ THIS ISNT NECESSARY ------

  if (keyboard == 'w') {
    if (currentRow1P != 6 && currentRow2P != 6) {
      digitalWrite(rowArray2[currentRow1P], LOW);
      digitalWrite(rowArray2[currentRow2P], LOW);
      currentRow1P++;
      currentRow2P++;
      keyboard =  0;
    }
  }

  if (keyboard == 'd') {
    if (currentColumn1P != 0 && currentColumn2P != 0) {
      digitalWrite(columnArray2[currentColumn1P], HIGH);
      digitalWrite(columnArray2[currentColumn2P], HIGH);
      currentColumn1P--;
      currentColumn2P--;
      keyboard =  0;
    }
  }

  if (keyboard == 'a') {
    if (currentColumn1P != 4 && currentColumn2P != 4) {
      digitalWrite(columnArray2[currentColumn1P], HIGH);
      digitalWrite(columnArray2[currentColumn2P], HIGH);
      currentColumn1P++;
      currentColumn2P++;
      keyboard =  0;
    }
  }

  if (keyboard == 's') {
    if (currentRow1P != 0 && currentRow2P != 0) {
      digitalWrite(rowArray2[currentRow1P], LOW);
      digitalWrite(rowArray2[currentRow2P], LOW);
      currentRow1P--;
      currentRow2P--;
      keyboard =  0;
    }
  }
   
    digitalWrite(columnArray2[currentColumn1P], LOW);
    digitalWrite(rowArray2[currentRow1P], HIGH);
    digitalWrite(columnArray2[currentColumn2P], LOW);
    digitalWrite(rowArray2[currentRow2P], HIGH);
    
  checkGame(currentColumn, currentRow, currentRow1P, currentColumn1P, currentRow2P, currentColumn2P);

}

void checkGame (int currentColumn, int currentRow, int currentRow1P, int currentColumn1P, int currentRow2P, int currentColumn2P) {
  if ((currentRow1P == currentRow) || (currentRow2P == currentRow)) {
    if ((currentColumn1P == currentColumn) || (currentColumn2P == currentColumn)) {
      predatorScore++;
      predatorWins();
    }
  }
}

void predatorWins() {
  turnOff();
  
    if (preyScore == predatorScore) {
      charToLED(5);
    }
    if ((predatorScore - preyScore) == 1 || (predatorScore - preyScore) == 2) {
      charToLED(8);
    }
    if ((predatorScore - preyScore) >= 3) {
      charToLED(9);
    }
    if ((predatorScore - preyScore) == -1 || (predatorScore - preyScore) == -2) {
      charToLED(6);
    }
    if ((predatorScore - preyScore) <= -3) {
      charToLED(7);
    }

  resetGame();

}

void preyWins () {
  preyScore++; 
  turnOff();

    if (preyScore == predatorScore) {
      charToLED(0);
    }
    if ((preyScore - predatorScore) == 1 || (preyScore - predatorScore) == 2) {
      charToLED(1);
    }
    if ((preyScore - predatorScore) >= 3) {
      charToLED(2);
    }
    if ((preyScore - predatorScore) == -1 || (preyScore - predatorScore) == -2) {
      charToLED(3);
    }
    if ((preyScore - predatorScore) <= -3) {
      charToLED(4);
    }

  resetGame();
}

void resetGame () {
  x = millis(); 
  currentRow = 4;
  currentColumn = 4;
  currentRow1P = 0;
  currentRow2P = 1;
  currentColumn1P = 0;
  currentColumn2P = 1;
  randomSpots(); 
}

unsigned char font_5x7[10][5] = {
  {0x00, 0x00, 0x90, 0x00, 0x00},
  {0x00, 0x80, 0x90, 0x00, 0x00},
  {0x80, 0x80, 0x90, 0x00, 0x00},
  {0x00, 0x00, 0x90, 0x80, 0x00},
  {0x00, 0x00, 0x90, 0x80, 0x80},
  {0x00, 0x00, 0x98, 0x18, 0x00}, // ----- Predator -----
  {0x00, 0x00, 0x98, 0x98, 0x00},
  {0x00, 0x00, 0x98, 0x98, 0x80},
  {0x00, 0x80, 0x98, 0x18, 0x00},
  {0x80, 0x80, 0x98, 0x18, 0x00},
};

void randomSpots(){ 
  currentRow = random(0,6); 
  currentColumn = random(0,4); 
  currentRow1P = random(0,6); 
  if (currentRow1P == 6){
    currentRow2P = currentRow1P + 1;   
  } else { 
    currentRow2P = currentRow1P + 1;
  }
  currentColumn1P = random(0,4);
  if (currentColumn1P == 4){
    currentColumn2P = currentColumn1P + 1;   
  } else { 
    currentColumn2P = currentColumn1P + 1;
  }
}

void charToLED (int character) {
  unsigned long t = millis();
  while (millis() - t < 4000) {
    for (int i = 9; i < 14; i++) {
      for (int j = 9; j < 14; j++) {
        if (i == j) {
          digitalWrite(j, LOW);
        } else {
          digitalWrite(j, HIGH);
        }
        for (int k = 2; k < 9; k++) {
          int value = (font_5x7[character][i - 9] >> (7 - k + 2)) & 1;
          if (value == 1) {
            digitalWrite(k, HIGH);
          }
          if (value != 1) {
            digitalWrite(k, LOW);
          }
        }
      }
      delay(3.5);
      for (int k = 2; k < 9; k++) {
        int value = (font_5x7[character][i - 9] >> (7 - k + 2)) & 1;
        if (value == 1) {
          digitalWrite(k, HIGH);
        }
        if (value != 1) {
          digitalWrite(k, LOW);
        }
      }
    }
  }
}

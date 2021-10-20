#include <Wire.h>

bool testing = false;

String input;
bool homed = false;
String mode = "";
long SerialBase = 0;
long SerialShoulder = 0;
long SerialTurnElbow = 0;
long SerialBuckleElbow = 0;
long SerialBuckleHand = 0;
long SerialTurnBase = 0;
long SerialCloseHand = 0;

long MaxBase ;
long MaxShoulder;
long MaxTurnElbow;
long MaxBucklEelbow;
long MaxBuckleHand;
long MaxTurnBase;
long MaxCloseHand;

int Result = 0;
int ResultBase = 0;
int ResultShoulder = 0;
int ResultElbow = 0;
int ResultTurnElbow = 0;
int ResultBuckleHand = 0;
int ResultCloseHand = 0;
int drive = 1;

int startPositionOneBase = 0;
int startPositionTwoBase = 0;
int sensorPositionOneBase = 0;
int sensorPositionTwoBase = 0;

int startPositionOneShoulder = 0;
int startPositionTwoShoulder = 0;
int sensorPositionOneShoulder = 0;
int sensorPositionTwoShoulder = 0;

int startPositionOneElbow = 0;
int startPositionTwoElbow  = 0;
int sensorPositionOneElbow  = 0;
int sensorPositionTwoElbow  = 0;

int startPositionOneTurnElbow = 0;
int startPositionTwoTurnElbow  = 0;
int sensorPositionOneTurnElbow  = 0;
int sensorPositionTwoTurnElbow  = 0;

int startPositionOneBuckleHand = 0;
int startPositionTwoBuckleHand  = 0;
int sensorPositionOneBuckleHand  = 0;
int sensorPositionTwoBuckleHand  = 0;

int startPositionOneCloseHand = 0;
int startPositionTwoCloseHand  = 0;
int sensorPositionOneCloseHand  = 0;
int sensorPositionTwoCloseHand  = 0;

const int PIN_SENSOR_ONEBase = 0;
const int PIN_SENSOR_TWOBase = 0;
const int PIN_END_STOPBase = 0;
const int PIN_END_STOPTwoBase = 0;
const int OUTPUT_FIRST_PINBase = 0;
const int OUTPUT_SECOND_PINBase = 0;

const int PIN_SENSOR_ONEShoulder = 25 ;
const int PIN_SENSOR_TWOShoulder = 24;
const int PIN_END_STOPShoulder = 33;
const int PIN_END_STOPTwoShoulder = 33;
const int OUTPUT_FIRST_PINShoulder = 6 ;
const int OUTPUT_SECOND_PINShoulder = 7;

const int PIN_SENSOR_ONETurnElbow = 0 ;
const int PIN_SENSOR_TWOTurnElbow = 0;
const int PIN_END_STOPTurnElbow = 0 ;
const int PIN_END_STOPTwoTurnElbow = 0 ;
const int OUTPUT_FIRST_PINTurnElbow = 12 ;
const int OUTPUT_SECOND_PINTurnElbow = 13 ;

const int PIN_SENSOR_ONEElbow = 26 ;
const int PIN_SENSOR_TWOElbow = 27;
const int PIN_END_STOPElbow = 27;
const int PIN_END_STOPTwoElbow = 27;
const int OUTPUT_FIRST_PINElbow = 4 ;
const int OUTPUT_SECOND_PINElbow = 5;

const int PIN_SENSOR_ONEBuckleHand  = 55 ;
const int PIN_SENSOR_TWOBuckleHand  = 56;
const int PIN_END_STOPBuckleHand = 27;
const int PIN_END_STOPTwoBuckleHand = 27;
const int OUTPUT_FIRST_PINBuckleHand = 2 ;
const int OUTPUT_SECOND_PINBuckleHand = 3;

const int PIN_SENSOR_ONECloseHand = 44 ;
const int PIN_SENSOR_TWOCloseHand = 45;
const int PIN_END_STOPCloseHand = 27;
const int PIN_END_STOPTwoCloseHand = 27;
const int OUTPUT_FIRST_PINCloseHand = 12 ;
const int OUTPUT_SECOND_PINCloseHand = 13;

int StepCounterBase = 0;
int StepCounterShoulder = 0;
int StepCounterTurnElbow = 0;
int StepCounterElbow = 0;
int StepCounterBuckleHand = 0;
int StepCounterCloseHand = 0;

void setup() {

  Serial.begin(9600);
  Serial.println("Started up");
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event

  pinMode(PIN_SENSOR_ONEBase, INPUT);
  pinMode(PIN_SENSOR_TWOBase, INPUT);
  pinMode(PIN_END_STOPBase, INPUT_PULLUP);
  pinMode(PIN_END_STOPTwoBase, INPUT_PULLUP);

  pinMode(PIN_SENSOR_ONEShoulder, INPUT);
  pinMode(PIN_SENSOR_TWOShoulder, INPUT);
  pinMode(PIN_END_STOPShoulder, INPUT_PULLUP);
  pinMode(PIN_END_STOPTwoShoulder, INPUT_PULLUP);


  pinMode(PIN_SENSOR_ONETurnElbow, INPUT);
  pinMode(PIN_SENSOR_TWOTurnElbow, INPUT);
  pinMode(PIN_END_STOPTurnElbow, INPUT_PULLUP);
  pinMode(PIN_END_STOPTwoTurnElbow, INPUT_PULLUP);

  pinMode(PIN_SENSOR_ONEElbow, INPUT);
  pinMode(PIN_SENSOR_TWOElbow, INPUT);
  pinMode(PIN_END_STOPElbow, INPUT_PULLUP);
  pinMode(PIN_END_STOPTwoElbow, INPUT_PULLUP);

  pinMode(PIN_SENSOR_ONEBuckleHand, INPUT);
  pinMode(PIN_SENSOR_TWOBuckleHand, INPUT);
  pinMode(PIN_END_STOPBuckleHand, INPUT_PULLUP);
  pinMode(PIN_END_STOPTwoBuckleHand, INPUT_PULLUP);

  pinMode(PIN_SENSOR_ONEBuckleHand, INPUT);
  pinMode(PIN_SENSOR_TWOBuckleHand, INPUT);
  pinMode(PIN_END_STOPBuckleHand, INPUT_PULLUP);
  pinMode(PIN_END_STOPTwoBuckleHand, INPUT_PULLUP);

  pinMode(PIN_SENSOR_ONECloseHand, INPUT);
  pinMode(PIN_SENSOR_TWOCloseHand, INPUT);
  pinMode(PIN_END_STOPCloseHand, INPUT_PULLUP);
  pinMode(PIN_END_STOPTwoCloseHand, INPUT_PULLUP);

  pinMode(OUTPUT_FIRST_PINBase, OUTPUT);
  pinMode(OUTPUT_SECOND_PINBase, OUTPUT);

  pinMode(OUTPUT_FIRST_PINShoulder, OUTPUT);
  pinMode(OUTPUT_SECOND_PINShoulder, OUTPUT);

  pinMode(OUTPUT_FIRST_PINTurnElbow, OUTPUT);
  pinMode(OUTPUT_SECOND_PINTurnElbow, OUTPUT);

  pinMode(OUTPUT_FIRST_PINElbow, OUTPUT);
  pinMode(OUTPUT_SECOND_PINElbow, OUTPUT);

  pinMode(OUTPUT_FIRST_PINBuckleHand, OUTPUT);
  pinMode(OUTPUT_SECOND_PINBuckleHand, OUTPUT);

  pinMode(OUTPUT_FIRST_PINCloseHand, OUTPUT);
  pinMode(OUTPUT_SECOND_PINCloseHand, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR_ONEBase), PositionBase, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR_TWOBase), PositionBase, CHANGE);

  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR_ONEShoulder), PositionShoulder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR_TWOShoulder), PositionShoulder, CHANGE);

  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR_ONETurnElbow), PositionTurnElbow, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR_TWOTurnElbow), PositionTurnElbow, CHANGE);

  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR_ONEElbow), PositionElbow, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR_TWOElbow), PositionElbow, CHANGE);

  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR_ONEBuckleHand), PositionBuckleHand, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR_TWOBuckleHand), PositionBuckleHand, CHANGE);

  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR_ONECloseHand), PositionCloseHand, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR_TWOCloseHand), PositionCloseHand, CHANGE);

  startPositionOneBase = digitalRead(PIN_SENSOR_ONEBase);
  startPositionTwoBase = digitalRead(PIN_SENSOR_TWOBase);

  startPositionOneShoulder = digitalRead(PIN_SENSOR_ONEShoulder);
  startPositionTwoShoulder = digitalRead(PIN_SENSOR_TWOShoulder);

  startPositionOneBase = digitalRead(PIN_SENSOR_ONETurnElbow);
  startPositionTwoBase = digitalRead(PIN_SENSOR_TWOTurnElbow);

  startPositionOneShoulder = digitalRead(PIN_SENSOR_ONEElbow);
  startPositionTwoShoulder = digitalRead(PIN_SENSOR_TWOElbow);

  startPositionOneBase = digitalRead(PIN_SENSOR_ONEBuckleHand);
  startPositionTwoBase = digitalRead(PIN_SENSOR_TWOBuckleHand);

  startPositionOneShoulder = digitalRead(PIN_SENSOR_ONECloseHand);
  startPositionTwoShoulder = digitalRead(PIN_SENSOR_TWOCloseHand);
}

void PositionBase() {

  sensorPositionOneBase = digitalRead(PIN_SENSOR_ONEBase);
  sensorPositionTwoBase = digitalRead(PIN_SENSOR_TWOBase);

  if (startPositionOneBase == 1) {
    if (sensorPositionTwoBase == 1) {
      StepCounterBase++;
    } else {

      StepCounterBase--;
      //   Serial.println(StepCounterBase);
    }
  } else if (sensorPositionTwoBase == 1) {
    StepCounterBase--;

  } else {
    StepCounterBase++;

    // Serial.println(StepCounterBase);
  }


  startPositionOneBase = sensorPositionOneBase;
  startPositionTwoBase = sensorPositionTwoBase;
}

void PositionShoulder() {

  sensorPositionOneShoulder = digitalRead(PIN_SENSOR_ONEShoulder);
  sensorPositionTwoShoulder = digitalRead(PIN_SENSOR_TWOShoulder);

  if (startPositionOneShoulder == 1) {
    if (sensorPositionTwoShoulder == 1) {
      StepCounterShoulder++;
    } else {

      StepCounterShoulder--;
      //  Serial.println(StepCounterShoulder);
    }
  } else if (sensorPositionTwoShoulder == 1) {
    StepCounterShoulder--;

  } else {
    StepCounterShoulder++;
    // Serial.println(StepCounterShoulder);
  }


  startPositionOneShoulder = sensorPositionOneShoulder;
  startPositionTwoShoulder = sensorPositionTwoShoulder;
}

void PositionTurnElbow() {

  sensorPositionOneTurnElbow = digitalRead(PIN_SENSOR_ONETurnElbow);
  sensorPositionTwoTurnElbow = digitalRead(PIN_SENSOR_TWOTurnElbow);

  if (startPositionOneTurnElbow == 1) {
    if (sensorPositionTwoTurnElbow == 1) {
      StepCounterTurnElbow++;
    } else {

      StepCounterTurnElbow--;
      //   Serial.println(StepCounterTurnElbow);
    }
  } else if (sensorPositionTwoTurnElbow == 1) {
    StepCounterTurnElbow--;

  } else {
    StepCounterTurnElbow++;

    // Serial.println(StepCounterTurnElbow);
  }


  startPositionOneTurnElbow = sensorPositionOneTurnElbow;
  startPositionTwoTurnElbow = sensorPositionTwoTurnElbow;
}

void PositionElbow() {

  sensorPositionOneElbow = digitalRead(PIN_SENSOR_ONEElbow);
  sensorPositionTwoElbow = digitalRead(PIN_SENSOR_TWOElbow);

  if (startPositionOneElbow == 1) {
    if (sensorPositionTwoElbow == 1) {
      StepCounterElbow++;
    } else {

      StepCounterElbow--;
      //  Serial.println(StepCounterElbow);
    }
  } else if (sensorPositionTwoElbow == 1) {
    StepCounterElbow--;

  } else {
    StepCounterElbow++;
    // Serial.println(StepCounterElbow);
  }


  startPositionOneElbow = sensorPositionOneElbow;
  startPositionTwoElbow = sensorPositionTwoElbow;
}

void PositionBuckleHand() {

  sensorPositionOneBuckleHand = digitalRead(PIN_SENSOR_ONEBuckleHand);
  sensorPositionTwoBuckleHand = digitalRead(PIN_SENSOR_TWOBuckleHand);

  if (startPositionOneBuckleHand == 1) {
    if (sensorPositionTwoBuckleHand == 1) {
      StepCounterBuckleHand++;
    } else {

      StepCounterBuckleHand--;
      //   Serial.println(StepCounterBuckleHand);
    }
  } else if (sensorPositionTwoBuckleHand == 1) {
    StepCounterBuckleHand--;

  } else {
    StepCounterBuckleHand++;

    // Serial.println(StepCounterBuckleHand);
  }


  startPositionOneBuckleHand = sensorPositionOneBuckleHand;
  startPositionTwoBuckleHand = sensorPositionTwoBuckleHand;
}


void PositionCloseHand() {

  sensorPositionOneCloseHand = digitalRead(PIN_SENSOR_ONECloseHand);
  sensorPositionTwoCloseHand = digitalRead(PIN_SENSOR_TWOCloseHand);

  if (startPositionOneCloseHand == 1) {
    if (sensorPositionTwoCloseHand == 1) {
      StepCounterCloseHand++;
    } else {

      StepCounterCloseHand--;
      //   Serial.println(StepCounterCloseHand);
    }
  } else if (sensorPositionTwoCloseHand == 1) {
    StepCounterCloseHand--;

  } else {
    StepCounterCloseHand++;

    // Serial.println(StepCounterCloseHand);
  }


  startPositionOneCloseHand = sensorPositionOneCloseHand;
  startPositionTwoCloseHand = sensorPositionTwoCloseHand;
}

int setzeZahlZusammen(unsigned int high, unsigned int low) {
  int kombiniert;
  kombiniert = high;
  kombiniert = kombiniert * 256;
  kombiniert |= low;
  return kombiniert;
}

void receiveEvent(int howMany)
{
  byte buffer[2];
  for (int i = 0; i < 2; i++) {
    if (Wire.available() > 0) {
      buffer[i] = Wire.read();
    }
  }
  int result = setzeZahlZusammen(buffer[0], buffer[1]);
  Serial.println("received data");
  Serial.println(result);

  Result = result;
  drive = 0;

  ResultCloseHand = result;
  ResultShoulder = result;
  // so müssen alle dann sein blob
}

int updateDistanceBase(int goalBase, int StepCounterBase) {
  if (goalBase < StepCounterBase) {
    return -(goalBase - StepCounterBase);
  } else {
    return goalBase - StepCounterBase;
  }
}

int updateDistanceShoulder(int goalShoulder, int StepCounterShoulder) {
  if (goalShoulder < StepCounterShoulder) {
    return -(goalShoulder - StepCounterShoulder);
  } else {
    return goalShoulder - StepCounterShoulder;
  }
}

int updateDistanceTurnElbow(int goalTurnElbow, int StepCounterTurnElbow) {
  if (goalTurnElbow < StepCounterTurnElbow) {
    return -(goalTurnElbow - StepCounterTurnElbow);
  } else {
    return goalTurnElbow - StepCounterTurnElbow;
  }
}

int updateDistanceElbow(int goalElbow, int StepCounterElbow) {
  if (goalElbow < StepCounterElbow) {
    return -(goalElbow - StepCounterElbow);
  } else {
    return goalElbow - StepCounterElbow;
  }
}

int updateDistanceBuckleHand(int goalBuckleHand, int StepCounterBuckleHand) {
  if (goalBuckleHand < StepCounterBuckleHand) {
    return -(goalBuckleHand - StepCounterBuckleHand);
  } else {
    return goalBuckleHand - StepCounterBuckleHand;
  }
}

int updateDistanceCloseHand(int goalCloseHand, int StepCounterCloseHand) {
  if (goalCloseHand < StepCounterCloseHand) {
    return -(goalCloseHand - StepCounterCloseHand);
  } else {
    return goalCloseHand - StepCounterCloseHand;
  }
}

int getNegativeSpeedBase(int DistanceBase) {
  if (DistanceBase < 50) {
    return 50;
  } else if (DistanceBase < 100) {
    return 140;
  } else {
    return 255;
  }
}

int getNegativeSpeedShoulder(int DistanceShoulder) {
  if (DistanceShoulder < 50) {
    return 50;
  } else if (DistanceShoulder < 100) {
    return 140;
  } else {
    return 255;
  }
}

int getNegativeSpeedTurnElbow(int DistanceTurnElbow) {
  if (DistanceTurnElbow < 50) {
    return 50;
  } else if (DistanceTurnElbow < 100) {
    return 140;
  } else {
    return 255;
  }
}

int getNegativeSpeedElbow(int DistanceElbow) {
  if (DistanceElbow < 50) {
    return 50;
  } else if (DistanceElbow < 100) {
    return 140;
  } else {
    return 255;
  }
}

int getNegativeSpeedBuckleHand(int DistanceBuckleHand) {
  if (DistanceBuckleHand < 50) {
    return 50;
  } else if (DistanceBuckleHand < 100) {
    return 140;
  } else {
    return 255;
  }
}

int getNegativeSpeedCloseHand(int DistanceCloseHand) {
  if (DistanceCloseHand < 50) {
    return 50;
  } else if (DistanceCloseHand < 100) {
    return 140;
  } else {
    return 255;
  }
}

int getPositiveSpeedBase(int DistanceBase) {
  if (DistanceBase > 1000) {
    return 255;
  } else if (DistanceBase > 100) {
    return 140;
  } else {
    return 100;
  }
}

int getPositiveSpeedShoulder(int DistanceShoulder) {
  if (DistanceShoulder > 1000) {
    return 255;
  } else if (DistanceShoulder > 100) {
    return 140;
  } else {
    return 100;
  }
}

int getPositiveSpeedTurnElbow(int DistanceTurnElbow) {
  if (DistanceTurnElbow > 1000) {
    return 255;
  } else if (DistanceTurnElbow > 100) {
    return 140;
  } else {
    return 100;
  }
}

int getPositiveSpeedElbow(int DistanceElbow) {
  if (DistanceElbow > 1000) {
    return 255;
  } else if (DistanceElbow > 100) {
    return 140;
  } else {
    return 100;
  }
}

int getPositiveSpeedBuckleHand(int DistanceBuckleHand) {
  if (DistanceBuckleHand > 1000) {
    return 255;
  } else if (DistanceBuckleHand > 100) {
    return 140;
  } else {
    return 100;
  }
}

int getPositiveSpeedCloseHand(int DistanceCloseHand) {
  if (DistanceCloseHand > 1000) {
    return 255;
  } else if (DistanceCloseHand > 100) {
    return 140;
  } else {
    return 100;
  }
}

void moveRobotBase(int newgoalBase) {


  long  goalBase = newgoalBase;
  long DistanceBase = (newgoalBase < 0) ? -newgoalBase : newgoalBase;
  if (StepCounterBase < goalBase) {
    //one direction

    while (!(DistanceBase <= 10)) {
      //Serial.println(StepCounterBase);

      DistanceBase = updateDistanceBase(goalBase, StepCounterBase);
      // Serial.println(DistanceBase);
      int speed = getNegativeSpeedBase(DistanceBase);
      analogWrite(OUTPUT_FIRST_PINBase, speed);
      analogWrite(OUTPUT_SECOND_PINBase, 0);
      /*    if (stepCounter == StepCounterBase) {
            localCounter += 1;
          } else {
            stepCounter = StepCounterBase;
          }
          if (localCounter >= 100) {
            break;
          }
      */
    }
  } else if (StepCounterBase > goalBase) {
    //another direction
    while (!(DistanceBase <= 10)) {
      //Serial.println(StepCounterBase);
      DistanceBase = updateDistanceBase(goalBase, StepCounterBase);
      // Serial.println(DistanceBase);
      int speed = getPositiveSpeedBase(DistanceBase);
      analogWrite(OUTPUT_FIRST_PINBase, 0);
      analogWrite(OUTPUT_SECOND_PINBase, speed);
      /*   if (stepCounter == StepCounterBase) {
           localCounter += 1;
         } else {
           stepCounter = StepCounterBase;
         }
         if (localCounter >= 100) {
           break;
         }
      */
    }
    Serial.println("On position");


  }
  analogWrite(OUTPUT_FIRST_PINBase, 0);
  analogWrite(OUTPUT_SECOND_PINBase, 0);

}

void moveRobotShoulder(int newgoalShoulder) {

  long stepCounter = StepCounterShoulder;
  size_t localCounter = 0;
  long goalShoulder = newgoalShoulder;
  long DistanceShoulder = (newgoalShoulder < 0) ? -newgoalShoulder : newgoalShoulder;
  if (StepCounterShoulder < goalShoulder) {
    //one direction

    while (!(DistanceShoulder <= 10)) {
      //Serial.println(StepCounterShoulder);

      DistanceShoulder = updateDistanceShoulder(goalShoulder, StepCounterShoulder);
      // Serial.println(DistanceShoulder);
      int speed = getNegativeSpeedShoulder(DistanceShoulder);
      analogWrite(OUTPUT_FIRST_PINShoulder, speed);
      analogWrite(OUTPUT_SECOND_PINShoulder, 0);
      /* if (stepCounter == StepCounterShoulder) {
         localCounter += 1;
        } else {
         stepCounter = StepCounterShoulder;
        }
        if (localCounter >= 100) {
         break;
        }
      */
    }
  } else if (StepCounterShoulder > goalShoulder) {
    //another direction
    while (!(DistanceShoulder <= 10)) {
      //Serial.println(StepCounterShoulder);
      DistanceShoulder = updateDistanceShoulder(goalShoulder, StepCounterShoulder);
      // Serial.println(DistanceShoulder);
      int speed = getPositiveSpeedShoulder(DistanceShoulder);
      analogWrite(OUTPUT_FIRST_PINShoulder, 0);
      analogWrite(OUTPUT_SECOND_PINShoulder, speed);
      /* if (stepCounter == StepCounterShoulder) {
         localCounter += 1;
        } else {
         stepCounter = StepCounterShoulder;
        }
        if (localCounter >= 100) {
         break;
        }
      */
    }


  }
  analogWrite(OUTPUT_FIRST_PINShoulder, 0);
  analogWrite(OUTPUT_SECOND_PINShoulder, 0);

}


void moveRobotTurnElbow(int newgoalTurnElbow) {
  long stepCounter = StepCounterTurnElbow;
  size_t localCounter = 0;
  long goalTurnElbow = newgoalTurnElbow;
  long DistanceTurnElbow = (newgoalTurnElbow < 0) ? -newgoalTurnElbow : newgoalTurnElbow;
  if (StepCounterTurnElbow < goalTurnElbow) {
    //one direction

    while (!(DistanceTurnElbow <= 10)) {
      //Serial.println(StepCounterTurnElbow);

      DistanceTurnElbow = updateDistanceTurnElbow(goalTurnElbow, StepCounterTurnElbow);
      // Serial.println(DistanceTurnElbow);
      int speed = getNegativeSpeedTurnElbow(DistanceTurnElbow);
      analogWrite(OUTPUT_FIRST_PINTurnElbow, 0);
      analogWrite(OUTPUT_SECOND_PINTurnElbow, speed);
      /*   if (stepCounter == StepCounterTurnElbow) {
           localCounter += 1;
         } else {
           stepCounter = StepCounterTurnElbow;
         }
         if (localCounter >= 100) {
           break;
         } */
    }
  } else if (StepCounterTurnElbow > goalTurnElbow) {
    //another direction
    while (!(DistanceTurnElbow <= 10)) {
      //Serial.println(StepCounterTurnElbow);
      DistanceTurnElbow = updateDistanceTurnElbow(goalTurnElbow, StepCounterTurnElbow);
      // Serial.println(DistanceTurnElbow);
      int speed = getPositiveSpeedTurnElbow(DistanceTurnElbow);
      analogWrite(OUTPUT_FIRST_PINTurnElbow, speed);
      analogWrite(OUTPUT_SECOND_PINTurnElbow, 0);
      /*    if (stepCounter == StepCounterTurnElbow) {
            localCounter += 1;
          } else {
            stepCounter = StepCounterTurnElbow;
          }
          if (localCounter >= 100) {
            break;
          } */
    }


  }
  analogWrite(OUTPUT_FIRST_PINTurnElbow, 0);
  analogWrite(OUTPUT_SECOND_PINTurnElbow, 0);

}

void moveRobotElbow(int newgoalElbow) {
  long stepCounter = StepCounterElbow;
  size_t localCounter = 0;
  long goalElbow = newgoalElbow;
  long DistanceElbow = (newgoalElbow < 0) ? -newgoalElbow : newgoalElbow;
  if (StepCounterElbow < goalElbow) {
    //one direction

    while (!(DistanceElbow <= 10)) {
      //Serial.println(StepCounterElbow);

      DistanceElbow = updateDistanceElbow(goalElbow, StepCounterElbow);
      // Serial.println(DistanceElbow);
      int speed = getNegativeSpeedElbow(DistanceElbow);
      analogWrite(OUTPUT_FIRST_PINElbow, 0);
      analogWrite(OUTPUT_SECOND_PINElbow, speed);
      /*    if (stepCounter == StepCounterElbow) {
            localCounter += 1;
          } else {
            stepCounter = StepCounterElbow;
          }
          if (localCounter >= 100) {
            break;
          } */
    }
  } else if (StepCounterElbow > goalElbow) {
    //another direction
    while (!(DistanceElbow <= 10)) {
      //Serial.println(StepCounterElbow);
      DistanceElbow = updateDistanceElbow(goalElbow, StepCounterElbow);
      // Serial.println(DistanceElbow);
      int speed = getPositiveSpeedElbow(DistanceElbow);
      analogWrite(OUTPUT_FIRST_PINElbow, speed);
      analogWrite(OUTPUT_SECOND_PINElbow, 0);
      /* if (stepCounter == StepCounterElbow) {
         localCounter += 1;
        } else {
         stepCounter = StepCounterElbow;
        }
        if (localCounter >= 100) {
         break;
        } */
    }


  }
  analogWrite(OUTPUT_FIRST_PINElbow, 0);
  analogWrite(OUTPUT_SECOND_PINElbow, 0);

}


void moveRobotBuckleHand(int newgoalBuckleHand) {
  long stepCounter = StepCounterBuckleHand;
  size_t localCounter = 0;
  long goalBuckleHand = newgoalBuckleHand;
  long DistanceBuckleHand = (newgoalBuckleHand < 0) ? -newgoalBuckleHand : newgoalBuckleHand;
  if (StepCounterBuckleHand < goalBuckleHand) {
    //one direction

    while (!(DistanceBuckleHand <= 10)) {
      //Serial.println(StepCounterBuckleHand);

      DistanceBuckleHand = updateDistanceBuckleHand(goalBuckleHand, StepCounterBuckleHand);
      // Serial.println(DistanceBuckleHand);
      int speed = getNegativeSpeedBuckleHand(DistanceBuckleHand);
      analogWrite(OUTPUT_FIRST_PINBuckleHand, 0);
      analogWrite(OUTPUT_SECOND_PINBuckleHand, speed);
      /* if (stepCounter == StepCounterBuckleHand) {
         localCounter += 1;
        } else {
         stepCounter = StepCounterBuckleHand;
        }
        if (localCounter >= 100) {
         break;
        } */
    }
  } else if (StepCounterBuckleHand > goalBuckleHand) {
    //another direction
    while (!(DistanceBuckleHand <= 10)) {
      //Serial.println(StepCounterBuckleHand);
      DistanceBuckleHand = updateDistanceBuckleHand(goalBuckleHand, StepCounterBuckleHand);
      // Serial.println(DistanceBuckleHand);
      int speed = getPositiveSpeedBuckleHand(DistanceBuckleHand);
      analogWrite(OUTPUT_FIRST_PINBuckleHand, speed);
      analogWrite(OUTPUT_SECOND_PINBuckleHand, 0);
      /* if (stepCounter == StepCounterBuckleHand) {
         localCounter += 1;
        } else {
         stepCounter = StepCounterBuckleHand;
        }
        if (localCounter >= 100) {
         break;
        } */
    }


  }
  analogWrite(OUTPUT_FIRST_PINBuckleHand, 0);
  analogWrite(OUTPUT_SECOND_PINBuckleHand, 0);

}

void moveRobotCloseHand(int newgoalCloseHand) {
  long stepCounter = StepCounterCloseHand;
  size_t localCounter = 0;
  long goalCloseHand = newgoalCloseHand;
  long DistanceCloseHand = (newgoalCloseHand < 0) ? -newgoalCloseHand : newgoalCloseHand;
  if (StepCounterCloseHand < goalCloseHand) {
    //one direction

    while (!(DistanceCloseHand <= 10)) {
      //Serial.println(StepCounterCloseHand);

      DistanceCloseHand = updateDistanceCloseHand(goalCloseHand, StepCounterCloseHand);
      // Serial.println(DistanceCloseHand);
      int speed = getNegativeSpeedCloseHand(DistanceCloseHand);
      analogWrite(OUTPUT_FIRST_PINCloseHand, 0);
      analogWrite(OUTPUT_SECOND_PINCloseHand, speed);
      if (stepCounter == StepCounterCloseHand) {
        localCounter += 1;
      } else {
        stepCounter = StepCounterCloseHand;
      }
      if (localCounter >= 100) {
        break;
      }
    }
  } else if (StepCounterCloseHand > goalCloseHand) {
    //another direction
    while (!(DistanceCloseHand <= 10)) {
      //Serial.println(StepCounterCloseHand);
      DistanceCloseHand = updateDistanceCloseHand(goalCloseHand, StepCounterCloseHand);
      // Serial.println(DistanceCloseHand);
      int speed = getPositiveSpeedCloseHand(DistanceCloseHand);
      analogWrite(OUTPUT_FIRST_PINCloseHand, speed);
      analogWrite(OUTPUT_SECOND_PINCloseHand, 0);
      if (stepCounter == StepCounterCloseHand) {
        localCounter += 1;
      } else {
        stepCounter = StepCounterCloseHand;
      }
      if (localCounter >= 100) {
        break;

      }
    }


  }
  analogWrite(OUTPUT_FIRST_PINCloseHand, 0);
  analogWrite(OUTPUT_SECOND_PINCloseHand, 0);

}

void homing() {

  bool homedBase = false;
  bool homedShoulder = false;
  bool homedTurnElbow = false;
  bool homedBuckleElbow = false;
  bool homedBuckleHand = false;
  bool homedCloseHand = false;


  while (digitalRead(PIN_END_STOPBase) == HIGH || digitalRead ( PIN_END_STOPTwoBase == HIGH)) {
    analogWrite(OUTPUT_FIRST_PINBase, 200);
    analogWrite(OUTPUT_SECOND_PINBase, 0);
    if (digitalRead(PIN_END_STOPBase) == LOW ) {
      homedBase = true;
      Serial.println("homed Base");
      StepCounterBase = 0;
    }
    if (digitalRead(PIN_END_STOPTwoBase) == LOW ) {
      homedBase = true;
      Serial.println("homed Base");
      StepCounterBase = 0;
    }

  }
  while (digitalRead(PIN_END_STOPBase) == HIGH || digitalRead ( PIN_END_STOPTwoBase == HIGH)) {
    analogWrite(OUTPUT_FIRST_PINBase, 0);
    analogWrite(OUTPUT_SECOND_PINBase, 200);
    if (digitalRead(PIN_END_STOPBase) == LOW ) {
      homedBase = true;
      Serial.println("homed Base");
      MaxBase = StepCounter;
    }
    if (digitalRead(PIN_END_STOPTwoBase) == LOW ) {
      homedBase = true;
      Serial.println("homed Base");
      MaxBase = StepCounter;
    }

  }



  if ( homedBase == true && homedShoulder == true && homedTurnElbow == true && homedBuckleElbow == true && homedBuckleHand == true && homedCloseHand == true) homed = true;
}

void loop() {

  if (homed == false) {
    homing();
  }



  while (!Serial.available());
  if (Serial.available() > 0) {
    input = Serial.readStringUntil('\n');

    if (input == "Shoulder" || input == "Base" || input == "TurnElbow" || input == "BuckleElbow" || input == "TurnHand" || input == "BuckleHand" || input == "CloseOpenHand" ) {
      mode = input;
      Serial.println(mode);
    } else {
      if (mode == "Base") {
        SerialBase =  atol(input.c_str());
        Serial.println(SerialBase);
        mode = "";
        moveRobotBase(SerialBase);
      }
      if (mode == "Shoulder") {
        SerialShoulder =  atol(input.c_str());
        Serial.println(SerialShoulder);
        mode = "";
        moveRobotShoulder(SerialShoulder);
      }
      if (mode == "TurnElbow") {
        SerialTurnElbow =  atol(input.c_str());
        Serial.println(SerialTurnElbow);
        mode = "";
        moveRobotTurnElbow(SerialTurnElbow);
      }
      if (mode == "BuckleElbow") {

        SerialBuckleElbow =  atol(input.c_str());
        Serial.println(SerialBuckleElbow);
        mode = "";
        moveRobotElbow(SerialBuckleElbow);
      }
      if (mode == "BuckleHand") {
        SerialBuckleHand =  atol(input.c_str());
        Serial.println(SerialBuckleHand);
        mode = "";
        moveRobotBuckleHand(SerialBuckleHand);
      }
      if (mode == "CloseOpenHand") {
        SerialCloseHand =  atol(input.c_str());
        Serial.println(SerialCloseHand);
        mode = "";
        moveRobotCloseHand(SerialCloseHand);
      }
    }
  }
}



/*
               INPUTS
      Pos     end    Pos     end
         Base         Shoulder
   I45,44I I43,42I I41,40I I39,38I
       Turn Ell       Buckle Ell
   I53,52I I51,50I I49,48I I47,46I
     Buckle Hand   Close Open Hand
   I22,23I I24,25I I26,27I I28,29I


          OUTPUTS

    Base  Shoulder  T_Ellbow
   I2,3I    I4,5I   I6,7I // PWM

       T_Hand       L_Base  IA6,A7,
   IA5,A4I IA3,A2I IA1,A0I //

   B_Ellbow B_Hand  C_Hand
   I9,8I    I10,11I I12,13I // PWM

*/

const int Pin_EndStop_L_Base = A6;
const int PIN_EndStoP2_L_Base = A7;
const int PIN_OUTPUT_FIRST_L_Base = A1;
const int PIN_OUTPUT_SECOND_L_Base = A0;

const int PIN_SENSOR_ONEBase = 44;
const int PIN_SENSOR_TWOBase = 45;
const int Pin_EndStop_Base = 43;
const int PIN_EndStoP2_Base = 42;
const int PIN_OUTPUT_FIRST_Base = 2;
const int PIN_OUTPUT_SECOND_Base = 3;
int startPositionOneBase = 0;
int startPositionTwoBase = 0;
int sensorPositionOneBase = 0;
int sensorPositionTwoBase = 0;

const int PIN_SENSOR_ONEShoulder = 41;
const int PIN_SENSOR_TWOShoulder = 40;
const int Pin_EndStop_Shoulder = 39;
const int PIN_EndStoP2_Shoulder = 38;
const int PIN_OUTPUT_FIRST_Shoulder = 4;
const int PIN_OUTPUT_SECOND_Shoulder = 5;
int startPositionOneShoulder = 0;
int startPositionTwoShoulder = 0;
int sensorPositionOneShoulder = 0;
int sensorPositionTwoShoulder = 0;

const int PIN_SENSOR_ONET_Ellbow = 53;
const int PIN_SENSOR_TWOT_Ellbow = 52;
const int Pin_EndStop_T_Ellbow = 51;
const int PIN_EndStoP2_T_Ellbow = 50;
const int PIN_OUTPUT_FIRST_T_Ellbow = 6;
const int PIN_OUTPUT_SECOND_T_Ellbow = 7;
int startPositionOneT_Ellbow = 0;
int startPositionTwoT_Ellbow = 0;
int sensorPositionOneT_Ellbow = 0;
int sensorPositionTwoT_Ellbow = 0;


const int PIN_SENSOR_ONEB_Ellbow = 49;
const int PIN_SENSOR_TWOB_Ellbow = 48;
const int Pin_EndStop_B_Ellbow = 47;
const int PIN_EndStoP2_B_Ellbow = 46;
const int PIN_OUTPUT_FIRST_B_Ellbow = 9;
const int PIN_OUTPUT_SECOND_B_Ellbow = 8;
int startPositionOneB_Ellbow = 0;
int startPositionTwoB_Ellbow = 0;
int sensorPositionOneB_Ellbow = 0;
int sensorPositionTwoB_Ellbow = 0;

const int PIN_SENSOR_ONEB_Hand = 28;
const int PIN_SENSOR_TWOB_Hand = 29;
const int Pin_EndStop_B_Hand = 27;
const int PIN_EndStoP2_B_Hand = 26;
const int PIN_OUTPUT_FIRST_B_Hand = 10;
const int PIN_OUTPUT_SECOND_B_Hand = 11;
int startPositionOneB_Hand = 0;
int startPositionTwoB_Hand = 0;
int sensorPositionOneB_Hand = 0;
int sensorPositionTwoB_Hand = 0;

const int PIN_SENSOR_ONEC_Hand = 25;
const int PIN_SENSOR_TWOC_Hand = 24;
const int Pin_EndStop_C_Hand = 23;
const int PIN_EndStoP2_C_Hand = 22;
const int PIN_OUTPUT_FIRST_C_Hand = 12;
const int PIN_OUTPUT_SECOND_C_Hand = 13;
int startPositionOneC_Hand = 0;
int startPositionTwoC_Hand = 0;
int sensorPositionOneC_Hand = 0;
int sensorPositionTwoC_Hand = 0;

const int Pin_EndStop_T_Hand = A6;
const int PIN_EndStoP2_T_Hand = A7;
const int PIN_OUTPUT_FIRST_T_Hand = A1;
const int PIN_OUTPUT_SECOND_T_Hand = A0;


struct Axis {
  int speed1;
  int speed2;
  int output1;
  int output2;
  int Endstop1;
  int Endstop2;
  long Distance;
  long goal;
  long Position;
  int StartPositionOne;
  int StartPositionTwo;
  int SensorPositionOne;
  int SensorPositionTwo;
  int PIN_Sens1;
  int PIN_Sens2;

};

typedef struct Axis MyAxis;

MyAxis L_Base, Base, Shoulder, T_Ellbow, B_Ellbow, T_Hand, B_Hand, C_Hand;

void setup() {
  // put your setup code here, to run once:
  long SearchEnd = -1000000;
  Serial.begin(9600);
  Serial.println("Started up");

  pinMode(PIN_SENSOR_ONEBase, INPUT_PULLUP);
  pinMode(PIN_SENSOR_TWOBase, INPUT_PULLUP);
  pinMode(Pin_EndStop_Base, INPUT_PULLUP);
  pinMode(PIN_EndStoP2_Base, INPUT_PULLUP);
  pinMode(PIN_OUTPUT_FIRST_Base, OUTPUT);
  pinMode(PIN_OUTPUT_SECOND_Base, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR_ONEBase), PositionOfBase, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR_TWOBase), PositionOfBase, CHANGE);
  init_Axis(&Base, 0, 0, PIN_OUTPUT_FIRST_Base, PIN_OUTPUT_SECOND_Base, Pin_EndStop_Base, PIN_EndStoP2_Base, 0, SearchEnd, 0, 0, 0, digitalRead(PIN_SENSOR_ONEBase), digitalRead(PIN_SENSOR_TWOBase), PIN_SENSOR_ONEBase, PIN_SENSOR_TWOBase);

  pinMode(PIN_SENSOR_ONEShoulder, INPUT_PULLUP);
  pinMode(PIN_SENSOR_TWOShoulder, INPUT_PULLUP);
  pinMode(Pin_EndStop_Shoulder, INPUT_PULLUP);
  pinMode(PIN_EndStoP2_Shoulder, INPUT_PULLUP);
  pinMode(PIN_OUTPUT_FIRST_Shoulder, OUTPUT);
  pinMode(PIN_OUTPUT_SECOND_Shoulder, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR_ONEShoulder), PositionOfShoulder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR_TWOShoulder), PositionOfShoulder, CHANGE);
  init_Axis(&Shoulder, 0, 0, PIN_OUTPUT_FIRST_Shoulder, PIN_OUTPUT_SECOND_Shoulder, Pin_EndStop_Shoulder, PIN_EndStoP2_Shoulder, 0, SearchEnd, 0, 0, 0, digitalRead(PIN_SENSOR_ONEShoulder), digitalRead(PIN_SENSOR_TWOShoulder), PIN_SENSOR_ONEShoulder, PIN_SENSOR_TWOShoulder);

  pinMode(PIN_SENSOR_ONET_Ellbow, INPUT_PULLUP);
  pinMode(PIN_SENSOR_TWOT_Ellbow, INPUT_PULLUP);
  pinMode(Pin_EndStop_T_Ellbow, INPUT_PULLUP);
  pinMode(PIN_EndStoP2_T_Ellbow, INPUT_PULLUP);
  pinMode(PIN_OUTPUT_FIRST_T_Ellbow, OUTPUT);
  pinMode(PIN_OUTPUT_SECOND_T_Ellbow, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR_ONET_Ellbow), PositionOfT_Ellbow, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR_TWOT_Ellbow), PositionOfT_Ellbow, CHANGE);
  init_Axis(&T_Ellbow, 0, 0, PIN_OUTPUT_FIRST_T_Ellbow, PIN_OUTPUT_SECOND_T_Ellbow, Pin_EndStop_T_Ellbow, PIN_EndStoP2_T_Ellbow, 0, SearchEnd, 0, 0, 0, digitalRead(PIN_SENSOR_ONET_Ellbow), digitalRead(PIN_SENSOR_TWOT_Ellbow), PIN_SENSOR_ONET_Ellbow, PIN_SENSOR_TWOT_Ellbow);

  pinMode(PIN_SENSOR_ONEB_Ellbow, INPUT_PULLUP);
  pinMode(PIN_SENSOR_TWOB_Ellbow, INPUT_PULLUP);
  pinMode(Pin_EndStop_B_Ellbow, INPUT_PULLUP);
  pinMode(PIN_EndStoP2_B_Ellbow, INPUT_PULLUP);
  pinMode(PIN_OUTPUT_FIRST_B_Ellbow, OUTPUT);
  pinMode(PIN_OUTPUT_SECOND_B_Ellbow, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR_ONEB_Ellbow), PositionOfB_Ellbow, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR_TWOB_Ellbow), PositionOfB_Ellbow, CHANGE);
  init_Axis(&B_Ellbow, 0, 0, PIN_OUTPUT_FIRST_B_Ellbow, PIN_OUTPUT_SECOND_B_Ellbow, Pin_EndStop_B_Ellbow, PIN_EndStoP2_B_Ellbow, 0, SearchEnd, 0, 0, 0, digitalRead(PIN_SENSOR_ONEB_Ellbow), digitalRead(PIN_SENSOR_TWOB_Ellbow), PIN_SENSOR_ONEB_Ellbow, PIN_SENSOR_TWOB_Ellbow);

  pinMode(PIN_SENSOR_ONEB_Hand, INPUT_PULLUP);
  pinMode(PIN_SENSOR_TWOB_Hand, INPUT_PULLUP);
  pinMode(Pin_EndStop_B_Hand, INPUT_PULLUP);
  pinMode(PIN_EndStoP2_B_Hand, INPUT_PULLUP);
  pinMode(PIN_OUTPUT_FIRST_B_Hand, OUTPUT);
  pinMode(PIN_OUTPUT_SECOND_B_Hand, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR_ONEB_Hand), PositionOfB_Hand, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR_TWOB_Hand), PositionOfB_Hand, CHANGE);
  init_Axis(&B_Hand, 0, 0, PIN_OUTPUT_FIRST_B_Hand, PIN_OUTPUT_SECOND_B_Hand, Pin_EndStop_B_Hand, PIN_EndStoP2_B_Hand, 0, SearchEnd, 0, 0, 0, digitalRead(PIN_SENSOR_ONEB_Hand), digitalRead(PIN_SENSOR_TWOB_Hand), PIN_SENSOR_ONEB_Hand, PIN_SENSOR_TWOB_Hand);

  pinMode(PIN_SENSOR_ONEC_Hand, INPUT_PULLUP);
  pinMode(PIN_SENSOR_TWOC_Hand, INPUT_PULLUP);
  pinMode(Pin_EndStop_C_Hand, INPUT_PULLUP);
  pinMode(PIN_EndStoP2_C_Hand, INPUT_PULLUP);
  pinMode(PIN_OUTPUT_FIRST_C_Hand, OUTPUT);
  pinMode(PIN_OUTPUT_SECOND_C_Hand, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR_ONEC_Hand), PositionOfC_Hand, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR_TWOC_Hand), PositionOfC_Hand, CHANGE);
  init_Axis(&C_Hand, 0, 0, PIN_OUTPUT_FIRST_C_Hand, PIN_OUTPUT_SECOND_C_Hand, Pin_EndStop_B_Hand, PIN_EndStoP2_B_Hand, 0, SearchEnd, 0, 0, 0, digitalRead(PIN_SENSOR_ONEB_Hand), digitalRead(PIN_SENSOR_TWOB_Hand), PIN_SENSOR_ONEB_Hand, PIN_SENSOR_TWOB_Hand);


  // homing();
}
void init_Axis(MyAxis* data, int speed1, int speed2, int output1, int output2, int Endstop1, int Endstop2, long Distance, long goal, long Position,  int StartPositionOne , int StartPositionTwo, int SensorPositionOne, int SensorPositionTwo, int PIN_Sens1,  int PIN_Sens2 ) {
  data->speed1 = speed1;
  data->speed2 = speed2;
  data->output1 = output1;
  data->output2 = output2;
  data->Endstop1 = Endstop1;
  data->Endstop2 = Endstop2;
  data->Distance = Distance;
  data->goal = goal;
  data->Position = Position;
  data->StartPositionOne = StartPositionOne;
  data->StartPositionTwo = StartPositionTwo;
  data->SensorPositionOne = SensorPositionOne;
  data->SensorPositionTwo = SensorPositionTwo;
  data->PIN_Sens1 = PIN_Sens1;
  data->PIN_Sens2 = PIN_Sens2;
}

void PositionOfBase() {
  Position(&Base);
}


void PositionOfShoulder() {
  Position(&Shoulder);
}

void PositionOfT_Ellbow() {
  Position(&T_Ellbow);
}


void PositionOfB_Ellbow() {
  Position(&B_Ellbow);
}

void PositionOfB_Hand() {
  Position(&B_Hand);
}

void PositionOfC_Hand() {
  Position(&C_Hand);
}

void Position(MyAxis*data) {
  data->SensorPositionOne =  digitalRead(data->PIN_Sens1);
  data->SensorPositionTwo = digitalRead(data->PIN_Sens2);
  if (data->StartPositionOne == 1) {
    if (data->SensorPositionTwo == 1) {
      data->Position++;
    } else {

      data->Position--;
      //   Serial.println(data->Position);
    }
  } else if (data->SensorPositionTwo == 1) {
    data->Position--;

  } else {
    data->Position++;

    // Serial.println(data->Position);

  }
  data->StartPositionOne = data->SensorPositionOne;
  data->StartPositionTwo = data->SensorPositionTwo;
}



int GetSpeed(MyAxis* data) {

  if (data->Distance < 50) {
    return 50;
  } else if (data->Distance < 100) {
    return 140;
  } else {
    return 255;
  }
}
void updateDistance(MyAxis* data) {
  if (data->goal < data->Position) {
    data->speed1 = 0;
    data->Distance = -(data->goal - data->Position);
    data->speed2 = GetSpeed(data);
  } else {
    data->speed2 = 0;
    data->Distance = data->goal - data->Position;
    data->speed1 = GetSpeed(data);
  }
}

int moveAxis(MyAxis* data) {

  updateDistance(data);
  while (!(data->Distance <= 10) && digitalRead(data->Endstop1) == 1 && digitalRead(data->Endstop2) == 1 ) {

    updateDistance(data);


    analogWrite(data->output1, data->speed1 );
    analogWrite(data->output2, data->speed2 );

  }
  analogWrite(data->output1, 0 );
  analogWrite(data->output2, 0 );
  data->speed1 = 0;
  data->speed2 = 0;
  Serial.println("Dis");
  Serial.println(data->Distance);

  Serial.println("Pos");
  Serial.println(data->Position);

  Serial.println("goal");
  Serial.println(data->goal);
  if (digitalRead(data->Endstop1) == 1 && digitalRead(data->Endstop2) == 0) {
    data->Position = 0;
    return 1;
  } else if (digitalRead(data->Endstop2) == 1 && digitalRead(data->Endstop1) == 0) {
    return 2;
  } else {
    return 0;
  }
}

bool homing() {
  Serial.println("homed Base with");
  Serial.println(moveAxis(&Base));
  Serial.println("homed Shoulder with");
  Serial.println(moveAxis(&Shoulder));
  Serial.println("homed T_Ellbow with");
  Serial.println(moveAxis(&T_Ellbow));
  Serial.println("homed B_Ellbow with");
  Serial.println(moveAxis(&B_Ellbow));
  Serial.println("homed B_Hand with");
  Serial.println(moveAxis(&B_Hand));
  Serial.println("homed C_Hand with");
  Serial.println(moveAxis(&C_Hand));
  return true;
}
void SetGoal(MyAxis* data, int goal) {
  data->goal = goal;
}
String SerialData = "";
void loop() {
  Serial.println("In loop");
  while (!Serial.available());
  if (Serial.available() > 0) {
    SerialData = Serial.readStringUntil('\n');
    Serial.println(SerialData);
    String str = SerialData.substring(0, 3);
    int str_len = SerialData.length() + 1;
    char char_array[str_len];
    str.toCharArray(char_array, str_len);
    int Mode = str[0] + str[1] + str[2];
    SerialData.remove(0, 3);
    SerialData.toInt();
    switch (Mode) {
      case 237: //L_B
        Serial.println(SerialData);
        SetGoal(&L_Base, SerialData.toInt());
        moveAxis(&L_Base);
        break;
      case 256: //__B
        Serial.println(SerialData);
        SetGoal(&Base,SerialData.toInt());
        moveAxis(&Base);
        break;
      case 273: //__S
        Serial.println(SerialData);
        SetGoal(&Shoulder,SerialData.toInt());
        moveAxis(&Shoulder);
        break;
      case 248: //T_E
        Serial.println(SerialData);
        SetGoal(&T_Ellbow,SerialData.toInt());
        moveAxis(&T_Ellbow);
        break;
      case 230: //B_E
        Serial.println(SerialData);
        SetGoal(&B_Ellbow,SerialData.toInt());
        moveAxis(&B_Ellbow);
        break;
      case 233: //B_H
        Serial.println(SerialData);
        SetGoal(&B_Hand,SerialData.toInt());
        moveAxis(&B_Hand);
        break;
      case 251: //T_H
        Serial.println(SerialData);
        SetGoal(&T_Hand,SerialData.toInt());
        moveAxis(&T_Hand);
        break;
      case 234: // C_H
        Serial.println(SerialData);
        SetGoal(&C_Hand,SerialData.toInt());
        moveAxis(&C_Hand);
        break;
      default:
        Serial.println("Error");
        break;
    }



  }

}

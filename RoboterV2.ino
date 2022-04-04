
/*
               INPUTS
      Pos     end    Pos     end
         Base         Shoulder
   I44,43I I42,41I I40,39I I38,37I
       Turn Ell       Buckle Ell
   I53,52I I51,50I I49,48I I46,45I
     Buckle Hand   Close Open Hand
   I22,23I I24,25I I26,27I I28,29I


          OUTPUTS


   I2,3I I4,5I I6,7I // PWM
   IA5,A4I IA3,A2I IA1,A0I //
   I9,8I I10,11I I12,13I // PWM

*/

const int PIN_SENSOR_ONEBase = 44;
const int PIN_SENSOR_TWOBase = 43;
const int Pin_EndStop_Base = 42;
const int PIN_EndStoP2_Base = 41;
const int PIN_OUTPUT_FIRST_Base = 2;
const int PIN_OUTPUT_SECOND_Base = 3;

int startPositionOneBase = 0;
int startPositionTwoBase = 0;
int sensorPositionOneBase = 0;
int sensorPositionTwoBase = 0;
long PositionBase = 0;


struct Axis{
  int speed1;
  int speed2;
  int output1;
  int output2;
  int Endstop1;
  int Endstop2;
  long Distance;
  long goal;
  long Position;
};

typedef struct Axis MyAxis;

MyAxis L_Base, Base, Shoulder, T_Ellbow, B_Ellbow, T_Hand, B_Hand, C_Hand;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Started up");

  pinMode(PIN_SENSOR_ONEBase, INPUT);
  pinMode(PIN_SENSOR_TWOBase, INPUT);
  pinMode(Pin_EndStop_Base, INPUT_PULLUP);
  pinMode(PIN_EndStoP2_Base, INPUT_PULLUP);
  pinMode(PIN_OUTPUT_FIRST_Base, OUTPUT);
  pinMode(PIN_OUTPUT_SECOND_Base, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR_ONEBase), PositionOfBase, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR_TWOBase), PositionOfBase, CHANGE);
  startPositionOneBase = digitalRead(PIN_SENSOR_ONEBase);
  startPositionTwoBase = digitalRead(PIN_SENSOR_TWOBase);
  init_Axis(&Base, 0,0, PIN_SENSOR_ONEBase, PIN_SENSOR_TWOBase, Pin_EndStop_Base, PIN_EndStoP2_Base, 0,-20,0);





}
void init_Axis(MyAxis* data, int speed1, int speed2, int output1, int output2, int Endstop1, int Endstop2, long Distance, long goal, long Position) {
  data->speed1 = speed1;
  data->speed2 = speed2;
  data->output1 = output1;
  data->output2 = output2;
  data->Endstop1 = Endstop1;
  data->Endstop2 = Endstop2;
  data->Distance = Distance;
  data->goal = goal;
  data->Position = Position;
}

void PositionOfBase() {
  sensorPositionOneBase = digitalRead(PIN_SENSOR_ONEBase);
  sensorPositionTwoBase = digitalRead(PIN_SENSOR_TWOBase);
  if (startPositionOneBase == 1) {
    if (sensorPositionTwoBase == 1) {
      PositionBase++;
    } else {

      PositionBase--;
      //   Serial.println(PositionBase);
    }
  } else if (sensorPositionTwoBase == 1) {
    PositionBase--;

  } else {
    PositionBase++;

    // Serial.println(PositionBase);
  
  }
  startPositionOneBase = sensorPositionOneBase;
  startPositionTwoBase = sensorPositionTwoBase;
 MyAxis* data = &Base;
 data->Position = PositionBase;
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
    data->Distance= -(data->goal - data->Position);
    data->speed2 = GetSpeed(data);
  } else {
    data->speed2 = 0;
    data->Distance= data->goal - data->Position;
    data->speed1 = GetSpeed(data);
  }
}

int moveAxis(MyAxis* data) {
  

  while (!(data->Distance <= 10) && digitalRead(data->Endstop1) == 0 ) {

    updateDistance(data);

    
    analogWrite(data->output1, data->speed1 );
    analogWrite(data->output2, data->speed2 );

  }
  if(digitalRead(data->Endstop1)==1){
    return 1;
  }else if(digitalRead(data->Endstop1)==1){
    return 2;
  }else{
    return 0;
  }
}

int homing() {
  
  moveAxis(&Base);
}

void loop() {
  // put your main code here, to run repeatedly:
  homing();
}

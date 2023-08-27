#include <CytronMotorDriver.h>
//Wiring Connections.
#define LED0          0   // Onboard LED 0
#define LED1          1   // Onboard LED 1
#define BUTTON        13  // nut bat dau
#define EDGE_L        12  // cam biến viền trái
#define EDGE_R        11  // cảm biến viền phải
#define OPPONENT_L    3   // cảm biến siêu âm trái
#define OPPONENT_R    10  // cảm biến siêu âm phải
#define OPPONENT_FR   A0  // cảm biến đổi thủ trước mặt bên phải
#define OPPONENT_FC   A1  // cảm biến đổi thủ trước mặt ở giữa
#define OPPONENT_FL   A2  // cảm biến đổi thủ trước mặt bên trái
//phương hướng
#define LEFT    0
#define RIGHT   1
// các biến toàn cục
uint8_t searchDir = LEFT;
/*******************************************************************************
 * bắt đầu chu trình
 * hàm này chỉ được gọi một lần khi trận đấu bắt đầu
 *******************************************************************************/
void startRoutine() {
  // bắt đầy delay.
  delay(1000);
  
  // rẻ phải khoảng 45 độ.
  motorL.setSpeed(255);
  motorR.setSpeed(0);
  delay(180);
  
  // đi thẳng.
  motorL.setSpeed(255);
  motorR.setSpeed(255);
  delay(450);
  
  // rẻ trái cho đến khi tìm thấy đối thủ.
  motorL.setSpeed(-0);
  motorR.setSpeed(255);
  uint32_t startTimestamp = millis();
  while (digitalRead(OPPONENT_FC)) {
    // thoát hàm nếu như không tìm thấy đối thủ sau khi hết thời gian
    if (millis() - startTimestamp > 400) {
      break;
    }
  }
  
}
/*******************************************************************************
 * hàm tìm kiếm đối thủ
 *******************************************************************************/
    void search() {
    // di chuyển theo chuyển động tròn.
    if (searchDir == LEFT) {
        motorL.setSpeed(100);
        motorR.setSpeed(255);
    } else {
        motorL.setSpeed(255);
        motorR.setSpeed(100);
    }
    }
/*******************************************************************************
 * Hàm tấn công
 * theo dõi và tấn công với tốc độ tối đa.
 * không làm gì khi không phát hiện đối thủ.
 *******************************************************************************/
    void attack() {
    uint32_t attackTimestamp = millis();
    // Lưu thời điểm tấn công bắt đầu (sử dụng hàm millis() để lấy thời gian hiện tại).

    // Đối thủ ở phía trước trung tâm.
    // Đi thẳng với tốc độ tối đa.
    if (!digitalRead(OPPONENT_FC)) {
        motorL.setSpeed(255);
        motorR.setSpeed(255);
    }
    
    // Đối thủ ở phía trước bên trái.
    // Rẽ trái.
    else if (!digitalRead(OPPONENT_FL)) {
        motorL.setSpeed(0);
        motorR.setSpeed(255);
    }
    
    // Đối thủ ở phía trước bên phải.
    // Rẽ phải.
    else if (!digitalRead(OPPONENT_FR)) {
        motorL.setSpeed(255);
        motorR.setSpeed(0);
    }
    
    // Đối thủ ở phía bên trái.
    // Xoay trái cho đến khi đối thủ ở phía trước.
    else if (!digitalRead(OPPONENT_L)) {
        motorL.setSpeed(-150);
        motorR.setSpeed(150);
        while (digitalRead(OPPONENT_FC)) {
            // Thoát nếu không tìm thấy đối thủ sau khoảng thời gian chờ.
            if (millis() - attackTimestamp > 400) {
                break;
            }
        }
    }
    
    // Đối thủ ở phía bên phải.
    // Xoay phải cho đến khi đối thủ ở phía trước.
    else if (!digitalRead(OPPONENT_R)) {
        motorL.setSpeed(150);
        motorR.setSpeed(-150);
        while (digitalRead(OPPONENT_FC)) {
            // Thoát nếu không tìm thấy đối thủ sau khoảng thời gian chờ.
            if (millis() - attackTimestamp > 400) {
                break;
            }
        }
    }
}
/*******************************************************************************
 * Back Off
 * Hàm này nên được gọi khi phát hiện viền của sàn đấu sumo.
 *******************************************************************************/
void backoff(uint8_t dir) {
  // Dừng động cơ.
  motorL.setSpeed(0);
  motorR.setSpeed(0);
  delay(100);
  
  // Lùi lại.
  motorL.setSpeed(-255);
  motorR.setSpeed(-255);
  delay(200);
  
  // Dừng động cơ.
  motorL.setSpeed(0);
  motorR.setSpeed(0);
  delay(100);
  
  // Xoay..
  if (dir == LEFT) {
    motorL.setSpeed(-150);
    motorR.setSpeed(150);
  } else {
    motorL.setSpeed(150);
    motorR.setSpeed(-150);
  }
  delay(100);
  
  // Bắt đầu tìm kiếm đối thủ.
  // Hết thời gian sau một khoảng thời gian ngắn.
  uint32_t uTurnTimestamp = millis();
  while (millis() - uTurnTimestamp < 300) {
    // Đối thủ được phát hiện nếu ít nhất một cảm biến đối thủ được kích hoạt.
    if ( !digitalRead(OPPONENT_FC) ||
         !digitalRead(OPPONENT_FL) ||
         !digitalRead(OPPONENT_FR) ||
         !digitalRead(OPPONENT_L) ||
         !digitalRead(OPPONENT_R) ) {
      // Dừng động cơ.
      motorL.setSpeed(0);
      motorR.setSpeed(0);
      delay(100);
  
      // Quay lại vòng lặp chính và thực hiện chương trình tấn công.
      return;
    }
  }
  
  // Nếu không tìm thấy đối thủ, di chuyển về phía trước và tiếp tục tìm kiếm trong vòng lặp chính.
  motorL.setSpeed(255);
  motorR.setSpeed(255);
  delay(200);
}


// chức năng này chạy một lần sau khi thiết lập lâij
void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(EDGE_L, INPUT_PULLUP);
  pinMode(EDGE_R, INPUT_PULLUP);
  pinMode(OPPONENT_L, INPUT_PULLUP);
  pinMode(OPPONENT_R, INPUT_PULLUP);
  pinMode(OPPONENT_FL, INPUT_PULLUP);
  pinMode(OPPONENT_FC, INPUT_PULLUP);
  pinMode(OPPONENT_FR, INPUT_PULLUP);

  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);

  // tắt đèn led.
  // Those LEDs are active low.
  digitalWrite(LED0, HIGH);
  digitalWrite(LED1, HIGH);
  
  // dừng động cơ
  motorL.setSpeed(0);
  motorR.setSpeed(0);

  // chờ cho đến khi nhấn nút.
  while (digitalRead(BUTTON)) {
    // trong khi chờ, hiển thị trạng thái của cảm biến để dễ dàng hiệu chỉnh
    if (!digitalRead(EDGE_L)) {
       digitalWrite(LED1, LOW);
    } else {
      digitalWrite(LED1, HIGH);
    }

    if (!digitalRead(EDGE_R)) {
       digitalWrite(LED0, LOW);
    } else {
      digitalWrite(LED0, HIGH);
    }
  }

  // chờ cho đến khi thả nút.
  while (!digitalRead(BUTTON));

  // bật đèn led.
  digitalWrite(LED0, LOW);
  digitalWrite(LED1, LOW);
  
  // bắt đầu chu trình..
  startRoutine();
}

// vòng lặp chính
void loop() {
  {
  // phát hiện cảm biến viền trái chạm vạch.
  if (!digitalRead(EDGE_L)) {
    // quay lại và quay đầu xe sang phải
    backoff(RIGHT);
  
    // chuyển hướng tiềm kiếm
    searchDir ^= 1;
  }
  
  //cảm biến phát hiện bên phải
  else if (!digitalRead(EDGE_R)) {
    // quay lại và quà quay lại đầu xe sang phải 
    backoff(LEFT);
  
    // chuyển hướng tìm kiếm 
    searchDir ^= 1;
  }
  
  // cạnh ko phát hiện được
  else {
    // tiếp tục tìm kiếm đối thủ nếu tiếp tục ko tìm thấy đối thủ
    if ( digitalRead(OPPONENT_FC) &&
         digitalRead(OPPONENT_FL) &&
         digitalRead(OPPONENT_FR) &&
         digitalRead(OPPONENT_L) &&
         digitalRead(OPPONENT_R) ) {
      search();
    }
  
    // tấn công đối thủ nếu trong tầm nhìn
    else {
      attack();
    }
  }
  
  
  // dừng robot nêu như nhấn nếu như nhận nút
  if (!digitalRead(BUTTON)) {
    // dừng moto.
    motorL.setSpeed(0);
    motorR.setSpeed(0);
  
    // vòng lặp mãi mãi ở dây.
    while (1);
  }

}

}


///// mode solving maze
const int trigPin1 = 6;//front
const int echoPin1 = 7;
const int trigPin2 = 10; //left
const int echoPin2 = 11;
const int trigPin3 = 8;//right
const int echoPin3 = 9;
const int in1 = 2;
const int in2 = 3;
const int in3 = 4;
const int in4 = 5;

#define DIS 7

void setup()
{
pinMode(trigPin1, OUTPUT);
pinMode(echoPin1, INPUT);
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);
pinMode(trigPin3, OUTPUT);
pinMode(echoPin3, INPUT);
pinMode (in1, OUTPUT);
pinMode (in2, OUTPUT);
pinMode (in3, OUTPUT);
pinMode (in4, OUTPUT);

}
void loop()
{
  if (FrontSensor ()>DIS && RightSensor () >DIS && LeftSensor () >DIS)
  {forward();}
 //else if ( FrontSensor () > DIS && RightSensor () < DIS && LeftSensor ()< DIS)
//{
  //forward();  
//}
else if ( FrontSensor() < DIS && RightSensor () <DIS && LeftSensor ()<DIS) // obstacle infront of all 3 sides
{
reverse ();
delay(500);
if((LeftSensor())>(RightSensor()) )
turn_left();
else
turn_right();
//then reverse
}
else if (FrontSensor() <DIS && RightSensor () <DIS && LeftSensor ()>DIS) // obstacle on right and front sides
{
turn_left (); // turn left side
}
else if (FrontSensor() <DIS && RightSensor () >DIS && LeftSensor ()<DIS) // obstacle on left and front sides
{
turn_right (); // turn right side
}
else if (FrontSensor() <DIS && RightSensor () >DIS && LeftSensor ()>DIS) // obstacle on front sides
{
turn_left (); 
delay(500);
forward();// then turn right //********************
}
else if (FrontSensor() >DIS && RightSensor () >DIS && LeftSensor ()<DIS) // obstacle on left sides
{
turn_right(); // then turn right and then forward
delay(500);
forward();
}
else if (FrontSensor() >DIS && RightSensor () <DIS && LeftSensor ()>DIS) // obstacle on right sides
{
turn_left (); // then turn left and then right
delay(500);
forward();
}
else
{
forward();
}
}
void forward ()
{
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
}
void turn_left ()
{
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);

}
void turn_right ()
{
digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);

}
void reverse ()
{
digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);

}
void stop()
{
digitalWrite(in1, LOW);
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);
digitalWrite(in4, LOW);

}
long FrontSensor ()
{
long dur;
digitalWrite(trigPin1, LOW);
delayMicroseconds(2); // delays are required for a succesful sensor operation.
digitalWrite(trigPin1, HIGH);
delayMicroseconds(10); //this delay is required as well!
digitalWrite(trigPin1, LOW);
dur = pulseIn(echoPin1, HIGH);
return (dur/58);// convert the distance to centimeters.
}

long RightSensor ()
{
long dur;
digitalWrite(trigPin2, LOW);
delayMicroseconds(2); // delays are required for a succesful sensor operation.
digitalWrite(trigPin2, HIGH);
delayMicroseconds(10); //this delay is required as well!
digitalWrite(trigPin2, LOW);
dur = pulseIn(echoPin2, HIGH);
return (dur/58);// convert the distance to centimeters.
}
long LeftSensor ()
{
long dur;
digitalWrite(trigPin3, LOW);
delayMicroseconds(2); // delays are required for a succesful sensor operation.
digitalWrite(trigPin3, HIGH);
delayMicroseconds(10); //this delay is required as well!
digitalWrite(trigPin3, LOW);
dur = pulseIn(echoPin3, HIGH);
return (dur/58);// convert the distance to centimeters.
}
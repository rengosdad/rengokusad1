#define IN1 7
#define IN2 6
#define MAX_SPEED 255 //từ 0-255
#define MIN_SPEED 0

int d3=5; ////////////////////////////////////
int d3f=0;
int ld1=8;
int ld2=9;
int ld3=10;
int ld4=11;
int d0=2;
int d0f=0;
int d1=3;
int d1f=0;
int d2=4;
int d2f=0;
/////////////////////
const int trig = 14; ////////////////////////
const int echo=15; ///////////////////////
const int  sda = 1;
const int scl = 2;
int cambien = 16; ////////////////////
int giatri;
int den = 17;  ///////////////////////////
unsigned long thoigian;
int khoangcach; 

#include "Stepper.h"
const int stepsPerRevolution = 2048;
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);
Stepper myStepper2 = Stepper(stepsPerRevolution, 8, 10, 9, 11);

#include "RTClib.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2); //LCD 16x02, địa chỉ I2C là 0X27
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
/////////////////////////////////////////////////////////////////////////////
void setup()
{
{
Serial.begin(9600);
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(d1,INPUT);
pinMode(d2,INPUT);
pinMode(d3,INPUT);
pinMode(d0,INPUT);
pinMode(ld1,OUTPUT);
pinMode(ld2,OUTPUT);
pinMode(ld3,OUTPUT);
pinMode(ld4,OUTPUT);
pinMode(cambien, INPUT);
pinMode(den,OUTPUT);
digitalWrite(den,LOW);
myStepper.setSpeed(15);
myStepper2.setSpeed(15);
}
lcd.begin (16,2);  // initialize the lcd 
  lcd.backlight();//To Power ON the back light
  if (! rtc.begin()) 
  {
    lcd.print("Couldn't find RTC");
    while (1);
  }
if (! rtc.isrunning()) 
  {
    lcd.print("RTC is NOT running!");
  }

  Serial.begin(9600); //Mở cổng Serial ở 9600
  pinMode(trig, OUTPUT); //Chân trig xuất tín hiệu
  pinMode(echo, INPUT); //Chân echo nhận tín hiệu
  
   lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(2,1);
  lcd.init(); //Khởi động LCD
  lcd.backlight(); //Bật đèn nền
  lcd.setCursor(1,0); //Cột 1, hàng 0
}

void motor_1_Dung() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
}
 
void motor_1_Tien(int speed) { //speed: từ 0 - MAX_SPEED
    speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED - http://arduino.vn/reference/constrain
    digitalWrite(IN1, HIGH);// chân này không có PWM
    analogWrite(IN2, 255 - speed);
}
 
void motor_1_Lui(int speed) {
    speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED - http://arduino.vn/reference/constrain
    digitalWrite(IN1, LOW);// chân này không có PWM
    analogWrite(IN2, speed);
}
//////////////////////////////////////////////
void loop()
{ 
{
  if(digitalRead(d0)==HIGH && d0f==0) {
    myStepper2.step(-stepsPerRevolution / 2);
  delay(50); 
  }
  else if(digitalRead(d1)==HIGH && d1f==0) {
myStepper.step(2 * stepsPerRevolution);
  delay(50);
  }
  if(digitalRead(d2)==HIGH && d2f==0) {
    motor_1_Tien(MAX_SPEED); // motor 1 tiến
  delay(5000);
  }
  if(digitalRead(d3)==LOW && d3f==0) {
     motor_1_Dung();
     delay(10);
  }
}
////////////////////////////////////////////////////////////
{
  digitalWrite(trig,0); //Tắt chân trig
  delayMicroseconds(2); 
  digitalWrite(trig,1); //bật chân trig để phát xung
  delayMicroseconds(10); //Xung có độ rộng là 10 microsecond
  digitalWrite(trig,0);
  thoigian = pulseIn (echo, HIGH);
  khoangcach = int(thoigian / 2 / 29.412); 
  Serial.print("Khoảng cách: ");
  Serial.print(khoangcach);
  Serial.println("cm");
 
  lcd.setCursor(0,1);
  lcd.print("muc nuoc:");
  lcd.setCursor(11,1);
  lcd.print(khoangcach);
  if (khoangcach < 10)
  {
    lcd.setCursor(12,1);
    lcd.print(" ");
  }
  
  if (khoangcach >= 10 && khoangcach < 100)
  {
    lcd.setCursor(13,1);
    lcd.print(" ");
  }
  {
    DateTime now = rtc.now();
    lcd.setCursor(0, 0);
     lcd.print("TIME  ");
    if(now.hour()<=9)
    {
      lcd.print("0");
      lcd.print(now.hour());
    }
    else {
     lcd.print(now.hour()); 
    }
    lcd.print(':');
    if(now.minute()<=9)
    {
      lcd.print("0");
      lcd.print(now.minute());
    }
    else {
     lcd.print(now.minute()); 
    }
    lcd.print(':');
    if(now.second()<=9)
    {
      lcd.print("0");
      lcd.print(now.second());
    }
    else {
     lcd.print(now.second()); 
    }
    lcd.print("   ");
}
{
  giatri = digitalRead(cambien); //Đọc giá trị digital từ cảm biến và gán vào biến giatri

  if (giatri == 1) //Nếu giá trị đọc từ cảm biến là 1
  {
    Serial.print("Có người ");
    digitalWrite(den,HIGH); //Đèn bật
  }
  else
  {
    Serial.print("Không có người");
    digitalWrite(den,LOW); //Đèn tắt
  }
  Serial.print("     Giá trị cảm biến là: ");
  Serial.println(giatri);
  Serial.println("  ");
}  
  delay(500);
 
}
}

const int trig = 8; //Khai báo chân trig nối với chân số 8 là hằng số
const int echo=7; //Khai báo chân echo nối với chân số 7 là hằng số
const int  sda = 1;
const int scl = 2;

unsigned long thoigian; //Thời gian là kiểu số nguyên
int khoangcach; //Khoảng cách là kiểu số nguyên
#include "RTClib.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2); //LCD 16x02, địa chỉ I2C là 0X27
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
void setup () 
{

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
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));//auto update from computer time
    //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));// to set the time manually 

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

void loop()
{
  //Phát xung từ chân trig, có độ rộng là 10ms
  digitalWrite(trig,0); //Tắt chân trig
  delayMicroseconds(2); 
  digitalWrite(trig,1); //bật chân trig để phát xung
  delayMicroseconds(10); //Xung có độ rộng là 10 microsecond
  digitalWrite(trig,0);

  //Chân echo sẽ nhận xung phản xạ lại

  //Và đo độ rộng xung cao ở chân echo
  thoigian = pulseIn (echo, HIGH);
  
  //Tính khoảng cách đến vật thể (Đơn vị đo là cm)
  //Tốc độ của âm thanh trong không khí là 340 m/s, tương đương 29,412 microSeconds/cm,
  //Do thời gian được tính từ lúc phát tín hiệu tới khi sóng âm phản xạ lại,
  //vì vậy phải chia cho 2
  khoangcach = int(thoigian / 2 / 29.412); 
 

  //In lên Serial kết quả
  Serial.print("Khoảng cách: ");
  Serial.print(khoangcach);
  Serial.println("cm");
 
  lcd.setCursor(0,1);
  lcd.print("Don vi cm:");
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
     lcd.print("TIME ");
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
// {
  // DateTime now = rtc.now();
  // if(now.hour()<=9)
   //{
   //  Serial.print("0");
   //  Serial.print(now.hour());
  // }
  // else {
  //  Serial.print(now.hour());
  // }
  //  Serial.print(':');
  //  if(now.minute()<=9)
  //  {
   //   Serial.print("0");
    //  Serial.print(now.minute());
   // }
   // else {
    // Serial.print(now.minute());
   // }
   // Serial.print(':');
   // if(now.second()<=9)
  //  {
     // Serial.print("0");
    //  Serial.print(now.second());
    //}
   // else {
    // Serial.print(now.second());
   // }
    //Serial.println();

    //Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
   // Serial.print(",");
   // if(now.day()<=9)
    // //{
    //  Serial.print("0");
      //Serial.print(now.day());
   // }
   // else {
   //  Serial.print(now.day());
    //}
    //Serial.print('/');
    //if(now.month()<=9)
    //{
    //  Serial.print("0");
     // Serial.print(now.month());
   // }
    //else {
    // Serial.print(now.month());
   // // }
    //Serial.print('/');
   // if(now.year()<=9)
   // {
     // Serial.print("0");
    //  Serial.print(now.year());
   // }
   // else {
    // Serial.print(now.year());
    //} 
   // Serial.println();
   // delay(1000);
 //}
  
  delay(500);
 
  }

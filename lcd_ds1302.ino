#include <LiquidCrystal.h>
#include <stdio.h>
#include <DS1302.h>
#include <stdlib.h>

int V0 = 3;
int RS = 4;
int E = 5;
int D4 = 6;
int D5 = 7;
int D6 = 8;
int D7 = 9;

const int RST   = 12;   // Chip Enable   // RST
const int DAT   = 11;   // Input/Output  // DAT
const int CLK = 10;     // Serial Clock  // CLK

DS1302 rtc(RST, DAT, CLK);
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

void setup() {
  Serial.begin(9600);
  analogWrite(V0, 50);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("starting");
  rtc.writeProtect(false);
  rtc.halt(false);
  Time t(2018, 6, 7, 14, 8, 50, Time::kThursday);
  rtc.time(t);
}

void loop() {
  delay(1000);
  lcd.clear();
  printTime();
}

String dayAsString(const Time::Day day) {
  switch (day) {
    case Time::kSunday: return "Sunday";
    case Time::kMonday: return "Monday";
    case Time::kTuesday: return "Tuesday";
    case Time::kWednesday: return "Wednesday";
    case Time::kThursday: return "Thursday";
    case Time::kFriday: return "Friday";
    case Time::kSaturday: return "Saturday";
  }
  return "(unknown day)";
}

void printTime() {
  // Get the current time and date from the chip.
  Time t = rtc.time();

  // Name the day of the week.
  const String day = dayAsString(t.day);

  // Format the time and date and insert into the temporary buffer.
  char buf[50];
  snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d %02d:%02d:%02d",
           day.c_str(),
           t.yr, t.mon, t.date,
           t.hr, t.min, t.sec);

  // Print the formatted string to serial so we can see the time.
  Serial.println(buf);
  lcd.print(getTime());
}

String getDatetime() {
  Time t = rtc.time();
  String year = String(t.yr);
  String month = String(t.mon);
  String days = String(t.date);
  String hours = String(t.hr);
  String minutes = String(t.min);
  String seconds = String(t.sec);
  String datetime = year + "-" + month + "-" + days + " " + hours + ":" + minutes + ":" + seconds;
  return datetime;
}

String getTime() {
  Time t = rtc.time();
  
  String h = "";
  String m = "";
  String s = "";
  
  if(t.hr < 10) {
    h = "0" + String(t.hr);
  } else {
    h = String(t.hr);
  }

  if(t.min < 10) {
    m = "0" + String(t.min);
  } else {
    m = String(t.min);
  }

  if(t.sec < 10) {
    s = "0" + String(t.sec);
  } else {
    s = String(t.sec);
  }
  
  String date = h + ":" + m + ":" + s;
  return date;
}

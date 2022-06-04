
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <BlynkSimpleEsp8266.h>

LiquidCrystal_I2C lcd(0x27,16,2);
char auth[] = "m4K5ihwga3o0uXUq9Xchvhw47SNNi51D";
char ssid[] = "xxx";
char pass[] = "xxx";
#define buzPin D7 
#define rsPinD D8//D3
#define rsPinA A0 
#define deviceStatusPin D6
int rsValue;

BlynkTimer timer;
WidgetLED led1(V1);
void setup() {
  Serial.begin(115200);
  delay(20);

  Blynk.begin(auth, ssid, pass);
  
  pinMode(buzPin, OUTPUT);
  pinMode(rsPinD, INPUT);
  pinMode(deviceStatusPin, INPUT);
  pinMode(rsPinA, INPUT); 
  
  digitalWrite(buzPin, HIGH);
  
  timer.setInterval(1000L, blinkLedWidget);

  Wire.begin(4, 5);
  lcd.init();                    
  lcd.backlight();

  lcd.setCursor(3,0);
  lcd.print("Hi everyone");
  lcd.setCursor(2,1);
  lcd.print("This is a TV");
  }
  
void loop()
{
  delay(250);
  getDeviceValue();
  delay(250);
  getRsValue();

  Blynk.run();
  timer.run();
}


void blinkLedWidget()
{
  if(digitalRead(deviceStatusPin)) {
    led1.on();
    Serial.println("LED on V1: on");
  } 
  else {
    led1.off();
    Serial.println("LED on V1: off");
  }
}

void getRsValue(void)
{
  rsValue = digitalRead(rsPin);
  Serial.print("Digital: ");
  Serial.println(rsValue);

  Serial.print("Analog: ");
  Serial.println(digitalRead(rsPinA));

  if (rsValue) 
  { 
    Serial.println("==> Door Opened");
    Blynk.notify("Alert! Someone opened the door on the 1st floor!");  
  }
  digitalWrite(buzPin, rsValue);
}

void getDeviceValue(void)
{ 
  if(digitalRead(deviceStatusPin))
  {
    Serial.println("Device on 1st floor is working");
    Blynk.notify("Device on 1st floor is working");
  }
}

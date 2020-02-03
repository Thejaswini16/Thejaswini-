#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "GG3HJaiOcF6LPVyt_Y8xIcMY7CGRJiHf";

char ssid[] = "AndroidAP";
char pass[] = "theju1999";

int irpin = D1;
int pirpin = D2;
int smokepin = A0;
int led = D3;
int buzzer = D4;
int s;

void setup()
{
  Serial.begin(9600);
  Serial.println("connecting");
  Blynk.begin(auth, ssid, pass);
  Serial.println("Auth");
  pinMode(irpin, INPUT);
  pinMode(pirpin, INPUT);
  pinMode(smokepin, INPUT);

  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.println("connected");
  Blynk.notify("Connected");
}


BLYNK_WRITE(V2)
{
  s = param.asInt();
}

void loop()
{
  Blynk.run();

  int ir = digitalRead(irpin);
  int pir = digitalRead(pirpin);
  int smoke = analogRead(smokepin);
  Blynk.virtualWrite(V3, pir);
  Blynk.virtualWrite(V4, smoke);

  Serial.println(ir);
  Serial.println(pir);
  Serial.println(smoke);

  if (ir == LOW)
  {
    Blynk.virtualWrite(V0, "PRESENT");
    digitalWrite(led, HIGH);
    if (s == HIGH)
    {
      if (pir == HIGH)
      {
        Blynk.notify("Intruder");
        digitalWrite(buzzer, HIGH);
      }
      else if (pir == LOW)
      {
        digitalWrite(buzzer, LOW);
      }
    }
    else
    {

    }

    if (smoke <=  200)
    {
      Blynk.virtualWrite(V1, "smoke detected");
    }
    else
    {
      Blynk.virtualWrite(V1, " ");
    }
  }
  else if (ir == HIGH)
  {
    Blynk.virtualWrite(V0, "ABSENT");

    if (pir == HIGH)
    {
      Blynk.notify("Intruder");
      digitalWrite(buzzer, HIGH);
    }
    else if (pir == LOW)
    {
      digitalWrite(buzzer, LOW);
    }

    if (smoke <= 200)
    {
      Blynk.virtualWrite(V1, "smoke detected");
    }
    else
    {
      Blynk.virtualWrite(V1, " ");
    }
  }
}

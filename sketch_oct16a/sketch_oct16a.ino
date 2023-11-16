// #include <Arduino.h>

// #include <FastLED.h>
// #define LED_PIN 2
// #define NUM_LEDS 16

// int LED_LIGHT = 5;
// CRGB Leds[NUM_LEDS];

// void setup() {
//   FastLED.addLeds<WS2812, LED_PIN, GRB>(Leds, NUM_LEDS);
//   FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
//   FastLED.clear();
//   FastLED.show();
// }

// void loop() {
//   // R G B
//   Leds[0] = CRGB(LED_LIGHT, 0, 0);
//   Leds[1] = CRGB(0, LED_LIGHT, 0);
//   Leds[2] = CRGB(0, 0, LED_LIGHT);
//   FastLED.show();
// }

#include <FastLED.h>
#define LED_PIN 2 // pin do osługi led
#define NUM_LEDS 16 // długosć tasmy led

int LED_LIGHT = 5;
CRGB Leds[NUM_LEDS];

#define outputA 3 // 
#define outputB 4

int counter = 0;
int aState;
int aLastState;

void display(int counter){
  Leds[counter - 1] = CRGB(LED_LIGHT, 0, 0);
  Leds[counter] = CRGB(0, LED_LIGHT, 0);
  Leds[counter + 1] = CRGB(0, 0, LED_LIGHT);
  FastLED.show();
}

int getPosition() {
  aState = digitalRead(outputA); // Odczytuje "bieżący" stan outputA
  // Jeśli poprzedni i obecny stan outputA są różne, oznacza to, że wystąpił impuls
  if (aState != aLastState) {
    // Jeśli stan outputB jest różny od stanu outputA, oznacza to, że enkoder obraca się zgodnie z ruchem wskazówek zegara
    if (digitalRead(outputB) != aState) { 
       counter ++;
      if (counter > NUM_LEDS -1)
       {
          counter = 0;
       }
     } else {
       counter --;
       if (counter < 0)
       {
          counter = NUM_LEDS -1;
       }
     }
    Serial.print("counter: ");
    Serial.println(counter);
  }
  aLastState = aState; // Aktualizuje poprzedni stan outputA na podstawie obecnego stanu

  return counter;
}

void setup() {
  // leds
  FastLED.addLeds<WS2812, LED_PIN, GRB>(Leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  FastLED.clear();
  FastLED.show();

  // encoder
  pinMode(outputA, INPUT); 
  pinMode(outputB, INPUT); 

  Serial.begin(9600);
  // Odczytuje początkowy stan outputA
  aLastState = digitalRead(outputA);
}

void loop() {
  display(getPosition());
}



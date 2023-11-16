#include <Arduino.h>

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

int matrix[NUM_LEDS][2];


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

void displayColor1(int counter){
  Leds[counter - 1] = CRGB(LED_LIGHT, 0, 0);
  FastLED.show();
}

void displayColor2(int counter){
  Leds[counter - 1] = CRGB(0, LED_LIGHT, 0);
  FastLED.show();
}

void displayColor3(int counter){
  Leds[counter - 1] = CRGB(0, 0, LED_LIGHT);
  FastLED.show();
}

void displayOff(int counter){
  Leds[counter - 1] = CRGB(0, 0, 0);
  FastLED.show();
}
void displayMatrixOff(){
  for (size_t i = 0; i < NUM_LEDS; i++)
  {
    matrix[i][0] = 0;
    matrix[i][1] = 0;
  }
}
void displayMatrixPointerOff(int i){
    matrix[i][0] = 0;
    matrix[i][1] = 0;
}
void displayMatrix(int p){
  //todo
  //resetowanie położenia pointera
  for (size_t i = 0; i < NUM_LEDS; i++)
  {
    matrix[i][0] = 0;
  }
  

  // ustawianie pointera POINTER(3)
  matrix[p][0] = 3; // ustawienie poitera(operator)
  matrix[p][1] = 3; // ustawienie poitera(kolor)

  // // dodawanie PRAWO(1)
  // if (p-1 >= 0)
  // {
  //   matrix[p-1][0] = 1;
  // }
  // // dodawanie LEWO(2)
  // if (p+1 <= NUM_LEDS-1)
  // {
  //   matrix[p+1][0] = 2;
  // }
  

  

  // sprawdzanie w --lewo dla operatora PRAWO(1)
  for (size_t i = NUM_LEDS-1; i >= 0; --i)
  {
    // operator = PRAWO(1)
    if (matrix[i][1] == 1){
      // sprawdza czy nie przekrazca tablicy
        if (i-1 <= 0){
          // czy poprzedni operator to POINTER(3)
          if (matrix[i-1][0] == 3)
          {
            //zniszcz obecne
            matrix[i][0] = 0;
            matrix[i][1] = 0;
          }
          // czy poprzedni operator to LEWO(2)
          if (matrix[i-1][0] == 2)
          {
            //zniszcz obecne i poprzednie
            matrix[i][0] = 0;
            matrix[i][1] = 0;
            matrix[i-1][0] = 0;
            matrix[i-1][1] = 0;
          }

        }
        // tablica przekroczona
        else{
          matrix[i][0] = 0;
          matrix[i][1] = 0;
        }
      }
    }
    // sprawdzanie w ++prawo dla operatora LEWO(2)
  for (int i = 0; i <= NUM_LEDS-1; ++i)
  {
    // operator = LEWO(2)
    if (matrix[i][1] == 1){
      // sprawdza czy nie przekrazca tablicy
        if (i+1 >= NUM_LEDS-1){
          // czy następny operator to POINTER(3)
          if (matrix[i+1][0] == 3)
          {
            //zniszcz obecne
            matrix[i][0] = 0;
            matrix[i][1] = 0;
          }
          // czy następny operator to PRAWO(1)
          if (matrix[i+1][0] == 1)
          {
            //zniszcz obecne i poprzednie
            matrix[i][0] = 0;
            matrix[i][1] = 0;
            matrix[i+1][0] = 0;
            matrix[i+1][1] = 0;
          }
        }
        // tablica przekroczona
        else{
          matrix[i][0] = 0;
          matrix[i][1] = 0;
        }
      }
    }
  // zapalanie odpowiednich diod
  for (size_t i = 0; i < NUM_LEDS; i++)
  {
    if (matrix[i][1] == 1)
    {
      displayColor1(i);
    }
    else if(matrix[i][1] == 2){
      displayColor2(i);
    }
    else if(matrix[i][1] == 3){
      displayColor3(i);
    }
    
  }
  delay(200);
}



    // todo przenieśćdo flasza progmen coś takiego
    //matrix memory  [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
    //matrix operator[ ][ ][p][p][p][ ][l][l][l][ ][ ][ ][ ]
    //matrix color   [ ][ ][1][2][1][ ][1][2][3][ ][ ][ ][ ]
  //matrix[i][y][z]:
  //y 3 = pointer
  //y 1 = prawo
  //y 2 = lefo
  //z = colorNumber

  


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
  displayMatrixOff();
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
  // display(getPosition());
  displayMatrix(getPosition());
  delay(200);
}



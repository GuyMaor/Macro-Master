#include <Keyboard.h>
extern const int NUM_ROWS;
extern const int NUM_COLS;
extern const int write_pins[];
extern const int read_pins[];
extern int key_state[];
extern const int key_assignment[];

void setup() {
  Serial.begin(9600);
  for(int row = 0; row < NUM_ROWS; row++){
    pinMode(read_pins[row], INPUT_PULLUP);
  }
  for(int col = 0; col < NUM_COLS; col++){
    pinMode(write_pins[col], OUTPUT);
    digitalWrite(write_pins[col],HIGH);
  }
  Keyboard.begin();
}
void check_keys(){
  for(int col = 0; col < NUM_COLS; col++){
    digitalWrite(write_pins[col],LOW);
    for(int row = 0; row < NUM_ROWS; row++){     
      if(digitalRead(read_pins[row]) == LOW){
        key_state[row * NUM_COLS + col] = 1;
      }
      else{
        key_state[row * NUM_COLS + col] = 0;  
      }
    }
    digitalWrite(write_pins[col],HIGH);
  } 
}
void report_keys(){
  for(int key = 0; key < NUM_ROWS * NUM_COLS; key++){
    if(key_state[key] == 1){
      Keyboard.press(key_assignment[key]);
    }
    else{
      Keyboard.release(key_assignment[key]);
    }
  }
  Serial.print("\n");
}
void loop() {
  check_keys();
  report_keys();
  delay(30);
}

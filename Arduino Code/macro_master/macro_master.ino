#include <Keyboard.h>
extern const int NUM_ROWS;
extern const int NUM_COLS;
extern const int write_pins[];
extern const int read_pins[];
extern const int key_assignment[];

void setup() {
  //Initialize serial port
  Serial.begin(9600);

  //Configure all read pins
  for(int row = 0; row < NUM_ROWS; row++){
    pinMode(read_pins[row], INPUT_PULLUP);
  }

  //Configure all write pins
  for(int col = 0; col < NUM_COLS; col++){
    pinMode(write_pins[col], OUTPUT);
    digitalWrite(write_pins[col],HIGH);
  }

  //Initialize keyboard
  Keyboard.begin();
}

void loop(){
  for(int col = 0; col < NUM_COLS; col++){
    //Activate the column
    digitalWrite(write_pins[col],LOW);

    //Read all keys only in the activated column
    for(int row = 0; row < NUM_ROWS; row++){
      int key_ind = row * NUM_COLS + col;
      if(digitalRead(read_pins[row]) == LOW){
        Keyboard.press(key_assignment[key_ind]);
      }
      else{
        Keyboard.release(key_assignment[key_ind]); 
      }
    }

    //Deactivate the column
    digitalWrite(write_pins[col],HIGH);
  }
  delay(30);  
}

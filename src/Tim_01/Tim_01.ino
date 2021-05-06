// digital pin 2 is the hall pin
int hall_pin = 2;
float hall_count;
 
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  // make the hall pin an input:
  pinMode(hall_pin, INPUT);

}

// the loop routine runs over and over again forever:
void loop() {
  // preallocate values for tach

  bool on_state = false;
  // counting number of times the hall sensor is tripped
  // but without double counting during the same trip

    if (digitalRead(hall_pin)==0){
      if (on_state==false){
        on_state = true;
        hall_count+=1.0;
        Serial.println(hall_count);
      }
    } else{
      on_state = false;
    }

}

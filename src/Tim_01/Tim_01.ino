// digital pin 2 is the hall pin
int hall_pin = 2;
float hall_count;
bool last_hall;
 
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
    
    bool new_hall;

    new_hall = digitalRead(hall_pin);

    if (new_hall != last_hall) {
      last_hall= new_hall;
      hall_count++;
      Serial.println(hall_count);
    }
   

}

// digital pin 2 is the hall pin
int hall_pin = 2;
float hall_count;
bool last_hall;
 
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  // make the hall pin an input:
  pinMode(hall_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(hall_pin), count, RISING);

}

void count(){
  hall_count++;
}

// the loop routine runs over and over again forever:
void loop() {
  // preallocate values for tach

  Serial.println(hall_count);
  delay(500);

}

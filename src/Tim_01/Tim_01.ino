// digital pin 2 is the hall pin
int hall_pin = 2;
int hall_count, last_hall, new_hall;
int rps;

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

  last_hall = new_hall;
  delay(1000);
  new_hall = hall_count;
  rps = new_hall - last_hall;
  Serial.print("RPS: ");
  Serial.println(rps);
  

}

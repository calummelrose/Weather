// digital pin 2 is the hall pin
int hall_pin = 2;
int hall_count, last_hall, new_hall;
int rps;

int timer1_counter;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  // make the hall pin an input:
  pinMode(hall_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(hall_pin), count, RISING);

  // initialize timer1 
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;

  // Set timer1_counter to the correct value for our interrupt interval
  //timer1_counter = 64911;   // preload timer 65536-16MHz/256/100Hz
  //timer1_counter = 64286;   // preload timer 65536-16MHz/256/50Hz
  timer1_counter = 34286;   // preload timer 65536-16MHz/256/2Hz
  
  TCNT1 = timer1_counter;   // preload timer
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();             // enable all interrupts
 

}

void count(){
  hall_count++;
}

ISR(TIMER1_OVF_vect)        // interrupt service routine 
{
  TCNT1 = timer1_counter;   // preload timer
  
  last_hall = new_hall;
  new_hall = hall_count;
  rps = new_hall - last_hall;
  Serial.print("counts: ");
  Serial.println(rps);
  
}

// the loop routine runs over and over again forever:
void loop() {
 

}

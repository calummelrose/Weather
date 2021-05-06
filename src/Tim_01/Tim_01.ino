// weather

/* the hall effect sensor produces a change in logic level 
 * when a pole goes by, and with different poles in the 
 * hardware, we get one count per revolution. We look for
 * a rising edge in the interrupt routine, and update the 
 * count by one everytime the interrupt routine is called.
 *  
 *  We also have a timer interrupt which prints the number 
 *  of counts since the last time the count was printed.
 *  This leaves the main loop free to do other stuff later.
 *  Note that we assume the serial output is handled in hardware, 
 *  and therefore it is ok to print in the interrupt handler. If 
 *  using software serial we need to set a flag to call the print routine
 */


// digital pin 2 is the hall pin
int hall_pin = 2;
int hall_count, last_hall, new_hall;
int rps;
int timer1_counter;
bool do_print;

void setup() {
  do_print = false;
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
  //timer1_counter = 34286;   // preload timer 65536-16MHz/256/2Hz
  //timer1_counter = 17143;   // preload timer 65536-16MHz/512/1Hz 
  timer1_counter = 3500;   // preload timer 65536-16MHz/512/1Hz tuned to work at 1Hz on nano every - results may vary! 
  
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
  do_print = true;
}

void print_count(){
  last_hall = new_hall;
  new_hall = hall_count;
  rps = new_hall - last_hall;
  Serial.print("counts: ");
  Serial.println(rps);  
}

// the loop routine runs over and over again forever:
void loop() {
// handle flags from interrupt routines
if (do_print > 0 ) {
    print_count();
    do_print = false;
  }
}

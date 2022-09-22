unsigned char currentstate = 0;
unsigned char priorstate = 0;
unsigned char ledstate = 0;

#define FAN_OFF   0
#define FAN_LO    1
#define FAN_MED   2
#define FAN_HIGH  3

#define LED_OFF 0x01
#define LED_LOW 0x02
#define LED_MED 0x04
#define LED_HIGH  0x08
#define PBUTTON 0x10

#define LED_ALL (LED_OFF|LED_LOW|LED_MED|LED_HIGH)
byte digitPin[2] = {A0,A1}; //segment select
int segment[6] = {0xFC, 0x18, 0x6C, 0x3C, 0x98, 0xB4};

void setup() {
  // put your setup code here, to run once:
  DDRB |= LED_ALL;
  DDRB &= ~PBUTTON;
  DDRC |= 0x03;
  DDRD |= 0xFC;
  DDRB |= 0x20;
  PORTB |= LED_OFF;
  PORTB |= PBUTTON;//pinMode(12, INPUT_PULLUP);
  PORTC |= 0x03;
  PORTD |= 0xFC;//초기설정
  PORTB |= 0x20;//초기설정
}

void loop() {
  // put your main code here, to run repeatedly:
  currentstate = PINB & PBUTTON;
  if(currentstate && !priorstate)
  {
    if(ledstate < FAN_HIGH)ledstate++;
    else ledstate = FAN_OFF;
    PORTB &= ~LED_ALL;
    PORTB |= (1<<ledstate);
  }
  printSegment();
  
  priorstate = currentstate;

}

void printSegment()
{
  if (ledstate%4 == 1)
  {
    PORTC = 0x01;
    PORTD &= ~segment[1];
    delay(1);
  	PORTD |= segment[1];
    
    PORTC = 0x02;
    PORTD &= ~segment[0];
    delay(1);
  	PORTD |= segment[0];
  }
  
  else if(ledstate%4 == 2)
  {
    PORTC = 0x01;
    PORTD &= ~segment[2];
    PORTB &= ~0x20;
    delay(1);
  	PORTD |= segment[2];
    PORTB |= 0x20;
    
    PORTC = 0x02;
    PORTD &= ~segment[5];
    PORTB &= ~0x20;
    delay(1);
  	PORTD |= segment[5];
    PORTB |= 0x20;
  }
  
  else if(ledstate%4 == 3)
  {
    PORTC = 0x01;
    PORTD &= ~segment[4];
    PORTB &= ~0x20;
    delay(1);
  	PORTD |= segment[4];
    PORTB |= 0x20;
    
    PORTC = 0x02;
    PORTD &= ~segment[3];
    PORTB &= ~0x20;
    delay(1);
  	PORTD |= segment[3];
    PORTB |= 0x20;
  }
}

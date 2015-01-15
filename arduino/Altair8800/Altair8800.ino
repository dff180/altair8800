/*
  Altair8800 Front Panel Controller
  
  Modes: Stop switch on at powerup: Switch test mode
 */

// Commands
byte CMD_NONE         = 0x30; // ASCII 0
byte CMD_STOP         = 0x31;
byte CMD_RUN          = 0x32;
byte CMD_SINGLE_STEP  = 0x33;
byte CMD_EXAMINE      = 0x34;
byte CMD_EXAMINE_NEXT = 0x35;
byte CMD_DEPOSIT      = 0x36;
byte CMD_DEPOSIT_NEXT = 0x37;
byte CMD_RESET        = 0x38;
byte CMD_CLR          = 0x39;
byte CMD_PROTECT      = 0x3A;
byte CMD_UNPROTECT    = 0x3B;
byte CMD_AUX1         = 0x3C;
byte CMD_AUX2         = 0x3D;
byte CMD_AUX3         = 0x3E;
byte CMD_AUX4         = 0x3F;

// Output pins
// Pins 0+1 are used for serial communication

int ALT_D0 = 2;
int ALT_D1 = 3;
int ALT_D2 = 4;
int ALT_D3 = 5;
int ALT_D4 = 6;
int ALT_D5 = 7;
int ALT_D6 = 8;
int ALT_D7 = 9;

int ALT_HLTA  = 10;
int ALT_STACK = 11;
int ALT_WO    = 12;
int ALT_INT   = 13;

int ALT_A0  = 14;
int ALT_A1  = 15;
int ALT_A2  = 16;
int ALT_A3  = 17;
int ALT_A4  = 18;
int ALT_A5  = 19;
int ALT_A6  = 20;
int ALT_A7  = 21;
int ALT_A8  = 22;
int ALT_A9  = 23;
int ALT_A10 = 24;
int ALT_A11 = 25;
int ALT_A12 = 26;
int ALT_A13 = 27;
int ALT_A14 = 28;
int ALT_A15 = 29;

int ALT_OUT  = 30;
int ALT_MI   = 31;
int ALT_INP  = 32;
int ALT_MEMR = 33;
int ALT_PROT = 34;
int ALT_INTE = 35;
int ALT_HLDA = 36;
int ALT_WAIT = 37;

// Input pins
int ALT_STOP         = 53;
int ALT_RUN          = 52;
int ALT_SINGLE_STEP  = 51;
int ALT_EXAMINE      = 50;
int ALT_EXAMINE_NEXT = 49;
int ALT_DEPOSIT      = 48;
int ALT_DEPOSIT_NEXT = 47;
int ALT_RESET        = 46;
int ALT_CLR          = 45;
int ALT_PROTECT      = 44;
int ALT_UNPROTECT    = 43;
int ALT_AUX1         = 42;
int ALT_AUX2         = 41;
int ALT_AUX3         = 40;
int ALT_AUX4         = 39;
int ALT_ON           = 38;

int ALT_DA0 = A0;
int ALT_DA1 = A1;
int ALT_DA2 = A2;
int ALT_DA3 = A3;
int ALT_DA4 = A4;
int ALT_DA5 = A5;
int ALT_DA6 = A6;
int ALT_DA7 = A7;
int ALT_DA8 = A8;
int ALT_DA9 = A9;
int ALT_DA10 = A10;
int ALT_DA11 = A11;
int ALT_DA12 = A12;
int ALT_DA13 = A13;
int ALT_DA14 = A14;
int ALT_DA15 = A15;

//int switchSingleStep;
int switchDA0;
int command;
int debounceWait = 20;

int serialInPCLow;
int serialInPCHigh;
int serialInData;

//long lastDebounceTime = 0;  // the last time the output pin was toggled
//long debounceDelay = 50;    // the debounce time; increase if the output flickers

// the setup routine runs once when you press reset:
void setup() {  
  // Output pins
  pinMode(ALT_INTE, OUTPUT);     
  pinMode(ALT_PROT, OUTPUT);     
  pinMode(ALT_MEMR, OUTPUT);     
  pinMode(ALT_INP, OUTPUT);     
  pinMode(ALT_MI, OUTPUT);     
  pinMode(ALT_OUT, OUTPUT);     
  pinMode(ALT_HLTA, OUTPUT);     
  pinMode(ALT_STACK, OUTPUT);     
  pinMode(ALT_WO, OUTPUT);     
  pinMode(ALT_INT, OUTPUT);     
    
  pinMode(ALT_D0, OUTPUT);     
  pinMode(ALT_D1, OUTPUT);     
  pinMode(ALT_D2, OUTPUT);     
  pinMode(ALT_D3, OUTPUT);     
  pinMode(ALT_D4, OUTPUT);     
  pinMode(ALT_D5, OUTPUT);     
  pinMode(ALT_D6, OUTPUT);     
  pinMode(ALT_D7, OUTPUT);     


  pinMode(ALT_WAIT, OUTPUT);     
  pinMode(ALT_HLDA, OUTPUT);     

  pinMode(ALT_A0, OUTPUT);     
  pinMode(ALT_A1, OUTPUT);     
  pinMode(ALT_A2, OUTPUT);     
  pinMode(ALT_A3, OUTPUT);     
  pinMode(ALT_A4, OUTPUT);     
  pinMode(ALT_A5, OUTPUT);     
  pinMode(ALT_A6, OUTPUT);     
  pinMode(ALT_A7, OUTPUT);     
  pinMode(ALT_A8, OUTPUT);     
  pinMode(ALT_A9, OUTPUT);     
  pinMode(ALT_A10, OUTPUT);     
  pinMode(ALT_A11, OUTPUT);     
  pinMode(ALT_A12, OUTPUT);     
  pinMode(ALT_A13, OUTPUT);     
  pinMode(ALT_A14, OUTPUT);     
  pinMode(ALT_A15, OUTPUT);     
  
  // Input pins
  pinMode(ALT_STOP, INPUT_PULLUP);     
  pinMode(ALT_RUN, INPUT_PULLUP);     
  pinMode(ALT_SINGLE_STEP, INPUT_PULLUP);     
  pinMode(ALT_EXAMINE, INPUT_PULLUP);     
  pinMode(ALT_EXAMINE_NEXT, INPUT_PULLUP);     
  pinMode(ALT_DEPOSIT, INPUT_PULLUP);     
  pinMode(ALT_DEPOSIT_NEXT, INPUT_PULLUP);     
  pinMode(ALT_RESET, INPUT_PULLUP);     
  pinMode(ALT_CLR, INPUT_PULLUP);     
  pinMode(ALT_PROTECT, INPUT_PULLUP);     
  pinMode(ALT_UNPROTECT, INPUT_PULLUP);     
  pinMode(ALT_AUX1, INPUT_PULLUP);     
  pinMode(ALT_AUX2, INPUT_PULLUP);     
  pinMode(ALT_AUX3, INPUT_PULLUP);     
  pinMode(ALT_AUX4, INPUT_PULLUP);     
  pinMode(ALT_ON, INPUT_PULLUP);     

  pinMode(ALT_DA0, INPUT_PULLUP);     
  pinMode(ALT_DA1, INPUT_PULLUP);     
  pinMode(ALT_DA2, INPUT_PULLUP);     
  pinMode(ALT_DA3, INPUT_PULLUP);     
  pinMode(ALT_DA4, INPUT_PULLUP);     
  pinMode(ALT_DA5, INPUT_PULLUP);     
  pinMode(ALT_DA6, INPUT_PULLUP);     
  pinMode(ALT_DA7, INPUT_PULLUP);     
  pinMode(ALT_DA8, INPUT_PULLUP);     
  pinMode(ALT_DA9, INPUT_PULLUP);     
  pinMode(ALT_DA10, INPUT_PULLUP);     
  pinMode(ALT_DA11, INPUT_PULLUP);     
  pinMode(ALT_DA12, INPUT_PULLUP);     
  pinMode(ALT_DA13, INPUT_PULLUP);     
  pinMode(ALT_DA14, INPUT_PULLUP);     
  pinMode(ALT_DA15, INPUT_PULLUP);     
  
  testLED();

  // Mode selection
  if (isOn(ALT_STOP))
  {
    modeSwitchTest(); // will not exit
  }

  // start serial port
  Serial.begin(9600);
  
  // Send serial ready signal
  Serial.print('S'); 

}

int blinkLED(int led)
{
  digitalWrite(led, HIGH);
  delay(100);
  digitalWrite(led, LOW);
}

void testLED()
{
  digitalWrite(ALT_INTE, HIGH);
  digitalWrite(ALT_PROT, HIGH);
  digitalWrite(ALT_MEMR, HIGH);
  digitalWrite(ALT_INP, HIGH);
  digitalWrite(ALT_MI, HIGH);
  digitalWrite(ALT_OUT, HIGH);
  digitalWrite(ALT_HLTA, HIGH);
  digitalWrite(ALT_STACK, HIGH);
  digitalWrite(ALT_WO, HIGH);
  digitalWrite(ALT_INT, HIGH);  
  
  digitalWrite(ALT_D0, HIGH);
  digitalWrite(ALT_D1, HIGH);
  digitalWrite(ALT_D2, HIGH);
  digitalWrite(ALT_D3, HIGH);
  digitalWrite(ALT_D4, HIGH);
  digitalWrite(ALT_D5, HIGH);
  digitalWrite(ALT_D6, HIGH);
  digitalWrite(ALT_D7, HIGH);

  digitalWrite(ALT_WAIT, HIGH);  
  digitalWrite(ALT_HLDA, HIGH);  

  digitalWrite(ALT_A0, HIGH);
  digitalWrite(ALT_A1, HIGH);
  digitalWrite(ALT_A2, HIGH);
  digitalWrite(ALT_A3, HIGH);
  digitalWrite(ALT_A4, HIGH);
  digitalWrite(ALT_A5, HIGH);
  digitalWrite(ALT_A6, HIGH);
  digitalWrite(ALT_A7, HIGH);
  digitalWrite(ALT_A8, HIGH);
  digitalWrite(ALT_A9, HIGH);
  digitalWrite(ALT_A10, HIGH);
  digitalWrite(ALT_A11, HIGH);
  digitalWrite(ALT_A12, HIGH);
  digitalWrite(ALT_A13, HIGH);
  digitalWrite(ALT_A14, HIGH);
  digitalWrite(ALT_A15, HIGH);
  delay(1000);              

  digitalWrite(ALT_INTE, LOW);
  digitalWrite(ALT_PROT, LOW);
  digitalWrite(ALT_MEMR, LOW);
  digitalWrite(ALT_INP, LOW);
  digitalWrite(ALT_MI, LOW);
  digitalWrite(ALT_OUT, LOW);
  digitalWrite(ALT_HLTA, LOW);
  digitalWrite(ALT_STACK, LOW);
  digitalWrite(ALT_WO, LOW);
  digitalWrite(ALT_INT, LOW);  

  digitalWrite(ALT_D0, LOW);
  digitalWrite(ALT_D1, LOW);
  digitalWrite(ALT_D2, LOW);
  digitalWrite(ALT_D3, LOW);
  digitalWrite(ALT_D4, LOW);
  digitalWrite(ALT_D5, LOW);
  digitalWrite(ALT_D6, LOW);
  digitalWrite(ALT_D7, LOW);


  digitalWrite(ALT_WAIT, LOW);  
  digitalWrite(ALT_HLDA, LOW);  

  digitalWrite(ALT_A0, LOW);
  digitalWrite(ALT_A1, LOW);
  digitalWrite(ALT_A2, LOW);
  digitalWrite(ALT_A3, LOW);
  digitalWrite(ALT_A4, LOW);
  digitalWrite(ALT_A5, LOW);
  digitalWrite(ALT_A6, LOW);
  digitalWrite(ALT_A7, LOW);  
  digitalWrite(ALT_A8, LOW);
  digitalWrite(ALT_A9, LOW);
  digitalWrite(ALT_A10, LOW);
  digitalWrite(ALT_A11, LOW);
  digitalWrite(ALT_A12, LOW);
  digitalWrite(ALT_A13, LOW);
  digitalWrite(ALT_A14, LOW);
  digitalWrite(ALT_A15, LOW);  
  delay(500);

  blinkLED(ALT_INTE);
  blinkLED(ALT_PROT);
  blinkLED(ALT_MEMR);
  blinkLED(ALT_INP);
  blinkLED(ALT_MI);
  blinkLED(ALT_OUT);
  blinkLED(ALT_HLTA);
  blinkLED(ALT_STACK);
  blinkLED(ALT_WO);
  blinkLED(ALT_INT);

  blinkLED(ALT_D7);
  blinkLED(ALT_D6);
  blinkLED(ALT_D5);
  blinkLED(ALT_D4);
  blinkLED(ALT_D3);
  blinkLED(ALT_D2);
  blinkLED(ALT_D1);
  blinkLED(ALT_D0);


  blinkLED(ALT_WAIT);
  blinkLED(ALT_HLDA);

  blinkLED(ALT_A15);
  blinkLED(ALT_A14);
  blinkLED(ALT_A13);
  blinkLED(ALT_A12);
  blinkLED(ALT_A11);
  blinkLED(ALT_A10);
  blinkLED(ALT_A9);
  blinkLED(ALT_A8);
  blinkLED(ALT_A7);
  blinkLED(ALT_A6);
  blinkLED(ALT_A5);
  blinkLED(ALT_A4);
  blinkLED(ALT_A3);
  blinkLED(ALT_A2);
  blinkLED(ALT_A1);
  blinkLED(ALT_A0);
}

void setLED(int led, int value, int comparison)
{
  if (value & comparison)
   digitalWrite(led, HIGH);
  else
   digitalWrite(led, LOW);   
}

int isDAOn(int da)
{
  int value = analogRead(da);
  if (value < 512)
    return 1;
  else
    return 0;
}

void getDA(byte & low, byte & high)
{
  low = 0x00;
  high = 0x00;
  if (isDAOn(ALT_DA0))
    low |= 1;
  if (isDAOn(ALT_DA1))
    low |= 2;
  if (isDAOn(ALT_DA2))
    low |= 4;
  if (isDAOn(ALT_DA3))
    low |= 8;
  if (isDAOn(ALT_DA4))
    low |= 16;
  if (isDAOn(ALT_DA5))
    low |= 32;
  if (isDAOn(ALT_DA6))
    low |= 64;
  if (isDAOn(ALT_DA7))
    low |= 128;
    
  if (isDAOn(ALT_DA8))
    high |= 1;
  if (isDAOn(ALT_DA9))
    high |= 2;
  if (isDAOn(ALT_DA10))
    high |= 4;
  if (isDAOn(ALT_DA11))
    high |= 8;
  if (isDAOn(ALT_DA12))
    high |= 16;
  if (isDAOn(ALT_DA13))
    high |= 32;
  if (isDAOn(ALT_DA14))
    high |= 64;
  if (isDAOn(ALT_DA15))
    high |= 128;

}

int isOn(int commandSwitch)
{
  int digitalSwitchState;  
  digitalSwitchState = digitalRead(commandSwitch);
  if (digitalSwitchState == LOW)
    return 1;
  else
    return 0;
  
}
void modeSwitchTest()
{
  while(1)
  {
    byte low, high;
    getDA(low, high);
    setLED(ALT_A0, low, 0x01);
    setLED(ALT_A1, low, 0x02);
    setLED(ALT_A2, low, 0x04);
    setLED(ALT_A3, low, 0x08);
    setLED(ALT_A4, low, 0x10);
    setLED(ALT_A5, low, 0x20);
    setLED(ALT_A6, low, 0x40);
    setLED(ALT_A7, low, 0x80);
  
    setLED(ALT_A8, high, 0x01);
    setLED(ALT_A9, high, 0x02);
    setLED(ALT_A10, high, 0x04);
    setLED(ALT_A11, high, 0x08);
    setLED(ALT_A12, high, 0x10);
    setLED(ALT_A13, high, 0x20);
    setLED(ALT_A14, high, 0x40);
    setLED(ALT_A15, high, 0x80);
    
    if (isOn(ALT_STOP) || isOn(ALT_RUN))
      setLED(ALT_D7, 0x01, 0x01);
    else
      setLED(ALT_D7, 0x00, 0x01);
     
    if (isOn(ALT_SINGLE_STEP))
      setLED(ALT_D6, 0x01, 0x01);
    else
      setLED(ALT_D6, 0x00, 0x01);
    
    if (isOn(ALT_EXAMINE) || isOn(ALT_EXAMINE_NEXT))
      setLED(ALT_D5, 0x01, 0x01);
    else
      setLED(ALT_D5, 0x00, 0x01);

    if (isOn(ALT_DEPOSIT) || isOn(ALT_DEPOSIT_NEXT))
      setLED(ALT_D4, 0x01, 0x01);
    else
      setLED(ALT_D4, 0x00, 0x01);

    if (isOn(ALT_RESET) || isOn(ALT_CLR))
      setLED(ALT_D3, 0x01, 0x01);
    else
      setLED(ALT_D3, 0x00, 0x01);

    if (isOn(ALT_PROTECT) || isOn(ALT_UNPROTECT))
      setLED(ALT_D2, 0x01, 0x01);
    else
      setLED(ALT_D2, 0x00, 0x01);

    if (isOn(ALT_AUX1) || isOn(ALT_AUX2))
      setLED(ALT_D1, 0x01, 0x01);
    else
      setLED(ALT_D1, 0x00, 0x01);

    if (isOn(ALT_AUX3) || isOn(ALT_AUX4))
      setLED(ALT_D0, 0x01, 0x01);
    else
      setLED(ALT_D0, 0x00, 0x01);

    if (isOn(ALT_ON))
      setLED(ALT_INTE, 0x01, 0x01);
    else
      setLED(ALT_INTE, 0x00, 0x01);
    
    delay(10);
  }
}


// the loop routine runs over and over again forever:
void loop() 
{
  int digitalSwitchState;

  // Check for command switch toggle
  command = CMD_NONE;
  
  if (isOn(ALT_STOP))
    command = CMD_STOP;
  else if (isOn(ALT_RUN))
    command = CMD_RUN;
  else if (isOn(ALT_SINGLE_STEP))
    command = CMD_SINGLE_STEP;
  else if (isOn(ALT_EXAMINE))
    command = CMD_EXAMINE;
  else if (isOn(ALT_EXAMINE_NEXT))
    command = CMD_EXAMINE_NEXT;
  else if (isOn(ALT_DEPOSIT))
    command = CMD_DEPOSIT;
  else if (isOn(ALT_DEPOSIT_NEXT))
    command = CMD_DEPOSIT_NEXT;
  else if (isOn(ALT_RESET))
    command = CMD_RESET;
  else if (isOn(ALT_CLR))
    command = CMD_CLR;
  else if (isOn(ALT_PROTECT))
    command = CMD_PROTECT;
  else if (isOn(ALT_UNPROTECT))
    command = CMD_UNPROTECT;

  // Send commands via serial
  
  if (command != CMD_NONE)
  {
    // Write command and wait for response
    Serial.write(command);
        
    if (command == CMD_EXAMINE)
    {
      byte low, high;
      getDA(low, high);
      Serial.write(low);
      Serial.write(high);
    }
    else if ((command == CMD_DEPOSIT) || (command == CMD_DEPOSIT_NEXT))
    {
      byte low, high;
      getDA(low, high);
      Serial.write(low);      
    }
    
    while (Serial.available() < 3)
      ;
      
    serialInPCLow = Serial.read();
    serialInPCHigh = Serial.read();
    serialInData = Serial.read();
    setLED(ALT_D0, serialInData, 0x01);
    setLED(ALT_D1, serialInData, 0x02);
    setLED(ALT_D2, serialInData, 0x04);
    setLED(ALT_D3, serialInData, 0x08);
    setLED(ALT_D4, serialInData, 0x10);
    setLED(ALT_D5, serialInData, 0x20);
    setLED(ALT_D6, serialInData, 0x40);
    setLED(ALT_D7, serialInData, 0x80);
    
    setLED(ALT_A0, serialInPCLow, 0x01);
    setLED(ALT_A1, serialInPCLow, 0x02);
    setLED(ALT_A2, serialInPCLow, 0x04);
    setLED(ALT_A3, serialInPCLow, 0x08);
    setLED(ALT_A4, serialInPCLow, 0x10);
    setLED(ALT_A5, serialInPCLow, 0x20);
    setLED(ALT_A6, serialInPCLow, 0x40);
    setLED(ALT_A7, serialInPCLow, 0x80);

    setLED(ALT_A8, serialInPCHigh, 0x01);
    setLED(ALT_A9, serialInPCHigh, 0x02);
    setLED(ALT_A10, serialInPCHigh, 0x04);
    setLED(ALT_A11, serialInPCHigh, 0x08);
    setLED(ALT_A12, serialInPCHigh, 0x10);
    setLED(ALT_A13, serialInPCHigh, 0x20);
    setLED(ALT_A14, serialInPCHigh, 0x40);
    setLED(ALT_A15, serialInPCHigh, 0x80);
     
    // Wait for command switch release
    if (command == CMD_SINGLE_STEP)
    {
// TODO use code when singlestepcontinue is connected
/*
      do
      {
        digitalSwitchState = digitalRead(ALT_SINGLE_STEP);
      }
      while (digitalSwitchState == LOW);
*/      
      delay(debounceWait); // debounce
    }
    else if (command == CMD_EXAMINE)
    {
      while (isOn(ALT_EXAMINE)) 
        ;
      delay(debounceWait); // debounce
    }
    else if (command == CMD_EXAMINE_NEXT)
    {
      while (isOn(ALT_EXAMINE_NEXT)) 
        ;
      delay(debounceWait); // debounce
    }
    else if (command == CMD_DEPOSIT)
    {
      while (isOn(ALT_DEPOSIT))
        ;
      delay(debounceWait); // debounce
    }
    else if (command == CMD_DEPOSIT_NEXT)
    {
      while (isOn(ALT_DEPOSIT_NEXT))
        ;
      delay(debounceWait); // debounce
    }
  }
}



//*****************************************************************************
//Toggle MIDI
//*****************************************************************************
//switches between 3 MIDI modes: MIDI off, baud rate 115200, and baud rate 31250

void toggleMIDI()
{
 MIDIstate++;
 if (MIDIstate == 3) {MIDIstate = 0;}
 EEPROM.write(370,MIDIstate);
 
 if (MIDIstate == 0)
   for (int i = 0; i < 3; i++) {
     delay(100);
     PORTD |= _BV(PD4);
     delay(100);
     PORTD &= ~_BV(PD4);
     }
     
 if (MIDIstate == 1)
   for (int i = 0; i < 3; i++) {
     delay(100);
     PORTD |= _BV(PD2);
     delay(100);
     PORTD &= ~_BV(PD2);
     }
     
 if (MIDIstate == 2)
     for (int i = 0; i < 3; i++) {
      delay(100);
     PORTD |= _BV(PD2);
     PORTD |= _BV(PD4);
     delay(100);
     PORTD &= ~_BV(PD2);
     PORTD &= ~_BV(PD4);
     }
     
  delay(500);
}
//*****************************************************************************
//Adafruit Button Checker
//*****************************************************************************

void check_switches()
{
  static byte previousstate[NUMBUTTONS];
  static byte currentstate[NUMBUTTONS];
  static long lasttime;
  static long longPressTime[NUMBUTTONS] = {0,0,0,0,0};
  static long extraLongPressTime[NUMBUTTONS] = {0,0,0,0,0};
  byte index;

  if (millis() < lasttime) {// we wrapped around, lets just try again
    lasttime = millis();
  }

  if ((lasttime + DEBOUNCE) > millis()) {// not enough time has passed to debounce
    return; 
  }// ok we have waited DEBOUNCE milliseconds, lets reset the timer
  lasttime = millis();

  for (index = 0; index < NUMBUTTONS; index++) {
    justpressed[index] = 0;       // when we start, we clear out the "just" indicators
    justreleased[index] = 0;

    currentstate[index] = digitalRead(buttons[index]);   // read the button

    if (currentstate[index] == previousstate[index]) {
      if ((pressed[index] == LOW) && (currentstate[index] == LOW)) {// just pressed
        justpressed[index] = 1;
      }
      else if ((pressed[index] == HIGH) && (currentstate[index] == HIGH)) {// just released
        
         justreleased[index] = 1;}
         

      pressed[index] = !currentstate[index];  // remember, digital HIGH means NOT pressed
    }
    //Serial.println(pressed[index], DEC);
    previousstate[index] = currentstate[index];   // keep a running tally of the buttons
    
    
    //*********************************************************************************************************longPress, extralongpress, and mode changes added by AM 2015
    
    if (justpressed[index]) {longPressTime[index] = millis();}
      
      
     if (!pressed[index]) {longPressTime[index] = 0;}
      
      
    if (pressed[index]  && !justreleased[index] && ((millis()-longPressTime[index]) > 250)){
     longpress[index] = 1;}
      
    if(justreleased[index] && longpress[index]){
      longpress[index] = 0;
      longPressTime[index] = millis();}
        
        
        
         //*********************************************************************************************************extraLongPress
    
    if (justpressed[index]) {extraLongPressTime[index] = millis();}
      
      
     if (!pressed[index]) {extraLongPressTime[index] = 0;}
      
      
    if (pressed[index]  && !justreleased[index] && ((millis()-extraLongPressTime[index]) > 2000)){
     extralongpress[index] = 1;}
      
    if(justreleased[index] && extralongpress[index]){
      extralongpress[index] = 0;
      extraLongPressTime[index] = millis();}
        
        
    //here we decrement the modeChange flags if they are on and a button has just been released. Then we cancel the justreleased flag because it was only needed to change modes and we don't want it to do anything else.     
    
    if (modeChange > 0 && justreleased[index]){     
          justreleased[index] = 0;
       modeChange-=1;}
           
      }
  }


//*****************************************************************************
//Pot Checker
//*****************************************************************************
//tells us if the pots have been turned since they were last locked.

void check_pots()
{
 
  static boolean firstRead[5]={0,0,0,0,0}; //true if an initial pot reading has been taken
  static int previousReading[5]={5000,5000,5000,5000,5000}; //an initial reading for monitoring whether a pot has been turned. Set to a high value at first for debugging

     for (int i = 0; i < 5; i++) {
    
      if  (livePots[i]==0 && firstRead[i]==0) {
        
         previousReading[i] = analogRead(i) ; //get an initial value for each pot so we can tell when it is first turned
         firstRead [i] = 1;} //note that we've taken a first reading 
       
       if (((POT[i] < 2000 && previousReading[i] < 2000) && (POT[i] > ((previousReading[i] + 10)) || ((POT[i] < (previousReading[i] - 10)))))) { //Get another value to see if the pot has been turned more than ~1/10th revolution. If so, unlock the pot.
          livePots[i] = 1;
          firstRead [i] = 0;} //now that the pot is unlocked we'll need a new initial reading next time it's locked.
      }
 }


//*****************************************************************************
//Lock Pots
//*****************************************************************************

//um, locks the pots.

void lock_pots()
{
   for (int i = 0; i < 5; i++) {
     livePots[i]=0;}
}


//*****************************************************************************
//Pot Reader
//*****************************************************************************

//reads the pots.

void get_pots()
{

  for (int i = 0; i < 5; i++) {
    
  analogRead(i); //throw this one away to give the ADC some time after switching between pots.
  POT[i] = analogRead(i); //save this one
     if (POT[i] > 1023){ //if for some reason we get a wacky reading,
      POT[i] = analogRead(i);} // throw it away and try again.
  }
}

//*****************************************************************************
//Battery Checker
//*****************************************************************************
//taken from: https://code.google.com/p/tinkerit/wiki/SecretVoltmeter

void check_battery() {

if (version == 2){//this first part is the battery checker for MintySynth rev. 2.0 and higher.
  long result;
  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  result = 1126400L / result; // Back-calculate AVcc in mV
  
  if (result <= 2200){ //if the batteries are low, pause the music and blink the LEDs a few times.
     
     edgar.suspend();
   
     for (int i = 0; i < 7; i++) {
        delay(250);
       PORTD |= _BV(PD2);
       PORTD |= _BV(PD4);
       delay(250);
       PORTD &= ~_BV(PD2);
       PORTD &= ~_BV(PD4);
   
     batteryLow=1; 
   
     edgar.resume();}
}}

else{
//this is the battery checker for MintySynth rev. 1.3 and earlier.

  unsigned int battery[9]; //stores battery readings
  int sorted_array[9]; //holds the sorted values
  
   analogRead(5); //throw this one away
  
  for (int i = 0; i < 9; i++) {
    
  battery[i] = analogRead(5);} //save these 9
  
memcpy(sorted_array, battery, sizeof (int) * 9);

//an insert sort to find the median value
 for (int z = 1; z < 9; ++z){
   int j = sorted_array[z];
   int k;
   for (k = z - 1; (k >= 0) && (j < sorted_array[k]); k--){
     sorted_array[k + 1] = sorted_array[k];}
      sorted_array[k + 1] = j;}
 
 batteryLevel = sorted_array[4];
   
   if (batteryLevel <= 460){ //if the batteries are low, pause the music and blink the LEDs a few times.
     
     edgar.suspend();
   
    for (int i = 0; i < 7; i++) {
      delay(250);
   PORTD |= _BV(PD2);
   PORTD |= _BV(PD4);
   delay(250);
   PORTD &= ~_BV(PD2);
   PORTD &= ~_BV(PD4);
   
   batteryLow=1; 
   
   edgar.resume();}
 }

}}


//*****************************************************************************
//Flash Leds
//*****************************************************************************

//the flash pattern when music is playing. We turn the LEDs off again in the main loop.

void flash_leds()
{
  
   if (programMode == 4){    
  
      if (thisStep == 0 || thisStep == 4 || thisStep == 8 || thisStep == 12) {//turn on LED 2 for the 1st, 4th, 8th, and 12th steps in the sequence if we're in Live Mode.
        PORTD |= _BV(PD4); //LED 2 (direct port manipulation)
        LED2state = 1;}}
   
   if (programMode < 4){//turn on LED 1 for the 1st, 4th, 8th, and 12th steps in the sequence if we're in Program Mode.
    
        if (thisStep == 0 || thisStep == 4 || thisStep == 8 || thisStep == 12) {     
          PORTD |= _BV(PD2);
          LED1state = 1;}}
}


//*****************************************************************************
//Save
//*****************************************************************************

//save current song to selected bank (0-3) in Eeprom

void save(int bank)
{
  
edgar.suspend();

  PORTD &= ~_BV(PD2); //make sure the LEDs are off
  PORTD &= ~_BV(PD4);
  for (int i = 0; i < 4; i++) { //flash LED 1 to indicate a save
   PORTD |= _BV(PD2); 
   delay(25);
   PORTD &= ~_BV(PD2);
   delay(200);}
  
  //write current song preferences to bank
   
    for (int i = 0; i < 4; i++) { 
    
     for (int j = 0; j < 7; j++) {
  
       EEPROM.write(bank*92 + (7 * i + j), (voicePrefs[2][i][j]));}}
       
       
   //write current song notes to bank
   
    for (int i = 0; i < 4; i++) { 
    
     for (int j = 0; j < 16; j++) {
  
       EEPROM.write(28 + bank*92 + (16 * i + j), (song[2][i][j]));}}
         
 edgar.resume();
}
 
//*****************************************************************************
//Load
//*****************************************************************************

//load song from selected bank (0-3) in Eeprom to bank 2 in voicePrefs and song.

void load(int bank)
{

   edgar.suspend(); 
   for(int i=0;i<4;i++){MIDI.sendControlChange(123,0,i);} //turn all the MIDI notes off 
   PORTD &= ~_BV(PD2); //make sure the LEDs are off
   PORTD &= ~_BV(PD4);
   for (int i = 0; i < 4; i++) { //flash LED 2 to indicate a load
   PORTD |= _BV(PD4);
   delay(10);
   PORTD &= ~_BV(PD4);
   delay(100);}
  
  //load current song preferences from bank
   
    for (int i = 0; i < 4; i++) { 
    
     for (int j = 0; j < 7; j++) {
  
       voicePrefs[2][i][j] = EEPROM.read(bank*92 + (7 * i + j));}}
       
       
   //load current song notes from bank
   
    for (int i = 0; i < 4; i++) { 
    
     for (int j = 0; j < 16; j++) {
  
       song[2][i][j] = EEPROM.read((bank*92 + 28) + (16 * i + j));}}
       
   Current = 2; //set the currently playing song to the bank that was just loaded.
   thisStep = 0; //begin at the first note in the song.
   songShift = 0; //reset song shift and scale shift.
   scaleShift = 0;
   lock_pots;
    
 appendMode = 0;
  
   edgar.resume(); 
}


//*****************************************************************************
//Append
//*****************************************************************************

//load song from selected bank (0-3) in Eeprom to the corresponding bank location in voicePrefs and song.

void append(int bank)
{

   for(int i=0;i<4;i++){MIDI.sendControlChange(123,0,i);} //turn all the MIDI notes off
   edgar.suspend();  
   PORTD &= ~_BV(PD2); //make sure the LEDs are off
   PORTD &= ~_BV(PD4);
   for (int i = 0; i < 4; i++) { //flash LED 2 to indicate a load
   PORTD |= _BV(PD4);
   delay(10);
   PORTD &= ~_BV(PD4);
   delay(100);}
  
  //load current song preferences from bank
   
    for (int i = 0; i < 4; i++) { 
    
     for (int j = 0; j < 7; j++) {
  
       voicePrefs[bank + 2][i][j] = EEPROM.read(bank*92 + (7 * i + j));}}
       
       
   //load current song notes from bank
   
    for (int i = 0; i < 4; i++) { 
    
     for (int j = 0; j < 16; j++) {
  
       song[bank + 2][i][j] = EEPROM.read((bank*92 + 28) + (16 * i + j));}}
  
   Current = 2; //set the currently playing song to bank 2 to start with.
   thisStep = 0; //begin at the first note in the song.
   songShift = 0; //reset song shift and scale shift.
   scaleShift = 0;
   lock_pots; 
  
   edgar.resume(); 
   }
   
//*****************************************************************************
//Binary LED Indicator
//*****************************************************************************

//counts from 0-4 in binary with the LEDs and repeats for numbers greater than 4.

void showBinary(int count)
{
  if (count % 2 == 0){
      PORTD &= ~_BV(PD4);}
      else {PORTD |= _BV(PD4);}
      if (count % 4 == 2 || count % 4 == 3 ){
      PORTD |= _BV(PD2);}
      else {PORTD &= ~_BV(PD2);}
}
   
//*****************************************************************************
//Print the Four Stored Songs to the Serial Monitor
//*****************************************************************************

void printSongs()
{
  Serial.println("voicePrefs, songs 2-5");
  for (int h = 0; h < 4; h++) {
    Serial.println("");
    Serial.print("{");
     for (int i = 0; i < 4; i++) {
       Serial.print("{");
       for (int j = 0; j < 7; j++) { 
         Serial.print(EEPROM.read(h*92 + (7 * i + j)));
         if (j < 6) {Serial.print(",");}}
       Serial.print("}");
       if (i < 3) {Serial.println(",");}}
     Serial.print("},");
   Serial.println("");}
   
   Serial.println("");
   Serial.println("");
   Serial.println("");
   
     Serial.println("song, songs 2-5");
  for (int h = 0; h < 4; h++) {
    Serial.println("");
    Serial.print("{");
     for (int i = 0; i < 4; i++) {
       Serial.print("{");
       for (int j = 0; j < 16; j++) { 
         Serial.print(EEPROM.read(28 + h*92 + (16 * i + j)));
         if (j < 15) {Serial.print(",");}}
       Serial.print("}");
       if (i < 3) {Serial.println(",");}}
     Serial.print("},");
   Serial.println("");}
}


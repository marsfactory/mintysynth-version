/*MintySynth
a four voice, 16-step wavetable sequencer, using five pots, five tact switches, and two LEDs.
Andrew Mowry 2015
http://mintysynth.com
Please see the web site for the hardware setup: http://mintysynth.com/hardware.html 
The software is designed for the MintySynth kit, but should work fine with an Arduino Uno or other Arduino running at 16 Mhz. See the Illutron link below for more details.

Version History:

Hardware revision 1.3 ships with 3.3, 3,4, or 3.5.
Hardware revision 2.0 ships with 4.1.

3.3 Added MIDI functionality.
3.4 Fixed unintentional changing of sound parameters if you turn a thumbwheel too fast (less than 200 ms) after holding a button down while sequencing notes, entering Mixer Mode, or reprogramming buttons. Now the sound paramters are only changed if no button is held.
    Also added disabling of digital input buffers on the analog pins at startup.
3.5 Changed the Program Mode reference notes from voice 9 to voice 10.
    Fixed a minor bug that prevented scaleShift from being reset to 0 when a saved song is reloaded.
    Also made it so voice 0 is temporarily turned to full volume while playing sample scales or sample waveforms/MIDI notes, then returned to it's previous setting when exiting modes that play sample sounds.
4.0 Revised for MintySynth rev. 2.0. Changed the battery monitor to internal voltage measurement, and added support for the LDR (photocell). Also works with earlier kit revisions. Change "version" to 1 below for maximum compatability.
4.1 Added Tripwire Mode, where a single loop of music is played if the ambient light (or light beam) is blocked. Can be used for art installations, etc., or just fun with lasers. There's a five-second calibration period where you have to show it the light levels with and without the light beam.
4.2 Changed the LEDs so that only the red LED (LED1) is on during Program Mode, and only the yellow LED (LED2) is on in Live Mode. This seems to make it easier to remember which mode we're in. The LED still flashes on steps 1,5,9, and 13, and step one gets a long flash.

based on the Illutron Synth library:
****************************************************************************
DZL 2014
HTTP://dzlsevilgeniuslair.blogspot.dk
HTTP://illutron.dk
https://github.com/electricmango/Arduino-Music-Project.git
****************************************************************************

I was also strongly influenced by Groovesizer by Moshang: http://groovesizer.com/


 * Copyright (C) 2015 Andrew Mowry mintysynth.com
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/
 */

#include "synth.h"
#include "song.h"
#include <EEPROM.h>
#include <avr/pgmspace.h>
#include <MIDI.h>

synth edgar; //declare a synth

byte version = 2; //change this to 1 if you're using MintySynth rev. 1.0-1.3 (without a photocell)

const byte LED1 =  2;      // the LED pins
const byte LED2 =  4; 
int thisStep = 0; //step counter
int POT[5] = {5000,5000,5000,5000,5000};//holds readings for each pot  
long stepLength = 250; //the length of each step, in miliseconds
byte userWave = 0; //the waveform
byte scalePitch = 62; //MIDI pitch, 0-127
byte userPitch = 62; //MIDI pitch once the selected scale is applied.
byte userEnv = 2; //envelope, 0-3
unsigned int userLength = 70;  //the length (duration) of each note, in milliseconds, 0-127. Not to be confused with step-- can be longer or shorter than the step.
byte userMod = 64;  //modulation, the pitch shift up or down over the duration of the note, 0-127
byte Swing = 0; //swing, the percentage of the step length that is added to even notes and subtracted from odd notes (the note numbers start with 0, which is even)
unsigned int swingLength; //length of the step once swing is taken into consideration
unsigned long triggerTime; //the time at the beginning of the step
boolean livePots[5] = {0,0,0,0,0}; //true if pot has been turned (unlocked), false if it has been locked and not yet turned
static long readTime=100; //the last time the pots were read
unsigned int batteryLevel; //the smoothed battery level, 0-1023
boolean batteryLow=0;
static long batteryTime=60000; //the last time the battery was checked. Set high so we check once at startup.
boolean mixerMode = 0; //mixerMode let us set volume levels for each voice. MixerMode can be on during Program Mode or Live Mode.
byte Current = 2; //the song that is currently being played. 0 and 1 are the two halves of the demo song
byte programMode = 0; //0-3 are Program Modes for voices 0-3. 4 means Program Mode is off (we're in Live mode).
boolean sequMode = 0; //Sequencer Mode, which is a subset of Program Mode. When we enter Sequencer Mode from Program Mode for voice i, we're in Sequencer Mode for voice i.
byte modeChange = 0; //This is a flag indicating that we've just changed modes. We use it to indicate whether to unflag justreleased if we were just using the buttons for the mode change. The value indicates the number of buttons that have simultaneously been pressed to change modes.
byte appendMode = 0; //0 if we're only playing song two (or the demo song), 2 if we're cycling through songs 2 and 3, 3 if we're cycling through 2-4; and 4 if we're cycling through 2-5
boolean LED1state = 0; //keep track of the LED states so we know when to turn them off.
boolean LED2state = 0;
byte scaleNumber = 0; //the current scale mode, 0-7 (see tables.h for scale names) 0 is chromatic
boolean pause = 0; //pausees the trigger timer, as opposed to suspend(), which pauses the audio engine. We use pause when we need to have the audio engine available for another use
boolean ascending = 1; //tells us if we're ascending or descending when playing a sample scale
byte scaleNote = 0; //the current note in a sample scale
boolean scaleChange; //tells us if we've changed the scale selection
byte prevScaleNumber; //the previous scale selection, so we can track whether it's changed
boolean envChange = 0; //tells us if we've just changed the envelope, so we know whether to show a binary LED indicator
byte prevEnv = 2; //the previous envelope selection
unsigned long envTimer; //used to turn off the envelope binary LED counter when the envelope pot hasn't been turned in the set amount of time
boolean envMode; //tells us if we've changed the envelope within the set amount of time
byte switchWave[5] = {11,1,6,7,0}; //the programmed waveform for each button.
boolean wavProgMode = 0; //tells us if we're in WavProgram Mode
boolean potLockFlag = 0; //set if we just locked pot0, so we can monitor when it becomes live. Used in WavProgMode.
int songShift = 0; //the number of semitones (positive or negative) by which to shift the entire currently playing song
int scaleShift = 0; //the number of semitones (positive or negative) by which to shift the current scale
boolean shiftMode = 0; //used to tell when we've just shifted the song or scale, for displaying the binary indicator.
unsigned long shiftTimer; //used to turn off the songShift/scaleSift binary indicator after some time.
unsigned long waveTimer; //used to tell us when to pause the music if we're programming waveforms.
byte voice0Volume = 8; //we remember the current volume setting of voice 0 so we can turn it up to play sample scakles and waveforms and then turn it back down if necessary.
unsigned int LDRread; //reading from the LDR (photocell)
boolean LDRMode = 0; //if we're in LDR mode (and in Live Mode) we read pitch from the LDR instead of Pot 1.
unsigned int LDRMax; //used to calibrate the LDR.
unsigned int LDRMin = 1023; //used to calibrate the LDR.
boolean tripwireMode = 0; //A simple tripwire alarm function, just for fun.
unsigned long LDRTimer; //used while calibrating the LDR for tripwireMode

//variables for MIDI (there are more on the synth.h tab):
byte MIDIswitchWave[5] = {1,57,73,17,1}; //the programmed MIDI instrument for each button.
byte MIDIswitchChannel[5] = {10,1,1,1,1}; //the programmed MIDI channel for each button.
byte currentInstrument = 0; //the instrument to which the voice that we're controlling is set (analagous to userWave), used to set MIDI voice when we trigger the MIDI note.
byte currentChannel = 1; //the instrument to which the voice that we're controlling is set, used to set MIDI voice when we trigger the MIDI note.
boolean instrumentProgMode = 0; //tells us if we're in instrumentProgram Mode
boolean potLockFlag1 = 0; //set if we just locked pot1, so we can monitor when it becomes live. Used in instrumentProgMode.
unsigned long instrumentTimer; //used to tell us when to pause the music if we're programming waveforms.
byte MIDIstate = 0; //0 is MIDI off, 1 is baud rate 115200, and 2 is baud rate 31250

//Adafruit Button Checker http://www.adafruit.com/blog/2009/10/20/example-code-for-multi-button-checker-with-debouncing/
#define DEBOUNCE 10  // button debouncer, how many ms to debounce, 5+ ms is usually plenty
byte buttons[] = {// here is where we define the buttons that we'll use. button "0" is the first, button "5" is the 6th, etc
  5, 7, 11, 8, 10}; // button pins
#define NUMBUTTONS sizeof(buttons)// This handy macro lets us determine how big the array up above is, by checking the size
byte pressed[NUMBUTTONS], justpressed[NUMBUTTONS], justreleased[NUMBUTTONS], longpress[NUMBUTTONS], extralongpress[NUMBUTTONS]; // we will track if a button is just pressed, just released, or 'currently pressed' 


void setup() 
{
  
  DIDR0 = 0x3F;   //disable the digital input buffers on the analog pins to save a bit of power and reduce noise.

  edgar.begin(CHB); //start the synth with output on Pin 3

  pinMode(LED1, OUTPUT);  // set the LED pins as output:
  pinMode(LED2, OUTPUT);

  for (byte i=0; i< NUMBUTTONS; i++) { //Make input & enable pull-up resistors on switch pins
    pinMode(buttons[i], INPUT);
    digitalWrite(buttons[i], HIGH);}
    
 check_switches(); //we check the switches twice at startup so we catch whether button 0 is held.
 delay(100);
 check_switches();
 
 if (pressed[0]){
   
    Current = 0; //if button 0 is held during startup we start in Live Mode, playing the demo song. Otherwise we'll be in Program Mode 0.
    Swing = 16;
    stepLength = 168;
    scaleNumber = 7;
    programMode = 4;
    modeChange = 1;} //we set modeChange whenever we are using a button for something other than setting the waveform. It tells us to turn off the justreleased flag so the waveform isn't changed.
    
 lock_pots();
 
MIDIstate = EEPROM.read(370); //read the stored MIDI state
if (MIDIstate > 2){MIDIstate = 0;} //if it's greater than 2 we've never saved it before, so set it to 0.
if (pressed[1]){toggleMIDI();} //toggle it if button 1 is held.
if (MIDIstate != 0){MIDI.begin();} //this defaults to the standard MIDI baud rate of 31250.
if (MIDIstate == 2){Serial.begin(115200);} //use MIDI state 2 for sending MIDI via serial to PC (e.g. using Hairless MIDI)


/* //uncomment this to print the four saved songs to the serial monitor on startup.
Serial.begin(9600);
printSongs();
*/


}


void loop() 
{
  
check_switches();  //we check these frequently so we don't miss a button press.

for(int i=0;i<4;i++){
  if (edgar.voiceFree(i) && MIDIOn[i]) {
    MIDI.sendNoteOff(MIDINotePlaying[i],0,channelPlaying[i]); //turn off the MIDI note if the Illutron Synth has stopped playing the note, meaning we've reached the end of the note duration.
   MIDIOn[i] = 0;}} 
 
if ((millis() - readTime) >= 50) {//we only need to read the pots every once in a while.
  get_pots();
  readTime=millis();} //reset the pot-reading timer
  
if (version == 2){
if (LDRMax > 500)
  {if (LDRMode && LED1state == 0 && LED1state == 0) {LDRread = constrain((map(analogRead(5),LDRMax-500,LDRMax,1023,0)),0,1023);}} //if we're in LDRMode we read the LDR any time we can as long as the LEDs aren't turned on.
  else if (LDRMode && LED1state == 0 && LED1state == 0) {LDRread = constrain((map(analogRead(5),0,LDRMax,1023,0)),0,1023);}}

check_pots();  //see if the pots are live

if (((millis() - triggerTime) >= 70) && thisStep == 1 && LED2state == 1 && !(sequMode && livePots[4]) && !envMode && !pause) {//turn off the LEDs after some time if they're on and we're not playing sample scales. If we're on step 1 we leave the LED on longer.
       PORTD &= ~_BV(PD4); //turn off LED2 (direct port manipulation)
       LED2state = 0;}
if (((millis() - triggerTime) >= 3) && thisStep > 1 && LED2state == 1  && !(sequMode && livePots[4]) && !envMode && !pause) {
       PORTD &= ~_BV(PD4); //turn off LED2
       LED2state = 0;}
if (((millis() - triggerTime) >= 70) && thisStep ==1 && LED1state == 1  && !(sequMode && livePots[4]) && !envMode && !pause) {
       PORTD &= ~_BV(PD2); //turn off LED1
       LED1state = 0;}     
if (((millis() - triggerTime) >= 3) && thisStep >1 && LED1state == 1 && !(sequMode && livePots[4]) && !envMode && !pause) {
       PORTD &= ~_BV(PD2); //turn off LED1
       LED1state = 0;}

//***********************************************************************
//LDR Mode
//***********************************************************************
//if we're in LDR mode (and in Live Mode) we read pitch from the LDR instead of Pot 1.

if (version == 2){
if (pressed[1] && pressed[2] && programMode == 4){ //enter LDR Mode if buttons 0 and 1 are pressed.
  modeChange = 2;
  LDRMode = 1;
  livePots[1] = 0;
  LDRMax = analogRead(5);} //take an ambient light reading to calibrate the LDR to the current light level.
  
if ((LDRMode && livePots[1] && !mixerMode && !instrumentProgMode && !wavProgMode && !pressed[0] && !pressed[1] && !pressed[2] && !pressed[3]) || programMode < 4) {LDRMode = 0;}} //turn LDRMode off if POT1 is turned or if we exit Live Mode.


//***********************************************************************
//Tripwire Mode
//***********************************************************************
//trigger a single loop of music if the ambient light source is blocked.

if (version == 2){
if ((pressed[2] && pressed[3] && programMode == 4 && !tripwireMode) || (pressed[2] && pressed[3] && programMode == 4 && tripwireMode && ((millis()-LDRTimer) > 6000))) { //enter tripwire Mode if buttons 2 and 3 are pressed and we're in Live Mode, or if we're already in Tripwire Mode and we just want to recalibrate.
  modeChange = 2;
  tripwireMode = 1;
  pause = 1;
  LDRMode = 0;
  lock_pots();
  PORTD &= ~_BV(PD2); //turn off the LEDs
  PORTD &= ~_BV(PD4);
  for (int i = 0; i < 3; i++) {//flash LED 1 to indicate beginning of calibration period
     delay(100);
    PORTD |= _BV(PD2);
    delay(25);
    PORTD &= ~_BV(PD2);}
  thisStep = 0; //begin at the first note in the song.
  LDRTimer = millis();
  
 while (((millis()-LDRTimer) < 5000) && tripwireMode) { // calibrate the LDR during the first five seconds of tripwire Mode. Taken from: https://www.arduino.cc/en/Tutorial/Calibration
   LDRread = analogRead(5);
  if (LDRread > LDRMax) { // record the maximum sensor value
     LDRMax = LDRread;}
   if (LDRread < LDRMin) {// record the minimum sensor value
     LDRMin = LDRread;}}
     
  for (int i = 0; i < 3; i++) {//flash LED 2 to indicate end of calibration
    delay(100);
    PORTD |= _BV(PD4);
    delay(25);
    PORTD &= ~_BV(PD4);}}

if (tripwireMode) {LDRread = analogRead(5);}
 
if (tripwireMode && pause && (LDRread < (((LDRMax - LDRMin)>>1) + LDRMin))) {
   pause = 0;}
   
if (tripwireMode && thisStep == 15) {
  pause = 1;
  thisStep = 0;}
  
for(int i=0;i<5;i++){
  if(livePots[i] && tripwireMode) {
  tripwireMode = 0;
   pause = 0;}} //exit tripwire Mode if any wheel is turned.

if (LDRMode || programMode < 4) {
  tripwireMode = 0;
  pause = 0;}} //exit tripwire Mode if any wheel if we enter LDR Mode or Program Mode.
  

//***********************************************************************
//Waveform Button Programming
//***********************************************************************
//lets us program the waveform for buttons 0-3.

if (potLockFlag && livePots[0] && !instrumentProgMode) { //if we've locked POT 0 because one of the buttons is held, and POT 0 becomes live again, we've turned it and we are in Wave Program Mode.
  wavProgMode = 1;
  voice0Volume = volume[0]; //remember the current volume of voice 0
  modeChange = 1;
  potLockFlag=0;
  waveTimer=millis();}
  
if (wavProgMode && ((millis() - waveTimer) >=1500)) { //if we've been in wavProgram mode for a bit,
    pause = 1; //pause the music; this also indicates that we should start playing sample notes so we can hear the waveforms.
    volume[0] = 8;} //temporarily turn up voice 0 if necessary.
   
   
 for(int i=0;i<4;i++){
     if (pause && longpress[i] && wavProgMode && ((millis() - triggerTime) >=500))  {
       edgar.setupVoice(0, switchWave[i], 50, 1, 70, 64); //play a sound so we can hear how the waves sound as we're selecting them.
       edgar.mTrigger(0,50);
       triggerTime=millis();}}
  
if (potLockFlag && !modeChange){potLockFlag=0;} //if there's no modeChange flag, the button has been released, so unflag the pot.
  
for(int i=0;i<4;i++){
  if (longpress[i] && programMode == 4 && !wavProgMode && !potLockFlag && !instrumentProgMode && modeChange == 0) { //if a button is held, lock POT0 and wait to see if it's turned, telling us to enter Wave Program Mode.
  livePots[0]=0;
  potLockFlag=1;} //the flag tells us we've locked the pot and we're waiting...

  if(wavProgMode == 1 && pressed[i]){
    switchWave[i]=constrain((map((POT[0]),0,1023,0,15)),0,14); //use the pot reading to select the wave.
    showBinary(switchWave[i]);}} //use the binary LED indicator to help see which waveform we've chosen.
       
   check_switches();    
       
if (wavProgMode && modeChange == 0){ //if there's no modeChange flag, it's because a button has been released, and it's time to exit wavProgMode.
   wavProgMode = 0;
   volume[0] = voice0Volume; //turn voice 0 back down if necessary.
   pause = 0; //restart the music
   PORTD &= ~_BV(PD2);//turn off the LEDs
   PORTD &= ~_BV(PD4);
   livePots[0] = 0;} //lock the pot that we used for waveform programming
   
 //***********************************************************************
//MIDI Instrument and Channel Button Programming
//***********************************************************************
//lets us program the instrument and channel for buttons 0-3.

if (potLockFlag1 && livePots[1] && !wavProgMode) { //if we've locked POT 1 because one of the buttons is held, and POT 1 becomes live again, we've turned it and we are in Instrument Program Mode.
  instrumentProgMode = 1;
  voice0Volume = volume[0]; //remember the current volume of voice 0
  modeChange = 1;
  potLockFlag1=0;
  instrumentTimer=millis();
  for(int i=0;i<4;i++){MIDI.sendControlChange(123,0,i);}} //turn all the MIDI notes off
  
if (instrumentProgMode){
  pause = 1; //pause the music
  volume[0] = 8;} //temporarily turn up voice 0 if necessary.
   
 for(int i=0;i<4;i++){
     if (pause && longpress[i] && instrumentProgMode && ((millis() - triggerTime) >=500))  {
       channelPlaying[0] = MIDIswitchChannel[i]; //set the MIDI channel for voice 0
       instrumentPlaying[0] = MIDIswitchWave[i];
       edgar.setupVoice(0, 0, 50, 1, 70, 64); //play a sound so we can hear how the waves sound as we're selecting them.
       edgar.mTrigger(0,50);
       triggerTime=millis();}}
 
if (potLockFlag1 && !modeChange){potLockFlag1=0;} //if there's no modeChange flag, the button has been released, so unflag the pot.
  
for(int i=0;i<4;i++){
  if (longpress[i] && programMode == 4 && !instrumentProgMode && !wavProgMode && !potLockFlag1 && modeChange == 0) { //if a button is held, lock POT1 and wait to see if it's turned, telling us to enter Instrument Program Mode.
  livePots[1]=0;
  potLockFlag1=1;} //the flag tells us we've locked the pot and we're waiting...

  if(instrumentProgMode == 1 && pressed[i]){
    MIDIswitchWave[i]=constrain((map((POT[1]),10,1023,0,128)),0,127); //use the pot reading to select the wave.
    showBinary(MIDIswitchWave[i]); //use the binary LED indicator to help see which waveform we've chosen.
    if(POT[1] < 10) {MIDIswitchChannel[i] = 10;}
    else {MIDIswitchChannel[i] = 1;} 
    }} 
       
   check_switches();    
       
if (instrumentProgMode && modeChange == 0){ //if there's no modeChange flag, it's because a button has been released, and it's time to exit instrumentProgMode.
   livePots[1] = 0;  //lock the pot that we used for instrument programming
   instrumentProgMode = 0;
   MIDI.sendControlChange(123,0,channelPlaying[0]);
   pause = 0; //restart the music
   potLockFlag=0;
   volume[0] = voice0Volume; //turn voice 0 back down if necessary.
   channelPlaying[0] = currentChannel; //set the MIDI channel for voice 3
   instrumentPlaying[0] = currentInstrument;
   PORTD &= ~_BV(PD2);//turn off the LEDs
   PORTD &= ~_BV(PD4);
}


//***********************************************************************
//Waveform and MIDI Instrument Selection using the buttons
//***********************************************************************
  
for(int i=0;i<5;i++){
    if (justreleased[i]){ // if a button was just released and we're in not in Mixer Mode or Sequencer Mode,
   userWave = switchWave[i]; //set the waveform
   if (MIDIswitchChannel[i] != currentChannel) {MIDI.sendControlChange(123,0,currentChannel);} //if we're switching channels, we turn off all notes on the previous channel, so none accidentally get stuck on.
   currentInstrument = MIDIswitchWave[i];
   currentChannel = MIDIswitchChannel[i];}}
  
   
//***********************************************************************
//Envelope Indicator
//***********************************************************************
//light binary LED display if the envelope is currently being changed.

 if (prevEnv != userEnv){
       envChange = 1; //set a flag if the envelope has been changed.
       envMode = 1;
       envTimer = millis();}
      else {envChange = 0;}
 if (envChange) {prevEnv = userEnv;}
   
 if (((millis() - envTimer) >= 1500) && envMode) { //if we haven't changed the envelope for some time...
        envMode = 0; //exit envMode...
        PORTD &= ~_BV(PD2); // and turn off the LEDs
        PORTD &= ~_BV(PD4);}
   
  if (envMode && !sequMode && !wavProgMode && !instrumentProgMode) {
      showBinary(userEnv);} //use the binary LED indicator to show us which envelope we've selected.
  
//***********************************************************************
//Mixer Mode
//***********************************************************************
//when button 4 (shift) is held, pots 0-3 set the volume levels for voices 0-3.

if (longpress[4] && !mixerMode){
  mixerMode=1;
   if (modeChange == 0) {modeChange = 1;} //set a modechange flag unless there's already one set
  lock_pots();}
    
for (int i = 0; i < 5; i++) {
     if (mixerMode && livePots[i]){
     volume[i]=constrain((map((POT[i]),0,1023,13,7)),8,13);}}
   
if (mixerMode && livePots[4]){
  userMod = constrain((map((POT[4]),0,1023,42,85)),42,84);} //we also use Mixer Mode to set modulation with POT4, because it seemed like a good place for it.
  
  if (userMod < 44) {userMod=64;}
    
if (mixerMode && modeChange == 0){ //if there's no modeChange flag, it's because a button has been released, and it's time to exit mixerMode.
mixerMode = 0;
lock_pots();} //we always lock the pots when we switch modes, so they don't immediately change all the settings in the mode we're entering. Turning them a little makes them live again.


//***********************************************************************
//Sequencer Mode
//***********************************************************************
//this is a subset of Program Mode. When in Program Mode and button 0-3 held is held down, pots 0-3 are used to select the 16 indivually sequenced notes. We also use this mode to select the scale with pot 4.

for (int i = 0; i < 4; i++) { 
if (longpress[i] && !sequMode && programMode < 4){ //enter Sequencer Mode when we hold down button 0-3
  sequMode=1;
  voice0Volume = volume[0]; //remember the current volume of voice 0
   if (modeChange == 0) {modeChange = 1;} //set a modechange flag unless there's already one set
  lock_pots();}
  
 for (int j = 0; j < 4; j++) {
    
 if (sequMode && longpress[i] && livePots[j]){
         
      if (scaleNumber == 0) {song[2][programMode][((4 * i) + j)]=constrain((map((POT[j]),0,1023,18,109)),18,108);}
      if (scaleNumber > 0) {song[2][programMode][((4 * i) + j)]=(pgm_read_byte(&(scale[scaleNumber - 1][constrain((map((POT[j]),0,1023,18,109)),18,108)]))) + scaleShift;}}
   
 if  ((song[2][programMode][((4 * i) + j)]) < 20){(song[2][programMode][((4 * i) + j)]) = 0;}
  
 if  ((song[2][programMode][((4 * i) + j)]) > 105){(song[2][programMode][((4 * i) + j)]) = voicePrefs[2][programMode][1];}}}
 
    
 //scale selection and sample scale player on pot 4 when we're in sequMode:
 
 if (sequMode && livePots[4]){
 
scaleNumber = constrain((map((POT[4]),0,1023,0,9)),0,8); //set the scale with pot4 if we're in sequMode.
 
  pause = 1; //pause the step timer while we're playing sample scale notes
  volume[0] = 8; //temporarily turn up voice 0 if necessary.
  
  if (scaleChange) {
    showBinary(scaleNumber);}
    
   if (prevScaleNumber != scaleNumber) {scaleChange = 1;} //set a flag if the scale has changed.
      else {scaleChange = 0;}
   if (scaleChange) {prevScaleNumber = scaleNumber;}
        
   if (scaleChange) { //reset the scale to the beginning if the scale has changed.
       scaleNote = 0;
       ascending = 1;} 

   if ((((millis() - triggerTime) >=100) && (scaleNote > 0 || !ascending)) || (scaleNote == 0 && ((millis() - triggerTime) >=500) && ascending))  { //trigger the next sample scale note if enough time has passed.
  
       edgar.setupVoice(0, 10, 60, 1, 60, 64);
       instrumentPlaying[0] = 0; 
       channelPlaying[0] = 1; //set MIDI channel to 1 and instrument to piano for the sample scale.
       
       edgar.mTrigger(0,sampleScale[scaleNumber][scaleNote]);
                 
       if (sampleScale[scaleNumber][scaleNote] == 72) {ascending = 0;} //reverse the scale when we get to the top.
       if (ascending) {scaleNote++;} //increment the scale note if we're going up.
       if (!ascending && scaleNote == 0){ascending = 1;} //reverse the scale again when we get to the bottom.
       if (!ascending && scaleNote > 0) {scaleNote--;} //decrement the scale note if we're going down.
 
      triggerTime=millis();}}

 if (sequMode && modeChange == 0){ //if there's no modeChange flag, it's because a button has been released, and it's time to exit sequMode. We also make sure we're set up to start the next sample scale at the beginning.
 sequMode = 0;
 pause = 0;
 volume[0] = voice0Volume; //turn voice 0 back down if necessary.
 scaleNote = 0; //reset the scale for next time.
 ascending = 1;
 scaleChange = 1;
 PORTD &= ~_BV(PD2); //turn off the LEDs if they're on.
 PORTD &= ~_BV(PD4);
 lock_pots();}

//***********************************************************************
//Program Mode
//***********************************************************************
//if Program mode 0-4 is on but sequMode isn't, the pots and buttons are used to set up voices 0-4.

for (int i = 0; i < 4; i++) { //enter Program Mode when we hold down button 4 and press button 0-3
if (pressed[4] && justpressed[i]){
modeChange = 2;
programMode = i;
PORTD &= ~_BV(PD2); //turn off LED 1 in case it was still on in Live Mode.
Current = 2; //set the currently playing song to 2 (this is always where we store the song currently being sequenced.
lock_pots();}}

if (programMode < 4 && !sequMode){  //when in Program Mode we use the buttons to set the waveform and write it to the voicePrefs array.
    for (int i = 0; i < 5; i++) {
    if (justreleased[i]){
    voicePrefs[2][programMode][0] = switchWave[i];
    voicePrefs[2][programMode][6] = MIDIswitchWave[i];
    voicePrefs[2][programMode][5] = MIDIswitchChannel[i];}}}
    
 if (programMode < 4 && !sequMode){ //if we're in Program mode but not Sequence Mode, use the pots to select the voice parameters and write them to the userPrefa array.
   
      if (livePots[1]){ voicePrefs[2][programMode][1] = userPitch;
          song[2][programMode][programMode * 4] = userPitch;}
     if (livePots[3]){voicePrefs[2][programMode][2] = userEnv;}
     if (livePots[2]){voicePrefs[2][programMode][3] = userLength;}}
   
if (programMode < 4 && !sequMode && mixerMode && livePots[4]){voicePrefs[2][programMode][4] = userMod;} //set modulation if we're in Mixer Mode

if (pressed[0] && justpressed[4] && programMode < 4){ //exit Program Mode (enter Live Mode) if we hold down 0 and press 4.
  modeChange = 2;
  programMode = 4;
  PORTD &= ~_BV(PD4); //turn off LED 2 in case it was still on in Program Mode.
  userWave = voicePrefs[2][3][0]; //preset the prefs for voice 3 using the array, so it will stay the same until the variables change after entering Live Mode.
  currentInstrument = voicePrefs[2][3][6];
  currentChannel = voicePrefs[2][3][5];
  userPitch = voicePrefs[2][3][1];
  userEnv = voicePrefs[2][3][2];
  prevEnv = userEnv;
  userLength = voicePrefs[2][3][3];
  userMod = voicePrefs[2][3][4];
  lock_pots();}

//***********************************************************************
//Save and Load
//***********************************************************************
 
 //save
for (int i = 0; i < 4; i++) { 
  if (!(modeChange == 2) && programMode == 4  && !wavProgMode && !instrumentProgMode &&  pressed[i] && extralongpress[4]) {
    modeChange = 2;
    save(i);}}
    
//load one song when a button is held for three seconds.
for (int i = 1; i < 4; i++) { //buttons 1-3
  if (modeChange == 0 && programMode == 4 && !wavProgMode && !instrumentProgMode && !pressed[4] && extralongpress[i] && !pressed[0]) {
    modeChange = 1; //only one button pressed to trigger load(), so we set one modechange flag.
   load(i);}}
 
 if (modeChange == 0 && programMode == 4  && !wavProgMode && !instrumentProgMode && !pressed[4] && extralongpress[0] && !pressed[1] && !pressed[2] && !pressed[3]) { //button 0
    modeChange = 1; //only one button pressed to trigger load(), so we set one modechange flag.
   load(0);}
   
//load and append up to four songs when 0 is pressed and button 1-3 is held
if (modeChange == 0 && programMode == 4 && !wavProgMode && !instrumentProgMode && pressed[0] && extralongpress[1] && !pressed[2] && !pressed[3]){
   append(0);
   append(1);
   modeChange = 2; //two buttons are held, so we set modeChange flag to 2.
   appendMode = 2;}
   
 if (modeChange == 0 && programMode == 4 && !wavProgMode && !instrumentProgMode && pressed[0] && extralongpress[2] && !pressed[3]){
   append(0);
   append(1);
   append(2);
   modeChange = 2;
   appendMode = 3;}
   
 if (modeChange == 0 && programMode == 4 && !wavProgMode && !instrumentProgMode && pressed[0] && extralongpress[3]){
   append(0);
   append(1);
   append(2);
   append(3);
   modeChange = 2;
   appendMode = 4;}
   
//***********************************************************************
//Song Shift and Scale Shift
//***********************************************************************

if (pressed[0] && justpressed[1] && programMode < 4){
  modeChange = 2;
  shiftMode = 1;
  shiftTimer = millis();
  if (songShift < 15) {songShift++;}
  showBinary(abs(songShift));
  justpressed[1] = 0;
  if (songShift < 15) {
    for (int i = 0; i < 4; i++) { 
       for (int j = 0; j < 16; j++) {
            if (song[2][i][j] != 0 && song[2][i][j] < 128){song[2][i][j] = song[2][i][j] + 1;}}}}}
  
if (pressed[1] && justpressed[0] && programMode < 4){
  modeChange = 2;
  shiftMode = 1;
  shiftTimer = millis();
  if (songShift > -15) {songShift--;}
  showBinary(abs(songShift));
  justpressed[0] = 0;
  if (songShift > -15) {
      for (int i = 0; i < 4; i++) { 
        for (int j = 0; j < 16; j++) {
             if (song[2][i][j] > 1){song[2][i][j] = song[2][i][j] - 1;}}}}}
              
  
if (pressed[2] && justpressed[3] && programMode < 4){
  modeChange = 2;
  shiftMode = 1;
  shiftTimer = millis();
  if (scaleShift < 15) {scaleShift++;}
  showBinary(abs(scaleShift));
  justpressed[3] = 0;
}
  
if (pressed[3] && justpressed[2] && programMode < 4){
  modeChange = 2;
  shiftMode = 1;
  shiftTimer = millis();
  if (scaleShift > -15) {scaleShift--;}
  justpressed[2] = 0;
  showBinary(abs(scaleShift));
}
   
 if (((millis() - shiftTimer) >= 1500) && shiftMode) {  //exit shift mode
        shiftMode = 0;
        PORTD &= ~_BV(PD2); //turn off the LEDs
        PORTD &= ~_BV(PD4);}
   

//***********************************************************************
//Battery
//***********************************************************************

if (((millis() - batteryTime) >= 60000) && batteryLow==0 && !LED1state && !LED2state) { //we check the battery at startup and then once/minute unless the battery has already been flagged as low.
   check_battery();
   batteryTime=millis();}
       
//***********************************************************************
//Voice Setup and Note Trigger
//***********************************************************************

 if ((millis() - triggerTime) >= swingLength && !pause) {//check to see if the previous step is done and the music is not paused. If so, reset the step timer, set up the voices, and trigger the next step.
 
       triggerTime=millis();
       
      //***********************************************************************
      //Voice Setup
      //***********************************************************************
       //set up all the voices to get ready for the next note.
       
      check_pots();  //see if the pots are live
 
      if (!mixerMode && !sequMode && !wavProgMode && !instrumentProgMode){
     
       //map the pots to variables as long as there aren't any buttons pressed.
      if (livePots[0] && !pressed[0] && !pressed[1] && !pressed[2] && !pressed[3] && !pressed[4]) {stepLength = constrain((map((POT[0]),0,1023,600,89)),90,600);}
      if (livePots[1] && !pressed[0] && !pressed[1] && !pressed[2] && !pressed[3] && !pressed[4] && !LDRMode) {scalePitch = constrain((map((POT[1]),0,1023,20,106)),20,105);}
      if (!pressed[0] && !pressed[1] && !pressed[2] && !pressed[3] && !pressed[4] && LDRMode) {scalePitch = constrain((map((LDRread),0,1023,20,106)),20,105);} //if we're in LDRMode we read pitch from the LDR instead of POT1.
      if (livePots[2] && !pressed[0] && !pressed[1] && !pressed[2] && !pressed[3] && !pressed[4]) {userLength = constrain((map((POT[2]),0,1023,0,91)),0,90);}
      if (livePots[3] && !pressed[0] && !pressed[1] && !pressed[2] && !pressed[3] && !pressed[4]) {userEnv = constrain((map((POT[3]),0,1023,0,5)),0,4);}
      if (livePots[4] && !pressed[0] && !pressed[1] && !pressed[2] && !pressed[3] && !pressed[4]) {Swing = constrain((map((POT[4]),0,1023,0,80)),0,80);}}
 
      if (scaleNumber > 0) {userPitch = (pgm_read_byte(&(scale[scaleNumber - 1][scalePitch]))) + scaleShift;} //here we map to the scale lookup tables if a scale other than chromatic is selected.
      if (scaleNumber == 0) {userPitch = scalePitch;}
       
      if ((thisStep % 2) == 0) { swingLength=stepLength+((stepLength*Swing)>>7); } //lengthen even steps by the swing percentage and shorten odd steps by the swing percentage.
        else swingLength=stepLength-((stepLength*Swing)>>7);
        
      if (swingLength > (stepLength * 2)) {swingLength = stepLength;} //just to make sure that we never lengthen the even steps by more than 100%
      
      //Set up the voices:
      
      for (int i = 0; i < 3; i++) { //set everything except pitch from the prefs array for each voices 0-2.
        
        edgar.setWave(i,voicePrefs[Current][i][0]);
        edgar.setEnvelope(i,voicePrefs[Current][i][2]);
        edgar.setLength(i,voicePrefs[Current][i][3]);
        edgar.setMod(i,voicePrefs[Current][i][4]);
        channelPlaying[i] = voicePrefs[Current][i][5]; //set the MIDI channel for voices 0-2
        instrumentPlaying[i] = voicePrefs[Current][i][6];} //set the MIDI instrument for voices 0-2
        
      if (programMode < 4){  //if we're in Program Mode 0-3 we want to read the voice 3 prefs from the array, just like the other voices.
         
         edgar.setWave(3,voicePrefs[Current][3][0]);
         edgar.setEnvelope(3,voicePrefs[Current][3][2]);
         edgar.setLength(3,voicePrefs[Current][3][3]);
         edgar.setMod(3,voicePrefs[Current][3][4]);
         channelPlaying[3] = voicePrefs[Current][3][5]; //set the MIDI channel for voices 0-2
         instrumentPlaying[3] = voicePrefs[Current][3][6];} //set the MIDI instrument for voices 0-2
          
            else {    //if we're in Live Mode we want to read the voice 3 prefs directly from the pots, not from the stored arrays.
              edgar.setWave(3,userWave);
              edgar.setEnvelope(3,userEnv);
              edgar.setLength(3,userLength);
              edgar.setMod(3,userMod);
              channelPlaying[3] = currentChannel; //set the MIDI channel for voice 3
              instrumentPlaying[3] = currentInstrument;} //set the MIDI instrument for voice 3
 
         //***********************************************************************
        //Note Trigger
        //***********************************************************************
 
       if (song[Current][0][thisStep] != 0 && volume[0] != 13 && (voicePrefs[Current][0][3]) > 2) {edgar.mTrigger(0,song[Current][0][thisStep]);}  //trigger voices 0-2, getting the pitch from the song array. If the value in the array is 0 or if the duration is very short, no note is played.
       if (song[Current][1][thisStep] != 0 && volume[1] != 13 && (voicePrefs[Current][1][3]) > 2) {edgar.mTrigger(1,song[Current][1][thisStep]);}
       if (song[Current][2][thisStep] != 0 && volume[2] != 13 && (voicePrefs[Current][2][3]) > 2) {edgar.mTrigger(2,song[Current][2][thisStep]);}
       if (programMode < 4 && song[Current][3][thisStep] != 0 && volume[3] != 13 && (voicePrefs[Current][3][3]) > 3){edgar.mTrigger(3,song[Current][3][thisStep]);}  //if we're in Program Mode 0-3 we want to read the voice 3 pitch from the array, just like the other voices.
         else if (song[Current][3][thisStep] != 0  && volume[3] != 13 && userLength > 3) {edgar.mTrigger(3,userPitch);}    //if we're in Live Mode we'll read voice 3 pitch from the Pot or LDR.
     
     
       //***********************************************************************
        //Housekeeping after each step is triggered
        //***********************************************************************
    
      if (!envMode && !shiftMode && !pause && !wavProgMode && !instrumentProgMode) {flash_leds();}
      
      thisStep++; //advance the step counter
    
      if (thisStep > 15) {thisStep=0;}//reset the counter after 16 steps
      
      if ((thisStep == 0) && (Current == 0)) {Current = 1;}//if we're playing the demo song, which is 32 steps long, toggle between the two 16-step halves.
      
       else if ((thisStep == 0) && (Current == 1)) {Current = 0;}
  
      if (thisStep == 0 && appendMode > 0){Current = Current + 1;} //if we've appended multiple songs, increment the currently playing song.
      
      if (thisStep == 0 && appendMode == 2 && Current == 4){Current = 2;} //if we've appended two songs, return to the first after the second has played.
      if (thisStep == 0 && appendMode == 3 && Current == 5){Current = 2;} //if we've appended three songs, return to the first after the third has played.
      if (thisStep == 0 && appendMode == 4 && Current == 6){Current = 2;}} //if we've appended four songs, return to the first after the fourth has played.
      
}


      
  
  
   
   





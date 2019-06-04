# EEG_final_code

### Project Description:

  My initial goal for my final project in this class was to see if I could use coding to help people suffering from medical conditions, specifically mental health conditions, in a way that is engaging and unique from the typical clinical setting. As I was doing research, I came across a kind of treatment for PTSD victims and victims of other various mental disorders and phobias called "exposure therapy," in which the patient is exposed to a triggering or stress-inducing experience, but in a secure and controlled clinical setting. I thought back to the virtual reality set that Sacred Heart purchased earlier this year, and became very intrigued by the idea of somehow incorporating the extremely realistic simulations of VR in the process of exposure therapy. My final idea was to hack an EEG headset capable of monitoring brain activity and connect it to an Arduino LCD screen where numbers representing brainwaves for attention/focus and meditation/relaxation would be shown (higher numbers meaning more focused and/or relaxed), and run test trials on people in which I have them wear the headset while experiencing a stressful VR simulation to see how their brainwaves fluctuate, and then have them try different concentration games after being exposed to stress. After gathering these base values, I would continue to test the same people and see if they eventually improve their ability to complete the concentration games, and then start to make the games harder in order to ultimately strengthen their ability to regain focus and composure after feeling stressed with the theory that perhaps this practice could help PTSD victims come back down to earth more quickly when they experience panic attacks or flashbacks in real life. My minimum viable product ended up being the Arduino LCD display hooked up to the hacked EEG headset, complete with code to display brainwave values on the screen. However, I hope to continue this project next year as an independent study and hopefully work with actual PTSD victims and medical professionals.

### Walkthrough of Code:

1. Defining pin numbers: I used the SPI (Serial Peripheral Interface), a system used for short-distance communication between devices, to connect the code on my laptop to the Arduino board and the EEG headset.
  * #define sclk 2 -> defines pin # 2 on the Arduino as the serial clock, an SPI signal that ensures that the slave devices read data at the same rate that the master device outputs data
  * #define mosi 3 -> clarifies the master device as the device that outputs data and the slave device as the one that is receiving the data, and designates this data input to pin # 3 on the Arduino
  * #define cs   4 -> used to designate a device as a slave device, and communicates to the Arduino board through pin # 4 that it must interact with the other devices to output/receive (in this case receive) data
  * #define dc   5 -> uses pin # 5 on the Arduino to help the slave device recognize if a certain input is data or a command

2. Libraries: I used three libraries in my code: one that contained the functions for the specific LCD screen that I used, one that contained the functions needed to interpret and discern the brainwaves monitored by the EEG, and the SPI in order to facilitate communication between the Arduino, EEG, and computer.
  * #include <LiquidCrystal.h> -> calls library for LCD screen
  * #include <SPI.h> -> calls SPI library
  * #include <Brain.h> -> calls library for EEG headset

3. Using LCD Library: The LiquidCrystal library was the library used for displaying the data on the LCD itself, and because of that it was necessary for all of the data from all of the pins to be accounted for when the LCD was displaying something in order for it to be accurate.
  * LiquidCrystal lcd(12, 11, cs, dc, mosi, sclk); -> uses a funcionality of the LiquidCrystal library to create a variable (lcd) that would be used in the rest of the code, which in and of itself incorporates the data from all of the necessary pins

4. Using EEG Library: The Brain library contained three other libraries, one of which was the BrainSerial library that is used to monitor the values of all of the brainwaves of the person wearing the headset.
  * Brain brain(Serial); -> calls on Serial library to monitor brainwaves

5. Code Setup: One unique feature of the Arduino IDE language is that it contains one "setup" section which is read at the beginning of the sketch and only runs once, and one "loop" section which will run continuously or until a certain condition is met. In the setup section, I included a command to tell the computer and Arduino what kind of LCD screen was being used and a command to clear the LCD screen so that no previous data would interfere with the next time the code was run.
  * void setup(void) { -> indicates beginning of setup section, "void" indicates that the setup function takes no arguments
  * lcd.begin(16, 2); -> clarifies that the LCD screen being used is one with 2 rows and 16 columns
  * lcd.clear(); -> clears the LCD screen of any previous data
  * } -> indicates end of setup section

6. Main Code: This is the "loop" section of the code which runs more than once that includes the commands to retrieve the data regarding brainwaves from the EEG and display them on the LCD screen.
  * void loop() { -> indicates beginning of loop section
  *   lcd.setCursor(0,0); -> moves the cursor on the LCD screen to the first row and first column so that the data begins displaying at the top left of the screen
  *   if (brain.update()) { -> if the signal between the Arduino and EEG headset...
  *     if (brain.readSignalQuality() > 100) { -> has a value greater than 100...
  *     lcd.print("signal quality low"); -> print "signal quality low," informing the user that any data displayed would not be accurate due to a poor signal quality
  * } -> end of second "if" command
  * else{ -> if the signal quality between the Arduino and the EEG headset is not greater than 100...
  *   lcd.setCursor(0,0); -> sets the LCD cursor to the first row and the first column
  *   lcd.print("Attention:"); -> print "Attention" to show that the following value refers to the focus and attentiveness of the person wearing the headset
  *   lcd.setCursor(11, 0); -> set the LCD cursor to the first row and eleventh column
  *   lcd.print(brain.readAttention()); -> print the value recorded from the "readAttention" function, with higher numbers meaning greater focus and lower numbers meaning lesser focus
  *   lcd.setCursor(0,1); -> set the LCD cursor to the second row and first column
  *   lcd.print("Meditation:"); -> print "Meditation" to show that the following value refers to the relaxation and calmness of the person wearing the headset
  *   lcd.setCursor(11, 1); -> set the LCD cursor to the second row and eleventh column
  *   lcd.print(brain.readMeditation()); -> print the value recorded from the "readMeditation" function, with higher numbers meaning greater level of calmness and lower numbers meaning lesser level of calmness
  * }} -> end of "else" and of first "if" command
  * } -> end of all of the code

### Error Analysis:

  After researching and using the library created for the specific LCD display I was using my code was no longer returning seemingly unfixable errors, however the RX pin on the Arduino is still sometimes an obstacle to displaying the data on the LCD correctly. Often when uploading the code to the board the Arduino IDE would say that there was a problem when uploading. One of the sources that I used in my research said that sometimes having a wire plugged into the RX pin can interfere with the uploading process and display the same error that I was getting. Because of this, I decided to unplug the wire from the RX pin and try again, which turned out to be successful in uploading the code to the board but in turn caused the LCD to display nonsensical symbols since it was not receiving the data it needed from the connection between the EEG and the RX pin. Uploading the code and receiving coherent results sometimes works after uploading many times while repeatedly plugging and unplugging the wire from the RX pin, but I would like to permanently solve this problem so that the upload process will be more reliable.

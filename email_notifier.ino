//Code by Oscar Rodgers
//Program goal: using libraries and classes create an automated email notifier (tell you when you have a new email)

//libraries
#include <LiquidCrystal_I2C.h> //LCD display library  

#include <SD.h> //library for writing to microSD card

#include <emailNotifier.h> //my custom library

#include <Ethernet.h> //library for ethernet shield, important for the UDP process

//Ethernet Setup
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip();

unsigned int localPort = 5002;      // local port to listen on

//UDP Setup
// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];  // buffer to hold incoming packet, this is a predefined constant.

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

//SD Card Setup
const int chipSelect = 4;

//Time setup, used in the recording of data
unsigned long longTime;

//Initialise the LCD display
LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

//create instance of my emailNotifier class
emailNotifier notifier(13);


//String to save the UDP data to and to check against
String dataString;
String check = "start"; //saved as "start" as the UDP package cannot match this and thus it will be only be changed after the first check if/else


void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Starting");
  Serial.println("LCD Started");

  Serial.println("Custom Library Established");

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.println("Serial Established");

  // Check for Ethernet hardware present
  Ethernet.begin(mac, ip);
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }
  Serial.println("Ethernet Established");

  // start UDP to read over the pre-defined port
  Udp.begin(localPort);
  Serial.println("UDP Established");

  //SD card setup (mostly for debugging purposes)
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }else{
  Serial.println("SD Card Initialized.");
  }
  Serial.println("Setup Complete");
}

void loop() {
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    // read the packet into packetBufffer
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);

    String dataString(packetBuffer); //save the packet message as a string

    Serial.println(dataString); //print the string to the serial monitor (just a number)

    if (dataString == check) {
      delay(5000);
    } else {
      Serial.println("didn't get checked");
      lcd.setCursor(0, 0);
      lcd.print("Unread Emails:");

      if (dataString == "0") {
        notifier.notiferOff();
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("No New Emails (:");
        delay(5000);
      } else {
        notifier.notifyFlash();
        notifier.notifierOn();
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Unread Emails:");
        lcd.setCursor(0, 1);
        lcd.print(dataString);
        delay(10000);
        }

      // if the file is available, write to it:
      File dataFile = SD.open("datalog.txt", FILE_WRITE);
      if (dataFile) {
        longTime = millis();
        dataFile.print("Email count changed to: ");
        dataFile.println(dataString);
        dataFile.print("This many milliseconds after startup: ");
        dataFile.println(longTime);
        dataFile.close();
        //print to the serial port too:
        Serial.println("Made it to SD");
      }
      

      //Set the check string to allow us to check if we need to repeat the process
      check = dataString;
    }
  }


}

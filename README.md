# Arduino-Email-Notifier
For a school project I designed and programmed an arduino to notifiy me when I had an unread email, and if I had more than one how many I had. 
Link to video of project working: https://www.youtube.com/watch?v=wZoGewQ54oQ

In order to work, a computer must be actively running the python script and the arduino must be connected via ethernet to a netwrok. 

Essentially what happens is the python script uses IMAP to connect to my email inbox, and fetch how many unread emails are present.

This number is then sent to the arduino over UDP (user datagram protocol). The arduino then outputs the number of unread messages to the lcd screen.
Additionally the arduino logs the change in number of emails onto a text file stored on an SD card in the arduino.

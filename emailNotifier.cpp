#include "emailNotifier.h"

#include "emailNotifier.h"

emailNotifier::emailNotifier(int ledPin){
	pinMode(ledPin, OUTPUT);
	//the arguments that I pass are then saved into private variables
	_ledPin = ledPin;
}

void emailNotifier::notifierOn(){
	digitalWrite(_ledPin, HIGH);
}

void emailNotifier::notiferOff(){
	digitalWrite(_ledPin, LOW);
}

void emailNotifier::notifyFlash(){
	for(int x = 0; x<=10; x++){
		digitalWrite(_ledPin, HIGH);
		delay(100);
		digitalWrite(_ledPin, LOW);
		delay(100);
	}
}



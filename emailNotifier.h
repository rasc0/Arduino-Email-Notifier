#ifndef emailNotifier_h
#define emailNotifier_h

#include "Arduino.h"

class emailNotifier{
	public:
		emailNotifier(int ledPin);
		void notifierOn();
		void notiferOff();
		void notifyFlash();
	private:
		int _ledPin; //the underscore denotes that it is a private variable
};

#endif
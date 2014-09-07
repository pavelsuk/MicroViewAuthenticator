// Simple MicroView application showing authentication code based on TOTP
// Published on: https://github.com/pavelsuk/MicroViewAuthenticator
//				 https://codebender.cc/sketch:47785
//
// The project was inspired by 
// 		https://github.com/AustinSaintAubin/Arduino_MicroView_OAuth_TOTP
// using lib and example from
//		DS1302:	http://www.henningkarlsen.com/electronics/library.php?id=5 
// 		TOTP: 	https://github.com/lucadentella/ArduinoLib_TOTP
// 		sha1	https://github.com/bakercp/Cryptosuite fork for sha1, 
// 				the original on https://github.com/Cathedrow/Cryptosuite is not compilable and not mantiained anymore
// 				I had to add these files to my codebender project by hand
//  
// I also used fragments of code (mostly for handling DS1302) from my other MicroView project
// 		https://github.com/pavelsuk/MicroViewClock
// HW schema is also on https://github.com/pavelsuk/MicroViewClock
//

#include "sha1.h"
#include "TOTP.h"
#include <DS1302.h>
#include <Time.h>
#include <MicroView.h>


// The shared secret is MicroView 
// use http://www.asciitohex.com/ 
// 		for conversion to hex
// use http://online-calculators.appspot.com/base32/ 
// 		for conversion to base32 
//		(if you want to verify that the code is generated correctly by using Google Authenticator application)
uint8_t hmacKey_MicroView[] = {0x4d, 0x69, 0x63, 0x72, 0x6f, 0x56, 0x69, 0x65, 0x77};


TOTP totp = TOTP(hmacKey_MicroView, sizeof(hmacKey_MicroView)/sizeof(uint8_t));
char code[7];

// Set your own pins with these defines !
#define DS1302_SCLK_PIN   3    // Arduino pin for the Serial Clock
#define DS1302_IO_PIN     5    // Arduino pin for the Data I/O
#define DS1302_CE_PIN     6    // Arduino pin for the Chip Enable

#define TZ_OFFSET_IN_SECS -2*SECS_PER_HOUR // offset from GMT in secs

DS1302 rtc(DS1302_CE_PIN,DS1302_IO_PIN,DS1302_SCLK_PIN);

MicroViewWidget *slider;  


void setup() {
	// MicroView setup:

    uView.begin();
    uView.clear(PAGE);      // clear the page buffer
	slider = new MicroViewSlider(0,40,0,30, WIDGETSTYLE1);  
	
// Remove the next define, 
// after the right date and time are set.
// #define SET_DATE_TIME_JUST_ONCE
#ifdef SET_DATE_TIME_JUST_ONCE  
	rtc.setDate(7,9,2014); // Set date to Sep 6, 2014
	rtc.setDOW(SUNDAY); // Set day of the week to Saturday
	rtc.setTime(17,18,45); // Set time to 16:41:00
#endif

	// set internal timer, accordning to exernal one
	Time tm = rtc.getTime();
	setTime(tm.hour , tm.min ,tm.sec, tm.date, tm.mon, tm.year);
}

void loop() {

  	char buffer[80];     // the code uses 70 characters.

  	long GMT = (TZ_OFFSET_IN_SECS) + now();  // It should be better to use external timer, if it's more accurate
	
	uView.setCursor(1,2);
	uView.print(rtc.getDateStr());

  	uView.setCursor(8,16);
	uView.print(rtc.getTimeStr()); // show current local time, not GMT

	
	slider->setValue(30-second()%30);  // Tokens expire every 30 seconds
	
  	char* newCode = totp.getCode(GMT);
	if(strcmp(code, newCode) != 0) {
		strcpy(code, newCode);
		uView.setCursor(16,30);
    	uView.print(code);
	}  

    uView.display();        // display current page buffer
  	delay(1000);
}

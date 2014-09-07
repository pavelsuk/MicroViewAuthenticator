MicroViewAuthenticator
======================

TOTP Authenticator that uses Microview (as Arduino+Display) +  DS1302. 

Inspired by [MicroView TOTP project from AustinSaintAubin](https://github.com/AustinSaintAubin/Arduino_MicroView_OAuth_TOTP)

Hardware schema is based on [MicroView Clock](https://github.com/pavelsuk/MicroViewClock). See also [Project page for MicroView Clock on samepage.io](https://samepage.io/app/#!/8740458cffb7c86971911d5f12e1e2291de7f7b7/page-132750646494497742-microview-clock). It contains several setup and installation hints. 

The project is also published on [codebender](https://codebender.cc/sketch:47785)

Tested with Google Authenticator and Sophos Authenticator. It works fine - just don't forget to change the timezone offset in microviewauth.ino.  

### Used libraries
- [DS1302](http://www.henningkarlsen.com/electronics/library.php?id=5)
- [ArduinoLib_TOTP](https://github.com/lucadentella/ArduinoLib_TOTP)
- [CryptoSuite](https://github.com/bakercp/Cryptosuite) - use bakercp version, the original is not compilable. Or just change in all occurences of write function in *.h a *.cpp: 

```
 -  virtual void write(uint8_t);
 +  virtual size_t write(uint8_t);
```


### Content
- /sketch: code for MicroView Authenticator. 
- /doc: schema (see also [MicroView Clock](https://github.com/pavelsuk/MicroViewClock))

![Breadboard](/doc/schema_bb.png) 
![Schema](/doc/schema_schem.png) 

 

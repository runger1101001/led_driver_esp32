
#include "./homekit.h"
#include "./ssid.h"
#include "./wifi.h"
#include "./pixels.h"

void init_homekit(Adafruit_NeoPixel* strip) {
    Serial.println("Initializing HomeKit...");
    Serial.flush();

    homeSpan.setLogLevel(1);
    homeSpan.reserveSocketConnections(1); // REST API
    homeSpan.setSketchVersion("1.0");
    homeSpan.setPortNum(1201);
    homeSpan.setWifiCallback(initWebserver);
    homeSpan.setWifiCredentials(WLAN_SSID, WLAN_PASS);
    homeSpan.setPairingCode(PAIR_CODE);
    homeSpan.begin(Category::Lighting, "Trixel LED Controller", "Trixel", "TrixelController_v1.0");
    homeSpan.enableOTA();

    new SpanAccessory();                                                          
    new Service::AccessoryInformation();    
      new Characteristic::Identify();               
      new Characteristic::Name("Trixel"); 
    new DEV_NeoLED(strip);

    //homeSpan.autoPoll();
};


DEV_NeoLED::DEV_NeoLED(Adafruit_NeoPixel *strip) : Service::LightBulb(){       // constructor() method
    power=new Characteristic::On();                    
    H=new Characteristic::Hue(0);              // instantiate the Hue Characteristic with an initial value of 0 out of 360
    S=new Characteristic::Saturation(0);       // instantiate the Saturation Characteristic with an initial value of 0%
    V=new Characteristic::Brightness(100);     // instantiate the Brightness Characteristic with an initial value of 100%
    V->setRange(0,100,1);                      // sets the range of the Brightness to be from a min of 5%, to a max of 100%, in steps of 1%
    _strip = strip;
}; // end constructor




boolean DEV_NeoLED::update(){

    boolean p;
    float v, h, s, r, g, b;
    char cBuf[128];

    h=H->getVal<float>(); // get and store all current values.  Note the use of the <float> template to properly read the values
    s=S->getVal<float>();
    v=V->getVal<float>(); // though H and S are defined as FLOAT in HAP, V (which is brightness) is defined as INT, but will be re-cast appropriately
    p=power->getVal();

    if(power->updated()){
      p=power->getNewVal();
      sprintf(cBuf,"Power=%s->%s, ",power->getVal()?"true":"false",p?"true":"false");
    } else {
      sprintf(cBuf,"Power=%s, ",p?"true":"false");
    }
    LOG1(cBuf);
      
    if(H->updated()){
      h=H->getNewVal<float>();
      sprintf(cBuf,"H=%.0f->%.0f, ",H->getVal<float>(),h);
    } else {
      sprintf(cBuf,"H=%.0f, ",h);
    }
    LOG1(cBuf);

    if(S->updated()){
      s=S->getNewVal<float>();
      sprintf(cBuf,"S=%.0f->%.0f, ",S->getVal<float>(),s);
    } else {
      sprintf(cBuf,"S=%.0f, ",s);
    }
    LOG1(cBuf);

    if(V->updated()){
      v=V->getNewVal<float>();
      sprintf(cBuf,"V=%.0f->%.0f  ",V->getVal<float>(),v);
    } else {
      sprintf(cBuf,"V=%.0f  ",v);
    }
    LOG1(cBuf);

    LedPin::HSVtoRGB(h,s/100.0,v/100.0,&r,&g,&b);   // since HomeKit provides S and V in percent, scale down by 100

    int R, G, B;

    R=r*255;
    G=g*255;
    B=b*255;

    sprintf(cBuf,"RGB=(%d,%d,%d)\n",R,G,B);
    LOG1(cBuf);

    if (p!=0) {
        setAnimation(false);
        setBrightness(255);
        setAllPixels(R, G, B);
    }
    else
      setAllPixelsOff();

    return(true);
  
  };
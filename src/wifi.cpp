
#include "./ssid.h"
#include "WiFi.h"
#include "WiFiClient.h"
#include "WiFiServer.h"
#include "WebServer.h"
#include "./pixels.h"
#include <uri/UriBraces.h>

WebServer webServer(80);


void initWebserver(){
    Serial.println("Starting webserver...");
    webServer.enableCORS(true);
    webServer.begin();

    webServer.on("/", [](){
        webServer.send(200, "text/plain", "Hello from ESP32!");
    });

    webServer.on("/off", HTTP_GET, [](){
        setAnimation(false); // TODO think about the threading model - it would be better to pass the pixel updates off to a separate thread
        setAllPixelsOff();
        webServer.send(200, "application/json", "");
    });

    webServer.on(UriBraces("/trixels/{}"), HTTP_GET, [](){
        String pix = webServer.pathArg(0);
        int pixel = pix.toInt();
        String color = webServer.arg("color");
        String r = webServer.arg("r");
        String g = webServer.arg("g");
        String b = webServer.arg("b");
        String br = webServer.arg("brightness");
        Serial.println("Setting trixel " + pix + " to " + r + "," + g + "," + b + " with brightness " + br);
        if (br!="") {
            setBrightness(br.toInt());
        }
        if (r!="" || b!="" || g!="") {
            if (r=="") r="0";
            if (g=="") g="0";
            if (b=="") b="0";
            setPixel(pixel, r.toInt(), g.toInt(), b.toInt());
        }
        else if (br!="") {  
            showPixels();
        }
        uint32_t pixVal = getPixel(pixel);
        r = String((pixVal >> 16) & 0xFF);
        g = String((pixVal >> 8) & 0xFF);
        b = String(pixVal & 0xFF);
        webServer.send(200, "application/json", "{ \"r\":" + r + ", \"g\":" + g + ", \"b\":" + b + ", \"brightness\":" + getBrightness() + " }");
    });

    webServer.on("/trixels", HTTP_OPTIONS, [](){
        webServer.send(200, "application/json", "");
    });


    webServer.on("/trixels", HTTP_PUT, [](){
        String hex = webServer.arg("plain");
        if (hex!="") {
            int i=0;
            while ((i+6) <= hex.length()){
                
            }
        }
        webServer.send(200, "application/json", "");
    });

    webServer.on("/trixels", HTTP_DELETE, [](){
        clearPixels();
        webServer.send(200, "application/json", "");
    });

    webServer.on("/config", HTTP_POST, [](){
        // TODO
        webServer.send(200, "application/json", "");
    });

    webServer.on("/config", HTTP_OPTIONS, [](){
        webServer.send(200, "application/json", "");
    });

    webServer.on("/config", HTTP_GET, [](){
        webServer.send(200, "application/json", "");
    });

    webServer.on("/animation", HTTP_GET, [](){
        String en = webServer.arg("enable");
        if (en=="")
            en = webServer.arg("enabled"); // support both, its a common mistake
        String delay = webServer.arg("delay");
        int delayMs = getAnimationDelayMs();
        if (delay!="")
            delayMs = delay.toInt();
        if (en!="") {
            if (en=="true" || en=="1")
                setAnimation(true, delayMs);
            else
                setAnimation(false);
        }
        else if (delay!="")
            setAnimation(isAnimation(), delayMs);
        String json = "{ \"enabled\":";
        json += isAnimation() ? "true" : "false";
        json += ", \"delay\":";
        json += getAnimationDelayMs();
        json += " }";
        webServer.send(200, "application/json", json);
    });


    webServer.onNotFound([](){
        webServer.send(404, "text/plain", "Not found");
    });

    Serial.println("Webserver started");
};


void handleWebserver(){
    webServer.handleClient();
};
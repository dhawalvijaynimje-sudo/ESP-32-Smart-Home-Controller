#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <WebServer.h>

WebServer server(80);

Adafruit_SSD1306 oled(128,64,&Wire,-1);

bool led1 = false;
bool led2 = false;


void home(){

String page =

"<html>"
"<body style='text-align:center;'>"
"<h1>ESP32 SMART HOME</h1>";


// LED 1

if(!led1){

page +=
"<h2>LED 1 OFF</h2>"
"<a href='/ledon1'>"
"<button>LED 1 ON</button>"
"</a>";

}
else{

page +=
"<h2>LED 1 ON</h2>"
"<a href='/ledoff1'>"
"<button>LED 1 OFF</button>"
"</a>"
"<br><br>"
"<a href='/power1'>"
"SET POWER LED 1"
"</a>";

}


page += "<br><br>";



// LED 2

if(!led2){

page +=
"<h2>LED 2 OFF</h2>"
"<a href='/ledon2'>"
"<button>LED 2 ON</button>"
"</a>";

}

else{

page +=

"<h2>LED 2 ON</h2>"
"<a href='/ledoff2'>"
"<button>LED 2 OFF</button>"
"</a>"
"<br><br>"
"<a href='/power2'>"
"SET POWER LED 2"
"</a>";

}



page +=

"</body>"
"</html>";


server.send(200,"text/html",page);

}



// LED FUNCTIONS


void ledon1(){

led1=true;
ledcWrite(4,255);

home();

}


void ledoff1(){

led1=false;
ledcWrite(4,0);

home();

}



void ledon2(){

led2=true;
ledcWrite(5,255);

home();

}


void ledoff2(){

led2=false;
ledcWrite(5,0);

home();

}



// SLIDER PAGE 1


void power1(){

server.send(200,"text/html",

"<html>"
"<body style='text-align:center;'>"

"<h1>LED 1 BRIGHTNESS</h1>"

"<form action='/setpower1'>"

"<input type='range' name='v1' min='0' max='255'>"

"<br><br>"

"<input type='submit' value='SET'>"

"</form>"

"<br>"
"<a href='/'>BACK</a>"

"</body>"
"</html>"

);

}



// SLIDER PAGE 2


void power2(){

server.send(200,"text/html",

"<html>"
"<body style='text-align:center;'>"

"<h1>LED 2 BRIGHTNESS</h1>"

"<form action='/setpower2'>"

"<input type='range' name='v2' min='0' max='255'>"

"<br><br>"

"<input type='submit' value='SET'>"

"</form>"

"<br>"
"<a href='/'>BACK</a>"

"</body>"
"</html>"

);

}



// SET PWM


void setpower1(){

int value = server.arg("v1").toInt();

ledcWrite(4,value);

led1=true;

home();

}



void setpower2(){

int value = server.arg("v2").toInt();

ledcWrite(5,value);

led2=true;

home();

}




void setup(){


Serial.begin(115200);


// OLED

Wire.begin(21,22);


if(!oled.begin(SSD1306_SWITCHCAPVCC,0x3C)){

Serial.println("OLED ERROR");

while(1);

}


oled.clearDisplay();

oled.setTextColor(WHITE);

oled.setTextSize(1);

oled.setCursor(0,0);

oled.println("ESP32 SMART HOME");

oled.display();



// PWM

ledcAttach(4,5000,8);
ledcAttach(5,5000,8);



// WIFI AP

WiFi.softAP("Smart-Home","12345678");


delay(1000);


String ip = WiFi.softAPIP().toString();


oled.clearDisplay();

oled.setTextSize(1);

oled.setCursor(0,0);

oled.println("CONNECT IP:");

oled.setTextSize(1);

oled.setCursor(0,20);

oled.println(ip);

oled.display();




// ROUTES


server.on("/",home);


server.on("/ledon1",ledon1);
server.on("/ledoff1",ledoff1);

server.on("/ledon2",ledon2);
server.on("/ledoff2",ledoff2);


server.on("/power1",power1);
server.on("/power2",power2);


server.on("/setpower1",setpower1);
server.on("/setpower2",setpower2);



server.begin();


Serial.println(ip);

}



void loop(){

server.handleClient();

}
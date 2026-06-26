#include <WebServer.h>
#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

Adafruit_SSD1306 oled(128,64,&Wire,-1);

WebServer server(80);


bool s1=false;
bool s2=false;

bool p1=false;
bool p2=false;



void home(){

String page =

"<html>"
"<body style='text-align:center;'>"
"<h1> SMART HOME CONTROLLER </h1>";


// LED CONTROL

if(s1 == false){

page +=

"<a href='/ledon'>"
"<button> LED ON </button>"
"</a>"
"<br><br>"
"<p> Light is OFF </p>"
"<br><br>";

}

else{

page +=

"<a href='/ledoff'>"
"<button> LED OFF </button>"
"</a>"
"<br><br>"
"<p> Light is ON </p>"
"<br><br>";


// show power option only when LED is ON

if(p1 == false){

page +=

"<a href='/setled'>"
"<button> Set power of LED </button>"
"</a>"
"<br><br>";

}

else{

page +=

"<form action='/ledpower'>"
"<input type='range' name='v1' min='0' max='255'>"
"<br><br>"
"<input type='submit' value='SET'>"
"</form>"
"<br><br>";

}

}




// FAN CONTROL


if(s2 == false){

page +=

"<a href='/fanon'>"
"<button> FAN ON </button>"
"</a>"
"<br><br>"
"<p> Fan is OFF </p>"
"<br><br>";

}

else{

page +=

"<a href='/fanoff'>"
"<button> FAN OFF </button>"
"</a>"
"<br><br>"
"<p> Fan is ON </p>"
"<br><br>";


// show fan power only when fan is ON

if(p2 == false){

page +=

"<a href='/setfan'>"
"<button> Set power of Fan </button>"
"</a>"
"<br><br>";

}

else{

page +=

"<form action='/fanpower'>"
"<input type='range' name='v2' min='0' max='255'>"
"<br><br>"
"<input type='submit' value='SET'>"
"</form>"
"<br><br>";

}

}



page +=

"</body>"
"</html>";


server.send(200,"text/html",page);

}






void ledon(){

s1=true;

ledcWrite(4,255);

status();
home();

}



void ledoff(){

s1=false;

ledcWrite(4,0);

status();
home();

}




void fanon(){

s2=true;


digitalWrite(18,HIGH);
digitalWrite(19,LOW);

ledcWrite(5,255);


status();
home();

}




void fanoff(){

s2=false;


digitalWrite(18,LOW);
digitalWrite(19,LOW);


ledcWrite(5,0);


status();
home();

}





void showLedPower(){

p1=true;

home();

}



void showFanPower(){

p2=true;

home();

}




void setled(){

int v1 = server.arg("v1").toInt();


ledcWrite(4,v1);


p1=false;


status();
home();

}





void setfan(){

int v2 = server.arg("v2").toInt();


digitalWrite(18,HIGH);
digitalWrite(19,LOW);


ledcWrite(5,v2);


p2=false;


status();
home();

}






void status(){

oled.clearDisplay();

oled.setTextSize(1);
oled.setTextColor(WHITE);


oled.setCursor(0,0);

oled.println("SMART HOME");


oled.setCursor(0,16);

oled.println(WiFi.softAPIP());



oled.setCursor(0,32);

if(s1)
oled.println("LED: ON");
else
oled.println("LED: OFF");



oled.setCursor(0,48);

if(s2)
oled.println("FAN: ON");
else
oled.println("FAN: OFF");


oled.display();

}





void setup(){


Serial.begin(115200);


WiFi.softAP("Smart-Home","12345678");


Wire.begin(21,22);



ledcAttach(4,5000,8);
ledcAttach(5,5000,8);



pinMode(18,OUTPUT);
pinMode(19,OUTPUT);



oled.begin(SSD1306_SWITCHCAPVCC,0x3C);



status();



// routes

server.on("/",home);


server.on("/ledon",ledon);
server.on("/ledoff",ledoff);


server.on("/fanon",fanon);
server.on("/fanoff",fanoff);



server.on("/setled",showLedPower);
server.on("/setfan",showFanPower);



server.on("/ledpower",setled);
server.on("/fanpower",setfan);


server.begin();

}




void loop(){

server.handleClient();

}
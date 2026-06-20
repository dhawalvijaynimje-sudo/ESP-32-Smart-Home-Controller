#include<WiFi.h>
#include<WebServer.h>

WebServer server(80);

bool state = false;
bool state1 = false;
void home(){
  String page = 
  "<html>"
  "<body style='text-align:center;'>"
  "<h1> LED CONTROL </h1>";
  if(state == false){
    page += 
    "<a href = '/ledon'>"
    "<button>LED 1 ON</button>"
    "</a>"
    "<p> LED 1 IS OFF </p>"
    "<br><br>";
  }
  else {
    page += 
    "<a href = '/power'>"
    "set power of LED 1"
    "</a>"
    "<br><br>"
    "<p> LED 1 is ON </p>"
    "<a href = '/ledoff'>"
    "<button>LED 1 OFF</button>"
    "</a>"
    "<br><br>";
  }
   if(state1 == false){
    page += 
    "<a href = '/ledon1'>"
    "<button>LED 2 ON</button>"
    "</a>"
    "<p> LED 2 IS OFF </p>"
    "<br><br>";
  }
  else {
    page += 
    "<a href = '/power1'>"
    "set power of LED 2"
    "</a>"
    "<br><br>"
    "<p> LED 2 is ON </p>"
    "<a href = '/ledoff1'>"
    "<button>LED 2 OFF</button>"
    "</a>"
    "<br><br>";
  }

  page +=
  "</body>"
  "</html>";

  server.send(200, "text/html", page);
}

void ledon(){
  state = true;
  ledcWrite(4, 255); 
  home();
}

void ledoff(){
  state = false;
  ledcWrite(4, 0); 
  home();
}

void ledon1(){
  state1 = true;
  ledcWrite(5, 255); 
  home();
}

void ledoff1(){
  state1 = false;
  ledcWrite(5, 0); 
  home();
}

void power(){
  server.send(200, "text/html",
  "<h1> Set Power of LED 1 </h1>"
  "<form action = '/setpower'>"
  "<input type = 'number' name = 'value' min = '0' max = '255'>"
  "<br><br>"
  "<input type = 'submit' value = 'Set'>"
  "</form>"
  );
}

void power1(){
  server.send(200, "text/html",
  "<h1> Set Power of LED 2 </h1>"
  "<form action = '/setpower1'>"
  "<input type = 'number' name = 'value1' min = '0' max = '255'>"
  "<br><br>"
  "<input type = 'submit' value = 'Set'>"
  "</form>"
  );
}

void setpower(){
  int value = server.arg("value").toInt();
  ledcWrite(4, value);
  server.send(200, "text/html",
  "<h1>Power Updated</h1>"
  "<a href = '/'>Back</a>"
  
  );
}

void setpower1(){
  int value1 = server.arg("value1").toInt();
  ledcWrite(5, value1);
  server.send(200, "text/html",
  "<h1>Power Updated</h1>"
  "<a href = '/'>Back</a>"
  
  );
}

void setup(){
  Serial.begin(115200);
  ledcAttach(4, 5000, 8);
  ledcAttach(5, 5000, 8);
  WiFi.softAP("test", "123455678");
  Serial.print(WiFi.softAPIP());
  server.on("/", home);
  server.on("/setpower", setpower);
  server.on("/ledon", ledon);
  server.on("/ledoff", ledoff);
  server.on("/power", power);
  server.on("/setpower1", setpower1);
  server.on("/ledon1", ledon1);
  server.on("/ledoff1", ledoff1);
  server.on("/power1", power1);
  server.begin();
}

void loop(){
  server.handleClient();
}

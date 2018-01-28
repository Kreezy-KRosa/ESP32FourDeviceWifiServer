// ESP32 Dev Kit V1 4 Device Wifi Server Example Code
// By Kreezy(KRosa) 1.28.2018

#include <WiFi.h>

const char* ssid = "ENTER YOUR WIFI NAME HERE";             // enter your wifi's ssid name inside the ""'s // EXAMPLE "MyWifi"

const char* password = "ENTER YOUR WIFI PASSWORD HERE";     // enter your wifi's password inside the ""'s  // Example "Password"
 

WiFiServer server(80);                // wifi server setup
 
void setup() {
  Serial.begin(115200);               // serial connection for debugging
  delay(10);
  pinMode(5, OUTPUT);                 // pins used to turn devices on/off are set to outputs here
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(2, OUTPUT);                 // pin 2 will control the onboard LED
  digitalWrite(5, LOW);               // turns all buttons to a default off state
  digitalWrite(4, LOW);
  digitalWrite(0, LOW);
  digitalWrite(13, LOW);
 
                                      // Connects to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {   // Onboard LED will flash while connecting to your network
    delay(500);
    Serial.print(".");
  digitalWrite(2, HIGH);
  delay(10);
  digitalWrite(2, LOW);
  delay(10);
  }
  digitalWrite(2, HIGH);                    // Onboard LED will stay ON while connected to your network
  Serial.println("");
  Serial.println("WiFi connected");
 
                                      // Starts the server
  server.begin();
  Serial.println("Server started");
 
                                      // Prints the IP address. Use serial monitor to double check the server ip
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
                                       // Checks if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
                                       // Waits until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
                                        // Reads the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
                                       // Matches the request
 
 
  if (request.indexOf("/device1on") > 0)  {
    digitalWrite(5, HIGH);
   
  }
  if (request.indexOf("/device1off") >0)  {
    digitalWrite(5, LOW);
   
  }

   if (request.indexOf("/device2on") > 0)  {
    digitalWrite(18, HIGH);
   
  }
  if (request.indexOf("/device2off") >0)  { 
    digitalWrite(18, LOW);                         // Logic for whether device is on or off
                                                  // Depending on button press from client
  }
    if (request.indexOf("/device3on") >0)  {
    digitalWrite(19, HIGH);
   
  }
  if (request.indexOf("/device3off") > 0)  {
    digitalWrite(19, LOW);
   
  }
   if (request.indexOf("/device4on") > 0)  {
    digitalWrite(21, HIGH);
   
  }
  if (request.indexOf("/device4off") > 0)  {
    digitalWrite(21, LOW);
   
  }
                              
 
                                        // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
  client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");                  // This is where the webpage is created that will reside inside the ESP32
 client.println("</head>");
  client.println("<body bgcolor = \"#62B4E1\">"); 
  client.println("<hr/><hr>");
  client.println("<h4><center> Kreezy's Wifi Device Dashboard </center></h4>");                                       
  client.println("<hr/><hr>");
  client.println("<br><br>");
  client.println("<br><br>");
  client.println("<center>");
  client.println("Device 1");
  client.println("<a href=\"/device1on\"\"><button>Turn On </button></a>");                                             // How the buttons are made and how they function
  client.println("<a href=\"/device1off\"\"><button>Turn Off </button></a><br />");  
  client.println("</center>");   
  client.println("<br><br>");
   client.println("<center>");
   client.println("Device 2");
  client.println("<a href=\"/device2on\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/device2off\"\"><button>Turn Off </button></a><br />");  
client.println("</center>"); 
  client.println("<br><br>");
    client.println("<center>");
   client.println("Device 3");
  client.println("<a href=\"/device3on\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/device3off\"\"><button>Turn Off </button></a><br />");  
client.println("</center>"); 
  client.println("<br><br>");
   client.println("<center>");
   client.println("Device 4");
  client.println("<a href=\"/device4on\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/device4off\"\"><button>Turn Off </button></a><br />");  
client.println("</center>"); 
  client.println("<br><br>");
  client.println("<center>");
  client.println("<table border=\"5\">");
 client.println("<tr>");
  if (digitalRead(5))
         { 
           client.print("<td>Device1 is ON</td>");
        
         }
          else
          {
            client.print("<td>Device 1 is OFF</td>");
      
        }
     
        client.println("<br />");
             
         if (digitalRead(4))
          { 
           client.print("<td>Device 2 is ON</td>");                                                 // Changes the text in the box on the webpage 

         }
          else
          {

            client.print("<td>Device 2 is OFF</td>");

          }
          client.println("</tr>");


          client.println("<tr>");

          if (digitalRead(0))

          { 
           client.print("<td>Device 3 is ON</td>");

          }

          else

          {
            client.print("<td>Device 3 is OFF</td>");
          }


          if (digitalRead(13))


          { 


           client.print("<td>Device 4 is ON</td>");

          }


          else


          {


            client.print("<td>Device 4 is OFF</td>");


          }

          client.println("</tr>");


          client.println("</table>");

          client.println("</center>");
  client.println("</html>"); 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
} // The End :) Kreezy..

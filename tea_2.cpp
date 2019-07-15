// Load Wi-Fi library
#include <ESP8266WiFi.h>
String local = "local";
// Replace with your network credentials
const char *ssid = "";
const char *password = "";
// Set web server port number to 80
WiFiServer server(80);
// Variable to store the HTTP request
String header;
// Load Servo Library
#include <Servo.h>
// variables for the servo
Servo servo;
int angle = 70;
// Auxiliar variables to store the current output state
String outputState = "off";
String outputWState = "off";
String outputBState = "off";
String outputGState = "off";
String outputHState = "off";
// Assign output variables to GPIO pins
const int led = 16; // D0
void setup()
{
  Serial.begin(9600);
  // Initialize the LED pin as an output:
  pinMode(led, OUTPUT);
  // Set outputs to HIGH which is off for the built in LED
  digitalWrite(led, LOW);
  // Initialize both the pin and motor for both servos:
  servo.attach(2); // D4
  servo.write(angle);
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}
void loop()
{
  WiFiClient client = server.available();
  if (client)
  {                                // If a new client connects,
    Serial.println("New Client."); // print a message out in the serial port
    String currentLine = "";       // make a String to hold incoming data from the client
    while (client.connected())
    { // loop while the client's connected
      if (client.available())
      {                         // if there's bytes to read from the client,
        char c = client.read(); // read a byte, then
        Serial.write(c);        // print it out the serial monitor
        header += c;
        if (c == '\n')
        { // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0)
          {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            // Blink LED to show it is starting
            digitalWrite(led, LOW);
            delay(100);
            digitalWrite(led, HIGH);
            delay(100);
            digitalWrite(led, LOW);
            delay(100);
            digitalWrite(led, HIGH);
            delay(100);
            digitalWrite(led, LOW);
            delay(100);
            digitalWrite(led, HIGH);
            delay(100);
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<link href=\"https://fonts.googleapis.com/css?family=Indie+Flower|Permanent+Marker&display=swap\" rel=\"stylesheet\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html {font-family: 'Indie Flower', cursive; display: inline-block; margin: 0px auto; text-align: center; background-color: rgba(255, 111, 0, 0.5);}");
            // Button Class
            client.println("button {border: none; color: white; padding: 16px 40px; font-family: 'Permanent Marker', cursive;");
            client.println("text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}");
            // Black Tea Buttons
            client.println("#blackOn {background-color: #cf1a11;}");
            client.println("#blackOff {background-color: #cf4b44;}");
            // White Tea Button
            client.println("#whiteOn {background-color: #44cfb3;}");
            client.println("#whiteOff {background-color: #94d1c5;}");
            // Green Tea Button
            client.println("#greenOn {background-color: #147002;}");
            client.println("#greenOff {background-color: #1d9106;}");
            // Herbal Tea Button
            client.println("#herbalOn {background-color: #dde010;}");
            client.println("#herbalOff {background-color: #f8fa78;}");
            // Exit Button
            client.println("#exitOn {background-color: #ccc;}");
            client.println("#exitOff {background-color: #eee;}</style></head>");
            // Web Page Heading
            client.println("<body><h1>T^2 - Tea Brewing Made Easy</h1>");
            if (header.indexOf("GET /black/on") >= 0)
            {
              outputBState = "on";
              client.println("<p class='button'>Brewing!</p>");
              // Loop to move servo
              for (angle = 70; angle > 0; angle--)
              {
                // sets the servo position according to the angle
                servo.write(angle);
                // waits for the servo to get there
                delay(5);
              }
              client.println("<p class='button'>Brewing!</p>");

              // Loop to print test length of brew time
              for (int brewTime = 10; brewTime > 0; brewTime--)
              {
                // count down the brew time in seconds
                client.println(brewTime);
                delay(1000);
              }
              outputBState = "off";
              client.println("<p class='button'>Finished!</p>");
            }
            else if (header.indexOf("GET /black/off") >= 0)
            {
              outputBState = "off";

              // Loop to return the servo motor back to starting position
              for (angle = 0; angle < 70; angle++)
              {
                // sets the servo position according to the angle
                servo.write(angle);
                // waits for the servo to get there
                delay(5);
              }
              client.println("<p class='button'>Finished!</p>");
              outputBState = "off";
            }

                        // Green Tea
            if (header.indexOf("GET /green/on") >= 0)
            {
              outputGState = "on";
              for (angle = 70; angle > 0; angle--)
              {
                // sets the servo position according to the angle
                servo.write(angle);
                // waits for the servo to get there
                delay(5);
              }
            }
            else if (header.indexOf("GET /green/off") >= 0)
            {
              outputGState = "off";
              for (angle = 0; angle < 70; angle++)
              {
                // sets the servo position according to the angle
                servo.write(angle);
                // waits for the servo to get there
                delay(5);
              }
            }
            if (header.indexOf("GET /white/on") >= 0)
            {
              outputWState = "on";
              for (angle = 70; angle > 0; angle--)
              {
                // sets the servo position according to the angle
                servo.write(angle);
                // waits for the servo to get there
                delay(5);
              }
            }
            else if (header.indexOf("GET /white/off") >= 0)
            {
              outputWState = "off";
              for (angle = 0; angle < 70; angle++)
              {
                // sets the servo position according to the angle
                servo.write(angle);
                // waits for the servo to get there
                delay(5);
              }
            }
            if (header.indexOf("GET /herbal/on") >= 0)
            {
              outputHState = "on";
              for (angle = 70; angle > 0; angle--)
              {
                // sets the servo position according to the angle
                servo.write(angle);
                // waits for the servo to get there
                delay(5);
              }
            }
            else if (header.indexOf("GET /herbal/off") >= 0)
            {
              outputHState = "off";
              for (angle = 0; angle < 70; angle++)
              {
                // sets the servo position according to the angle
                servo.write(angle);
                // waits for the servo to get there
                delay(5);
              }
            }
            if (header.indexOf("GET /exit/on") >= 0)
            {
              outputState = "on";
            }
            else if (header.indexOf("GET /exit/off") >= 0)
            {
              outputState = "off";
              outputWState = "off";
              outputBState = "off";
              outputGState = "off";
              outputHState = "off";
            }
            // Display current state, and ON/OFF buttons for black tea
            client.println("<p>Black Tea - State " + outputBState + "</p>");
            // If the outputBState is off, it displays the ON button
            if (outputBState == "off")
            {
              client.println("<p><a href=\"/black/on\"><button class=\"button\" id=\"blackOn\">BREW</button></a></p>");
            }
            else
            {
              client.println("<p><a href=\"/black/off\"><button class=\"button\" id=\"blackOff\">BREWING</button></a></p>");
            }
            client.println("<p>Green Tea State " + outputGState + "</p>");
            // If the outputGState is off, it displays the ON button
            if (outputGState == "off")
            {
              client.println("<p><a href=\"/green/on\"><button class=\"button\" id=\"greenOn\">BREW</button></a></p>");
            }
            else
            {
              client.println("<p><a href=\"/green/off\"><button class=\"button\" id=\"greenOff\">BREWING</button></a></p>");
            }
            // Display current state, and ON/OFF buttons for white tea
            client.println("<p>White Tea - State " + outputWState + "</p>");
            // If the outputWState is off, it displays the ON button
            if (outputWState == "off")
            {
              client.println("<p><a href=\"/white/on\"><button class=\"button\" id=\"whiteOn\">BREW</button></a></p>");
            }
            else
            {
              client.println("<p><a href=\"/white/off\"><button class=\"button\" id=\"whiteOff\">BREWING</button></a></p>");
            }
            // Display current state, and ON/OFF buttons for white tea
            client.println("<p>Herbal Tea - State " + outputHState + "</p>");
            // If the outputHState is off, it displays the ON button
            if (outputHState == "off")
            {
              client.println("<p><a href=\"/herbal/on\"><button class=\"button\" id=\"herbalOn\">BREW</button></a></p>");
            }
            else
            {
              client.println("<p><a href=\"/herbal/off\"><button class=\"button\" id=\"herbalOff\">BREWING</button></a></p>");
            }
            // Display current state, and ON/OFF buttons for exit button
            client.println("<p>Exit Button - State " + outputState + "</p>");
            // If the outputState is off, it displays the ON button
            if (outputState == "off")
            {
              client.println("<p><a href=\"/exit/on\"><button class=\"button\" id=\"exitOn\">CANCEL</button></a></p>");
            }
            else
            {
              client.println("<p><a href=\"/exit/off\"><button class=\"button\" id=\"exitOff\">RESET</button></a></p>");
            }
            client.println("</body></html>");
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          }
          else
          { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        }
        else if (c != '\r')
        {                   // if you got anything else but a carriage return character,
          currentLine += c; // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
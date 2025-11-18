#include <WiFi.h>

// WiFi credentials
const char* ssid     = "EYANG";
const char* password = "MekahMadinah";

// Motor pins
#define IN1 27
#define IN2 26
#define IN3 25
#define IN4 33
#define ENA 14
#define ENB 32

// Motor speed
int speedVal = 150;     
const int MIN_SPEED = 80;   // minimum working speed

// Current movement state
String currentAction = "stop";

// --- Apply speed instantly ---
void applySpeed() {
  int spd = speedVal;
  if (spd < MIN_SPEED && spd > 0) spd = MIN_SPEED;

  ledcWrite(0, spd); // ENA → channel 0
  ledcWrite(1, spd); // ENB → channel 1
}

// --- Motor actions ---
void forward() {
  Serial.println("FORWARD");
  currentAction = "forward";
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  Serial.println("BACKWARD");
  currentAction = "backward";
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left() {
  Serial.println("LEFT");
  currentAction = "left";
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right() {
  Serial.println("RIGHT");
  currentAction = "right";
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  Serial.println("STOP");
  currentAction = "stop";
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// --- Re-run last action after speed change ---
void replayLastAction() {
  if (currentAction == "forward") forward();
  else if (currentAction == "backward") backward();
  else if (currentAction == "left") left();
  else if (currentAction == "right") right();
  else stopMotors();
}

WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // NEW ESP32 core 3.x API
  ledcAttachChannel(ENA, 1000, 8, 0); 
  ledcAttachChannel(ENB, 1000, 8, 1);

  stopMotors();
  applySpeed();

  // WiFi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(400);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  String req = client.readStringUntil('\r');
  client.flush();

  // Movement
  if (req.indexOf("/forward") != -1) { forward(); }
  if (req.indexOf("/backward") != -1) { backward(); }
  if (req.indexOf("/left") != -1) { left(); }
  if (req.indexOf("/right") != -1) { right(); }
  if (req.indexOf("/stop") != -1) { stopMotors(); }

  // Speed
  if (req.indexOf("/speedup") != -1) {
    speedVal += 20;
    if (speedVal > 255) speedVal = 255;
    applySpeed();
    replayLastAction();
  }

  if (req.indexOf("/speeddown") != -1) {
    speedVal -= 20;
    if (speedVal < 0) speedVal = 0;
    applySpeed();
    replayLastAction();
  }

  // Web UI response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html\n");

  client.println("<html><body style='text-align:center;'>");
  client.println("<h1>ESP32 Robot Control</h1>");
  client.println("<h2>Speed: " + String(speedVal) + "</h2>");

  client.println("<button onclick=\"location.href='/speedup'\" style='width:120px;height:40px;'>Speed +</button>");
  client.println("<button onclick=\"location.href='/speeddown'\" style='width:120px;height:40px;'>Speed -</button><br><br>");

  client.println("<button onclick=\"location.href='/forward'\" style='width:150px;height:60px;font-size:20px;'>Forward</button><br><br>");
  client.println("<button onclick=\"location.href='/left'\" style='width:150px;height:60px;font-size:20px;'>Left</button>");
  client.println("<button onclick=\"location.href='/stop'\" style='width:150px;height:60px;font-size:20px;'>Stop</button>");
  client.println("<button onclick=\"location.href='/right'\" style='width:150px;height:60px;font-size:20px;'>Right</button><br><br>");

  client.println("<button onclick=\"location.href='/backward'\" style='width:150px;height:60px;font-size:20px;'>Backward</button>");

  client.println("</body></html>");
  client.stop();
}

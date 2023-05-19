// Pin assignments for relays
const int light1Pin = 2;
const int light2Pin = 3;
const int fanPin = 4;

// Variables to store the current state of lights and fan
bool light1State = false;
bool light2State = false;
bool fanState = false;

void setup() {
  // Set relay pins as output
  pinMode(light1Pin, OUTPUT);
  pinMode(light2Pin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  
  // Initially turn off lights and fan
  digitalWrite(light1Pin, LOW);
  digitalWrite(light2Pin, LOW);
  digitalWrite(fanPin, LOW);
  
  // Serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Check for incoming serial data
  if (Serial.available() > 0) {
    char command = Serial.read();
    
    // Process the received command
    switch (command) {
      case '1':
        toggleLight(1);
        break;
      case '2':
        toggleLight(2);
        break;
      case 'F':
        toggleFan();
        break;
      default:
        break;
    }
  }
}

// Function to toggle the state of a light
void toggleLight(int lightNum) {
  bool* lightState;
  int relayPin;
  
  // Determine the light based on the parameter
  switch (lightNum) {
    case 1:
      lightState = &light1State;
      relayPin = light1Pin;
      break;
    case 2:
      lightState = &light2State;
      relayPin = light2Pin;
      break;
    default:
      return;
  }
  
  // Toggle the state of the light
  *lightState = !(*lightState);
  digitalWrite(relayPin, *lightState ? HIGH : LOW);
  
  // Print the current state of the light
  Serial.print("Light ");
  Serial.print(lightNum);
  Serial.print(": ");
  Serial.println(*lightState ? "ON" : "OFF");
}

// Function to toggle the state of the fan
void toggleFan() {
  fanState = !fanState;
  digitalWrite(fanPin, fanState ? HIGH : LOW);
  
  // Print the current state of the fan
  Serial.print("Fan: ");
  Serial.println(fanState ? "ON" : "OFF");
}

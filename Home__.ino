#include <ESP8266WiFi.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>

// WiFi credentials
const char* ssid = "Marshal";
const char* password = "1234567890";

// Sinric Pro credentials
const char* APP_KEY = "6d50b77d-ba65-465a-a5fd-2b4e20c418e3pklmn0";
const char* APP_SECRET = "f6aa3ec3-cfd1-44d4-8906-fa46d628b24e-c5e761a0-de5c-4e94-a88a-63e757d0cb9dcgd0djn";
const char* SWITCH_ID = "674f9bce716c0bcb088d4007415554"; // Device ID from Sinric Pro dashboard

// Pin configuration
const int relayPin = 2; // GPIO pin connected to the relay
//const int relayPin = 1; // GPIO pin connected to the relay
bool onPowerState = false;

// Callback function for device state change
bool onPowerStateChange(const String &deviceId, bool &state) {
    Serial.printf("Device %s turned %s\n", deviceId.c_str(), state ? "ON" : "OFF");
    onPowerState = state;
    digitalWrite(relayPin, state ? LOW : HIGH); // Active LOW for relay
    return true;
}

void setup() {
    Serial.begin(115200);
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, HIGH); // Start with relay OFF

    // Connect to WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi!");

    // Initialize Sinric Pro
    SinricProSwitch &mySwitch = SinricPro[SWITCH_ID];
    mySwitch.onPowerState(onPowerStateChange);

    SinricPro.begin(APP_KEY, APP_SECRET);
}

void loop() {
    SinricPro.handle();
}

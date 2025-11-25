/*
 * UNIHIKER K10 Fridge Manager - Example Code
 *
 * This example shows how to send ingredient data from UNIHIKER K10 to the SustainHub API
 *
 * Board: UNIHIKER K10 (ESP32-S3 based)
 *
 * Arduino IDE Setup (Standard ESP32 Method - RECOMMENDED):
 * 1. Add ESP32 board manager URL in File → Preferences → Additional Boards Manager URLs:
 *    https://espressif.github.io/arduino-esp32/package_esp32_index.json
 * 2. Install "esp32" by Espressif from Tools → Board → Boards Manager
 * 3. Select Board: Tools → Board → ESP32 Arduino → ESP32S3 Dev Module
 * 4. Configure these settings in Tools menu:
 *    - USB CDC On Boot: "Enabled" (REQUIRED for Serial Monitor)
 *    - USB Mode: "Hardware CDC and JTAG"
 *    - Flash Size: "16MB (128Mb)"
 *    - Partition Scheme: "Default 4MB with spiffs (1.2MB APP/1.5MB SPIFFS)"
 *    - PSRAM: "OPI PSRAM"
 * 5. Select your K10's COM port in Tools → Port
 *
 * Alternative - UNIHIKER Official Package (if above doesn't work):
 * 1. Add: https://downloadcd.dfrobot.com.cn/UNIHIKER/package_unihiker_index.json
 * 2. Install "UNIHIKER" board package
 * 3. Select: Tools → Board → UNIHIKER → UNIHIKER K10
 * Note: The UNIHIKER package may have compatibility issues
 *
 * Required Libraries:
 * - WiFi (comes with ESP32-S3 board package)
 * - HTTPClient (comes with ESP32-S3 board package)
 * - ArduinoJson (install via Library Manager)
 *
 * UNIHIKER K10 Built-in Features (can be integrated):
 * - 2MP Camera (for barcode/QR scanning)
 * - Temperature & Humidity Sensor (for fridge monitoring)
 * - Light Sensor
 * - Accelerometer
 * - 2 Microphones
 * - 2 Buttons
 * - 3 RGB LEDs
 * - 1 Speaker
 * - 2.8" Color Display (240x320)
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// WiFi credentials
const char* ssid = "TinkercademyHome";
const char* password = "gethacking.com";

// API server address (update this to your server's IP when deployed)
const char* serverUrl = "http://192.168.1.100:3001/api";  // Replace with your server IP

// UNIHIKER K10 Built-in Buttons (optional - for manual ingredient entry)
#define BUTTON_A 0   // Button A
#define BUTTON_B 21  // Button B

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Test the connection
  delay(1000);
  testAPIConnection();
}

void loop() {
  // Example: Update ingredient every 60 seconds
  // In real use, you'd trigger this based on sensor data

  delay(60000);  // Wait 60 seconds

  // Example: Add or update an ingredient
  addOrUpdateIngredient("tomato", "vegetable", 5, "pieces", "2025-12-01");
}

// Test if the API server is reachable
void testAPIConnection() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(serverUrl) + "/health";

    http.begin(url);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("API Server Status: " + response);
    } else {
      Serial.println("Error connecting to API server");
      Serial.println("Make sure the backend is running and the IP address is correct");
    }

    http.end();
  }
}

// Add or update an ingredient
void addOrUpdateIngredient(String name, String category, int quantity, String unit, String expiryDate) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(serverUrl) + "/ingredients";

    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    // Create JSON document
    StaticJsonDocument<256> doc;
    doc["name"] = name;
    doc["category"] = category;
    doc["quantity"] = quantity;
    doc["unit"] = unit;
    doc["expiry_date"] = expiryDate;

    // Serialize JSON to string
    String jsonString;
    serializeJson(doc, jsonString);

    // Send POST request
    int httpResponseCode = http.POST(jsonString);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Ingredient added successfully!");
      Serial.println("Response: " + response);
    } else {
      Serial.print("Error adding ingredient. HTTP Response code: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
}

// Update a specific ingredient by ID
void updateIngredient(int id, String name, String category, int quantity, String unit, String expiryDate) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(serverUrl) + "/ingredients/" + String(id);

    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    // Create JSON document
    StaticJsonDocument<256> doc;
    doc["name"] = name;
    doc["category"] = category;
    doc["quantity"] = quantity;
    doc["unit"] = unit;
    doc["expiry_date"] = expiryDate;

    // Serialize JSON to string
    String jsonString;
    serializeJson(doc, jsonString);

    // Send PUT request
    int httpResponseCode = http.PUT(jsonString);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Ingredient updated successfully!");
      Serial.println("Response: " + response);
    } else {
      Serial.print("Error updating ingredient. HTTP Response code: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  }
}

// Delete an ingredient by ID
void deleteIngredient(int id) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(serverUrl) + "/ingredients/" + String(id);

    http.begin(url);

    // Send DELETE request
    int httpResponseCode = http.sendRequest("DELETE");

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Ingredient deleted successfully!");
      Serial.println("Response: " + response);
    } else {
      Serial.print("Error deleting ingredient. HTTP Response code: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  }
}

// Get all ingredients (useful for syncing)
void getAllIngredients() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(serverUrl) + "/ingredients";

    http.begin(url);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String payload = http.getString();
      Serial.println("All ingredients:");
      Serial.println(payload);

      // You can parse this JSON to work with the data
      // Example parsing:
      DynamicJsonDocument doc(2048);
      deserializeJson(doc, payload);
      JsonArray ingredients = doc.as<JsonArray>();

      for (JsonObject ingredient : ingredients) {
        const char* name = ingredient["name"];
        int quantity = ingredient["quantity"];
        const char* expiryDate = ingredient["expiry_date"];

        Serial.printf("- %s: %d (expires: %s)\n", name, quantity, expiryDate);
      }
    } else {
      Serial.print("Error fetching ingredients. HTTP Response code: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  }
}

/*
 * USAGE EXAMPLES:
 *
 * 1. Add a new ingredient:
 *    addOrUpdateIngredient("apple", "fruit", 3, "pieces", "2025-12-05");
 *
 * 2. Update an existing ingredient (you need to know its ID):
 *    updateIngredient(1, "tomato", "vegetable", 10, "pieces", "2025-12-01");
 *
 * 3. Delete an ingredient:
 *    deleteIngredient(1);
 *
 * 4. Get all ingredients:
 *    getAllIngredients();
 *
 * UNIHIKER K10 INTEGRATION IDEAS:
 * - Use the built-in 2MP camera for barcode/QR code scanning to identify products
 * - Use temperature & humidity sensor to monitor fridge conditions
 * - Use the 2.8" color display to show ingredient list and expiry dates
 * - Use buttons (BUTTON_A, BUTTON_B) for manual ingredient entry/navigation
 * - Use RGB LEDs to indicate ingredient status (green=fresh, yellow=expiring, red=expired)
 * - Connect weight sensors via Gravity ports to detect quantity changes
 * - Use RFID reader modules to track ingredients automatically
 * - Display alerts on screen when ingredients are about to expire
 * - Use the speaker to play audio alerts
 * - Connect external sensors via the Edge Connector (compatible with micro:bit accessories)
 *
 * Example K10-specific enhancement:
 * - Press BUTTON_A to add a new ingredient
 * - Press BUTTON_B to refresh and display all ingredients on the screen
 * - Camera scans barcode to auto-fill ingredient information
 */

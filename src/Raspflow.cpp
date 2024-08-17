#include "Raspflow.hpp"

#include <BluetoothLowEnergy.hpp>
#include <Network.hpp>

void Raspflow::processMessage(void* message) {
	Serial.print(static_cast<String*>(message)->c_str());
}

Application * app;

void setup() {
	Serial.begin(115200);

	app = new Raspflow();

#ifdef __SMART_APPLICATION_WITH_BLE__
	app->setBluetoothName("Raspflow", true);

	// We turn on safety
	BluetoothLowEnergy * ble = new BluetoothLowEnergy(app);
#endif

#ifdef __SMART_APPLICATION_WITH_WIFI__
	Network::getInstance()->begin("raspflow", true);

	WiFi.onEvent(
		[](WiFiEvent_t event, WiFiEventInfo_t info) {
			Serial.print("WiFi lost IP\n");
		},
		WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_LOST_IP
	);
	WiFi.onEvent(
		[](WiFiEvent_t event, WiFiEventInfo_t info) {
			Serial.print("WiFi.connected\n");
		},
		WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_CONNECTED
	);
	WiFi.onEvent(
		[](WiFiEvent_t event, WiFiEventInfo_t info) {
			Serial.print("WiFi.addressed: ");
			Serial.println(WiFi.localIP());
		},
		WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_GOT_IP
	);
	WiFi.onEvent(
		[](WiFiEvent_t event, WiFiEventInfo_t info) {
			Serial.print("WiFi.disconnected\n");
			digitalWrite(2, LOW);
		},
		WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED
	);

	// If there aren't credentials won't connect
	Network::getInstance()->connect();
#endif
}

void loop() {
#ifdef __SMART_APPLICATION_WITH_BLE__
	app->checkAdvertising();
#endif
}

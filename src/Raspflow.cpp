#include "Raspflow.hpp"
#include "Sensor.hpp"
#include "Motor.hpp"

#include <ArduinoJson.h>
#include <BluetoothLowEnergy.hpp>
#include <Network.hpp>

void Raspflow::processMessage(unsigned char * message, size_t length, bool printable) {
	if (printable) {
		for (int i = 0; i < length; ++i) {
			Serial.print((char) message[i]);
		}
	}

	#ifdef __SMART_APPLICATION_WITH_BLE__
	BluetoothLowEnergy::sendOut(&this->bleCharacteristics[0], "Recibido");
	#endif

	JsonDocument jsonRequest;
	deserializeJson(jsonRequest, message);
	delete[] message;

	// Execute all instructions here
	switch(jsonRequest["cmd"].as<uint8_t>()) {
		case 0:
			this->initializeModulesPointerArray(2);
			this->modulesPointer[0] = new Sensor("snsr", 1);
			this->modulesPointer[0]->start();
			this->modulesPointer[1] = new Motor("mtr", 1);
			this->modulesPointer[1]->start();
	}
}

void Raspflow::initializeModulesPointerArray(unsigned int quantity) {
	if (this->modulesPointer != nullptr) {
		while (this->modulesPointerQuantity) {
			delete this->modulesPointer[--this->modulesPointerQuantity];
		}
		delete[] this->modulesPointer;
	}

	this->modulesPointerQuantity = quantity;

	this->modulesPointer = new Module*[quantity];
}

#ifdef __SMART_APPLICATION_WITH_BLE__
void Raspflow::initializeBluetoothCharacteristicsArray() {
	if (this->bleCharacteristics != nullptr) {
		delete[] this->bleCharacteristics;
	}

	this->bluetoothCharacteristicsQuantity = 1;

	this->bleCharacteristics = new BLECharacteristic[1] {
		BLE_PINGPONG_UUID
	};

	this->bleCharacteristics[0].setWriteProperty(true);
	this->bleCharacteristics[0].setReadProperty(true);
	this->bleCharacteristics[0].setNotifyProperty(true);
	this->bleCharacteristics[0].addDescriptor(new BLEDescriptor(BLEUUID((uint16_t)0x2902)));
}

BluetoothLowEnergy * ble;
#endif

Application * app;

void setup() {
	app = new Raspflow();
	app->initializeModulesPointerArray(1);
	app->beginSerialPort(Serial);

#ifdef __SMART_APPLICATION_WITH_BLE__
	app->setBluetoothName("Proteus Raspflow", true);

	// We turn on safety
	ble = new BluetoothLowEnergy(app);
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

	Network::PASSWORD = "";
	Network::SSID = "";
	// If there aren't credentials won't connect
	Network::getInstance()->connect();
#endif
}

void loop() {
#ifdef __SMART_APPLICATION_WITH_BLE__
	ble->checkAdvertising();
#endif
}

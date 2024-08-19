#include "Sensor.hpp"

Sensor::Sensor(const char * name, int taskCore) : Module(name, taskCore) {
}

void Sensor::connect(void * data) {
}

void Sensor::run(void* data) {
	while (1) {
		vTaskDelay(this->iterationDelay);
		Serial.print("sensor iter\n");
	}
}

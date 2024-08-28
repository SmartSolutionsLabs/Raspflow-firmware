#include "Motor.hpp"

Motor::Motor(const char * name, int taskCore) : Module(name, taskCore) {
}

void Motor::connect(void * data) {
}

void Motor::run(void* data) {
	while (1) {
		vTaskDelay(this->iterationDelay);
		Serial.print("motor iter\n");
	}
}

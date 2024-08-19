#ifndef INC_SENSOR
#define INC_SENSOR

#include <Module.hpp>

class Sensor : public Module {
	public:
		Sensor(const char * name, int taskCore = 1);

		void connect(void * data) override;

		void run(void* data) override;
};

#endif

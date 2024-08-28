#ifndef INC_SENSOR
#define INC_SENSOR

#include <Module.hpp>

class Sensor : public Module {
	private:
		unsigned int value = 0;

	public:
		Sensor(const char * name, int taskCore = 1);

		void connect(void * data) override;

		void run(void* data) override;

		unsigned int getValue() const {
			return value;
		}
};

#endif

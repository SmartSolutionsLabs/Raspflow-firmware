#ifndef _INC_RASPFLOW_
#define _INC_RASPFLOW_

#include "BluetoothLowEnergy.hpp"
#include "Network.hpp"

#include <Arduino.h>

class Raspflow : public Application {
	public:
		void processMessage(void* message);
};

#endif

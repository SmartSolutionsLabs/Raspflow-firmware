#ifndef _INC_RASPFLOW_
#define _INC_RASPFLOW_

#include <Application.hpp>
#include <Arduino.h>

#define BLE_SERVICE_UUID  "49e0b347-e722-4ac0-92fb-a316e887fdea"
#define BLE_PINGPONG_UUID "a1e00971-7498-4cd5-9cd6-b03c1d394770"  // Read and write
#define BLE_STATUS_UUID   "a12f4c9e-503b-45eb-8d7b-7fb774cf51d0"  // Notify sensor data

class Raspflow : public Application {
	public:
		void processMessage(unsigned char * message, size_t length, bool printable);
		void initializeBluetoothCharacteristicsArray();
		void initializeModulesPointerArray(unsigned int quantity) override;
};

#endif

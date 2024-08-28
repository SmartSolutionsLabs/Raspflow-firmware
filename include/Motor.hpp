#ifndef INC_MOTOR
#define INC_MOTOR

#include <Module.hpp>

class Motor : public Module {
	private:
		bool running = false;

	public:
		Motor(const char * name, int taskCore = 1);

		void connect(void * data) override;

		void run(void* data) override;

		void setRunning(bool running) {
			running = running;
		}

		bool isRunning() const {
			return running;
		}
};

#endif

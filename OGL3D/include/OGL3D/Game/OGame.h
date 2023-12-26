#pragma once
#include <memory>

class OWindow;
class OGame
{
public:
	OGame();
	~OGame();

	void run();
	void quit();
protected:
	bool m_isRunning = true;
	/* An object that takes a
	pointer to a paticular type of instance */
	std::unique_ptr<OWindow> m_display;
};


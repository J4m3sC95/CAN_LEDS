# CAN_LEDS
LEDs Controlled via CAN

Current development points:
- SAMD10:
	- implement interrupt pin on MCP2515 to simplify code
	- create more flexible methods for configuring the MCP2515 (useful for future development)
	- create universal CAN code to allow use across whole setup (include light functions from 4313)
	- implement a control scheme for the LED strip
- Linux Interface:
	- Implement a way to distinguish between LED cube and strip (eg. another serial byte)
	- Add controls for LED strip
- Attiny84 RGB LED strip:
	- Write code modules to allow CAN comms/control (use code from above)
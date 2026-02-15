# IRDriverMock
A kernel module to mock [simple_ir_driver](https://github.com/BrianDelalex/simple-ir-driver) in a development environment where using the real driver is not possible.

Developping the IRHomeLab application on the target raspberrypi4 is not very convenient. Using this module coupled with RemoteControllerMock, we are able to simulates the missing parts in a development environment (Debian VM in my case).
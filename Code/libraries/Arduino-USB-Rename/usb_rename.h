#include "PluggableUSB.h"

class USBRename : public PluggableUSBModule {
  public:
    USBRename(
      const u8 *product_name = NULL,
      const u8 *manufacturer_name = NULL,
      const u8 *serial_num = NULL);
    int getInterface(uint8_t* interfaceCount);
    int getDescriptor(USBSetup& setup);
    bool setup(USBSetup& setup);

  private:
    const u8 *manufacturer_name;
    const u8 *product_name;
    const u8 *serial_num;
    uint8_t epType[0];
};

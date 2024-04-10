# Arduino USB Rename

Programatically rename a USB based Arduino without editing the board file.

```cpp
#include "usb_rename.h"

// Product name, Manufacturer, serial
// Any argument can be left off, or NULL to keep the original Arduino name
USBRename dummy = USBRename("USB Rename Demo", "mon.im", "1234");
```

No other code is required - the USB stack handles the rest.

## Caveats
Windows tends to consider a device with a different product name a new device -
you may experience some difficulty during initial programming as it assigns
a new serial port.

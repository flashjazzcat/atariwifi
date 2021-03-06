#include <Arduino.h>
#include <WiFiUdp.h>

#include "sio.h"
#include "networkDeviceSpec.h"
#include "networkProtocol.h"

class networkProtocolUDP : public networkProtocol 
{
public:
    networkProtocolUDP();
    ~networkProtocolUDP();

    virtual bool open(networkDeviceSpec* spec);
    virtual bool close();
    virtual bool read(byte* rx_buf, unsigned short len);
    virtual bool write(byte* tx_buf, unsigned short len);
    virtual bool status(byte* status_buf);
    virtual bool special(byte* sp_buf, unsigned short len, cmdFrame_t* cmdFrame);

private:
    WiFiUDP udp;
    char dest[64];
    unsigned short port;

    bool special_set_destination(const char* dest);
    bool special_set_tx_buffer_size(unsigned short size);
};
#include "bluetooth.h"
#include "sio.h"
#include "disk.h"
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void BluetoothManager::setup()
{
  SerialBT.begin(BT_NAME);
}

void BluetoothManager::start()
{
#ifdef DEBUG
  Debug_println("START SIO2BT");
#endif
  mActive = true;
  mPrevBaudrate = SIO.getBaudrate();
  SIO.setBaudrate(mBTBaudrate);
  SIO.sio_led(true);
}

void BluetoothManager::stop()
{
#ifdef DEBUG
  BUG_UART.println("STOP SIO2BT");
#endif
  mActive = false;
  SIO.setBaudrate(mPrevBaudrate);
  SIO.sio_led(false);
}

eBTBaudrate BluetoothManager::toggleBaudrate()
{
  SIO.sio_led(false);
  if(mBTBaudrate == eBTBaudrate::BT_STANDARD_BAUDRATE)
  {
    mBTBaudrate = eBTBaudrate::BT_HISPEED_BAUDRATE;
  }
  else
  {
    mBTBaudrate = eBTBaudrate::BT_STANDARD_BAUDRATE;
  }
  SIO.setBaudrate(mBTBaudrate);
  SIO.sio_led(true);
  return mBTBaudrate;
}

void BluetoothManager::service()
{
    if (SIO_UART.available()) {
      SerialBT.write(SIO_UART.read());
    }
    if (SerialBT.available()) {
      SIO_UART.write(SerialBT.read());
    }
}
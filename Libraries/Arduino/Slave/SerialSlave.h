
//      ******************************************************************
//      *                                                                *
//      *                 Header file for SerialSlave.c                  *
//      *                                                                *
//      *               Copyright (c) S. Reifel & Co, 2014               *
//      *                                                                *
//      ******************************************************************


#ifndef SerialSlave_h
#define SerialSlave_h

#include <Arduino.h>

//
// maximum packet sizes
//
const byte MASTER_COMMAND_MAX_DATA_BYTES = 16;
const byte SLAVE_RESPONSE_MAX_DATA_BYTES = 16;

//
// the SerialSlave class
//
class SerialSlave
{
  public:
    //
    // public functions
    //
    SerialSlave();
    void open(long baudRate, byte slaveAddr, byte transmitterEnablePin);
    void respondToCommandSendingNoData();
    void respondToCommandSendingWithData(byte dataLength, byte data[]);
    void sendResendCommandToMaster(void);

  private:
    //
    // private functions
    //
    void sentResponsePacketToMaster();
};


typedef void Func(byte dataLength, byte dataArray[]);

typedef struct callable {
  const char * shortName; //must be <= 16 characters
  Func * call;
} Callable;

Func numberOfCallables;
Func getNthCallable;
Func echo;
Func _pinMode;
Func _digitalWrite;
Func _digitalRead;
Func _analogWrite;
Func _analogRead;


extern Callable callables[];


byte lengthOf(const char* string);

void returns(const char* string);
void returns(byte dataLength, byte *dataArray);

void returns(byte v);
void processCommandFromMaster(byte commandByteFromMaster, 
                              byte dataLengthFromMaster, 
                              byte dataArrayFromMaster[]);

void respondAccordingly();


extern SerialSlave serialSlave;


// ------------------------------------ End ---------------------------------
#endif

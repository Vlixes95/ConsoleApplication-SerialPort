#ifndef CONSOLEAPPLICATION_SERIALPORT_ACTIONS_H
#define CONSOLEAPPLICATION_SERIALPORT_ACTIONS_H

#include "iostream"
#include "msgpack.h"

std::string ChooseAction();
void AddFileNameToMSGPackByAction( MSGPack &sendPack, const std::string &election );
void AddContentToMSGPack( MSGPack &sendPack, const std::string &election );

#endif //CONSOLEAPPLICATION_SERIALPORT_ACTIONS_H

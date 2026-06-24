#ifndef OSSM_COMMUNICATION_COMMAND_HPP
#define OSSM_COMMUNICATION_COMMAND_HPP

#include <queue>
#include "Arduino.h"
#include "NimBLECharacteristic.h"
#include "NimBLEService.h"
#include "NimBLEUUID.h"
#include "command/commands.hpp"
#include "nimble.h"
#include "queue.h"
#include "services/led.h"

/** Handler class for characteristic actions */
class CharacteristicCallbacks : public NimBLECharacteristicCallbacks {
    uint32_t lastWriteTime = 0;
    float writeHz = 0;
    const float alpha = 0.1;  // Smoothing factor for exponential moving average

    void onWrite(NimBLECharacteristic* pCharacteristic,
                 NimBLEConnInfo& connInfo) override {
        noteBleActivity(connInfo);
        std::string cmd = pCharacteristic->getValue();
        String command = String(cmd.c_str());

        if (!isValidOssmCommand(command)) {
            ESP_LOGD("NIMBLE_COMMAND", "Invalid command: %s", cmd.c_str());
            pCharacteristic->setValue("fail:" + String(cmd.c_str()));
            return;
        }
        messageQueue.push(command);

        // Trigger LED communication pulse for received command
        pulseForCommunication();
    }

    /**
     *  The value returned in code is the NimBLE host return code.
     */
    void onStatus(NimBLECharacteristic* pCharacteristic, int code) override {
        ESP_LOGV("NIMBLE_COMMAND",
                 "Notification/Indication return code: %d, %s", code,
                 NimBLEUtils::returnCodeToString(code));
    }
} inline chrCallbacks;

inline NimBLECharacteristic* initCommandCharacteristic(NimBLEService* pService,
                                                NimBLEUUID uuid) {
    // Command characteristic (writable, readable)
    NimBLECharacteristic* pChar = pService->createCharacteristic(
        uuid, NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE_NR);

    // Store the characteristic pointer globally

    pChar->setCallbacks(&chrCallbacks);

    return pChar;
}

#endif  // OSSM_COMMUNICATION_COMMAND_HPP

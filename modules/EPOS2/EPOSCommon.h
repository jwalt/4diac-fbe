#pragma once
#include <cstdint>

extern const char * initDevice(uint8_t node);
extern const char * deinitDevice(uint8_t node);

extern const char * moveToPosition(uint8_t node, float targetPosition, bool relative, float speed = 100.0f, float accel = 100.0f);
extern const char * moveWithVelocity(uint8_t node, float targetSpeed, float accel = 100.0f, float decel = 100.0f);
extern const char * stopMovement(uint8_t node);
extern const char * waitForMovementComplete(uint8_t node);
extern bool isMovementComplete(uint8_t node);
extern bool isNegLimit(uint8_t node);
extern bool isPosLimit(uint8_t node);
extern uint8_t getError(uint8_t node);
extern uint16_t getStatus(uint8_t node);
extern const char * setZero(uint8_t node);
extern const char * clearError(uint8_t node);

extern const char * getVelocity(uint8_t node, float &val);
extern const char * getPosition(uint8_t node, float &val);
extern const char * getCurrent(uint8_t node, float &val);

extern void dumpInfo(uint8_t node);
extern void dumpPos(uint8_t node);

extern void emergencyAbort();

#define handleINIT() do {                                   \
    if (var_QI) {                                           \
        auto err = initDevice(var_NODE);                    \
        if (err) {                                          \
            var_QO = CIEC_BOOL(false);                      \
            var_STATUS = CIEC_WSTRING(err);                 \
        } else {                                            \
            var_QO = CIEC_BOOL(true);                       \
            var_STATUS = CIEC_WSTRING("Initialised successfully");          \
        }                                                   \
    } else {                                                \
        if (var_QO) {                                         \
            auto err = deinitDevice(var_NODE);              \
            if (err) var_STATUS = CIEC_WSTRING(err);        \
            else var_STATUS = CIEC_WSTRING("Deinitialised successfully");   \
        }                                                   \
        var_QO = CIEC_BOOL(false);                          \
    }                                                       \
    sendOutputEvent(scmEventINITOID, paECET);               \
    } while (false)


#define handleREQ(lambda) do {                  \
    if (var_QI && var_QO) {                     \
        const char *handleREQ_err = (lambda)(); \
        if (handleREQ_err) {                    \
            var_STATUS = CIEC_WSTRING(handleREQ_err);           \
            deinitDevice(var_NODE);             \
            var_QO = CIEC_BOOL(false);          \
        }                                       \
    }                                           \
    sendOutputEvent(scmEventCNFID, paECET);     \
    } while (false)

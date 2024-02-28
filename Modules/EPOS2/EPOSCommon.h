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
    if (QI()) {                                             \
        auto err = initDevice(NODE());                      \
        if (err) {                                          \
            QO() = CIEC_BOOL(false);                        \
            STATUS() = CIEC_WSTRING(err);                    \
        } else {                                            \
            QO() = CIEC_BOOL(true);                         \
            STATUS() = CIEC_WSTRING("Initialised successfully");          \
        }                                                   \
    } else {                                                \
        if (QO()) {                                         \
            auto err = deinitDevice(NODE());                \
            if (err) STATUS() = CIEC_WSTRING(err);           \
            else STATUS() = CIEC_WSTRING("Deinitialised successfully");   \
        }                                                   \
        QO() = CIEC_BOOL(false);                            \
    }                                                       \
    sendOutputEvent(scm_nEventINITOID);                     \
    } while (false)


#define handleREQ(lambda) do {                  \
    if (QI() && QO()) {                         \
        const char *handleREQ_err = (lambda)(); \
        if (handleREQ_err) {                    \
            STATUS() = CIEC_WSTRING(handleREQ_err);           \
            deinitDevice(NODE());               \
            QO() = CIEC_BOOL(false);            \
        }                                       \
    }                                           \
    sendOutputEvent(scm_nEventCNFID);           \
    } while (false)

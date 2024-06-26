#ifdef TEST_STANDALONE

#undef LOGDEBUG
#define LOGDEBUG
#undef NOLOG

#include "EPOSCommon.h"
#include "../../forte/src/arch/devlog.h"
#include <cstdio>
#include <string>
#include <cstdarg>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <iostream>
#include "signal.h"

using namespace std;
using namespace std::chrono;


void logMessage(E_MsgLevel paLevel, const char *pacMessage, ...) {
    va_list args;
    va_start(args, pacMessage);

    fprintf(stderr, "LOG%i: ", int(paLevel));
    vfprintf(stderr, pacMessage, args);
    fflush(stderr);
    va_end(args);
}

static uint8_t node = 0;

extern "C" {
    void exit_movement() {
        emergencyAbort();
    }
    void kill_movement(int arg) {
        exit_movement();
        _Exit(arg);
    }
}

void check(const char *err) {
    if (err) {
        fprintf(stderr, "ERROR: %s\n", err);
        exit(1);
    }
}

void waitForMovement() {
    do {
        dumpPos(node);
        this_thread::sleep_for(100ms);
    } while (!isMovementComplete(node));
}

void homeMotor() {
    check(moveToPosition(node, 10000, true, 100, 1000));
    waitForMovement();
    check(clearError(node));

    while (isPosLimit(node)) {
        check(moveToPosition(node, -1, true, 10, 1000));
        waitForMovement();
    }

    check(setZero(node));

    check(moveToPosition(node, -100, true, 100, 1000));
    waitForMovement();
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 5) {
        cerr << "Usage: " << argv[0] << " <nodeid> [<pos> [<speed> [<accel>]]] | home | zero" << endl;
        exit(1);
    }
    
    signal(SIGINT, kill_movement);
    signal(SIGTERM, kill_movement);
    signal(SIGABRT, kill_movement);
    ::atexit(exit_movement);

    node = (uint8_t)stoi(argv[1]);

    check(initDevice(node));

    dumpInfo(node);
    dumpPos(node);

    if (argc > 2) {
        if (string(argv[2]) == "home") {
            homeMotor();
            exit(0);
        } else if (string(argv[2]) == "zero") {
            check(clearError(node));
            check(setZero(node));
            exit(0);
        }

        auto rel = argv[2][0] != '=';
        if (!rel) argv[2]++;
        
        auto pos = stof(argv[2]);
        auto speed = 100.0f;
        auto accel = 100.0f;

        if (argc > 3) speed = stof(argv[3]);
        if (speed < 0 || speed > 10000) {
            fprintf(stderr, "ERROR: speed is invalid\n");
            exit(1);
        }
        if (argc > 4) accel = stof(argv[4]);
        if (accel < 0 || accel > 10000) {
            fprintf(stderr, "ERROR: acceleration is invalid\n");
            exit(1);
        }
        check(moveToPosition(node, pos, rel, speed, accel));
        waitForMovement();
        dumpPos(node);
    }
}


#include "EPOSCommon.cpp"

#endif
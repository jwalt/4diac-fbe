#undef LOGDEBUG
#define LOGDEBUG
#undef NOLOG

#include "../../../forte/src/arch/devlog.h"
#include "LMS1xxCommon.h"
#include <cstdio>
#include <cstdarg>
#include <thread>
#include <chrono>
#include <cstdlib>

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

void check(const char *msg) {
    if (!msg) return;
    DEVLOG_ERROR("ERROR: %s\n", msg);
    exit(1);
}

#include <chrono>

int main(int, char *[]) {
    check(LMS1xx_init());

    auto last = steady_clock::now();
    for (;;) {
        uint16_t near = 0, far = 0;
        check(LMS1xx_fetchLatest());
        auto next = steady_clock::now();

        check(LMS1xx_measureNearest(near));
        check(LMS1xx_measureFarthest(far));

        printf("Min= %i Max= %i t= %i\n", near, far,
               (int)duration_cast<milliseconds>(next-last).count());
        last = next;
    }
}

#include "LMS1xxCommon.cpp"

#pragma once
#ifdef _WIN32
#include <windows.h>
#endif

#include IMCEA_CIO_PATH
#include IMCEA_PCIO_PATH
#define _MSC_VER 1000
#include IMCEA_IMCDRV_PATH
#include IMCEA_IMCEALIB_PATH
#undef _MSC_VER
#include IMCEA_PCIOPORT_PATH
#include IMCEA_PCIOPORTWIN32_PATH

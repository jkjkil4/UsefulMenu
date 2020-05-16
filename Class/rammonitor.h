#ifndef RAMMONITOR_H
#define RAMMONITOR_H

#include <windows.h>

__int64 Filetime2Int64(const FILETIME* ftime);
__int64 CompareFileTime(FILETIME preTime,FILETIME nowTime);

double getRAMUsage();

#endif // RAMMONITOR_H

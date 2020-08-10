#include "rammonitor.h"

__int64 Filetime2Int64(const FILETIME* ftime)
{
    LARGE_INTEGER li;
    li.LowPart = ftime->dwLowDateTime;
    li.HighPart = static_cast<LONG>( ftime->dwHighDateTime );
    return li.QuadPart;
}
__int64 CompareFileTime(FILETIME preTime,FILETIME nowTime){
    return Filetime2Int64(&nowTime) - Filetime2Int64(&preTime);
}

double getRAMUsage(){
    MEMORYSTATUSEX memory;
    memory.dwLength = sizeof(memory);
    double result=0;
    if(GlobalMemoryStatusEx(&memory)){
        int nMemFree = static_cast<int>( memory.ullAvailPhys/1024/1024 );
        int nMemTotal = static_cast<int>( memory.ullTotalPhys/1024/1024 );
        int nMemUsed= nMemTotal- nMemFree;
        result=static_cast<double>(nMemUsed)/static_cast<double>(nMemTotal);
    }
    return result;
}

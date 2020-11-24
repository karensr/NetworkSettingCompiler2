#include <iostream>
using namespace std;

#include <string.h>


int stringToUnsignedByte(char* s) {

    char* p;
    int base = 10;

    if (NULL == s || s[0] == '-')
    {
        return -1;
    }

    if (strlen(s) > 2 && memcmp(s, "0x", strlen("0x")) == 0)
    {
        s += strlen("0x");
        base = 16;
    }

    uint32_t n = strtol(s, &p, base);
    if (s == p) {
        return -1;
    }

    return ((n > 255 || n < 0) ? -1 : n);

}



#include "ConfigSettings.h"

int main(int argc, char* argv[])
{
    if (argc < 5) {
        cout << "Syntax Error: 4 arguments in range (0-255) must be provided\n";
        cout << "ex: './test.out cpuId channelId speedId profileId'\n";
        return 1;
    }
    
    int cpuId, channelId, speedId, profileId;

    cpuId = stringToUnsignedByte(argv[1]);
    channelId = stringToUnsignedByte(argv[2]);
    speedId = stringToUnsignedByte(argv[3]);
    profileId = stringToUnsignedByte(argv[4]);
    
    if (cpuId == -1 || channelId == -1 || speedId == -1 || profileId == -1) {
        cout << "Err: one or more arguments have incorrect format.\n";
        return 1;
    }

    ConfigSettings myconfig;
    settingRow const* detectedRow = myconfig.findSettings(cpuId, channelId, speedId, profileId);
    if (detectedRow == NULL) {
        cout << "config is not detected\n";
        return 1;
    }
    cout << "detected config: key = " << detectedRow->key << " setting0 = " << (int)detectedRow->setting.data[0] << " setting1 = " << (int)detectedRow->setting.data[1] << " setting2 = " << (int)detectedRow->setting.data[2] << " setting3 = " << (int)detectedRow->setting.data[3] << " setting4 = " << (int)detectedRow->setting.data[4] << " setting5 = " << (int)detectedRow->setting.data[5];
    return 0;
}

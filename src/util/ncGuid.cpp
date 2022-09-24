#include <sstream>
#include "ncGuid.h"

#define UUID_HEX_STR_SIZE 32

ncGuid::ncGuid(void)
{
    ::uuid_generate_random(_id);
}

ncGuid::~ncGuid(void)
{
}

std::string
ncGuid::ToHexString(void)
{
    std::string hexStr(UUID_HEX_STR_SIZE, 0);
    for(uint i = 0; i < UUID_HEX_STR_SIZE; i += 2) {
        sprintf(&hexStr[i], "%02x", _id[i / 2]);
    }
    return hexStr;
}
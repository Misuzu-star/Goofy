/******************************************************************************
ncGuid.h
    Copyright © 2022 Goofy Inc. All rights reserved.

Purpose:
    uuid标准字符串工具

Author:
    Miruy (miruy@foxmail.com)

Created Time:
    2022-09-18
******************************************************************************/
#ifndef __NC_GUID_H__
#define __NC_GUID_H__

#include <uuid.h>
#include <string>

class ncGuid
{
public:
    ncGuid(void);
    ~ncGuid(void);

    /**
     * 形如 00112233445566778899aabbccddeeff 
     */
    std::string ToHexString(void);

private:
    uuid_t _id;
};

#endif // !__NC_GUID_H__

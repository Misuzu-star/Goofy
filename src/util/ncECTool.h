/******************************************************************************
ncECTool.h
    Copyright © 2022 Goofy Inc. All rights reserved.

Purpose:
    

Author:
    Miruy (miruy@foxmail.com)

Created Time:
    2022-09-18
******************************************************************************/
#ifndef __NC_ECTOOL_H__
#define __NC_ECTOOL_H__

#if PRAGMA_ONCE
#pragma once
#endif

#include <vector>
#include <liberasurecode_rs_vand.h>

struct ncIniter;

class ncECTool
{
public:
    ncECTool(const int dataNum, const int parityNum);
    ~ncECTool(void);

    void SetData(const std::vector<char*>& data);
    void SetPairy(const std::vector<char*>& parity);
    void SetData(std::initializer_list<char*> data);
    void SetPairy(std::initializer_list<char*> parity);

    void Encode(int blockSize);
    void Decode(std::vector<int> missIndexs, int blockSize);

private:
    int _dataNum;               // 数据组数量
    int _parityNum;             // 冗余数据组数量
    int* _matrix;               // 范德蒙矩阵
    std::vector<char*> _data;   // 数据
    std::vector<char*> _parity; // 冗余数据
    static ncIniter _initer;    // EC算法初始化工具
};

#endif // !__NC_ECTOOL_H__

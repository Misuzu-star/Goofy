#include <stdexcept>
#include "ncECTool.h"

#define REBUILD_PARITY 1

struct ncIniter
{
    ncIniter(void) { init_liberasurecode_rs_vand(0, 0); }
    ~ncIniter(void) { deinit_liberasurecode_rs_vand(); }
};

ncIniter ncECTool::_initer;

ncECTool::ncECTool(const int dataNum, const int parityNum)
    : _dataNum(dataNum)
    , _parityNum(parityNum)
{
    _matrix = make_systematic_matrix(_dataNum, _parityNum);
}

ncECTool::~ncECTool(void)
{
    free_systematic_matrix(_matrix);
}

void
ncECTool::SetData(const std::vector<char*>& data)
{
    _data = data;
}

void
ncECTool::SetPairy(const std::vector<char*>& parity)
{
    _parity = parity;
}

void
ncECTool::SetData(std::initializer_list<char*> data)
{
    _data = data;
}

void
ncECTool::SetPairy(std::initializer_list<char*> parity)
{
    _parity = parity;
}

void
ncECTool::Encode(int blockSize)
{
    if(int(_data.size()) != _dataNum || int(_parity.size()) != _parityNum) {
        // TODO:抛异常
        throw std::logic_error("argument err");
    }

    liberasurecode_rs_vand_encode(_matrix, &_data[0], &_parity[0], _dataNum,
                                  _parityNum, blockSize);
}

void
ncECTool::Decode(std::vector<int> missIndexs, int blockSize)
{
    if(int(_data.size()) != _dataNum || int(_parity.size()) != _parityNum) {
        // TODO:抛异常
        throw std::logic_error("argument err");
    }

    missIndexs.push_back(-1);

    liberasurecode_rs_vand_decode(_matrix, &_data[0], &_parity[0], _dataNum,
                                  _parityNum, &missIndexs[0], blockSize,
                                  REBUILD_PARITY);
}

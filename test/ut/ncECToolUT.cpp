#include <iostream>
#include <gtest/gtest.h>
#include "ncECTool.h"

class ncECToolTest : public testing::Test
{
protected:
    void SetUp(void) override
    {
        std::cout << "=========== ncECToolTest SetUp ===========" << std::endl;
    }

    void TearDown(void) override
    {
        std::cout << "========== ncECToolTest TearDown =========" << std::endl;
    }
};

char*
GenericRandom(int size)
{
    char* data = (char*)malloc(size);
    for(int i = 0; i < size; ++i) {
        data[i] = rand() % 256;
    }
    return data;
}

char*
Generic(int size)
{
    char* data = (char*)malloc(size);
    return data;
}

void
Free(const std::vector<char*> data)
{
    for(size_t i = 0; i < data.size(); ++i) {
        free(data[i]);
    }
}

TEST_F(ncECToolTest, tt1)
{
    const int k = 4;
    const int m = 2;
    const int blockSize = 512;
    std::vector<char*> data(k, nullptr);
    std::vector<char*> parity(m, nullptr);

    for(int i = 0; i < k; ++i) {
        data[i] = GenericRandom(blockSize);
    }

    for(int i = 0; i < m; ++i) {
        parity[i] = Generic(blockSize);
    }

    ncECTool ecTool(k, m);
    ecTool.SetData(data);
    ecTool.SetPairy(parity);

    ecTool.Encode(blockSize);

    std::vector<char*> reserv(m, nullptr);
    for(int i = 0; i < m; ++i) {
        reserv[i] = Generic(blockSize);
    }

    std::swap(data[1], reserv[0]);
    std::swap(data[3], reserv[1]);

    ecTool.Decode({1, 3}, blockSize);

    EXPECT_EQ(0, memcmp(data[1], reserv[0], blockSize));
    EXPECT_EQ(0, memcmp(data[3], reserv[1], blockSize));
    Free(data);
    Free(parity);
    Free(reserv);
}

TEST_F(ncECToolTest, tt2)
{
    const int k = 4;
    const int m = 2;
    const int blockSize = 512;
    char* data_buf = GenericRandom(k * blockSize);
    char* parity_buf = Generic(m * blockSize);

    char* data[k];
    char* parity[m];
    for(int i = 0; i < k; ++i) {
        data[i] = data_buf + i * blockSize;
    }
    for(int i = 0; i < m; ++i) {
        parity[i] = parity_buf + i * blockSize;
    }

    ncECTool ectool(k, m);
    ectool.SetData({data[0], data[1], data[2], data[3]});
    ectool.SetPairy({parity[0], parity[1]});
    ectool.Encode(blockSize);

    char* reserv_buf = Generic(m * blockSize);
    char* reserv[m];
    for(int i = 0; i < m; ++i) {
        reserv[i] = reserv_buf + i * blockSize;
    }

    ectool.SetData({data[0], reserv[0], data[2], data[3]});
    ectool.SetPairy({parity[0], reserv[1]});
    ectool.Decode({1, 5}, blockSize);

    EXPECT_EQ(0, memcmp(data[1], reserv[0], blockSize));
    EXPECT_EQ(0, memcmp(parity[1], reserv[1], blockSize));
    free(data_buf);
    free(parity_buf);
    free(reserv_buf);
}

TEST_F(ncECToolTest, tt3)
{
    const int k = 4;
    const int m = 2;
    const int blockSize = 512;
    ncECTool ectool(k, m);

    EXPECT_THROW(ectool.Encode(blockSize), std::logic_error);
    EXPECT_THROW(ectool.Decode({}, blockSize), std::logic_error);
}

#pragma once

int Testdectype();
void TestInitList();

void CGramma_Test();

int gramma_add(int a, int b);

class CGramma
{
public:
    CGramma() = delete;
    CGramma(const CGramma& other);
    CGramma(int size);
    ~CGramma();

    CGramma& operator = (const CGramma& other);

public:
    int GetSize();

protected:
    int m_nSize;
};


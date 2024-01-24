#pragma once


namespace cpp14
{
    void StartGramma();
    void StartGramma_RRef();

    void Gramma_Lambda();

    int Testdectype();
    void TestInitList();
    int gramma_add(int a, int b);

    class CGrammaBase
    {
    public:
        virtual int& Display()& noexcept = 0;
    };

    class CGramma final : public CGrammaBase
    {
    public:
        CGramma() = delete;
        CGramma(const CGramma& other);
        CGramma(int size);
        ~CGramma();

        CGramma& operator = (const CGramma& other);

    public:
        virtual int& Display()& noexcept override { return m_nSize; }
        int GetSize() { return m_nSize; }
        int GetSizeV2()& { return m_nSize; }
        int GetSizeV3()&& { return m_nSize; }

        int GetSizeEx() const { return m_nSize; }
        int GetSizeExV2() const & { return m_nSize; }
        int GetSizeExV3() const && { return m_nSize; }

        int& GetSizeExEx() { return m_nSize; }
        int& GetSizeExExV2()& { return m_nSize; }
        int& GetSizeExExV3()&& { return m_nSize; }

        
        //int& GetSizeExExEx()const { return m_nSize; }  //err, 无法从“const int”转换为“int &”
        //int& GetSizeExExExV2()const& { return m_nSize; } //err, 无法从“const int”转换为“int &”
        //int& GetSizeExExExV3()const&& { return m_nSize; } //err, 无法从“const int”转换为“int &”

    public:

    protected:
        int m_nSize;
    };
}




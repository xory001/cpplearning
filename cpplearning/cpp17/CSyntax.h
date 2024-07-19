#pragma once


namespace cpp17
{
    class CSyntax_A
    {
    public:
        CSyntax_A() {}
        CSyntax_A( const CSyntax_A& ) = delete;
        CSyntax_A& operator=( const CSyntax_A& ) = delete;
        CSyntax_A( CSyntax_A&& ) = default;
    };

    class CSyntax_ReturnValOptimi
    {
    public:
        CSyntax_ReturnValOptimi();
        CSyntax_ReturnValOptimi( int nVal );
        CSyntax_ReturnValOptimi( const std::string& strVal );
        CSyntax_ReturnValOptimi( int nVal, const std::string& strVal );
        virtual ~CSyntax_ReturnValOptimi();

    public:
        void Display();

    protected:
        int m_nIntVal{0};
        std::string m_strVal;
    };


    class CSyntax final
    {
    public:
        CSyntax();
        ~CSyntax();

    public:
        void Start();

    protected:
        void RRef();
        void Lambda();
        void Decltype();
        CSyntax_ReturnValOptimi ReturnValueOptimization(); //RVO, vs2019 can not be closed, use it by default
    };
}




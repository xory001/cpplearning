#include "..\inc.h"
#include "CPointer.h"
#include <memory>

namespace cpp14
{
    void freePointer(CPointer* p)
    {
        delete p;
    }


    //template <typename T >
    //T Add(T x, T y)
    //{
    //    return x + y;
    //}

    //template<>
    int Add(int x, int y) { return x + y; }
	bool lengthCompare(const std::string& a, const std::string& b)
	{
		return a.length() < b.length();
	}

    bool InitPointer()
    {
        ConstPtr();
        FunctionPtr();
        StdPtr();


        return true;
    }

	bool ConstPtr()
	{
		//from right to left, right const named top-level const, left const named low-level const
		//if has one const, named top level const
		//auto will ignore top-level const
		//dectype will bring in const
		int a = 10;
		int b = 10;
		int& ra = a;
		const int& cra = a;
		const int* cpa = &a;
		//*cpa = 30;   //err, from right to left, int* defiend by const, so can't modify *cpa
		cpa = &b;      //ok. cpa not const, *cpa is const
		
		int* const pca = &a;
		*pca = 30;    //ok, pca is const, but *pca is not const
		//pca = &b;   //err, from right to left, pca defined by const, so can't modify cpa

		const int* const ccptr = &a; //can't modify ccptr by 'ccptr = ' or '*ccptr = '

		//auto

        return true;
	}

	bool FunctionPtr()
	{
		//function ptr
		{
			using TfnAdd1 = int(int, int);
			TfnAdd1* fnAdd1 = Add;
			int y1 = fnAdd1(1, 2);   //y = 3

			typedef int TfnAdd2(int, int);
			TfnAdd2* fnAdd2 = Add;
			int y2 = fnAdd2(1, 2);   //y = 3

			typedef int (*TfnAdd3)(int, int);
			TfnAdd3 fnAdd3 = Add;
			int y3 = fnAdd3(1, 2);   //y = 3

			bool lengthCompare(const std::string&, const std::string&);
			lengthCompare("a", "b");
		}
        return true;
	}

	bool StdPtr()
	{
		{
			std::shared_ptr<CPointer> pt0; // empty point

			std::shared_ptr<CPointer> pt = std::make_shared<CPointer>(1);
			std::shared_ptr<CPointer> pt10(new CPointer(10), freePointer);
		}
		std::puts("------------lamba-----------");
		{
			std::shared_ptr<CPointer> pt(new CPointer(100), [](CPointer* p) {delete p; });
		}
		std::puts("-----");
		{
			std::shared_ptr<CPointer> ptArr(new CPointer[10], std::default_delete<CPointer[]>());
			for (int i = 0; i < 10; i++)
			{
				ptArr.get()[i].SetId(i);
				ptArr.get()[i].Display();
			}
		}
		std::puts("-----unique_ptr-------");
		{
			std::unique_ptr<CPointer> pt(new CPointer(100));
			std::unique_ptr<CPointer, void (*)(CPointer*)>  pt1(new CPointer(10), freePointer);
			std::unique_ptr<CPointer, decltype(freePointer)*>  pt2(new CPointer(10), freePointer);
			CFreePointer fp;
			std::unique_ptr<CPointer, CFreePointer>  pt3(new CPointer(10), fp);
			//std::unique_ptr<CPointer, CFreePointer>  pt3(fp); //err syntax
		}
		{
			//type convert
			CPointer pt1;
			if (pt1)
			{
				pt1.Display();
			}
		}
        return true;
	}

	CPointer::CPointer(INT64 id)
    {
        m_llId = id;
        m_nPointerType = 0;
        m_nX = 0;
        m_nY = 0;
        TRACE_INFO_THIS("m_llId = " << m_llId);
    }

    CPointer::~CPointer()
    {
        TRACE_INFO_THIS("m_llId = " << m_llId);
    }



    void CPointer::Display()
    {
        std::ostringstream oss;
        oss << "id = " << m_llId <<  ", ( " << m_nX << ", " << m_nY << " )\n";
        std::cout << oss.str();
    }

    std::string CPointer::ToString()
    {
        std::ostringstream oss;
        oss << "( " << m_nX << ", " << m_nY << " )";
        return oss.str();
    }

    void CFreePointer::operator()(CPointer* ppt)
    {
        delete ppt;
    }

    CPointerEx::CPointerEx()
    {
        m_nPointerExType = 0;
        TRACE_INFO_THIS("m_nPointerExType = " << m_nPointerExType);
    }

    CPointerEx::~CPointerEx()
    {
        TRACE_INFO_THIS("m_nPointerExType = " << m_nPointerExType);
    }



}
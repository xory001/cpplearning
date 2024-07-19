#pragma once

namespace cpp17
{

	bool InitPointer();
	bool ConstPtr();
	bool FunctionPtr();
	bool StdPtr();


	class CPointer
	{
	public:
		CPointer() :CPointer(0) {}
		CPointer( INT64 id );
		virtual ~CPointer();

	public:
		void SetId(INT64 id) { m_llId = id; }
		INT64 GetId() { return m_llId; };
		void Set(int x, int y) { m_nX = x; m_nY = y; }
		bool Get(int& x, int& y) { x = m_nX; y = m_nY; }
		void Display();
		std::string ToString();

	public:
		operator bool() { return 0 != m_llId; }

	protected:
		INT64 m_llId;
		int m_nPointerType;
		int m_nX;
		int m_nY;
	};

	class CFreePointer
	{
	public:
		void operator()(CPointer* ppt);
	};


	class CPointerEx : public CPointer
	{
	public:
		CPointerEx();
		virtual ~CPointerEx();

	protected:
		int m_nPointerExType;

	};

}

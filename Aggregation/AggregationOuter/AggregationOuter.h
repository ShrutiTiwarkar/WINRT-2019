#include<Windows.h>

class ISum :public IUnknown {
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
};

class ISubtract :public IUnknown {
public:
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};


const CLSID CLSID_SumSubtract = { 0xc870fdaa, 0x19df, 0x461f, 0x9c, 0x8e, 0x87, 0x18, 0x55, 0xec, 0xc0, 0xca };

const IID IID_ISum = { 0x8f76c277, 0xcbc8, 0x45a4, 0xa3, 0x18, 0x4e, 0x86, 0x98, 0xb1, 0xb3, 0xe8 };

const IID IID_ISubtract = { 0x9a96f0d2, 0x412d, 0x4714, 0x93, 0xfd, 0x60, 0xd2, 0x55, 0x8f, 0xe, 0x75 };


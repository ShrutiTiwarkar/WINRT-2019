#pragma once
#include<Windows.h>

class IMyMath : public IDispatch
{
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0; //pure virtual
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0; //pure virtual
};

const CLSID CLSID_MyMath = { 0x315077a3, 0xbaca, 0x4b3a, 0xa7, 0x3, 0xa3, 0x7c, 0x53, 0xf5, 0x3b, 0xe5 };

const IID IID_IMyMath = { 0xca61e6d3, 0x1532, 0x4875, 0x80, 0x57, 0x91, 0x5e, 0x6d, 0xe7, 0xf6, 0x76 };


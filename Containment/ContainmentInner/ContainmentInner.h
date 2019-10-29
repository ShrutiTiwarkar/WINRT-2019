#include<Windows.h>

class IMultiplication :public IUnknown {
public:
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;
};

class IDivision :public IUnknown {
public:
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;
};

//Guid.txt

const CLSID CLSID_IMultiplicationDivision = { 0x9da6bed5, 0xaa68, 0x48ad, 0x80, 0xff, 0x14, 0xfe, 0xaa, 0x1f, 0x7b, 0xe8 };

const IID IID_IMultiplication = { 0x61de4561, 0xeca, 0x452f, 0x93, 0x16, 0x66, 0x7b, 0x82, 0x86, 0xdd, 0xf3 };

const IID IID_IDivision = { 0xcb486389, 0xd3b8, 0x418e, 0x93, 0xed, 0xfe, 0xe5, 0x65, 0x41, 0x28, 0x85 };
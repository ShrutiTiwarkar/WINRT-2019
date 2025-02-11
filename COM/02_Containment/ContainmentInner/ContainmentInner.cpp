#include<windows.h>

#include "ContainmentInner.h"

class CMultiplicationDivision :public IMultiplication, IDivision {
private:
	long m_cRef;
public:
	CMultiplicationDivision(void);
	~CMultiplicationDivision(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);

};

class CMultiplicationDivisionClassFactory :public IClassFactory {
private:
	long m_cRef;
public:
	CMultiplicationDivisionClassFactory(void);
	~CMultiplicationDivisionClassFactory(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);

};

long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved) {
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}

	return(TRUE);

}


CMultiplicationDivision::CMultiplicationDivision(void) {

	m_cRef = 1;

	InterlockedIncrement(&glNumberOfActiveComponents);

}
CMultiplicationDivision::~CMultiplicationDivision(void) {


	InterlockedDecrement(&glNumberOfActiveComponents);

}

HRESULT CMultiplicationDivision::QueryInterface(REFIID riid, void **ppv) {


	if (riid == IID_IUnknown) {
		*ppv = static_cast<IMultiplication *>(this);
	}
	else if (riid == IID_IMultiplication) {
		*ppv = static_cast<IMultiplication *>(this);
	}
	else if (riid == IID_IDivision) {
		*ppv = static_cast<IDivision *>(this);
	}
	else {
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();


	return(S_OK);
}

ULONG CMultiplicationDivision::AddRef(void) {


	InterlockedIncrement(&m_cRef);

	return(S_OK);
}

ULONG CMultiplicationDivision::Release(void) {


	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0) {
		delete(this);
		return(0);

	}
	return(m_cRef);
}

HRESULT CMultiplicationDivision::MultiplicationOfTwoIntegers(int num1, int num2, int* pMultiplication) {


	*pMultiplication = num1 * num2;


	return(S_OK);

}

HRESULT CMultiplicationDivision::DivisionOfTwoIntegers(int num1, int num2, int* pDivision) {

	*pDivision = num1 / num2;


	return(S_OK);
}


CMultiplicationDivisionClassFactory::CMultiplicationDivisionClassFactory(void) {

	m_cRef = 1;

}

CMultiplicationDivisionClassFactory::~CMultiplicationDivisionClassFactory(void) {


}

HRESULT CMultiplicationDivisionClassFactory::QueryInterface(REFIID riid, void **ppv) {

	if (riid == IID_IUnknown) {
		*ppv = static_cast<IClassFactory *>(this);
	}
	else if (riid == IID_IClassFactory) {
		*ppv = static_cast<IClassFactory *>(this);
	}
	else {

		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CMultiplicationDivisionClassFactory::AddRef(void) {
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CMultiplicationDivisionClassFactory::Release(void) {
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return(0);
	}
	return(m_cRef);

}

HRESULT CMultiplicationDivisionClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void **ppv) {

	CMultiplicationDivision *pCMultiplicationDivision = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL) {
		return(CLASS_E_NOAGGREGATION);
	}
	pCMultiplicationDivision = new CMultiplicationDivision;

	hr = pCMultiplicationDivision->QueryInterface(riid, ppv);
	pCMultiplicationDivision->Release();
	return(hr);
}

HRESULT CMultiplicationDivisionClassFactory::LockServer(BOOL fLock) {

	if (fLock) {
		InterlockedIncrement(&glNumberOfServerLocks);
	}
	else {
		InterlockedDecrement(&glNumberOfServerLocks);
	}

	return(S_OK);
}


extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv) {


	CMultiplicationDivisionClassFactory *pCMultiplicationDivisionClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_IMultiplicationDivision) {
		return(CLASS_E_CLASSNOTAVAILABLE);
	}

	pCMultiplicationDivisionClassFactory = new CMultiplicationDivisionClassFactory;
	hr = pCMultiplicationDivisionClassFactory->QueryInterface(riid, ppv);
	pCMultiplicationDivisionClassFactory->Release();


	return(hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void) {
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0)) {
		return(S_OK);
	}
	else {
		return(S_FALSE);
	}
}


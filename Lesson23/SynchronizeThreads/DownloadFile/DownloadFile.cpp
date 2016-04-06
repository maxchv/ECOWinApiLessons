// DownloadFile.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <urlmon.h>

#pragma comment(lib, "urlmon")

class DownloadProgess: public IBindStatusCallback 
{
public:
    virtual HRESULT STDMETHODCALLTYPE OnStartBinding(
        /* [in] */ DWORD dwReserved,
        /* [in] */ __RPC__in_opt IBinding *pib)

    {
        return E_NOTIMPL;
    }

    virtual HRESULT STDMETHODCALLTYPE GetPriority(
        /* [out] */ __RPC__out LONG *pnPriority)
    {		
        return E_NOTIMPL;		
    }

    virtual HRESULT STDMETHODCALLTYPE OnLowResource(
        /* [in] */ DWORD reserved) 
    {
        return E_NOTIMPL;
    }

    virtual HRESULT STDMETHODCALLTYPE OnProgress(
        /* [in] */ ULONG ulProgress,
        /* [in] */ ULONG ulProgressMax,
        /* [in] */ ULONG ulStatusCode,
        /* [unique][in] */ __RPC__in_opt LPCWSTR szStatusText)
    {
        _tprintf(TEXT("%ld/%ld status: %ld\n"), ulProgress, ulProgressMax, ulStatusCode);
		if (ulStatusCode == 5)
		{
			return E_ABORT;
		}
        if (szStatusText)
        {
            _tprintf(TEXT("status: %s\n"), szStatusText);
        }
        return S_OK;
    }

    virtual HRESULT STDMETHODCALLTYPE OnStopBinding(
        /* [in] */ HRESULT hresult,
        /* [unique][in] */ __RPC__in_opt LPCWSTR szError)
    {
        return E_NOTIMPL;
    }

    virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetBindInfo(
        /* [out] */ DWORD *grfBINDF,
        /* [unique][out][in] */ BINDINFO *pbindinfo) 
    {
        return E_NOTIMPL;
    }

    virtual /* [local] */ HRESULT STDMETHODCALLTYPE OnDataAvailable(
        /* [in] */ DWORD grfBSCF,
        /* [in] */ DWORD dwSize,
        /* [in] */ FORMATETC *pformatetc,
        /* [in] */ STGMEDIUM *pstgmed) 
    {
        return E_NOTIMPL;
    }

    virtual HRESULT STDMETHODCALLTYPE OnObjectAvailable(
        /* [in] */ __RPC__in REFIID riid,
        /* [iid_is][in] */ __RPC__in_opt IUnknown *punk) 
    {
        return E_NOTIMPL;
    }

    virtual HRESULT STDMETHODCALLTYPE QueryInterface(
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR *__RPC_FAR *ppvObject)
    {
        return E_NOTIMPL;
    }

    virtual ULONG STDMETHODCALLTYPE AddRef(void)
    {
        return E_NOTIMPL;
    }

    virtual ULONG STDMETHODCALLTYPE Release(void)
    {
        return E_NOTIMPL;
    }
};

int main()
{
    TCHAR *url = TEXT("http://www.ex.ua/get/236826899");	
    TCHAR *local_file = TEXT("video.avi");
    DownloadProgess progress;
    IBindStatusCallback *callback = &progress;
    if (URLDownloadToFile(NULL, url, local_file, 0, callback) == S_OK)
    {
        system("video.avi");
    }

    return 0;
}


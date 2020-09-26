#include "pch.h"
#include "CHttpClient.h"

int main()
{
	winrt::init_apartment();

	http_context	dctx;
	CHttpClient		httpclient;

	dctx.urls.push_back(L"https://releases.ubuntu.com/18.04.5/ubuntu-18.04.5-desktop-amd64.iso");
	dctx.out = L"c:\\temp\\";
	httpclient.Notidownload(dctx).get();
}

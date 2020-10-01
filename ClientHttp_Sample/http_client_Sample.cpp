#include "pch.h"
#include "http_client.h"

int main()
{
	winrt::init_apartment();

	http_context	context;
	http_client		httpclient;

	context.urls.push_back(L"https://releases.ubuntu.com/18.04.5/ubuntu-18.04.5-desktop-amd64.iso");
	context.out = L"c:\\temp\\";
	httpclient.getfile(context).get();

}

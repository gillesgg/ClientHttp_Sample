// ClientHttp_Sample.cpp : This file contains the 'main' function. Program execution begins and ends there.
//https://github.com/pedropbazzo/React-Native-for-Windows/blob/c03226884d248fd4f6592931b917bd92bac068a3/vnext/ReactUWP/Modules/DevSupportManagerUwp.cpp

#include "pch.h"
#include <iostream>
#include "CHttpClient.h"

using CallbackFunc = std::function<void(void)>;


class Test
{
public:
	void RunAsync(CallbackFunc callback)
	{

	}
};








int main()
{

	
	/*Test test;
	std::function< void() > callback = std::bind(&Test::RunAsync, test);*/

	winrt::init_apartment();


	Dcontext dctx;

	dctx.urls.push_back(L"https://releases.ubuntu.com/18.04.5/ubuntu-18.04.5-desktop-amd64.iso");
	dctx.out = L"c:\\temp\\";
	Notidownload(dctx).get();


	
	// Works fine.
	//auto uri = Windows::Foundation::Uri(L"https://www.example.com");

	/*winrt::Windows::Web::Http::Filters::HttpBaseProtocolFilter filter;
	winrt::Windows::Web::Http::HttpClient httpClient(filter);
	winrt::Windows::Web::Http::HttpRequestMessage request;


	auto res = httpClient.GetAsync(winrt::Windows::Foundation::Uri(L"http://msdn.microsoft.com")).get();*/


	


	//Microsoft::WRL::ComPtr< winrt::Windows::Web::Http::Filters::HttpBaseProtocolFilter> filter;

	//Microsoft::WRL::ComPtr< winrt::Windows::Web::Http::HttpClient> client(filter);



	//auto requestmessage = PrepareRequestMessage();
	//HttpBaseProtocolFilter^ filter = ref new HttpBaseProtocolFilter();
	////  filter->AllowAutoRedirect = false;
	//HttpClient^ client = ref new HttpClient(filter);

	//Microsoft::WRL::ComPtr< ABI::Windows::Web::Http::IHttpClientFactory> httpClientFactory;


	
}

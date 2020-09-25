#pragma once


class CHttpClient
{
public:
	CHttpClient();

	//std::future<void> download(const winrt::Windows::Foundation::Uri& url, const std::wstring& dstFilePath, const std::function<void(float)>& progressUpdateCallback);
	//std::future<void> download(const winrt::Windows::Foundation::Uri& url, const std::wstring& dstFilePath);
	
	std::future<void> download(const wchar_t* url, const wchar_t* savefile);

	
private:
	winrt::Windows::Web::Http::HttpClient m_client;
};

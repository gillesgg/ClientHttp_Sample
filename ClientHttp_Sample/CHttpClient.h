#pragma once

class uri_exception : public std::exception
{
public:
	uri_exception(std::string msg) : m_msg(std::move(msg)) {}

	~uri_exception() noexcept {}

	const char* what() const noexcept { return m_msg.c_str(); }

private:
	std::string m_msg;
};

class CHttpClient
{
public:
	CHttpClient();
	IAsyncAction DownloadFile(const wchar_t* url, const wchar_t* outfolder, const http_context& dctx);
	IAsyncAction Notidownload(const http_context& dctx);
	//std::future<void> download(const winrt::Windows::Foundation::Uri& url, const std::wstring& dstFilePath, const std::function<void(float)>& progressUpdateCallback);
	//std::future<void> download(const winrt::Windows::Foundation::Uri& url, const std::wstring& dstFilePath);
	
	//std::future<void> download(const wchar_t* url, const wchar_t* savefile);


private:
	static void validate_uri(std::wstring uri_string);
	static std::wstring pathfilename(const wchar_t* begin, const wchar_t* end);
	std::wstring get_outfolder(std::wstring str_outfolder);

private:
	winrt::Windows::Web::Http::HttpClient m_client;
};

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

class http_client_config
{

};

class http_client
{
public:
	http_client();
	IAsyncAction DownloadFile(const wchar_t* url, const wchar_t* outfolder, const http_context& dctx);
	IAsyncAction getfile(const http_context& dctx);


private:
	static void validate_uri(std::wstring uri_string);
	static std::wstring pathfilename(const wchar_t* begin, const wchar_t* end);
	std::wstring get_outfolder(std::wstring str_outfolder);
	//void authenticate(winrt::Windows::Web::Http::HttpResponseMessage resp);

private:
	winrt::Windows::Web::Http::HttpClient						m_client;
	winrt::Windows::Web::Http::Filters::HttpBaseProtocolFilter	m_baseFilter;

};

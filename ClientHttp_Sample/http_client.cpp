#include "pch.h"
#include "http_client.h"


using namespace winrt;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Web;
using namespace winrt::Windows::Web::Http;
using namespace winrt::Windows::Web::Http::Headers;
using namespace winrt::Windows::Web::Http::Filters;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Streams;
using namespace winrt::Windows::Foundation::Collections;

http_client::http_client() 
{
}

void http_client::validate_uri(std::wstring uri_string)
{
    // TODO validate url

    /*USES_CONVERSION;

    if (!validate_uri(uri_string))
    {
        throw uri_exception("provided uri is invalid: " + std::string(W2A(uri_string.c_str())));
    }*/
}

std::wstring http_client::pathfilename(const wchar_t* begin, const wchar_t* end) 
{
    if (begin == end) {
        return std::wstring(L"index.html");
    }
    std::wstring filename(begin, end - begin);
    while (!filename.empty() && filename.back() == '/') {
        filename.pop_back();
    }
    if (filename.empty()) {
        return std::wstring(L"index.html");
    }
    auto pos = filename.rfind('/');
    if (pos != std::wstring::npos) {
        return filename.substr(pos + 1);
    }
    return filename;
}

std::wstring http_client::get_outfolder(std::wstring str_outfolder)
{
    std::wstring fulldir, filename;

    if (!str_outfolder.empty())
    {
        auto p = std::filesystem::path(str_outfolder);
        auto pdir = std::filesystem::path(str_outfolder).parent_path();
        if (!std::filesystem::exists(pdir))
        {
            std::error_code ec;
            if (!std::filesystem::create_directories(pdir, ec))
            {
                throw std::filesystem::filesystem_error("unable to create the foler, name: ", ec);
            }
        }
        fulldir = pdir.wstring();
        if (p.has_filename()) {
            filename = p.filename().wstring();
        }
    }
    else {
        fulldir = std::filesystem::current_path().wstring();
    }
    return fulldir;
}


void http_client::authenticate(HttpResponseMessage resp)
{

    ATLTRACE("Authenticate Status code=%d", resp.StatusCode());

    if (!resp.IsSuccessStatusCode() && resp.StatusCode() == HttpStatusCode::ProxyAuthenticationRequired)
    {

    }

    if (!resp.IsSuccessStatusCode() && resp.StatusCode() == HttpStatusCode::Unauthorized)
    {
        IVectorView<HttpChallengeHeaderValue> blaa = resp.Headers().WwwAuthenticate().GetView();

        for (auto const& authchalenge : resp.Headers().WwwAuthenticate().GetView())
        {
            auto sc = authchalenge.Scheme();
        }       
    }
}

IAsyncAction http_client::DownloadFile(const wchar_t* url, const wchar_t* outfolder, const http_context& context)
{
    try 
    {
        auto fulldir = get_outfolder(outfolder);
        std::wstring filename;

        ATLTRACE("download url: %ls %ls\n", url, fulldir.c_str());

        HttpBaseProtocolFilter baseFilter;
        baseFilter.AllowAutoRedirect(false);
        baseFilter.AllowUI(true);

        ATLTRACE("HTTP version: %d\n",baseFilter.MaxVersion());

       
        m_client.DefaultRequestHeaders().Append(
            L"User-Agent", L"IE/5.0 (Windows NT 10.0; Win64; x64)");
        
        Uri uri(url);

        m_client.GetAsync(uri, HttpCompletionOption::ResponseHeadersRead);

        auto resp = co_await m_client.GetAsync(uri, HttpCompletionOption::ResponseHeadersRead); /// Only read header.
        int times = 0;
        while ((resp.StatusCode() == HttpStatusCode::Found || resp.StatusCode() == HttpStatusCode::MovedPermanently || resp.StatusCode() == HttpStatusCode::TemporaryRedirect) && (times <= context.tries))
        {
            auto location = resp.Headers().Location();
            ATLTRACE("Redirect to %ls\n", location.AbsoluteUri().c_str());
            resp = co_await m_client.GetAsync(location, HttpCompletionOption::ResponseHeadersRead);
            times++;
        }
        
        if (!resp.IsSuccessStatusCode()) 
        {            
            authenticate(resp);
            co_return;
        }

        if (resp.Version() == HttpVersion::Http20) {
            ATLTRACE("HTTP 2.0\n");
        }

        if (filename.empty() && resp.Content().Headers().ContentDisposition()) 
        {
            if (!resp.Content().Headers().ContentDisposition().FileName().empty()) 
            {
                filename.assign(resp.Content().Headers().ContentDisposition().FileName().c_str());
                ATLTRACE("use filename %ls\n", filename.c_str());
            }
        }

        if (filename.empty())
        {
            filename = pathfilename(uri.Path().c_str(), uri.Path().c_str() + uri.Path().size());
            ATLTRACE("filename: %ls\n", filename.c_str());
        }

        uint64_t blen = 0;
        if (resp.Content().TryComputeLength(blen)) 
        {
            ATLTRACE("content len=%" PRId64 "\n", blen);
        }
        /// If cannot download some dir,
        auto folder = co_await StorageFolder::GetFolderFromPathAsync(fulldir); /// Must fullpath
        auto file = co_await folder.CreateFileAsync(filename,CreationCollisionOption::ReplaceExisting); /// replace existing
        auto stream = co_await file.OpenAsync(FileAccessMode::ReadWrite);
        // HttpProgress

        auto task = resp.Content().WriteToStreamAsync(stream);
        task.Progress([](const IAsyncOperationWithProgress<uint64_t, uint64_t>&,const uint64_t& pb) 
        {            
                ATLTRACE(L"download %llu\n", pb);
        });
        auto result = co_await task;
        ATLTRACE(L"total %llu\n", result);
    }
    catch (const hresult_error& e) 
    {
        ATLTRACE("download error: 0x%08x %ls\n", e.code().value, e.message().c_str());
    }
    catch (const std::exception& e) 
    {
        ATLTRACE("download url: %s\n", e.what());
    }  
}

IAsyncAction http_client::getfile(const http_context& dctx)
{
    try
    {
        co_await DownloadFile(dctx.urls[0].c_str(), dctx.out.c_str(), dctx);
    }
    catch (const hresult_error& e)
    {
        ATLTRACE("open dir: %ls\n", e.message().c_str());
    }
    catch (const std::exception& e)
    {
        ATLTRACE("open dir: %s\n", e.what());
    }
}

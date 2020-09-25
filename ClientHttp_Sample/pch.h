// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// wrl support
#include <wrl.h>
#include <wrl/client.h>


#include "winrt/base.h"
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Web.Http.Filters.h>
#include <winrt/Windows.Web.Http.Headers.h>
#include <winrt/Windows.Web.Http.h>
#include <winrt/Windows.Security.Credentials.UI.h>
#include <winrt/Windows.Networking.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.UI.Popups.h>

#include <wincred.h>

#include <future>
#include <memory>
#include <sstream>

// std

#include <atomic>
#include <condition_variable>
#include <ppltasks.h>
#include <concurrent_queue.h>
#include <filesystem>
#include <inttypes.h>

struct Dcontext {
	std::vector<std::wstring> urls;
	std::wstring out;
	int tries{ 5 };
	int location{ 3 };
	bool disposition{ true };
	bool verbose{ false };
};

using winrt::Windows::Foundation::IAsyncAction;

IAsyncAction Notidownload(const Dcontext& dctx);

#endif //PCH_H

#ifndef __SAMPLE_WEB_EXTENSION_
#define __SAMPLE_WEB_EXTENSION_

#include <gio/gio.h>

#include <JavaScriptCore/JSContextRef.h>
#include <jsc/jsc.h>

#ifdef PLATFORM_GTK
#include <webkit2/webkit-web-extension.h>
#elif defined(PLATFORM_WPE)
#include <wpe/webkit-web-extension.h>
#endif

#endif /* __SAMPLE_WEB_EXTENSION_ */

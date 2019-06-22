/*
 *  Copyright 2019, Munez Bokkapatna Nayakwady <munezbn.dev@gmail.com>, All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *  Author(s)        : Munez BN <munezbn.dev@gmail.com>
 *  File             : WebExtension.cpp
 *  Description      : Web Extension for WebKit 
 *
 */ 

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#include "sample_web_extension.h"

using namespace std;

static GFile*
createGFile(const char* path, gpointer usr_data)
{
    GFile* file = nullptr;
    if(path)
        file = g_file_new_for_path(path);
    return file;
}

static char*
getGFilePath(GFile* file, gpointer usr_data)
{
    char *path = nullptr;
    if(file && G_IS_FILE(file))
        path = g_file_get_path(file);
    return path;
}

static JSCValue*
createWrappedGFile(char *path, gpointer usr_data)
{
    auto* jscContext = jsc_context_get_current();

    JSCValue* ret =  jsc_value_new_undefined(jscContext);
    GFile* file = createGFile(path, nullptr);
    JSCClass* js_class = (JSCClass*) usr_data;

    if(file && js_class)
        ret = jsc_value_new_object (jscContext, file, js_class);
    return ret;
}

static void 
window_object_cleared_callback (WebKitScriptWorld *world, 
                                WebKitWebPage     *web_page, 
                                WebKitFrame       *frame, 
                                gpointer           user_data)
{
	g_autoptr(JSCContext) jscContext = NULL;

    jscContext = webkit_frame_get_js_context_for_script_world(frame, world);
    g_assert_true(JSC_IS_CONTEXT(jscContext));
    
    /* Register a JSC class named GFile */
    JSCClass* jscClass = jsc_context_register_class(jscContext, "GFile", nullptr, nullptr, reinterpret_cast<GDestroyNotify>(g_object_unref));
    jsc_class_add_method(jscClass, "getPath", G_CALLBACK(getGFilePath), nullptr, nullptr, G_TYPE_STRING, 0, G_TYPE_NONE);

    /* Method 1 : Wrap  GFile Object using constructor */
    JSCValue* constructor = jsc_class_add_constructor(jscClass, nullptr, G_CALLBACK(createGFile), nullptr, nullptr, G_TYPE_OBJECT, 1, G_TYPE_STRING);
    jsc_context_set_value(jscContext, jsc_class_get_name(jscClass), constructor);

    /* Method 2 : Wrap  GFile Object without constructor */
    g_autoptr(JSCValue) function = jsc_value_new_function(jscContext, "getGfileObject", G_CALLBACK(createWrappedGFile), jscClass, nullptr, JSC_TYPE_VALUE, 1, G_TYPE_STRING);
    jsc_context_set_value(jscContext, "getGfileObject", function);
}

/**
 * WebKit Web Extension Initialize API implementation.
 */
extern "C" void
webkit_web_extension_initialize(WebKitWebExtension* extension)
{
    g_signal_connect (webkit_script_world_get_default (),
                        "window-object-cleared",
                        G_CALLBACK (window_object_cleared_callback),
                        NULL);
    return;
}

/**
 * WebKit Web Extension Initialize with user data API implementation.
 */
extern "C" void
webkit_web_extension_initialize_with_user_data(WebKitWebExtension *extension,
                                                               const GVariant     *user_data)
{
	g_signal_connect (webkit_script_world_get_default (),
                        "window-object-cleared",
                        G_CALLBACK (window_object_cleared_callback),
                        (gpointer)user_data);
    return;
}


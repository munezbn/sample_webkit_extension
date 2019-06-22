# sample_webkit_extension
Sample Web Extension for Webkit [ GTK &amp; WPE ] based on JSC GLib API <br />

## Build Options
webkit_port : wpe or gtk <br /> 
extension_path : Relative path to webkit libdir, where the extension will be installed  <br /> 

## Build commands

meson -Dwebkit_port='gtk' -Dextension_path=webkit/web-extensions builddir  <br /> 
ninja -C builddir/  <br /> 
sudo ninja -C builddir install <br /> 

NOTE: In case if webkit is installed to a custom location configure with PKG_CONFIG_PATH=<package config path of webkit> <br /> 
Example<br /> 
PKG_CONFIG_PATH=/usr/local/lib64/pkgconfig/ meson -Dwebkit_port='gtk' -Dextension_path=webkit/web-extensions builddir <br /> 

## Testing
In the browser make sure you connect to web-extension signal, and in signal handler make sure to set extenstion directory and call extension initialize.<br />
You can use html/sample_web_extension.html as reference<br />

#define WEB_EXTENSIONS_DIRECTORY "/usr/local/lib64/webkit/web-extensions/"<br /> 

static void initialize_web_extensions (WebKitWebContext *context, gpointer user_data)<br /> 
{<br /> 
  // Web Extensions get a different ID for each Web Process <br /> 
  static guint32 unique_id = 0;<br /> 

  webkit_web_context_set_web_extensions_directory ( context, WEB_EXTENSIONS_DIRECTORY);<br /> 
  webkit_web_context_set_web_extensions_initialization_user_data (context, g_variant_new_uint32 (unique_id++));<br /> 
}<br /> 

g_signal_connect (webContext, "initialize-web-extensions", G_CALLBACK (initialize_web_extensions), NULL);<br /> 

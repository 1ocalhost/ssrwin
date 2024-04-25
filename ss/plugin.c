#include <stdint.h>  // keep it before plugin.h
#include "plugin.h"

int start_plugin(const char *plugin,
                 const char *plugin_opts,
                 const char *remote_host,
                 const char *remote_port,
                 const char *local_host,
                 const char *local_port,
#ifdef __MINGW32__
                 uint16_t control_port,
#endif
                 enum plugin_mode mode)
{
}

uint16_t get_local_port()
{
    return 0;
}

void stop_plugin()
{

}


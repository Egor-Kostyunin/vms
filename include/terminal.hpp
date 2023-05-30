#ifndef TERMINAL_HPP
#define TERMINAL_HPP
#include "plugin.hpp"

namespace treminal{
        extern "C" {
        plugin_api::function_info* plugin_export(unsigned short int *count);
	plugin_api::PluginError exec_cmd(plugin_api::pfarg *ret,plugin_api::pfarg *arg);
	}
};
#endif

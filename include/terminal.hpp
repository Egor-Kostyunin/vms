#ifndef TERMINAL_HPP
#define TERMINAL_HPP
#include "plugin.hpp"

namespace terminal{
	extern "C" {
		char** plugin_export(unsigned short int *count);
		plugin_api::PluginError exec_cmd(plugin_api::pfarg *ret,plugin_api::pfarg *arg);
	}
};
#endif

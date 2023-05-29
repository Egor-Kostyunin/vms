#ifndef TERMINAL_HPP
#define TERMINAL_HPP
#include "plugin.hpp"

namespace treminal{
	plugin_api::PluginError start_cmd_server(plugin_api::pfarg *ret,plugin_api::pfarg *arg);
	plugin_api::PluginError post_cmd(plugin_api::pfarg *ret,plugin_api::pfarg *arg);
	plugin_api::PluginError exec_cmd(plugin_api::pfarg *ret,plugin_api::pfarg *arg);
};
#endif
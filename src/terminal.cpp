#include "terminal.hpp"

namespace treminal{
	plugin_api::PluginError start_cmd_server(plugin_api::pfarg *ret,plugin_api::pfarg *arg){
		return plugin_api::PluginError::Saccess;
	}
	plugin_api::PluginError post_cmd(plugin_api::pfarg *ret,plugin_api::pfarg *arg){
		return plugin_api::PluginError::Saccess;
	}
	plugin_api::PluginError exec_cmd(plugin_api::pfarg *ret,plugin_api::pfarg *arg){
		return plugin_api::PluginError::Saccess;
	}
};
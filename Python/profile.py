import xml.etree.ElementTree as ET
from cmd_tree import CMDTreeNode

class ProfileParser:
	def __init__(self,profile):
		self.name = profile
		self.root_node = ET.parse('./Profiles/'+profile+'.xml').getroot()
		self.plugins = self.GetPluginList()
		pass
	def GetPluginList(self):
		for plugin in self.root_node.findall('req/plugin'):
			yield plugin.attrib('name')
	def NextPlugin(self):
		return next(self.plugins,"END PLUGINS")
	def GetCommadTree(self):
		for command in self.root_node.findall('cmd/command'):
			
import xml.etree.ElementTree as ET
from bigtree import dict_to_tree,print_tree

class ProfileParser:
	def __init__(self,profile):
		self.name = profile
		self.root_node = ET.parse('./Profiles/'+profile+'.xml').getroot()
		pass
	def GetPluginList(self):
		pass
	def GetCommandTree(self):
		command_tree = {}
		for command in self.root_node.findall('cmd/command'):
			command_tree[self.name+'/'+command.attrib['name'].replace(' ','/')] =  {'function' : command.attrib['function']}
		print(command_tree)
		command_tree = dict_to_tree(command_tree)
		return command_tree
pp = ProfileParser('терминал')
print_tree(pp.GetCommandTree(),attr_list=['function'])


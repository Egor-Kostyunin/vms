import xml.etree.ElementTree as ET

class Profile:
	def __init__(self,profile):
		print('./Profiles/'+profile+'.xml')
		self.name = profile
		self.root_node = ET.parse('./Profiles/'+profile+'.xml').getroot()
		self.cmd_list = {}
		for tag in self.root_node.findall('req/plugin'):
			value = tag.attrib['name'] 
			print(value)
		self.onopenaction = self.root_node.findall('onopenacton')[0].attrib['function']
		for tag in self.root_node.findall('cmd/command'):
			self.cmd_list[tag.attrib['name']] = tag.attrib['function'] 
		pass
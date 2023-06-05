from fuzzywuzzy import fuzz
CMDNotFull = 'command not full'
class CMDTreeNode:
	def __init__(self,name,cmd = None,child = None,next = None):
		if type(name) is not str:
			raise ValueError("Node name argument value is not str.")
		self.nodeName = name
		if type(cmd) is not str and cmd is not None:
			raise ValueError("Command name argument value is not str.")
		self.cmdName = cmd
		if type(child) is not CMDTreeNode and child is not None:
			raise ValueError("Child node argument value is not CMDTreeNode.")
		self.child = child
		if type(next) is not CMDTreeNode and next is not None:
			raise ValueError("Next node argument value is not CMDTreeNode.")
		self.next = next
		pass
	def SetChild(self,child):
		if type(child) is not CMDTreeNode and child is not None:
			raise ValueError("Child node argument value is not CMDTreeNode.")
		self.child = child
		pass
	def SetNext(self,next):
		if type(next) is not CMDTreeNode and next is not None:
			raise ValueError("Next node argument value is not CMDTreeNode.")
		self.next = next
		pass
	def SetBrunch(self,brunch_str,cmd,level = 0):
		if level < len(brunch_str):
			if self.child is None:
				self.SetChild(CMDTreeNode(brunch_str[level]))
			current = self.child
			find_word_flag = False
			while find_word_flag != True:
				if current.nodeName == brunch_str[level]:
					find_word_flag = True
				elif current.next is CMDTreeNode:
					current = current.next
				else:
					break;
			if find_word_flag is False:
				current.SetNext(CMDTreeNode(brunch_str[level]))
				current = current.next
			if level == len(brunch_str)-1:
				current.cmdName = cmd
				return
			current.SetBrunch(brunch_str,cmd,level+1)
		pass
	def FindCmd(self,str_array,iter_count = 0,ratio = 90):
		if iter_count < len(str_array):
			if fuzz.ratio(self.nodeName, str_array[iter_count]) >= ratio:
				if type(self.cmdName) is str:
					return self.cmdName
				else:
					command = CMDNotFull
			elif type(self.next) is CMDTreeNode:
				command = self.next.FindCmd(str_array,iter_count)
			else:
				return None
			
			if command == CMDNotFull and type(self.child) is CMDTreeNode:
				command = self.child.FindCmd(str_array,iter_count + 1)
			if type(command) is str:
				return command
			else:
				return None
		else:
			return None
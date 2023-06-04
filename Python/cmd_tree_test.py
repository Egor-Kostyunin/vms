from cmd_tree import CMDTreeNode
#Структура тестового дерева команд
#Root
#-Test
#--Command(Test_Command)
#---Screen(Test_Command_Screen)(Не достежима из за комнды Test_Command)
#-Random
#--File(Random_File)
#--Image(Random_Image)
#-Find
#--Mark(Команда не назначенна)
#--Cat(Find_Cat)
root = CMDTreeNode('Root',child=CMDTreeNode('Test',next=CMDTreeNode('Random',next=CMDTreeNode('Find'))))
root.child.SetChild(CMDTreeNode('Command',cmd='Test_Command'))
root.child.child.SetChild(CMDTreeNode('Screen',cmd='Test_Command_Screen'))
root.child.next.SetChild(CMDTreeNode('File',cmd='Random_File'))
root.child.next.child.SetNext(CMDTreeNode('Image',cmd='Random_Image'))
root.child.next.next.SetChild(CMDTreeNode('Mark'))
root.child.next.next.child.SetNext(CMDTreeNode('Cat',cmd='Find_Cat'))

#Тест поиска существующей команды
ret = root.FindCmd(['Root','Test','Command'])
assert type(ret) is str and ret == 'Test_Command','Тест поиска существующей команды'

#Тест поиска не существующей команды с результатом команда не найдена
ret = root.FindCmd(['Root','Test','CommandNotExists'])
assert ret is None,'Тест поиска не существующей команды с результатом команда не найдена'

#Тест поиска не существующей команды с результатом найдена похожая команда
ret = root.FindCmd(['Root','Test','CommandN'])
assert type(ret) is str and ret == 'Test_Command','Тест поиска не существующей команды с результатом найдена похожая команда'

#Тест поиска не достижимой команды
ret = root.FindCmd(['Root','Test','Command','Screen'])
assert type(ret) is str and ret == 'Test_Command','Тест поиска не достижимой команды'

#Тест поиска команды длинее любой имеющийся в дереве
ret = root.FindCmd(['Root','Test','Very','Long','Command'])
assert ret is None,'Тест поиска команды длинее любой имеющийся в дереве'

#Тест поиска не назначенной команды
ret = root.FindCmd(['Root','Find','Mark'])
assert ret is None,'Тест поиска не назначенной команды'

print('Успех')
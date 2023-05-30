from Python.audioSpeecherOOP import AuidoSpeecher
import json
from fuzzywuzzy import fuzz
from Python.profile import Profile

auidoSpeecherObj = AuidoSpeecher()

KEYWORD = 'компьютер'
OPENCMD = 'открой'
SWITCHCMD = 'преключи'
CLOSECMD = 'закрой'

profiles = {}

def StartProggram():
		for command in auidoSpeecherObj.Degenerator():
			strArray = json.loads(command)['text'].split(' ')
			if fuzz.ratio(strArray[0], KEYWORD) >= 80:
				if fuzz.ratio(strArray[1], OPENCMD) >= 80:
					if strArray[2] in profiles:
						print(profiles[strArray[2]].cmd_list['покажи файлы'])
					else:
						profiles[strArray[2]] = Profile(strArray[2])
				if fuzz.ratio(strArray[1], SWITCHCMD) >= 80:
					print(json.loads(command)['text'])
				if fuzz.ratio(strArray[1], CLOSECMD) >= 80:
					print(json.loads(command)['text'])
			
if(__name__ == "__main__"):
	StartProggram()
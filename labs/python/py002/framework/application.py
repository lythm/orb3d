
import gevent;

class App(object):
	
	AppConfig = {};
	
	def __new__(cls,*args,**kwargs):
		if '_inst' not in vars(cls):
			cls._inst = object.__new__(cls,*args,**kwargs)           
		
		return cls._inst
		
	def Init(self):
		self.LoadConfig("./app.conf");
		

	def Run(self):
				
		while 1:
			gevent.sleep(0.01);
		
		
	def LoadConfig(self, filename):
		
		f = file(filename, "r");
		
		lines = f.readlines();
		
		for line in lines:
			s = line.split(None, 1);
			if len(s) > 1 and s[0][0] != '#':
				self.AppConfig[s[0]] = s[1];
				
		print self.AppConfig;
		
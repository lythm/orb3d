
import gevent;
from gevent.server import StreamServer;
import gevent.event;

class App(object):
	
	AppConfig = {};
	
	__network = None;
	
	__quit = gevent.event.Event();
	
	
	def __new__(cls,*args,**kwargs):
		if '_inst' not in vars(cls):
			cls._inst = object.__new__(cls,*args,**kwargs)           
		
		return cls._inst
		
	def Run(self):
				
		self.LoadConfig("./app.conf");
		
		#self.__network = StreamServer();
		
		self.__quit.wait();
		
		
	def LoadConfig(self, filename):
		
		f = file(filename, "r");
		
		lines = f.readlines();
		
		for line in lines:
			s = line.split(None, 1);
			if len(s) > 1 and s[0][0] != '#':
				self.AppConfig[s[0]] = s[1];
				
		print self.AppConfig;
		 


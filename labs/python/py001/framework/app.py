import sys;
import time;

from event_hub import *;
from registry import Registry;


class Application:
	
	_hub = EventHub();
	_reg = Registry();
	
	
	def __init__(self):
		pass;
	
	
	def t_h(self, event):
		print event._eid;
		
		
	def __init(self):
		
		print sys.argv;
		
		self._hub.RegisterEvent(2, self.t_h);
		
		return True;
	
	
	
	def __fin(self):
		pass;
		
	def __run(self):
		while True:
					
			e = Event();
			
			e._eid = 1;
			
			e2 = Event();
			
			e2._eid = 2;
			
			self._hub.Dispatch([e, e2]);
			
			time.sleep(0.001);
			
	def run(self):
		if self.__init() != True:
			return False;
			
		self.__run();
		
		self.__fin();
		
		return True;
		
		
		

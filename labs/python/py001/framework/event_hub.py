
class Event:
	_eid = 0;
	
	def GetID():
		return _eid;
		

class EventHub:
	
	_handler_map = {};
	
	def __init__(self):
		pass
	
	
	def Dispatch(self, events):
		
		for e in events:
			if e._eid in self._handler_map:
				for handler in self._handler_map[e._eid]:
					handler(e);
				
	def RegisterEvent(self, eid, handler):
		
		if (eid in self._handler_map) == False:
			self._handler_map[eid] = [];
		
		self._handler_map[eid].append(handler);
	
	def UnregisterEvent(self, eid, handler):
		
		if eid in self._handler_map:
			self._handler_map[eid].remove(handler);
	
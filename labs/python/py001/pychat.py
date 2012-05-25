

import gevent;


from gevent.server import StreamServer;

class Session:
	
	def run(self):
		
		while 1:
			print "session running";
			gevent.sleep(1);
		

def cb(socket, address):
	print address, "connected";
	
	session = Session();
	
	session.run();
		

if __name__ == "__main__":
	s = StreamServer(("192.168.0.2", 8900), cb, backlog = 10000, spawn = 1000);
	
	s.serve_forever();



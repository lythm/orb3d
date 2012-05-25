import gevent;
import gevent.monkey;
from gevent.server import StreamServer;
from gevent.wsgi import WSGIServer;

from framework import App;
from framework import Registry;



class SampleApp(App):
	def Init(self):
		App.Init(self);
		print "SampleApp";
		

if __name__ == "__main__":

	gevent.monkey.patch_all();
	app = SampleApp();
	
	app.Init();
	app.Run();
	

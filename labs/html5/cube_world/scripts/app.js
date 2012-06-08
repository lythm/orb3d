
include("scripts/world.js");
include("scripts/rendermanager.js");
include("scripts/entitymanager.js");


function Application()
{
	this.init = function(screen_id, fps)
	{

		this.date = new Date();

		this.fps = fps;
		this.screen = document.getElementById(screen_id);
		
		this.screen_ctx = this.screen.getContext("2d");


		this.world = new World();
		
		this.render_manager = new RenderManager();

		this.render_manager.init(this.screen);
				
		this.entity_manager = new EntityManager();


		window.setInterval(this.update.bind(this), 1000 / fps);

		//document.getElementById("output").value = fps;

		var t = [];

		t[0] = "a";
		t[1] = "b";

		alert(t[0] + "," + t[1]);
		
	}
	
	this.update = function()
	{
		
		var tick = this.date.getTime();

		this.entity_manager.update(tick);

		this.screen_ctx.clearRect(0, 0, this.screen.width, this.screen.height); 
		this.render_manager.render();

		//document.getElementById("output").value += this.world.width + "," + this.world.height + "\n";
		//document.getElementById("output").value += this.fps + "<br>";
	}

}

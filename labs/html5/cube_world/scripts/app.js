
include("scripts/world.js");
include("scripts/rendermanager.js");
include("scripts/entitymanager.js");


function Application()
{
	this.init = function(screen_id, fps)
	{

		this.date = new Date();

		this.screen = document.getElementById(screen_id);
		
		this.screen_ctx = this.screen.getContext("2d");


		this.world = new World();
		
		this.render_manager = new RenderManager();

		this.render_manager.init(this.screen);
				
		this.entity_manager = new EntityManager();

		window.setInterval(this.update.bind(this), 1000 / fps);


		this.frame_count = 0;
		this.frame_tick = 0;
	}
	
	this.draw_fps = function(tick)
	{
		var dt = tick - this.frame_tick;
		if(dt > 1000)
		{
			this.fps = this.frame_count * 1000 / dt;
			this.frame_tick = tick;
			this.frame_count = 0;
		}
		else
		{
			this.frame_count ++;
		}
		
		this.screen_ctx.fillStyle = "RGB(255,255,255)";

		this.screen_ctx.fillText("fps: " + this.fps.toFixed(3), 10, 10);

	}
	this.update = function()
	{
		var date = new Date();
		var tick = date.getTime();

		this.screen_ctx.clearRect(0, 0, this.screen.width, this.screen.height); 

		this.screen_ctx.fillStyle = "RGB(0,0,0)";

		this.screen_ctx.fillRect(0, 0, this.screen.width, this.screen.height); 

		this.entity_manager.update(tick);
		
		this.render_manager.render();


		this.draw_fps(tick);
		
	}

}

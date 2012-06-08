

function RenderData()
{
	this.x = 0;
	this.y = 0;
	this.w = 1;
	this.h = 1;
	this.sprite = null;


}

function RenderManager()
{
	this.init = function(canvas)
	{
		this.canvas = canvas;
		
		this.ctx2d = canvas.getContext("2d");

		
		this.render_data = [];
	}

	

	this.render = function()
	{

		this.ctx2d.strokeStyle="RGBA(0,0,0, 255)";
		this.ctx2d.strokeRect(100, 100, 10, 10);

		var rd;
		for( rd in this.render_data)
		{
			this.ctx2d.drawImage(rd.sprite, rd.x, rd.y, rd.w, rd.h);
		}
	}


}
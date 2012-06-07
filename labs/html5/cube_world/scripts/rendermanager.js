


function RenderManager()
{
	this.init = function(canvas)
	{
		this.canvas = canvas;
		
		this.ctx2d = canvas.getContext("2d");


	}

	

	this.render = function()
	{

		this.ctx2d.strokeStyle="RGBA(0,0,0, 255)";
		this.ctx2d.strokeRect(100, 100, 10, 10);

	}


}
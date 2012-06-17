

function Sprite()
{
	this.load_from_url = function(url)
	{
		this.img = new Image();
		this.img.src = url;

	}
	
	this.draw = function(target, x, y, w, h, sx, sy, sw, sh)
	{
		//target.drawImage
	}

}

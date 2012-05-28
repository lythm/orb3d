

function con_writeln(text) {
	this.lines.push(text);
	this.draw();
}

function con_clear() {

	var s = document.getElementById(this.canvas_id);

	var ctx = s.getContext("2d");

	if(this.bgcolor)
	{
		ctx.fillStyle = this.bgcolor;
	}
	else
	{
		ctx.fillStyle = "rgb(0,0,0)";
	}
	ctx.clearRect(0, 0, s.width, s.height);
	ctx.fillRect(0, 0, s.width, s.height);

}

function con_resize(w, h) {

	var s = document.getElementById(this.canvas_id);

	s.width = w;
	s.height = h;

	this.draw();
}
function con_draw() {

	this.clear();

	var s = document.getElementById(this.canvas_id);

	var ctx = s.getContext("2d");

	ctx.fillStyle=this.fontcolor;
	
	for(var i = this.lines.length - 1; i >= 0; --i)
	{
		var x = 5;
		var y =  s.height - (this.lines.length - i ) * 12 - 10;
		if( y <= 0)
		{
			break;
		}
		ctx.fillText(this.prompt + this.lines[i], 10, y);
	}

	ctx.fillText(this.prompt + this.input_buffer, 10, s.height - 10);
}


function con_onkey(event)
{
	var e = event || window.event;
	
	var ch = String.fromCharCode(e.keyCode);

	if(e.keyCode == 0xd)
	{
		this.writeln(this.input_buffer);
		this.input_buffer = "";
	}
	else
	{
		this.input_buffer += ch;
	}

	this.draw();
}

function Console(canvas_id) {

    this.canvas_id = canvas_id;

    this.lines = [];
	this.input_buffer = "";

    this.on_resize = con_resize;

    this.draw = con_draw;

    this.clear = con_clear;

    this.writeln = con_writeln;

	this.prompt = "#";

	this.bgcolor="rgb(0,0,0)";
	this.fontcolor="rgb(255,255,255)";
	
	this.on_key = con_onkey;


}





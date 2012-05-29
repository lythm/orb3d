

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
		ctx.fillText(this.lines[i], 10, y);
	}
	
	if(this.show_cursor)
	{
		ctx.fillText(this.prompt + this.input_buffer + "_", 10, s.height - 10);
	}
	else
	{
		ctx.fillText(this.prompt + this.input_buffer, 10, s.height - 10);
	}
}


function con_onkey(event)
{
	var e = event || window.event;
	
	var ch = String.fromCharCode(e.keyCode);

	if(e.type == "keydown")
	{
		switch(e.keyCode)
		{
			case 8:
				
				this.input_buffer = this.input_buffer.slice(0, -1);
				
				e.returnValue = false;
				e.cancelBubble = true;
				this.draw();
				return false;
			default:
				return true;
		}
	}

	if(e.type == "keypress")
	{

		switch(e.keyCode)
		{
			case 0xd:
				
				this.writeln(this.prompt + this.input_buffer);

				this.parse_cmdln(this.input_buffer);

				this.input_buffer = "";
				break;
			
			
			default:

				this.input_buffer += ch;
				break;
		}
	}

	this.draw();

	return true;
}

function con_parse_cmdln(cmdln)
{
	var ret = cmdln.split(" ", 1);

	if(ret == "")
	{
		return;
	}
	if(this.on_syscmd(ret[0], cmdln) == true)
	{
		return;
	}
	
	

	if(this.on_cmd)
	{
		if(this.on_cmd(ret[0], cmdln) == false)
		{
			this.writeln("unknown command: " + ret[0] + ".");
		}
	}

}

function con_on_syscmd(cmd, cmdln)
{
	switch(cmd)
	{
		case "sys_help":
			this.writeln("sys_help:				print sys command list.");
			this.writeln("sys_bgclr:			change background color.");
			this.writeln("sys_fgclr:			change foreground color.")
			break;
		case "sys_bgclr":
			
			var result = cmdln.split(" ", 2);
			
			if(result.length != 2)
			{
				this.writeln("invalid parameter.");
			}
			else
			{
				this.bgcolor = result[1];
				this.draw();
			}

			break;

		case "sys_fgclr":
			var result = cmdln.split(" ", 2);
			
			if(result.length != 2)
			{
				this.writeln("invalid parameter.");
			}
			else
			{
				this.fontcolor = result[1];
				this.draw();
			}

			break;
		default:
			return false;
	}

	return true;
}

function con_on_interval()
{
	this.show_cursor = !this.show_cursor;
	this.draw();
}

function Console(canvas_id) {

    this.canvas_id = canvas_id;

    this.lines = [];
	this.input_buffer = "";

    this.resize = con_resize;

    this.draw = con_draw;

    this.clear = con_clear;

    this.writeln = con_writeln;

	this.prompt = "#";

	this.bgcolor="rgb(0,0,0)";
	this.fontcolor="rgb(255,255,255)";

	
	this.on_key = con_onkey;

	this.parse_cmdln = con_parse_cmdln;

	this.on_syscmd = con_on_syscmd;

	this.on_cmd = function(cmd, cmdline){return false;}

	this.on_interval = con_on_interval.bind(this);

	setInterval(this.on_interval, 500);

	this.show_cursor = true;
}





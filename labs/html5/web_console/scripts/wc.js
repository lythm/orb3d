
function Console(canvas_id) {

    this.canvas_id = canvas_id;
	this.prompt = "#";
	this.bgcolor="rgb(0,0,0)";
	this.fontcolor="rgb(255,255,255)";
    this.lines = [];
	this.input_buffer = "";
	this.show_cursor = true;
	
	// resize
	this.resize = function (w, h) {

		var s = document.getElementById(this.canvas_id);

		s.width = w;
		s.height = h;

		this.draw();
	}

	// draw
    this.draw = function () {

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


	// clear
    this.clear = function () {

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

	// writeln
    this.writeln = function (text) {
		this.lines.push(text);
		this.draw();
	}
	

	// on_key
	this.on_key = function (event){
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

	// parse command line
	this.parse_cmdln = function (cmdln){
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

	// on system command
	this.on_syscmd = function (cmd, cmdln){
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

	// on command
	this.on_cmd = function(cmd, cmdline){
		return false;
	}

	// on timer
	this.on_interval = function(){
		this.show_cursor = !this.show_cursor;
		this.draw();
	}

	
	
	setInterval(this.on_interval.bind(this), 500);

}





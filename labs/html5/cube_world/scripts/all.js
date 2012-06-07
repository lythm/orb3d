
function include(src)
{
	var script = document.createElement("script");
    script.setAttribute("src", src);
    document.getElementsByTagName("head")[0].appendChild(script);
}


include("scripts/app.js");




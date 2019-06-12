

const char MAIN_page[] PROGMEM = R"=====(
<html>
  <head>
    <title>Moteur</title>
    <script>
	function getRandomInt(max) {
  return Math.floor(Math.random() * Math.floor(max));
	}
    function s(u){var x = new XMLHttpRequest();x.open("GET", u+"?x="+getRandomInt(10000), true);x.send(null);}
    function ret(u){return function(e){
                                s(u);
                                e.returnValue = false;
                                return false;
                            }
                    }
    window.addEventListener('load', function(){
        var lf = document.getElementById('lf');
        var rf = document.getElementById('rf');
        var av = document.getElementById('av');
        var rc = document.getElementById('rc');
        var acc = document.getElementById('acc');
        
        lf.addEventListener('click', ret("startUp"), false);
        rf.addEventListener('click', ret("shutDown"), false);
        av.addEventListener('click', ret("goForward"), false);
        rc.addEventListener('click', ret("goBackward"), false);
        acc.addEventListener('click', ret("accelerer"), false);
   }, false);
    </script>
  </head>
  <body>
  <div>
    <button id="lf" style="width:50%;height:50%;float:left;">ON</button>
    <button id="rf" style="width:50%;height:50%;float:left;">OFF</button>
	</div>
  <div>
    <button id="av" style="width:50%;height:50%;float:left;">Avancer</button>
    <button id="rc" style="width:50%;height:50%;float:left;">Reculer</button>
  </div>
  <div>
    <button id="acc" style="width:50%;height:50%;float:left;">Accelerer</button>
    </div>
  </body>
</html>
)=====";

		

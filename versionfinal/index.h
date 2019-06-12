

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
        var re = document.getElementById('re');
        
        lf.addEventListener('click', ret("startUp"), false);
        rf.addEventListener('click', ret("shutDown"), false);
        av.addEventListener('click', ret("goForward"), false);
        rc.addEventListener('click', ret("goBackward"), false);
        acc.addEventListener('click', ret("accelerer"), false);
        re.addEventListener('click', ret("ralentir"), false);
   }, false);
    </script>
  </head>
  <body>
  <div>
  <div style="width:100%;heigth:100%">
    <button id="lf" style="width:50%;height:35%;float:left;background-color: #008CBA;color: white;border-radius: 50%;font-size: 24px;"><strong>ON</strong></button>
    <button id="rf" style="width:50%;height:35%;float:left;background-color: #008CBA;color: white;border-radius: 50%;font-size: 24px;"><strong>OFF</strong></button>
	</div>
  <div>
    <button id="av" style="width:50%;height:35%;float:left;background-color: #008CBA;color: white;border-radius: 50%;font-size: 24px;"><strong>Avancer</strong></button>
    <button id="rc" style="width:50%;height:35%;float:left;background-color: #008CBA;color: white;border-radius: 50%;font-size: 24px;"><strong>Reculer</strong></button>
  </div>
  <div>
    <button id="acc" style="width:50%;height:35%;float:left;background-color: #008CBA;color: white;border-radius: 50%;font-size: 24px;"><strong>Accelerer</strong></button>
    <button id="re" style="width:50%;height:35%;float:left;background-color: #008CBA;color: white;border-radius: 50%;font-size: 24px;"><strong>Relantir</strong></button>
    </div>
  </div> 
  </body>
</html>
)=====";

		

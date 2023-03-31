String contentHome;
String contentAccel;
String contentBreath;
String contentSensors;
String contentMode;
String contentHTMLScript;

void monContentHTMLScript(){
  
  contentHTMLScript = ""

  "<body>"
  "<canvas id=\"myCanvas\" width=\"250\" height=\"250\" style=\"border:1px solid grey\"></canvas>"
  "<p></p>"
    "<form method='get' action='filters'>"
    "<input type=\"checkbox\" id=\"s1EMAFilter\" name=\"s1EMAFilter\""
    +s1EMAFilter+
    ">"
    "<label for=\"s1EMAFilter\">EMAFilter</label><br>"
    "<INPUT type=\"submit\" value=\"save filter settings\">"
    "</form></body></html>";
}

String contentScript = ""
// Get current sensor readings when the page loads  
"<script>"
"let myData = 42;"
"let offset = 25;"
"let myValues = [];"
"let counter = 0;"

/*"window.addEventListener('load', getReadings);"

// Function to get current readings on the webpage when it loads for the first time
"function getReadings(){"
  "var xhr = new XMLHttpRequest();"
  "xhr.onreadystatechange = function() {"
    "if (this.readyState == 4 && this.status == 200) {"
      "var myObj = JSON.parse(this.responseText);"
      "console.log(myObj);"
      //"var temp = myObj.temperature;"
      //"var hum = myObj.humidity;"
      //"gaugeTemp.value = temp;"
      //"gaugeHum.value = hum;"
    "}"
  "};"
  "xhr.open(\"GET\", \"/readings\", true);"
  "xhr.send();"
"}"*/

"function showSensor(data){"
  "const canvas = document.getElementById(\"myCanvas\");"
  "const ctx = canvas.getContext(\"2d\");"
  //"ctx.style.position = 'absolute';"
  //"ctx.style.top = '10px';"
  //"ctx.style.left = '50px';"
  "ctx.font = \"16px Arial\";"
  "ctx.clearRect(0,0,canvas.width,canvas.height);"
  "let myObj = JSON.parse(data);"
  "myValues[counter] = myObj.sensor1Value;"
  "ctx.beginPath();"
  "for(i=0;i<200;i++){"
      "ctx.arc(offset+i, (myValues[i]/-25)+175, 1, 0, 2 * Math.PI);"
  "}"
  "ctx.stroke();"
  "ctx.fillText(\"sensor1Value: \", 25, 200);"
  "ctx.fillText(myObj.sensor1Value, 150, 200);"
  "ctx.fillText(\"max: \", 25, 218);"
  "ctx.fillText(myObj.myMax, 150, 218);"
  "ctx.fillText(\"min: \", 25, 236);"
  "ctx.fillText(myObj.myMin, 150, 236);"
  
"}"

"if (!!window.EventSource) {"
 " var source = new EventSource('/events');"
  
  "source.addEventListener('open', function(e) {"
    "console.log(\"Events Connected\");"
  "}, false);"

  "source.addEventListener('error', function(e) {"
    "if (e.target.readyState != EventSource.OPEN) {"
      "console.log(\"Events Disconnected\");"
    "}"
  "}, false);"
  
  "source.addEventListener('message', function(e) {"
    "console.log(\"message\", e.data);"
    "showSensor(e.data);"
    "var myObj = JSON.parse(e.data);"
    "console.log(myObj);"
    "counter++;"
    "if (counter > 200){"
      "counter = 0;"
      "}"
    //"myData = e.data;"
  "}, false);"
"}"
  
"</script>";

String contentHeadStyle = ""
"<!DOCTYPE HTML><html>"
"<head>"
"<title>CajitaAbierta</title>"
"<meta name = \"viewport\" content = \"width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0\">"
"<link rel=\"icon\" href=\"data:,\">"
"<style>" 
"body { background-color: #FF9F0F;font-family: Arial, Helvetica, sans-serif;Color: #111111;"
"font-size: 18px; margin-left:auto;margin-right:auto;}"
"ol {list-style-type: none}"

"input[type=button]{  background-color: #DDDDD;border: none;color: white;padding: 15px 20px;"
"text-align: center;text-decoration: none;display: inline-block;font-size: 18px;}"

"input[type=submit]{  background-color: #  ;border: none;color: white;padding: 15px 20px;"
"text-align: center;text-decoration: none;display: inline-block;font-size: 18px;border: none;border-radius: 4px;}"

"input[type=select]{  background-color: #DD622D ;border: none;color: white;padding: 15px 20px;"
"text-align: center;text-decoration: none;display: inline-block;font-size: 18px;border: none;border-radius: 4px;}"

"a:link {color: #DDDDDD; text-decoration: none;}"/* unvisited link */
"a:visited {color: #CCCCCC;}"/* visited link */
"a:hover {color: #FFFFFF;}"/* mouse over link */
"a:active {color: #FFFFFF;}"/* selected link */

"</style>"
"</head>"
"<body>";

  String contentReboot =

    "<center><b>Config saved</b></center><br>"
    "<center><b>"
    " <a href = \"wifi.html\"> WiFI </a>"
    " / <a href = \"accel.html\"> Accelerometer </a>"
    " / <a href = \"blowsuck.html\"> Blow suck </a>"
    " / <a href = \"sensors.html\"> Sensors </a>"
    " / <a href = \"mode.html\"> Mode </a>"
    " / <a href = \"/update\"> Firmware </a>"
    "</b></center>"
    "<p></p>"
    "<form method='get' action='reboot'>"
    "<INPUT type=\"submit\" value=\"reboot\">"
    "</form></body></html>";

  String menuHome = 
    "<center><b>WiFI Credentials</b></center><br>"
    "<b><center>"
    " <a href = \"accel.html\"> Accelerometer </a>"
    " / <a href = \"blowsuck.html\"> Blow suck </a>"
    " / <a href = \"sensors.html\"> Sensors </a>"
    " / <a href = \"mode.html\"> Mode </a>"
    " / <a href = \"/update\"> Firmware </a>"
    "</b></center>";

void monContentHome(){
    
    contentHome = "" 
    "<ol><li>"
    //"<form action=\"/scan\" method=\"POST\">"
    //"<INPUT type=\"submit\" value=\" scan\">"
    //"</form>"
    "<p></p>"
    "<form method='get' action='wificfg'>"
    "<label> SSID: </label>"
    "<input type='text' name='ssid' placeholder="
    + ssid +
    "><br/>" 
    "</li><li>"
    "<label> PASS: </label>"
    
    "<input type='text' name='pass' placeholder="
    + password +
    "> <p>"
    "</li><ol>"
    //"<INPUT type=\"submit\" value=\"save\">"
    //"</form>"

    //"<form method='get' action='OSCServer'>"
    "<p>Sensor output goes to : </p>"
    
    "<input type=\"radio\" id=\"OSC1\" name=\"OSCServer\" value=\"checkedTOSCB\" required "
    +checkedTOSCB+
    ">"
    "<label for=\"OSC1\">TouchOSCBridge</label><br>"
    
    "<input type=\"radio\" id=\"TDLF\" name=\"OSCServer\" value=\"checkedTDLF\" "
    +checkedTDLF+
    ">"
    "<label for=\"TDLF\">TDLF</label><br>"
    
    "<input type=\"radio\" id=\"OSC2\" name=\"OSCServer\" value=\"checkedOSC\" "
    +checkedOSC+
    ">"
    "<label for=\"OSC2\">OSC</label><br>"
    
    "<INPUT type=\"submit\" value=\"submit\">"  
    "</form></body></html>";
  }
 
 
/////// Accelerometer ////////
#if defined Accelerometer
void monContentAccel(){
  contentAccel = ""
      
    "<center><b>Accelerometer</b></center><br>"
    "<b><center>"
    " <a href = \"/\"> WiFI </a>"
    " / <a href = \"blowsuck.html\"> Blow suck </a>"
    " / <a href = \"sensors.html\"> Sensors </a>"
    " / <a href = \"mode.html\"> Mode </a>"
    " / <a href = \"/update\"> Firmware </a>"
    "</b></center>"
          
    "<form method='get' action='accelcfg'>"
    
    "<ol><li>"
    "<input type=\"checkbox\" id=\"accelX\" name=\"accelX\""
    +accelX+
    ">"
    "<label for=\"accelX\">Accel X</label>"
    "<label for=\"accelXChan\">Channel</label><select name=\"accelXChan\" id=\"accelXChan\" >"
    "<option value=\"\" disabled selected>"
    +accelXChan+ 
    "</option>"
    "<option value=\"1\">1</option><option value=\"2\">2</option><option value=\"3\">3</option><option value=\"4\">4</option><option value=\"5\">5</option><option value=\"6\">6</option><option value=\"7\">7</option><option value=\"8\">8</option><option value=\"9\">9</option><option value=\"10\">10</option><option value=\"11\">11</option><option value=\"12\">12</option><option value=\"13\">13</option><option value=\"14\">14</option><option value=\"15\">15</option><option value=\"16\">16</option></select>"
    "<label for=\"accelXCC\">CC</label><select name=\"accelXCC\" id=\"accelXCC\" >"
    "<option value=\"\" disabled selected>"
    +accelXCC+
    "</option>"
    
    "<option value=\"0\">0</option><option value=\"1\">1</option><option value=\"2\">2</option><option value=\"3\">3</option><option value=\"4\">4</option><option value=\"5\">5</option><option value=\"6\">6</option><option value=\"7\">7</option><option value=\"8\">8</option><option value=\"9\">9</option><option value=\"10\">10</option><option value=\"11\">11</option><option value=\"12\">12</option><option value=\"13\">13</option><option value=\"14\">14</option><option value=\"15\">15</option><option value=\"16\">16</option><option value=\"17\">17</option><option value=\"18\">18</option><option value=\"19\">19</option><option value=\"20\">20</option><option value=\"21\">21</option><option value=\"22\">22</option><option value=\"23\">23</option><option value=\"24\">24</option><option value=\"25\">25</option><option value=\"26\">26</option><option value=\"27\">27</option><option value=\"28\">28</option><option value=\"29\">29</option><option value=\"30\">30</option><option value=\"31\">31</option><option value=\"32\">32</option><option value=\"33\">33</option><option value=\"34\">34</option><option value=\"35\">35</option><option value=\"36\">36</option><option value=\"37\">37</option><option value=\"38\">38</option><option value=\"39\">39</option><option value=\"40\">40</option><option value=\"41\">41</option><option value=\"42\">42</option><option value=\"43\">43</option><option value=\"44\">44</option><option value=\"45\">45</option><option value=\"46\">46</option><option value=\"47\">47</option><option value=\"48\">48</option><option value=\"49\">49</option><option value=\"50\">50</option><option value=\"51\">51</option><option value=\"52\">52</option><option value=\"53\">53</option><option value=\"54\">54</option><option value=\"55\">55</option><option value=\"56\">56</option><option value=\"57\">57</option><option value=\"58\">58</option><option value=\"59\">59</option><option value=\"60\">60</option><option value=\"61\">61</option><option value=\"62\">62</option><option value=\"63\">63</option><option value=\"64\">64</option><option value=\"65\">65</option><option value=\"66\">66</option><option value=\"67\">67</option><option value=\"68\">68</option><option value=\"69\">69</option><option value=\"70\">70</option><option value=\"71\">71</option><option value=\"72\">72</option><option value=\"73\">73</option><option value=\"74\">74</option><option value=\"75\">75</option><option value=\"76\">76</option><option value=\"77\">77</option><option value=\"78\">78</option><option value=\"79\">79</option><option value=\"80\">80</option><option value=\"81\">81</option><option value=\"82\">82</option><option value=\"83\">83</option><option value=\"84\">84</option><option value=\"85\">85</option><option value=\"86\">86</option><option value=\"87\">87</option><option value=\"88\">88</option><option value=\"89\">89</option><option value=\"90\">90</option><option value=\"91\">91</option><option value=\"92\">92</option><option value=\"93\">93</option><option value=\"94\">94</option><option value=\"95\">95</option><option value=\"96\">96</option><option value=\"97\">97</option><option value=\"98\">98</option><option value=\"99\">99</option><option value=\"100\">100</option><option value=\"101\">101</option><option value=\"102\">102</option><option value=\"103\">103</option><option value=\"104\">104</option><option value=\"105\">105</option><option value=\"106\">106</option><option value=\"107\">107</option><option value=\"108\">108</option><option value=\"109\">109</option><option value=\"110\">110</option><option value=\"111\">111</option><option value=\"112\">112</option><option value=\"113\">113</option><option value=\"114\">114</option><option value=\"115\">115</option><option value=\"116\">116</option><option value=\"117\">117</option><option value=\"118\">118</option><option value=\"119\">119</option><option value=\"120\">120</option><option value=\"121\">121</option><option value=\"122\">122</option><option value=\"123\">123</option><option value=\"124\">124</option><option value=\"125\">125</option><option value=\"126\">126</option><option value=\"127\">127</option></select>"
    "</li><li>"
    "<input type=\"checkbox\" id=\"accelY\" name=\"accelY\""
    +accelY+
    ">"
    "<label for=\"accelY\">Accel Y</label>"
    "<label for=\"accelYChan\">Channel</label><select name=\"accelYChan\" id=\"accelYChan\">"
    "<option value=\"\" disabled selected>"
    +accelYChan+
    "</option>"
    "<option value=\"1\">1</option><option value=\"2\">2</option><option value=\"3\">3</option><option value=\"4\">4</option><option value=\"5\">5</option><option value=\"6\">6</option><option value=\"7\">7</option><option value=\"8\">8</option><option value=\"9\">9</option><option value=\"10\">10</option><option value=\"11\">11</option><option value=\"12\">12</option><option value=\"13\">13</option><option value=\"14\">14</option><option value=\"15\">15</option><option value=\"16\">16</option></select>"
    "<label for=\"accelYCC\">CC</label><select name=\"accelYCC\" id=\"accelYCC\" >"
    "<option value=\"\" disabled selected>"
    +accelYCC+
    "</option>"
    "<option value=\"0\">0</option><option value=\"1\">1</option><option value=\"2\">2</option><option value=\"3\">3</option><option value=\"4\">4</option><option value=\"5\">5</option><option value=\"6\">6</option><option value=\"7\">7</option><option value=\"8\">8</option><option value=\"9\">9</option><option value=\"10\">10</option><option value=\"11\">11</option><option value=\"12\">12</option><option value=\"13\">13</option><option value=\"14\">14</option><option value=\"15\">15</option><option value=\"16\">16</option><option value=\"17\">17</option><option value=\"18\">18</option><option value=\"19\">19</option><option value=\"20\">20</option><option value=\"21\">21</option><option value=\"22\">22</option><option value=\"23\">23</option><option value=\"24\">24</option><option value=\"25\">25</option><option value=\"26\">26</option><option value=\"27\">27</option><option value=\"28\">28</option><option value=\"29\">29</option><option value=\"30\">30</option><option value=\"31\">31</option><option value=\"32\">32</option><option value=\"33\">33</option><option value=\"34\">34</option><option value=\"35\">35</option><option value=\"36\">36</option><option value=\"37\">37</option><option value=\"38\">38</option><option value=\"39\">39</option><option value=\"40\">40</option><option value=\"41\">41</option><option value=\"42\">42</option><option value=\"43\">43</option><option value=\"44\">44</option><option value=\"45\">45</option><option value=\"46\">46</option><option value=\"47\">47</option><option value=\"48\">48</option><option value=\"49\">49</option><option value=\"50\">50</option><option value=\"51\">51</option><option value=\"52\">52</option><option value=\"53\">53</option><option value=\"54\">54</option><option value=\"55\">55</option><option value=\"56\">56</option><option value=\"57\">57</option><option value=\"58\">58</option><option value=\"59\">59</option><option value=\"60\">60</option><option value=\"61\">61</option><option value=\"62\">62</option><option value=\"63\">63</option><option value=\"64\">64</option><option value=\"65\">65</option><option value=\"66\">66</option><option value=\"67\">67</option><option value=\"68\">68</option><option value=\"69\">69</option><option value=\"70\">70</option><option value=\"71\">71</option><option value=\"72\">72</option><option value=\"73\">73</option><option value=\"74\">74</option><option value=\"75\">75</option><option value=\"76\">76</option><option value=\"77\">77</option><option value=\"78\">78</option><option value=\"79\">79</option><option value=\"80\">80</option><option value=\"81\">81</option><option value=\"82\">82</option><option value=\"83\">83</option><option value=\"84\">84</option><option value=\"85\">85</option><option value=\"86\">86</option><option value=\"87\">87</option><option value=\"88\">88</option><option value=\"89\">89</option><option value=\"90\">90</option><option value=\"91\">91</option><option value=\"92\">92</option><option value=\"93\">93</option><option value=\"94\">94</option><option value=\"95\">95</option><option value=\"96\">96</option><option value=\"97\">97</option><option value=\"98\">98</option><option value=\"99\">99</option><option value=\"100\">100</option><option value=\"101\">101</option><option value=\"102\">102</option><option value=\"103\">103</option><option value=\"104\">104</option><option value=\"105\">105</option><option value=\"106\">106</option><option value=\"107\">107</option><option value=\"108\">108</option><option value=\"109\">109</option><option value=\"110\">110</option><option value=\"111\">111</option><option value=\"112\">112</option><option value=\"113\">113</option><option value=\"114\">114</option><option value=\"115\">115</option><option value=\"116\">116</option><option value=\"117\">117</option><option value=\"118\">118</option><option value=\"119\">119</option><option value=\"120\">120</option><option value=\"121\">121</option><option value=\"122\">122</option><option value=\"123\">123</option><option value=\"124\">124</option><option value=\"125\">125</option><option value=\"126\">126</option><option value=\"127\">127</option></select>"
    "</li><li>"
    "<input type=\"checkbox\" id=\"accelZ\" name=\"accelZ\""
    +accelZ+
    ">"
    "<label for=\"accelZ\">Accel Z</label>"
    "<label for=\"accelZChan\">Channel</label><select name=\"accelZChan\" id=\"accelZChan\">"
    "<option value=\"\" disabled selected>"
    +accelZChan+
    "</option>"
    "<option value=\"1\">1</option><option value=\"2\">2</option><option value=\"3\">3</option><option value=\"4\">4</option><option value=\"5\">5</option><option value=\"6\">6</option><option value=\"7\">7</option><option value=\"8\">8</option><option value=\"9\">9</option><option value=\"10\">10</option><option value=\"11\">11</option><option value=\"12\">12</option><option value=\"13\">13</option><option value=\"14\">14</option><option value=\"15\">15</option><option value=\"16\">16</option></select>"
    "<label for=\"accelZCC\">CC</label><select name=\"accelZCC\" id=\"accelZCC\" >"
    "<option value=\"\" disabled selected>"
    +accelZCC+
    "</option>"
    "<option value=\"0\">0</option><option value=\"1\">1</option><option value=\"2\">2</option><option value=\"3\">3</option><option value=\"4\">4</option><option value=\"5\">5</option><option value=\"6\">6</option><option value=\"7\">7</option><option value=\"8\">8</option><option value=\"9\">9</option><option value=\"10\">10</option><option value=\"11\">11</option><option value=\"12\">12</option><option value=\"13\">13</option><option value=\"14\">14</option><option value=\"15\">15</option><option value=\"16\">16</option><option value=\"17\">17</option><option value=\"18\">18</option><option value=\"19\">19</option><option value=\"20\">20</option><option value=\"21\">21</option><option value=\"22\">22</option><option value=\"23\">23</option><option value=\"24\">24</option><option value=\"25\">25</option><option value=\"26\">26</option><option value=\"27\">27</option><option value=\"28\">28</option><option value=\"29\">29</option><option value=\"30\">30</option><option value=\"31\">31</option><option value=\"32\">32</option><option value=\"33\">33</option><option value=\"34\">34</option><option value=\"35\">35</option><option value=\"36\">36</option><option value=\"37\">37</option><option value=\"38\">38</option><option value=\"39\">39</option><option value=\"40\">40</option><option value=\"41\">41</option><option value=\"42\">42</option><option value=\"43\">43</option><option value=\"44\">44</option><option value=\"45\">45</option><option value=\"46\">46</option><option value=\"47\">47</option><option value=\"48\">48</option><option value=\"49\">49</option><option value=\"50\">50</option><option value=\"51\">51</option><option value=\"52\">52</option><option value=\"53\">53</option><option value=\"54\">54</option><option value=\"55\">55</option><option value=\"56\">56</option><option value=\"57\">57</option><option value=\"58\">58</option><option value=\"59\">59</option><option value=\"60\">60</option><option value=\"61\">61</option><option value=\"62\">62</option><option value=\"63\">63</option><option value=\"64\">64</option><option value=\"65\">65</option><option value=\"66\">66</option><option value=\"67\">67</option><option value=\"68\">68</option><option value=\"69\">69</option><option value=\"70\">70</option><option value=\"71\">71</option><option value=\"72\">72</option><option value=\"73\">73</option><option value=\"74\">74</option><option value=\"75\">75</option><option value=\"76\">76</option><option value=\"77\">77</option><option value=\"78\">78</option><option value=\"79\">79</option><option value=\"80\">80</option><option value=\"81\">81</option><option value=\"82\">82</option><option value=\"83\">83</option><option value=\"84\">84</option><option value=\"85\">85</option><option value=\"86\">86</option><option value=\"87\">87</option><option value=\"88\">88</option><option value=\"89\">89</option><option value=\"90\">90</option><option value=\"91\">91</option><option value=\"92\">92</option><option value=\"93\">93</option><option value=\"94\">94</option><option value=\"95\">95</option><option value=\"96\">96</option><option value=\"97\">97</option><option value=\"98\">98</option><option value=\"99\">99</option><option value=\"100\">100</option><option value=\"101\">101</option><option value=\"102\">102</option><option value=\"103\">103</option><option value=\"104\">104</option><option value=\"105\">105</option><option value=\"106\">106</option><option value=\"107\">107</option><option value=\"108\">108</option><option value=\"109\">109</option><option value=\"110\">110</option><option value=\"111\">111</option><option value=\"112\">112</option><option value=\"113\">113</option><option value=\"114\">114</option><option value=\"115\">115</option><option value=\"116\">116</option><option value=\"117\">117</option><option value=\"118\">118</option><option value=\"119\">119</option><option value=\"120\">120</option><option value=\"121\">121</option><option value=\"122\">122</option><option value=\"123\">123</option><option value=\"124\">124</option><option value=\"125\">125</option><option value=\"126\">126</option><option value=\"127\">127</option></select>"
    "</li></ol>"
    
    "<ol><li>"
    "<input type=\"checkbox\" id=\"pan_\" name=\"pan_\""
    +pan_+
    ">"
    "Pan <label for=\"panChan\"> Channel</label><select name=\"panChan\" id=\"panChan\">"
    "<option value=\"\" disabled selected>"
     +panChan+
    "</option>"
    "<option value=\"1\">1</option><option value=\"2\">2</option><option value=\"3\">3</option><option value=\"4\">4</option><option value=\"5\">5</option><option value=\"6\">6</option><option value=\"7\">7</option><option value=\"8\">8</option><option value=\"9\">9</option><option value=\"10\">10</option><option value=\"11\">11</option><option value=\"12\">12</option><option value=\"13\">13</option><option value=\"14\">14</option><option value=\"15\">15</option><option value=\"16\">16</option></select>"
    "<label for=\"panCC\">CC</label><select name=\"panCC\" id=\"panCC\" >"
    "<option value=\"\" disabled selected>"
    +panCC+
    "</option>"
    "<option value=\"0\">0</option><option value=\"1\">1</option><option value=\"2\">2</option><option value=\"3\">3</option><option value=\"4\">4</option><option value=\"5\">5</option><option value=\"6\">6</option><option value=\"7\">7</option><option value=\"8\">8</option><option value=\"9\">9</option><option value=\"10\">10</option><option value=\"11\">11</option><option value=\"12\">12</option><option value=\"13\">13</option><option value=\"14\">14</option><option value=\"15\">15</option><option value=\"16\">16</option><option value=\"17\">17</option><option value=\"18\">18</option><option value=\"19\">19</option><option value=\"20\">20</option><option value=\"21\">21</option><option value=\"22\">22</option><option value=\"23\">23</option><option value=\"24\">24</option><option value=\"25\">25</option><option value=\"26\">26</option><option value=\"27\">27</option><option value=\"28\">28</option><option value=\"29\">29</option><option value=\"30\">30</option><option value=\"31\">31</option><option value=\"32\">32</option><option value=\"33\">33</option><option value=\"34\">34</option><option value=\"35\">35</option><option value=\"36\">36</option><option value=\"37\">37</option><option value=\"38\">38</option><option value=\"39\">39</option><option value=\"40\">40</option><option value=\"41\">41</option><option value=\"42\">42</option><option value=\"43\">43</option><option value=\"44\">44</option><option value=\"45\">45</option><option value=\"46\">46</option><option value=\"47\">47</option><option value=\"48\">48</option><option value=\"49\">49</option><option value=\"50\">50</option><option value=\"51\">51</option><option value=\"52\">52</option><option value=\"53\">53</option><option value=\"54\">54</option><option value=\"55\">55</option><option value=\"56\">56</option><option value=\"57\">57</option><option value=\"58\">58</option><option value=\"59\">59</option><option value=\"60\">60</option><option value=\"61\">61</option><option value=\"62\">62</option><option value=\"63\">63</option><option value=\"64\">64</option><option value=\"65\">65</option><option value=\"66\">66</option><option value=\"67\">67</option><option value=\"68\">68</option><option value=\"69\">69</option><option value=\"70\">70</option><option value=\"71\">71</option><option value=\"72\">72</option><option value=\"73\">73</option><option value=\"74\">74</option><option value=\"75\">75</option><option value=\"76\">76</option><option value=\"77\">77</option><option value=\"78\">78</option><option value=\"79\">79</option><option value=\"80\">80</option><option value=\"81\">81</option><option value=\"82\">82</option><option value=\"83\">83</option><option value=\"84\">84</option><option value=\"85\">85</option><option value=\"86\">86</option><option value=\"87\">87</option><option value=\"88\">88</option><option value=\"89\">89</option><option value=\"90\">90</option><option value=\"91\">91</option><option value=\"92\">92</option><option value=\"93\">93</option><option value=\"94\">94</option><option value=\"95\">95</option><option value=\"96\">96</option><option value=\"97\">97</option><option value=\"98\">98</option><option value=\"99\">99</option><option value=\"100\">100</option><option value=\"101\">101</option><option value=\"102\">102</option><option value=\"103\">103</option><option value=\"104\">104</option><option value=\"105\">105</option><option value=\"106\">106</option><option value=\"107\">107</option><option value=\"108\">108</option><option value=\"109\">109</option><option value=\"110\">110</option><option value=\"111\">111</option><option value=\"112\">112</option><option value=\"113\">113</option><option value=\"114\">114</option><option value=\"115\">115</option><option value=\"116\">116</option><option value=\"117\">117</option><option value=\"118\">118</option><option value=\"119\">119</option><option value=\"120\">120</option><option value=\"121\">121</option><option value=\"122\">122</option><option value=\"123\">123</option><option value=\"124\">124</option><option value=\"125\">125</option><option value=\"126\">126</option><option value=\"127\">127</option></select>"
    "</li><li>"
    "<input type=\"checkbox\" id=\"tilt_\" name=\"tilt_\""
    +tilt_+
    ">" 
    "Tilt <label for=\"tiltChan\">Channel</label><select name=\"tiltChan\" id=\"tiltChan\">"
    "<option value=\"\" disabled selected>"
     +tiltChan+
    "</option>"
    "<option value=\"1\">1</option><option value=\"2\">2</option><option value=\"3\">3</option><option value=\"4\">4</option><option value=\"5\">5</option><option value=\"6\">6</option><option value=\"7\">7</option><option value=\"8\">8</option><option value=\"9\">9</option><option value=\"10\">10</option><option value=\"11\">11</option><option value=\"12\">12</option><option value=\"13\">13</option><option value=\"14\">14</option><option value=\"15\">15</option><option value=\"16\">16</option></select>"
    "<label for=\"tilt\">tiltCC</label><select name=\"tiltCC\" id=\"tiltCC\" >"
    "<option value=\"\" disabled selected>"
     +tiltCC+
    "</option>"
    "<option value=\"0\">0</option><option value=\"1\">1</option><option value=\"2\">2</option><option value=\"3\">3</option><option value=\"4\">4</option><option value=\"5\">5</option><option value=\"6\">6</option><option value=\"7\">7</option><option value=\"8\">8</option><option value=\"9\">9</option><option value=\"10\">10</option><option value=\"11\">11</option><option value=\"12\">12</option><option value=\"13\">13</option><option value=\"14\">14</option><option value=\"15\">15</option><option value=\"16\">16</option><option value=\"17\">17</option><option value=\"18\">18</option><option value=\"19\">19</option><option value=\"20\">20</option><option value=\"21\">21</option><option value=\"22\">22</option><option value=\"23\">23</option><option value=\"24\">24</option><option value=\"25\">25</option><option value=\"26\">26</option><option value=\"27\">27</option><option value=\"28\">28</option><option value=\"29\">29</option><option value=\"30\">30</option><option value=\"31\">31</option><option value=\"32\">32</option><option value=\"33\">33</option><option value=\"34\">34</option><option value=\"35\">35</option><option value=\"36\">36</option><option value=\"37\">37</option><option value=\"38\">38</option><option value=\"39\">39</option><option value=\"40\">40</option><option value=\"41\">41</option><option value=\"42\">42</option><option value=\"43\">43</option><option value=\"44\">44</option><option value=\"45\">45</option><option value=\"46\">46</option><option value=\"47\">47</option><option value=\"48\">48</option><option value=\"49\">49</option><option value=\"50\">50</option><option value=\"51\">51</option><option value=\"52\">52</option><option value=\"53\">53</option><option value=\"54\">54</option><option value=\"55\">55</option><option value=\"56\">56</option><option value=\"57\">57</option><option value=\"58\">58</option><option value=\"59\">59</option><option value=\"60\">60</option><option value=\"61\">61</option><option value=\"62\">62</option><option value=\"63\">63</option><option value=\"64\">64</option><option value=\"65\">65</option><option value=\"66\">66</option><option value=\"67\">67</option><option value=\"68\">68</option><option value=\"69\">69</option><option value=\"70\">70</option><option value=\"71\">71</option><option value=\"72\">72</option><option value=\"73\">73</option><option value=\"74\">74</option><option value=\"75\">75</option><option value=\"76\">76</option><option value=\"77\">77</option><option value=\"78\">78</option><option value=\"79\">79</option><option value=\"80\">80</option><option value=\"81\">81</option><option value=\"82\">82</option><option value=\"83\">83</option><option value=\"84\">84</option><option value=\"85\">85</option><option value=\"86\">86</option><option value=\"87\">87</option><option value=\"88\">88</option><option value=\"89\">89</option><option value=\"90\">90</option><option value=\"91\">91</option><option value=\"92\">92</option><option value=\"93\">93</option><option value=\"94\">94</option><option value=\"95\">95</option><option value=\"96\">96</option><option value=\"97\">97</option><option value=\"98\">98</option><option value=\"99\">99</option><option value=\"100\">100</option><option value=\"101\">101</option><option value=\"102\">102</option><option value=\"103\">103</option><option value=\"104\">104</option><option value=\"105\">105</option><option value=\"106\">106</option><option value=\"107\">107</option><option value=\"108\">108</option><option value=\"109\">109</option><option value=\"110\">110</option><option value=\"111\">111</option><option value=\"112\">112</option><option value=\"113\">113</option><option value=\"114\">114</option><option value=\"115\">115</option><option value=\"116\">116</option><option value=\"117\">117</option><option value=\"118\">118</option><option value=\"119\">119</option><option value=\"120\">120</option><option value=\"121\">121</option><option value=\"122\">122</option><option value=\"123\">123</option><option value=\"124\">124</option><option value=\"125\">125</option><option value=\"126\">126</option><option value=\"127\">127</option></select>"
    "</li><li>" 
    "<input type=\"checkbox\" id=\"roll_\" name=\"roll_\""
    +roll_+
    ">"
    "Roll <label for=\"rollChan\"> Channel</label><select name=\"rollChan\" id=\"rollChan\">"
    "<option value=\"\" disabled selected>"
    +rollChan+
    "</option>"
    "<option value=\"1\">1</option><option value=\"2\">2</option><option value=\"3\">3</option><option value=\"4\">4</option><option value=\"5\">5</option><option value=\"6\">6</option><option value=\"7\">7</option><option value=\"8\">8</option><option value=\"9\">9</option><option value=\"10\">10</option><option value=\"11\">11</option><option value=\"12\">12</option><option value=\"13\">13</option><option value=\"14\">14</option><option value=\"15\">15</option><option value=\"16\">16</option></select>"
    "<label for=\"Roll\">rollCC</label><select name=\"rollCC\" id=\"rollCC\" >"
    "<option value=\"\" disabled selected>"
    +rollCC+
    "</option>"
    "<option value=\"0\">0</option><option value=\"1\">1</option><option value=\"2\">2</option><option value=\"3\">3</option><option value=\"4\">4</option><option value=\"5\">5</option><option value=\"6\">6</option><option value=\"7\">7</option><option value=\"8\">8</option><option value=\"9\">9</option><option value=\"10\">10</option><option value=\"11\">11</option><option value=\"12\">12</option><option value=\"13\">13</option><option value=\"14\">14</option><option value=\"15\">15</option><option value=\"16\">16</option><option value=\"17\">17</option><option value=\"18\">18</option><option value=\"19\">19</option><option value=\"20\">20</option><option value=\"21\">21</option><option value=\"22\">22</option><option value=\"23\">23</option><option value=\"24\">24</option><option value=\"25\">25</option><option value=\"26\">26</option><option value=\"27\">27</option><option value=\"28\">28</option><option value=\"29\">29</option><option value=\"30\">30</option><option value=\"31\">31</option><option value=\"32\">32</option><option value=\"33\">33</option><option value=\"34\">34</option><option value=\"35\">35</option><option value=\"36\">36</option><option value=\"37\">37</option><option value=\"38\">38</option><option value=\"39\">39</option><option value=\"40\">40</option><option value=\"41\">41</option><option value=\"42\">42</option><option value=\"43\">43</option><option value=\"44\">44</option><option value=\"45\">45</option><option value=\"46\">46</option><option value=\"47\">47</option><option value=\"48\">48</option><option value=\"49\">49</option><option value=\"50\">50</option><option value=\"51\">51</option><option value=\"52\">52</option><option value=\"53\">53</option><option value=\"54\">54</option><option value=\"55\">55</option><option value=\"56\">56</option><option value=\"57\">57</option><option value=\"58\">58</option><option value=\"59\">59</option><option value=\"60\">60</option><option value=\"61\">61</option><option value=\"62\">62</option><option value=\"63\">63</option><option value=\"64\">64</option><option value=\"65\">65</option><option value=\"66\">66</option><option value=\"67\">67</option><option value=\"68\">68</option><option value=\"69\">69</option><option value=\"70\">70</option><option value=\"71\">71</option><option value=\"72\">72</option><option value=\"73\">73</option><option value=\"74\">74</option><option value=\"75\">75</option><option value=\"76\">76</option><option value=\"77\">77</option><option value=\"78\">78</option><option value=\"79\">79</option><option value=\"80\">80</option><option value=\"81\">81</option><option value=\"82\">82</option><option value=\"83\">83</option><option value=\"84\">84</option><option value=\"85\">85</option><option value=\"86\">86</option><option value=\"87\">87</option><option value=\"88\">88</option><option value=\"89\">89</option><option value=\"90\">90</option><option value=\"91\">91</option><option value=\"92\">92</option><option value=\"93\">93</option><option value=\"94\">94</option><option value=\"95\">95</option><option value=\"96\">96</option><option value=\"97\">97</option><option value=\"98\">98</option><option value=\"99\">99</option><option value=\"100\">100</option><option value=\"101\">101</option><option value=\"102\">102</option><option value=\"103\">103</option><option value=\"104\">104</option><option value=\"105\">105</option><option value=\"106\">106</option><option value=\"107\">107</option><option value=\"108\">108</option><option value=\"109\">109</option><option value=\"110\">110</option><option value=\"111\">111</option><option value=\"112\">112</option><option value=\"113\">113</option><option value=\"114\">114</option><option value=\"115\">115</option><option value=\"116\">116</option><option value=\"117\">117</option><option value=\"118\">118</option><option value=\"119\">119</option><option value=\"120\">120</option><option value=\"121\">121</option><option value=\"122\">122</option><option value=\"123\">123</option><option value=\"124\">124</option><option value=\"125\">125</option><option value=\"126\">126</option><option value=\"127\">127</option></select>"
    "</li></ol>"
    //      
    "<ol><li>"
    "<label for='stx'>NIY!! Single tap X </label><input type='checkbox' id='stx' name='stx' value='enabled'>"
    "<label for='dtx'>NIY!!  Double tap X </label><input type='checkbox' id='dtx' name='dtx' value='enabled'>"
    "</li><li>"
    "<label for='sty'>NIY!! Single tap Y </label><input type='checkbox' id='sty' name='sty' value='enabled'>"
    "<label for='dty'>NIY!!  Double tap Y </label><input type='checkbox' id='dty' name='dty' value='enabled'>"
    "</li><li>"
    "<label for='stz'>NIY!! Single tap Z </label><input type='checkbox' id='stz' name='stz' value='enabled'>"
    "<label for='dtz'>NIY!! Double tap Z </label><input type='checkbox' id='dtz' name='dtz' value='enabled'>"
    "</li><li>"
    "<label for='freefall'>NIY!! Freefall </label><input type='checkbox' id='freefall' name='freefall' value='enabled'><br>"
    "<INPUT type=\"submit\" value=\"save\" style=\"font-size:18px ; border: none;\">"
    "</li></ol>"
          
    "</form></body></html>";
    
    //// Fin HTML Accelerometer
  }
#endif

//// Breath sensor 
#if defined PressureSensor
void monContentBreath(){
    contentBreath = ""
    "<center><b>Blow / Suck</b></center><br>"
    "<b><center>"
    " <a href = \"/\"> WiFI </a>"
    #if defined Acclerometer
    " / <a href = \"accel.html\"> Accelerometer </a>"
    #endif
    " / <a href = \"sensors.html\"> Sensors </a>"
    " / <a href = \"mode.html\"> Mode </a>"
    " / <a href = \"/update\"> Firmware </a>"
    "</b></center>"
    
    "<p></p><form method='get' action='blowsuckcfg'>"
    
    "<ol><li>"
    "<input type=\"checkbox\" id=\"expire\" name=\"expire\""
    +expire+
    ">"
    "<label for=\"expire\">Check Blow</label>"
    " Blow <label for=\"blowChan\">Channel</label><select name=\"blowChan\" id=\"blowChan\">"
    "<option value=\"\" disabled selected>"
    +blowChan+
    "</option>"
    "<option value=\"1\">1</option><option value=\"2\">2</option><option value=\"3\">3</option><option value=\"4\">4</option><option value=\"5\">5</option><option value=\"6\">6</option><option value=\"7\">7</option><option value=\"8\">8</option><option value=\"9\">9</option><option value=\"10\">10</option><option value=\"11\">11</option><option value=\"12\">12</option><option value=\"13\">13</option><option value=\"14\">14</option><option value=\"15\">15</option><option value=\"16\">16</option></select>"
    "<label for=\"blowCC\">CC</label><select name=\"blowCC\" id=\"blowCC\" >"
    "<option value=\"\" disabled selected>"
    +blowCC+
    "</option>"
    "<option value=\"0\">0</option><option value=\"1\">1</option><option value=\"2\">2</option><option value=\"3\">3</option><option value=\"4\">4</option><option value=\"5\">5</option><option value=\"6\">6</option><option value=\"7\">7</option><option value=\"8\">8</option><option value=\"9\">9</option><option value=\"10\">10</option><option value=\"11\">11</option><option value=\"12\">12</option><option value=\"13\">13</option><option value=\"14\">14</option><option value=\"15\">15</option><option value=\"16\">16</option><option value=\"17\">17</option><option value=\"18\">18</option><option value=\"19\">19</option><option value=\"20\">20</option><option value=\"21\">21</option><option value=\"22\">22</option><option value=\"23\">23</option><option value=\"24\">24</option><option value=\"25\">25</option><option value=\"26\">26</option><option value=\"27\">27</option><option value=\"28\">28</option><option value=\"29\">29</option><option value=\"30\">30</option><option value=\"31\">31</option><option value=\"32\">32</option><option value=\"33\">33</option><option value=\"34\">34</option><option value=\"35\">35</option><option value=\"36\">36</option><option value=\"37\">37</option><option value=\"38\">38</option><option value=\"39\">39</option><option value=\"40\">40</option><option value=\"41\">41</option><option value=\"42\">42</option><option value=\"43\">43</option><option value=\"44\">44</option><option value=\"45\">45</option><option value=\"46\">46</option><option value=\"47\">47</option><option value=\"48\">48</option><option value=\"49\">49</option><option value=\"50\">50</option><option value=\"51\">51</option><option value=\"52\">52</option><option value=\"53\">53</option><option value=\"54\">54</option><option value=\"55\">55</option><option value=\"56\">56</option><option value=\"57\">57</option><option value=\"58\">58</option><option value=\"59\">59</option><option value=\"60\">60</option><option value=\"61\">61</option><option value=\"62\">62</option><option value=\"63\">63</option><option value=\"64\">64</option><option value=\"65\">65</option><option value=\"66\">66</option><option value=\"67\">67</option><option value=\"68\">68</option><option value=\"69\">69</option><option value=\"70\">70</option><option value=\"71\">71</option><option value=\"72\">72</option><option value=\"73\">73</option><option value=\"74\">74</option><option value=\"75\">75</option><option value=\"76\">76</option><option value=\"77\">77</option><option value=\"78\">78</option><option value=\"79\">79</option><option value=\"80\">80</option><option value=\"81\">81</option><option value=\"82\">82</option><option value=\"83\">83</option><option value=\"84\">84</option><option value=\"85\">85</option><option value=\"86\">86</option><option value=\"87\">87</option><option value=\"88\">88</option><option value=\"89\">89</option><option value=\"90\">90</option><option value=\"91\">91</option><option value=\"92\">92</option><option value=\"93\">93</option><option value=\"94\">94</option><option value=\"95\">95</option><option value=\"96\">96</option><option value=\"97\">97</option><option value=\"98\">98</option><option value=\"99\">99</option><option value=\"100\">100</option><option value=\"101\">101</option><option value=\"102\">102</option><option value=\"103\">103</option><option value=\"104\">104</option><option value=\"105\">105</option><option value=\"106\">106</option><option value=\"107\">107</option><option value=\"108\">108</option><option value=\"109\">109</option><option value=\"110\">110</option><option value=\"111\">111</option><option value=\"112\">112</option><option value=\"113\">113</option><option value=\"114\">114</option><option value=\"115\">115</option><option value=\"116\">116</option><option value=\"117\">117</option><option value=\"118\">118</option><option value=\"119\">119</option><option value=\"120\">120</option><option value=\"121\">121</option><option value=\"122\">122</option><option value=\"123\">123</option><option value=\"124\">124</option><option value=\"125\">125</option><option value=\"126\">126</option><option value=\"127\">127</option></select>"
    "</li><li>"
    "<input type=\"checkbox\" id=\"inspire\" name=\"inspire\""
    +inspire+
    ">"
    "<label for=\"inspire\">Check Suck</label>"
    " Suck <label for=\"suckChan\">Channel</label><select name=\"suckChan\" id=\"suckChan\">"
    "<option value=\"\" disabled selected>"
    +suckChan+
    "</option>"
    "<option value=\"1\">1</option><option value=\"2\">2</option><option value=\"3\">3</option><option value=\"4\">4</option><option value=\"5\">5</option><option value=\"6\">6</option><option value=\"7\">7</option><option value=\"8\">8</option><option value=\"9\">9</option><option value=\"10\">10</option><option value=\"11\">11</option><option value=\"12\">12</option><option value=\"13\">13</option><option value=\"14\">14</option><option value=\"15\">15</option><option value=\"16\">16</option></select>"
    "<label for=\"suckCC\">CC</label><select name=\"suckCC\" id=\"suckCC\" >"
    "<option value=\"\" disabled selected>"
    +suckCC+
    "</option>"
    "<option value=\"0\">0</option><option value=\"1\">1</option><option value=\"2\">2</option><option value=\"3\">3</option><option value=\"4\">4</option><option value=\"5\">5</option><option value=\"6\">6</option><option value=\"7\">7</option><option value=\"8\">8</option><option value=\"9\">9</option><option value=\"10\">10</option><option value=\"11\">11</option><option value=\"12\">12</option><option value=\"13\">13</option><option value=\"14\">14</option><option value=\"15\">15</option><option value=\"16\">16</option><option value=\"17\">17</option><option value=\"18\">18</option><option value=\"19\">19</option><option value=\"20\">20</option><option value=\"21\">21</option><option value=\"22\">22</option><option value=\"23\">23</option><option value=\"24\">24</option><option value=\"25\">25</option><option value=\"26\">26</option><option value=\"27\">27</option><option value=\"28\">28</option><option value=\"29\">29</option><option value=\"30\">30</option><option value=\"31\">31</option><option value=\"32\">32</option><option value=\"33\">33</option><option value=\"34\">34</option><option value=\"35\">35</option><option value=\"36\">36</option><option value=\"37\">37</option><option value=\"38\">38</option><option value=\"39\">39</option><option value=\"40\">40</option><option value=\"41\">41</option><option value=\"42\">42</option><option value=\"43\">43</option><option value=\"44\">44</option><option value=\"45\">45</option><option value=\"46\">46</option><option value=\"47\">47</option><option value=\"48\">48</option><option value=\"49\">49</option><option value=\"50\">50</option><option value=\"51\">51</option><option value=\"52\">52</option><option value=\"53\">53</option><option value=\"54\">54</option><option value=\"55\">55</option><option value=\"56\">56</option><option value=\"57\">57</option><option value=\"58\">58</option><option value=\"59\">59</option><option value=\"60\">60</option><option value=\"61\">61</option><option value=\"62\">62</option><option value=\"63\">63</option><option value=\"64\">64</option><option value=\"65\">65</option><option value=\"66\">66</option><option value=\"67\">67</option><option value=\"68\">68</option><option value=\"69\">69</option><option value=\"70\">70</option><option value=\"71\">71</option><option value=\"72\">72</option><option value=\"73\">73</option><option value=\"74\">74</option><option value=\"75\">75</option><option value=\"76\">76</option><option value=\"77\">77</option><option value=\"78\">78</option><option value=\"79\">79</option><option value=\"80\">80</option><option value=\"81\">81</option><option value=\"82\">82</option><option value=\"83\">83</option><option value=\"84\">84</option><option value=\"85\">85</option><option value=\"86\">86</option><option value=\"87\">87</option><option value=\"88\">88</option><option value=\"89\">89</option><option value=\"90\">90</option><option value=\"91\">91</option><option value=\"92\">92</option><option value=\"93\">93</option><option value=\"94\">94</option><option value=\"95\">95</option><option value=\"96\">96</option><option value=\"97\">97</option><option value=\"98\">98</option><option value=\"99\">99</option><option value=\"100\">100</option><option value=\"101\">101</option><option value=\"102\">102</option><option value=\"103\">103</option><option value=\"104\">104</option><option value=\"105\">105</option><option value=\"106\">106</option><option value=\"107\">107</option><option value=\"108\">108</option><option value=\"109\">109</option><option value=\"110\">110</option><option value=\"111\">111</option><option value=\"112\">112</option><option value=\"113\">113</option><option value=\"114\">114</option><option value=\"115\">115</option><option value=\"116\">116</option><option value=\"117\">117</option><option value=\"118\">118</option><option value=\"119\">119</option><option value=\"120\">120</option><option value=\"121\">121</option><option value=\"122\">122</option><option value=\"123\">123</option><option value=\"124\">124</option><option value=\"125\">125</option><option value=\"126\">126</option><option value=\"127\">127</option></select>"   
    "<INPUT type=\"submit\" value=\"save\">"
    "</li></ol>"
    
    "</form></body></html>";
    }
/// Fin Breath HTML content
#endif

/// Sensors
void monContentSensors(){
  
  contentSensors = 
  "<center><b>Sensors</b></center><br>"
  "<b><center>"
  " <a href = \"/\"> WiFI </a>"
  " / <a href = \"accel.html\"> Accelerometer </a>"
  " / <a href = \"blowsuck.html\"> Blow/Suck </a>"
  " / <a href = \"mode.html\"> Mode </a>"
  " / <a href = \"/update\"> Firmware </a>"
  "</b></center>"

  "</p><form method='get' action='sensorscfg'>"
      
  "<ol><li>"
  "<input type=\"checkbox\" id=\"sensor1\" name=\"sensor1\""
  +sensor1+
  ">"
  "<label for=\"sensor1\">Check Sensor1</label>"
  "<br>"
  "<label for=\"sensor1Chan\">Channel</label><select name=\"sensor1Chan\" id=\"sensor1Chan\">"
  "<option value=\"\" disabled selected>"
  +sensor1Chan+
  "</option>"
  "<option value=\"1\">1</option><option value=\"2\">2</option><option value=\"3\">3</option><option value=\"4\">4</option><option value=\"5\">5</option><option value=\"6\">6</option><option value=\"7\">7</option><option value=\"8\">8</option><option value=\"9\">9</option><option value=\"10\">10</option><option value=\"11\">11</option><option value=\"12\">12</option><option value=\"13\">13</option><option value=\"14\">14</option><option value=\"15\">15</option><option value=\"16\">16</option></select>"
  "<label for=\"sensor1CC\">CC</label><select name=\"sensor1CC\" id=\"sensor1CC\">"
  "<option value=\"\" disabled selected>"
  +sensor1CC+
  "</option>"
  "<option value=\"0\">0</option><option value=\"1\">1</option><option value=\"2\">2</option><option value=\"3\">3</option><option value=\"4\">4</option><option value=\"5\">5</option><option value=\"6\">6</option><option value=\"7\">7</option><option value=\"8\">8</option><option value=\"9\">9</option><option value=\"10\">10</option><option value=\"11\">11</option><option value=\"12\">12</option><option value=\"13\">13</option><option value=\"14\">14</option><option value=\"15\">15</option><option value=\"16\">16</option><option value=\"17\">17</option><option value=\"18\">18</option><option value=\"19\">19</option><option value=\"20\">20</option><option value=\"21\">21</option><option value=\"22\">22</option><option value=\"23\">23</option><option value=\"24\">24</option><option value=\"25\">25</option><option value=\"26\">26</option><option value=\"27\">27</option><option value=\"28\">28</option><option value=\"29\">29</option><option value=\"30\">30</option><option value=\"31\">31</option><option value=\"32\">32</option><option value=\"33\">33</option><option value=\"34\">34</option><option value=\"35\">35</option><option value=\"36\">36</option><option value=\"37\">37</option><option value=\"38\">38</option><option value=\"39\">39</option><option value=\"40\">40</option><option value=\"41\">41</option><option value=\"42\">42</option><option value=\"43\">43</option><option value=\"44\">44</option><option value=\"45\">45</option><option value=\"46\">46</option><option value=\"47\">47</option><option value=\"48\">48</option><option value=\"49\">49</option><option value=\"50\">50</option><option value=\"51\">51</option><option value=\"52\">52</option><option value=\"53\">53</option><option value=\"54\">54</option><option value=\"55\">55</option><option value=\"56\">56</option><option value=\"57\">57</option><option value=\"58\">58</option><option value=\"59\">59</option><option value=\"60\">60</option><option value=\"61\">61</option><option value=\"62\">62</option><option value=\"63\">63</option><option value=\"64\">64</option><option value=\"65\">65</option><option value=\"66\">66</option><option value=\"67\">67</option><option value=\"68\">68</option><option value=\"69\">69</option><option value=\"70\">70</option><option value=\"71\">71</option><option value=\"72\">72</option><option value=\"73\">73</option><option value=\"74\">74</option><option value=\"75\">75</option><option value=\"76\">76</option><option value=\"77\">77</option><option value=\"78\">78</option><option value=\"79\">79</option><option value=\"80\">80</option><option value=\"81\">81</option><option value=\"82\">82</option><option value=\"83\">83</option><option value=\"84\">84</option><option value=\"85\">85</option><option value=\"86\">86</option><option value=\"87\">87</option><option value=\"88\">88</option><option value=\"89\">89</option><option value=\"90\">90</option><option value=\"91\">91</option><option value=\"92\">92</option><option value=\"93\">93</option><option value=\"94\">94</option><option value=\"95\">95</option><option value=\"96\">96</option><option value=\"97\">97</option><option value=\"98\">98</option><option value=\"99\">99</option><option value=\"100\">100</option><option value=\"101\">101</option><option value=\"102\">102</option><option value=\"103\">103</option><option value=\"104\">104</option><option value=\"105\">105</option><option value=\"106\">106</option><option value=\"107\">107</option><option value=\"108\">108</option><option value=\"109\">109</option><option value=\"110\">110</option><option value=\"111\">111</option><option value=\"112\">112</option><option value=\"113\">113</option><option value=\"114\">114</option><option value=\"115\">115</option><option value=\"116\">116</option><option value=\"117\">117</option><option value=\"118\">118</option><option value=\"119\">119</option><option value=\"120\">120</option><option value=\"121\">121</option><option value=\"122\">122</option><option value=\"123\">123</option><option value=\"124\">124</option><option value=\"125\">125</option><option value=\"126\">126</option><option value=\"127\">127</option></select>"
  "<label for=\"sensor1Cal\">Calibrate</label><select name=\"sensor1Cal\" id=\"sensor1Cal\">"
  "<option value=\"calibrate\" disabled selected>"
  +sensor1Cal+
  "</option>"
  
  "</li><br><li>"
  "<input type=\"checkbox\" id=\"sensor2\" name=\"sensor2\""
  +sensor2+
  ">"
  "<label for=\"sensor2\">Check Sensor2</label>"
  "<br>"
  "<label for=\"sensor2Chan\">Channel</label><select name=\"sensor2Chan\" id=\"sensor2Chan\">"
  "<option value=\"\" disabled selected>"
  +sensor2Chan+
  "</option>"
  "<option value=\"1\">1</option><option value=\"2\">2</option><option value=\"3\">3</option><option value=\"4\">4</option><option value=\"5\">5</option><option value=\"6\">6</option><option value=\"7\">7</option><option value=\"8\">8</option><option value=\"9\">9</option><option value=\"10\">10</option><option value=\"11\">11</option><option value=\"12\">12</option><option value=\"13\">13</option><option value=\"14\">14</option><option value=\"15\">15</option><option value=\"16\">16</option></select>"
  "<label for=\"sensor2CC\">CC</label><select name=\"sensor2CC\" id=\"sensor2CC\">"
  "<option value=\"\" disabled selected>"
  +sensor2CC+
  "</option>"
  "<option value=\"0\">0</option><option value=\"1\">1</option><option value=\"2\">2</option><option value=\"3\">3</option><option value=\"4\">4</option><option value=\"5\">5</option><option value=\"6\">6</option><option value=\"7\">7</option><option value=\"8\">8</option><option value=\"9\">9</option><option value=\"10\">10</option><option value=\"11\">11</option><option value=\"12\">12</option><option value=\"13\">13</option><option value=\"14\">14</option><option value=\"15\">15</option><option value=\"16\">16</option><option value=\"17\">17</option><option value=\"18\">18</option><option value=\"19\">19</option><option value=\"20\">20</option><option value=\"21\">21</option><option value=\"22\">22</option><option value=\"23\">23</option><option value=\"24\">24</option><option value=\"25\">25</option><option value=\"26\">26</option><option value=\"27\">27</option><option value=\"28\">28</option><option value=\"29\">29</option><option value=\"30\">30</option><option value=\"31\">31</option><option value=\"32\">32</option><option value=\"33\">33</option><option value=\"34\">34</option><option value=\"35\">35</option><option value=\"36\">36</option><option value=\"37\">37</option><option value=\"38\">38</option><option value=\"39\">39</option><option value=\"40\">40</option><option value=\"41\">41</option><option value=\"42\">42</option><option value=\"43\">43</option><option value=\"44\">44</option><option value=\"45\">45</option><option value=\"46\">46</option><option value=\"47\">47</option><option value=\"48\">48</option><option value=\"49\">49</option><option value=\"50\">50</option><option value=\"51\">51</option><option value=\"52\">52</option><option value=\"53\">53</option><option value=\"54\">54</option><option value=\"55\">55</option><option value=\"56\">56</option><option value=\"57\">57</option><option value=\"58\">58</option><option value=\"59\">59</option><option value=\"60\">60</option><option value=\"61\">61</option><option value=\"62\">62</option><option value=\"63\">63</option><option value=\"64\">64</option><option value=\"65\">65</option><option value=\"66\">66</option><option value=\"67\">67</option><option value=\"68\">68</option><option value=\"69\">69</option><option value=\"70\">70</option><option value=\"71\">71</option><option value=\"72\">72</option><option value=\"73\">73</option><option value=\"74\">74</option><option value=\"75\">75</option><option value=\"76\">76</option><option value=\"77\">77</option><option value=\"78\">78</option><option value=\"79\">79</option><option value=\"80\">80</option><option value=\"81\">81</option><option value=\"82\">82</option><option value=\"83\">83</option><option value=\"84\">84</option><option value=\"85\">85</option><option value=\"86\">86</option><option value=\"87\">87</option><option value=\"88\">88</option><option value=\"89\">89</option><option value=\"90\">90</option><option value=\"91\">91</option><option value=\"92\">92</option><option value=\"93\">93</option><option value=\"94\">94</option><option value=\"95\">95</option><option value=\"96\">96</option><option value=\"97\">97</option><option value=\"98\">98</option><option value=\"99\">99</option><option value=\"100\">100</option><option value=\"101\">101</option><option value=\"102\">102</option><option value=\"103\">103</option><option value=\"104\">104</option><option value=\"105\">105</option><option value=\"106\">106</option><option value=\"107\">107</option><option value=\"108\">108</option><option value=\"109\">109</option><option value=\"110\">110</option><option value=\"111\">111</option><option value=\"112\">112</option><option value=\"113\">113</option><option value=\"114\">114</option><option value=\"115\">115</option><option value=\"116\">116</option><option value=\"117\">117</option><option value=\"118\">118</option><option value=\"119\">119</option><option value=\"120\">120</option><option value=\"121\">121</option><option value=\"122\">122</option><option value=\"123\">123</option><option value=\"124\">124</option><option value=\"125\">125</option><option value=\"126\">126</option><option value=\"127\">127</option></select>"
      
  "</li></ol>"
  //"</li><li>"
  //"<label for=\"sensor3Chan\">Channel</label><select name=\"sensor3Chan\" id=\"sensor3Chan\"><option value=\"1\">1</option><option value=\"2\">2</option><option value=\"3\">3</option><option value=\"4\">4</option><option value=\"5\">5</option><option value=\"6\">6</option><option value=\"7\">7</option><option value=\"8\">8</option><option value=\"9\">9</option><option value=\"10\">10</option><option value=\"11\">11</option><option value=\"12\">12</option><option value=\"13\">13</option><option value=\"14\">14</option><option value=\"15\">15</option><option value=\"16\">16</option></select>"
  //"<label for=\"sensor3CC\">CC</label><select name=\"sensor3CC\" id=\"sensor3CC\"><option value=\"0\">0</option><option value=\"1\">1</option><option value=\"2\">2</option><option value=\"3\">3</option><option value=\"4\">4</option><option value=\"5\">5</option><option value=\"6\">6</option><option value=\"7\">7</option><option value=\"8\">8</option><option value=\"9\">9</option><option value=\"10\">10</option><option value=\"11\">11</option><option value=\"12\">12</option><option value=\"13\">13</option><option value=\"14\">14</option><option value=\"15\">15</option><option value=\"16\">16</option><option value=\"17\">17</option><option value=\"18\">18</option><option value=\"19\">19</option><option value=\"20\">20</option><option value=\"21\">21</option><option value=\"22\">22</option><option value=\"23\">23</option><option value=\"24\">24</option><option value=\"25\">25</option><option value=\"26\">26</option><option value=\"27\">27</option><option value=\"28\">28</option><option value=\"29\">29</option><option value=\"30\">30</option><option value=\"31\">31</option><option value=\"32\">32</option><option value=\"33\">33</option><option value=\"34\">34</option><option value=\"35\">35</option><option value=\"36\">36</option><option value=\"37\">37</option><option value=\"38\">38</option><option value=\"39\">39</option><option value=\"40\">40</option><option value=\"41\">41</option><option value=\"42\">42</option><option value=\"43\">43</option><option value=\"44\">44</option><option value=\"45\">45</option><option value=\"46\">46</option><option value=\"47\">47</option><option value=\"48\">48</option><option value=\"49\">49</option><option value=\"50\">50</option><option value=\"51\">51</option><option value=\"52\">52</option><option value=\"53\">53</option><option value=\"54\">54</option><option value=\"55\">55</option><option value=\"56\">56</option><option value=\"57\">57</option><option value=\"58\">58</option><option value=\"59\">59</option><option value=\"60\">60</option><option value=\"61\">61</option><option value=\"62\">62</option><option value=\"63\">63</option><option value=\"64\">64</option><option value=\"65\">65</option><option value=\"66\">66</option><option value=\"67\">67</option><option value=\"68\">68</option><option value=\"69\">69</option><option value=\"70\">70</option><option value=\"71\">71</option><option value=\"72\">72</option><option value=\"73\">73</option><option value=\"74\">74</option><option value=\"75\">75</option><option value=\"76\">76</option><option value=\"77\">77</option><option value=\"78\">78</option><option value=\"79\">79</option><option value=\"80\">80</option><option value=\"81\">81</option><option value=\"82\">82</option><option value=\"83\">83</option><option value=\"84\">84</option><option value=\"85\">85</option><option value=\"86\">86</option><option value=\"87\">87</option><option value=\"88\">88</option><option value=\"89\">89</option><option value=\"90\">90</option><option value=\"91\">91</option><option value=\"92\">92</option><option value=\"93\">93</option><option value=\"94\">94</option><option value=\"95\">95</option><option value=\"96\">96</option><option value=\"97\">97</option><option value=\"98\">98</option><option value=\"99\">99</option><option value=\"100\">100</option><option value=\"101\">101</option><option value=\"102\">102</option><option value=\"103\">103</option><option value=\"104\">104</option><option value=\"105\">105</option><option value=\"106\">106</option><option value=\"107\">107</option><option value=\"108\">108</option><option value=\"109\">109</option><option value=\"110\">110</option><option value=\"111\">111</option><option value=\"112\">112</option><option value=\"113\">113</option><option value=\"114\">114</option><option value=\"115\">115</option><option value=\"116\">116</option><option value=\"117\">117</option><option value=\"118\">118</option><option value=\"119\">119</option><option value=\"120\">120</option><option value=\"121\">121</option><option value=\"122\">122</option><option value=\"123\">123</option><option value=\"124\">124</option><option value=\"125\">125</option><option value=\"126\">126</option><option value=\"127\">127</option></select>"
  //"</li><li>"
  //"<label for=\"sensor4Chan\">Channel</label><select name=\"sensor4Chan\" id=\"sensor4Chan\"><option value=\"1\">1</option><option value=\"2\">2</option><option value=\"3\">3</option><option value=\"4\">4</option><option value=\"5\">5</option><option value=\"6\">6</option><option value=\"7\">7</option><option value=\"8\">8</option><option value=\"9\">9</option><option value=\"10\">10</option><option value=\"11\">11</option><option value=\"12\">12</option><option value=\"13\">13</option><option value=\"14\">14</option><option value=\"15\">15</option><option value=\"16\">16</option></select>"
  //"<label for=\"sensor4CC\">CC</label><select name=\"sensor4CC\" id=\"sensor4CC\"><option value=\"0\">0</option><option value=\"1\">1</option><option value=\"2\">2</option><option value=\"3\">3</option><option value=\"4\">4</option><option value=\"5\">5</option><option value=\"6\">6</option><option value=\"7\">7</option><option value=\"8\">8</option><option value=\"9\">9</option><option value=\"10\">10</option><option value=\"11\">11</option><option value=\"12\">12</option><option value=\"13\">13</option><option value=\"14\">14</option><option value=\"15\">15</option><option value=\"16\">16</option><option value=\"17\">17</option><option value=\"18\">18</option><option value=\"19\">19</option><option value=\"20\">20</option><option value=\"21\">21</option><option value=\"22\">22</option><option value=\"23\">23</option><option value=\"24\">24</option><option value=\"25\">25</option><option value=\"26\">26</option><option value=\"27\">27</option><option value=\"28\">28</option><option value=\"29\">29</option><option value=\"30\">30</option><option value=\"31\">31</option><option value=\"32\">32</option><option value=\"33\">33</option><option value=\"34\">34</option><option value=\"35\">35</option><option value=\"36\">36</option><option value=\"37\">37</option><option value=\"38\">38</option><option value=\"39\">39</option><option value=\"40\">40</option><option value=\"41\">41</option><option value=\"42\">42</option><option value=\"43\">43</option><option value=\"44\">44</option><option value=\"45\">45</option><option value=\"46\">46</option><option value=\"47\">47</option><option value=\"48\">48</option><option value=\"49\">49</option><option value=\"50\">50</option><option value=\"51\">51</option><option value=\"52\">52</option><option value=\"53\">53</option><option value=\"54\">54</option><option value=\"55\">55</option><option value=\"56\">56</option><option value=\"57\">57</option><option value=\"58\">58</option><option value=\"59\">59</option><option value=\"60\">60</option><option value=\"61\">61</option><option value=\"62\">62</option><option value=\"63\">63</option><option value=\"64\">64</option><option value=\"65\">65</option><option value=\"66\">66</option><option value=\"67\">67</option><option value=\"68\">68</option><option value=\"69\">69</option><option value=\"70\">70</option><option value=\"71\">71</option><option value=\"72\">72</option><option value=\"73\">73</option><option value=\"74\">74</option><option value=\"75\">75</option><option value=\"76\">76</option><option value=\"77\">77</option><option value=\"78\">78</option><option value=\"79\">79</option><option value=\"80\">80</option><option value=\"81\">81</option><option value=\"82\">82</option><option value=\"83\">83</option><option value=\"84\">84</option><option value=\"85\">85</option><option value=\"86\">86</option><option value=\"87\">87</option><option value=\"88\">88</option><option value=\"89\">89</option><option value=\"90\">90</option><option value=\"91\">91</option><option value=\"92\">92</option><option value=\"93\">93</option><option value=\"94\">94</option><option value=\"95\">95</option><option value=\"96\">96</option><option value=\"97\">97</option><option value=\"98\">98</option><option value=\"99\">99</option><option value=\"100\">100</option><option value=\"101\">101</option><option value=\"102\">102</option><option value=\"103\">103</option><option value=\"104\">104</option><option value=\"105\">105</option><option value=\"106\">106</option><option value=\"107\">107</option><option value=\"108\">108</option><option value=\"109\">109</option><option value=\"110\">110</option><option value=\"111\">111</option><option value=\"112\">112</option><option value=\"113\">113</option><option value=\"114\">114</option><option value=\"115\">115</option><option value=\"116\">116</option><option value=\"117\">117</option><option value=\"118\">118</option><option value=\"119\">119</option><option value=\"120\">120</option><option value=\"121\">121</option><option value=\"122\">122</option><option value=\"123\">123</option><option value=\"124\">124</option><option value=\"125\">125</option><option value=\"126\">126</option><option value=\"127\">127</option></select>"
  "<INPUT type=\"submit\" value=\"save\">"
  "</form</body</html>";
}

     

/// Mode
void monContentMode(){
      contentMode = ""
      "<center><b>Mode</b></center><br>"
      "<b><center>"
      " <a href = \"/\"> WiFI </a>"
      " / <a href = \"accel.html\"> Accelerometer </a>"
      " / <a href = \"blowsuck.html\"> Blow/Suck </a>"
      " / <a href = \"sensors.html\"> Sensors </a>"
      " / <a href = \"/update\"> Firmware </a>"
      " / <a href = \"/calibrate\"> Calibrate </a>"
      "</b></center>"
      "<p>"
      "<ol><li>"
      "</p>"
      "<form method='get' action='modeConfig'>"
      "</li><li>"
      "<p>Mode : </p>"
      "<p>Live / Playback / Record</p>"
      "</li><li>"
      "<input type=\"radio\" id=\"live\" name=\"myMode\" value=\"checkedLive\" required "
      +checkedLive+
      ">"
      "<label for=\"live\">Live</label><br>"
      "</li><li>"
      
      "<input type=\"radio\" id=\"play\" name=\"myMode\" value=\"checkedPlay\""
      +checkedPlay+
      ">"
      "<label for=\"play\">Playback</label><br>"
      "</li><li>"
      
      "<input type=\"radio\" id=\"rec\" name=\"myMode\" value=\"checkedRecord\""
      +checkedRecord+
      ">"
      "<label for=\"rec\">Recording</label><br>"
      "</li><li>"

      "<input type=\"radio\" id=\"format\" name=\"myMode\" value=\"checkedFormatFS\""
      +checkedFormatFS+
      ">"
      "<label for=\"format\">Format FS</label><br>"
      "</li><li>"
      
      "</li><li>"
      "<p></p>"
      "<label> Delay : </label>"
      "<input type ='text' name='monDelai' placeholder= "
      + monDelai +
      ">"
      "</li><li>"
      "<label> arrayLength : </label>"
      "<input type ='text' name='arrayLength' placeholder= "
      + arrayLength +
      ">"
      "</li></ol>"
      "<INPUT type=\"submit\" value=\"save\">"
      
      "</form></body></html>";
   }
   
   ///// Fin mode /////
      

      String contentFirmware = ""
      "<center><b>Firmware</b></center><br>"
      "<b><center>"
      " <a href = \"/\"> WiFI </a>"
      " / <a href = \"accel.html\"> Accelerometer </a>"
      " / <a href = \"blowsuck.html\"> Blow/Suck </a>"
      " / <a href = \"recording.html\"> Mode </a>"
      " / <a href = \"sensors.html\"> Sensors </a>"
      "</b></center>"
       "</p><p><form method='get' action='uploadFirmware'>"
      "<INPUT type=\"submit\" value=\"Upload Firmware (NIY)\">"
      "</form></body></html>";

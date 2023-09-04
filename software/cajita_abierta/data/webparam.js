/**
 * ##copyright##
 * See LICENSE
 *
 * @author    Maxime Damecour (http://nnvtn.ca)
 * @version   0.1.0
 * @since     2019-09-01
 */

window.onload = function() {

};
// globals
var sendCMD, socket;
var ui;
var DEFAULT_WEBSOCKET_ADDR = "ws://10.0.0.42/";

function receiveWebsocketMessage (mess) {
    // console.log(mess);
    var json = 0;
    try{
        json = JSON.parse(mess);
        if(json === null){
            console.log("invalid JSON");
            console.log(mess);
        }
        else {
            // console.log(mess);
        }
    }
    catch(e){}
    if(json != 0){
        if(json.ok != undefined){
            console.log(json);
        }
        else if(json.add != undefined){
            // console.log(JSON.stringify(json));
            receiveParam(json.add);
        }
    }
}

// receive JSON data, add or update the element
function receiveParam (param) {
    // console.log("adding param "+param);
    var group, name;
    // support nesting?
    var paramObject = getParam(param.addr);
    var input = makeInputElement(param, true);
    // if input is undefined create it otherwise set its value
    if(paramObject.input === undefined) {
        paramObject.input = input;
        paramObject.div.appendChild(input);
    }
    else {
        paramObject.input.value = param.v;
        if(paramObject.type == "option"){
            paramObject.div.removeChild[1];
            paramObject.div.appendChild(input);
        }
    }
}

// creates nested structure
// should re-write it its a mess
function getParam (address) {
    if(ui === undefined) {
        ui = {};
        ui.div = document.getElementById("wrapper");
    }
    var path = address.split('/');
    var pos = ui;
    for(var i = 1; i < path.length; i++){
        if(pos[path[i]] === undefined) {
            var div = document.createElement("div");
            div.innerHTML = path[i];
            if((i === path.length - 1)) {
                div.className = "widget";
            } else {
                div.className = "container";
            }
            pos.div.appendChild(div);
            pos[path[i]] = {};
            pos[path[i]].div = div;
        }
        pos = pos[path[i]];
    }
    return pos;
}

function hide(thing) {
    // console.log(thing);
    if(thing.div.className === "widget") {
        if(thing.div.style.display === "none") thing.div.style.display === "block";
        else thing.div.style.display = "none";
    }
}

// wrapper to get the correct field depending on input type
function getInputValue(input){
    if(input.type === "checkbox"){
        return input.checked ? 1 : 0;
    }
    else if(input.tagName === "SELECT"){
        return input.options[input.selectedIndex].value;
    }
    else {
        return input.value;
    }
}

function enableInputs() {
    var inputDivs = document.getElementsByClassName("widget");
    Array.from(inputDivs).forEach(function(div){
        div.lastChild.disabled = false;
    });
}

function makeInputElement(param, makeCallback){
    var input;
    switch (param.type) {
        case "toggle":
            input = makeToggle(param, makeCallback);
            break;
        case "color":
            input = makeColor(param, makeCallback);
            break;
        case "text":
            input = makeText(param, makeCallback);
            break;
        case "i_slider":
            input = makeIntSlider(param, makeCallback);
            break;
        case "f_slider":
            input = makeFloatSlider(param, makeCallback);
            break;
        case "bang":
            input = makeBang(param, makeCallback);
            break;
        case "option":
            input = makeSelect(param, makeCallback);
            break;
        case "number":
            input = makeNumber(param, makeCallback);
            break;
        case "file":
            div.innerHTML = "file upload not supported yet";
            // input = makeFileUpload(param, makeCallback);
            break;
        default:
            console.log("unknown control type "+param);
    }
    return input;
}

/*
* /////////////////////////////////////////////////////////////
* make inputs
* /////////////////////////////////////////////////////////////
*/

function makeToggle(param, makeCallback){
    var input = document.createElement("input");
    input.setAttribute("type", "checkbox");
    input.checked = param.v;
    if(makeCallback){
        input.onchange = function(){
            var mess = {};
            mess.addr = param.addr;
            mess.v = input.checked ? 1 : 0;
            sendCMD(JSON.stringify(mess));
        };
    }
    return input;
}

function makeText(param, makeCallback){
    var input = document.createElement("input");
    input.setAttribute("type", "text");
    input.value = param.v;
    if(makeCallback){
        input.oninput = function(){
            var mess = {};
            mess.addr = param.addr;
            mess.v = input.value;
            sendCMD(JSON.stringify(mess));
        };
    }
    return input;
}

function makeColor(param, makeCallback){
    var input = document.createElement("input");
    input.setAttribute("type", "color");
    input.value = "#"+Number(param.v).toString(16);
    if(makeCallback){
        input.oninput = function(){
            var str = input.value;
            var mess = {};
            mess.addr = param.addr;
            mess.v = parseInt(str.replace('#',''), 16);
            sendCMD(JSON.stringify(mess));
        };
    }
    return input;
}

function makeIntSlider(param, makeCallback){
    var input = document.createElement("input");
    input.setAttribute("type", "range");
    input.setAttribute("min", param.min);
    input.setAttribute("max", param.max);
    if(makeCallback){
        input.oninput = function(){
            var mess = {};
            mess.addr = param.addr;
            mess.v = input.value;
            sendCMD(JSON.stringify(mess));
        };
    }
    input.value = param.v;
    return input;
}

function makeFloatSlider(param, makeCallback) {
    var input = makeIntSlider(param, makeCallback);
    input.setAttribute("step", "any");
    return input;
}

function makeBang(param, makeCallback){
    var input = document.createElement("input");
    input.setAttribute("type", "button");
    if(makeCallback){
        input.onclick = function(){
            var mess = {};
            mess.addr = param.addr;
            mess.v = input.value;
            sendCMD(JSON.stringify(mess));
        };
    }
    return input;
}

function makeSelect(param, makeCallback){
    var input = document.createElement("select");
    // console.log(param.options);
    for(var x in param.options){
        if(param.options[x] != ''){
            var _option = document.createElement("option");
            _option.text = param.options[x];
            input.add(_option);
            if(param.v === param.options[x]) input.value = param.options[x];
        }
    }
    if(makeCallback){
        input.onchange = function(){
            var mess = {};
            mess.addr = param.addr;
            mess.v = getInputValue(input);
            sendCMD(JSON.stringify(mess));
        };
    }
    return input;
}

function makeNumber(param, makeCallback){
    var input = document.createElement("input");
    input.setAttribute("type", "number");
    input.setAttribute("min", param.min);
    input.setAttribute("max", param.max);
    if(makeCallback){
        input.onchange = function(){
            var mess = {};
            mess.addr = param.addr;
            mess.v = input.value;
            sendCMD(JSON.stringify(mess));
        };
    }
    input.value = param.v;
    return input;
}

function grayout(){
    var widgets = document.getElementsByClassName("widget");
    for(var i in widgets) {
        widgets[i].firstElementChild.disabled = true;
        widgets[i].style.color = "#010000";
    }
}

// ES6 code
function throttled(delay, fn) {
    var lastCall = 0;
    return function (arguments) {
        var now = (new Date()).getTime();
        if (now - lastCall < delay) {
            return;
        }
        lastCall = now;
        return fn(arguments);
    }
}

/*
* /////////////////////////////////////////////////////////////
* webSocket!
* /////////////////////////////////////////////////////////////
*/

// make a websocket
function makeSocket(_adr) {
    var socket = new WebSocket(_adr);
    socket.onmessage = function (evt) {
        receiveWebsocketMessage(evt.data);
        document.getElementById("logline").innerHTML = evt.data;
    };
    // https://stackoverflow.com/questions/4812686/closing-websocket-correctly-html5-javascript
    window.onbeforeunload = function() {
        socket.onclose = function () {}; // disable onclose handler first
        socket.close();
    };
    // this needs to be adapted with the form
    // document.getElementById("reload").onclick = function() {
    //     socket.onclose = function () {}; // disable onclose handler first
    //     socket.close();
    //     window.location.reload(true);
    // };
    return socket;
}

function connect() {
    // clear current model
    var oldiv = document.getElementById("wrapper");
    while(oldiv.firstChild) {
        oldiv.removeChild(oldiv.firstChild);
    }
    if(ui) {
        ui = undefined;
    }

    var _addr = document.getElementById("ipaddr").value;
    _addr = "ws://"+_addr+"/";
    console.log("[webparam] connecting to :"+_addr);
    // make a function to send commands through a websocket
    sendCMD = (function () {
        var socket, ping;
        // _addr = prompt("connect to", DEFAULT_WEBSOCKET_ADDR);
        if (_addr != null) socket = makeSocket(_addr);
        else socket = makeSocket(DEFAULT_WEBSOCKET_ADDR);

        ping = setInterval(function() {
            var msg = {};
            msg.ping = 1;
            sendCMD(JSON.stringify(msg));
            if(socket.readyState === 2 || socket.readyState === 3) {
                clearInterval(ping);
                console.log("[webparam]lost connection");
                grayout();
            }
        }, 1000);

        return function (_cmd) {
            if( _cmd.localeCompare('{"ping":1}') ){
                document.getElementById("logline").innerHTML = _cmd;
            }
            if(socket.readyState === 1) socket.send(_cmd);
        };
    })();

}

function ipEnterKeyDetect(event) {
    //See notes about 'which' and 'key'
    if (event.keyCode == 13) {
        connect();
    }
}

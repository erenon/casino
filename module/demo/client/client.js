//var socket = new io.Socket(null, {port: 3000, rememberTransport: false});


var socket = io.connect(null, {port: 3000, rememberTransport: true});

socket.on('connect', function(event) {
    socket.emit('register_sid', {
        sid: $.cookie('casino-session')
    });
});

socket.on('notify', function(event) {
    console.log(event);
});

socket.on('pick_action', function(callback) {
    callback(5);
});

/*socket.on('game_start', function(event) {
    console.log(event);
});

socket.on('player_joined', function(obj){
    console.log(obj);
});*/

/*socket.send('client hello');*/

var test = (function() {
    
    return {
        init: function() {
            $('a#start').click(function(){
                socket.emit('start_game');
            });
        }
    };
}());

$(document).ready(function() {
    test.init();
});

var socket = io.connect(null, {port: 8000, rememberTransport: true});

socket.on('connect', function(event) {
    socket.emit('register_sid', {
        sid: $.cookie('casino-session-test')
    });
});

$(document).ready(function() {
    $('#whoami').bind('click', function() {
        console.log('sending whoami...');
        socket.emit('whoami');
    });
});

function setupi18n() {
    var dictionary = {
        'Start Game' : 'Start Game'
    };
    
    $.i18n.setDictionary(dictionary);
}

function setupSocket() {
    var socket = socketio.connect();
    
    socket.on('connect', function(event) {
        socket.emit('register_sid', {
            sid: $.cookie('casino-session')
        });
    });
    
    return socket;
}

$(document).ready(function() {
    var socket;

    setupi18n();
    socket = setupSocket();
    

    unoTable.init(
        $('#unoTable'),
        {
            socket: socket,
            cardBuilder: cardBuilder
        }
    );
});

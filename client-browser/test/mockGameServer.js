var port = 3001,
    io = require('socket.io').listen(port)
    ;


/*
 * socket.io setup
 */

//io.set('log level', 2);

console.log('Socket.IO testGameServer listens on port ' + port);

io.sockets.on('connection', function(socket) {
    console.log('Client connected to testGameServer');
    
    // TODO replay game
    socket.emit('player_joined', {
        player: {
            name: 'oppositeLeft'
        }
    });
    
    socket.emit('player_joined', {
        player: {
            name: 'oppositeTop'
        }
    });
    
    socket.emit('player_joined', {
        player: {
            name: 'oppositeRight'
        }
    });
});

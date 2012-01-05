var app = require('express').createServer(),
    io,
    port = 3000
    ;

app.listen(port);
console.log('App listens on port ' + port);

/*
 * socket.io setup
 */

io = require('socket.io').listen(app);
//io.set('log level', 2);

io.sockets.on('connection', function(socket) {
    console.log('socket connected');
});
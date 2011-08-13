var express = require('express'),
    app = express.createServer(),
    fs = require('fs'),
    assert = require('assert'),
    casino = require('../lib/casino'),
    Player = require('../lib/player').Player,
    players = require('../lib/player').players
    ;


/* 
 * app config 
 */

app.set('view engine', 'jade');

app.use(express.cookieParser());
app.use(express.session({ 
    secret: '16dawdaw4+8aw6.-51dagaw5',
    key: 'casino-session',
    cookie: { path: '/', httpOnly: false, maxAge: 14400000 }
}));


/*
 * routes
 */

app.get('/', function(req, res) {   
    res.render('index', {});
});

/* serve client javascript */
app.get('/client/*.js', function(req, res) {
    var filename = './client/' + req.params[0] + '.js';
    
    res.header("Content-Type", "text/javascript");
    
    fs.readFile(filename, function(err, data) {
        if (err) {
            throw err;
        }
        res.end(data);
    });
});

app.get('/client/*.css', function(req, res) {
    var filename = './client/' + req.params[0] + '.css';
    
    res.header("Content-Type", "text/css");
    
    fs.readFile(filename, function(err, data) {
        if (err) {
            throw err;
        }
        res.end(data);
    });
});

console.log("Server is now listening on port 3000");
app.listen(3000);


/*
 * socket.io setup
 */

var io = require('socket.io').listen(app);

io.set('log level', 2);

io.sockets.on('connection', function(socket) {
    socket.on('register_sid', function(data) {
        assert.ok(data.sid);
        // register socket id <-> session id
        players.sessionToSocket[data.sid] = socket;
        players.socketToSession[socket.id] = data.sid;
    });    
    
    socket.on('start_game', function(data) {
        var game = new casino.Game(4),
            session_id = players.socketToSession[socket.id],
            p;
            
        try {
            p = new Player(session_id);
        } catch (e) {
            console.log(e);
            return;
        }
        
        game.joinPlayer(p);
        game.addBot(3);
        game.start();
    });
});

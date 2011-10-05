var express = require('express'),
    app = express.createServer(),
    fs = require('fs'),
    assert = require('assert'),
    casino = require('../lib/casino'),
    Player = require('../lib/player').Player,
    playerFactory = require('../lib/player'),
    gameFactory = require('../lib/game')
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

/* serve client resources */
{
    var serveFile = function(res, file, contentType) {
        if (contentType) {       
            res.header("Content-Type", contentType);
        }
        
        fs.readFile(file, function(err, data) {
            if (err) {
                /** @todo remove this throw, log instead in prod */
                throw err;
            }
            res.end(data);
        });
    };
    
    app.get('/client/*.js', function(req, res) {
        var filename = './client/js/' + req.params[0] + '.js';        
        serveFile(res, filename, "text/javascript");
    });
    
    app.get('/client/*.css', function(req, res) {
        var filename = './client/css/' + req.params[0] + '.css';
        serveFile(res, filename, "text/css");
    });
    
    app.get('/client/*.png', function(req, res) {
        var filename = './client/png/' + req.params[0] + '.png';
        serveFile(res, filename, "image/png");
    });

}

console.log("Server is now listening on port 3000");
app.listen(3000);


/*
 * socket.io setup
 */

var io = require('socket.io').listen(app);

//io.set('log level', 2);

io.sockets.on('connection', function(socket) {
    var player;
    
    socket.on('register_sid', function(data) {
        assert.ok(data.sid);
       
        // create player if not yet created
        if (player == undefined) {
            try {
                player = 
                    playerFactory.playerList.getPlayerBySessionId(data.sid)
                    || playerFactory.createPlayer(socket);
            } catch (e) {
                console.log('player: ', player);
                console.log(e);
            }
        }
    });    
    
    socket.on('create_game', function(options) {
        var maxPlayerCount;
            
        options = options || {};
        
        if (typeof options.maxPlayerCount == 'number') {
            maxPlayerCount = options.maxPlayerCount;
        } else {
            maxPlayerCount = 4;
        }
        
        gameFactory.createGame(maxPlayerCount);
    });
    
    socket.on('list_games', function(callback) {
        callback(gameFactory.getNotStartedGames());
    });
    
    socket.on('start_instant_game', function(data) {
        var game = gameFactory.createGame(4);
        
        assert.ok(player);
        
        if (player) {
            game.joinPlayer(player);
            game.addBot(3);
            game.start();
        }
    });
});

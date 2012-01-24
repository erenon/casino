var app = require('express').createServer(),
    fs = require('fs'),
    casino = require('../../lib/casino'),
    playerFactory = require('../../lib/player'),
    gameFactory = require('../../lib/game'),
    io,
    port = 3000
    ;

/* 
 * app config 
 */

app.set('view engine', 'jade');

app.listen(port);
console.log('App listens on port ' + port);

/*
 * routes
 */

app.get('/', function(req, res) {   
    res.render('index', {});
});

/* serve client resources */
(function() {
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

}());


/*
 * socket.io setup
 */

io = require('socket.io').listen(app);
//io.set('log level', 2);

io.sockets.on('connection', function(socket) {
    var player,
        game;
        
    console.log('socket connected');
    
    player = playerFactory.createPlayer(socket);
    game = gameFactory.createGame(4);
    
    game.joinPlayer(player);
    game.addBot(3);
    game.start();
});

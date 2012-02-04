var port = 3001,
    io = require('socket.io').listen(port),
    
    nameManager = require('../src/player/NameManager')(),
    Game = require('../src/game/Game'),
    RobotEasyPlayer = require('../src/player/RobotEasyPlayer'),
    SocketPlayer = require('../src/player/SocketPlayer')
    ;


/*
 * socket.io setup
 */

//io.set('log level', 2);

console.log('Socket.IO testGameserver listens on port ' + port);

io.sockets.on('connection', function(socket) {
    console.log('Client connected to testGameServer');
    
    var game = Game({
            config: {
                initialHandSize: 7,
                unoPenalty: 2
            }
        }),
        player = SocketPlayer({
            game: game,
            socket: socket,
            name: 'player'    
        }),
        botA = RobotEasyPlayer({
            game: game,
            name: nameManager.getAnonName()
        }),
        botB = RobotEasyPlayer({
            game: game,
            name: nameManager.getAnonName()
        }),
        botC = RobotEasyPlayer({
            game: game,
            name: nameManager.getAnonName()
        })
        ;
        
    game.addPlayer(player);   
    game.addPlayer(botA);
    game.addPlayer(botB);
    game.addPlayer(botC);
    
    game.start();     
});
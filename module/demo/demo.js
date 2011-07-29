var casino = require('../lib/casino'),
    player = require('../lib/player.js'),
    player_a = new player(123),
    //player_b = new player(456),
    game = new casino.game(4);
    
        
game.joinPlayer(player_a);
//game.joinPlayer(player_b);


game.addBot(3);
game.start();
game.dispose();

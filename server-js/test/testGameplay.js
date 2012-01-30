var Game = require('../src/game/Game'),
    Player = require('../src/player/Player'),
    RobotEasyPlayer = require('../src/player/RobotEasyPlayer'),
    nameManager = require('../src/player/NameManager')(),
    game,
    alice,
    bob,
    charlie
    ;
    
game = Game({
    config: {
        initialHandSize: 7
    }
});

alice = RobotEasyPlayer({
    game: game,
    name: nameManager.getAnonName()
});
bob = RobotEasyPlayer({
    game: game,
    name: nameManager.getAnonName()
});
charlie = RobotEasyPlayer({
    game: game,
    name: nameManager.getAnonName()
});

game.addPlayer(alice);
game.addPlayer(bob);
game.addPlayer(charlie);

game.start();

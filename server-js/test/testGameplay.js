var Game = require('../src/game/Game'),
    Player = require('../src/player/Player'),
    RobotEasyPlayer = require('../src/player/RobotEasyPlayer'),
    nameManager = require('../src/player/NameManager')(),
    game,
    alice,
    bob,
    charlie,
    delta
    ;
    
game = Game({
    config: {
        initialHandSize: 7,
        unoPenalty: 2
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

delta = RobotEasyPlayer({
    game: game,
    name: nameManager.getAnonName()
});

game.addPlayer(alice);
game.addPlayer(bob);
game.addPlayer(charlie);
game.addPlayer(delta);

game.start();

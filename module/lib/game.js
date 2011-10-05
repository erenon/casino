var 
NativeGame = require('./casino').Game,

gameList = (function() {
    var list = [];
    
    return {
        addGame : function(game) {
            list.push({
                game: game
            });
        },
        
        getNotStartedGames : function() {
            var notStarted = [];
            
            for (var i = list.length - 1; i >= 0; i--){
                if (list[i].game.isStarted() === false) {
                    notStarted.push({
                        maxPlayerCount : list[i].game.getMaxPlayerCount()
                    });
                }
            };
            
            return notStarted;
        }      
    };
}()),

createGame = function(maxPlayerCount) {
    var game = {},
        nativeGame = new NativeGame(maxPlayerCount),
        isStarted = false
        ;
    
    // methods
    
    game.joinPlayer = function(player) {
        try {
            nativeGame.joinPlayer(player);
        } catch (e) {
            console.log(e);
        }
    };
    
    game.addBot = function(count) {
        try {
            nativeGame.addBot(count);
        } catch (e) {
            console.log(e);
        }
    };
    
    game.start = function() {
        nativeGame.start();
        isStarted = true;
    };
    
    game.isStarted = function() {
        return isStarted;
    };
    
    game.getMaxPlayerCount = function() {
        return maxPlayerCount;
    };
    
    // add game to the list
    gameList.addGame(game);
    
    return game;
}
;

module.exports.createGame = createGame;
module.exports.getNotStartedGames = gameList.getNotStartedGames;

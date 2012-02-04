var
EventReceiver = require('./EventReceiver');
Player = function(options, player) {
var blockFlag = false,
    unoFlag = false
    ;
        
    player = player || {};
    EventReceiver(player);
    
    player.on('playerJoined', function(data) {
        //console.log(data);
    });
    
    player.on('gameStarted', function(data) {
        console.log(data); 
    });
    
    player.on('gameEnded', function(data) {
        console.log(data.winner.name); 
    });    
    
    player.on('cardAdded', function(data) {
        //console.log(player.name, data);
        player.hand.push(data.card); 
    });
    
    player.on('cardPlayed', function(data) {
        //console.log(data.player.name + ' played ' + data.card);
    });
    
    player.on('playerGotCard', function(data) {
        //console.log(data.player.name + ' got ' + data.cardCount + ' card(s)'); 
    });
    
    player.on('playerTurn', function(data) {
       //console.log(player.name + ': turn of ' + data.player.name + ' (cc: ' +data.player.getCardCount()+ ')'); 
    });
    
    player.game = options.game;
    player.name = options.name;
    player.hand = [];
    
    player.getCardCount = function() {
        return player.hand.length;
    };
    
    player.block = function() {
        if (arguments[0] !== undefined) {
            blockFlag = arguments[0];
        }
        
        return blockFlag;
    };
    
    player.uno = function() {
        if (arguments[0] !== undefined) {
            unoFlag = arguments[0];
            if (arguments[0] === true) {
                player.game.sayUno(player);
            }
        }
        
        return unoFlag;        
    };

    
    return player;
}
;

module.exports = Player;

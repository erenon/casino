var
EventReceiver = require('./EventReceiver');
Player = function(options, player) {
/*var hand = []
    ;*/
        
    player = player || {};
    EventReceiver(player);
    
    player.on('playerJoined', function(data) {
        //console.log(data);
    });
    
    player.on('gameStarted', function(data) {
        console.log(data); 
    });
    
    player.on('cardAdded', function(data) {
        console.log(player.name, data);
        player.hand.push(data.card); 
    });
    
    player.on('playerGotCard', function(data) {
        //console.log(data); 
    });
    
    player.game = options.game;
    player.name = options.name;
    player.hand = [];
    
    return player;
}
;

module.exports = Player;

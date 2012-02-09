var
Player = require('./Player'),
SocketPlayer = function(options, player) {
var socket = options.socket,
    filterPlayerObject = function(fullPlayer) {
        var filteredPlayer = {}
            ;
            
        filteredPlayer.name = fullPlayer.name;
        
        return filteredPlayer;
    },
    
    filterCardObject = function(fullCard) {
        var filteredCard = {}
            ;
            
        filteredCard.color = fullCard.color;
        filteredCard.value = fullCard.value;
        
        if (fullCard.pickedColor) {
            filteredCard.pickedColor = fullCard.pickedColor;
        }
        
        return filteredCard;
    }
    ;
    
    player = player || {};
    Player(options, player);
    
    player.on('playerJoined', function(data) {
        var event = {};
        event.player = filterPlayerObject(data.player);
        
        socket.emit('playerJoined', event);
    });
    
    player.on('gameStarted', function(data) {
        var event = {};
        event.firstCard = filterCardObject(data.firstCard);
        
        socket.emit('gameStarted', event); 
    });
    
    player.on('gameEnded', function(data) {
        var event = {};
        event.winner = filterPlayerObject(data.winner);
        
        socket.emit('gameEnded', event); 
    });    
    
    player.on('cardAdded', function(data) {
        var event = {};
        event.card = filterCardObject(data.card);
        
        socket.emit('cardAdded', event);
    });
    
    player.on('cardPlayed', function(data) {
        var event = {};
        event.card = filterCardObject(data.card);
        event.player = filterPlayerObject(data.player);
        
        socket.emit('cardPlayed', event);
    });
    
    player.on('playerGotCard', function(data) {
        var event = {};
        event.player = filterPlayerObject(data.player);
        event.cardCount = data.cardCount;
        
        socket.emit('playerGotCard', event);
    });
    
    player.on('playerTurn', function(data) {
        var event = {};
        event.player = filterPlayerObject(data.player);
        
        socket.emit('playerTurn', event);
    });   
    
    socket.on('playCard', function(data) {
        var card = data.card,
            pickedCard,
            successfulPlay = false,
            i
            ;
            
        // remove card from hand
        for (i = 0; i < player.hand.length; i++) {
            if (player.hand[i].color === card.color
            &&  player.hand[i].value === card.value) {
                // the card object sent through the socket
                // is only a partial copy of the original card
                pickedCard = player.hand.splice(i,1)[0];
                
                if (card.pickedColor) {
                    pickedCard.pickedColor = card.pickedColor;
                }
                
                // we want remove one card only
                // there may be same cards in hand
                break;
            }
        }            
            
        successfulPlay = player.game.playCard(player, pickedCard);
        if (!successfulPlay) {
            player.hand.push(pickedCard);
        }
    });
    
    socket.on('playDraw', function() {
        player.game.playDraw(player);
    });
    
    socket.on('sayUno', function() {
        player.uno(true);
    });
    
    return player; 
}

module.exports = SocketPlayer;

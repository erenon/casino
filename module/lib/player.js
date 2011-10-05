var 
NativePlayer = require('./casino').Player,

createPlayer = function(socket) {
    var player = {},
        nativePlayer = new NativePlayer(player);
        
    /** @todo get rid of bind methods to player.nativePlayer */
    /**
     * the NativePlayer will bind native methods
     * to the returned object that uses 
     * the callbacks of the given object (this).
     */
    player.nativePlayer = nativePlayer;
    
    if (!socket) {
        throw {
            name: 'InvalidArgument',
            message: 'Must provide a socket to create a player'
        };
    }
    
    player.notify = function(event) {
        var type = event.event_type;
        delete event.event_type;
        socket.emit(type, event);
        
        /** @todo remove debug messages */
        if (type == 'card_played') {
            console.log(
                event.played_by.name,
                ' : ',
                event.played_card.value, 
                ' / ', 
                event.played_card.color
            );
        } else if (type == 'draw_card') {
            console.log(
                event.player.name,
                ' : draws ',
                event.card_count,
                ' card(s)'
            );
        }
    };
    
    player.addAction = function(action) {
        //console.log('action added: ', action);
        socket.emit('action_added', action);
    };
    
    player.takeAction = function(nativePlayerCallback, nativePlayerArguments, clientCallback) {
        var isValid = true,
            message;
        
        /** @todo remove debug messages */ 
        console.log('-------8<--------');
        console.log('player : ', nativePlayerArguments);
    
        try {
            nativePlayer[nativePlayerCallback](nativePlayerArguments);
        } catch (e) {
            isValid = false;
            message = e.message;
        }
        
        clientCallback(isValid, message);        
    };
    
    socket.on('play_card', function(card, statusCallback) {
        player.takeAction('playCard', card, statusCallback);
    });
    
    socket.on('play_draw', function(statusCallback) {
        player.takeAction('draw', null, statusCallback);  
    });
    
    socket.on('say_uno', function() {
        nativePlayer.sayUno();
    });
    
    return player;
},

playerList = (function() {
    var players = {};
    
    return {
        addPlayer : function(player, sessionId) {
            players[sessionId] = player;   
        },
        
        getPlayerBySessionId : function(sessionId) {
            return players[sessionId];   
        }
    };
}());

module.exports.createPlayer = createPlayer;
module.exports.playerList = playerList;
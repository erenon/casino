var NativePlayer = require('./casino').Player;

var Player = function(session_id) {
    this.session_id = session_id;
    var that = this,
        socket = players.sessionToSocket[session_id];
        
    if (!socket) {
        throw {
            name: 'OutOfBounds',
            message: 'Given session id is not found in session to socket map'
        };
    }
    
    this.notify = function(event) {
        var type = event.event_type;
        delete event.event_type;
        socket.emit(type, event);
    };
    
    this.addAction = function(action) {
        //console.log('action added: ', action);
        socket.emit('action_added', action);
    };
    
    this.takeAction = function(nativePlayerCallback, nativePlayerArguments, clientCallback) {
        var isValid = true,
            message;
    
        try {
            this.nativePlayer[nativePlayerCallback](nativePlayerArguments);
        } catch (e) {
            isValid = false;
            message = e.message;
        }
        
        clientCallback(isValid, message);        
    };
    
    socket.on('play_card', function(card, statusCallback) {
        that.takeAction('playCard', card, statusCallback);
    });
    
    socket.on('play_draw', function(statusCallback) {
        that.takeAction('draw', null, statusCallback);  
    });
    
    /**
     * the NativePlayer will bind native methods
     * to the returned object that uses 
     * the callbacks of the given object (this).
     */
    this.nativePlayer = new NativePlayer(this);
};

var players = {};
players.sessionToSocket = [];
players.socketToSession = [];
    
module.exports.Player = Player;
module.exports.players = players;

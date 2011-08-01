var NativePlayer = require('./casino').Player;

var Player = function(session_id) {
    this.session_id = session_id;
    var that = this,
        socket = players.sessionToSocket[that.session_id],
        native_player;
        
    this.registerCallback = function(cb_name, cb) {
        console.log('register cb: ', cb_name);
        this[cb_name] = cb;
    };
    
    this.notify = function(event) {
        var type = event.event_type;
        delete event.event_type;
        socket.emit(type, event);
    };
    
    this.addAction = function(action) {
        //console.log('action added: ', action);
        socket.emit('action_added', action);
    };
    
    socket.on('play_card', function(card) {
        console.log(card);
        try {
            native_player.playCard(card);
        } catch (e) {
            socket.emit('invalid_move', e.message);
        }
    });
    
    socket.on('play_draw', function() {
        try {
            native_player.draw();
        } catch (e) {
            socket.emit('invalid_move', e.message);
        }    
    });
    
    /**
     * the NativePlayer will bind native methods
     * to the given object (this).
     */
    native_player = new NativePlayer(this);
    
    this.native_player = native_player;
};

var players = {};
players.sessionToSocket = [];
players.socketToSession = [];
    
module.exports.Player = Player;
module.exports.players = players;

var Player = function(session_id) {
    this.session_id = session_id;
    var that = this;
    
    this.socket = function() {
        return players.sessionToSocket[that.session_id];
    };
    
    this.notify = function(event) {
        var socket = that.socket();
        socket.emit('notify', event);
    };
    
    this.pickAction = function(callback) {
        console.log('picking action...');
        
        var socket = that.socket();
        socket.emit('pick_action', function(picked_index) {
            console.log(picked_index);
            
            try {
                callback(picked_index);
            } catch (e) {
                console.log('failed to call javascript player action pick cb');
            }
        });
        
        console.log('+-----+');
        return 0;
    };
};

var players = {};
players.sessionToSocket = [];
players.socketToSession = [];
    
module.exports.Player = Player;
module.exports.players = players;

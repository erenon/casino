var
PlayerCollection = function() {
var playerCollection = {},
    players = [],
    currentIndex,
    nextPlayerOffset = 1,
    getNextPlayerIndex = function() {
        var nextPlayerIndex = currentIndex + nextPlayerOffset,
            mod = players.length
            ;
        
        // % is the remainder operator in javascript, not the modulo
        // we have to do this little trick to handle the
        // 0 -> -1 transition.
        return (((nextPlayerIndex % mod) + mod) % mod);
    }
    ;
    
    playerCollection.addPlayer = function(player) {
        players.push(player);
    };
    
    playerCollection.reset = function() {
        currentIndex = 0;
    };
    
    playerCollection.getCurrentPlayer = function() {
        return players[currentIndex];
    };
    
    playerCollection.getNextPlayer = function() {
        return players[getNextPlayerIndex()];    
    };
    
    playerCollection.next = function() {
        currentIndex = getNextPlayerIndex();
        return players[currentIndex];
    };
    
    playerCollection.reverseTurn = function() {
        nextPlayerOffset *= (-1);
    };
    
    playerCollection.notifyAll = function(event, data) {
        var i;
        for (i = 0; i < players.length; i++) {
            players[i].notify(event, data);
        }
    };
    
    playerCollection.notifyOthers = function(event, data, player) {
        var i;
        for (i = players.length - 1; i >= 0; i--) {
            if (players[i] !== player) {
                players[i].notify(event, data);
            }
        }        
    };
    
    playerCollection.length = function() {
        return players.length;
    };
    
    
    playerCollection.reset();
    
    return playerCollection;
}
;

module.exports = PlayerCollection;

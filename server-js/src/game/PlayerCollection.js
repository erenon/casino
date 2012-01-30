var
PlayerCollection = function() {
var playerCollection = {},
    players = [],
    currentIndex 
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
    
    playerCollection.next = function() {
        currentIndex = (currentIndex + 1) % players.length;
        return players[currentIndex];
    };
    
    playerCollection.notifyAll = function(event, data) {
        var i;
        for (i = players.length - 1; i >= 0; i--) {
            players[i].notify(event, data);
        }
    };
    
    playerCollection.notifyOthers = function(event, data, player) {
        var i;
        for (i = players.length - 1; i >= 0; i--) {
            if (players[i] != player) {
                players[i].notify(event, data);
            }
        }        
    };
    
    playerCollection.length = function() {
        return players.length;
    }
    
    
    playerCollection.reset();
    
    return playerCollection;
}
;

module.exports = PlayerCollection;

var
SeatManager = function(options) {
var $ = options.$,
    pubsub = options.pubsub,
    OppositePlayer = options.OppositePlayer,
    seats = options.seats,
    defaultPlayerOptions = options.defaultPlayerOptions,
    currentSeatIndex = 0,
    getSeat = function() {
        var seat;
        
        if (currentSeatIndex < seats.length) {
            // I was tempted here to do this in one statement
            // by post incrementing currentSeatIndex while indexing the array
            // but I'm strong in the faith.
            seat = seats[currentSeatIndex];
            currentSeatIndex++;
            return seat;    
        } else {
            return undefined;
        }
    },
    addPlayer = function(playerOptions) {
        // merge default, seat, player options.
        var options = {}
            ;
            
        $.extend(options, 
                 defaultPlayerOptions, 
                 getSeat(), 
                 playerOptions
        );
        
        return OppositePlayer(options);
    }
    ;
    
    pubsub.on('playerJoined', function(event) {
        addPlayer({
            name: event.player.name
        });
    });
    
}
;

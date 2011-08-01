var socket = io.connect(null, {port: 3000, rememberTransport: true});

socket.on('connect', function(event) {
    socket.emit('register_sid', {
        sid: $.cookie('casino-session')
    });
});

/*socket.on('notify', function(event) {
    console.log(event);
    
    switch (event.event_type) {
        case 'players_turn':
            if (event.player.name = player.getName()) {
                console.log('your turn');
            }
            break;
        default:
            break;
    };
});*/

socket.on('game_start', function(event) {
    console.log(event);
    table.addInfo('The Game has begun. First card is: ' 
        + event.first_card.color
        + ' / '
        + event.first_card.value
    );
});

socket.on('action_added', function(action) {
    //console.log(action);
    table.addPlayerCard(action);
});

socket.on('players_turn', function(event) {
    var name = event.player.name;
    if (name == player.getName()) {
        table.addInfo('Your turn');
    } else {
        table.addInfo(name + '\'s turn');
    }
});

socket.on('invalid_move', function(message) {
    table.addInfo('Invalid move: ' + message);
});

socket.on('card_played', function(event) {
    var card = event.played_card,
        name = event.played_by.name;
    table.addInfo('Card: '+card.color+' / '+card.value+' played by '+name);
});

/*socket.on('pick_action', function(callback) {
    callback(5);
});*/

/*socket.on('game_start', function(event) {
    console.log(event);
});

socket.on('player_joined', function(obj){
    console.log(obj);
});*/

var table = function() {
    var areas,
    
    cardBuilder = function(card) {
        var div = $('<div></div>');
        div.html('color: ' + card.color + ' / value: ' + card.value);
        div.data('card', card);
        div.click(function(){
            socket.emit('play_card', div.data('card'));
            div.closest('li').remove();
        });
        
        return div;
    };
    
    
    
    return {
        setAreas: function(a) {
            areas = a;
        },
        
        addPlayerCard: function(card) {
            var li = $('<li></li>');
            li.html(cardBuilder(card));
            areas.playerCards.append(li);
        },
        
        addInfo: function(info) {
            var li = $('<li></li>');
            li.html(info);
            areas.infoBar.append(li);
        }
    };
}();

var test = (function() {
    
    return {
        init: function() {
            $('a#start').click(function(){
                socket.emit('start_game');
            });
        }
    };
}());

$(document).ready(function() {
    test.init();
    
    table.setAreas(
    { 
        playerCards: $('#playerCards'),
        infoBar: $('#infoBar')
    }
    );
});

var player = function() {
    var player_name = 'player';
    
    return {
        getName: function() {
            return player_name;
        }
    };
}();

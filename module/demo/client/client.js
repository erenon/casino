var socket = io.connect(null, {port: 3000, rememberTransport: true});

socket.on('connect', function(event) {
    socket.emit('register_sid', {
        sid: $.cookie('casino-session')
    });
});

socket.on('game_start', function(event) {
    console.log(event);
    table.addInfo('The Game has begun. First card is: ' 
        + event.first_card.color
        + ' / '
        + event.first_card.value
    );
});

socket.on('card_played', function(event) {
    var card = event.played_card,
        name = event.played_by.name;
    table.addInfo('Card: '+card.color+' / '+card.value+' played by '+name);
});

socket.on('game_end', function(event) {
    table.addInfo('Game ended. Winner: ' + event.winner.name);
});

socket.on('colorpick', function(event) {
    var color = event.color,
        name = event.picked_by.name;
    table.addInfo(name + ' picked color ' + color);
});

socket.on('draw_card', function(event) {
    var count = event.card_count,
        name = event.player.name;
        
    if (count == 1) {
        table.addInfo(name + ' draws a card');
    } else {
        table.addInfo(name + ' draws ' + count + ' cards');
    }
});

socket.on('gets_blocked', function(event) {
    var blocked = event.gets_blocked.name,
        blocker = event.blocked_by.name;
    table.addInfo(blocked + ' gets blocked by ' + blocker);
});

socket.on('uno_said', function(event) {
    var name = event.said_by.name,
        type = event.type;
    table.addInfo(name + ' is on UNO (' + type + ')');
});

socket.on('player_joined', function(event) {
    table.addInfo(event.player.name + ' joined to the game');
});

socket.on('players_turn', function(event) {
    var name = event.player.name;
    if (name == player.getName()) {
        table.addInfo('Your turn');
    } else {
        table.addInfo(name + '\'s turn');
    }
});

socket.on('unknow_event', function(event) {
    console.log(event);
    table.addInfo('[UNKNOWN EVENT]');
});



socket.on('action_added', function(action) {
    //console.log(action);
    table.addPlayerCard(action);
});



var table = function() {
    var areas,
    
    cardBuilder = function(card) {
        var div = $('<div></div>');
        div.html('color: ' + card.color + ' / value: ' + card.value);
        div.data('card', card);
        div.click(function(){
            socket.emit('play_card', div.data('card'), function(isValid, message) {
                if (isValid === true) {
                    div.closest('li').remove();
                } else {
                    table.addInfo('Invalid move: ' + message);
                }
            });
            
        });
        
        return div;
    };
    
    
    
    return {
        setAreas: function(a) {
            areas = a;
        },
        
        init: function() {
            var drawButton = $('<a></a>');
            drawButton.html('Draw');
            drawButton.click(function(){
                socket.emit('play_draw', function(isValid, message) {
                    
                });
            });
            areas.buttons.append(drawButton);
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
        infoBar: $('#infoBar'),
        buttons: $('#buttons')
    }
    );
    
    table.init();
});

var player = function() {
    var player_name = 'player';
    
    return {
        getName: function() {
            return player_name;
        }
    };
}();

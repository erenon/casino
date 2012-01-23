/**
 * options:
 * - $: jQuery object
 * - pubusb: PubSub object
 * - target: domElement contains player
 * - cardBuilder: CardBuilder object
 * - stock: Deck of unused cards
 * - pile: Deck of used cards
 * - name: players name
 * - nameContainer: domElement contains players name
 * - orientation: rotation of the player container. 
 *       0: normal horizontal 
 *      90: vertical, topside to the left
 *     180: horizontal upside down
 *     270: vertical, topside to the right     
 * 
 * player: (optional) Inherited object to bind methods to it
 */
var
Player = function(options, player) {
var $ = options.$,
    pubsub = options.pubsub,
    target = $(options.target),    
    cardBuilder = options.cardBuilder,    // unused
    stock = options.stock,    // unused
    pile = options.pile,    // unused
    name,
    nameContainer = options.nameContainer,
    hand = $('<div class="hand"/>'),
    isHorizontal,
    isVertical,
    setHandSize = function() {
        // set width/height
        if (isHorizontal) {
            // dimensions
            hand.css('width', cardBuilder.getCardWidth()*4+'px');
            hand.css('height', cardBuilder.getCardHeight()+'px');
            
            // paddings
            hand.css('padding-left', cardBuilder.getCardWidth()*3/4+'px');
        } else if (isVertical) {
            // dimensions
            hand.css('width', cardBuilder.getCardHeight()+'px');        
            hand.css('height', cardBuilder.getCardWidth()*3+'px');
            
            // paddings
            hand.css('padding-top', cardBuilder.getCardHeight()*3/4+'px');
        }      
    },
    setCardPosition = function(domCard) {
        if (isHorizontal) {
            domCard.css('margin-left', cardBuilder.getCardWidth()*-3/4+'px');
        } else if (isVertical) {
            domCard.css('margin-top', 
                cardBuilder.getCardHeight()*-3/4
                + (cardBuilder.getCardWidth() - cardBuilder.getCardHeight())/2
                + 'px'
            );
            domCard.css('margin-left', 
                    (cardBuilder.getCardHeight() - cardBuilder.getCardWidth())/2
                    + 'px'    
            );
            
            if (player.orientation === 90) {
                domCard.css('transform', 'rotate(-90deg)');
            } else if (player.orientation === 270) {
                domCard.css('transform', 'rotate(90deg)');
            }
        }        
    }
    ;
    
    player = player || {};
    
    player.orientation = options.orientation || 0;
    isHorizontal = (player.orientation === 0 || player.orientation === 180);
    isVertical = (player.orientation === 90 || player.orientation === 270);
    
    // init hand
    player.hand = hand;
    target.append(hand);
    
    hand.addCard = function(domCard) {
        setCardPosition(domCard);
        hand.append(domCard);        
    };
    
    player.getName = function() {
        return name;
    };
    
    player.setName = function(newName) {
        // TODO check name collosion
        name = newName;
        nameContainer.text(name);
    };
    
    player.isItMe = function(playerObject) {
        return (playerObject.name === name);
    };
    
    pubsub.on('changeCardSize', function(data) {
        setHandSize();
        setCardPosition(hand.find('.card'));       
    });
    
    player.setName(options.name || "");
},

/**
 * options:
 * - $: jQuery object
 * - pubusb: PubSub object
 * - target: domElement contains player
 * - cardBuilder: CardBuilder object
 * - stock: Deck of unused cards
 * - pile: Deck of used cards
 * 
 * player: (optional) Inherited object to bind methods to it
 */
OppositePlayer = function(options, player) {
var $ = options.$,
    pubsub = options.pubsub,
    cardBuilder = options.cardBuilder, 
    stock = options.stock,
    pile = options.pile,
    events = options.events
    ;
    
    player = player || {};
    Player(options, player);
    
    
    // shows and pulls the recently played card to the pile
    pubsub.on('card_played', function(event) {
        if (player.isItMe(event.played_by)) {
            var domCard = cardBuilder.get(event.played_card);
            events.add(function(endCallback) {
                
                // TODO use 3D flip effect
                player.hand.find('.card').last().remove();
                player.hand.addCard(domCard);
                pile.pushCard(domCard, endCallback);
            });
        }
    });
    
    // draws some cards from the stock
    pubsub.on('draw_card', function(event) {
        var i,
            drawCard = function(endCallback) {
                var domCard = cardBuilder.getBackside();
                player.hand.addCard(domCard);
                stock.pullCard(domCard, endCallback);
            }
            ;
        
        if (player.isItMe(event.player)) {
            for (i = event.card_count - 1; i >= 0; i--) {
                events.add(drawCard);
            }
        }
    });
    
    return player;
},

/**
 * options:
 * - $: jQuery object
 * - pubusb: PubSub object
 * - target: domElement contains player
 * - cardBuilder: CardBuilder object
 * - stock: Deck of unused cards
 * - pile: Deck of used cards
 * - events: EventQueue object
 * - validator: Validator object
 * - socket. SocketioGateway object
 * 
 * player: (optional) Inherited object to bind methods to it
 */
ControlledPlayer = function(options, player) {
var $ = options.$,
    pubsub = options.pubsub,
    cardBuilder = options.cardBuilder,
    stock = options.stock,
    pile = options.pile,
    events = options.events,
    validator = options.validator,
    socket = options.socket,
    isPlaying = false
    ;
    
    player = player || {};
    Player(options, player);
    
    validator.setPlayerName(player.getName());
    
    pubsub.on('get_card', function(event) {
        if (player.isItMe(event.player)) {
            events.add(function(endCallback) {
                var domCard = cardBuilder.get(event.card);
                player.hand.addCard(domCard);
                stock.pullCard(domCard, endCallback);
                
                domCard.click(function() {
                    var card,
                        msg
                        ;
                        
                    if (isPlaying) {
                        card = domCard.data('card');
                        msg = validator.isCardValid(card);
                        
                        if (msg === true) {
                            // TODO handle wild card
                            // on colorpick set choosenColor property
                            // on card object
                            socket.emit('play_card', card);
                        } else {
                            pubsub.emit('invalid_move', {message: msg});
                        }
                    }
                });
            });
        }
    });
    
    pubsub.on('game_start', function(event) {
        player.hand.addClass('handOpen');
        isPlaying = true;
    });
    
    pubsub.on('game_end', function(event) {
        player.hand.removeClass('handOpen');
        isPlaying = false;
    });    
    
    return player; 
}
;

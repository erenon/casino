/**
 * options:
 * - $: jQuery object
 * - pubusb: PubSub object
 * - target: domElement contains player
 * - cardBuilder: CardBuilder object
 * - stock: Deck of unused cards
 * - pile: Deck of used cards
 * - name: players name
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
    pubsub = options.pubsub,    // unused
    target = $(options.target),    
    cardBuilder = options.cardBuilder,    // unused
    stock = options.stock,    // unused
    pile = options.pile,    // unused
    player = player || {},
    name = options.name || "",
    hand = $('<div class="hand"/>'),
    isHorizontal,
    isVertical
    ;
    
    player.orientation = options.orientation || 0;
    isHorizontal = (player.orientation == 0 || player.orientation == 180);
    isVertical = (player.orientation == 90 || player.orientation == 270);
    
    // init hand
    player.hand = hand;
    target.append(hand);
    
    hand.addCard = function(domCard) {
        if (isHorizontal) {
            domCard.css('margin-left', cardBuilder.getCardWidth()*-3/4+'px');
        } else if (isVertical) {
            domCard.css('margin-top', cardBuilder.getCardHeight()*-3/4+'px');
            if (player.orientation == 90) {
                domCard.css('transform', 'rotate(-90deg)');
            } else if (player.orientation == 270) {
                domCard.css('transform', 'rotate(90deg)');
            }
        }
        hand.append(domCard);        
    }
    
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
        hand.css('padding-top', cardBuilder.getCardWidth()*3/4+'px');
    }
    
    player.getName = function() {
        return name;
    }
    
    player.setName = function(newName) {
        // TODO check name collosion
        name = newName;
    }
    
    player.isItMe = function(playerObject) {
        return (playerObject.name === name);
    };

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
    player = player || {},
    cardBuilder = options.cardBuilder, 
    stock = options.stock,
    pile = options.pile
    ;
    
    Player(options, player);
    
    
    // shows and pulls the recently played card to the pile
    pubsub.on('card_played', function(event) {
        if (player.isItMe(event.played_by)) {
            var domCard = cardBuilder.get(event.played_card);
            // TODO remove one card from hand,
            // use CardBuilder.flip
            player.hand.addCard(domCard);
            pile.pushCard(domCard);
        }
    });
    
    // draws some cards from the stock
    pubsub.on('draw_card', function(event) {
        if (player.isItMe(event.player)) {
            for (var i = event.card_count - 1; i >= 0; i--) {
                var domCard = cardBuilder.getBackside();
                player.hand.addCard(domCard);
                stock.pullCard(domCard);
            };
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
 * 
 * player: (optional) Inherited object to bind methods to it
 */
ControlledPlayer = function(options, player) {
var $ = options.$,
    pubsub = options.pubsub,
    player = player || {},
    cardBuilder = options.cardBuilder,
    stock = options.stock,
    pile = options.pile
    ;
    
    Player(options, player);
    
    pubsub.on('get_card', function(event) {
        if (player.isItMe(event.player)) {
            var domCard = cardBuilder.get(event.card);
            player.hand.addCard(domCard);
            stock.pullCard(domCard);
        }
    });
    
    return player; 
}
;
/**
 * options:
 *  - $: jQuery object
 *  - target: DOM element to place the cards into
 *  - pubsub: (optional) PubSub object, listens to game speed changes
 *  - events: eventQueue object, synchronizes moving cards
 * 
 * deck: 
 */
var
Deck = function(options, deck) {
var $ = options.$,
    target = options.target,    // unused
    pubsub = options.pubsub || false,
    deck = deck || {}
    ;
    
    deck.movable = function(domObject) {
        var margin = 'originalMargin'
            ;
        
        if (!domObject.movable) {
            domObject.movable = true;
            domObject.enableMove = function() {
                domObject.css('transition', 'all '+deck.speed/1000+'s ease-in');
                domObject.css('position', 'absolute');
                
                // store margins
                domObject.data(margin, {
                    'top': domObject.css('margin-top'),
                    'right': domObject.css('margin-right'),
                    'bottom': domObject.css('margin-bottom'),
                    'left': domObject.css('margin-left'),
                });
                // disable margins
                domObject.css('margin-top', 0);
                domObject.css('margin-right', 0);
                domObject.css('margin-bottom', 0);
                domObject.css('margin-left', 0);     
            };
            
            domObject.disableMove = function() {
                domObject.css('transition', 'none');
                domObject.css('position', 'static');
                
                // restore margins
                domObject.css('margin-top', domObject.data(margin).top);
                domObject.css('margin-right', domObject.data(margin).right);
                domObject.css('margin-bottom', domObject.data(margin).bottom);
                domObject.css('margin-left', domObject.data(margin).left);
                // unset margin store
                domObject.data(margin, undefined);
            }
        }
        
        return domObject;
    };
    
    deck.speed = 400;
    
    if (pubsub) {
        pubsub.on('changeGameSpeed', function(data) {
            deck.speed = data.speed;
        });
    }
},

Stock = function(options, deck) {
var target = options.target,
    events = options.events || {add: function(eventCallback) {
        eventCallback(function(){});    
    }},     // unused
    deck = deck || {}
    ;
    
    Deck(options, deck);
    
    deck.pullCard = function(domCard, endCallback) {
        var finalOffset = domCard.offset(),
            cardTarget = domCard.parent(),
            finalTransform = domCard.css('transform');
        
        domCard = domCard.detach();
        domCard.offset(target.offset());
        domCard.css('transform', 'none');
            
        deck.movable(domCard).enableMove();
        $('body').append(domCard);
        
        domCard.offset(finalOffset);
        domCard.css('transform', finalTransform);
        
        setTimeout(function() {
            cardTarget.append(domCard);
            
            domCard.disableMove();
            
            domCard.css('top', '');
            domCard.css('left', '');
            
            if (endCallback) {
                endCallback();
            }
        }, deck.speed);                
    }
    
    return deck;
},

Pile = function(options, deck) {
var target = options.target,
    events = options.events || {add: function(eventCallback) {
        eventCallback(function(){});    
    }},
    pubsub = options.pubsub,
    stock = options.stock,
    cardBuilder = options.cardBuilder,
    deck = deck || {}
    ;
    
    Deck(options, deck);
    
    deck.pushCard = function(domCard) {
        var initialOffset = domCard.offset();
        
        domCard.detach();
        domCard.offset(initialOffset);
        
        events.add(function(endCallback) {
            $('body').append(domCard);
            
            deck.movable(domCard).enableMove();
            domCard.offset(target.offset());
            
            setTimeout(function() {
                //TODO remove previous card if any
                target.append(domCard);
                
                domCard.disableMove();
                
                domCard.css('top', '');
                domCard.css('left', '');
                
                endCallback();
            }, deck.speed);
        });
    }
    
    // show first card
    pubsub.on('game_start', function(data) {
        var card = data.first_card,
            domCard = cardBuilder.get(card)
            ;
        
        events.add(function(endCallback) {
            target.append(domCard);
            stock.pullCard(domCard, endCallback);
        });
    });
        
    return deck;
}
;

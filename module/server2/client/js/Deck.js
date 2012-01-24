/**
 * options:
 *  - $: jQuery object
 *  - pubsub: (optional) PubSub object, listens to changeGameSpeed
 * 
 * deck: (Optional) Inherited object to bind methods to 
 */
var
Deck = function(options, deck) {
var $ = options.$,
    pubsub = options.pubsub || false
    ;
    
    deck = deck || {};
    
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
            };
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

/**
 * options:
 *  - target: DOM element to place the cards into
 *  - pubsub: (optional) PubSub object, listens to changeCardSize
 *  - cardBuilder: CardBuilder object
 * 
 * deck: (Optional) Inherited object to bind methods to 
 */
Stock = function(options, deck) {
var target = options.target,
    pubsub = options.pubsub,
    cardBuilder = options.cardBuilder
    ;
    
    deck = deck || {};
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
            
            if (endCallback) {
                endCallback();
            }
        }, deck.speed);                
    };
    
    // taloon cards - decoration purpose only
    (function() {
        var taloonCards = [],
            taloonCard,
            i
            ;
             
        for (i = 2; i >= 0; i--) {
            taloonCard = cardBuilder.getBackside();
            taloonCards.push(taloonCard);
            target.append(taloonCard);
        }
        
        pubsub.on('changeCardSize', function(cardSize) {
            for (i = 2; i >= 1; i--) {
                taloonCards[i].css('margin-left', -1*cardSize.width);
            }
        });
    }());
    
    return deck;
},

/**
 * options:
 *  - target: DOM element to place the cards into
 *  - events: EventQueue object, enques deal of first card
 *  - pubsub: (optional) PubSub object, listens to game_start
 *  - stock: Stock object, pulls the first card from it
 *  - cardBuilder: CardBuilder object, used to build the first card
 * 
 * deck: (Optional) Inherited object to bind methods to 
 */
Pile = function(options, deck) {
var target = options.target,
    events = options.events || {add: function(eventCallback) {
        eventCallback(function(){});    
    }},
    pubsub = options.pubsub,
    stock = options.stock,
    cardBuilder = options.cardBuilder
    ;
    
    deck = deck || {};
    Deck(options, deck);
    
    deck.pushCard = function(domCard, endCallback) {
        var startingOffset = domCard.offset();
        
        deck.movable(domCard).enableMove();
        
        domCard = domCard.detach();
        domCard.offset(startingOffset);
        $('body').append(domCard);

        domCard.offset(target.offset());
        domCard.css('transform', 'none');
            
        
        setTimeout(function() {
            target.append(domCard);
            domCard.disableMove();
            
            target.find('.card').first().remove();
            domCard.css('margin', 0);
            
            if (endCallback) {
                endCallback();
            }
        }, deck.speed);
    };
    
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

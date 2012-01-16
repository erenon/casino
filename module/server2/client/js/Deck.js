/**
 * options:
 *  - $: jQuery object
 *  - target: DOM element to place the cards into
 *  - pubsub: (optional) PubSub object, listens to game speed changes
 *  - events: eventQueue object, synchronizes moving cards
 */
var
Deck = function(options) {
var $ = options.$,
    deck = options.target,
    pubsub = options.pubsub || false,
    events = options.events || {add: function(eventCallback) {
        eventCallback(function(){});    
    }},
    speed = 400,
    movable = function(domObject) {
        
        if (!domObject.movable) {
            domObject.movable = true;
            domObject.enableMove = function() {
                domObject.css('transition', 'all '+speed/1000+'s ease-in');         
            };
            
            domObject.disableMove = function() {
                domObject.css('transition', 'none');
            }
        }
        
        return domObject;
    }
    ;
    
    if (pubsub) {
        pubsub.on('changeGameSpeed', function(data) {
            speed = data.speed;
        });
    }
    
    return {
        pullCard: function(domCard) {
            var finalOffset = domCard.offset(),
                cardTarget = domCard.parent();
            
            domCard = domCard.detach();
            domCard.offset(deck.offset());
                
            events.add(function(endCallback) {
                $('body').append(domCard);
                
                movable(domCard).enableMove();
                
                domCard.offset(finalOffset);
                
                setTimeout(function() {
                    cardTarget.append(domCard);
                    
                    domCard.disableMove();
                    
                    domCard.css('top', '');
                    domCard.css('left', '');
                    
                    endCallback();
                }, speed);                
            });
        },
        
        pushCard: function(domCard) {
            var initialOffset = domCard.offset();
            
            domCard.detach();
            domCard.offset(initialOffset);
            
            events.add(function(endCallback) {
                $('body').append(domCard);
                
                movable(domCard).enableMove();
                domCard.offset(deck.offset());
                
                setTimeout(function() {
                    //TODO remove previous card if any
                    deck.append(domCard);
                    
                    domCard.disableMove();
                    
                    domCard.css('top', '');
                    domCard.css('left', '');
                    
                    endCallback();
                }, speed);
            });
        }
    };
};

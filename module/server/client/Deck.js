/**
 * config:
 *  - target
 *  - socket
 *  - events
 *  - cardBuilder
 *  - onClickEvent
 */
var
Deck = function(config) {
    var that = this,
        socket = config.socket,
        events = config.events,
        cardBuilder = config.cardBuilder,
        played,
        deck;
        
    // init piles
    played = $('<div/>');
    
    deck = $('<div/>');
    if (config.onClickEvent) {
        deck.bind('click.unoTableGameplay', config.onClickEvent);
    }
    
    for (var i = 1; i <= 3; i++) {
        var deckCard = cardBuilder(cardBuilder.backside);
        deckCard.addClass('deck-card-'+i);
        deck.append(deckCard);
    }
    
    config.target.append(played).append(deck);
    
    this.setPosition = function(domNode, position) {
        domNode.css('top', position.top + 'px');
        domNode.css('left', position.left + 'px');
    };
    
    this.clearPosition = function(domNode) {
        domNode.css('top', '');
        domNode.css('left', '');
    };
    
    this.addToPlayed = function(card, initialPosition, isRotated, eventCallback) {
        var domCard = cardBuilder(card);
        
        if (initialPosition) {
            var mvCard = cardBuilder(card);
            
            mvCard.addClass('cardFloating');
            this.setPosition(mvCard, initialPosition);
            
            if (isRotated) {
                mvCard.addClass('cardHorizontal');
            }
            
            $('body').append(mvCard);
            
            if (isRotated) {
                mvCard.removeClass('cardHorizontal');
                
                /*setTimeout(function() {
                    mvCard.addClass('cardVertical');                    
                }, 20);*/
            }
            
            //move over deck
            mvCard.addClass('cardMoving');
            this.setPosition(mvCard, played.children('div').offset());
            
            //zoom
            setTimeout(function(){
                mvCard.addClass('cardZoom');
                setTimeout(function(){
                    mvCard.remove();
                    played.html(domCard);
                    eventCallback(); 
                }, 200);
            }, 300);
             
        } else {
            played.html(domCard);
        }
    };
    
    this.dealCard = function(domCard, finalPosition, isRotated, eventCallback) {
        domCard.hide();
        domCard.addClass('cardFloating');
        domCard.addClass('cardMoving');
        
        $('body').append(domCard);
        
        this.setPosition(domCard, deck.children('div').offset());
        domCard.show();
        this.setPosition(domCard, finalPosition);
        
        setTimeout(function(){
            domCard.removeClass('cardFloating');
            domCard.removeClass('cardMoving');
            that.clearPosition(domCard);
            
            if (eventCallback) {
                eventCallback();
            } 
        }, 200);
    }
    
    this.changeColor = function(color) {
        var colorMap = {
            red: "EE0000",
            green: "056100",
            blue: "0E0A8E",
            yellow: "FFCC00"  
        },
        newColor = colorMap[color];
        
        $(played).find('.card').css('background', '#'+newColor);
    };
    
    socket.on('colorpick', function(event) {
        events.add(function(eventCallback) {
            that.changeColor(event.color);
            setTimeout(eventCallback, events.baseDelay);    
        });
    });
};
var
Player = function(target, isOpposite, name, socket, deck, events) {
    var that = this,
        opposite = isOpposite || false,
        name = name || '',
        nameContainer,
        domName,
        hand,
        maxHandSize,
        draw,
        sayUno,
        buttonContainer,
        drawButton,
        penaltyIndicator,
        unoButton;
        
    function pickColor(card, callback) {
        if (card.color == 'black') {    // pick color
            var pick = function(color) {
                card.choosenColor = color;
                callback(card);
            },
            box,
            colors = ['red', 'green', 'blue', 'yellow'];
            
            //create colorpicker modal
            box = $('<div id="colorpickBox" class="overlayBox"/>');
            
            $.each(colors, function(index, color) {
                var button = $('<a class="colorpickOption"/>'),
                    colorClass;
                    
                //uppercase color, e.g: colorpickOptionRed
                colorClass = color.charAt(0).toUpperCase();
                colorClass += color.substr(1);
                
                button.addClass('colorpickOption'+colorClass);
                button.bind('click.unoTableGameplay', function() {
                    pick(color);
                    box.remove();
                });
                
                box.append(button);
            });
            
            $('body').append(box);
        } else {    // no colorpicking needed
            callback(card);
        }
    }
        
    this.addCard = function(card, eventCallback) {
        var domCard = cardBuilder(card),
            offset;
        
        hand.append(domCard);
        offset = domCard.offset();
        domCard.remove();
        
        deck.dealCard(
            domCard,
            offset,
            this.isRotated(),
            function() {
                hand.append(domCard);
                that.increaseHandLoad(1);
                eventCallback();
                
                if (!opposite) { // bind play out
                    domCard.bind('click.unoTableGameplay', function() {
                        that.playCard(card, domCard);
                    });
                }
            }
        );
    }
    
    this.removeCard = function(card) {
        var toRemove,
            offset;
        
        if (card) {
            toRemove = card;
        } else {
            toRemove = hand.find('.card').last();
        }
        
        offset = toRemove.offset();
        toRemove.remove();
        this.decreaseHandLoad(1);
        
        return offset;
    }
    
    this.playCard = function(card, domCard) {
        pickColor(card, function(card) {
            events.lock();
            socket.emit('play_card', card, function(isValid, message) {
                if (isValid === true) {
                    var offset;
                    
                    offset = that.removeCard(domCard);
                    
                    events.addFront(function(eventCallback) {
                        deck.addToPlayed(
                            card,
                            offset,
                            false,
                            function() {
                                //that.removeCard(domCard);
                                eventCallback();
                            }
                        )
                    });
                } else {
                    status.warn(_._('Invalid move') + ': ' + _._(message));
                }
                
                events.run();
            });                            
        });                
    };
    
    this.getName = function() {
        return name;
    }
    
    this.isRotated = function() {
        return $(target).parent().hasClass('verticalOppositeContainer');
    };
    
    this.highlight = function() {
        /** @todo use config */
        //var highlightClass = config.playerHighlightClass;
        var highlightClass = 'playerHighlight';
        
        $('.'+highlightClass).removeClass(highlightClass);
        target.addClass(highlightClass);
    }
    
    this.increaseHandLoad = function(addition) {
        var currentLoad = hand.data('load'),
            newLoad,
            maxHandSize,
            firstCard,
            fullCardSize,
            marginSide,
            handSizeProperty,
            handSize,
            newHandSize,
            cardMargin,
            coveredCardSize,
            cardsSize,
            handMargin,
            overflowSize,
            reduction,
            newHandMargin,
            newCardMargin;
            
        newLoad = currentLoad + addition;
        hand.data('load', newLoad);
        
        maxHandSize = hand.data('maxSize');
        firstCard = hand.find('.card').first();
        
        // tweak margin only on limited sized,
        // not empty hands
        // unlimited hand has 0 as max size
        if (maxHandSize > 0 && firstCard) {
            
            if (this.isRotated()) {
                fullCardSize = firstCard.outerHeight();
                marginSide = 'margin-top';
                handSizeProperty = 'height';
            } else {
                fullCardSize = firstCard.outerWidth();
                marginSide = 'margin-left';
                handSizeProperty = 'width';
            }
            
            // margin is originally negative to make overlapping cards
            // e.g: -105px
            cardMargin = parseInt(firstCard.css(marginSide)) * -1;
            coveredCardSize = fullCardSize - cardMargin;
            
            // covered cards * covered size + fully visible card's size
            cardsSize = (newLoad - 1) * coveredCardSize + fullCardSize;
            handMargin = parseInt(hand.css(marginSide));
            
            overflowSize = cardsSize - maxHandSize - handMargin;
            
            // tweak margin if the cards overflow
            // >= : chrome puts the last card into a new line if == 0
            if (overflowSize >= 0) {
                // too many cards in the hand
                // increase overlap (decrease margin)
                // +1 : avoid rounding errors
                reduction = Math.round(overflowSize / newLoad) + 1;
                newCardMargin = (cardMargin + reduction) * -1;
                
                hand.find('.card').css(marginSide, newCardMargin + 'px');
                
                //increase hand margin, decrease size
                newHandMargin = handMargin + reduction;
                hand.css(marginSide, newHandMargin);
                
                handSize = parseInt(hand.css(handSizeProperty));
                newHandSize = handSize - reduction;
                hand.css(handSizeProperty, newHandSize + 'px');
            }
            
        }
    };
    
    this.decreaseHandLoad = function(reduction) {
        var currentLoad = hand.data('load'),
            newLoad;
            
        newLoad = currentLoad - reduction;
        hand.data('load', newLoad);
        
        /** @TODO increase margins */
    };
    
    this.resetPenaltyIndicator = function() {
        if (penaltyIndicator.data('penalty') > 0) {
            penaltyIndicator.data('penalty', 0);
            penaltyIndicator.text(0).hide();
        }
    }
    
    if (!opposite) {
        this.draw = function() {
            socket.emit('play_draw', function(isValid, message) {
                if (!isValid) {
                    status.warn(message);
                } else {
                    that.resetPenaltyIndicator();
                }
            });
        }
        
        this.sayUno = function () {
            socket.emit('say_uno');
        }
    }
    
    // name
    domName = $('<span class="playerName"/>').text(name);
    nameContainer = $('<div class="nameContainer"/>').append(domName);
    
    // cards
    hand = $('<div class="hand"/>');
    hand.data('load', 0);
    
    // set max size
    if (isOpposite) {
        if (this.isRotated()) {
            maxHandSize = 300;
        } else {
            maxHandSize = 600;
        }
    } else {
        maxHandSize = 0;
    }
    hand.data('maxSize', maxHandSize);
    
    target
        .append(nameContainer)
        .append(hand);
    
    // buttons
    if (!opposite) {
        drawButton = $('<a id="drawButton" class="button">').text('Draw');
        drawButton.bind('click.unoTableGameplay', this.draw);
        
        penaltyIndicator = $('<span/>').data('penalty', 0).hide();
        drawButton.append(penaltyIndicator);
        
        socket.on('card_played', function(event) {
            var value = event.played_card.value,
                currentPenalty = penaltyIndicator.data('penalty'),
                addition = 0;
               
            if (value == '+2') {
                addition = 2;
            } else if (value == '+4') {
                addition = 4;
            }
               
            if (addition > 0) {
                currentPenalty += addition;
                penaltyIndicator.data('penalty', currentPenalty);
                penaltyIndicator
                    .text(currentPenalty)
                    .show();
            }
        });
        
        socket.on('draw_card', function() {
            that.resetPenaltyIndicator(); 
        });
        
        unoButton = $('<a class="button">').text('Uno');
        unoButton.bind('click.unoTableGameplay', function() {
            that.sayUno();
            
            unoButton.addClass('buttonPressed');
            setTimeout(function() {
                unoButton.removeClass('buttonPressed');
            }, 2500);
        });
        
        buttonContainer = $('<div class="buttonContainer">');
        buttonContainer
            .append(drawButton)
            .append(unoButton);
        
        target.append(buttonContainer);
    }
    
    //containers.centerHorizontalContainer(target);
    
    // socket events
    socket.on('draw_card', function(event) {
        if (event.player.name == that.getName()) {
            for (var i = 0; i < event.card_count; i++) {
                events.add(function(eventCallback) {
                    that.addCard(
                        cardBuilder.backside,
                        eventCallback
                    );
                });
            }
        } 
    });
    
    socket.on('gets_blocked', function(event) {
        if (event.gets_blocked.name == that.getName()) {
            // display block sign
            events.add(function(eventCallback) {
                var domSign = $('<div class="playerOverlay playerOverlayBlock"/>');
                domSign.text('ø');
                
                domSign.css('top', ((target.outerHeight()/2) - domSign.outerHeight()) + target.offset().top + "px");
                domSign.css('left', ((target.width()/2) - domSign.outerWidth()) + target.offset().left + "px");
                
                $('body').append(domSign);

                domSign.removeClass('playerOverlayBlock');
                
                setTimeout(function() {
                    domSign.addClass('playerOverlayBlockZoom');
                }, 0);  // let the render engine catch up.
                
                setTimeout(function() {
                    eventCallback();
                    domSign.remove();
                }, 1500);
            });
        }
    });
    
    socket.on('players_turn', function(event) {
        if (event.player.name == that.getName()) {
            events.add(function(eventCallback) {
                that.highlight();
                eventCallback(); 
            });
        }
    });
    
    if (opposite) {
        socket.on('card_played', function(event) {
            if (event.played_by.name == that.getName()) {
                /*events.add(function(eventCallback) {
                    that.removeCard();
                    eventCallback();    
                })*/
                
                events.add(function(eventCallback) {
                    var offset;
                
                    offset = that.removeCard();
                    deck.addToPlayed(
                        event.played_card,
                        offset,
                        that.isRotated(),
                        eventCallback
                    );
                })
            }
        });
    }
};
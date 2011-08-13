var unoTable = (function($) {

    var
        config, //plugin init wide config
        _,  //i18n
        socket, //socket.io endpoint
        deck,   //deck instance
        events, //event queue instance
        EventQueue = function() {
            var that = this,
                events = [],
                locked = false
                ;
                
            this.add = function(eventCallback /*, and callback arguments*/) {
                events.push({
                    callback: eventCallback,
                    arguments: Array.prototype.slice.call(arguments, 1)
                });
                
                if (!locked) {
                    // only the current event is there
                    // start event loop
                    this.run();
                }
            }
            
            this.run = function() {
                var event,
                    arguments;
                    
                locked = false;
                
                if (events.length > 0) {
                    locked = true;
                    
                    event = events.shift();
                    
                    arguments = event.arguments || new Array();
                    arguments.push(that.run);
                    
                    event.callback.apply(this, arguments);
                }
            };
        },
        
        Deck = function(target) {
            var that = this,
                played,
                deck;
                
            // init piles
            played = $('<div/>');
            
            deck = $('<div/>');
            
            for (var i = 1; i <= 3; i++) {
                var deckCard = cardBuilder(cardBuilder.backside);
                deckCard.addClass('deck-card-'+i);
                deck.append(deckCard);
            }
            
            target.append(played).append(deck);
            
            this.addToPlayed = function(card, eventCallback) {
                var domCard = cardBuilder(card);
                played.html(domCard);
                
                if (eventCallback) {
                    setTimeout(eventCallback, events.baseDelay);
                }
            };
            
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
            
            // socket events
            socket.on('card_played', function(event) {
                events.add(that.addToPlayed, event.played_card);
            });
            
            socket.on('colorpick', function(event) {
                events.add(function(eventCallback) {
                    that.changeColor(event.color);
                    setTimeout(eventCallback, events.baseDelay);    
                });
            });
        },
        
        player, //player instance
        Player = function(target, isOpposite, name) {
            var that = this,
                opposite = isOpposite || false,
                name = name || '',
                nameContainer,
                domName,
                cardContainer,
                draw,
                sayUno,
                buttonContainer,
                drawButton,
                unoButton;
                
            this.addCard = function(card) {
                var domCard = cardBuilder(card);
                
                if (!opposite) { // bind play out
                    domCard.bind('click.unoTableGameplay', function() {
                        socket.emit('play_card', card, function(isValid, message) {
                            if (isValid === true) {
                                domCard.remove();
                            } else {
                                status.warn(_._('Invalid move') + ': ' + _._(message));
                            }
                        });
                    });
                }
                
                cardContainer.append(domCard);
            }
            
            this.removeCard = function(card) {
                var toRemove;
                
                if (card) {
                    toRemove = cardContainer.find(card);
                } else {
                    toRemove = cardContainer.find('.card').last();
                }
                
                toRemove.remove();
            }
            
            this.getName = function() {
                return name;
            }
            
            this.highlight = function() {
                var highlightClass = 'playerHighlight';
                
                $('.'+highlightClass).removeClass(highlightClass);
                target.addClass(highlightClass);
            }
            
            if (!opposite) {
                this.draw = function() {
                    socket.emit('play_draw', function(isValid, message) {
                        if (!isValid) {
                            status.warn(message);
                        }
                    });
                }
                
                this.sayUno = function () {
                    console.log('Player.this.sayUno not implemented');
                }
            }
            
            // name
            domName = $('<span class="playerName"/>').text(name);
            nameContainer = $('<div class="nameContainer"/>').append(domName);
            
            // cards
            cardContainer = $('<div class="hand"/>');
            
            target
                .append(nameContainer)
                .append(cardContainer);
            
            // buttons
            if (!opposite) {
                drawButton = $('<a>').text('Draw');
                drawButton.bind('click.unoTableGameplay', this.draw);
                
                unoButton = $('<a>').text('Uno');
                unoButton.bind('click.unoTableGameplay', this.sayUno);
                
                target
                    .append(drawButton)
                    .append(unoButton);
            }
            
            // socket events
            socket.on('draw_card', function(event) {
                if (event.player.name == that.getName()) {
                    events.add(function(eventCallback) {
                        for (var i = 0; i < event.card_count; i++) {
                            that.addCard(cardBuilder.backside);
                        }
                        setTimeout(eventCallback, events.baseDelay);
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
                        events.add(function(eventCallback) {
                            that.removeCard();
                            eventCallback();    
                        })
                    }
                });
            }
        },
        
        containers = function() {},
              
        cardBuilder = function(card) {
            if (card == this.backside) {
                var domCard,
                    inner;
                    
                inner = $('<div class="card-inner"/>').text('UNO');            
                domCard = $('<div class="card card-backside"/>').append(inner);
                
                return domCard;
            }
            
            var domCard,
                sign,
                inner,
                value,
                extraClass;
                
            //set value and extraclass if needed
            switch (card.value) {
                case 'block':
                    value = 'ø';
                    extraClass = 'block';
                    break;
                case 'reverse':
                    value = '⟲';
                    extraClass = 'reverse';
                    break;
                case 'plustwo':
                    extraClass = 'plustwo';
                    break;                    
                case 'colorpick':
                    value = 'CP';
                    extraClass = 'colorpick';
                    break;
                case 'plusfour':
                    extraClass = 'plusfour';
                    break;
                default:
                    value = card.value;
                    break;
            }
                
            domCard = $('<div class="card"/>');
            domCard.addClass('card-'+card.color);
            if (extraClass) {
                domCard.addClass('card-'+extraClass);
            }
            
            sign = $('<span class="card-topleft-sign"/>');
            sign.text(value);
            
            inner = $('<div class="card-inner"/>');
            inner.text(value);
            
            domCard.append(sign).append(inner);
            
            return domCard;
        },
        
        status = function() {},
        
        initStartButton = function(target) {
            var button = $('<a>');
            button.html(_._('Start Game'));
            button.bind('click.unoTable', function() {
                socket.emit('start_game');
                button.remove();
            });
            target.append(button);
        },
        
        setupSocketEvents = function(target) {
            
            socket.on('game_start', function(event) {
                // init deck
                deck = new Deck(target.find('#'+config.deckId));
                deck.addToPlayed(event.first_card);
                
                events.add(function(eventCallback) {
                    events.baseDelay = 1000;
                    eventCallback();                    
                });
            });

            socket.on('player_joined', function(event) {
               var target,
                   opposite;
                   
               target = containers.getFreeOppositeSlot();
               opposite = new Player(target, true, event.player.name);
            });
            
            socket.on('action_added', function(card) {
                player.addCard(card);
            });
            
            socket.on('game_end', function(event) {
                events.add(function(eventCallback) {
                    status.info(_._('Game has ended. The Winner is:') + event.winner.name);
                    eventCallback();                    
                });
                
                target.find('*').unbind('.unoTableGameplay');
            });
            
        }
        ;
        
    containers.getPlayerSlot = function() {
        var container = $('#'+config.playerContainerId),
            playerSlot = $('<div class="player"/>');
            
        container.append(playerSlot);
        return playerSlot;
    };
        
    containers.getFirstNotFullOppositeContainer = function() {
        var containers,
            minOrder,
            firstNotFullContainer;
            //minLoad,
            //mostEmptyContainer;
            
        containers = $('.'+config.oppositeContainerClass);
        
        containers.each(function(index, container) {
            var load,   //player count in the container
                capacity,   //maximal player count in the container
                order,  //placement order in the visual representation
                container = $(container);
            
            load = container.data('load') || 0;
            capacity = container.data('capacity') || 0;
            order = container.data('order') || 5;
            
            if (load < capacity) {  //container is not full
                /*if (minLoad == undefined || load < minLoad) {
                    // load of this container is the lowest so far
                    minLoad = load;
                    mostEmptyContainer = container;
                }*/
                if (minOrder == undefined || order < minOrder) {
                    // not full container with lowest order so far
                    minOrder = order;
                    firstNotFullContainer = container;
                }
            }
        });
        
        return firstNotFullContainer;
    };
    
    containers.getFreeOppositeSlot = function() {
        var container = containers.getFirstNotFullOppositeContainer(),
            oppositeSlot = $('<div class="player"/>'),
            containerLoad;
        
        container.append(oppositeSlot);
        containerLoad = container.data('load') || 0;
        containerLoad++;
        container.data('load', containerLoad);
        
        return oppositeSlot;
    };
    
    cardBuilder.prototype.backside = {
        color: 'backside',
        value: 'backside'
    };
    
    status.init = function(target) {
        this.target = target;
    };
    
    status.log = function(message, severity) {
        var severity = severity || 'info',
            entry;
        
        entry = $('<li class="' + severity + '"/>').text(message);
        this.target.prepend(entry);
    };
    
    status.info = function(message) {
        status.log(message, 'info');  
    };
    
    status.warn = function(message) {
        status.log(message, 'warn');
    };
    
    status.error = function(message) {
        status.log(message, 'error');
    }

    return {
        init : function(target, userConfig) {
            config = {
                _ : $.i18n,
                            
                // table areas
                deckId : 'deck',
                playerContainerId : 'playerContainer',
                oppositeContainerClass : 'oppositeContainer',
                statusBarId : 'statusBar',
            };
            
            $.extend(config, userConfig);
            
            _ = config._;
            
            socket = config.socket || socketio.connect();
            
            initStartButton(target.find('#'+config.deckId));
            status.init(target.find('#'+config.statusBarId));
            events = new EventQueue();
            // baseDelay is low on the initial deal
            // game_start event overwrites it
            events.baseDelay = 50;
            
            player = new Player(
                containers.getPlayerSlot(), 
                false, 
                'player'
            );
                        
            setupSocketEvents(target);
        }
    };

})(jQuery);

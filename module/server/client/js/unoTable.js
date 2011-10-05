var unoTable = (function($) {

    var
        config, //plugin init wide config
        _,  //i18n
        socket, //socket.io endpoint
        deck,   //deck instance
        status, //StatusBar instance
        events, //EventQueue instance
        
        player, //player instance
        
        containers = function() {},
        cardBuilder,        
        
        initStartButton = function(target) {
            var button = $('<a id="startButton" class="button">');
            button.html(_._('Start Game'));
            button.bind('click.unoTable', function() {
                socket.emit('start_instant_game');
                button.remove();
                loadTable();
            });
            
            target.append(button);
        },
        
        loadTable = function() {
            // init status bar
            status = new config.StatusBar(config.tableDomRoot.find('#'+config.statusBarId));
            
            // init deck
            deck = new Deck({
                target : config.tableDomRoot.find('#'+config.deckId),
                socket : socket,
                events : events,
                cardBuilder : cardBuilder/*,
                onClickEvent : player.draw*/
                /** @TODO enable functionality above after fixing player setup */
            });
            
            // init player
            player = new config.Player(
                containers.getPlayerSlot(), 
                false, 
                'player',
                socket,
                deck,
                events,
                _,
                status
            );
        },
        
        setupSocketEvents = function(target) {
            
            socket.on('game_start', function(event) {
                events.add(function(eventCallback) {
                    deck.addToPlayed(event.first_card);
                    events.baseDelay = 1000;
                    eventCallback();                    
                });
            });

            socket.on('player_joined', function(event) {
               var target,
                   opposite;
                   
               target = containers.getFreeOppositeSlot();
               opposite = new config.Player(target, true, event.player.name, socket, deck, events, _, status);
               
               // @TODO remove this
               if (!unoTable.opposites) {
                   unoTable.opposites = new Array();   
               }
               
               unoTable.opposites.push(opposite);
               
               if (!unoTable.deal) {
                   unoTable.deal = function(cardCount, oppositeIndex) {
                       oppositeIndex = oppositeIndex || 0;
                       for (var i = 0; i < cardCount; i++) {
                           unoTable.opposites[oppositeIndex].addCard(
                               cardBuilder.backside,
                               function() {}
                           );
                       }
                   };
               }
               // end debug code
            });
            
            socket.on('action_added', function(card) {
                events.add(function(eventCallback){
                    player.addCard(card, eventCallback);                    
                });
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
    
    /*containers.centerHorizontalContainer = function(container) {
        var containerWidth;
        
        containerWidth = container.innerWidth();
        container.css('width', containerWidth);        
    };*/
    
    return {
        init : function(target, userConfig) {
            config = {
                _ : $.i18n,
                            
                // table areas
                tableDomRoot : target,
                deckId : 'deck',
                playerContainerId : 'playerContainer',
                oppositeContainerClass : 'oppositeContainer',
                statusBarId : 'statusBar',
                playerHighlightClass : 'playerHighlight',
                cardBuilder : cardBuilder,
                StatusBar : StatusBar,
                EventQueue : EventQueue,
                Player : Player
            };
            
            $.extend(config, userConfig);
            
            _ = config._;
            socket = config.socket || socketio.connect();
            /** @TODO should omit this, only one valid use */
            cardBuilder = config.cardBuilder;
            events = new EventQueue();
            
            initStartButton(target.find('#'+config.deckId));
            // baseDelay is low on the initial deal
            // game_start event overwrites it
            events.baseDelay = 20;
            
            setupSocketEvents(target);
        },
        
        create : function() {
            socket.emit('create_game');  
        },
        
        list : function() {
            socket.emit('list_games', function(games) {
                console.log(games);
            });    
        }
    };

})(jQuery);

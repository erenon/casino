var
Deck = require('./Deck'),
PlayerCollection = require('./PlayerCollection'),
Game = function(options, game) {
var config = options.config,
    players = PlayerCollection(),
    currentPenalty = 0,
    
    dealPenalty = function(player) {
        dealCard(player, currentPenalty);
        currentPenalty = 0;
    },
    
    dealCard = function(player, cardCount) {
        var i;
        
        for (i = 0; i < cardCount; i++) {
            player.notify('cardAdded', {
                card: game.deck.drawCard()
            });
        }
        
        players.notifyOthers('playerGotCard', {
            player: player,
            cardCount: cardCount
        }, player);        
    }
    ;
    
    game = game || {};
    
    game.deck = {};
    Deck(game.deck);
    
    game.addPlayer = function(player) {
        players.notifyAll('playerJoined', {player: player});
        players.addPlayer(player);
    };
    
    game.start = function() {
        var totalDealedCount,
            firstCard,
            i
            ;
        
        game.deck.shuffle();

        // deal initial hand 
        totalDealedCount = config.initialHandSize * players.length();
        players.reset();
        for (i = 0; i < totalDealedCount; i++) {
            dealCard(players.getCurrentPlayer(), 1);
            players.next();
        }
        
        // show first card
        firstCard = game.deck.getFirstCard();
        players.notifyAll('gameStarted', {firstCard: firstCard});
        
        players.reset();
        players.notifyAll('playerTurn', {
            player: players.getCurrentPlayer()
        });
    };
    
    game.isValidMove = function(player, move) {
        var isMyTurn = (player === players.getCurrentPlayer()),
            lastCard = game.deck.getLastPlayedCard(),
            card = move
            ;
            
        // if draw
        if (move.value === 'draw') {
            // draw is only valid if it's own turn
            return isMyTurn;
        } 
        
        // valid if same card
        if (lastCard.color === card.color
        &&  lastCard.value === card.value) {
            return true;
        }
        
        if (isMyTurn) {
            if (game.isPenalty()) {
                if (lastCard.value === '+4') {
                    return (card.value === '+4');
                } else {
                    return (card.value === '+4' || card.value === '+2');
                }
            } else {
                if (card.color === 'black') {
                    return true;
                } else if (lastCard.color === card.color) {
                    return true;
                } else if (lastCard.value === card.value) {
                    return true;
                } else {
                    return false;
                }
            }
        } else {
            return false;
        }   
    };
    
    game.isPenalty = function() {
        return (currentPenalty > 0);
    };
    
    game.increasePenalty = function(addition) {
        currentPenalty += addition;
    };
    
    game.playDraw = function(player) {
        if (game.isValidMove(player, {
            color: 'draw',
            value: 'draw'
        })) {
            if (game.isPenalty()) {
                dealPenalty(player);
            } else {
                dealCard(player, 1);
            }
            
            // TODO call next player routine
        } else {
            return false;
        }
    }
    
    game.playCard = function(player, card) {
        if (game.isValidMove(player, card)) {
            // TODO call next player routine
        } else {
            return false;
        }
    }
    
    return game;
}
;

module.exports = Game;
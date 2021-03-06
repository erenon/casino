/**
 * options:
 * - pubsub: PubSub object. listens to
 * - controlledPlayerName: name of the controlled player
 * - penaltyIndicator: PenaltyIndicator object to determine current penalty
 * 
 * TODO add tests
 * TODO review the following todo, controlled players moves also
 * come through cardPlayed event
 * TODO does not intercept cards played by controlled player.
 * This causes malfunction, consider 2 players and block card.
 */
var
Validator = function(options) {
var pubsub = options.pubsub,
    penaltyIndicator = options.penaltyIndicator,
    controlledPlayerName,
    isMyTurn = false,
    lastCard
    ;
    
    pubsub.on('cardPlayed', function(event) {
        isMyTurn = false;
        
        lastCard = event.card;
        if (event.card.pickedColor) {
            lastCard.color = event.card.pickedColor;
        }
    });
    
    pubsub.on('playerTurn', function(event) {
        if (event.player.name !== controlledPlayerName) {
            isMyTurn = false;
        } else {
            isMyTurn = true;
        }       
    });
    
    pubsub.on('gameStarted', function(event) {
        lastCard = event.firstCard;    
    });
    
    return {
        setPlayerName: function(name) {
            controlledPlayerName = name;    
        },
        
        isCardValid: function(card) {
            // valid if same card
            if (lastCard.color === card.color
            &&  lastCard.value === card.value) {
                return true;
            }
            
            if (isMyTurn) {
                if (penaltyIndicator.isPenalty()) {
                    if (lastCard.value === '+4') {
                        if (card.value === '+4') {
                            return true;
                        } else {
                            return 'must_play_+4_or_draw';
                        }
                    } else if (card.value === '+4' || card.value === '+2') {
                        return true;
                    } else {
                        return 'must_play_+4_+2_or_draw';
                    }
                } else {
                    if (card.color === 'black') {
                        return true;
                    } else if (lastCard.color === card.color) {
                        return true;
                    } else if (lastCard.value === card.value) {
                        return true;
                    } else {
                        return 'color_or_value_must_match';
                    }
                }
            } else {
                return "not_your_turn";
            }
        },
        
        isDrawValid: function() {
            // draw is valid only if it's my turn
            return isMyTurn;
        }
    };
}
;

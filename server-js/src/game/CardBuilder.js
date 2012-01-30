var
CardBuilder = function(cb) {
var colors = ['red', 'green', 'blue', 'yellow'],
    rankValues = ['block', 'reverse', '+2', '0'],
    simpleValues = [1, 2, 3, 4, 5, 6, 7, 8, 9],
    cards = []
    ;
    
    // init cards
    (function() {
        var c, v,
            actionNone = function() {},
            actionBlock = function(game) { game.actionBlock(); },
            actionReverse = function(game) { game.actionReverseTurn(); },
            actionPlustwo = function(game) { game.increasePenalty(2); }
            ;
        for (c = 0; c < colors.length; c++) {
            cards[colors[c]] = [];
            
            for (v = 0; v < simpleValues.length; v++) {
                cards[colors[c]][simpleValues[v]] = {
                    color: colors[c],
                    value: simpleValues[v],
                    takeAction: actionNone
                }
            }
            
            cards[colors[c]]['block'] = {
                color: colors[c],
                value: 'block',
                takeAction: actionBlock
            };
            
            cards[colors[c]]['reverse'] = {
                color: colors[c],
                value: 'reverse',
                takeAction: actionReverse
            };
            
            cards[colors[c]]['+2'] = {
                color: colors[c],
                value: '+2',
                takeAction: actionPlustwo
            };
            
            cards[colors[c]]['0'] = {
                color: colors[c],
                value: '0',
                takeAction: actionNone
            };
        }
        
        cards['black'] = [];
        
        cards['black']['colorpick'] = {
            color: 'black',
            value: 'colorpick',
            pickedColor: null,
            takeAction: function(game) { game.actionColorpick(); }
        };
        
        cards['black']['+4'] = {
            color: 'black',
            value: '+4',
            pickedColor: null,
            takeAction: function(game) { 
                game.increasePenalty(4);
                game.actionColorpick(); 
            }
        };
    }());

    cb = cb || {};
    
    cb.get = function(color, value) {
        return cards[color][value];
    };
    
    cb.getAll = function() {
        var deck = [],
            c, v, i;
       
        for (c = 0; c < colors.length; c++) {
            for (v = 0; v < simpleValues.length; v++) {
                for (i = 0; i < 2; i++) {
                    deck.push(cb.get(colors[c], simpleValues[v]));
                }    
            }
            
            for (v = 0; v < rankValues.length; v++) {
                deck.push(cb.get(colors[c], rankValues[v]));
            }
        }
        
        for (i = 0; i < 4; i++) {
            deck.push(cb.get('black', 'colorpick'));
            deck.push(cb.get('black', '+4'));
        }        
        
        return deck;
    };
    
    cb.isSimple = function(card) {
        var v;
        
        if (card.color !== 'black') {
            if (card.value === '0') {
                return true;
            }
            
            for (v = 0; v < simpleValues.length; v++) {
                if (card.value === simpleValues[v]) {
                    return true;
                }
            }
        }
    }
    
    return cb;
}
;

module.exports = CardBuilder();

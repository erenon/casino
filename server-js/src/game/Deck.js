var
cardBuilder = require('./CardBuilder'),
Deck = function(deck) {
var stock = cardBuilder.getAll(),
    pile = []
    ;    
    
    deck = deck || {};
    
    deck.shuffle = function() {
        var tmp, 
            picked, 
            current;
    
        for (current = 0; current < stock.length; current++) {
            picked = parseInt(Math.random() * (current + 1));
            
            // swap picked and current
            tmp = stock[picked];
            stock[picked] = stock[current];
            stock[current] = tmp;
        }
        
    };
    
    deck.getFirstCard = function() {
        var firstCard;
              
        do {
            firstCard = deck.drawCard();
            deck.playCard(firstCard);
        } while (!cardBuilder.isSimple(firstCard));
        
        return firstCard;
    };
    
    deck.drawCard = function() {
        if (stock.length === 0) {
            stock = pile;
            pile = [];
            deck.shuffle();    
        }
        
        return stock.shift();
    };
    
    deck.playCard = function(card) {
        pile.unshift(card);
    };
    
    deck.getLastPlayedCard = function() {
        return pile[0];
    }
    
    return deck;
}
;

module.exports = Deck;

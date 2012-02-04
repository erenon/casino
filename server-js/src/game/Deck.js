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
            picked = parseInt(Math.random() * (current + 1), 10);
            
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
        var lastPlayedCard;
        
        if (stock.length === 0) {
            lastPlayedCard = pile.shift();
            stock = pile;
            deck.shuffle();    

            pile = [];
            pile.push(lastPlayedCard);
        }
        
        var card = stock.shift(); 
        
        if (!card) {
            // TODO what to do now?
            console.log('FAILURE', pile.length, stock.length);
        }
        
        return card;
    };
    
    deck.playCard = function(card) {
        pile.unshift(card);
    };
    
    deck.getLastPlayedCard = function() {
        var lastCard = pile[0];
        
        if (lastCard.color === 'black') {
            lastCard.color = lastCard.pickedColor;
        }
        
        return lastCard;
    };
    
    return deck;
}
;

module.exports = Deck;

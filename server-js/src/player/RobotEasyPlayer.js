var
Player = require('./Player');
RobotEasyPlayer = function(options, player) {
var cardValueOrder = function(cardA, cardB) {
        var a = cardA.value,
            b = cardB.value,
            aIndex, 
            bIndex,
            i,
            valueOrder = [0,1,2,3,4,5,6,7,8,9,'block','reverse', '+2', 'colorpick', '+4'];
            
        for (i = 0; i < valueOrder.length; i++) {
            if (a === valueOrder[i]) {
                aIndex = i;
            }
            if (b === valueOrder[i]) {
                bIndex = i;
            }
        }
        
        return aIndex - bIndex;
    },
    pickColor = function() {
        var colorCount = [],
            cardColor,
            pickedColor,
            i;
        
        colorCount['red'] = 0;
        colorCount['green'] = 0;
        colorCount['blue'] = 0;
        colorCount['yellow'] = 0;
        
        for (i = 0; i < player.hand.length; i++) {
            cardColor = player.hand[i].color;
            if (colorCount[cardColor]) {
                colorCount[cardColor]++;
            }
        }
        
        pickedColor = 'red';
        if (colorCount['green'] > colorCount[pickedColor]) {
            pickedColor = 'green';
        }
        if (colorCount['blue'] > colorCount[pickedColor]) {
            pickedColor = 'blue';
        }
        if (colorCount['yellow'] > colorCount[pickedColor]) {
            pickedColor = 'yellow';
        }
        
        return pickedColor;
    }
    ;
    player = player || {};
    Player(options, player);
    
    player.on('playerTurn', function(data) {
        var validMoves = [],
            i,
            pickedCard
            ;
        
        if (data.player === player) {
            // filter valid moves
            for (i = 0; i < player.hand.length; i++) {
                if (player.game.isValidMove(player, player.hand[i])) {
                    validMoves.push(player.hand[i]);
                }
            }    
        }
        
        if (validMoves.length > 0) {
            // sort by value
            validMoves.sort(cardValueOrder);
            // pick lowest
            pickedCard = validMoves[0];
            // colorpick if black
            if (pickedCard.color === 'black') {
                pickedCard.pickedColor = pickColor();
            }
            // play
            player.game.playCard(player, pickedCard);
        } else {
            player.game.playDraw(player);
        }
    });  
    
    return player;  
}
;

module.exports = RobotEasyPlayer;
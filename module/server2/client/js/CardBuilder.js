/**
 * options:
 *  - $: jQuery
 */

var
CardBuilder = function(options) {
var $ = options.$,
    cardWidth = 148;
    cardHeight = 208;
    ;
    
    return {
        get: function(card) {
            var domCard,
                sign,
                inner,
                value,
                extraClass;
                
            //set value and extra class if needed
            switch (card.value) {
                case 'block':
                    value = 'ø';
                    extraClass = 'block';
                    break;
                case 'reverse':
                    value = '⟲';
                    extraClass = 'reverse';
                    break;
                case '+2':
                    value = '+2';
                    extraClass = 'plustwo';
                    break;                    
                case 'colorpick':
                    value = 'CP';
                    extraClass = 'colorpick';
                    break;
                case '+4':
                    value = '+4';
                    extraClass = 'plusfour';
                    break;
                default:
                    value = card.value;
                    break;
            }
                
            domCard = $('<div class="card card-'+card.color+'"/>');
            //domCard.addClass('card-'+card.color);
            if (extraClass) {
                domCard.addClass('card-'+extraClass);
            }
            
            sign = $('<span class="card-topleft-sign"/>');
            sign.text(value);
            
            inner = $('<div class="card-inner"/>');
            if (card.value != 'colorpick') {
                inner.text(value);
            }
            
            domCard.append(sign).append(inner);
            
            return domCard;
        },
        
        getBackside: function() {           
            return $('<div class="card card-backside"/>').append(
                $('<div class="card-inner"/>').text('UNO')
            );
        },
        
        getCardWidth: function() {
            return cardWidth;
        },
        
        getCardHeight: function () {
            return cardHeight;
        }
    };
};
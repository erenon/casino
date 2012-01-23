/**
 * options:
 *  - $: jQuery
 *  - pubsub: (optional) PubSub object - listens to changeViewport events
 */

var
CardBuilder = function(options) {
var $ = options.$,
    pubsub = options.pubsub || false,
    cardWidth = 148,
    cardHeight = 208,
    cardBorder = 4,
    setCardSize = function(domCard) {
        var w = cardWidth - 2*cardBorder,
            h = cardHeight - 2*cardBorder,
            value = domCard.data('card').value,
            inner = domCard.find('.card-inner')
            ;
            
        domCard.css('width', w);
        domCard.css('height', h);
        domCard.css('border-width', cardBorder);
        
        domCard.find('.card-topleft-sign')
            .css('font-size', cardHeight / 8.5)
            .css('text-shadow', h*0.01 +'px '+h*0.01 +'px 0px #000')
            ;
        
        if (value !== 'backside') {    
            inner
                .css('margin-top', h *0.125)
                .css('margin-bottom', h *0.125)
                .css('margin-left', w *0.1)
                .css('margin-right', w *0.1)
                .css('padding-left', w / 7)
                .css('text-shadow', h*0.025 +'px '+h*0.025 +'px 0px #000')
                ;
                
        } else {
           inner
                .css('height', h *0.68)
                .css('width', w *0.9)
                .css('padding-top', h *0.32)
                .css('padding-left', w *0.1)
                .css('font-size', cardHeight *0.27)
                .css('margin', 0)
                .css('border-radius', h *0.2 +'px 6px')
                ; 
        }
            
        if (value === '+2' || value === '+4') {
            inner
                .css('font-size', cardHeight / 2.4)
                .css('height', h *0.625)
                .css('width', w *0.76)
                .css('padding-top', h *0.125)
                .css('padding-left', w / 25)
                .css('border-radius', h *0.2 +'px 0px')
                ;
                
        } else if (value === 'colorpick') {
            inner
                .css('width', 0)
                .css('height', 0)
                .css('padding', 0)
                .css('border-top-width', w *0.35)
                .css('border-right-width', w *0.35)
                .css('border-bottom-width', w *0.35)
                .css('border-left-width', w *0.35)
                .css('border-radius', w *0.35 +'px 0px')
                .css('margin-top', h *0.25)
                .css('margin-left', w *0.15)
                ;
        
        } else if (value !== 'backside') {           
            inner
                .css('font-size', cardHeight / 1.8)
                .css('height', h *0.75)
                .css('width', w *0.64)
                .css('border-radius', h *0.2 +'px 0px')
                ;
        }
        
        if (value === 'reverse') {
           inner
                .css('width', w *0.80)
                .css('padding-left', 0)
                ;            
        }
    }
    ;
    
    if (pubsub) {
        pubsub.on('changeViewportSize', function(viewport) {
            var baseCardHeight = 200,
                baseCardWidth = 140,
                fullTableHeight = 5,  // expressed in card height
                fullTableWidth = 7, // expressed in card width
                maxCardHeight,
                maxCardWidth,
                multi
                ;
                
            for (multi = 1; multi >= 0.30; multi -= 0.1) {
                maxCardHeight = baseCardHeight * multi;
                maxCardWidth = baseCardWidth * multi;
                
                if (maxCardHeight < viewport.height / fullTableHeight
                &&  maxCardWidth  < viewport.width  / fullTableWidth)
                {
                    break;
                } 
            }
            
            // set card dimensions
            cardHeight = baseCardHeight * multi;
            cardWidth = baseCardWidth * multi;
            cardBorder = 4 * multi;   //4: baseCardBorderWidth
            
            // adjust all cards on the table
            $('.card').each(function(index, card) {
                setCardSize($(card));
            });
            
            // notify card size based elements:
            pubsub.emitSync('changeCardSize', {
                height: cardHeight,
                width: cardWidth
            });
        });
    }
    
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

            if (extraClass) {
                domCard.addClass('card-'+extraClass);
            }
            
            sign = $('<span class="card-topleft-sign"/>');
            inner = $('<div class="card-inner"/>');
            
            if (card.value !== 'colorpick') {
                inner.text(value);
                sign.text(value);
            }
            
            domCard.append(sign).append(inner);
            domCard.data('card', card);
            
            setCardSize(domCard);
            
            return domCard;
        },
        
        getBackside: function() {           
            var domCard = $('<div class="card card-backside"/>').append(
                    $('<div class="card-inner"/>').text('UNO')
                )
                .data('card', {
                    value: 'backside',
                    color: 'backside'
                })
                ;
                
            setCardSize(domCard);                
            
            return domCard;
        },
        
        getCardWidth: function() {
            return cardWidth;
        },
        
        getCardHeight: function () {
            return cardHeight;
        }
    };
};
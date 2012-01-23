/**
 * options
 * - $: jQuery object
 * - pubsub: PubSub object, listens to changeCardSize
 * - tableContainer: element containing main table
 * - table: main table element
 * - corners: elements in the corners of the table
 * - names: elements containing names
 */
var
GameTable = function(options) {
    var $ = options.$,
        pubsub = options.pubsub,
        tableContainer = options.tableContainer,
        table = options.table,
        corners = options.corners || [],
        deckContainer = options.deckContainer,
        names = options.names || [],
        viewportChanged = function() {
            pubsub.emitSync('changeViewportSize', {
                height: $(window).height(),
                width: $(window).width()
            });            
        }
        ;
        
    pubsub.on('changeCardSize', function(cardSize) {
        $.each(corners, function(index, corner) {
            $(corner)
                .css('height', cardSize.height)
                .css('width', cardSize.height)
                ;
        });
        
        $.each(names, function(index, name) {
            $(name).css('max-width', cardSize.height);
        });
        
        tableContainer.css('width', table.innerWidth());
        
        deckContainer.css('width', cardSize.width * 2.1);
    });
      
    $(window).resize(function() {
        viewportChanged();
    });
    
    // set sizes on load
    viewportChanged();
}
;

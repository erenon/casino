$(document).ready(function() {
var socket = SocketioGateway({
        io: io
    }),
    pubsub = PubSub({
        socket: socket
    }),
    eventQueue = EventQueue(),
    cardBuilder = CardBuilder({
        $: $,
        pubsub: pubsub
    }),
    stock = Stock({
        $: $,
        target: $('#stock'),
        events: eventQueue,
        pubsub: pubsub,
        cardBuilder: cardBuilder
    }),
    pile = Pile({
        $: $,
        target: $('#pile'),
        events: eventQueue,
        pubsub: pubsub,
        stock: stock,
        cardBuilder: cardBuilder
    }),
    penaltyIndicator = PenaltyIndicator({
        $: $,
        pubsub: pubsub,
        target: $('#buttonDraw span')
    }),
    validator = Validator({
        pubsub: pubsub,
        penaltyIndicator: penaltyIndicator
    }),
    statusBar = StatusBar({
        $: $,
        pubsub: pubsub,
        target: $('#statusBar')
    }),
    player = ControlledPlayer({
        $: $,
        pubsub: pubsub,
        target: $('.horizontalPlayer')[1],
        cardBuilder: cardBuilder,
        stock: stock,
        pile: pile,
        name: 'player',
        nameContainer: $('#nameBottom'),
        events: eventQueue,
        validator: validator,
        socket: socket
    }),
    seatManager = SeatManager({
        $: $,
        pubsub: pubsub,
        OppositePlayer: OppositePlayer,
        seats: [
            { // left
              target: $('.verticalPlayer')[0],
              nameContainer: $('#nameLeft'),
              orientation: 270
            },
            { // top
              target: $('.horizontalPlayer')[0],  
              nameContainer: $('#nameTop'),
              orientation: 180  
            },
            { // top
              target: $('.verticalPlayer')[1],  
              nameContainer: $('#nameRight'),
              orientation: 90  
            }
        ],
        defaultPlayerOptions: {
            $: $,
            pubsub: pubsub,
            cardBuilder: cardBuilder,
            stock: stock,
            pile: pile,
            events: eventQueue
        }
    }),
    gameTable = GameTable({
        $: $,
        pubsub: pubsub,
        tableContainer: $('#gameTableContainer'),
        table: $('#gameTable'),
        corners: $('.cornerContainer'),
        deckContainer: $('.deckContainer'),
        names: $('.name')
    }),
    drawButton = DrawButton({
        validator: validator,
        socket: socket,
        target: $('#buttonDraw'),
        pubsub: pubsub
    }),
    unoButton = UnoButton({
        validator: validator,
        socket: socket,
        target: $('#buttonUno')
    })
    ;     
});
/**
 * options:
 *  - config: Socket.IO config
 *  - io: Socket.IO object
 */

var
SocketioGateway = function(options) {
var config = options.config || {
        host: null,
        connect_options: {port: 3000, rememberTransport: true}
    },
    io = options.io,
    socket
    ;
    
    // connect
    socket = io.connect(config.host, config.connect_options);
    
    return socket;
};

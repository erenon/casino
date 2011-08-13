var socketio = function() {};

socketio.config = {
    host: null,
    connect_options: {port: 3000, rememberTransport: true}
};

socketio.connect = function() {
    var config = this.config;

    var socket = io.connect(config.host, config.connect_options);
    
    return socket; 
};

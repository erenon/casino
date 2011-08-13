var io;

describe('socketio', function() {

    var socket = {dummy:'dummy'};

    beforeEach(function() {
        io = {};
        io.connect = function() {
            return socket;
        };
    });

    it('connects', function() {
        spyOn(io, 'connect');
        
        socketio.connect();
        
        expect(io.connect).toHaveBeenCalled();
    });
    
    it('uses config', function() {
        spyOn(io, 'connect');
        
        //setup config
        socketio.config.host = 'foobar';
        socketio.config.connect_options.port = 1234;
        socketio.config.connect_options.rememberTransport = false;
        
        socketio.connect();
        
        expect(io.connect).toHaveBeenCalledWith('foobar', {port: 1234, rememberTransport: false});
    });
    
    it('returns connection', function() {
        var returned = socketio.connect();
        
        expect(returned).toBe(socket);
    });

});

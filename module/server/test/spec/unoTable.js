describe('unoTable', function() {
    var target,
        socketspy = {};
    
    beforeEach(function() {
        this.addMatchers({
            toBeDomElementSet: function() {
                return (this.actual.size() > 0);
            }
        });
    
        //init test dom
        var oppositeContainers = [],
            oppositeContainerCount = 3,
            deck,
            statusBar,
            playerContainer;
            
        target = $('<div />');
            
        for (i = 0; i < 3; i++) {
            oppositeContainers[i] = $('<div class="oppositeContainer" />');
            target.append(oppositeContainers[i]);
        }
            
        deck = $('<div id="deck" />');
        statusBar = $('<div id="statusBar" />');
        playerContainer = $('<div id="playerContainer" />');
        
        target.append(deck);
        target.append(statusBar);
        target.append(playerContainer);
        
        //init spies
        socketspy.emit = jasmine.createSpy();
        socketspy.on = jasmine.createSpy();
        
        //init table on target
        unoTable.init(
            target,
            {
                socket: socketspy
            }
        );
    });

    it('displays start game button', function() {
        var button = target.find('#deck').find('a');
        expect(button).toBeDomElementSet();
    });
    
    describe('startButton', function() {
        
        it('emits game start', function() {
            var button = target.find('#deck').find('a');
            
            button.click();
            
            expect(socketspy.emit).toHaveBeenCalledWith('start_game');
        });
    })

});

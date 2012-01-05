// Original code is from http://api.jquery.com/jQuery.cssHooks/


(function($) {
    if(!$.cssHooks) {
        throw ("jQuery 1.4.3+ is needed for this plugin to work");
        return;
    }

    function styleSupport(prop) {
        var vendorProp, 
            supportedProp, 
            capProp = prop.charAt(0).toUpperCase() + prop.slice(1), 
            prefixes = ["Moz", "Webkit", "O", "ms"], 
            div = document.createElement("div");

        if( prop in div.style) {
            supportedProp = prop;
        } else {
            for(var i = 0; i < prefixes.length; i++) {
                vendorProp = prefixes[i] + capProp;
                if( vendorProp in div.style) {
                    supportedProp = vendorProp;
                    break;
                }
            }
        }
        
        div = null;
        $.support[prop] = supportedProp
        return supportedProp;
    }

    function setHook(property) {
        var supportedProp = styleSupport(property);

        // Set cssHooks only for browsers that
        // support a vendor-prefixed property
        if(supportedProp && supportedProp !== property) {
            $.cssHooks[property] = {
                get : function(elem, computed, extra) {
                    return $.css(elem, supportedProp);
                },
                set : function(elem, value) {
                    elem.style[supportedProp] = value;
                }
            };
        }
    }

    var properties = ['borderRadius', 'transition', 'transform'];

    for(var i = properties.length - 1; i >= 0; i--) {
        setHook(properties[i]);
    };

})(jQuery);


PACKAGE = casino

#NODEJS   = $(if $(shell test -f /usr/bin/nodejs && echo "true"),nodejs,node)
#NODEUNIT = $(if $(shell test -f /usr/bin/nodeunit && echo "true"),nodeunit,~/node_modules/.bin/nodeunit)
NODELINT = $(if $(shell test -f /usr/bin/jslint && echo "true"),nodelint,~/node_modules/.bin/jslint)

#Doesn't work: express can't find the view templates...
#demo:
#	$(NODEJS) ./demo/server.js

#test:
#	$(NODEUNIT) test

lint:
	$(NODELINT) --config nodelint.cfg `find ./server2 -name "*.js" | grep -v jquery | grep -v jasmine`

.PHONY: test lint

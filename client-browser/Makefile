PACKAGE = casino

NODEJS   = $(if $(shell test -f /usr/bin/nodejs && echo "true"),nodejs,node)
NODELINT = $(if $(shell test -f /usr/bin/jslint && echo "true"),nodelint,~/node_modules/.bin/jslint)

demo:
	$(NODEJS) testServer.js

lint:
	$(NODELINT) --config nodelint.cfg `find ./ -name "*.js" | grep -v jquery.js | grep -v jasmine`

.PHONY: demo lint

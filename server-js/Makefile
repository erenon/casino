PACKAGE = casino

NODELINT = $(if $(shell test -f /usr/local/bin/jslint && echo "true"),nodelint,~/node_modules/.bin/jslint)
NODEJASM = $(if $(shell test -f /usr/local/bin/jasmine-node && echo "true"),jasmine-node,~/node_modules/.bin/jasmine-node)


test:
	$(NODEJASM) ./test

lint:
	$(NODELINT) --config nodelint.cfg `find ./src ./test -name "*.js"`

.PHONY: test lint

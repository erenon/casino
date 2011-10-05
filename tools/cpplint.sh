#! /bin/bash
./cpplint.py --filter=-legal/copyright,-whitespace/line_length,-whitespace/blank_line,-whitespace/parens `find ../src/ -not -type d` 2> ../out


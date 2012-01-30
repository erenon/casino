#! /bin/bash
TOOL_DIR="$( cd "$( dirname "$0" )" && pwd )"

$TOOL_DIR/cpplint.py \
--filter=-legal/copyright,-whitespace/line_length,-whitespace/blank_line,-whitespace/parens,-build/header_guard \
`find $TOOL_DIR/../src/ -not -type d` 2> ./cpplint_report


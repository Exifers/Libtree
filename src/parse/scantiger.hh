#pragma once

#include <parse/parsetiger.hh>
#include <parse/tiger-parser.hh>

// Set parameters for Flex header, and include it.
# define YY_FLEX_NAMESPACE_BEGIN namespace parse {
# define YY_FLEX_NAMESPACE_END   }

#include <misc/flex-lexer.hh>

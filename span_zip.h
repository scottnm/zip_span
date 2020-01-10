#pragma once

#include <gsl/span>

// Define for tuple
#undef TUPLE_NAME
#define TUPLE_NAME Tuple
#undef APPLY_TO_TEMPLATE_LIST
#define APPLY_TO_TEMPLATE_LIST(MACRO) \
    MACRO(1) \

#include "span_zip_template.h"

// Define for triple
#undef TUPLE_NAME
#define TUPLE_NAME Triple
#undef APPLY_TO_TEMPLATE_LIST
#define APPLY_TO_TEMPLATE_LIST(MACRO) \
    MACRO(1) \
    MACRO(2) \

#include "span_zip_template.h"

// Define for 4-ple
#undef TUPLE_NAME
#define TUPLE_NAME 4ple
#undef APPLY_TO_TEMPLATE_LIST
#define APPLY_TO_TEMPLATE_LIST(MACRO) \
    MACRO(1) \
    MACRO(2) \
    MACRO(3) \

#include "span_zip_template.h"

// Define for 5-ple
#undef TUPLE_NAME
#define TUPLE_NAME 5ple
#undef APPLY_TO_TEMPLATE_LIST
#define APPLY_TO_TEMPLATE_LIST(MACRO) \
    MACRO(1) \
    MACRO(2) \
    MACRO(3) \
    MACRO(4) \

#include "span_zip_template.h"

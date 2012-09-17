#ifndef	INTEGER_DEFINE_H__
#define INTEGER_DEFINE_H__

#include "known_env.h"

#if (defined(_ENV_GNUC))
#include <stdint.h>
#include <inttypes.h>
#else
#include "stdint.h"
#include "inttypes.h"
#endif

#endif INTEGER_DEFINE_H__
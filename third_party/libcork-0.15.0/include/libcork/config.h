/* -*- coding: utf-8 -*-
 * ----------------------------------------------------------------------
 * Copyright © 2011, RedJack, LLC.
 * All rights reserved.
 *
 * Please see the COPYING file in this distribution for license
 * details.
 * ----------------------------------------------------------------------
 */

#ifndef LIBCORK_CONFIG_H
#define LIBCORK_CONFIG_H

/*** include all of the parts ***/

#include <libcork/config/config.h>

#define CORK_API
#define mkdir(a, b) _mkdir(a)

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define CORK_CONFIG_IS_BIG_ENDIAN 1
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define CORK_CONFIG_IS_LITTLE_ENDIAN 1
#endif

#endif /* LIBCORK_CONFIG_H */

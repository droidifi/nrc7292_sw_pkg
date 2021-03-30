/*
//  * Copyright (c) 2021 James Ewing jim@droidifi.com
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _NRC_S1G_H_
#define _NRC_S1G_H_

#include "nrc.h"
#include <linux/types.h>
#include <stddef.h>

#define FREQ_TO_100KHZ(mhz, khz) (mhz * 10 + khz / 100)

extern char * fw_country;

struct nrc_s1g_map {
    char alpha2[3];
    int s1g_freq;
    int fw_freq;
    int channel;
    int width; 
};

int nrc_get_s1g_freq(const char* alpha2, int ch);
int nrc_freq_fw_s1g(const char* alpha2, int fw_freq);
int nrc_freq_s1g_fw(const char* alpha2, int s1g_freq);
int nrc_s1g_width(const char* alpha2, int s1g_freq);
int nrc_num_channels(const char* alpha2);
void nrc_remap_status(const char* alpha2, struct ieee80211_rx_status *status);
void nrc_set_s1g_country(const char* alpha2);
const char* nrc_get_s1g_country(void);
int nrc_is_eu(const char* alpha2);
#endif

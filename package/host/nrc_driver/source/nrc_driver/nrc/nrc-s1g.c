/*
 * Copyright (c) 2021 James Ewing jim@droidifi.com
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

#include "nrc-s1g.h"
#include "nrc-debug.h"

#ifdef CONFIG_S1G_CHANNEL

#include <linux/sort.h>

#define S1GMAP(_alpha2, _freq_s1g, _freq_fw, _ch, _bw) { \
	.alpha2 = _alpha2,   \
	.s1g_freq = (_freq_s1g),\
	.fw_freq = (_freq_fw),   \
	.channel = (_ch),       \
	.width = (_bw) \
}

const struct nrc_s1g_map s1g_map[] = {
    S1GMAP("US", 9025, 2412, 1, 1),
    S1GMAP("US", 9035, 2422, 3, 1),
    S1GMAP("US", 9045, 2432, 5, 1),
    S1GMAP("US", 9055, 2442, 7, 1),
    S1GMAP("US", 9065, 2452, 9, 1),
    S1GMAP("US", 9075, 2462, 11, 1),
    S1GMAP("US", 9085, 5180, 36, 1),
    S1GMAP("US", 9095, 5185, 37, 1),
    S1GMAP("US", 9105, 5190, 38, 1),
    S1GMAP("US", 9115, 5195, 39, 1),
    S1GMAP("US", 9125, 5200, 40, 1),
    S1GMAP("US", 9135, 5205, 41, 1),
    S1GMAP("US", 9145, 5210, 42, 1),
    S1GMAP("US", 9155, 5215, 43, 1),
    S1GMAP("US", 9165, 5220, 44, 1),
    S1GMAP("US", 9175, 5225, 45, 1),
    S1GMAP("US", 9185, 5230, 46, 1),
    S1GMAP("US", 9195, 5235, 47, 1),
    S1GMAP("US", 9205, 5240, 48, 1),
    S1GMAP("US", 9215, 5745, 149, 1),
    S1GMAP("US", 9225, 5750, 150, 1),
    S1GMAP("US", 9235, 5755, 151, 1),
    S1GMAP("US", 9245, 5760, 152, 1),
    S1GMAP("US", 9255, 5500, 100, 1),
    S1GMAP("US", 9265, 5520, 104, 1),
    S1GMAP("US", 9275, 5540, 108, 1),
    S1GMAP("US", 9030, 2417, 2, 2),
    S1GMAP("US", 9040, 2427, 4, 2),    
    S1GMAP("US", 9050, 2437, 6, 2),
    S1GMAP("US", 9070, 2457, 10, 2),
    S1GMAP("US", 9090, 5765, 153, 2),
    S1GMAP("US", 9110, 5770, 154, 2),
    S1GMAP("US", 9130, 5775, 155, 2),
    S1GMAP("US", 9150, 5780, 156, 2),
    S1GMAP("US", 9170, 5785, 157, 2),
    S1GMAP("US", 9190, 5790, 158, 2),
    S1GMAP("US", 9210, 5795, 159, 2),
    S1GMAP("US", 9230, 5800, 160, 2),
    S1GMAP("US", 9250, 5805, 161, 2),
    S1GMAP("US", 9270, 5560, 112, 2),
    S1GMAP("US", 9060, 2447, 8, 4),
    S1GMAP("US", 9100, 5810, 162, 4),
    S1GMAP("US", 9140, 5815, 163, 4),
    S1GMAP("US", 9180, 5820, 164, 4),
    S1GMAP("US", 9220, 5825, 165, 4),
    S1GMAP("US", 9260, 5580, 116, 4),
    S1GMAP("KX", 9180, 5180, 36, 1), 
    S1GMAP("KX", 9190, 5185, 37, 1),
    S1GMAP("KX", 9200, 5190, 38, 1),
    S1GMAP("KX", 9210, 5195, 39, 1),
    S1GMAP("KX", 9220, 5200, 40, 1),
    S1GMAP("KX", 9230, 5205, 41, 1),
    S1GMAP("KX", 9428, 5230, 46, 1),
    S1GMAP("KX", 9438, 5235, 47, 1),
    S1GMAP("KX", 9448, 5240, 48, 1),
    S1GMAP("KX", 9458, 5745, 149, 1),
    S1GMAP("KX", 9185, 5210, 42, 2),
    S1GMAP("KX", 9205, 5215, 43, 2),
    S1GMAP("KX", 9225, 5220, 44, 2),
    S1GMAP("KX", 9433, 5750, 150, 2),
    S1GMAP("KX", 9453, 5755, 151, 2),
    S1GMAP("KX", 9215, 5225, 45, 4),
    S1GMAP("KX", 9443, 5760, 152, 4),
    S1GMAP("KR", 9255, 5180, 36, 1),
    S1GMAP("KR", 9265, 5185, 37, 1),
    S1GMAP("KR", 9275, 5190, 38, 1),
    S1GMAP("KR", 9285, 5195, 39, 1),
    S1GMAP("KR", 9295, 5200, 40, 1),
    S1GMAP("KR", 9305, 5205, 41, 1),
    S1GMAP("KR", 9270, 5210, 42, 2),
    S1GMAP("KR", 9290, 5215, 43, 2),
    S1GMAP("JP", 9170, 5180, 36, 1),
    S1GMAP("JP", 9180, 5185, 37, 1),
    S1GMAP("JP", 9190, 5190, 38, 1),
    S1GMAP("JP", 9200, 5195, 39, 1),
    S1GMAP("JP", 9210, 5200, 40, 1),
    S1GMAP("JP", 9220, 5205, 41, 1),
    S1GMAP("JP", 9230, 5210, 42, 1),
    S1GMAP("JP", 9240, 5215, 43, 1),
    S1GMAP("JP", 9250, 5220, 44, 1),
    S1GMAP("JP", 9260, 5725, 45, 1),
    S1GMAP("JP", 9270, 5230, 46, 2),
    S1GMAP("TW", 8390, 5180, 36, 1),
    S1GMAP("TW", 8400, 5185, 37, 1),
    S1GMAP("TW", 8410, 5190, 38, 1),
    S1GMAP("TW", 8420, 5195, 39, 1),
    S1GMAP("TW", 8430, 5200, 40, 1),
    S1GMAP("TW", 8440, 5205, 41, 1),
    S1GMAP("TW", 8450, 5210, 42, 1),
    S1GMAP("TW", 8460, 5215, 43, 1),
    S1GMAP("TW", 8470, 5220, 44, 1),
    S1GMAP("TW", 8480, 5225, 45, 1),
    S1GMAP("TW", 8490, 5230, 46, 1),
    S1GMAP("TW", 8500, 5235, 47, 1),
    S1GMAP("TW", 8510, 5240, 48, 1),
    S1GMAP("TW", 8395, 5745, 149, 2),
    S1GMAP("TW", 8415, 5750, 150, 2),
    S1GMAP("TW", 8435, 5755, 151, 2),
    S1GMAP("TW", 8455, 5760, 152, 2),
    S1GMAP("TW", 8475, 5765, 153, 2),
    S1GMAP("TW", 8495, 5770, 154, 2),
    S1GMAP("TW", 8405, 5775, 155, 4),
    S1GMAP("TW", 8445, 5780, 156, 4),
    S1GMAP("TW", 8485, 5785, 157, 4),
    S1GMAP("EU", 8635, 5180, 36, 1),
    S1GMAP("EU", 8645, 5185, 37, 1),
    S1GMAP("EU", 8655, 5190, 38, 1),
    S1GMAP("EU", 8665, 5195, 39, 1),
    S1GMAP("EU", 8675, 5200, 40, 1),
    S1GMAP("EU", 8640, 5205, 41, 2),
    S1GMAP("EU", 8660, 5210, 42, 2),
    S1GMAP("CN", 7550, 5180, 36, 1),
    S1GMAP("CN", 7565, 5185, 37, 1),
    S1GMAP("CN", 7570, 5190, 38, 1),
    S1GMAP("CN", 7585, 5195, 39, 1),
    S1GMAP("CN", 7595, 5200, 40, 1),
    S1GMAP("CN", 7605, 5205, 41, 1),
    S1GMAP("CN", 7615, 5210, 42, 1),
    S1GMAP("CN", 7625, 5215, 43, 1),
    S1GMAP("CN", 7635, 5220, 44, 1),
    S1GMAP("CN", 7645, 5225, 45, 1),
    S1GMAP("CN", 7655, 5230, 46, 1),
    S1GMAP("CN", 7665, 5235, 47, 1),
    S1GMAP("CN", 7675, 5240, 48, 1),
    S1GMAP("CN", 7685, 5745, 149, 1),
    S1GMAP("CN", 7695, 5750, 150, 1),
    S1GMAP("CN", 7705, 5755, 151, 1),
    S1GMAP("CN", 7795, 5760, 152, 1),
    S1GMAP("CN", 7805, 5765, 153, 1),
    S1GMAP("CN", 7815, 5770, 154, 1),
    S1GMAP("CN", 7825, 5775, 155, 1),
    S1GMAP("CN", 7835, 5780, 156, 1),
    S1GMAP("CN", 7845, 5785, 156, 1),
    S1GMAP("CN", 7855, 5790, 156, 1),
    S1GMAP("CN", 7865, 5795, 156, 1),
    S1GMAP("CN", 7800, 5800, 156, 2),
    S1GMAP("CN", 7820, 5805, 156, 2),
    S1GMAP("CN", 7840, 5810, 156, 2),
    S1GMAP("CN", 7860, 5815, 156, 2),
    S1GMAP("CN", 7810, 5820, 156, 4),
    S1GMAP("CN", 7850, 5825, 156, 4),
    S1GMAP("", 0, 0, 0, 0),
};

#define NUM_S1G_CHANNELS ARRAY_SIZE(s1g_map)
#define S1G_GUARD(p) (p && (p - s1g_map) < NUM_S1G_CHANNELS)

static const struct nrc_s1g_map* find_entry(const char* alpha2, int freq)
{
    const struct nrc_s1g_map *p = s1g_map;
    
//     nrc_dbg(NRC_DBG_S1G, "%s %s %d\n", __func__, alpha2, freq);
    
    while(S1G_GUARD(p) && memcmp(p->alpha2, alpha2, 2))
        p++;
        
    if(freq > 7500) {
        while(S1G_GUARD(p) && p->s1g_freq != freq)
            p++;
    }
    else if (freq > 0) {
        while(S1G_GUARD(p) && p->fw_freq != freq)
            p++;
    }
    
    if((p - s1g_map) > NUM_S1G_CHANNELS)
        p = &s1g_map[NUM_S1G_CHANNELS - 1];
    
//     nrc_dbg(NRC_DBG_S1G, "%s %s p->s1g_freq %d p->fw_freq %d\n", __func__, alpha2, p->s1g_freq, p->fw_freq);
    
    return p;
}

int nrc_get_s1g_freq(const char* alpha2, int ch)
{
    const struct nrc_s1g_map *p;
    
    nrc_dbg(NRC_DBG_S1G, "%s\n", __func__);
    
    p = find_entry(alpha2, 0);
    
    while(S1G_GUARD(p) && ch--)
        p++;
    
    nrc_dbg(NRC_DBG_S1G, "%s p->alpha2 %s p->s1g_freq %d p->fw_freq %d\n", __func__, p->alpha2, p->s1g_freq, p->fw_freq);
    
    return p->s1g_freq;
}

int nrc_freq_fw_s1g(const char* alpha2, int fw_freq)
{
    nrc_dbg(NRC_DBG_S1G, "%s\n", __func__);
    
    return find_entry(alpha2, fw_freq)->s1g_freq;
}

int nrc_freq_s1g_fw(const char* alpha2, int s1g_freq)
{
    nrc_dbg(NRC_DBG_S1G, "%s\n", __func__);
    
    return find_entry(alpha2, s1g_freq)->fw_freq;
}

int nrc_s1g_width(const char* alpha2, int s1g_freq)
{
    nrc_dbg(NRC_DBG_S1G, "%s\n", __func__);
    
    return find_entry(alpha2, s1g_freq)->width;
}
// 
int nrc_num_channels(const char* alpha2)
{
    const struct nrc_s1g_map *p1, *p2;
 
    nrc_dbg(NRC_DBG_S1G, "%s\n", __func__);

    p1 = p2 = find_entry(alpha2, 0);

    do{
        p2++;
    } while(S1G_GUARD(p2) && p2->alpha2[0] == alpha2[0] && p2->alpha2[1] == alpha2[1]);
    
    nrc_dbg(NRC_DBG_S1G, "%s num_channels %d\n", __func__, (int)(p2 - p1));
    
    return (int)(p2 - p1);
}

void nrc_remap_status(const char* alpha2, struct ieee80211_rx_status *status)
{
    int s1g_freq;
    
    nrc_dbg(NRC_DBG_S1G, "%s status->freq %d status->freq_offset %d\n", __func__, status->freq, status->freq_offset);
    
    status->freq_offset = 0;
    s1g_freq = nrc_freq_fw_s1g(alpha2, status->freq);
    
    nrc_dbg(NRC_DBG_S1G, "%s s1g_freq %d\n", __func__, s1g_freq);
    
    status->freq = s1g_freq / 10;
    status->freq_offset = (s1g_freq % 10 ? 1 : 0);
    
    nrc_dbg(NRC_DBG_S1G, "%s status->freq %d status->freq_offset %d\n", __func__, status->freq, status->freq_offset);
}

#endif /* CONFIG_S1G_CHANNEL */

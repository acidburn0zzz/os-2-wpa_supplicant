/*
 * hostapd - internal driver interface wrappers
 * Copyright (c) 2002-2009, Jouni Malinen <j@w1.fi>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Alternatively, this software may be distributed under the terms of BSD
 * license.
 *
 * See README and COPYING for more details.
 */

#ifndef DRIVER_I_H
#define DRIVER_I_H

#include "drivers/driver.h"
#include "config.h"

static inline void *
hostapd_driver_init(struct hostapd_data *hapd, const u8 *bssid)
{
	struct wpa_init_params params;
	void *ret;
	size_t i;

	if (hapd->driver == NULL || hapd->driver->hapd_init == NULL)
		return NULL;

	os_memset(&params, 0, sizeof(params));
	params.bssid = bssid;
	params.ifname = hapd->conf->iface;
	params.ssid = (const u8 *) hapd->conf->ssid.ssid;
	params.ssid_len = hapd->conf->ssid.ssid_len;
	params.test_socket = hapd->conf->test_socket;
	params.use_pae_group_addr = hapd->conf->use_pae_group_addr;

	params.num_bridge = hapd->iface->num_bss;
	params.bridge = os_zalloc(hapd->iface->num_bss * sizeof(char *));
	if (params.bridge == NULL)
		return NULL;
	for (i = 0; i < hapd->iface->num_bss; i++) {
		struct hostapd_data *bss = hapd->iface->bss[i];
		if (bss->conf->bridge[0])
			params.bridge[i] = bss->conf->bridge;
	}

	params.own_addr = hapd->own_addr;

	ret = hapd->driver->hapd_init(hapd, &params);
	os_free(params.bridge);

	return ret;
}

static inline void
hostapd_driver_deinit(struct hostapd_data *hapd)
{
	if (hapd->driver == NULL || hapd->driver->hapd_deinit == NULL)
		return;
	hapd->driver->hapd_deinit(hapd->drv_priv);
}

static inline int
hostapd_set_ieee8021x(struct hostapd_data *hapd, struct wpa_bss_params *params)
{
	if (hapd->driver == NULL || hapd->driver->set_ieee8021x == NULL)
		return 0;
	return hapd->driver->set_ieee8021x(hapd->drv_priv, params);
}

static inline int
hostapd_set_privacy(struct hostapd_data *hapd, int enabled)
{
	if (hapd->driver == NULL || hapd->driver->set_privacy == NULL)
		return 0;
	return hapd->driver->set_privacy(hapd->conf->iface, hapd->drv_priv,
					 enabled);
}

static inline int
hostapd_get_seqnum(const char *ifname, struct hostapd_data *hapd,
		   const u8 *addr, int idx, u8 *seq)
{
	if (hapd->driver == NULL || hapd->driver->get_seqnum == NULL)
		return 0;
	return hapd->driver->get_seqnum(ifname, hapd->drv_priv, addr, idx,
					seq);
}

static inline int
hostapd_flush(struct hostapd_data *hapd)
{
	if (hapd->driver == NULL || hapd->driver->flush == NULL)
		return 0;
	return hapd->driver->flush(hapd->drv_priv);
}

static inline int
hostapd_set_generic_elem(struct hostapd_data *hapd, const u8 *elem,
			 size_t elem_len)
{
	if (hapd->driver == NULL || hapd->driver->set_generic_elem == NULL)
		return 0;
	return hapd->driver->set_generic_elem(hapd->conf->iface,
					      hapd->drv_priv, elem, elem_len);
}

static inline int
hostapd_get_ssid(struct hostapd_data *hapd, u8 *buf, size_t len)
{
	if (hapd->driver == NULL || hapd->driver->hapd_get_ssid == NULL)
		return 0;
	return hapd->driver->hapd_get_ssid(hapd->conf->iface, hapd->drv_priv,
					   buf, len);
}

static inline int
hostapd_set_ssid(struct hostapd_data *hapd, const u8 *buf, size_t len)
{
	if (hapd->driver == NULL || hapd->driver->hapd_set_ssid == NULL)
		return 0;
	return hapd->driver->hapd_set_ssid(hapd->conf->iface, hapd->drv_priv,
					   buf, len);
}

static inline int
hostapd_set_countermeasures(struct hostapd_data *hapd, int enabled)
{
	if (hapd->driver == NULL ||
	    hapd->driver->hapd_set_countermeasures == NULL)
		return 0;
	return hapd->driver->hapd_set_countermeasures(hapd->drv_priv, enabled);
}

static inline int
hostapd_sta_add(const char *ifname, struct hostapd_data *hapd, const u8 *addr,
		u16 aid, u16 capability, const u8 *supp_rates,
		size_t supp_rates_len, u16 listen_interval,
		const struct ieee80211_ht_capabilities *ht_capabilities)
{
	struct hostapd_sta_add_params params;

	if (hapd->driver == NULL)
		return 0;
	if (hapd->driver->sta_add == NULL)
		return 0;

	os_memset(&params, 0, sizeof(params));
	params.addr = addr;
	params.aid = aid;
	params.capability = capability;
	params.supp_rates = supp_rates;
	params.supp_rates_len = supp_rates_len;
	params.listen_interval = listen_interval;
	params.ht_capabilities = ht_capabilities;
	return hapd->driver->sta_add(ifname, hapd->drv_priv, &params);
}

static inline int
hostapd_set_freq(struct hostapd_data *hapd, int mode, int freq, int channel,
		 int ht_enabled, int sec_channel_offset)
{
	struct hostapd_freq_params data;
	if (hapd->driver == NULL)
		return 0;
	if (hapd->driver->set_freq == NULL)
		return 0;
	os_memset(&data, 0, sizeof(data));
	data.mode = mode;
	data.freq = freq;
	data.channel = channel;
	data.ht_enabled = ht_enabled;
	data.sec_channel_offset = sec_channel_offset;
	return hapd->driver->set_freq(hapd->drv_priv, &data);
}

static inline int
hostapd_set_rts(struct hostapd_data *hapd, int rts)
{
	if (hapd->driver == NULL || hapd->driver->set_rts == NULL)
		return 0;
	return hapd->driver->set_rts(hapd->drv_priv, rts);
}

static inline int
hostapd_set_frag(struct hostapd_data *hapd, int frag)
{
	if (hapd->driver == NULL || hapd->driver->set_frag == NULL)
		return 0;
	return hapd->driver->set_frag(hapd->drv_priv, frag);
}

static inline int
hostapd_sta_set_flags(struct hostapd_data *hapd, u8 *addr,
		      int total_flags, int flags_or, int flags_and)
{
	if (hapd->driver == NULL || hapd->driver->sta_set_flags == NULL)
		return 0;
	return hapd->driver->sta_set_flags(hapd->drv_priv, addr, total_flags,
					   flags_or, flags_and);
}

static inline int
hostapd_set_rate_sets(struct hostapd_data *hapd, int *supp_rates,
		      int *basic_rates, int mode)
{
	if (hapd->driver == NULL || hapd->driver->set_rate_sets == NULL)
		return 0;
	return hapd->driver->set_rate_sets(hapd->drv_priv, supp_rates,
					   basic_rates, mode);
}

static inline int
hostapd_set_country(struct hostapd_data *hapd, const char *country)
{
	if (hapd->driver == NULL ||
	    hapd->driver->set_country == NULL)
		return 0;
	return hapd->driver->set_country(hapd->drv_priv, country);
}

static inline int
hostapd_set_cts_protect(struct hostapd_data *hapd, int value)
{
	if (hapd->driver == NULL || hapd->driver->set_cts_protect == NULL)
		return 0;
	return hapd->driver->set_cts_protect(hapd->drv_priv, value);
}

static inline int
hostapd_set_preamble(struct hostapd_data *hapd, int value)
{
	if (hapd->driver == NULL || hapd->driver->set_preamble == NULL)
		return 0;
	return hapd->driver->set_preamble(hapd->drv_priv, value);
}

static inline int
hostapd_set_short_slot_time(struct hostapd_data *hapd, int value)
{
	if (hapd->driver == NULL || hapd->driver->set_short_slot_time == NULL)
		return 0;
	return hapd->driver->set_short_slot_time(hapd->drv_priv, value);
}

static inline int
hostapd_set_tx_queue_params(struct hostapd_data *hapd, int queue, int aifs,
			    int cw_min, int cw_max, int burst_time)
{
	if (hapd->driver == NULL || hapd->driver->set_tx_queue_params == NULL)
		return 0;
	return hapd->driver->set_tx_queue_params(hapd->drv_priv, queue, aifs,
						 cw_min, cw_max, burst_time);
}

static inline int
hostapd_valid_bss_mask(struct hostapd_data *hapd, const u8 *addr,
		       const u8 *mask)
{
	if (hapd->driver == NULL || hapd->driver->valid_bss_mask == NULL)
		return 1;
	return hapd->driver->valid_bss_mask(hapd->drv_priv, addr, mask);
}

static inline int
hostapd_if_add(struct hostapd_data *hapd, enum wpa_driver_if_type type,
	       const char *ifname, const u8 *addr, void *bss_ctx)
{
	if (hapd->driver == NULL || hapd->driver->if_add == NULL)
		return -1;
	return hapd->driver->if_add(hapd->conf->iface, hapd->drv_priv, type,
				    ifname, addr, bss_ctx);
}

static inline int
hostapd_if_remove(struct hostapd_data *hapd, enum wpa_driver_if_type type,
		  const char *ifname)
{
	if (hapd->driver == NULL || hapd->driver->if_remove == NULL)
		return -1;
	return hapd->driver->if_remove(hapd->drv_priv, type, ifname);
}

static inline struct hostapd_hw_modes *
hostapd_get_hw_feature_data(struct hostapd_data *hapd, u16 *num_modes,
			    u16 *flags)
{
	if (hapd->driver == NULL ||
	    hapd->driver->get_hw_feature_data == NULL)
		return NULL;
	return hapd->driver->get_hw_feature_data(hapd->drv_priv, num_modes,
						 flags);
}

static inline int
hostapd_driver_commit(struct hostapd_data *hapd)
{
	if (hapd->driver == NULL || hapd->driver->commit == NULL)
		return 0;
	return hapd->driver->commit(hapd->drv_priv);
}

static inline int
hostapd_set_ht_params(const char *ifname, struct hostapd_data *hapd,
		      const u8 *ht_capab, size_t ht_capab_len,
		      const u8 *ht_oper, size_t ht_oper_len)
{
	if (hapd->driver == NULL || hapd->driver->set_ht_params == NULL ||
	    ht_capab == NULL || ht_oper == NULL)
		return 0;
	return hapd->driver->set_ht_params(
		ifname, hapd->drv_priv, ht_capab, ht_capab_len,
		ht_oper, ht_oper_len);
}

static inline int
hostapd_drv_none(struct hostapd_data *hapd)
{
	return hapd->driver && os_strcmp(hapd->driver->name, "none") == 0;
}

static inline int hostapd_driver_scan(struct hostapd_data *hapd,
				      struct wpa_driver_scan_params *params)
{
	if (hapd->driver && hapd->driver->scan2)
		return hapd->driver->scan2(hapd->drv_priv, params);
	return -1;
}

static inline struct wpa_scan_results * hostapd_driver_get_scan_results(
	struct hostapd_data *hapd)
{
	if (hapd->driver && hapd->driver->get_scan_results2)
		return hapd->driver->get_scan_results2(hapd->drv_priv);
	return NULL;
}

#endif /* DRIVER_I_H */

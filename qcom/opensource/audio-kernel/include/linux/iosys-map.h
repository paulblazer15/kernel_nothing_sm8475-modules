/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef __AUDIO_IOSYS_MAP_COMPAT_H__
#define __AUDIO_IOSYS_MAP_COMPAT_H__

#include <linux/dma-buf.h>
#include <linux/errno.h>

/*
 * Android 5.10 predates struct iosys_map and uses pointer-returning dma-buf
 * vmap helpers. Keep the newer audio driver interface while translating it
 * to the 5.10 API. Newer kernels provide their own linux/iosys-map.h before
 * this external-module compatibility header is searched.
 */
struct iosys_map {
	void *vaddr;
};

static inline int audio_dma_buf_vmap(struct dma_buf *dmabuf,
				     struct iosys_map *map)
{
	map->vaddr = dma_buf_vmap(dmabuf);
	return map->vaddr ? 0 : -ENOMEM;
}

static inline void audio_dma_buf_vunmap(struct dma_buf *dmabuf,
					struct iosys_map *map)
{
	dma_buf_vunmap(dmabuf, map->vaddr);
}

#define dma_buf_vmap(dmabuf, map) audio_dma_buf_vmap((dmabuf), (map))
#define dma_buf_vunmap(dmabuf, map) audio_dma_buf_vunmap((dmabuf), (map))

#endif /* __AUDIO_IOSYS_MAP_COMPAT_H__ */

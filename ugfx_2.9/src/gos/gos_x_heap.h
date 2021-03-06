/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#ifndef _GOS_X_HEAP_H
#define _GOS_X_HEAP_H

#if GOS_NEED_X_HEAP || defined(__DOXYGEN__)

/*===========================================================================*/
/* Type definitions                                                          */
/*===========================================================================*/

#if GFX_OS_HEAP_SIZE != 0 || defined(__DOXYGEN__)
	/**
	 * @brief	Take a chunk of memory and add it to the available heap
	 * @note	Memory added must obviously not already be on the heap.
	 * @note	It is allowable to add multiple non-contiguous blocks of memory
	 * 			to the heap. If however it is contiguous with a previously added block
	 * 			it will get merged with the existing block in order to allow
	 * 			allocations that span the boundary.
	 * @pre		GFX_OS_HEAP_SIZE != 0 and an operating system that uses the
	 * 			internal ugfx heap allocator rather than its own allocator.
	 */
	void gfxAddHeapBlock(void *ptr, gMemSize sz);
#endif

void *gfxAlloc(gMemSize sz);
void *gfxRealloc(void *ptr, gMemSize oldsz, gMemSize newsz);
void gfxFree(void *ptr);

#endif /* GOS_NEED_X_HEAP */
#endif /* _GOS_X_HEAP_H */

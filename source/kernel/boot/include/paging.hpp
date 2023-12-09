#pragma once
#include "../../ng.hpp"

struct PageDirectoryEntry {
    u4 PresentFlag : 1;
    u4 ReadWriteFlag : 1;
    u4 SupervisorFlag : 1;
    u4 WriteThroughFlag : 1;
    u4 CacheDisableFlag : 1;
    u4 AccessedFlag : 1;
    u4 AvailableFlag : 1;
    u4 PageSizeFlag : 1;
    u4 Available : 4;
    u4 Address : 20;
    PageDirectoryEntry();
};

struct page {
	u4 present		: 1;	// page present in memory
	u4 rw		: 1;	// read-only if 0, rw else
	u4 user		: 1;	// supervisor if 0, user else
	u4 accessed		: 1;	// accessed since last refresh?
	u4 dirty		: 1;	// written since last refresh?
	u4 unused		: 7;
	u4 frame		: 20;	// frame address (shifted left 12 bits)
}; __attribute__((packed));

struct PageTableEntry {
    u4 PresentFlag : 1;
    u4 ReadWriteFlag : 1;
    u4 SupervisorFlag : 1;
    u4 WriteThroughFlag : 1;
    u4 CacheDisableFlag : 1;
    u4 AccessedFlag : 1;
    u4 DirtyFlag : 1;
    u4 PageAttributeTable : 1;
    u4 GlobalFlag : 1;
    u4 Available : 3;
    u4 Address : 20;
    PageTableEntry();
};
#include "include/paging.hpp"

PageDirectoryEntry::PageDirectoryEntry()
{
    this->PresentFlag = 0;
    this->SupervisorFlag = 1;
    this->ReadWriteFlag = 1;    
}

PageTableEntry::PageTableEntry()
{
    this->SupervisorFlag = 1;
    this->ReadWriteFlag = 1;
    this->PresentFlag = 1;
}

#ifndef __LINUX_BRIDGE_EBT_MARK_T_H
#define __LINUX_BRIDGE_EBT_MARK_T_H

struct ebt_mark_t_info
{
	unsigned long mark;
	
	int target;
};
#define EBT_MARK_TARGET "mark"

#endif
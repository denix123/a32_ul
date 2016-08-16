/**
 * @file op_model_p4.c
 * P4 model-specific MSR operations
 *
 * @remark Copyright 2002 OProfile authors
 * @remark Read the file COPYING
 *
 * @author Graydon Hoare
 */

#include "op_x86_model.h"
#include "op_msr.h"
#include "op_apic.h"
#include "op_arch.h"

#define NUM_EVENTS 39

#define NUM_COUNTERS_NON_HT 8
#define NUM_ESCRS_NON_HT 45
#define NUM_CCCRS_NON_HT 18
#define NUM_CONTROLS_NON_HT (NUM_ESCRS_NON_HT + NUM_CCCRS_NON_HT)

#define NUM_COUNTERS_HT2 4
#define NUM_ESCRS_HT2 23
#define NUM_CCCRS_HT2 9
#define NUM_CONTROLS_HT2 (NUM_ESCRS_HT2 + NUM_CCCRS_HT2)

static unsigned int num_counters = NUM_COUNTERS_NON_HT;


static inline void setup_num_counters(void)
{
#ifdef HT_SUPPORT
	if (smp_num_siblings == 2)
		num_counters = NUM_COUNTERS_HT2;
#endif
}

static int inline addr_increment(void)
{
#ifdef HT_SUPPORT
	return smp_num_siblings == 2 ? 2 : 1;
#else
	return 1;
#endif
}


struct p4_counter_binding {
	int virt_counter;
	int counter_address;
	int cccr_address;
};

struct p4_event_binding {
	
	int escr_select;
	
	int event_select;
	struct {
		
		int virt_counter;
		
		int escr_address;
	} bindings[2];
};



#define CTR_BPU_0      (1 << 0)
#define CTR_MS_0       (1 << 1)
#define CTR_FLAME_0    (1 << 2)
#define CTR_IQ_4       (1 << 3)
#define CTR_BPU_2      (1 << 4)
#define CTR_MS_2       (1 << 5)
#define CTR_FLAME_2    (1 << 6)
#define CTR_IQ_5       (1 << 7)

static struct p4_counter_binding p4_counters[NUM_COUNTERS_NON_HT] = {
	{ CTR_BPU_0,   MSR_P4_BPU_PERFCTR0,   MSR_P4_BPU_CCCR0 },
	{ CTR_MS_0,    MSR_P4_MS_PERFCTR0,    MSR_P4_MS_CCCR0 },
	{ CTR_FLAME_0, MSR_P4_FLAME_PERFCTR0, MSR_P4_FLAME_CCCR0 },
	{ CTR_IQ_4,    MSR_P4_IQ_PERFCTR4,    MSR_P4_IQ_CCCR4 },
	{ CTR_BPU_2,   MSR_P4_BPU_PERFCTR2,   MSR_P4_BPU_CCCR2 },
	{ CTR_MS_2,    MSR_P4_MS_PERFCTR2,    MSR_P4_MS_CCCR2 },
	{ CTR_FLAME_2, MSR_P4_FLAME_PERFCTR2, MSR_P4_FLAME_CCCR2 },
	{ CTR_IQ_5,    MSR_P4_IQ_PERFCTR5,    MSR_P4_IQ_CCCR5 }
};

#define NUM_UNUSED_CCCRS	NUM_CCCRS_NON_HT - NUM_COUNTERS_NON_HT

static int p4_unused_cccr[NUM_UNUSED_CCCRS] = {
	MSR_P4_BPU_CCCR1, 	MSR_P4_BPU_CCCR3,
	MSR_P4_MS_CCCR1, 	MSR_P4_MS_CCCR3,
	MSR_P4_FLAME_CCCR1, 	MSR_P4_FLAME_CCCR3,
	MSR_P4_IQ_CCCR0, 	MSR_P4_IQ_CCCR1,
	MSR_P4_IQ_CCCR2, 	MSR_P4_IQ_CCCR3
};


static struct p4_event_binding p4_events[NUM_EVENTS] = {
	
	{ 
		0x05, 0x06, 
		{ {CTR_IQ_4, MSR_P4_CRU_ESCR2},
		  {CTR_IQ_5, MSR_P4_CRU_ESCR3} }
	},
	
	{ 
		0x04, 0x03, 
		{ { CTR_IQ_4, MSR_P4_CRU_ESCR0},
		  { CTR_IQ_5, MSR_P4_CRU_ESCR1} }
	},
	
	{ 
		0x01, 0x01,
		{ { CTR_MS_0, MSR_P4_TC_ESCR0},  
		  { CTR_MS_2, MSR_P4_TC_ESCR1} }
	},
	
	{ 
		0x00, 0x03, 
		{ { CTR_BPU_0, MSR_P4_BPU_ESCR0},
		  { CTR_BPU_2, MSR_P4_BPU_ESCR1} }
	},

	{ 
		0x03, 0x18,
		{ { CTR_BPU_0, MSR_P4_ITLB_ESCR0},
		  { CTR_BPU_2, MSR_P4_ITLB_ESCR1} }
	},

	{ 
		0x05, 0x02,
		{ { CTR_FLAME_0, MSR_P4_DAC_ESCR0},
		  { CTR_FLAME_2, MSR_P4_DAC_ESCR1} }
	},

	{ 
		0x02, 0x08,
		{ { CTR_FLAME_0, MSR_P4_SAAT_ESCR0},
		  { CTR_FLAME_2, MSR_P4_SAAT_ESCR1} }
	},

	{ 
		0x02, 0x04, 
		{ { CTR_FLAME_0, MSR_P4_SAAT_ESCR0},
		  { CTR_FLAME_2, MSR_P4_SAAT_ESCR1} }
	},

	{ 
		0x02, 0x05,
		{ { CTR_FLAME_0, MSR_P4_SAAT_ESCR0},
		  { CTR_FLAME_2, MSR_P4_SAAT_ESCR1} }
	},

	{ 
		0x02, 0x03,
		{ { CTR_BPU_0, MSR_P4_MOB_ESCR0},
		  { CTR_BPU_2, MSR_P4_MOB_ESCR1} }
	},

	{ 
		0x04, 0x01,
		{ { CTR_BPU_0, MSR_P4_PMH_ESCR0},
		  { CTR_BPU_2, MSR_P4_PMH_ESCR1} }
	},

	{ 
		0x07, 0x0c, 
		{ { CTR_BPU_0, MSR_P4_BSU_ESCR0},
		  { CTR_BPU_2, MSR_P4_BSU_ESCR1} }
	},

	{ 
		0x06, 0x03, 
		{ { CTR_BPU_0, MSR_P4_FSB_ESCR0},
		  { 0, 0 } }
	},

	{ 
		0x06, 0x1a, 
		{ { CTR_BPU_2, MSR_P4_FSB_ESCR1},
		  { 0, 0 } }
	},

	{ 
		0x06, 0x17, 
		{ { CTR_BPU_0, MSR_P4_FSB_ESCR0},
		  { CTR_BPU_2, MSR_P4_FSB_ESCR1} }
	},

	{ 
		0x07, 0x05, 
		{ { CTR_BPU_0, MSR_P4_BSU_ESCR0},
		  { 0, 0 } }
	},

	{ 
		0x07, 0x06,
		{ { CTR_BPU_2, MSR_P4_BSU_ESCR1 },  
		  { 0, 0 } }
	},

	{ 
		0x05, 0x03, 
		{ { CTR_IQ_4, MSR_P4_CRU_ESCR2},
		  { CTR_IQ_5, MSR_P4_CRU_ESCR3} }
	},

	{ 
		0x01, 0x34,
		{ { CTR_FLAME_0, MSR_P4_FIRM_ESCR0},
		  { CTR_FLAME_2, MSR_P4_FIRM_ESCR1} }
	},
  
	{ 
		0x01, 0x08, 
		{ { CTR_FLAME_0, MSR_P4_FIRM_ESCR0},
		  { CTR_FLAME_2, MSR_P4_FIRM_ESCR1} }
	},
  
	{ 
		0x01, 0x0c, 
		{ { CTR_FLAME_0, MSR_P4_FIRM_ESCR0},
		  { CTR_FLAME_2, MSR_P4_FIRM_ESCR1} }
	},

	{ 
		0x01, 0x0a, 
		{ { CTR_FLAME_0, MSR_P4_FIRM_ESCR0},
		  { CTR_FLAME_2, MSR_P4_FIRM_ESCR1} }
	},

	{ 
		0x01, 0x0e,
		{ { CTR_FLAME_0, MSR_P4_FIRM_ESCR0},
		  { CTR_FLAME_2, MSR_P4_FIRM_ESCR1} }
	},

	{ 
		0x01, 0x02, 
		{ { CTR_FLAME_0, MSR_P4_FIRM_ESCR0},
		  { CTR_FLAME_2, MSR_P4_FIRM_ESCR1} }
	},
  
	{ 
		0x01, 0x1a, 
		{ { CTR_FLAME_0, MSR_P4_FIRM_ESCR0},
		  { CTR_FLAME_2, MSR_P4_FIRM_ESCR1} }
	},

	{ 
		0x01, 0x04, 
		{ { CTR_FLAME_0, MSR_P4_FIRM_ESCR0},
		  { CTR_FLAME_2, MSR_P4_FIRM_ESCR1} }
	},
  
	{ 
		0x01, 0x2e, 
		{ { CTR_FLAME_0, MSR_P4_FIRM_ESCR0},
		  { CTR_FLAME_2, MSR_P4_FIRM_ESCR1} }
	},
  
	{ 
		0x05, 0x02, 
		{ { CTR_IQ_4, MSR_P4_CRU_ESCR2},
		  { CTR_IQ_5, MSR_P4_CRU_ESCR3} }
	},

	{ 
		0x06, 0x13 ,
		{ { CTR_BPU_0, MSR_P4_FSB_ESCR0},
		  { CTR_BPU_2, MSR_P4_FSB_ESCR1} }
	},
  
	{ 
		0x00, 0x05, 
		{ { CTR_MS_0, MSR_P4_MS_ESCR0},
		  { CTR_MS_2, MSR_P4_MS_ESCR1} }
	},

	{ 
		0x00, 0x09,
		{ { CTR_MS_0, MSR_P4_MS_ESCR0},
		  { CTR_MS_2, MSR_P4_MS_ESCR1} }
	},

	{ 
		0x05, 0x08,
		{ { CTR_IQ_4, MSR_P4_CRU_ESCR2},
		  { CTR_IQ_5, MSR_P4_CRU_ESCR3} }
	},

	{ 
		0x05, 0x0c,
		{ { CTR_IQ_4, MSR_P4_CRU_ESCR2},
		  { CTR_IQ_5, MSR_P4_CRU_ESCR3} }
	},

	{ 
		0x05, 0x09,
		{ { CTR_IQ_4, MSR_P4_CRU_ESCR2},
		  { CTR_IQ_5, MSR_P4_CRU_ESCR3} }
	},

	{ 
		0x04, 0x02, 
		{ { CTR_IQ_4, MSR_P4_CRU_ESCR0},
		  { CTR_IQ_5, MSR_P4_CRU_ESCR1} }
	},

	{ 
		0x04, 0x01,
		{ { CTR_IQ_4, MSR_P4_CRU_ESCR0},
		  { CTR_IQ_5, MSR_P4_CRU_ESCR1} }
	},

	{     
		0x02, 0x02, 
		{ { CTR_IQ_4, MSR_P4_RAT_ESCR0},
		  { CTR_IQ_5, MSR_P4_RAT_ESCR1} }
	},

	{ 
		0x02, 0x05, 
		{ { CTR_MS_0, MSR_P4_TBPU_ESCR0},
		  { CTR_MS_2, MSR_P4_TBPU_ESCR1} }
	},

	{ 
		0x02, 0x04,
		{ { CTR_MS_0, MSR_P4_TBPU_ESCR0},
		  { CTR_MS_2, MSR_P4_TBPU_ESCR1} }
	}
};


#define MISC_PMC_ENABLED_P(x) ((x) & 1 << 7)

#define ESCR_RESERVED_BITS 0x80000003
#define ESCR_CLEAR(escr) ((escr) &= ESCR_RESERVED_BITS)
#define ESCR_SET_USR_0(escr, usr) ((escr) |= (((usr) & 1) << 2))
#define ESCR_SET_OS_0(escr, os) ((escr) |= (((os) & 1) << 3))
#define ESCR_SET_USR_1(escr, usr) ((escr) |= (((usr) & 1)))
#define ESCR_SET_OS_1(escr, os) ((escr) |= (((os) & 1) << 1))
#define ESCR_SET_EVENT_SELECT(escr, sel) ((escr) |= (((sel) & 0x3f) << 25))
#define ESCR_SET_EVENT_MASK(escr, mask) ((escr) |= (((mask) & 0xffff) << 9))
#define ESCR_READ(escr, high, ev, i) do {rdmsr(ev->bindings[(i)].escr_address, (escr), (high));} while (0)
#define ESCR_WRITE(escr, high, ev, i) do {wrmsr(ev->bindings[(i)].escr_address, (escr), (high));} while (0)

#define CCCR_RESERVED_BITS 0x38030FFF
#define CCCR_CLEAR(cccr) ((cccr) &= CCCR_RESERVED_BITS)
#define CCCR_SET_REQUIRED_BITS(cccr) ((cccr) |= 0x00030000)
#define CCCR_SET_ESCR_SELECT(cccr, sel) ((cccr) |= (((sel) & 0x07) << 13))
#define CCCR_SET_PMI_OVF_0(cccr) ((cccr) |= (1 << 26))
#define CCCR_SET_PMI_OVF_1(cccr) ((cccr) |= (1 << 27))
#define CCCR_SET_ENABLE(cccr) ((cccr) |= (1 << 12))
#define CCCR_SET_DISABLE(cccr) ((cccr) &= ~(1 << 12))
#define CCCR_READ(low, high, i) do {rdmsr(p4_counters[(i)].cccr_address, (low), (high));} while (0)
#define CCCR_WRITE(low, high, i) do {wrmsr(p4_counters[(i)].cccr_address, (low), (high));} while (0)
#define CCCR_OVF_P(cccr) ((cccr) & (1U << 31))
#define CCCR_CLEAR_OVF(cccr) ((cccr) &= (~(1U << 31)))

#define CTR_READ(l, h, i) do {rdmsr(p4_counters[(i)].counter_address, (l), (h));} while (0)
#define CTR_WRITE(l, i) do {wrmsr(p4_counters[(i)].counter_address, -(u32)(l), -1);} while (0)
#define CTR_OVERFLOW_P(ctr) (!((ctr) & 0x80000000))


static unsigned int get_stagger(void)
{
#ifdef HT_SUPPORT
	int cpu;
	if (smp_num_siblings > 1) {
		cpu = smp_processor_id();
		return (cpu_sibling_map[cpu] > cpu) ? 0 : 1;
	}
#endif	
	return 0;
}


#define VIRT_CTR(stagger, i) ((i) + ((num_counters) * (stagger)))


static void p4_fill_in_addresses(struct op_msrs * const msrs)
{
	unsigned int i; 
	unsigned int addr, stag;

	setup_num_counters();
	stag = get_stagger();

	
	for (i = 0; i < num_counters; ++i) {
		msrs->counters.addrs[i] =
			p4_counters[VIRT_CTR(stag, i)].counter_address;
	}

	

	
	for (i = 0, addr = MSR_P4_BPU_CCCR0 + stag;
	     addr <= MSR_P4_IQ_CCCR5; ++i, addr += addr_increment()) {
		msrs->controls.addrs[i] = addr;
	}
	
	
	for (addr = MSR_P4_BSU_ESCR0 + stag;
	     addr < MSR_P4_IQ_ESCR0; ++i, addr += addr_increment()) {
		msrs->controls.addrs[i] = addr;
	}

	if (boot_cpu_data.x86_model >= 0x3) {
		for (addr = MSR_P4_BSU_ESCR0 + stag;
		     addr <= MSR_P4_BSU_ESCR1; ++i, addr += addr_increment()) {
			msrs->controls.addrs[i] = addr;
		}
	} else {
		for (addr = MSR_P4_IQ_ESCR0 + stag;
		     addr <= MSR_P4_IQ_ESCR1; ++i, addr += addr_increment()) {
			msrs->controls.addrs[i] = addr;
		}
	}

	for (addr = MSR_P4_RAT_ESCR0 + stag;
	     addr <= MSR_P4_SSU_ESCR0; ++i, addr += addr_increment()) {
		msrs->controls.addrs[i] = addr;
	}
	
	for (addr = MSR_P4_MS_ESCR0 + stag;
	     addr <= MSR_P4_TC_ESCR1; ++i, addr += addr_increment()) { 
		msrs->controls.addrs[i] = addr;
	}
	
	for (addr = MSR_P4_IX_ESCR0 + stag;
	     addr <= MSR_P4_CRU_ESCR3; ++i, addr += addr_increment()) { 
		msrs->controls.addrs[i] = addr;
	}

	

	if (num_counters == NUM_COUNTERS_NON_HT) {		
		
		msrs->controls.addrs[i++] = MSR_P4_CRU_ESCR5;
		msrs->controls.addrs[i++] = MSR_P4_CRU_ESCR4;

	} else if (stag == 0) {
		msrs->controls.addrs[i++] = MSR_P4_CRU_ESCR4;

	} else {
		msrs->controls.addrs[i++] = MSR_P4_CRU_ESCR5;
		msrs->controls.addrs[i++] = MSR_P4_CRU_ESCR5;
	}
}


static void pmc_setup_one_p4_counter(unsigned int ctr)
{
	int i;
	int const maxbind = 2;
	unsigned int cccr = 0;
	unsigned int escr = 0;
	unsigned int high = 0;
	unsigned int counter_bit;
	struct p4_event_binding * ev = NULL;
	unsigned int stag;

	stag = get_stagger();
	
	
	counter_bit = 1 << VIRT_CTR(stag, ctr);
	
	
	if (sysctl.ctr[ctr].event <= 0 || sysctl.ctr[ctr].event > NUM_EVENTS) {
		printk(KERN_ERR 
		       "oprofile: P4 event code 0x%x out of range\n", 
		       sysctl.ctr[ctr].event);
		return;
	}
	
	ev = &(p4_events[sysctl.ctr[ctr].event - 1]);
	
	for (i = 0; i < maxbind; i++) {
		if (ev->bindings[i].virt_counter & counter_bit) {

			
			ESCR_READ(escr, high, ev, i);
			ESCR_CLEAR(escr);
			if (stag == 0) {
				ESCR_SET_USR_0(escr, sysctl.ctr[ctr].user);
				ESCR_SET_OS_0(escr, sysctl.ctr[ctr].kernel);
			} else {
				ESCR_SET_USR_1(escr, sysctl.ctr[ctr].user);
				ESCR_SET_OS_1(escr, sysctl.ctr[ctr].kernel);
			}
			ESCR_SET_EVENT_SELECT(escr, ev->event_select);
			ESCR_SET_EVENT_MASK(escr, sysctl.ctr[ctr].unit_mask);			
			ESCR_WRITE(escr, high, ev, i);
		       
			
			CCCR_READ(cccr, high, VIRT_CTR(stag, ctr));
			CCCR_CLEAR(cccr);
			CCCR_SET_REQUIRED_BITS(cccr);
			CCCR_SET_ESCR_SELECT(cccr, ev->escr_select);
			if (stag == 0) {
				CCCR_SET_PMI_OVF_0(cccr);
			} else {
				CCCR_SET_PMI_OVF_1(cccr);
			}
			CCCR_WRITE(cccr, high, VIRT_CTR(stag, ctr));
			return;
		}
	}

	printk(KERN_ERR 
	       "oprofile: P4 event code 0x%x no binding, ctr %d\n",
	       sysctl.ctr[ctr].event, ctr);
}


static void p4_setup_ctrs(struct op_msrs const * const msrs)
{
	unsigned int i;
	unsigned int low, high;
	unsigned int addr;
	unsigned int stag;

	stag = get_stagger();

	rdmsr(MSR_IA32_MISC_ENABLE, low, high);
	if (!MISC_PMC_ENABLED_P(low)) {
		printk(KERN_ERR "oprofile: P4 PMC not available\n");
		return;
	}

	
	for (i = 0 ; i < num_counters ; i++) {
		rdmsr(p4_counters[VIRT_CTR(stag, i)].cccr_address, low, high);
		CCCR_CLEAR(low);
		CCCR_SET_REQUIRED_BITS(low);
		wrmsr(p4_counters[VIRT_CTR(stag, i)].cccr_address, low, high);
	}

	
	for (i = stag ; i < NUM_UNUSED_CCCRS ; i += addr_increment()) {
		rdmsr(p4_unused_cccr[i], low, high);
		CCCR_CLEAR(low);
		CCCR_SET_REQUIRED_BITS(low);
		wrmsr(p4_unused_cccr[i], low, high);
	}

	
	for (addr = MSR_P4_BSU_ESCR0 + stag;
	     addr <  MSR_P4_IQ_ESCR0; addr += addr_increment()) {
		wrmsr(addr, 0, 0);
	}

	
	if (boot_cpu_data.x86_model < 0x3) {
		wrmsr(MSR_P4_IQ_ESCR0, 0, 0);
		wrmsr(MSR_P4_IQ_ESCR1, 0, 0);
	}

	for (addr = MSR_P4_RAT_ESCR0 + stag;
	     addr <= MSR_P4_SSU_ESCR0; ++i, addr += addr_increment()) {
		wrmsr(addr, 0, 0);
	}
	
	for (addr = MSR_P4_MS_ESCR0 + stag;
	     addr <= MSR_P4_TC_ESCR1; addr += addr_increment()) { 
		wrmsr(addr, 0, 0);
	}
	
	for (addr = MSR_P4_IX_ESCR0 + stag;
	     addr <= MSR_P4_CRU_ESCR3; addr += addr_increment()) { 
		wrmsr(addr, 0, 0);
	}

	if (num_counters == NUM_COUNTERS_NON_HT) {		
		wrmsr(MSR_P4_CRU_ESCR4, 0, 0);
		wrmsr(MSR_P4_CRU_ESCR5, 0, 0);
	} else if (stag == 0) {
		wrmsr(MSR_P4_CRU_ESCR4, 0, 0);
	} else {
		wrmsr(MSR_P4_CRU_ESCR5, 0, 0);
	}		
	
	
	for (i = 0 ; i < num_counters ; ++i) {
		if (sysctl.ctr[i].event) {
			pmc_setup_one_p4_counter(i);
			CTR_WRITE(sysctl.ctr[i].count, VIRT_CTR(stag, i));
		}
	}
}


static void p4_check_ctrs(unsigned int const cpu, 
			  struct op_msrs const * const msrs,
			  struct pt_regs * const regs)
{
	unsigned long ctr, low, high, stag, real;
	int i;

	stag = get_stagger();

	for (i = 0; i < num_counters; ++i) {
		
		if (!sysctl.ctr[i].enabled) 
			continue;

		
		real = VIRT_CTR(stag, i);

		CCCR_READ(low, high, real);
 		CTR_READ(ctr, high, real);
		if (CCCR_OVF_P(low) || CTR_OVERFLOW_P(ctr)) {
			op_do_profile(cpu, instruction_pointer(regs), IRQ_ENABLED(regs), i);
 			CTR_WRITE(oprof_data[cpu].ctr_count[i], real);
			CCCR_CLEAR_OVF(low);
			CCCR_WRITE(low, high, real);
 			CTR_WRITE(oprof_data[cpu].ctr_count[i], real);
		}
	}

	
	apic_write(APIC_LVTPC, apic_read(APIC_LVTPC) & ~APIC_LVT_MASKED);
}


static void p4_start(struct op_msrs const * const msrs)
{
	unsigned int low, high, stag;
	int i;

	stag = get_stagger();

	for (i = 0; i < num_counters; ++i) {
		if (!sysctl.ctr[i].enabled)
			continue;
		CCCR_READ(low, high, VIRT_CTR(stag, i));
		CCCR_SET_ENABLE(low);
		CCCR_WRITE(low, high, VIRT_CTR(stag, i));
	}
}


static void p4_stop(struct op_msrs const * const msrs)
{
	unsigned int low, high, stag;
	int i;

	stag = get_stagger();

	for (i = 0; i < num_counters; ++i) {
		
		if (!sysctl.ctr[i].enabled)
			continue;
		CCCR_READ(low, high, VIRT_CTR(stag, i));
		CCCR_SET_DISABLE(low);
		CCCR_WRITE(low, high, VIRT_CTR(stag, i));
	}
}

#ifdef HT_SUPPORT

struct op_x86_model_spec const op_p4_ht2_spec = {
	.num_counters = NUM_COUNTERS_HT2,
	.num_controls = NUM_CONTROLS_HT2,
	.fill_in_addresses = &p4_fill_in_addresses,
	.setup_ctrs = &p4_setup_ctrs,
	.check_ctrs = &p4_check_ctrs,
	.start = &p4_start,
	.stop = &p4_stop
};
#endif

struct op_x86_model_spec const op_p4_spec = {
	.num_counters = NUM_COUNTERS_NON_HT,
	.num_controls = NUM_CONTROLS_NON_HT,
	.fill_in_addresses = &p4_fill_in_addresses,
	.setup_ctrs = &p4_setup_ctrs,
	.check_ctrs = &p4_check_ctrs,
	.start = &p4_start,
	.stop = &p4_stop
};
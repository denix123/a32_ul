#ifndef HW_MIPS_H
#define HW_MIPS_H

PCIBus *pci_gt64120_init(qemu_irq *pic);

void *ds1225y_init(hwaddr mem_base, const char *filename);

int g364fb_mm_init(hwaddr vram_base,
                   hwaddr ctrl_base, int it_shift,
                   qemu_irq irq);

void mipsnet_init(int base, qemu_irq irq, NICInfo *nd);

extern void jazz_led_init(hwaddr base);

extern void cpu_mips_irq_init_cpu(CPUOldState *env);

extern void cpu_mips_clock_init(CPUOldState *);

typedef struct rc4030DMAState *rc4030_dma;
void rc4030_dma_memory_rw(void *opaque, hwaddr addr, uint8_t *buf, int len, int is_write);
void rc4030_dma_read(void *dma, uint8_t *buf, int len);
void rc4030_dma_write(void *dma, uint8_t *buf, int len);

void *rc4030_init(qemu_irq timer, qemu_irq jazz_bus,
                  qemu_irq **irqs, rc4030_dma **dmas);

void dp83932_init(NICInfo *nd, hwaddr base, int it_shift,
                  qemu_irq irq, void* mem_opaque,
                  void (*memory_rw)(void *opaque, hwaddr addr, uint8_t *buf, int len, int is_write));

#endif

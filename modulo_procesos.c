#include <linux/init.h>
#include <linux/module.h>

#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/hugetlb.h>
#include <linux/mman.h>
#include <linux/mmzone.h>
#include <linux/proc_fs.h>
#include <linux/quicklist.h>
#include <linux/seq_file.h>
#include <linux/swap.h>
#include <linux/vmstat.h>
#include <linux/atomic.h>
#include <linux/vmalloc.h>
#ifdef CONFIG_CMA
#include <linux/cma.h>
#endif
#include <asm/page.h>
#include <asm/pgtable.h>
#include "internal.h"

MODULE_LICENSE("GPL");

void __attribute__((weak)) arch_report_meminfo(struct seq_file *m)
{
}

static int meminfo_proc_show(struct seq_file *m, void *v)
{
	struct sysinfo i;
	unsigned long committed;
	


	unsigned long pages[NR_LRU_LISTS];
	int lru;

/*
 * display in kilobytes.
 */
#define K(x) ((x) << (PAGE_SHIFT - 10))
	si_meminfo(&i);

	committed = percpu_counter_read_positive(&vm_committed_as);

	

	for (lru = LRU_BASE; lru < NR_LRU_LISTS; lru++)
		pages[lru] = global_page_state(NR_LRU_BASE + lru);




	/*
	 * Tagged format, for easy grepping and expansion.
	 */
	seq_printf(m,
		"Carne:200815396\n"
		"Nombre:Servio Jose Boguerin Guerra\n"
		"Sistema Operativo:Elementary OS\n"
		"Nombre del proceso:       %8lu \n"
		"PID:        %8lu \n"		
		"Estado:        %8lu \n"
		
,
		K(i.totalram),
		K(i.freeram),
		K(i.bufferram)
				);

	//hugetlb_report_meminfo(m);

	arch_report_meminfo(m);

	return 0;
#undef K
}


static int meminfo_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, meminfo_proc_show, NULL);
}

static const struct file_operations meminfo_proc_fops = {
	.open		= meminfo_proc_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};


static int modulo_memoria_init(void)
{
        printk(KERN_ALERT "carne 200815396\n");
	proc_create("sjbg90", 0, NULL, &meminfo_proc_fops);
        return 0;
}

static void modulo_memoria_exit(void)
{
        printk(KERN_ALERT "adios modulo proceso descargado!\n");
}

module_init(modulo_memoria_init);
module_exit(modulo_memoria_exit);

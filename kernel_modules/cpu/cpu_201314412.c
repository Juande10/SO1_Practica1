#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_INFO */
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/uaccess.h>
#include <linux/hugetlb.h>
#include <linux/mm.h>
#include <linux/mman.h>
#include <linux/mmzone.h>
#include <linux/swap.h>
#include <linux/swapfile.h>
#include <linux/vmstat.h>
#include <linux/atomic.h>

MODULE_AUTHOR("Juan de Dios Molina Herrera - 201314412");
MODULE_DESCRIPTION("Escribir informacion del cpu.");
MODULE_LICENSE("GPL");

#define FileProc "cpu_201314412"

struct sysinfo mem;
long total;
long consumido;

static int show_cpu_stat(struct seq_file *f, void *v)
{

        si_meminfo(&mem);
        total = (mem.totalram * 4)/1024;
        consumido = ((mem.totalram - mem.freeram) * 4)/1024;
        seq_printf(f, "{\n");
        seq_printf(f, "\"usado\": %lu \n}\n", (consumido*100)/total);
        return 0;
}

static int cpuinfo_proc_open(struct inode *inode, struct file *file)
{
        size_t size = 1024 + 128 * num_online_cpus();
        size += 2 * nr_irqs;
        return single_open_size(file, show_cpu_stat, NULL, size);
}

static const struct file_operations Cpuinfo_fops = {
        .owner = THIS_MODULE,
        .open = cpuinfo_proc_open,
        .read = seq_read,
        .llseek = seq_lseek,
        .release = single_release,
};

static int __init start_function(void)
{
        printk(KERN_INFO "Modulo cpu cargado");
        proc_create(FileProc, 0777, NULL, &Cpuinfo_fops);
        printk(KERN_INFO "Archivo creado: /proc/%s.\n", FileProc);
        return 0;
}

static void __exit clean_function(void)
{
        remove_proc_entry(FileProc, NULL);
        printk(KERN_INFO "Modulo cpu eliminado :)");
}

module_init(start_function);
module_exit(clean_function);





#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched/signal.h>
#include <linux/sched.h>

#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <linux/seq_file.h>
#include <linux/proc_fs.h>
#include <linux/mm.h>

struct task_struct *task;
struct task_struct *task_child; 
struct list_head *list;         

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("CPU");
MODULE_AUTHOR("Juan de Dios Molina Herrera - 201314412");

int iterate_init(struct seq_file *archivo) /*    Init Module    */
{
    
    seq_printf(archivo, "-----------------------------------------------------------------OBTENIENDO PROCESOS---------------------------------------------------------------------\n");
    for_each_process(task)
    {                     
        char estadoq = 79; //otro estado
        if (task->state == TASK_RUNNING)
        {
            estadoq = 82;
        }
        else if (task->state == __TASK_STOPPED)
        {
            estadoq = 83;
        }
        else if (task->state == TASK_INTERRUPTIBLE)
        {
            estadoq = 73;
        }
        else if (task->state == TASK_UNINTERRUPTIBLE)
        {
            estadoq = 85;
        }
        else if (task->exit_state == EXIT_ZOMBIE)
        {
            estadoq = 90;
        }
        else if (task->state == TASK_DEAD)
        {
            estadoq = 68;
        }
        seq_printf(archivo, "\n\n\t\t| PID PROCESO ACTUAL: %d \t NOMBRE: %s \t ESTADO: %c |\n", task->pid, task->comm, estadoq); 
        int actual=1;
        list_for_each(list, &task->children)
        {                                                               
            task_child = list_entry(list, struct task_struct, sibling);

            char estado = 79; //otro estado
            if (task_child->state == TASK_RUNNING)
            {
                estado = 82;
            }
            else if (task_child->state == __TASK_STOPPED)
            {
                estado = 83;
            }
            else if (task_child->state == TASK_INTERRUPTIBLE)
            {
                estado = 73;
            }
            else if (task_child->state == TASK_UNINTERRUPTIBLE)
            {
                estado = 85;
            }
            else if (task_child->exit_state == EXIT_ZOMBIE)
            {
                estado = 90;
            }
            else if (task_child->state == TASK_DEAD)
            {
                estado = 68;
            }
            seq_printf(archivo, "\n%d) PPROCESO_PADRE: %s PID_PROCESO_PADRE%d || PID_HIJO: %d NOMBRE: %s ESTADO: %c \n", actual, task->comm, task->pid, task_child->pid, task_child->comm, estado);
            actual++;
        }
        seq_printf(archivo, "\n\n-----------------------------------------------------------------------------------------------------------------------------------------------------\n"); 
    }

    return 0;
}

static int write_file(struct seq_file *archivo, void *v)
{
    seq_printf(archivo, "\n");
    seq_printf(archivo, "      -------------------------------------\n");
    seq_printf(archivo, "      |     PROYECTO 1 - MODULO DE CPU    |\n");
    seq_printf(archivo, "      | LABORATORIO SISTEMAS OPERATIVOS 1 |\n");
    seq_printf(archivo, "      |           2SEM  2020              |\n");
    seq_printf(archivo, "      -------------------------------------\n");
    seq_printf(archivo, "\n");
    seq_printf(archivo, "      JUAN DE DIOS MOLINA HERRERA - 201314412\n");
    seq_printf(archivo, "\n");
    seq_printf(archivo, "      -------------------------------------\n");
    seq_printf(archivo, "      |              ESTADOS              |\n");
    seq_printf(archivo, "      |  TASK_RUNNING         =        R  |\n");
    seq_printf(archivo, "      |  TASK_INTERRUPTIBLE   =        I  |\n");
    seq_printf(archivo, "      |  TASK_UNINTERRUPTIBLE =        U  |\n");
    seq_printf(archivo, "      |  TASK_STOPPED         =        S  |\n");
    seq_printf(archivo, "      |  TASK_ZOMBIE          =        Z  |\n");
    seq_printf(archivo, "      |  OTRO_TASK            =        0  |\n");
    seq_printf(archivo, "      -------------------------------------\n");
    seq_printf(archivo, "\n");
    return iterate_init(archivo);
}

static int abrir(struct inode *inode, struct file *file)
{
    return single_open(file, write_file, NULL);
}

static struct file_operations ops =
    {
        .open = abrir,
        .read = seq_read

};

static int iniciar(void)
{
    proc_create("cpu_201314412", 0, NULL, &ops);
    printk(KERN_INFO "\nNombre:Juan de Dios Molina Herrera");
    return 0;
}

static void salir(void)
{
    remove_proc_entry("cpu_201314412", NULL);
    printk(KERN_INFO "\nSistemas Operativos 1\n");
}


void cleanup_exit(void) 
{

    printk(KERN_INFO "%s", "REMOVING MODULE\n");

} 

module_init(iniciar);
module_exit(salir); 

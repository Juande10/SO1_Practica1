#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/uaccess.h>
#include <linux/hugetlb.h>
#include <linux/sched/signal.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>

struct list_head *p;
struct task_struct *proceso, ts, *tsk;

#define BUFSIZE 150

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Lista de procesos...");
MODULE_AUTHOR("Juan de Dios Molina Herrera");

static int escribir_archivo(struct seq_file *archivo, void *v)
{
    int pros = 0;
    int pros2 = 0;
    seq_printf(archivo, "{\n");
    seq_printf(archivo, "\"procesos\":[\n");

    bool seconditerative=false;

    for_each_process(proceso)
    {

        //seq_printf(archivo, "{\n\"proceso%i\":{\n", pros2);
        if(seconditerative){
        seq_printf(archivo, ",");    
        }else{
            seconditerative=true;
        }

        seq_printf(archivo, "{\n");
        seq_printf(archivo, "\"PID\": %d, \n", proceso->pid);
        seq_printf(archivo, "\"Nombre\": \"%s\", \n", proceso->comm);
        seq_printf(archivo, "\"Usuario\": %d, \n", (int) proceso->sessionid);
        //seq_printf(archivo, "\"Memory\": \"%lu\", \n",(unsigned long) proceso->mm->start_data);
        //printf("ULONG_MAX   :   %lu\n", (unsigned long) ULONG_MAX);
        seq_printf(archivo, "\"Memory\": \"%d\", \n",__kuid_val(proceso->real_cred->uid)); //__kuid_val(s->real_cred->uid)
        seq_printf(archivo, "\"Estado\": %ld} \n", proceso->state);


        list_for_each(p, &(proceso->children))
        {
            
            //seq_printf(archivo, "    -------------------------------\n");
            seq_printf(archivo, ",{\n");
            //seq_printf(archivo, "   \"procesoh%i\":{\n", cont);
            //seq_printf(archivo, "{\n");
            ts = *list_entry(p, struct task_struct, sibling);
            seq_printf(archivo, "     \"Proceso padre\":%d,\n", proceso->pid);
            seq_printf(archivo, "     \"PID\":%d, \n", ts.pid);
            seq_printf(archivo, "     \"Nombre\":\"%s\",\n", ts.comm);
            seq_printf(archivo, "     \"Usuario\": %d, \n", (int) proceso->sessionid);
            seq_printf(archivo, "     \"Estado\":%ld \n", ts.state);
            
             seq_printf(archivo, "}\n");
        }

    }
    seq_printf(archivo, "],\n");
    seq_printf(archivo, "\"arbol\":[\n");
    
    seconditerative=false;
    for_each_process(proceso)
    {
        if(seconditerative){
        seq_printf(archivo, ",");    
        }else{
            seconditerative=true;
        }

        seq_printf(archivo, "{\n");
        seq_printf(archivo, "\"id\": %d, \n", proceso->pid);
        seq_printf(archivo, "\"parentId\": %d ,\n",0);
        seq_printf(archivo, "\"label\": \"%s\", \n", proceso->comm);
        //seq_printf(archivo, "\"Usuario\": %d, \n", (int) proceso->sessionid);
        //seq_printf(archivo, "\"Memory\": \"%ld\", \n",(long) proceso->mm->total_vm);
        //seq_printf(archivo, "\"Estado\": %ld} \n", proceso->state);
        seq_printf(archivo, "\"items\": %s \n", "[]");
        seq_printf(archivo, "}\n");
        list_for_each(p, &(proceso->children))
        {
            
            seq_printf(archivo, ",{\n");
            ts = *list_entry(p, struct task_struct, sibling);
            seq_printf(archivo, "     \"id\":%d, \n", ts.pid);
            seq_printf(archivo, "     \"label\":\"%s\",\n", ts.comm);
            seq_printf(archivo, "     \"parentId\":%d,\n", proceso->pid);
            //seq_printf(archivo, "     \"Usuario\": %d, \n", (int) proceso->sessionid);
            //seq_printf(archivo, "     \"Estado\":%ld \n", ts.state);
            seq_printf(archivo, "\"items\": %s \n", "[]");
             seq_printf(archivo, "}\n");
        }
        
        
    }
    
    seq_printf(archivo, "]\n");

    seq_printf(archivo, "}\n");

    return 0;
}

static int al_abrir(struct inode *inode, struct file *file)
{
    return single_open(file, escribir_archivo, NULL);
}

static struct file_operations operaciones =
    {
        .open = al_abrir,
        .read = seq_read};

static int iniciar(void)
{
    proc_create("cpu_practica1", 0, NULL, &operaciones);
    printk(KERN_INFO "Practica 1 sopes 1\n");
    return 0;
}

static void salir(void)
{
    remove_proc_entry("cpu_practica1", NULL);
    printk(KERN_INFO "Sistemas Operativos 2\n");
}

module_init(iniciar);
module_exit(salir);


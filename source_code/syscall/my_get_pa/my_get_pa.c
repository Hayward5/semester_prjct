#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/mm.h>
#include <linux/sched.h>

/*

SYSCALL_DEFINEn(), n 
The ‘n’ indicates the number of arguments to the system call,
and the macro takes the system call name followed by the (type, name) pairs as arguments.

*/
SYSCALL_DEFINE1(my_get_physical_addresses, void __user *, addr_p)
{
    unsigned long vaddr = (unsigned long)addr_p;
    pgd_t *page_global_directory;
    p4d_t *page_4_directory;
    pud_t *page_upper_directory;
    pmd_t *page_middle_directory;
    pte_t *page_table_entry;
    unsigned long paddr = 0;
    unsigned long page_addr = 0;
    unsigned long page_offset = 0;

    page_global_directory = pgd_offset(current->mm, vaddr);
    if (pgd_none(*page_global_directory))
    {
        printk(KERN_INFO "Address not mapped in page_global_directory\n");
        return 0;
    }

    page_4_directory = p4d_offset(page_global_directory, vaddr);
    if (p4d_none(*page_4_directory))
    {
        printk(KERN_INFO "Address not mapped in page_4_directory\n");
        return 0;
    }

    page_upper_directory = pud_offset(page_4_directory, vaddr);
    if (pud_none(*page_upper_directory))
    {
        printk(KERN_INFO "Address not mapped in page_upper_directory\n");
        return 0;
    }

    page_middle_directory = pmd_offset(page_upper_directory, vaddr);
    if (pmd_none(*page_middle_directory))
    {
        printk(KERN_INFO "Address not mapped in page_middle_directory\n");
        return 0;
    }

    page_table_entry = pte_offset_kernel(page_middle_directory, vaddr);
    if (pte_none(*page_table_entry))
    {
        printk(KERN_INFO "Address not mapped in page_table_entry\n");
        return 0;
    }
    
    // Definition: PAGE_MASK 0xfffff000
    /* Page frame physical address mechanism | offset */
    page_addr = pte_val(*page_table_entry) & PAGE_MASK;
    page_offset = vaddr & ~PAGE_MASK;
    paddr = page_addr | page_offset;

    return paddr;
}
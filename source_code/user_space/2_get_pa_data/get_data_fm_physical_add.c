#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

//void * my_get_physical_addresses(void *);
void * my_get_physical_addresses(void *);

int a[2000000]; // 2 Million int

int main()
{
    int loc_a;
    void *phy_add; phy_add = my_get_physical_addresses(&a[0]);
    printf("global element a[0]:\n");
    printf("Offest of logical address:[%p] Physical address:[%p]\n", &a[0], phy_add);
    printf("========================================================================\n");
    
    phy_add = my_get_physical_addresses(&a[1999999]);
    printf("global element a[1999999]:\n");
    printf("Offest of logical address:[%p] Physical address:[%p]\n", &a[1999999], phy_add);
    printf("========================================================================\n");
}

// void * my_get_physical_addresses(void *)
// {

// }


// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/types.h>
// #include <unistd.h>
// #include <pthread.h>

// void *my_get_physical_addresses(void *); // syscall declaration

// int a[2000000]; // 2 Million int (approximately 8 MB on a 32-bit int system)

// // Thread function to get the physical address of a part of the array
// void *check_physical_address(void *arg) {
//     int index = *(int *)arg;
//     void *phy_add = my_get_physical_addresses(&a[index]);

//     printf("Array element a[%d]:\n", index);
//     printf("Offset of logical address:[%p] Physical address:[%p]\n", &a[index], phy_add);
//     printf("========================================================================\n");

//     pthread_exit(phy_add); // return physical address for comparison
// }

// int main() {
//     int start_index = 0;
//     int end_index = 1999999;

//     // Print addresses in single-thread mode
//     printf("Checking physical addresses in single-thread mode:\n");
//     void *phy_add_start = my_get_physical_addresses(&a[start_index]);
//     void *phy_add_end = my_get_physical_addresses(&a[end_index]);

//     printf("Array element a[%d]:\n", start_index);
//     printf("Offset of logical address:[%p] Physical address:[%p]\n", &a[start_index], phy_add_start);
//     printf("========================================================================\n");

//     printf("Array element a[%d]:\n", end_index);
//     printf("Offset of logical address:[%p] Physical address:[%p]\n", &a[end_index], phy_add_end);
//     printf("========================================================================\n");

//     // Create two threads to simulate concurrent access
//     pthread_t thread1, thread2;

//     // Run each thread to check physical address
//     printf("\nChecking physical addresses in multi-thread mode:\n");
//     pthread_create(&thread1, NULL, check_physical_address, &start_index);
//     pthread_create(&thread2, NULL, check_physical_address, &end_index);

//     // Collect physical addresses returned by each thread
//     void *phy_addr_thread1;
//     void *phy_addr_thread2;
//     pthread_join(thread1, &phy_addr_thread1);
//     pthread_join(thread2, &phy_addr_thread2);

//     // Compare physical addresses to check for shared memory
//     if (phy_addr_thread1 == phy_addr_thread2) {
//         printf("Physical address is the same for both threads. Pages are shared (not fully loaded).\n");
//     } else {
//         printf("Physical addresses differ for each thread. Memory pages are loaded.\n");
//     }

//     return 0;
// }

void * my_get_physical_addresses(void *vaddr)
{
    void *result = (void *)syscall(462, vaddr);  // Replace 336 with your actual syscall number
    if ((long)result == -1)
    {
        perror("Error calling my_get_physical_addresses");
    }
    return result;
}
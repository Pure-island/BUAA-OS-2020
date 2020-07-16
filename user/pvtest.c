#include "lib.h"


void umain()
{
    int i,j;
	int id =  syscall_init_PV_var(0);
    int f = fork();
    if(f==0){
        while(1)
             for(i=0;i<10;i++) {
                 syscall_P(id);
                 j = syscall_check_PV_value(id);
                 writef("p %d\n",j);
             }
    }
    else{
        while(1)
             if(syscall_check_PV_value(id)<=100)for(i=0;i<10;i++) {
                 syscall_V(id);
                 j = syscall_check_PV_value(id);
                 writef("v %d\n",j);
            }
    }
    return;
}


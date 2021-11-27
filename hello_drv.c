#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<asm/uaccess.h>

#define HELLO_MAJOR_NUM 290
#define HELLO_NAME "hello"



static int hello_open(struct inode *node,struct file *pfile){
    printk("hello_open enter\n");
    return 0;
}


static ssize_t hello_read(struct file *pfile,char __user *pBuff,size_t size,loff_t *filepos){
    char arrData[4]={'1','2','3','4'};
    printk("hello_read enter\n");
    if(size>=4){
        copy_to_user(pBuff,arrData,4);
        return 4;
    }
    return 0;
}

static ssize_t hello_write(struct file *pfile, const char __user *pBuff,size_t size,loff_t *filepos){
    char arrData[4];
    printk("hello_Write enter\n");
      if(size>=4){
        copy_from_user(arrData,pBuff,4);
          //get_user(i, pBuff);  
        return 4;
}
    return 0;
}

static int hello_release(struct inode *node, struct file *pfile)
{
    printk("hello_release enter\n");
    return 0;
}

static const struct file_operations hello_fops={
    .owner=THIS_MODULE,
    .open=hello_open,
    .read=hello_read,
    .write=hello_write,
    .release=hello_release,
};

int flagRegisterSuccess=0;




int __init init_hello(void){
    int ret;
    printk("hello world\n");
    ret=register_chrdev(HELLO_MAJOR_NUM,HELLO_NAME,&hello_fops);
    if(ret<0)
    {
        printk("hello registr_chrdev fail\n");
        return ret;
    }
    flagRegisterSuccess=1;
    return 0;
}




void __exit exit_hello(void){
    if(flagRegisterSuccess)
    {
        flagRegisterSuccess=0;
        unregister_chrdev(HELLO_MAJOR_NUM,HELLO_NAME);
    }
    printk("Good Bye~\n");
}

module_init(init_hello);
module_exit(exit_hello);

 MODULE_LICENSE("GPL");





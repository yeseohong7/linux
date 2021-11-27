#include <linux/init.h>  //module_init, module_exit 매크로 정의
#include <linux/kernel.h> //printk 함수 정의
#include <linux/module.h> // 모듈 관련 자료 구조 및 매크로 정의 
#include <linux/fs.h>

int yeseo_open(struct inode *InodeYS, struct file *FileYs){
    printk("file opened");
    return 0;
}

int yeseo_read(struct file *FileYs,char* Data,size_t s,loff_t *lof){
    printk("read request");
    return 0;
}
//int yeseo_write(struct file *FileYs,char* Data,size_t s,loff_t *lof){
    // printk("//

int yeseo_release(struct inode *inode,struct file *filp){
    printk("devicenode closed");
    return 0;
}

struct file_operations yeseoDrvLinkTable={
    .owner=THIS_MODULE,
    .open= yeseo_open,
    .release=test_release,
};

                                   // (~/ecube/linux_kernel/include/...)
int init(void) //_init:optional 쏘면 좋고 안써도 됨
{
    register_chrdev(999,"yeseoNewDriver",&yeseoDrvLinkTable);
	printk("Hello World.\n");
	return 0;
}

void exiT(void) //_exit: optional
{
	printk("Good-bye~ \n");
    unregister_chrdev(999,"yeseoNewDriver");
}
module_init(init);  //모듈 로딩시 해당 함수 호출
module_exit(exiT);  //모듈 제거시 해당 함수 호출

MODULE_LICENSE("GPL");

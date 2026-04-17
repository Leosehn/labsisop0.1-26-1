#include <linux/module.h>
#include <linux/init.h>
#include <linux/printk.h>
#include <linux/hrtimer.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Leonardo");
MODULE_DESCRIPTION("Timer Module");
MODULE_VERSION("0.0.1");

#define TIMEOUT_SEC 1
#define TIMEOUT_NSEC 0

static struct hrtimer hr_timer;

static enum hrtimer_restart timer_callback(struct hrtimer *);

static enum hrtimer_restart timer_callback(struct hrtimer *timer)
{
    pr_info("Hello from timer!\n");
	ktime_t ktime = ktime_set(TIMEOUT_SEC, TIMEOUT_NSEC);
	hrtimer_forward_now(timer, ktime);

	return HRTIMER_RESTART;
}

static int timerdrv_init(void)
{
    pr_info("Inserting the Timer module\n");

    hrtimer_init(&hr_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
    hr_timer.function = timer_callback;

    ktime_t ktime = ktime_set(TIMEOUT_SEC, TIMEOUT_NSEC);
    hrtimer_start(&hr_timer, ktime, HRTIMER_MODE_REL);

    return 0;
}

static void timerdrv_exit(void)
{
    hrtimer_cancel(&hr_timer);
    pr_info("Removed the Timer module\n");
}

module_init(timerdrv_init);
module_exit(timerdrv_exit);